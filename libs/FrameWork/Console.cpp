#include "Console.hpp"

Console::Console()
{
	return;
}

void Console::InitializeConsole(const char* ConsoleName)
{
	AllocConsole();
	g_Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	g_hWnd = GetConsoleWindow();
	freopen_s(&stream_in, "CONIN$", "r", stdin);
	freopen_s(&stream_out, "CONOUT$", "w", stdout);
	freopen_s(&stream_error, "CONOUT$", "w", stderr);
	SetConsoleTitleA(ConsoleName);
	ShowWindow(g_hWnd, SW_SHOW);
	return;
}

void Console::printdbg(const char* Text, int Color, ...)
{
	SetConsoleTextAttribute(g_Handle, Color);
	va_list arg;
	va_start(arg, Color);
	vfprintf(stream_out, Text, arg);
	va_end(arg);
	SetConsoleTextAttribute(g_Handle, Colors::DEFAULT);
	return;
}

void Console::scandbg(const char* Text, ...)
{
	va_list arg;
	va_start(arg, Text);
	vfscanf(stream_in, Text, arg);
	va_end(arg);
	return;
}

bool Console::writeFile(const char* Path, const char* Text, unsigned int Length, DWORD* out)
{
	DWORD temp = 0;
	if (out == NULL)
		out = &temp;
	*out = 0;
	auto handle = CreateFileA(Path, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle)
	{
		bool result = WriteFile(handle, Text, Length, out, NULL) && *out > 0;
		CloseHandle(handle);
		return result;
	}
	return false;
}

bool Console::readFile(const char* Path, char* Text, unsigned int Length, DWORD* out)
{
	DWORD temp = 0;
	if (out == NULL)
		out = &temp;
	*out = 0;
	auto handle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (handle)
	{
		bool result = ReadFile(handle, Text, Length, out, NULL) && *out > 0;
		CloseHandle(handle);
		return result;
	}
	return false;
}

/// <summary>
/// Log Toggle Events
/// </summary>
/// <param name="EXAMPLE: ">g_Console->LogEvent("[+] MENU:: ESP - ", g_GameVariables->bESP);</param>
void Console::LogEvent(std::string TEXT, bool FLAG)
{
	std::string output;
	std::string append;
	int color;
	switch (FLAG) {
	case(TRUE):
		output = " [ON]\n";
		color = Colors::green;
		append = TEXT + output;
		printdbg(append.c_str(), color);
		break;
	case(FALSE):
		output = " [OFF]\n";
		color = Colors::red;
		append = TEXT + output;
		printdbg(append.c_str(), color);
		break;
	}
}

const wchar_t* Console::Char2WChar(const char* in)
{
	if (in == NULL) {
		wchar_t* Out = NULL;
		return Out;
	}
	wchar_t* Out = new wchar_t[strlen(in) + 1];
	mbstowcs_s(NULL, Out, strlen(in) + 1, in, strlen(in));
	return Out;
}

const char* Console::WChar2Char(const wchar_t* in)
{
	if (in == L"") {
		const char* e_out = NULL;
		return e_out;
	}
	std::wstring convert(in);
	std::string out(convert.begin(), convert.end());
	return out.c_str();
}

const wchar_t* Console::String2WChar(std::string in)
{
	if (in == "") {
		wchar_t* out = NULL;
		return out;
	}
	std::wstring convert = std::wstring(in.begin(), in.end());
	const wchar_t* out = convert.c_str();
	return out;
}

std::string Console::CurrentProcName(CHAR* path)
{
	//  Obtain full module path
	GetModuleFileNameA(NULL, path, MAX_PATH);
	const std::string fullpath = path;

	//  Search for last backslash in the index
	const size_t lastSlashIndex = fullpath.find_last_of("/\\");

	//  remove everything except the filename and return
	return fullpath.substr(lastSlashIndex + 1);
}

void Console::DestroyConsole()
{
	fclose(stream_in);
	fclose(stream_out);
	fclose(stream_error);
	DestroyWindow(g_hWnd);
	FreeConsole();
	return;
}