#pragma once
#include <windows.h>

//	Establish Pointer Paths and base address
inline HMODULE g_hModule{};
inline LPCWSTR g_ModuleName{};
static uintptr_t dwGameBase = (uintptr_t)GetModuleHandle(g_ModuleName);    
static uintptr_t dwEEMem = (uintptr_t)GetProcAddress(g_hModule, "EEmem");
static uintptr_t BasePS2MemorySpace = *(uintptr_t*)dwEEMem;

class PS2 {
    
    // Core Functionality
public:

    struct Vector2 {
        float x, y;
    };

    struct Vector3 {
        float x, y, z;
    };

    struct Vector4 {
        float x, y, z, w;
    };

    struct EMU
    {

        uintptr_t hk_OnLeftDClick = NULL;
        uintptr_t hk_ResetEE = NULL;

        void __cdecl recResetEE(uintptr_t Address)
        {
            typedef void(__cdecl* pFunctionAddress)();
            pFunctionAddress pResetEE = (pFunctionAddress)((Address));
            pResetEE();
        }

    };

    PS2() 
    {
        InitializeSDK();
    }
    ~PS2() {}

    void InitializeSDK()
    {
        //	m_OnLeftDClick = Signature("48 8B 05 ? ? ? ? 80 B8 ? ? ? ? ? 74 0C").Scan().As<uint64_t>();
        //  m_ResetEE = Signature("80 3D ? ? ? ? ? 74 13 B8 ? ? ? ? 86").Scan().As<uint64_t>();	// 80 3D 09 18 E8 0C 00 74 13 B8 01 00 00 00 86 05 DF 0B E8 0C C6 05 F6 17 E8 0C 01
    }



    // Memory Operations
public:
    
    bool isNullPtr()
    {
        return (this == nullptr) ? TRUE : FALSE;
    }

    /// <summary>
    /// Converts shortened RAW PS2 format address to x64 address
    /// </summary>
    /// <param name="RAW_PS2_OFFSET"></param>
    /// <returns></returns>
    /// EXAMPLE:
    /// - Original RAW  : 2048D548  
    /// - Shortened RAW : 0x48D548
    /// - Base Memory   : 7FF660000000
    /// - Result        : 7FF660000000 + 0x48D548 = 7FF66048D548
    uintptr_t GetAddr(unsigned int RAW_PS2_OFFSET)
    {
        return (BasePS2MemorySpace + RAW_PS2_OFFSET);
    }

    /// <summary>
    /// Assigns Shortened RAW PS2 Format Code to Class Pointer
    /// Note: Must be a base address
    /// </summary>
    /// <returns>ClassPointer</returns>
    /// - CPlayer
    /// - CCamera
    uintptr_t GetClassPtr(unsigned int RAW_PS2_OFFSET)
    {
        return *(int32_t*)(RAW_PS2_OFFSET + BasePS2MemorySpace) + BasePS2MemorySpace;
    }

    /// <summary>
    /// Resolves Pointer Chain from input Shorthand RAW PS2 Format Address
    /// </summary>
    /// <param name="RAW_PS2_OFFSET"></param>
    /// <param name="offsets"></param>
    /// <returns></returns>
    uintptr_t ResolvePtrChain(unsigned int RAW_PS2_OFFSET, std::vector<unsigned int> offsets = {})
    {
        //  --
        uintptr_t addr = (*(int32_t*)GetAddr(RAW_PS2_OFFSET)) + BasePS2MemorySpace;
        if (offsets.empty())
            return addr;

        // --- untested (possibly not needed anyways, should work)
        // GetClassPtr and relevent functions within each class will make this useless
        for (int i = 0; i < offsets.size(); i++)
        {
            addr = *(int32_t*)addr;
            addr += (offsets[i] + BasePS2MemorySpace);
        }
        return addr;
    }

    // Takes Full Address
    // Make sure to resolve any offsets prior to running this function
    // NOTE: only reads last 4bytes
    template<typename T> inline T PS2Read(uintptr_t Address)
    {
        /// USING FRAMERATE AS AN EXAMPLE
        //0x7FF6B048CF60 0000001E0000001E   //  8   Bytes
        //0x7FF6B048CF60 0000001E           //  4   Bytes
        // Reformat Value from designated address
        unsigned int format = *(int32_t*)Address;
        
        T A{};
        A = (T)format;
        return A;
    }

    // Takes Full Address
    // Make sure to resolve any offsets prior to running this function
    // NOTE: only writes last 4bytes
    template<typename T> inline void PS2Write(uintptr_t Address, T Patch)
    {
        /// USING FRAMERATE AS AN EXAMPLE
        //0x7FF6B048CF60 0000001E0000001E   //  8   Bytes
        //0x7FF6B048CF60 0000001E           //  4   Bytes
        // Reformat Value from designated address
        *(int32_t*)Address = Patch;
    }

    /// <summary>
    /// Write Assembly patches to desired location
    /// </summary>
    /// <param name="Address">Destination</param>
    /// <param name="src"></param>
    /// <param name="size"></param>
    /// <returns>TRUE if operation is a success, otherwise result is FALSE</returns>
    /// Note: resolve any offsets prior to running this function.
    bool BytePatch(uintptr_t Address, BYTE* bytes, unsigned int size)
    {
        DWORD oldprotect;
        auto status = VirtualProtect(reinterpret_cast<void*>(Address), size, PAGE_EXECUTE_READWRITE, &oldprotect);
        if (!status)
            return FALSE;

        memcpy(reinterpret_cast<void*>(Address), bytes, size);
        VirtualProtect(reinterpret_cast<void*>(Address), size, oldprotect, &oldprotect);
        return TRUE;
    }

    /// <summary>
    /// Write NOP opcodes for desired size at the set destination
    /// </summary>
    /// <param name="Address">Destination</param>
    /// <param name="size">Space to wipe</param>
    /// <returns>TRUE if operation is a success, otherwise result is FALSE</returns>
    bool Nop(uintptr_t Address, unsigned int size)
    {
        DWORD oldprotect;
        auto status = VirtualProtect(reinterpret_cast<void*>(Address), size, PAGE_EXECUTE_READWRITE, &oldprotect);
        if (!status)
            return FALSE;

        memset(reinterpret_cast<void*>(Address), 0x00, size);
        VirtualProtect(reinterpret_cast<void*>(Address), size, oldprotect, &oldprotect);
        return TRUE;
    }

    // Extra Tools
public:

    /// <summary>
    //	Gets distance from Position A to Position B
    /// </summary>
    /// <param name="POS">Position A</param>
    /// <param name="POS2">Position B</param>
    /// <returns>Vector3</returns>
    float GetDistanceTo3DObject(Vector3 POS, Vector3 POS2)
    {
        float x = (POS2.x - POS.x);
        float y = (POS2.y - POS.y);
        float z = (POS2.z - POS.z);
        float distance = std::sqrt(x * x + y * y + z * z);
        return (distance);
    }
};
inline std::unique_ptr<PS2> g_Engine;
