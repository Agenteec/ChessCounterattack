#pragma once
#include "RenderMenu.h"
#include "CSettings.h"
#include "ChessBoard.h"
#include <iostream>

class OnGameUI
{
public:
	void draw()
	{
        ImGui::SetNextWindowSize(ImVec2(RenderMenu::CGlobalSettings.video.WinW /4, RenderMenu::CGlobalSettings.video.WinH / 4));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0,  0,  0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);

        // Отображаем шахматные ходы
        if (ImGui::Button(u8"Ход 1: e2 -> e4"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }
        if (ImGui::Button(u8"Ход 2: d7 -> d5"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }
        if (ImGui::Button(u8"Ход 2: d7 -> d5"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }
        if (ImGui::Button(u8"Ход 2: d7 -> d5"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }
        if (ImGui::Button(u8"Ход 2: d7 -> d5"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }
        if (ImGui::Button(u8"Ход 2: d7 -> d5"))
        {
            // Действие при нажатии на ход
            std::cout << " Ход \n";
        }

        // Заканчиваем окно ImGui
        ImGui::End();
	}
};

