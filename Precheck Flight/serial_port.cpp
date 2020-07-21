#include <tchar.h>
#include <stdio.h>
#include <sstream>
#include <algorithm>
#include "serial_port.h"

CSerialPort::CSerialPort(CSerialPortHandle* callback):
	_handle(NULL),
	_open(false),
	_callback(callback),
	_port(0)
{
	memset(&_os_read, 0, sizeof(OVERLAPPED));
	memset(&_os_write, 0, sizeof(OVERLAPPED));
}

CSerialPort::~CSerialPort()
{
	Close();
}

bool CSerialPort::Open(uint32_t port, uint32_t baudrate)
{
	if (IsOpen())
	{
		return true;
	}

	_open = true;
	if (!Port(port))
	{
		Close();
		return false;
	}

	string_t str_port = PortToString(port);

	// 为重叠读创建事件对象，手工重置，初始化为无信号的
	if ((_os_read.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
	{
		Close();
		return false;
	}
	// 为重叠写创建事件对象，手工重置，初始化为无信号的
	if ((_os_write.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL)) == NULL)
	{
		Close();
		return false;
	}

	DCB dcb;
	_handle = CreateFile(str_port.c_str(),
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		NULL
	);
	if (_handle == INVALID_HANDLE_VALUE)
	{
		_handle = NULL;
		Close();
		return false;
	}
	//设置事件驱动的类型 
	if (!SetCommMask(_handle, EV_RXCHAR | EV_TXEMPTY))
	{
		Close();
		return false;
	}
	//设置输入、输出缓冲区的大小
	if (!SetupComm(_handle, 1024, 1024))
	{
		Close();
		return false;
	}

	//清空输入、输出缓冲区
	if (!PurgeComm(_handle, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR
		| PURGE_RXCLEAR))
	{
		Close();
		return false;
	}

	COMMTIMEOUTS time_outs; //定义超时结构，并填写该结构
	time_outs.ReadIntervalTimeout = MAXDWORD;
	time_outs.ReadTotalTimeoutConstant = 50;
	time_outs.ReadTotalTimeoutMultiplier = 50;
	time_outs.WriteTotalTimeoutConstant = 50;
	time_outs.WriteTotalTimeoutMultiplier = 50;

	if (!SetCommTimeouts(_handle, &time_outs))
	{
		Close();
		return false;
	}
	//读串口原来的参数设置
	if (!GetCommState(_handle, &dcb))
	{
		Close();
		return false;
	}
	dcb.BaudRate = baudrate;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE;
	//串口参数配置
	if (!SetCommState(_handle, &dcb))
	{
		Close();
		return false;
	}

	PurgeComm(_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

#ifdef _SERIALPORT_READ_STANDALONE_TASK
	_thread = std::thread(&CSerialPort::ReadTask, this);
#endif

	return true;
}

bool CSerialPort::Close()
{
	if (!IsOpen())
	{
		return true;
	}

	_open = false;
#ifdef _SERIALPORT_READ_STANDALONE_TASK
	if (_thread.joinable())
	{
		_thread.join();
	}
#endif

	if (_handle != NULL)
	{
		CloseHandle(_handle);
	}

	if (_os_read.hEvent != NULL)
	{
		CloseHandle(_os_read.hEvent);
	}

	if (_os_write.hEvent)
	{
		CloseHandle(_os_write.hEvent);
	}

	memset(&_os_read, 0, sizeof(OVERLAPPED));
	memset(&_os_write, 0, sizeof(OVERLAPPED));
	_handle = NULL;

	return true;
}

bool CSerialPort::IsOpen()
{
	return _open;
}

size_t CSerialPort::Write(uint8_t* buf, size_t length, bool wait_finish/* = false*/)
{
	if (!IsOpen())
	{
		return 0;
	}

	DWORD write_len = 0;
	try
	{
		COMSTAT com_stat;
		DWORD error_flags;
		ClearCommError(_handle, &error_flags, &com_stat);
		if (WriteFile(_handle, buf, length, &write_len, &_os_write) == FALSE)
		{
			write_len = 0;
			DWORD error = GetLastError();
			if (error == ERROR_IO_PENDING)
			{
				if (::GetOverlappedResult(_handle, &_os_write, &write_len, wait_finish ? TRUE : FALSE) == FALSE)
				{
					write_len = 0;
				}
			}
		}
	}
	catch (...)
	{
		PurgeComm(_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		return 0;
	}

	return write_len;
}

uint32_t CSerialPort::Port()
{
	if (!IsOpen())
	{
		return 0;
	}
	return _port;
}

bool CSerialPort::Port(uint32_t com)
{
	if (com <= 0 || com >= 999)
	{
		return false;
	}

	_port = com;

	return true;
}

void CSerialPort::ClearCache()
{
	if (!IsOpen())
	{
		return;
	}
	PurgeComm(_handle, PURGE_TXCLEAR);
}

void CSerialPort::Process()
{
	if (!IsOpen())
	{
		return;
	}

	try
	{
		uint8_t buf[10240];
		uint32_t read_length = 10240;

		DWORD com_mask;
		COMSTAT com_stat;
		DWORD error_flags;
		DWORD rtl_read_length = 0;

		com_mask = 0;
		_os_read.Offset = 0;

		if (ClearCommError(_handle, &error_flags, &com_stat) == FALSE)
		{
			return;
		}
		if (com_stat.cbInQue > 0)
		{
			read_length = std::min<uint32_t>(read_length, com_stat.cbInQue);
			if (ReadFile(_handle, buf, read_length, &rtl_read_length, &_os_read) == FALSE)
			{
				rtl_read_length = 0;
				DWORD error = GetLastError();
				if (error == ERROR_IO_PENDING)
				{
					if (GetOverlappedResult(_handle, &_os_read, &rtl_read_length, TRUE) == FALSE)
					{
						ClearCommError(_handle, &error_flags, &com_stat);
					}
				}
				else
				{
					return;
				}
			}

			if (rtl_read_length > read_length)
			{
				rtl_read_length = read_length;
			}

			//LOG_CONSOLE_IF(INFO, LOG_LEVEL_INFO >= 4) << "[" << _port << ",read_" << rtl_read_length << "]" << CBuffer<uint8_t>(buf, rtl_read_length);
			if (_callback != nullptr)
			{
				_callback->DataHandle(buf, rtl_read_length);
			}

			return;
		}
	}
	catch (...)
	{
		PurgeComm(_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	}

	return;
}

string_t CSerialPort::PortToString(uint32_t port)
{
#ifdef _UNICODE
	std::wstringstream stream;
#else
	std::stringstream stream;
#endif // _UNICODE


	if (port > 9)
	{
		stream << _T("\\\\.\\COM") << port;
	}
	else
	{
		stream << _T("COM") << port;
	}

	return stream.str();
}

#ifdef _SERIALPORT_READ_STANDALONE_TASK
void CSerialPort::ReadTask()
{
	DWORD com_mask;

	while (_open)
	{
		_os_read.Offset = 0;
		_os_read.Internal = 0;
		_os_read.InternalHigh = 0;
		_os_read.Offset = 0;
		_os_read.OffsetHigh = 0;
		com_mask = 0;

		if (WaitCommEvent(_handle, &com_mask, &_os_read) == TRUE)
		{
			Process();
		}
		else
		{
			DWORD rtl = GetLastError();
			if (ERROR_IO_PENDING == rtl)
			{
				Process();
			}
			else
			{
				//LOG(FATAL) << "等待串口读取失败" << GetLastError();
			}
		}
	}
	return;
}
#endif

