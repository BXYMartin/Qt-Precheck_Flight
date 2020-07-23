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
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b10000000, "CPU 1", "NVM 记忆测试"},
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00100000, "CPU 1", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00010000, "CPU 1", "版本测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00001000, "CPU 1", "通道号测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00000100, "CPU 1", "通道故障逻辑" },
	{ PrecheckStateMachine::PUBIT_RESULT, 5, 0b00000001, "CPU 1", "硬线同步" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b10000000, "CPU 1", "659 总线状态" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b01000000, "CPU 1", "定时器中断" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00100000, "CPU 1", "659 中断检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00010000, "CPU 1", "看门狗检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00001000, "CPU 1", "NOR-FLASH 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000100, "CPU 1", "NVM 读写测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000010, "CPU 1", "RAM 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 6, 0b00000001, "CPU 1", "CPU 检测" },

	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b10000000, "CPU 2", "NVM 记忆测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00100000, "CPU 2", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00010000, "CPU 2", "版本测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00001000, "CPU 2", "通道号测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00000100, "CPU 2", "通道故障逻辑" },
	{ PrecheckStateMachine::PUBIT_RESULT, 7, 0b00000001, "CPU 2", "硬线同步" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b10000000, "CPU 2", "659 总线状态" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b01000000, "CPU 2", "定时器中断" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00100000, "CPU 2", "659 中断检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00010000, "CPU 2", "看门狗检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00001000, "CPU 2", "NOR-FLASH 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000100, "CPU 2", "NVM 读写测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000010, "CPU 2", "RAM 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 8, 0b00000001, "CPU 2", "CPU 检测" },

	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b10000000, "CPU 3", "NVM 记忆测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00100000, "CPU 3", "659 BUF" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00010000, "CPU 3", "版本测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00001000, "CPU 3", "通道号测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00000100, "CPU 3", "通道故障逻辑" },
	{ PrecheckStateMachine::PUBIT_RESULT, 9, 0b00000001, "CPU 3", "硬线同步" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b10000000, "CPU 3", "659 总线状态" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b01000000, "CPU 3", "定时器中断" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00100000, "CPU 3", "659 中断检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00010000, "CPU 3", "看门狗检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00001000, "CPU 3", "NOR-FLASH 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000100, "CPU 3", "NVM 读写测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000010, "CPU 3", "RAM 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 10, 0b00000001, "CPU 3", "CPU 检测" },

	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000100, "MRAM", "CPU3-MRAM 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000010, "MRAM", "CPU2-MRAM 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 11, 0b00000001, "MRAM", "CPU1-MRAM 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00100000, "CPU 3", "CPU3-MIO2 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00010000, "CPU 3", "CPU3-MIO1 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00001000, "CPU 2", "CPU2-MIO2 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000100, "CPU 2", "CPU2-MIO1 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000010, "CPU 1", "CPU1-MIO2 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 12, 0b00000001, "CPU 1", "CPU1-MIO1 测试" },

	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00100000, "MIO 1", "GJB289A 总线测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00010000, "MIO 1", "离散输出回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00001000, "MIO 1", "离散输入回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000100, "MIO 1", "模拟输出回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000010, "MIO 1", "模拟输入回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 13, 0b00000001, "MIO 1", "RS422/RS485 回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b10000000, "MIO 1", "659 总线状态" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b01000000, "MIO 1", "定时器中断" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00100000, "MIO 1", "659 中断检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00010000, "MIO 1", "看门狗检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00001000, "MIO 1", "FPGA 切除 DSP 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000100, "MIO 1", "FLASH 读写测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000010, "MIO 1", "RAM 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 14, 0b00000001, "MIO 1", "CPU 检测" },

	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00100000, "MIO 2", "GJB289A 总线测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00010000, "MIO 2", "离散输出回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00001000, "MIO 2", "离散输入回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000100, "MIO 2", "模拟输出回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000010, "MIO 2", "模拟输入回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 15, 0b00000001, "MIO 2", "RS422/RS485 回绕" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b10000000, "MIO 2", "659 总线状态" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b01000000, "MIO 2", "定时器中断" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00100000, "MIO 2", "659 中断检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00010000, "MIO 2", "看门狗检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00001000, "MIO 2", "FPGA 切除 DSP 测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000100, "MIO 2", "FLASH 读写测试" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000010, "MIO 2", "RAM 检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 16, 0b00000001, "MIO 2", "CPU 检测" },

	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00100000, "当前 CPU", "-15V2 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00010000, "当前 CPU", "-15V1 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00001000, "当前 CPU", "+15V2 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000100, "当前 CPU", "+15V1 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000010, "当前 CPU", "5V2 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 17, 0b00000001, "当前 CPU", "5V1 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b10000000, "当前 CPU", "MIO 板电源监控不一致" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00010000, "当前 CPU", "启动号检测" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00001000, "当前 CPU", "28V4 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000100, "当前 CPU", "28V3 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000010, "当前 CPU", "28V2 电源" },
	{ PrecheckStateMachine::PUBIT_RESULT, 18, 0b00000001, "当前 CPU", "28V1 电源" },

	//{ PrecheckStateMachine::PUBIT_RESULT, 23, 0b11111110, "三机一致标志", "三块 CPU 板版本" },
	//{ PrecheckStateMachine::PUBIT_RESULT, 24, 0b11111110, "三机一致标志", "三块 CPU 板版本" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 5, 0b10000000, "MIO 板 2 模拟输入", "端口 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 5, 0b00000001, "MIO 板 2 模拟输入", "端口 1" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 6, 0b10000000, "MIO 板 1 模拟输入", "端口 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 6, 0b00000001, "MIO 板 1 模拟输入", "端口 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 7, 0b10000000, "MIO 板 2 离散输入", "端口 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 8, 0b00000001, "MIO 板 2 离散输入", "端口 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 9, 0b10000000, "MIO 板 1 离散输入", "端口 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 10, 0b00000001, "MIO 板 1 离散输入", "端口 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 11, 0b10000000, "MIO 板 1 422/485 回绕 1~16", "端口 16" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 12, 0b00000001, "MIO 板 1 422/485 回绕 1~16", "端口 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 13, 0b01000000, "MIO 板 1 422/485 回绕 17~24", "端口 24" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 13, 0b00000001, "MIO 板 1 422/485 回绕 17~24", "端口 17" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 14, 0b10000000, "MIO 板 2 422/485 回绕 1~8", "端口 8" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 14, 0b00000001, "MIO 板 2 422/485 回绕 1~8", "端口 1" },

	{ PrecheckStateMachine::PUBIT_CONNECT, 15, 0b10000000, "MIO 板 2 422/485 回绕 9~24", "端口 24" },
	{ PrecheckStateMachine::PUBIT_CONNECT, 16, 0b00000001, "MIO 板 2 422/485 回绕 9~24", "端口 9" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 5, 0b00001111, "CPUA CFL 结果", "D0-D11 12个通道" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 6, 0b11111111, "CPUA CFL 结果", "D0-D11 12个通道" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 7, 0b00001111, "CPUB CFL 结果", "D0-D11 12个通道" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 8, 0b11111111, "CPUB CFL 结果", "D0-D11 12个通道" },

	{ PrecheckStateMachine::CHANNEL_LOGIC, 9, 0b00001111, "CPUC CFL 结果", "D0-D11 12个通道" },
	{ PrecheckStateMachine::CHANNEL_LOGIC, 10, 0b11111111, "CPUC CFL 结果", "D0-D11 12个通道" },
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