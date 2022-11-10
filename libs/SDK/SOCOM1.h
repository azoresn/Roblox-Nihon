#pragma once
#include "engine.h"

namespace SOCOM1 {

	class Offsets : public PS2
	{
	public:
		// Match
		int gameEndAddr = 0x5D708C;
		int forceMatch = 0x1F66F4;

		// Character
		int PlayerPointer = 0x48D548;
		int entArray = 0x4D46A4;

		// Environment
		int fog = 0x1E5AC0;
		int fps1 = 0x48CF60;
		int fps2 = 0x48CF64;

	public:
		uintptr_t SEALPointer = GetClassPtr(PlayerPointer);
		uintptr_t EntityArray = GetAddr(entArray);
		uintptr_t GameEndAddress = GetAddr(gameEndAddr);
		uintptr_t FrameRate1 = GetAddr(fps1);
		uintptr_t FrameRate2 = GetAddr(fps2);
	};

	class CCamera {
	
		//	OFFSETS
	public:
		char pad_0000[80];	//0x0000
		Vector3 Position;	//0x0050
		char pad_005C[132];	//0x005C

		//	FUNCTIONS
	public:	
		std::string LogData()
		{

		}
	};

	class CPlayer : public PS2
	{
		// SUB CLASSES
	public:
		class CPlayerPhysics
		{
		public:
			char pad_0000[48];	//0x0000
			Vector3 absPosition;	//0x0030
			char pad_003C[348];	//0x003C

			//	FUNCTIONS
		public:	// FUNCTIONS
			std::string LogData()
			{

			}

		};	//Size: 0x0198

		//	OFFSETS
	public:
		char pad_0000[20];	//0x0000
		int32_t NamePTR;	//0x0014
		char pad_0018[4];	//0x0018
		Vector3 Position;	//0x001C
		CPlayerPhysics* PlayerMovement;	//0x0028
		char pad_0030[148];	//0x0030
		int TeamID;	//0x00C4
		char pad_00C8[1588];	//0x00C8
		int PrimaryMag1;	//0x06FC
		int PrimaryMag2;	//0x0700
		int PrimaryMag3;	//0x0704
		int PrimaryMag4;	//0x0708
		int PrimaryMag5;	//0x070C
		int PrimaryMag6;	//0x0710
		int PrimaryMag7;	//0x0714
		int PrimaryMag8;	//0x0718
		int PrimaryMag9;	//0x071C
		int PrimaryMag10;	//0x0720
		int SecondaryMag1;	//0x0724
		int SecondaryMag2;	//0x0728
		int SecondaryMag3;	//0x072C
		int SecondaryMag4;	//0x0730
		int SecondaryMag5;	//0x0734
		int SecondaryMag6;	//0x0738
		int SecondaryMag7;	//0x073C
		int SecondaryMag8;	//0x0740
		int SecondaryMag9;	//0x0744
		int SecondaryMag10;	//0x0748
		int EquipmentSlot1;	//0x074C
		char pad_0750[36];	//0x0750
		int EquipmentSlot2;	//0x0774
		char pad_0778[36];	//0x0778
		int EquipmentSlot3;	//0x079C
		char pad_07A0[1840];	//0x07A0
		float Health;	//0x0ED0

		//	FUNCTIONS
	public:

		bool IsValid() 
		{
			return (this->NamePTR == NULL || this->PlayerMovement == nullptr || this->TeamID == NULL) ? FALSE : TRUE;
		}

		bool IsAlive()
		{
			return (this->Health > 0.0f) ? TRUE : FALSE;
		}

		CPlayerPhysics* PlayerPhysicsPtr()
		{
			return (CPlayerPhysics*)((unsigned int)this->PlayerMovement + BasePS2MemorySpace);
		}

		std::string GetName() 
		{
			return (char*)(NamePTR + BasePS2MemorySpace);
		}

