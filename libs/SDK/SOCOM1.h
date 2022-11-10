#pragma once
#include "engine.h"

namespace SOCOM1 {

	class Offsets : public PS2
	{
	public:
		std::vector<int> OffsetArray = {
			0x5D708C, // gameEndAddr
			0x1F66F4, // forceMatch
			0x48D548, // PlayerPointer
			0x4D46A4, // entArray
			0x1E5AC0, // fog
			0x48CF60, // fps1
			0x48CF64  // fps2
		};
		std::vector<std::string> names = {
			"GameEndedAddress",
			"ForceStartMatch",
			"SEALPointer",
			"EntityArrayPointer",
			"FOG",
			"Framerate",
			"Framerate"
		};

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

		// Auto Resolve List
	public:
		uintptr_t SEALPointer = GetClassPtr(PlayerPointer);
		uintptr_t EntityArray = GetAddr(entArray);
		uintptr_t GameEndAddress = GetAddr(gameEndAddr);
		uintptr_t FrameRate1 = GetAddr(fps1);
		uintptr_t FrameRate2 = GetAddr(fps2);

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
			std::string result;
			for (int i = 0; i < OffsetArray.size(); i++) {
				sprintf_s(data, data2, GetAddr(OffsetArray[i]), PS2Read<int>(GetAddr(OffsetArray[i])), names[i].c_str());
				result += data;
			}
			return (result += "\n");
		}
	};

	class CCamera : public PS2 
	{
	
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

		enum Teams : unsigned int
		{
			SEALS		= 0x40000001,		//	Seal
			TERRORIST	= 0x80000100,		//	Terrorist
			TURRET		= 0x48000000,		//	Turret
			SPECTATOR	= 0x00010000,		//	Spectator

			// CAMPAIGN
			SP_ABLE		= 0x84000006,		//	Alpha Team
			SP_BRAVO	= 0x8400000A,		//	Bravo Team
			SP_ENEMY_A	= 0x40000050,		//	Iron Brother / Iron Leader
			SP_ENEMY_B	= 0x40000100,		//	
			SP_ENEMY_C	= 0x40000210,		//	
			SP_ENEMY_D	= 0x40000410,		//	
			SP_ENEMY_E	= 0x40000810,		//	
			SP_ENEMY_F	= 0x40001010,		//	
			SP_ENEMY_G	= 0x40002010,		//	
			SP_ENEMY_H	= 0x40004010,		//	
			SP_ENEMY_I	= 0x40021010,		//	

		};

		class CWeapon
		{
		public:
			enum Weapon : unsigned int
			{
				// Primaries
				AR_552		= 0xCC4550,
				SMG_9MM		= 0x00CC61F0,

				// Secondaries
				PISTOL_9MM	= 0xCC2B60,
			};
			
			enum WeaponSlot : unsigned int
			{
				Primary,	// = 0x60C,
				Secondary,	// = 0x610,
				EqSlot1,	// = 0x614,
				EqSlot2,	// = 0x618,
				EqSlot3,	// = 0x61C,
			};

		};

		//	OFFSETS
	public:
		char pad_0000[20];	//0x0000
		int NamePTR;	//0x0014
		char pad_0018[4];	//0x0018
		Vector3 Position;	//0x001C
		CPlayerPhysics* CPlayerMovement;	//0x0028
		char pad_0030[148];	//0x0030
		int TeamID;	//0x00C4
		char pad_00C8[1348];	//0x00C8
		unsigned int PrimaryWeapon;	//0x060C
		unsigned int SecondaryWeapon;	//0x0610
		unsigned int EqSlot1;	//0x0614
		unsigned int EqSlot2;	//0x0618
		unsigned int EqSlot3;	//0x061C
		char pad_0620[220];	//0x0620
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

		/// <summary>
		/// Returns Class Pointer Status
		/// </summary>
		/// <returns>BOOL</returns>
		bool IsValid() 
		{
			return ((unsigned int)this->pad_0000 == 0x000000 || this->NamePTR == NULL || this->CPlayerMovement == nullptr || this->TeamID == NULL) ? FALSE : TRUE;
		}

		/// <summary>
		/// Returns Players Alive State
		/// </summary>
		/// <returns>BOOL</returns>
		bool IsAlive()
		{
			return (this->Health > 0.0f) ? TRUE : FALSE;
		}

		/// <summary>
		/// Returns a Pointer to CPlayerPhysics Class
		/// </summary>
		/// <returns>CPlayerPhysics*</returns>
		CPlayerPhysics* PlayerPhysicsPtr()
		{
			return (CPlayerPhysics*)((unsigned int)this->CPlayerMovement + BasePS2MemorySpace);
		}

		/// <summary>
		/// Returns Player Name
		/// </summary>
		/// <returns>std::string</returns>
		std::string GetPlayerName() 
		{
			return (char*)(NamePTR + BasePS2MemorySpace);
		}

		/// <summary>
		/// Returns Player Team Name
		/// </summary>
		/// <returns>std::string</returns>
		std::string GetTeamName() 
		{
			switch (this->TeamID)
			{
				case (SEALS):		return "SEAL";
				case (TERRORIST):	return "TERRORIST";
				case (SPECTATOR):	return "SPECTATOR";
				case (SP_ABLE):		return	"SEALS - ABLE Team";
				case (SP_BRAVO):	return	"SEALS - BRAVO Team";
				case (SP_ENEMY_A):	return	"Hostile";
				case (SP_ENEMY_B):	return	"Hostile";
				case (SP_ENEMY_C):	return	"Hostile";
				case (SP_ENEMY_D):	return	"Hostile";
				case (SP_ENEMY_E):	return	"Hostile";
				case (SP_ENEMY_F):	return	"Hostile";
				case (SP_ENEMY_G):	return	"Hostile";
				case (SP_ENEMY_H):	return	"Hostile";
				case (SP_ENEMY_I):	return	"Hostile";
			}
			return std::to_string(this->TeamID);
		}

		/// <summary>
		/// Returns Weapon Name
		/// </summary>
		/// <param name="Weapon"></param>
		/// <returns>std::string</returns>
		std::string GetWeaponName(unsigned int Weapon)
		{
			switch (Weapon)
			{
				case(CWeapon::AR_552): return "552";
			}
			return std::to_string(Weapon);
		}

		/// <summary>
		/// Replaces current weapon in slot with input Weapon
		/// </summary>
		/// <param name="Slot	: ">CWeapon::WeaponSlot</param>
		/// <param name="Weapon : ">CWeapon::Weapon</param>
		void GiveWeapon(unsigned int Slot, unsigned int Weapon)
		{
			// Intended usage
			switch (Slot)
			{
				case (CWeapon::WeaponSlot::Primary):	this->PrimaryWeapon		= Weapon;	break;
				case (CWeapon::WeaponSlot::Secondary):	this->SecondaryWeapon	= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot1):	this->EqSlot1			= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot2):	this->EqSlot2			= Weapon;	break;
				case (CWeapon::WeaponSlot::EqSlot3):	this->EqSlot3			= Weapon;	break;
			}
		}

		/// <summary>
		/// generates a log containing important player data
		/// </summary>
		/// <returns>std::string</returns>
		/// NOTE: Ends with 2New Line
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
			const char* data2 = "PlayerObjectBase: %llX\nPlayerName: %s\nTeamName: %s\nPrimary Weapon: %s	|	PrimaryAmmo: %i\nSecondary Weapon: %s	|	SecondaryAmmo: %i\nHealth: %0.f\nPosition: { %f, %f, %f }\nDistance: { %f }\n\n";
			sprintf_s(data, data2, this, this->GetPlayerName().c_str(), this->GetTeamName().c_str(),
				GetWeaponName(this->PrimaryWeapon).c_str(), this->PrimaryMag1, 
				GetWeaponName(this->SecondaryWeapon).c_str(), this->SecondaryMag1, 
				(this->Health * 100.f),
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
			return (PS2Read<int>(offset.GameEndAddress) == NULL) ? TRUE : FALSE;
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