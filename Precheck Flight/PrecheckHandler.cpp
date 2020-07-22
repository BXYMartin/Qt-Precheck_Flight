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
	//emit(response->sendDetailsToWindow(PrecheckStateMachine::GND_INIT, PrecheckStateMachine::FAILED, "����", "hh"));
	//return true;

	char message[128];
	// ��鸱֡ͷ��
	for (int i = 0; i < 4; i++)
	{
		sprintf(message, "�� %d ��֡ͷ������ 0x%02x 0x%02x ӦΪ 0xEB 0x90", i + 1, frame[i * 64], frame[i * 64 + 1]);
		genReport(frame[i * 64] != 0xEB || frame[i * 64 + 1] != 0x90, state, "��֡ͷ���", message, &passed);
	}
		
	int offset = 64 * 3 - 1; // ��Ӧ��׼�еĴ� 1 ����
	switch (state)
	{
	case PrecheckStateMachine::GND_INIT:
		// ��Ϊδ֪���չ�
		break;
	case PrecheckStateMachine::PUBIT_CONNECT:
		sprintf(message, "�� 4 ��֡ͷ������ 0x%02x ӦΪ 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "�� 4 ��֡�������", message, &passed);
		
		sprintf(message, "�� 4 ��֡�� 5 �ֽ����뷵�� 0x%02x ӦΪ 0x00", frame[offset + 5] & 0b10000001);
		genReport(frame[offset + 5] & 0b10000001, state, "MIO �� 2 ģ��", message, &passed);

		sprintf(message, "�� 4 ��֡�� 6 �ֽ����뷵�� 0x%02x ӦΪ 0x00", frame[offset + 6] & 0b10000001);
		genReport(frame[offset + 6] & 0b10000001, state, "MIO �� 1 ģ��", message, &passed);

		sprintf(message, "�� 4 ��֡�� 7��8 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 7] & 0b10000000, frame[offset + 7 + 1] & 0b00000001);
		genReport(frame[offset + 7] & 0b10000000 || frame[offset + 7 + 1] & 0b00000001, state, "MIO �� 2 ��ɢ����", message, &passed);

		sprintf(message, "�� 4 ��֡�� 9��10 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 9] & 0b10000000, frame[offset + 9 + 1] & 0b00000001);
		genReport(frame[offset + 9] & 0b10000000 || frame[offset + 9 + 1] & 0b00000001, state, "MIO �� 1 ��ɢ����", message, &passed);

		sprintf(message, "�� 4 ��֡�� 11��12 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 11] & 0b10000000, frame[offset + 11 + 1] & 0b00000001);
		genReport(frame[offset + 11] & 0b10000000 || frame[offset + 11 + 1] & 0b00000001, state, "MIO �� 1 422/485 ���� 1~16", message, &passed);

		sprintf(message, "�� 4 ��֡�� 13 �ֽ����뷵�� 0x%02x ӦΪ 0x00", frame[offset + 13] & 0b01000001);
		genReport(frame[offset + 13] & 0b01000001, state, "MIO �� 1 422/485 ���� 17~24", message, &passed);

		sprintf(message, "�� 4 ��֡�� 14 �ֽ����뷵�� 0x%02x ӦΪ 0x00", frame[offset + 14] & 0b10000001);
		genReport(frame[offset + 14] & 0b10000001, state, "MIO �� 2 422/485 ���� 1~8", message, &passed);

		sprintf(message, "�� 4 ��֡�� 15��16 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 15] & 0b10000000, frame[offset + 15 + 1] & 0b00000001);
		genReport(frame[offset + 15] & 0b10000000 || frame[offset + 15 + 1] & 0b00000001, state, "MIO �� 1 422/485 ���� 9~24", message, &passed);

		sprintf(message, "�� 4 ��֡���� %02x%02x-%02x-%02x", frame[offset + 21], frame[offset + 22], frame[offset + 19], frame[offset + 20]);
		genReport(true, state, "�ɿ�������Ϣ", message, &passed);

		sprintf(message, "�� 4 ��֡���� %c%c%c%c%c%c%c%c%c%c%c%c", frame[offset + 23], frame[offset + 24], frame[offset + 25], frame[offset + 26], frame[offset + 27], frame[offset + 28], frame[offset + 29], frame[offset + 30], frame[offset + 60], frame[offset + 61], frame[offset + 62], frame[offset + 63]);
		genReport(true, state, "�ɿذ汾��Ϣ", message, &passed);

		break;
	case PrecheckStateMachine::PUBIT_RESULT:
		sprintf(message, "�� 4 ��֡ͷ������ 0x%02x ӦΪ 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "�� 4 ��֡�������", message, &passed);

		for (int i = 5; i < 10; i += 2) // CPU ���
		{
			char id[6] = "CPU  ";
			id[5] = ((i - 5) / 2 + '1');
			sprintf(message, "�� 4 ��֡�� %d��%d �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", i, i + 1, frame[offset + i] & 0b10111101, frame[offset + i + 1] & 0b11111111);
			genReport(frame[offset + i] & 0b10111101 || frame[offset + i + 1] & 0b11111111, state, id, message, &passed);
		}

		sprintf(message, "�� 4 ��֡�� 11��12 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 11] & 0b00000111, frame[offset + 12] & 0b00111111);
		genReport(frame[offset + 11] & 0b00000111 || frame[offset + 12] & 0b00111111, state, "CPUx-MIO-MRAM ����", message, &passed);

		for (int i = 13; i < 16; i+=2) // MIO ���
		{
			char id[6] = "MIO  ";
			id[5] = ((i - 13) / 2 + '1');
			sprintf(message, "�� 4 ��֡�� %d��%d �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", i, i + 1, frame[offset + i] & 0b00111111, frame[offset + i + 1] & 0b11111111);
			genReport(frame[offset + i] & 0b00111111 || frame[offset + i + 1] & 0b11111111, state, id, message, &passed);
		}

		sprintf(message, "�� 4 ��֡�� 17��18 �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", frame[offset + 17] & 0b00111111, frame[offset + 18] & 0b10011111);
		genReport(frame[offset + 17] & 0b00111111 || frame[offset + 18] & 0b10011111, state, "��ǰ CPU", message, &passed);

		break;
	case PrecheckStateMachine::CHANNEL_LOGIC:
		sprintf(message, "�� 4 ��֡ͷ������ 0x%02x ӦΪ 0x78", frame[offset + 3]);
		genReport(frame[offset + 3] != 0x78, state, "�� 4 ��֡�������", message, &passed);

		for (int i = 5; i < 10; i += 2) // CPU ���
		{
			char id[20] = "CPU   CFL ���";
			id[5] = ((i - 5) / 2 + 'A');
			sprintf(message, "�� 4 ��֡�� %d��%d �ֽ����뷵�� 0x%02x 0x%02x ӦΪ 0x00 0x00", i, i + 1, frame[offset + i] & 0b00001111, frame[offset + i + 1] & 0b11111111);
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
	frame[0x02] = 0xFF; // �ؼ�
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