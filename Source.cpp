#include <iostream>
#include <chrono>
#include <ctime>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>
#include <imgui_console/imgui_console.h>
#include <windows.h>
#include "RenderMenu.h"
#include "CSettings.h"
//#include "ChessBoard.h"
#include "RenderClassicChess.h"
//#include "SFC/Svg.hpp"
//void MovePiece(sf::RenderWindow* window, sf::Event event, sf::Sprite& sprite);

std::string toChessNote(sf::Vector2f p)
{
    std::string s = "";
    s += char(p.x / 50 + 97);
    s += char(7 - p.y / 50 + 49);
    return s;
}

sf::Vector2f toCoord(char a, char b)
{
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return sf::Vector2f(x * 50, y * 50);
}
/*void move(std::string str)
{
    sf::Vector2f oldPos = toCoord(str[0], str[1]);
    sf::Vector2f newPos = toCoord(str[2], str[3]);

    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == newPos) f[i].setPosition(-100, -100);

    for (int i = 0; i < 32; i++)
        if (f[i].getPosition() == oldPos) f[i].setPosition(newPos);

    //castling       //if the king didn't move
    if (str == "e1g1") if (position.find("e1") == -1) move("h1f1");
    if (str == "e8g8") if (position.find("e8") == -1) move("h8f8");
    if (str == "e1c1") if (position.find("e1") == -1) move("a1d1");
    if (str == "e8c8") if (position.find("e8") == -1) move("a8d8");
}*/
int main()
{
    //float Scale = 1.5f;

    Starter();
    #pragma region Время/Версия билда
    // получаем текущую дату и время
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    std::stringstream* ss = new stringstream;
    // форматируем дату в нужном формате
    *ss << "Alpha V(0.3.0)  ";
    *ss << std::put_time(&tm, "%d.%m.%Y") << std::endl;
    RenderMenu::VersionBuildStr = ss->str();
    delete ss;

#pragma endregion
	#pragma region Настройка конслоси Windows
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	setlocale(LC_ALL, "Russian");
	#pragma endregion
	#pragma region Создание окна SFML
    sf::RenderWindow* window;
    if (!RenderMenu::CGlobalSettings.video.FullScreen)
    {
        window = new sf::RenderWindow(sf::VideoMode(RenderMenu::CGlobalSettings.video.WinW, RenderMenu::CGlobalSettings.video.WinH), "Chess counterattack", sf::Style::Close);
    }
    else
    {
        window = new sf::RenderWindow(sf::VideoMode::getDesktopMode(), "Chess counterattack", sf::Style::Fullscreen);
        RenderMenu::CGlobalSettings.video.WinW = sf::VideoMode::getDesktopMode().width;
        RenderMenu::CGlobalSettings.video.WinH = sf::VideoMode::getDesktopMode().height;
    }
    sf::Image icon;
    if (!icon.loadFromFile("source\\images\\icon.png"))
    {
        // Ошибка загрузки файла
    }
    // Изменение иконки окна
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    window->setFramerateLimit(RenderMenu::CGlobalSettings.video.FrameRateLimit);

    // Инициализация imgui
    ImGui::SFML::Init(*window);

    // Загрузка шрифта для imgui
   // Load font
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    io.Fonts->AddFontFromFileTTF("source\\Fonts\\impact.ttf", 20.f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

    // Update font texture
    ImGui::SFML::UpdateFontTexture();

    // Настройка стилей для imgui
    ImGui::StyleColorsDark();
    ImGui::GetStyle().WindowBorderSize = 0.f;

    // Загрузка текстур для фона
    sf::Texture texture;
    texture.loadFromFile("source\\images\\background.png");
    sf::Sprite background(texture);
    scaleImage(background, texture.getSize().x, texture.getSize().y);
    ImGui::StyleColorsDark(); // устанавливаем стиль

    ImGuiStyle& style = ImGui::GetStyle(); // получаем текущий стиль

    // изменяем цвет фона кнопок
    style.Colors[ImGuiCol_Button] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

    // изменяем цвет текста на кнопке
    style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    // изменяем отступ вокруг кнопки
    style.FramePadding = ImVec2(10.0f, 5.0f);

    // изменяем выравнивание текста на кнопке
    style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	#pragma endregion
    #pragma region Загрузка шахматных спрайтов
    
    ChessBoard CB;
    #pragma endregion

    


    #pragma region SFMLFont
    sf::Font font;
    if (!font.loadFromFile("source\\Fonts\\arial.ttf"))
    {
        std::cout << "Unable to load font!\n";
        return EXIT_FAILURE;
    }
    #pragma endregion
    #pragma region FPSText
    sf::Clock clock;
    sf::Text fpsText("0", font, 17);
    fpsText.setFillColor(sf::Color::Green);
    fpsText.setPosition(RenderMenu::CGlobalSettings.video.WinW - 100, 5);
    #pragma endregion
    
    int r = 0, g = 0, b = 0;
    const int cellSize = 50;
     
    RenderMenu::CGlobalSettings.chess.scale = 1.5;
    RenderClassicChess ChessRender;
    ChessRender.Rotate(2);
    //ImGuiConsole console;
	#pragma region Цикл отрисовки
        // Основной цикл
        while (window->isOpen())
        {
            
            // Обработка событий окна
            sf::Event event;
            while (window->pollEvent(event))
            {
                ImGui::SFML::ProcessEvent(event);
                if (event.type == sf::Event::Closed)
                    window->close();
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Tilde)
                    {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
                        {
                            RenderMenu::showConsole = RenderMenu::showConsole ? 0 : 1;
                        }

                    }
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        if (RenderMenu::OnGameGUI)
                        {
                            RenderMenu::showRenderMenu = RenderMenu::showRenderMenu == 0 ? 1 : 0;
                        }
                        
                    }
                }
                ChessRender.Mover(event, window);
               
            }
            
            // Начало отрисовки imgui
            //cout << (RenderMenu::CGlobalSettings.video.FrameRateLimit == 0 ? 120 : RenderMenu::CGlobalSettings.video.FrameRateLimit)<<endl;
            ImGui::SFML::Update(*window, sf::seconds(1.f /(RenderMenu::CGlobalSettings.video.FrameRateLimit==0?120: RenderMenu::CGlobalSettings.video.FrameRateLimit)));
            if (RenderMenu::showRenderMenu)
            {
                RenderMenu::ShovMenu(window);
            }
            
            #pragma region FPS
            float deltaTime = clock.restart().asSeconds();

            // Вычисляем текущее FPS
            float fps = 1.0f / deltaTime;

            // Обновляем текст с текущим FPS
            
            fpsText.setString("FPS: " + std::to_string(static_cast<int>(fps)));
            #pragma endregion
            if (RenderMenu::Play)
            {
                RenderMenu::Play = false;
                ChessRender.play();
            }
           
            // Завершение отрисовки imgui
            window->clear();
            window->draw(background);

            if (RenderMenu::OnGameGUI)
            ChessRender.Draw(window);
            if (RenderMenu::OnGameGUI)
            {
                //for (int i = 0; i < 32; i++) ChessRender.SpritePieces[0][i].Piece.move(offset);
                //for (int i = 0; i < 32; i++) window->draw(ChessRender.SpritePieces[0][i].Piece); window->draw(ChessRender.SpritePieces[0][n].Piece);
                //for (int i = 0; i < 32; i++) ChessRender.SpritePieces[0][i].Piece.move(-offset);
            }
            ImGui::SFML::Render(*window);
            
            window->draw(fpsText);
            window->display();
        }

        
        
	
	#pragma endregion
        // Очистка ресурсов imgui
        ImGui::SFML::Shutdown();
        delete window;
        SaveSettings();
	return 0;
}





//Настройки
//// Установка фиксированного размера окна
            //window.setSize(sf::Vector2u(1024, 720));

            //// Отключение масштабирования содержимого окна
            //sf::View view(sf::FloatRect(0, 0, 1024, 720));
            //window.setView(view);