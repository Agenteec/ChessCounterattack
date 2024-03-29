#pragma once


#include <imgui.h>
#include "SFtoS.h"
#include "CSettings.h"
#include "OnGameUI.h"
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <imgui_console/imgui_console.h>
#include <cstdlib>
#include <fstream>
void Starter();
void SaveSettings();
void StartServer();
void scaleImage(sf::Sprite& sprite, int desiredWidth, int desiredHeight);
class RenderMenu
{
public:
    static bool showRenderMenu;


    ///����������� � ��������� �����
    static int gameMode; // ������ ���������� ������ ����
    static float moveTime; // ���������� ������ �� ���
    static int addTimeIndex; // ������ ���������� ������� ��� ����������

    static bool isControlTime;
    static bool withRating;
    static const char* gameModes[];
    static const char* addTimes[];
    static const float moveTimes[];

    ///����������� � ��������� �����\\\

    static bool OnGameGUI;
    static bool OnNetGameGUI;
    static bool Play;

    static bool is_server_waiting;

    static bool showConsole;
    static bool showSettings;
    static bool showLocalGame;
    static bool showNetworkGame;
    static bool showNetworkGameCreator;
    
    static bool ServerOrClient;
    //static RenderClassicChess* netGame;
    static bool ShowGraphicsSettings;
    static bool showControlsSettings;
    static bool showSoundSettings;

    static float deltaTime;
    static float lastFrameTime;
    static int fps;

    static bool showReloadDialog;
    static ImGuiConsole console;

    static CSettings tempSettings;

    static CSettings CGlobalSettings;

    static string VersionBuildStr;
    
