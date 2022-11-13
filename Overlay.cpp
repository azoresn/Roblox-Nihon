#include "include/Overlay.hpp"

//-----------------------------------------------------------------------------------
//										MENU
//-----------------------------------------------------------------------------------

void InitStyle()
{
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = ImGui::GetStyle().Colors;

	//	STYLE PROPERTIES
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);

	//  Base ImGui Styling , Aplying a custyom style is left up to you.
	ImGui::StyleColorsClassic();

	/// EXAMPLE COLOR 
	//colors[ImGuiCol_FrameBg] = ImVec4(0, 0, 0, 0);

	//	COLORS
	if (g_Menu->dbg_RAINBOW_THEME) {
		//  RGB MODE STLYE PROPERTIES
		colors[ImGuiCol_Separator] = ImVec4(g_Menu->dbg_RAINBOW);
		colors[ImGuiCol_TitleBg] = ImVec4(0, 0, 0, 1.0f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0, 0, 0, 1.0f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0, 0, 0, 1.0f);
	}
	else {
		/// YOUR DEFAULT STYLE PROPERTIES HERE
	}
}

static ImVec4 defaultColor = ImVec4(16.0f / 255.0f, 16.0f / 255.0f, 16.0f / 255.0f, 128.0f / 255.0f);
static ImVec4 color_picker = ImVec4(16.0f / 255.0f, 16.0f / 255.0f, 16.0f / 255.0f, 128.0f / 255.0f);

void ChangeOutlineColor(ImVec4 Color)
{

	// Convert ImVec4
	float test[4] = { (Color.x * 255), (Color.y * 255), (Color.z * 255), (Color.w * 255) };

	Offsets offsets;
	auto address = offsets.CustomColors;
	if (g_Engine->PS2Read<int>(address) != NULL)
		g_Engine->PS2Write<int>(address, NULL);

	auto colorAddress = offsets.EntityOutlineColors;
	for (int i = 0; i < 4; i++) {
		g_Engine->PS2Write<int8_t>(colorAddress, test[i]);
		colorAddress++;
	}

	g_Engine->PS2Write<int>(address, 0xAC910268);
}


void RGBSLY()
{
	// Convert ImVec4
	float test[4] = { (g_Menu->dbg_RAINBOW.Value.x * 255), (g_Menu->dbg_RAINBOW.Value.y * 255), (g_Menu->dbg_RAINBOW.Value.z * 255), (g_Menu->dbg_RAINBOW.Value.w * 255) };
	Offsets offsets;
	auto colorAddress = offsets.EntityOutlineColors;
	for (int i = 0; i < 4; i++) {
		g_Engine->PS2Write<int8_t>(colorAddress, test[i]);
		colorAddress++;
	}
}

// Default Sly Backpack = 0x447A00
static bool bSlyOutline = FALSE;
static bool bRGB_SLY = FALSE;
static bool bActiveOutline = FALSE;
void RenderContent()
{
	//  Initize so that we can set and store ImGui Content Positions
	ImGuiWindow* window = GImGui->CurrentWindow;
	ImVec2 ToolLocation;

	ImGui::Text("PCSX2 v1.7 MENU FRAMEWORK");
	ImGui::Text("BUILD VERSION: v1.0");
	ImGui::Text("DATE: %s", g_Console->GetTimeString().c_str());

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	Sly1::Offsets offsets;
	Sly1::JT* PLAYER = (Sly1::JT*)offsets.slyPointer;

	ImGui::Toggle(" Sly Outline ", &bSlyOutline);
	if (bSlyOutline)
	{
		window->DC.CursorPos.x = (window->DC.CursorPos.x + 10);
		ToolLocation.x = window->DC.CursorPos.x;
		ImGui::SameLine();
		if (ImGui::Button("RESET"))
			ChangeOutlineColor(defaultColor);
		ImGui::SameLine();
		ImGui::ColorEdit4("##fhajwdegfjSG", (float*)&color_picker, ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_AlphaPreviewHalf | ImGuiColorEditFlags_NoInputs);
		ImGui::SameLine();
		ImGui::Checkbox("ACTIVE", &bActiveOutline);
		if (bActiveOutline)
			ChangeOutlineColor(color_picker);

	}

	if (ImGui::Toggle("RGB SLY", &bRGB_SLY))
	{
		// on deactivate restore sky outline to normal
		if (!bRGB_SLY)
			ChangeOutlineColor(defaultColor);
	}
	
	if (ImGui::Button("Test Read Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
	{
		auto address = offsets.CustomColors;

		auto value = g_Engine->PS2Read<int>(address);

		g_Console->printdbg("Test Read Memory Address: %llX\nVALUE: [%08X]\n\n", Console::Colors::blue, (address + BasePS2MemorySpace), value);
	}

	if (ImGui::Button("Test Write Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
	{

		auto address = offsets.CustomColors;

		unsigned int value = g_Engine->PS2Read<int>(address);

		if (value != NULL)
			g_Engine->PS2Write<int>(address, NULL);
		else
			g_Engine->PS2Write<int>(address, 0xAC910268);

		g_Console->printdbg("Test Write Memory: %llX\nVALUE: [%08X]\n\n", Console::Colors::blue, address, g_Engine->PS2Read<int>(address));

	}

	if (ImGui::Button("Display Offsets Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		g_Console->printdbg("[+] LOG::OffsetData\n%s", Console::Colors::DEFAULT, offsets.LogData().c_str());

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		g_Killswitch = TRUE;
}

void Menu::Draw()
{
	if (g_GameVariables->m_ShowMenu)
	{
		MainMenu();
	
		if (g_GameVariables->m_ShowDemo)
			ImGui::ShowDemoWindow();
	}

	if (g_GameVariables->m_ShowHud)
		HUD(&g_GameVariables->m_ShowHud);
}

void Menu::MainMenu()
{
	if (!g_GameVariables->m_ShowDemo)
		InitStyle();

	if (g_Menu->dbg_RAINBOW_THEME) {
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_Menu->dbg_RAINBOW));
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(g_Menu->dbg_RAINBOW));
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(g_Menu->dbg_RAINBOW));
	}
	if (!ImGui::Begin("(DX11) ImGui Internal Base", &g_GameVariables->m_ShowMenu, 96))
	{
		ImGui::End();
		return;
	}
	if (g_Menu->dbg_RAINBOW_THEME)
		ImGui::PopStyleColor(3);

	//  Display Menu Content
	RenderContent();

	ImGui::End();
}

void Menu::HUD(bool* p_open)
{

}

void Menu::Loops()
{
	if (bRGB_SLY)
		RGBSLY();
}