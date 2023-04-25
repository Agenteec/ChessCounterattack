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

        // ���������� ��������� ����
        if (ImGui::Button(u8"��� 1: e2 -> e4"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }
        if (ImGui::Button(u8"��� 2: d7 -> d5"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }
        if (ImGui::Button(u8"��� 2: d7 -> d5"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }
        if (ImGui::Button(u8"��� 2: d7 -> d5"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }
        if (ImGui::Button(u8"��� 2: d7 -> d5"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }
        if (ImGui::Button(u8"��� 2: d7 -> d5"))
        {
            // �������� ��� ������� �� ���
            std::cout << " ��� \n";
        }

        // ����������� ���� ImGui
        ImGui::End();
	}
};

