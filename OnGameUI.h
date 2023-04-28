#pragma once
#include "RenderMenu.h"
#include "CSettings.h"
#include "ChessBoard.h"
struct MoveFrTo
{
    int piece;
    sf::Vector2i from;
    sf::Vector2i to;
    MoveFrTo(sf::Vector2i from, sf::Vector2i to, int piece) :from(from), to(to), piece(piece) {}
};
struct MoveWB
{
    MoveFrTo White;
    MoveFrTo Black;
    MoveWB(MoveFrTo White, MoveFrTo Black) :White(White), Black(Black) {}

};

class OnGameUI
{
    
public:
    static float& WinW;
    static float& WinH;
    OnGameUI(){}
    string MoveToStr(MoveFrTo move)
    {
        std::string s = "";
        if(move.piece == WKing|| move.piece == BKing)
        {
            if (move.to.y - move.from.y == 2)
            {
                return "0-0";
            }
            if (move.to.y - move.from.y <= -2)
            {
                return "0-0-0";
            }
        }
       
        s += char(move.from.y + 'A');
        s += char(move.from.x +'1');
        
        s += '-';
        s += char(move.to.y + 'A');
        s += char(move.to.x +'1');
        
        return s;
    }
    void draw(int HBoard,vector <MoveWB> moves)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 5.2, WinH / 4));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos("Chess Game", ImVec2(ImVec2(WinW+WinW/3, WinH/4)));
        // ���������� ��������� ����
        ImGui::Columns();
        for (size_t i = 0; i < moves.size(); i++)
        {
            if (ImGui::Button(MoveToStr(moves[i].White).c_str()))
            {
                
                std::cout << " ��� \n";
            }
            ImGui::SameLine();
            if(moves[i].Black.piece!=EMPTYPiece)
            if (ImGui::Button(MoveToStr(moves[i].Black).c_str()))
            {
                
                std::cout << " ��� \n";
            }
        }
        // ����������� ���� ImGui
        ImGui::End();
    }
    void WinDraw(int i,bool& b)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 3, WinH / 4));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        switch (i)
        {case 0:
            ImGui::Begin(u8"�����!", &b);
            break;
        case 1:
            ImGui::Begin(u8"����� ��������!", &b);
            break;
        case 2:
            ImGui::Begin(u8"׸���� ��������!", &b);
            break;
        default:
            break;
        }
        if (ImGui::Button(u8"��"))
        {
            b = false;
        }
        ImGui::End();
    }
};