    static void restart_program();
    static void ReloaderDialog();
    
    
    static void ShowControlSettings()
    {
        if (ImGui::CollapsingHeader(u8"����������"))
        {
            #pragma region ������
            ImGui::Text(u8"������");
            ImGui::SameLine();
            ImGui::PushID("Jump");

            if (ImGui::Button(SFtoS::toString(tempSettings.controls.Jump).c_str()))
            {
                ImGui::OpenPopup("JumpKeyPopup");
            }
            if (ImGui::BeginPopup("JumpKeyPopup"))
            {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
                {
                    if (ImGui::Selectable(SFtoS::toString(static_cast<sf::Keyboard::Key>(i)).c_str()))
                    {
                        tempSettings.controls.Jump = static_cast<sf::Keyboard::Key>(i);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::PopID();
            #pragma endregion

            

            ImGui::Text(u8"�����");
            ImGui::SameLine();
            ImGui::PushID(u8"Shoot");
            if (ImGui::Button(SFtoS::toString(tempSettings.controls.Attack).c_str()))
            {
                ImGui::OpenPopup(u8"ShootKeyPopup");
            }
            if (ImGui::BeginPopup(u8"ShootKeyPopup"))
            {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
                {
                    if (ImGui::Selectable(SFtoS::toString(static_cast<sf::Keyboard::Key>(i)).c_str()))
                    {
                        tempSettings.controls.Attack = static_cast<sf::Keyboard::Key>(i);
                        ImGui::CloseCurrentPopup();
                    }
                }
                ImGui::EndPopup();
            }
            ImGui::PopID();
        }
    }

    static void showGraphicsSettings()
    {
        ImGui::Text(u8"��������� �������");
        ImGui::SliderFloat(u8"�������", &tempSettings.video.brightness, 0.0f, 1.0f);
        ImGui::Text(u8"������ ����");
        ImGui::SameLine();
        ImGui::PushID("WinSize");

        std::string s;
        s = "";
        s += std::to_string((int)tempSettings.video.WinW) + "x" + std::to_string((int)tempSettings.video.WinH);
        if (ImGui::Button(s.c_str()))
        {
            ImGui::OpenPopup("WindowSize");
        }
        if (ImGui::BeginPopup("WindowSize"))
        {
            if (ImGui::Selectable("Adaptive"))
            {

                tempSettings.video.WinH = sf::VideoMode::getDesktopMode().height;
                tempSettings.video.WinW = sf::VideoMode::getDesktopMode().width;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1920x1080"))
            {
                tempSettings.video.WinH = 1080;
                tempSettings.video.WinW = 1920;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1366x768"))
            {
                tempSettings.video.WinW = 1366;
                tempSettings.video.WinH = 768;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1280x720"))
            {
                tempSettings.video.WinW = 1280;
                tempSettings.video.WinH = 720;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("1024x768"))
            {
                tempSettings.video.WinW = 1024;
                tempSettings.video.WinH = 768;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("800x600"))
            {
                tempSettings.video.WinW = 800;
                tempSettings.video.WinH = 600;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("640x480"))
            {
                tempSettings.video.WinW = 640;
                tempSettings.video.WinH = 480;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();
        ImGui::Checkbox("Vsynk", &tempSettings.video.Vsynk);
        ImGui::Checkbox(u8"������ �����", &tempSettings.video.FullScreen);
        ImGui::Text(u8"FrameRateLimit");
        ImGui::SameLine();
        ImGui::PushID("FrameRateLimit");
        s = "";
        s += std::to_string((int)tempSettings.video.FrameRateLimit);
        if (ImGui::Button(s.c_str()))
        {
            ImGui::OpenPopup("FrameRateLimit");
        }
        if (ImGui::BeginPopup("FrameRateLimit"))
        {

            if (ImGui::Selectable("30"))
            {
                tempSettings.video.FrameRateLimit = 30;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("60"))
            {
                tempSettings.video.FrameRateLimit = 60;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("120"))
            {
                tempSettings.video.FrameRateLimit = 120;
                ImGui::CloseCurrentPopup();
            }
            if (ImGui::Selectable("Off limit"))
            {
                tempSettings.video.FrameRateLimit = 0;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();

    }

    static void ShowLocalGame()
    {
        ImGui::Begin(u8"�������� ��������� ����",&showLocalGame);

        // ����� ������ ����

        ImGui::Text(u8"������� �����:");
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 8, 4);

        // ����� �������� �������
        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(u8"�������� �������", &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(u8"�������� �������:");
                ImGui::SliderFloat(u8"����� �� ������", &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(u8"���������� ������ �� ���", &addTimeIndex, addTimes, 6);
            }
            ImGui::Checkbox(u8"����������� ������", &withRating);
            // ������ "������" � "������"
        }
        

        if (ImGui::Button(u8"������"))
        {
            showRenderMenu = false;
            showLocalGame = false;

            OnGameGUI = true;

            printf("Starting game...\n");
        }

        ImGui::SameLine();

        if (ImGui::Button(u8"������"))
        {
            showLocalGame = 0;
        }

        // ���������� ���� ImGui

        ImGui::End();

    }

    static void ShowNetworkGame()
    {
        ImGui::Begin(u8"�������� ������� ����", &showNetworkGameCreator);

        // ����� ������ ����

        ImGui::Text(u8"������� �����:");
        ImGui::ListBox("##gamemode", &RenderMenu::gameMode, gameModes, 8, 4);

        // ����� �������� �������

        if (RenderMenu::gameMode != 7)
        {
            ImGui::Checkbox(u8"�������� �������", &isControlTime);
            if (isControlTime)
            {
                ImGui::Text(u8"�������� �������:");
                ImGui::SliderFloat(u8"����� �� ������", &moveTime, 30.0f, 3600.0f, "%.0f sec");
                ImGui::Combo(u8"���������� ������ �� ���", &addTimeIndex, addTimes, 6);
            }
            ImGui::Checkbox(u8"����������� ������", &withRating);
            // ������ "������" � "������"
        }


        if (ImGui::Button(u8"������"))
        {
            StartServer();
            is_server_waiting = true;
            showRenderMenu = false;
            showLocalGame = false;
            showNetworkGameCreator = false;
            showNetworkGame = false;
            OnNetGameGUI = true;
            ServerOrClient = true;
            printf("Starting game...\n");
        }

        ImGui::SameLine();

        if (ImGui::Button(u8"������"))
        {
            showNetworkGameCreator = 0;
        }

        // ���������� ���� ImGui

        ImGui::End();

    }

    static void NetworkMenu()
    {
        ImGui::Begin(u8"������� ����",&showNetworkGame);

        ImGui::Text(u8"����������� � �������");
        static char serverAddress[64] = "127.0.0.1"; // IP-����� �������
        ImGui::InputText(u8"����� �������", serverAddress, 64);

        if (ImGui::Button(u8"������������")) {
            cout << serverAddress << endl;
            CGlobalSettings.network.ip = serverAddress;
            ServerOrClient = false;
            is_server_waiting = false;
            showRenderMenu = false;
            showLocalGame = false;
            showNetworkGameCreator = false;
            showNetworkGame = false;
            OnNetGameGUI = true;
            
            printf("Starting game...\n");
        }

        ImGui::Separator();

        ImGui::Text(u8"������ ��������� ���");
        static std::vector<std::string> games;// = GetAvailableGames(); // ��������� ������ ��������� ���
        //games.push_back("127.0.0.1");
        static int selectedGame = 0; // ������ ��������� ����
        static bool gameListChanged = true; // ���� ��������� ������ ���

        if (ImGui::ListBoxHeader(u8"##������ ���", ImVec2(-1, 100))) {
            for (int i = 0; i < games.size(); i++) {
                bool isSelected = (selectedGame == i);
                if (ImGui::Selectable(games[i].c_str(), isSelected)) {
                    selectedGame = i;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::ListBoxFooter();
        }

        if (ImGui::Button(u8"�������� ������ ���")) {
            // ��������� ������� �� ������ "�������� ������ ���"
            //games = GetAvailableGames();
            gameListChanged = true;
        }

        ImGui::Separator();

        if (ImGui::Button(u8"������� ����� ����")) {
            showNetworkGameCreator = true;
        }

        if (ImGui::Button(u8"�������������� � ��������� ����")) {
            // ��������� ������� �� ������ "�������������� � ��������� ����"
            if (selectedGame >= 0 && selectedGame < games.size()) {
                //JoinGame(games[selectedGame]);
            }
        }

        ImGui::End();
    }

    static void SerwerWait()
    {
            ImGui::Begin(u8"Waiting for opponent", &is_server_waiting, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
            ImGui::Text(u8"����������, ��������� ���� � ��� �� ����������� �������...");
            if (ImGui::Button(u8"������"))
            {
                //is_cancelled = true;
            }
            ImGui::End();
        
    }

    static void ImGuiFunctionDebug() {
        // ������� ����������� ���������� ��� ������������ ������� � FPS


        // ��������� ����� ��������� � ���������� ���������� �����
        const float current_time = ImGui::GetTime();
        deltaTime = current_time - lastFrameTime;
        lastFrameTime = current_time;
        fps = 1.0f / deltaTime;

        // ���������� �������� FPS
        ImGui::Begin(u8"Debug", nullptr);
        ImGui::Text("FPS: %d", fps);
        ImGui::End();
    }


	static int ShovMenu(sf::RenderWindow* window)
	{
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.8f);
        if (showSettings)
        {
            ImGui::SetNextWindowSize(ImVec2(800, 400), ImGuiCond_FirstUseEver);
            ImGui::SetNextWindowPos(ImVec2(100, 100), ImGuiCond_FirstUseEver);
            ImGui::Begin(u8"���������", &showSettings);

            if (ImGui::Button(u8"�������"))
            {
                ShowGraphicsSettings = true;
                showControlsSettings = false;
                showSoundSettings = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(u8"����������"))
            {
                ShowGraphicsSettings = false;
                showControlsSettings = true;
                showSoundSettings = false;
            }
            ImGui::SameLine();
            if (ImGui::Button(u8"����"))
            {
                ShowGraphicsSettings = false;
                showControlsSettings = false;
                showSoundSettings = true;
            }

            if (ShowGraphicsSettings)
            {
                showGraphicsSettings();
            }
            else if (showControlsSettings)
            {
                ImGui::Text(u8"��������� ����������");
                ShowControlSettings();
            }
            else if (showSoundSettings)
            {
                ImGui::Text(u8"��������� �����");
                ImGui::SliderFloat(u8"��������� ���������", &tempSettings.volume.ambientVolume, 0.0f, 1.0f);
                ImGui::SliderFloat(u8"��������� ������", &tempSettings.volume.musicVolume, 0.0f, 1.0f);
            }

            ImGui::Separator();

            ImGui::SetCursorPos(ImVec2(ImGui::GetWindowContentRegionMax().x - 300, ImGui::GetWindowContentRegionMax().y - 50));

            // ��������� ������ ������ � ����������� �� ������
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0)); // ������������� ���������� ����� ����������
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.8f, 0.3f, 1.0f)); // ������������� ���� ������
            if (ImGui::Button(u8"��", ImVec2(80, 0))) {
                // ��������, ����������� ��� ������� �� ������
                showSettings = false;
                if (tempSettings.SetSettings(window) || tempSettings.video.FullScreen != CGlobalSettings.video.FullScreen)
                {
                    showReloadDialog = true;
                }
                CGlobalSettings = tempSettings;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();

            // ��������� ������ ������ � ����������� �� ������
            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.3f, 0.3f, 1.0f));
            if (ImGui::Button(u8"������", ImVec2(80, 0))) {
                // ��������, ����������� ��� ������� �� ������
                tempSettings = CGlobalSettings;
                showSettings = false;
            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();

            // ��������� ������ ������ � ����������� �� ������
            ImGui::SameLine();
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5, 0));
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.8f, 1.0f));
            if (ImGui::Button(u8"���������", ImVec2(100, 0))) {
                // ��������, ����������� ��� ������� �� ������
                if (tempSettings.SetSettings(window)|| tempSettings.video.FullScreen != CGlobalSettings.video.FullScreen)
                {
                    showReloadDialog = true;
                }
                CGlobalSettings = tempSettings;

            }
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
            ImGui::End();
        }
        if (showConsole)
        {
            console.Draw(&showConsole);
            ImGuiFunctionDebug();
        }
        if (showReloadDialog)
        {
            ReloaderDialog();
        }
        if (showLocalGame)
        {
            ShowLocalGame();
        }
        if (showNetworkGame)
        {
            NetworkMenu();
        }
        if (showNetworkGameCreator)
        {
            ShowNetworkGame();
        }
        if (is_server_waiting)
        {
            SerwerWait();
        }
        // �������� �������� ���� imgui
        ImGui::SetNextWindowSizeConstraints(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImVec2(FLT_MAX, FLT_MAX));
        ImGui::SetNextWindowSize(ImVec2(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.25f);
        ImGui::Begin(VersionBuildStr.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoBringToFrontOnFocus);

        // ��������� ������
        ImGui::Dummy(ImVec2(10.0f, RenderMenu::CGlobalSettings.video.WinH / 2));
        if (OnGameGUI)
            if (ImGui::Button(u8"��������� ����", ImVec2(200.f, 50.f)))
            {
                
                OnGameGUI = false;
            }
        if (!OnGameGUI)
        if (ImGui::Button(u8"��������� ����", ImVec2(200.f, 50.f)))
        {
            
            showLocalGame = true;
        }
        ImGui::Spacing();
        if (!OnGameGUI)
        if (ImGui::Button(u8"������� ����", ImVec2(200.f, 50.f)))
        {
            showNetworkGame = true;
        }
        ImGui::Spacing();
        if (!OnGameGUI)
        if (ImGui::Button(u8"��������� ����", ImVec2(200.f, 50.f)))
        {
            
        }
        ImGui::Spacing();
        if (ImGui::Button(u8"���������", ImVec2(200.f, 50.f)))
        {
            showSettings = true;
        }
        ImGui::Spacing();
        if (ImGui::Button(u8"�����", ImVec2(200.f, 50.f)))
        {
            window->close();
        }

        // �������� �������� ���� imgui
        ImGui::End();
        return 0;
	}
    

};

