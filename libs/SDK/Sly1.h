#pragma once
#include "engine.h"

/// RESOURCES & CREDITS: Sly Cooper Modding Server
/// <summary>
/// - https://github.com/zzamizz/weed-sheet
/// - https://docs.google.com/spreadsheets/d/1ISxw587iICRDdaLJfLaTvJUaYkjGBReH4NY-yKN-Ip0/edit#gid=0
/// - https://discord.com/invite/2GSXcEzPJA
/// </summary>

namespace Sly1 {

	class Offsets : public PS2
	{
	public:

		//	
	public:
		std::string _data;
		
		//	Pointers
		int o_GS = 0x2623C0;
		int o_WS = 0x2623C4;
		int o_LS = 0x2623C8;
		int o_JT = 0x262E10;
		int o_CC = 0x126A64;
		int o_EOC = 0x2623E0;

		std::vector<int> OffsetArray = {
			o_GS,		//	GameState
			o_WS,       //  WorldState
			o_LS,       //  LevelState
			o_JT,       //  SlyPointer
			o_CC,		//	CustomColors
			o_EOC,		//	EntityOutlineColor
		};

		std::vector<std::string> names = {
			"GameState",
			"WorldState",
			"LevelState",
			"SlyPointer",
			"CustomColorAddr"
			"EntityOutlineColorAddr"
		};

		// Auto Resolve List
	public:
		uintptr_t slyPointer = GetClassPtr(o_JT);
		uintptr_t gsPointer = GetClassPtr(o_GS);
		uintptr_t wsPointer = GetClassPtr(o_WS);
		uintptr_t lsPointer = GetClassPtr(o_LS);
		uintptr_t CustomColors = GetAddr(o_CC);
		uintptr_t EntityOutlineColors = GetAddr(o_EOC);


		//	Functions
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		//	OUTPUT
		// 0x00000000	0x00000000	:	<OffsetName>		// display like native PS2 Memory
		//NOTE: Ends with 2New Line
		std::string LogData()
		{
			char data[0x1024];
			const char* data2 = "%llX	0x%08X	:	%s\n";
			_data;
			for (int i = 0; i < OffsetArray.size(); i++) {
				sprintf_s(data, data2, GetAddr(OffsetArray[i]), PS2Read<int>(GetAddr(OffsetArray[i])), names[i].c_str());
				_data += data;
			}
			return (_data += "\n");
		}
	};

	class JT : public PS2
	{
		//	ENUMS
	public:
		enum JTStates : int {
			JT_Stand = 0,
			JT_Run = 1,
			JT_Jump = 2,
			JT_Hang = 3,
			JT_Zap = 4,
			JT_SideStep = 5,
			JT_Hide = 6,
			JT_Pipe = 7,
			JT_Edge = 8,
			JT_Celebrate = 9,
			JT_Rush = 10,
			JT_Puppet = 11,
			JT_Peek = 12,
			JT_Ski = 13,
			JT_Ball = 14,
		};

		enum JTBodyStates : int {
			Jump_Init = 0,
			Jump_Rise = 1,
			Jump_Fall = 2,
			Jump_Boost = 3,
			Jump_In = 4,
			Jump_Out = 5,
			Jump_Thrown = 6,
			Jump_Smash = 7,
			Jump_Dive = 8,
			Jump_Target = 9,
			Jump_Spire = 10,
			Jump_Rail = 11,
			Jump_Hshape = 12,
			Jump_Hpnt = 13,
			Hide_Stand = 14,
			Hide_Sidestep = 15,
			Hide_PeekLeft = 16,
			Hide_PeekRight = 17,
			Hide_Run = 18,
			Hide_Spin = 19,
			Pipe_Init = 20,
			Pipe_Stay = 21,
			Pipe_Up = 22,
			Pipe_Down = 23,
			Pipe_Spin = 24,
			Celebrate_Key = 25,
			Celebrate_Timed = 26,
			Celebrate_UseKey = 27,
			Rush_Attack = 28,
			Rush_Bounce = 29,
			Peek_Enter = 30,
			Peek_Peek = 31,
			Peek_Exit = 32,
			Zap_Blunt = 33,
			Zap_Electric = 34,
			Zap_Fire = 35,
			Zap_Water = 36,
			Zap_Crush = 37,
			Zap_Pit = 38,
			Zap_Thrown = 39,
			Zap_Dead = 40,
			Zap_DeadFront = 41,
			Zap_DeadInWater = 42,
		};

		enum JTCaneStates : int {
			Reach = 0,
			Hang = 1,
			Pipe = 2,
			SweepInit = 3,
			SweepFore = 4,
			SweepBack = 5,
			StandingSweepFore = 6,
			StandingSweepBack = 7,
			Max = 8,
		};

		//	NATIVE OFFSETS
	public:
		//int objectBase;			//0x0000
		//char pad_0004[16];		//0x0004
		//__int64 SWPointer;		//0x0014
		//char pad_001C[228];		//0x001C
		char pad_0000[256];		//0x0000
		Vector3 Position;		//0x0100
		char pad_010C[68];		//0x010C
		Vector3 Velocity;		//0x0150
		char pad_015C[508];		//0x015C
		float Gravity;			//0x0358
		char pad_035C[732];		//0x035C
		float FacingAngle;		//0x0638
		char pad_063C[108];		//0x063C
		float JumpHeight;		//0x06A8
		char pad_06AC[7028];	//0x06AC
		int JTState;			//0x2220
		int JTBodyState;		//0x2224
		int JTCaneState;		//0x2228
		char pad_222C[60];		//0x222C
		int MomentumHalting;	//0x2268
		char pad_226C[556];		//0x226C
		int JumpAddress2;		//0x2498
		char pad_249C[367884];	//0x249C
		float CaneHandleOutline;	//0x5C1A8
		char pad_5C1AC[3420];	//0x5C1AC
		float CaneHookHandle;		//0x5CF08
		char pad_5CF0C[192076];	//0x5CF0C
		float LeftHandOutlineA;	//0x8BD58
		char pad_8BD5C[230044];	//0x8BD5C
		float HeadOutline;		//0xC3FF8
		char pad_C3FFC[23868];	//0xC3FFC
		float EarsOutline;		//0xC9D38
		char pad_C9D3C[23212];	//0xC9D3C
		float HatOutline;			//0xCF7E8
		char pad_CF7EC[38844];	//0xCF7EC
		float BackpackOutline;	//0xD8FA8
		//Size: 0xD8FAC

		//	FUNCTIONS
	public:

		/// <summary>
		/// Returns Class Pointer Status
		/// </summary>
		/// <returns>BOOL</returns>
		bool IsValid()
		{
			return ((unsigned int)this->pad_0000 == 0x000000) ? FALSE : TRUE;
		}


		void ChangeOutlines(float value)
		{
			Offsets offsets;
			auto address = offsets.CustomColors;
			if (g_Engine->PS2Read<int>(address) != NULL)
				g_Engine->PS2Write<int>(address, NULL);
				
			//	Change all Slys outline colors
			this->CaneHandleOutline		= value;
			this->CaneHookHandle		= value;	
			this->LeftHandOutlineA		= value;
			this->HeadOutline			= value;
			this->HatOutline			= value;
			this->BackpackOutline		= value;

			g_Engine->PS2Write<int>(address, 0xAC910268);
		}
	};
}