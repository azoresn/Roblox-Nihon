#include "include/Overlay.hpp"

//-----------------------------------------------------------------------------------
//										MENU
//-----------------------------------------------------------------------------------
CWeapon WeaponData;
void WeaponManager(CPlayer* player)
{
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::TextCentered("[WEAPON MANAGER]", TRUE, ImColor(0, 255, 255, 200));
	ImGui::Separator();
	ImGui::SetNextItemWidth(100);
	ImGui::Combo("##jfhgjdflkhklsdh", (int*)&WeaponData.e_selectedSlot, WeaponData.AvailSlots, IM_ARRAYSIZE(WeaponData.AvailSlots));
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	switch (WeaponData.e_selectedSlot)
	{
		case(0): ImGui::Combo("##jfhgjdflkhklsdh1", (int*)&WeaponData.e_selected_Primary, WeaponData.PrimaryWeapons, IM_ARRAYSIZE(WeaponData.PrimaryWeapons)); break;
		case(1): ImGui::Combo("##kdgdsazhljfna", (int*)&WeaponData.e_selected_Secondary, WeaponData.SecondaryWeapons, IM_ARRAYSIZE(WeaponData.SecondaryWeapons)); break;
		case(2): ImGui::Combo("##zjdfhbadeh", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
		case(3): ImGui::Combo("##hsdfgjsytkiet", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
		case(4): ImGui::Combo("##gjnkdtoythmyuk", (int*)&WeaponData.e_selected_Equipment, WeaponData.EquipmentWeapon, IM_ARRAYSIZE(WeaponData.EquipmentWeapon)); break;
	}
	if (ImGui::Button("GIVE WEAPON", ImVec2(ImGui::GetContentRegionAvail().x, 0)))
	{
		switch (WeaponData.e_selectedSlot)
		{
			case 0:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Primary); break;
			case 1:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Secondary); break;
			case 2:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
			case 3:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
			case 4:        player->GiveWeapon(WeaponData.e_selectedSlot, WeaponData.e_selected_Equipment); break;
		}
	}
}


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

		SOCOM1::Offsets offsets;
		SOCOM1::CPlayer* PLAYER = (CPlayer*)offsets.SEALPointer;
		SOCOM1::MatchData MATCH;

		if (ImGui::Button("Test Read Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			auto address = offsets.FrameRate1;

			auto value = g_Engine->PS2Read<int>(offsets.FrameRate1);

			g_Console->printdbg("Test Read Memory:\nFrameRate1: [%08X]\nVALUE: [%i]\n\n", Console::Colors::blue, address, value);
		}

		if (ImGui::Button("Test Write Memory", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			g_Engine->PS2Write<int>(offsets.FrameRate1, 30);

			g_Engine->PS2Write<int>(offsets.FrameRate2, 30);

			g_Console->printdbg("Test Write Memory:\nFrameRate1: [%i]\nFrameRate2: [%i]\n\n", Console::Colors::blue, g_Engine->PS2Read<int>(offsets.FrameRate1), g_Engine->PS2Read<int>(offsets.FrameRate2));

		}

		if (ImGui::Button("Test ResolvePointer", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {
			
				CPlayer::CPlayerPhysics* move = PLAYER->PlayerPhysicsPtr();

				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Display Offsets Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("Dumping Offset Data:\n%s", Console::Colors::DEFAULT, offsets.LogData().c_str());

		if (ImGui::Button("Check isValid", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			bool result = PLAYER->IsValid();

			switch (result) {

				case (TRUE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::yellow, result); break;

				case (FALSE):	g_Console->printdbg("isValid: [%i]\n", Console::Colors::red, result); break;
			}
		}

		if (ImGui::Button("Dump Player Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
				g_Console->printdbg("%s", Console::Colors::DEFAULT, PLAYER->LogData().c_str());
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Give 552", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid()) {
				//player->PrimaryWeapon = CPlayer::CWeapon::AR_552;
				PLAYER->PrimaryWeapon = CWeapon::AR_552;
				for (int i = 0; i < 10; i++)
					PLAYER->PrimaryMag[i] = 1337;
			}
			else
				g_Console->printdbg("[!] INVALID PLAYER OBJECT\n", Console::Colors::red);
		}

		if (ImGui::Button("Dump Entity Array", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

			if (!ent.empty()) {

				for (int i = 0; i < ent.size(); i++)
					g_Console->printdbg("%s", Console::Colors::DEFAULT, ent[i]->LogData().c_str());

			}

		}

		if (ImGui::Button("Telpeort All Entities", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
		{
			if (PLAYER->IsValid())
			{
				std::vector<SOCOM1::CPlayer*> ent = MATCH.GetPlayers();

				if (!ent.empty()) {

					for (int i = 0; i < ent.size(); i++) {
						
						float distance = PLAYER->GetDistanceTo3DObject(PLAYER->Position, ent[i]->Position);
						g_Console->printdbg("Teleporting Entity:\n- Name: %s\n - Position: { %0.2f, %0.2f, %0.2f }\n - Distance: %0.0fm\n\n", Console::Colors::DEFAULT, ent[i]->GetPlayerName().c_str(), ent[i]->Position.x, ent[i]->Position.y, ent[i]->Position.z, distance);
						ent[i]->Teleport(PLAYER->Position);
					}
				}
			}
		}

		if (ImGui::Button("Dump Match Data", ImVec2(ImGui::GetWindowContentRegionWidth(), 20)))
			g_Console->printdbg("IsMatchEnded: [%i]\n\n", Console::Colors::yellow, MATCH.isMatchEnded());

		if (PLAYER->IsValid())
			WeaponManager(PLAYER);

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