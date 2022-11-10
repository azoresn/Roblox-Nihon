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
			auto value = g_Engine->Read<int>(dwGameBase);
			g_Console->printdbg("dwGameBase: %llX\nVALUE: %X\n\n", Console::Colors::blue, dwGameBase, value);
		}

		if (ImGui::Button("Test Write", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			if (offsets.SEALPointer != NULL) {

				auto base = (SOCOM1::CPlayer*)offsets.SEALPointer;

				if (base->IsValid())
					base->Health = 0;	//	Temporary, although this is expected behavior
					//g_Engine->Write<float>(base->Health, 0.f);	// needs thorough testing and though. 
			}
		}

		if (ImGui::Button("Test ResolvePointer", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			if (offsets.SEALPointer != NULL)
			{
				auto base = (CPlayer*)offsets.SEALPointer;
			
				CPlayer::CPlayerPhysics* move = base->PlayerPhysicsPtr();
				
				g_Console->printdbg("%s", Console::Colors::DEFAULT, base->LogData().c_str());
			}
		}

		if (ImGui::Button("Dump Player Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			SOCOM1::Offsets offsets;

			if (offsets.SEALPointer != NULL) {

				auto base = (SOCOM1::CPlayer*)offsets.SEALPointer;

				g_Console->printdbg("%s", Console::Colors::DEFAULT, base->LogData().c_str());
			}
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