		std::string GetTeam() 
		{
			
			//
			/*
			
				1073741904	40000050	Iron Brother / Iron Leader
				1073742080	40000100	
				1073742352	40000210
				1073742864	40000410	
				1073743888	40000810	
				1073745936	40001010
				1073750032	40002010
				1073758224	40004010
				1073877008	40021010
				2214592518	84000006	Alpha Team
				2214592522	8400000A	Bravo Team
				1073741825	40000001	Seal
				2147483904	80000100	Terrorist
				1207959552	48000000	Turret
				65536		00010000	Spectator
			
			*/

			// For now
			const unsigned int SEALS = 1073741825; // 0x84000006
			const unsigned int TERRORIST = 2147483904;
			const unsigned int SPECTATOR = 65536;
			const unsigned int TURRET = 1207959552;
			const unsigned int CAMPAIGN = 2214592516;
			const unsigned int CAMPAIGN2 = 2214592518;

			switch (this->TeamID)
			{
				case (SEALS): return "SEAL";
				case (TERRORIST): return "TERRORIST";
				case (SPECTATOR): return "SPECTATOR";
				case (CAMPAIGN): return ("SEALS - CAMPAIGN");
				case (CAMPAIGN2): return ("SEALS - CAMPAIGN");
			}
			return std::to_string(this->TeamID);
		}

		std::string LogData()
		{
			Offsets offsets;
			auto SEAL = (CPlayer*)offsets.SEALPointer;
			float distance;
			if (SEAL != this)
				distance = GetDistanceTo3DObject(SEAL->Position, this->Position);
			else
				distance = 0.0f;

			char data[0x256];
			const char* data2 = "PlayerObjectBase: %llX\nPlayerName: %s\nTeamName: %s\nPrimaryAmmo: %i\nSecondaryAmmo: %i\nHealth: %0.f\nPosition: { %f, %f, %f }\nDistance: { %f }\n\n";
			sprintf_s(data, data2, this, this->GetName().c_str(), this->GetTeam().c_str(),
				this->PrimaryMag1, this->SecondaryMag1, (this->Health * 100.f),
				this->Position.x, this->Position.y, this->Position.z, distance);
			return data;
		}

	};	//Size: 0x0ED4

	class MatchData : public PS2
	{
		// NOTES
		// Host
		// - Force Start
		// - 
		// Match Info
		// - Map
		// - Round
		// - Time
		// - Players
		// - Score

		// SUB CLASSES
	public:

		//	OFFSETS
	public:

		//	FUNCTIONS
	public: 
		bool isMatchEnded()
		{
			Offsets offset;
			return (Read<int>(offset.GameEndAddress) == NULL) ? TRUE : FALSE;
		}

		void ForceStartMatch()
		{	
			//
		}

		std::vector<CPlayer*> GetPlayers()
		{
			int count = NULL;
			Offsets offsets;
			std::vector<CPlayer*> ents{};

			//   Grab the first entityObjectPointer in the array
			auto entArray = offsets.EntityArray;
			if (entArray == NULL) return ents;

			//   Store base address for later because the entity array loops back to the beginning
			auto baseEntity = entArray;

			size_t maxSize = 0x64;
			for (int i = 0; i <= maxSize; i++)
			{
				//	Cast entity object to CPlayer Class
				CPlayer* ent = (CPlayer*)((*(int32_t*)(entArray + 0x8)) + BasePS2MemorySpace);
				if (ent == NULL)
					break;

				if (!ent->IsValid())
				{
					// Get next entity in the array
					entArray = *(int32_t*)entArray + BasePS2MemorySpace;
					continue;
				}

				//	Push CPlayer Object into the vector array
				ents.push_back(ent);

				// Get next entity in the array
				entArray = *(int32_t*)entArray + BasePS2MemorySpace;

				if (entArray == baseEntity)
					break;
			}
			
			//	return array of players
			return ents;
		}

		std::string LogData()
		{
			// Data
			// - Player Count
			// - Map Name
			// - Current Round
			// - Match Timer
			return "";
		}
	};
}