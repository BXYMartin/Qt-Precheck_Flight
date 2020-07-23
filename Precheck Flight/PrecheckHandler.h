#pragma once
#include "PrecheckStateMachine.h"
#include "PrecheckThread.h"

class PrecheckThread;

class PrecheckHandler
{
public:

	struct CheckList {
		PrecheckStateMachine::State state;
		int position;
		uint8_t mask;
		char* function;
		char* message;
	};

	struct CheckList list[255] = { 
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b10000000, "CPU 1", "NVM �������"},
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00100000, "CPU 1", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00010000, "CPU 1", "�汾����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00001000, "CPU 1", "ͨ���Ų���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00000100, "CPU 1", "ͨ�������߼�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00000001, "CPU 1", "Ӳ��ͬ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b10000000, "CPU 1", "659 ����״̬" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b01000000, "CPU 1", "��ʱ���ж�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00100000, "CPU 1", "659 �жϼ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00010000, "CPU 1", "���Ź����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00001000, "CPU 1", "NOR-FLASH ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000100, "CPU 1", "NVM ��д����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000010, "CPU 1", "RAM ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000001, "CPU 1", "CPU ���" },

	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b10000000, "CPU 2", "NVM �������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00100000, "CPU 2", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00010000, "CPU 2", "�汾����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00001000, "CPU 2", "ͨ���Ų���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00000100, "CPU 2", "ͨ�������߼�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00000001, "CPU 2", "Ӳ��ͬ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b10000000, "CPU 2", "659 ����״̬" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b01000000, "CPU 2", "��ʱ���ж�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00100000, "CPU 2", "659 �жϼ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00010000, "CPU 2", "���Ź����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00001000, "CPU 2", "NOR-FLASH ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000100, "CPU 2", "NVM ��д����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000010, "CPU 2", "RAM ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000001, "CPU 2", "CPU ���" },

	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b10000000, "CPU 3", "NVM �������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00100000, "CPU 3", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00010000, "CPU 3", "�汾����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00001000, "CPU 3", "ͨ���Ų���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00000100, "CPU 3", "ͨ�������߼�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00000001, "CPU 3", "Ӳ��ͬ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b10000000, "CPU 3", "659 ����״̬" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b01000000, "CPU 3", "��ʱ���ж�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00100000, "CPU 3", "659 �жϼ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00010000, "CPU 3", "���Ź����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00001000, "CPU 3", "NOR-FLASH ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000100, "CPU 3", "NVM ��д����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000010, "CPU 3", "RAM ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000001, "CPU 3", "CPU ���" },

	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000100, "MRAM", "CPU3-MRAM ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000010, "MRAM", "CPU2-MRAM ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000001, "MRAM", "CPU1-MRAM ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00100000, "CPU 3", "CPU3-MIO2 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00010000, "CPU 3", "CPU3-MIO1 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00001000, "CPU 2", "CPU2-MIO2 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000100, "CPU 2", "CPU2-MIO1 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000010, "CPU 1", "CPU1-MIO2 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000001, "CPU 1", "CPU1-MIO1 ����" },

	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00100000, "MIO 1", "GJB289A ���߲���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00010000, "MIO 1", "��ɢ�������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00001000, "MIO 1", "��ɢ�������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000100, "MIO 1", "ģ���������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000010, "MIO 1", "ģ���������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000001, "MIO 1", "RS422/RS485 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b10000000, "MIO 1", "659 ����״̬" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b01000000, "MIO 1", "��ʱ���ж�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00100000, "MIO 1", "659 �жϼ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00010000, "MIO 1", "���Ź����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00001000, "MIO 1", "FPGA �г� DSP ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000100, "MIO 1", "FLASH ��д����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000010, "MIO 1", "RAM ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000001, "MIO 1", "CPU ���" },

	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00100000, "MIO 2", "GJB289A ���߲���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00010000, "MIO 2", "��ɢ�������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00001000, "MIO 2", "��ɢ�������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000100, "MIO 2", "ģ���������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000010, "MIO 2", "ģ���������" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000001, "MIO 2", "RS422/RS485 ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b10000000, "MIO 2", "659 ����״̬" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b01000000, "MIO 2", "��ʱ���ж�" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00100000, "MIO 2", "659 �жϼ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00010000, "MIO 2", "���Ź����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00001000, "MIO 2", "FPGA �г� DSP ����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000100, "MIO 2", "FLASH ��д����" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000010, "MIO 2", "RAM ���" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000001, "MIO 2", "CPU ���" },

	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00100000, "��ǰ CPU", "-15V2 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00010000, "��ǰ CPU", "-15V1 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00001000, "��ǰ CPU", "+15V2 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000100, "��ǰ CPU", "+15V1 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000010, "��ǰ CPU", "5V2 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000001, "��ǰ CPU", "5V1 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b10000000, "��ǰ CPU", "MIO ���Դ��ز�һ��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00010000, "��ǰ CPU", "�����ż��" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00001000, "��ǰ CPU", "28V4 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000100, "��ǰ CPU", "28V3 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000010, "��ǰ CPU", "28V2 ��Դ" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000001, "��ǰ CPU", "28V1 ��Դ" },

	//{ PrecheckStateMachine::PUBIT_RESULT, 23, 0b11111110, "����һ�±�־", "���� CPU ��汾" },
	//{ PrecheckStateMachine::PUBIT_RESULT, 24, 0b11111110, "����һ�±�־", "���� CPU ��汾" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 5, 0b10000000, "MIO �� 2 ģ������", "�˿� 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 5, 0b00000001, "MIO �� 2 ģ������", "�˿� 1" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 6, 0b10000000, "MIO �� 1 ģ������", "�˿� 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 6, 0b00000001, "MIO �� 1 ģ������", "�˿� 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 7, 0b10000000, "MIO �� 2 ��ɢ����", "�˿� 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 8, 0b00000001, "MIO �� 2 ��ɢ����", "�˿� 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 9, 0b10000000, "MIO �� 1 ��ɢ����", "�˿� 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 10, 0b00000001, "MIO �� 1 ��ɢ����", "�˿� 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 11, 0b10000000, "MIO �� 1 422/485 ���� 1~16", "�˿� 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 12, 0b00000001, "MIO �� 1 422/485 ���� 1~16", "�˿� 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 13, 0b01000000, "MIO �� 1 422/485 ���� 17~24", "�˿� 24" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 13, 0b00000001, "MIO �� 1 422/485 ���� 17~24", "�˿� 17" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 14, 0b10000000, "MIO �� 2 422/485 ���� 1~8", "�˿� 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 14, 0b00000001, "MIO �� 2 422/485 ���� 1~8", "�˿� 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 15, 0b10000000, "MIO �� 2 422/485 ���� 9~24", "�˿� 24" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 16, 0b00000001, "MIO �� 2 422/485 ���� 9~24", "�˿� 9" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 5, 0b00001111, "CPUA CFL ���", "D0-D11 12��ͨ��" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 6, 0b11111111, "CPUA CFL ���", "D0-D11 12��ͨ��" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 7, 0b00001111, "CPUB CFL ���", "D0-D11 12��ͨ��" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 8, 0b11111111, "CPUB CFL ���", "D0-D11 12��ͨ��" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 9, 0b00001111, "CPUC CFL ���", "D0-D11 12��ͨ��" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 10, 0b11111111, "CPUC CFL ���", "D0-D11 12��ͨ��" },
	};
	PrecheckHandler(PrecheckThread* callback);

	void generateFrame(PrecheckStateMachine::State, uint8_t* frames);
	bool checkFrame(PrecheckStateMachine::State, uint8_t* frames);

private:
	void genReport(uint8_t item, uint8_t mask, PrecheckStateMachine::State state, char* function, char* message, bool* passed);
	void fillInstruction(PrecheckStateMachine::State, uint8_t* frames);
	void fillHeader(uint8_t* frames);
	void fillType(uint8_t* frames);
	PrecheckThread* response;
};