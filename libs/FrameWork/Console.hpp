#pragma once
#include "header.hpp"
#define CONSOLE_OUTPUT 1

class Console
{
public:
	enum Colors {
		dark_blue = 1,
		dark_green = 2,
		dark_teal = 3,
		dark_red = 4,
		dark_pink = 5,
		dark_yellow = 6,
		dark_white = 7,
		dark_gray = 8,
		blue = 9,
		green = 10,
		teal = 11,
		red = 12,
		pink = 13,
		yellow = 14,
		white = 15,
		DEFAULT = 15,
	};

	//	IO
	FILE* stream_in{};
	FILE* stream_out{};
	FILE* stream_error{};
	char input[32]{};
	char input2[32]{};

	//	ObjectReferences
	HANDLE g_Handle{};
	HWND g_hWnd{};

	//	Class Variables
	bool m_ShowConsole{};
	bool verbose{};
	bool ACTIVE{};

	explicit Console();
	~Console() noexcept = default;
	Console(Console const&) = delete;
	Console(Console&&) = delete;
	Console& operator=(Console const&) = delete;
	Console& operator=(Console&&) = delete;

	//	BASIC FUNCTIONS
	void InitializeConsole(const char* ConsoleName);
	void printdbg(const char* Text, int Color = {}, ...);
	void scandbg(const char* Text, ...);
	void LogEvent(std::string TEXT, bool FLAG);
	void DestroyConsole();

	//	ADVANCED FUNCTIONS
	bool writeFile(const char* Path, const char* Text, unsigned int Length, DWORD* out = {});
	bool readFile(const char* Path, char* Text, unsigned int Length, DWORD* out = {});
	void SaveCFG();
	void LoadCFG();

	//	SPECIAL FUNCTIONS
	const wchar_t* Char2WChar(const char* in);
	const char* WChar2Char(const wchar_t* in);
	const wchar_t* String2WChar(std::string in);
	std::string CurrentProcName(CHAR* path);
};
inline std::unique_ptr<Console> g_Console;