#include "PrecheckHandler.h"

#pragma execution_character_set("utf-8")

unsigned short CRC16_XMODEM(uint8_t *puchMsg, unsigned int usDataLen)
{
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;

	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for (int i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin);
}

PrecheckHandler::PrecheckHandler(PrecheckThread* callback)
{
	response = callback;
}

void PrecheckHandler::genReport(uint8_t item, uint8_t mask, PrecheckStateMachine::State state, char* function, char* message, bool* passed)
{
	if (!(item & mask))
	{
		emit(response->sendDetailsToWindow(state, PrecheckStateMachine::FINISH, function, message));
	}
	else
	{
		*passed = false;
		emit(response->sendDetailsToWindow(state, PrecheckStateMachine::FAILED, function, message));
	}
}

bool PrecheckHandler::checkFrame(PrecheckStateMachine::State state, uint8_t* frame)
{
	bool passed = true;
	//emit(response->sendDetailsToWindow(PrecheckStateMachine::GND_INIT, PrecheckStateMachine::FAILED, "测试", "hh"));
	//return true;

	char message[128];
	// 检查副帧头部
	/*for (int i = 0; i < 4; i++)
	{
		sprintf(message, "第 %d 副帧头部返回 0x%02x 0x%02x 应为 0xEB 0x90", i + 1, frame[i * 64], frame[i * 64 + 1]);
		genReport(frame[i * 64 + 1], 0b01101111, state, "副帧头检查", message, &passed);
		genReport(frame[i * 64], 0b00010100, state, "副帧头检查", message, &passed);
	}*/
		
	int offset = -1; // 适应标准中的从 1 计数
	switch (state)
	{
	case PrecheckStateMachine::GND_INIT:
	case PrecheckStateMachine::GND_TEST:
		// 行为未知，空过
		break;
	case PrecheckStateMachine::PUBIT_CONNECT:
		sprintf(message, "第 4 副帧返回 %02x%02x-%02x-%02x", frame[offset + 21], frame[offset + 22], frame[offset + 19], frame[offset + 20]);
		genReport(0, 0, state, "飞控日期信息", message, &passed);
		sprintf(message, "第 4 副帧返回 %c%c%c%c%c%c%c%c%c%c%c%c", frame[offset + 23], frame[offset + 24], frame[offset + 25], frame[offset + 26], frame[offset + 27], frame[offset + 28], frame[offset + 29], frame[offset + 30], frame[offset + 60], frame[offset + 61], frame[offset + 62], frame[offset + 63]);
		genReport(0, 0, state, "飞控版本信息", message, &passed);
		// 不退出，继续
	default:
		sprintf(message, "第 4 副帧头部返回 0x%02x 应为 0x78", frame[offset + 3]);
		genReport(frame[offset + 3], 0b10000111, state, "第 4 副帧计数检查", message, &passed);
		
		for (int i = 0; i < sizeof(list) / sizeof(list[0]); i++)
		{
			if (list[i].state == state)
			{
				genReport(frame[offset + list[i].position], list[i].mask, state, list[i].function, list[i].message, &passed);
			}
		}

		break;
	}

	return passed;
}

void PrecheckHandler::generateFrame(PrecheckStateMachine::State state, uint8_t* frame)
{
	for (int i = 0; i < 64; i++)
		frame[i] = 0x00;
	fillHeader(frame);
	fillType(frame);
	fillInstruction(state, frame);
	frame[0x3E] = CRC16_XMODEM(frame, 62) & 0b0000000011111111;
	frame[0x3F] = CRC16_XMODEM(frame, 62) >> 8;
}

void PrecheckHandler::fillHeader(uint8_t* frame)
{
	frame[0x00] = 0xEB;
	frame[0x01] = 0x90;
}

void PrecheckHandler::fillType(uint8_t* frame)
{
	frame[0x02] = 0xFF; // 地检
	frame[0x03] = 0x00;
	frame[0x04] = 0x00;
	frame[0x05] = 0xEC;
}

void PrecheckHandler::fillInstruction(PrecheckStateMachine::State state, uint8_t* frame)
{
	switch (state)
	{
	case PrecheckStateMachine::GND_INIT:
		frame[0x0E] = 0xAB;
		frame[0x0F] = 0xAB;
		frame[0x10] = 0xAB;
		frame[0x12] = 0x30;
		break;
	case PrecheckStateMachine::PUBIT_CONNECT:
		frame[0x0E] = 0xEC;
		frame[0x0F] = 0xEC;
		frame[0x10] = 0xEC;
		frame[0x12] = 0x32;
		break;
	case PrecheckStateMachine::PUBIT_RESULT:
		frame[0x0E] = 0xEC;
		frame[0x0F] = 0xEC;
		frame[0x10] = 0xEC;
		frame[0x12] = 0x31;
		break;
	case PrecheckStateMachine::CHANNEL_LOGIC:
		frame[0x0E] = 0xEC;
		frame[0x0F] = 0xEC;
		frame[0x10] = 0xEC;
		frame[0x12] = 0x33;
		break;
	default:
		frame[0x0E] = 0xEC;
		frame[0x0F] = 0xEC;
		frame[0x10] = 0xEC;
		frame[0x12] = 0x30;
		break;
	}
	frame[0x11] = 0x33;
}