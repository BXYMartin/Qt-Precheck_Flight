#include "PrecheckHandler.h"

#pragma execution_character_set("utf-8")

PrecheckHandler::PrecheckHandler(PrecheckThread* callback)
{
	response = callback;
}

void PrecheckHandler::genReport(bool accord, PrecheckStateMachine::State state, char* function, char* message, bool* passed)
{
	char temp[128];
	std::strcpy(temp, message);
	char temp_1[128];
	std::strcpy(temp_1, function);
	if (!accord)
	{
		emit(response->sendDetailsToWindow(state, PrecheckStateMachine::FINISH, temp_1, temp));
	}
	else
	{
		*passed = false;
		emit(response->sendDetailsToWindow(state, PrecheckStateMachine::FAILED, temp_1, temp));
	}
}

bool PrecheckHandler::checkFrame(PrecheckStateMachine::State state, uint8_t* frame)
{
	bool passed = true;
	//emit(response->sendDetailsToWindow(PrecheckStateMachine::GND_INIT, PrecheckStateMachine::FAILED, "测试", "hh"));
	//return true;

	char message[128];
	// 检查副帧头部
	for (int i = 0; i < 4; i++)
	{
		sprintf(message, "第 %d 副帧头部返回 0x%02x 0x%02x 应为 0xEB 0x90", i + 1, frame[i * 64], frame[i * 64 + 1]);
		genReport(frame[i * 64] != 0xEB || frame[i * 64 + 1] != 0x90, state, "副帧头检查", message, &passed);
	}
		
	int offset = 64 * 3 - 1; // 适应标准中的从 1 计数
	switch (state)
	{
	case PrecheckStateMachine::GND_INIT:
		// 行为未知，空过
		break;
	case PrecheckStateMachine::PUBIT_CONNECT:
		sprintf(message, "第 4 副帧头部返回 0x%02x 应为 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "第 4 副帧计数检查", message, &passed);
		
		sprintf(message, "第 4 副帧第 5 字节输入返回 0x%02x 应为 0x00", frame[offset + 5] & 0b10000001);
		genReport(frame[offset + 5] & 0b10000001, state, "MIO 板 2 模拟", message, &passed);

		sprintf(message, "第 4 副帧第 6 字节输入返回 0x%02x 应为 0x00", frame[offset + 6] & 0b10000001);
		genReport(frame[offset + 6] & 0b10000001, state, "MIO 板 1 模拟", message, &passed);

		sprintf(message, "第 4 副帧第 7、8 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 7] & 0b10000000, frame[offset + 7 + 1] & 0b00000001);
		genReport(frame[offset + 7] & 0b10000000 || frame[offset + 7 + 1] & 0b00000001, state, "MIO 板 2 离散输入", message, &passed);

		sprintf(message, "第 4 副帧第 9、10 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 9] & 0b10000000, frame[offset + 9 + 1] & 0b00000001);
		genReport(frame[offset + 9] & 0b10000000 || frame[offset + 9 + 1] & 0b00000001, state, "MIO 板 1 离散输入", message, &passed);

		sprintf(message, "第 4 副帧第 11、12 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 11] & 0b10000000, frame[offset + 11 + 1] & 0b00000001);
		genReport(frame[offset + 11] & 0b10000000 || frame[offset + 11 + 1] & 0b00000001, state, "MIO 板 1 422/485 回绕 1~16", message, &passed);

		sprintf(message, "第 4 副帧第 13 字节输入返回 0x%02x 应为 0x00", frame[offset + 13] & 0b01000001);
		genReport(frame[offset + 13] & 0b01000001, state, "MIO 板 1 422/485 回绕 17~24", message, &passed);

		sprintf(message, "第 4 副帧第 14 字节输入返回 0x%02x 应为 0x00", frame[offset + 14] & 0b10000001);
		genReport(frame[offset + 14] & 0b10000001, state, "MIO 板 2 422/485 回绕 1~8", message, &passed);

		sprintf(message, "第 4 副帧第 15、16 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 15] & 0b10000000, frame[offset + 15 + 1] & 0b00000001);
		genReport(frame[offset + 15] & 0b10000000 || frame[offset + 15 + 1] & 0b00000001, state, "MIO 板 1 422/485 回绕 9~24", message, &passed);

		sprintf(message, "第 4 副帧返回 %02x%02x-%02x-%02x", frame[offset + 21], frame[offset + 22], frame[offset + 19], frame[offset + 20]);
		genReport(true, state, "飞控日期信息", message, &passed);

		sprintf(message, "第 4 副帧返回 %c%c%c%c%c%c%c%c%c%c%c%c", frame[offset + 23], frame[offset + 24], frame[offset + 25], frame[offset + 26], frame[offset + 27], frame[offset + 28], frame[offset + 29], frame[offset + 30], frame[offset + 60], frame[offset + 61], frame[offset + 62], frame[offset + 63]);
		genReport(true, state, "飞控版本信息", message, &passed);

		break;
	case PrecheckStateMachine::PUBIT_RESULT:
		sprintf(message, "第 4 副帧头部返回 0x%02x 应为 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "第 4 副帧计数检查", message, &passed);

		for (int i = 5; i < 10; i += 2) // CPU 检查
		{
			char id[6] = "CPU  ";
			id[5] = ((i - 5) / 2 + '1');
			sprintf(message, "第 4 副帧第 %d、%d 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", i, i + 1, frame[offset + i] & 0b10111101, frame[offset + i + 1] & 0b11111111);
			genReport(frame[offset + i] & 0b10111101 || frame[offset + i + 1] & 0b11111111, state, id, message, &passed);
		}

		sprintf(message, "第 4 副帧第 11、12 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 11] & 0b00000111, frame[offset + 12] & 0b00111111);
		genReport(frame[offset + 11] & 0b00000111 || frame[offset + 12] & 0b00111111, state, "CPUx-MIO-MRAM 测试", message, &passed);

		for (int i = 13; i < 16; i+=2) // MIO 检查
		{
			char id[6] = "MIO  ";
			id[5] = ((i - 13) / 2 + '1');
			sprintf(message, "第 4 副帧第 %d、%d 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", i, i + 1, frame[offset + i] & 0b00111111, frame[offset + i + 1] & 0b11111111);
			genReport(frame[offset + i] & 0b00111111 || frame[offset + i + 1] & 0b11111111, state, id, message, &passed);
		}

		sprintf(message, "第 4 副帧第 17、18 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", frame[offset + 17] & 0b00111111, frame[offset + 18] & 0b10011111);
		genReport(frame[offset + 17] & 0b00111111 || frame[offset + 18] & 0b10011111, state, "当前 CPU", message, &passed);

		break;
	case PrecheckStateMachine::CHANNEL_LOGIC:
		sprintf(message, "第 4 副帧头部返回 0x%02x 应为 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "第 4 副帧计数检查", message, &passed);

		for (int i = 5; i < 10; i += 2) // CPU 检查
		{
			char id[20] = "CPU   CFL 结果";
			id[5] = ((i - 5) / 2 + 'A');
			sprintf(message, "第 4 副帧第 %d、%d 字节输入返回 0x%02x 0x%02x 应为 0x00 0x00", i, i + 1, frame[offset + i] & 0b00001111, frame[offset + i + 1] & 0b11111111);
			genReport(frame[offset + i] & 0b00001111 || frame[offset + i + 1] & 0b11111111, state, id, message, &passed);
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