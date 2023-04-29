#pragma once
#include "RenderMenu.h"
#include "CSettings.h"
#include "ChessBoard.h"
struct MoveFrTo
{
    int piecef;
    int pieceto;
    sf::Vector2i from;
    sf::Vector2i to;
    MoveFrTo(sf::Vector2i from, sf::Vector2i to, int piecef, int pieceto) :from(from), to(to), piecef(piecef), pieceto(pieceto) {}
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
    int selected_move;
    bool wb_move;
    OnGameUI(){}
    string MoveToStr(MoveFrTo move)
    {
        if (move.piecef == EMPTYPiece)
            return "-";
        std::string s = "";
        if(move.piecef == WKing)
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
        if (move.piecef == BKing)
        {
            if (move.to.y - move.from.y == 2)
            {
                return "O-O";
            }
            if (move.to.y - move.from.y <= -2)
            {
                return "O-O-O";
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
        ImGui::SetNextWindowSize(ImVec2(WinW / 5.1, WinH / 4));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        ImGui::SetWindowPos("Chess Game", ImVec2(ImVec2(WinW+WinW/3, WinH/4)));
        // Отображаем шахматные ходы
        
        for (size_t i = 0; i < moves.size(); i++)
        {
            
            if (ImGui::Button(MoveToStr(moves[i].White).c_str()))
            {
                
                std::cout << " Ход \n";
            }
            ImGui::SameLine();
            if(moves[i].Black.piecef!=EMPTYPiece)
            if (ImGui::Button(MoveToStr(moves[i].Black).c_str()))
            {
                
                std::cout << " Ход \n";
            }
            ImGui::Columns();
        }
        // Заканчиваем окно ImGui
        ImGui::End();
    }
    void RenderChessMovesWindow(int HBoard, vector <MoveWB> moves,bool& back)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 2.5, WinH / 3.5));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        ImGui::Begin("Chess Game", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        // Кнопки для сдачи, ничьей и отмены хода
        ImGui::BeginGroup();

        //ImGui::SetCursorPos(ImVec2(ImGui::GetWindowWidth() - 200, 10)); // Установка положения курсора внутри группы
        ImGui::SetCursorPos(ImVec2(20, 30));
        if (ImGui::Button(u8"Сдаться"))
        {
            // Обработка сдачи
        }

        ImGui::SetCursorPos(ImVec2(110, 30)); // Установка положения курсора внутри группы
        if (ImGui::Button(u8"Ничья"))
        {
            // Обработка ничьи
        }

        ImGui::SetCursorPos(ImVec2(180, 30)); // Установка положения курсора внутри группы
        if (ImGui::Button(u8"Отменить ход"))
        {
            back = true;
        }

        ImGui::EndGroup();
        // Колонка ходов белых
        ImGui::Text(u8"Ходы белых/чёрных");
        ImGui::Separator();
        ImGui::Columns(2, "moves_columns", true);

        for (auto& move : moves)
        {
            if (ImGui::Button(MoveToStr(move.White).c_str()))
            {
                // Обработка нажатия на ход белых
            }
            ImGui::NextColumn();
            if (ImGui::Button(MoveToStr(move.Black).c_str()))
            {
                // Обработка нажатия на ход чёрных
            }
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
        
        //ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 50); // Установка положения курсора по горизонтали перед рисованием текста




        ImGui::End();
    }
    void WinDraw(int i,bool& b)
    {
        ImGui::SetNextWindowSize(ImVec2(WinW / 5, WinH /6));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 0.5f);
        switch (i)
        {case 0:
            ImGui::Begin(u8"Ничья!", &b);
            break;
        case 1:
            ImGui::Begin(u8"Белые победили!", &b);
            break;
        case 2:
            ImGui::Begin(u8"Чёрные победили!", &b);
            break;
        default:
            break;
        }
        if (ImGui::Button(u8"Ок"))
        {
            b = false;
        }
        ImGui::End();
    }
};

