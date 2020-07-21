#include "PrecheckHandler.h"

PrecheckHandler::PrecheckHandler()
{

}

bool PrecheckHandler::checkFrame(PrecheckStateMachine::State state, uint8_t* frame)
{
	return true;
	// 检查副帧头部
	for (int i = 0; i < 4; i++)
		if (frame[i*64] != 0xEB || frame[i*64+1] != 0x90)
			return false;
	int offset = 64 * 3 - 1; // 适应标准中的从 1 计数
	switch (state)
	{
	case PrecheckStateMachine::GND_INIT:
		// 行为未知，空过
		break;
	case PrecheckStateMachine::PUBIT_CONNECT:
		if (frame[offset + 3] != 0x78) // 第四副帧计数
			return false;
		if (frame[offset + 5] & 0b10000001 || frame[offset + 6] & 0b10000001)
			return false;
		for (int i = 5; i < 12; i += 2) // MIO 检查
			if (frame[offset + i] & 0b10000000 || frame[offset + i + 1] & 0b00000001)
				return false;
		if (frame[offset + 13] & 0b01000001 || frame[offset + 14] & 0b10000001)
			return false;
		if (frame[offset + 15] & 0b10000000 || frame[offset + 16] & 0b00000001)
			return false;
		break;
	case PrecheckStateMachine::PUBIT_RESULT:
		if (frame[offset + 3] != 0x78) // 第四副帧计数
			return false;
		for (int i = 5; i < 10; i+=2) // CPU 检查
			if (frame[offset + i] & 0b10111101 || frame[offset + i + 1] & 0b11111111)
				return false;
		if (frame[offset + 11] & 0b00000111 || frame[offset + 12] & 0b00111111)
			return false;
		for (int i = 13; i < 16; i+=2) // MIO 检查
			if (frame[offset + i] & 0b00111111 || frame[offset + i + 1] & 0b11111111)
				return false;
		if (frame[offset + 17] & 0b00111111 || frame[offset + 18] & 0b10011111)
			return false;
		break;
	case PrecheckStateMachine::CHANNEL_LOGIC:
		if (frame[offset + 3] != 0x78) // 第四副帧计数
			return false;
		for (int i = 5; i < 10; i += 2) // CPU 检查
			if (frame[offset + i] & 0b00001111 || frame[offset + i + 1] & 0b11111111)
				return false;
		break;
	}

	return true;
}

void PrecheckHandler::generateFrame(PrecheckStateMachine::State state, uint8_t* frame)
{
	for (int i = 0; i < 64; i++)
		frame[i] = 0x00;
	fillHeader(frame);
	fillType(frame);
	fillInstruction(state, frame);
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
	default:
		frame[0x0E] = 0xEC;
		frame[0x0F] = 0xEC;
		frame[0x10] = 0xEC;
		frame[0x12] = 0x30;
		break;
	}
	frame[0x11] = 0x33;
}