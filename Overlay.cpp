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

void RenderContent()
	{
		ImGui::Text("BASE PCSX2 v1.7 MENU FRAMEWORK");
		ImGui::Text("BUILD VERSION: v1.0");
		ImGui::Text("BUILD DATE: 11/9/2022");

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Button("Test Read", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			auto address = offsets.FrameRate1;

			auto value = g_Engine->PS2Read<int>(offsets.FrameRate1);

			g_Console->printdbg("Test Read Memory:\nFrameRate1: [%08X]\nVALUE: [%i]\n\n", Console::Colors::blue, address, value);
		}

		if (ImGui::Button("Test Write Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			g_Engine->PS2Write<int>(offsets.FrameRate1, 30);

			g_Engine->PS2Write<int>(offsets.FrameRate2, 30);

			g_Console->printdbg("Test Write Memory:\nFrameRate1: [%i]\nFrameRate2: [%i]\n\n", Console::Colors::blue, g_Engine->PS2Read<int>(offsets.FrameRate1), g_Engine->PS2Read<int>(offsets.FrameRate2));

		}

		if (ImGui::Button("Test ResolvePointer", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			auto base = (CPlayer*)offsets.SEALPointer;

			if (base->IsValid()) {
			
				CPlayer::CPlayerPhysics* move = base->PlayerPhysicsPtr();

				g_Console->printdbg("%s", Console::Colors::DEFAULT, base->LogData().c_str());
			}
		}

		if (ImGui::Button("Display Offsets Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			g_Console->printdbg("Dumping Offset Data:\n%s", Console::Colors::DEFAULT, offsets.LogData().c_str());
		}

		if (ImGui::Button("Check isValid", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			Offsets offsets;

			auto base = (CPlayer*)offsets.SEALPointer;

			bool result = base->IsValid();

			switch (result) {

				case (TRUE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::yellow, result); break;

				case (FALSE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::red, result); break;
			}
		}

		if (ImGui::Button("Dump Player Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			auto base = (SOCOM1::CPlayer*)offsets.SEALPointer;

			if (base->IsValid())
				g_Console->printdbg("%s", Console::Colors::DEFAULT, base->LogData().c_str());
		}

		if (ImGui::Button("Give 552", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1:Offsets offsets;

			auto player = (SOCOM1::CPlayer*)offsets.SEALPointer;

			if (player->IsValid())
				player->PrimaryWeapon = CPlayer::CWeapon::AR_552;
		}

		if (ImGui::Button("Dump Entity Array", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::MatchData match;

			std::vector<SOCOM1::CPlayer*> ent = match.GetPlayers();

			if (!ent.empty()) {

				for (int i = 0; i < ent.size(); i++)
					g_Console->printdbg("%s", Console::Colors::DEFAULT, ent[i]->LogData().c_str());

			}

		}

		if (ImGui::Button("Dump Match Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::MatchData data;

			g_Console->printdbg("IsMatchEnded: [%i]\n\n", Console::Colors::yellow, data.isMatchEnded());
		}

		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Button("UNHOOK DLL", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Killswitch = TRUE;
	}

void Menu::Draw()
{
	if (g_GameVariables->m_ShowMenu)
		MainMenu();

	if (g_GameVariables->m_ShowHud)
		HUD(&g_GameVariables->m_ShowHud);

	if (g_GameVariables->m_ShowDemo)
		ImGui::ShowDemoWindow();
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

}