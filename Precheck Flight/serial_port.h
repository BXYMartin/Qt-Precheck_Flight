#pragma once

#include <assert.h>
#include <process.h>
#include <thread>
#include <windows.h>
#include "def_type.h"

#define _SERIALPORT_READ_STANDALONE_TASK

class CSerialPortHandle 
{
public:
	virtual ~CSerialPortHandle() = default;
	virtual void DataHandle(uint8_t* data, size_t size) = 0;
};

class CSerialPort
{
public:
	CSerialPort(CSerialPortHandle* callback);
	virtual ~CSerialPort();

	bool Open(uint32_t port, uint32_t baudrate);
	bool Close();
	bool IsOpen();

	size_t Write(uint8_t* buf, size_t length, bool wait_finish = false);

	uint32_t Port();
	void ClearCache();

#ifndef _SERIALPORT_READ_STANDALONE_TASK
	void Process();
#else
protected:
	void Process();
	void ReadTask();
#endif

private:
	bool Port(uint32_t com);
	string_t PortToString(uint32_t port);

protected:
	uint32_t _port;
	OVERLAPPED  _os_read, _os_write;
	HANDLE _handle;
	bool _open;
	CSerialPortHandle* _callback;

#ifdef _SERIALPORT_READ_STANDALONE_TASK
	std::thread _thread;
#endif
};
