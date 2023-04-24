#pragma once
#include "ChessBoard.h"
#include "RenderMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <cmath>
struct MoveFrTo
{
    sf::Vector2i from;
    sf::Vector2i to;
    MoveFrTo(sf::Vector2i from, sf::Vector2i to) :from(from), to(to){}
};
struct MoveWB
{
    MoveFrTo White;
    MoveFrTo Black;
    MoveWB(MoveFrTo White, MoveFrTo Black) :White(White), Black(Black){}

};
struct LastMove
{
    int piece;
    sf::Vector2i from;
    sf::Vector2i to;
    LastMove(sf::Vector2i from, sf::Vector2i to,int piece) :from(from), to(to),piece(piece) {}
};
class RenderClassicChess
{
public:
    std::vector<SpritePiece>* SpritePieces;
    sf::Texture* ChessPicesTexture;
    ChessBoard Board;
#pragma region Chess text
    sf::Text ChessText;
    sf::Font font;
    int Rotation;

    LastMove lastmove;

    bool isMove;
    int n;
    float dx, dy;
    sf::Vector2f oldPos, newPos;
    sf::Vector2f offset;
    sf::Vector2i pos;

    sf::SoundBuffer MoveSoundBuffer;
    sf::Sound MoveSound;
    sf::SoundBuffer CaptureSoundBuffer;
    sf::Sound CaptureeSound;

    bool WorB;

    std::vector<MoveWB> Moves;

    RenderClassicChess() :Board(ChessBoard()), Rotation(1), offset(sf::Vector2f(25 * RenderMenu::CGlobalSettings.chess.scale, 25 * RenderMenu::CGlobalSettings.chess.scale)), isMove(0), n(0), dx(0), dy(0), WorB(1) ,lastmove(LastMove(sf::Vector2i(), sf::Vector2i(),12)){
        MoveSoundBuffer.loadFromFile("source\\Sounds\\Move.wav");
        CaptureSoundBuffer.loadFromFile("source\\Sounds\\Сapture.wav");
        MoveSound.setBuffer(MoveSoundBuffer);
        CaptureeSound.setBuffer(CaptureSoundBuffer);

        Rotation = 4;
        ChessText.setFillColor(sf::Color::Green);

        if (!font.loadFromFile("source\\Fonts\\arial.ttf"))
        {
            std::cout << "Unable to load font!\n";
        }
        ChessText.setFont(font);
        ChessText.setCharacterSize(14 * RenderMenu::CGlobalSettings.chess.scale * 0.7);
        //ChessText.setScale(RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.scale);
        ChessPicesTexture = new sf::Texture[EMPTYPiece];

        ChessText.scale(RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.scale);

        ChessPicesTexture[WPawn].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WPawn) + ".png");

        ChessPicesTexture[WKnight].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WKnight) + ".png");

        ChessPicesTexture[WBishop].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WBishop) + ".png");

        ChessPicesTexture[WRook].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WRook) + ".png");

        ChessPicesTexture[WQueen].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WQueen) + ".png");

        ChessPicesTexture[WKing].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(WKing) + ".png");

        ChessPicesTexture[BPawn].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BPawn) + ".png");

        ChessPicesTexture[BKnight].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BKnight) + ".png");

        ChessPicesTexture[BBishop].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BBishop) + ".png");

        ChessPicesTexture[BRook].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BRook) + ".png");

        ChessPicesTexture[BQueen].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BQueen) + ".png");

        ChessPicesTexture[BKing].loadFromFile("source\\images\\ChessPiece\\500png\\" + ChessPieceStr(BKing) + ".png");
        SpritePieces = new std::vector<SpritePiece>;
        for (int i = 0; i < Board.XMax; ++i)
        {
            for (int j = 0; j < Board.YMax; ++j)
            {
                if (Board.board[i][j] != 12)
                {
                    sf::Sprite temp;
                    temp.setScale(0.1 * RenderMenu::CGlobalSettings.chess.scale, 0.1 * RenderMenu::CGlobalSettings.chess.scale);
                    temp.setTexture(ChessPicesTexture[Board.board[i][j]]);
                    temp.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    SpritePieces->push_back(SpritePiece(temp, sf::Vector2i(i, j), (int)Board.board[i][j]));
                }
            }
        }
    }
    void Mover(sf::Event event, sf::RenderWindow* window)
    {

        pos = sf::Mouse::getPosition(*window) - sf::Vector2i(offset);
        /////drag and drop///////
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == sf::Mouse::Left)
                for (int i = 0; i < SpritePieces->size(); i++)
                    if (SpritePieces[0][i].Piece.getGlobalBounds().contains(pos.x + 25 * RenderMenu::CGlobalSettings.chess.scale, pos.y + 25 * RenderMenu::CGlobalSettings.chess.scale))
                    {
                        isMove = true; n = i;
                        dx = pos.x - SpritePieces[0][i].Piece.getPosition().x;
                        dy = pos.y - SpritePieces[0][i].Piece.getPosition().y;
                        oldPos = SpritePieces[0][i].Piece.getPosition();
                    }

        if (event.type == sf::Event::MouseButtonReleased)
            if (event.key.code == sf::Mouse::Left)
            {
                if (isMove)
                {
                    isMove = false;
                    sf::Vector2f p = SpritePieces[0][n].Piece.getPosition() + sf::Vector2f((25 * RenderMenu::CGlobalSettings.chess.scale), (25 * RenderMenu::CGlobalSettings.chess.scale));
                    int min = 50;
                    int xx = -1;
                    int yy = -1;
                    float xp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
                    float yp = RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale;
                    for (int i = 0; i < Board.XMax; ++i)
                    {

                        for (int j = 0; j < Board.YMax; ++j)
                        {
                            //cout << i << " " << j << endl;
                            float temp = sqrt(pow((i * xp + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale - pos.x), 2) + pow((j * yp + RenderMenu::CGlobalSettings.video.WinH / 10 - pos.y), 2));
                            //cout << temp << endl;
                            if (temp < min)
                            {

                                min = temp;
                                xx = i;
                                yy = j;
                            }
                        }
                    }
                    int xe = xx;
                    int temp;
                    int x = xx;
                    int y = yy;
                    switch (Rotation)
                    {
                    case 1:
                        break;
                    case 2:
                        temp = xx;
                        xx = Board.YMax - yy - 1;
                        yy = temp;
                        break;
                    case 3:
                        temp = yy;
                        yy = Board.XMax - xx - 1;
                        xx = temp;
                        break;
                    case 4:

                        yy = Board.YMax - yy - 1;
                        xx = Board.XMax - xx - 1;
                        break;
                    default:
                        break;
                    }
                    std::cout << "(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" << xx << ", " << yy << ") - 1" << std::endl;
                    if (((SpritePieces[0][n].Type>=0&& SpritePieces[0][n].Type  <=5)&&!WorB)|| ((SpritePieces[0][n].Type >= 6 && SpritePieces[0][n].Type <= 11) && WorB))
                    {
                        SpritePieces[0][n].Piece.setPosition(oldPos);
                    }
                    else if (xe != -1&& !(xx == SpritePieces[0][n].Pos.x&&yy == SpritePieces[0][n].Pos.y))
                    {
                        int result = isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(xx, yy));
                        if (0 < result)
                        {

                            newPos = sf::Vector2f(x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);

                            SpritePieces[0][n].Piece.setPosition(newPos);
                            if (WorB)
                            {
                                int del = -1;
                                if (result == 5)
                                {
                                    for (size_t i = 0; i < SpritePieces->size(); i++)
                                    {
                                        if (SpritePieces[0][i].Pos == lastmove.to) {
                                            del = i;
                                            break;
                                        }
                                    }
                                    Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                                }
                                Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy)), MoveFrTo(sf::Vector2i(0, 0), sf::Vector2i(0, 0))));
                                lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                if (result != 5)
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                        del = i;
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                               
                                if (result == 2|| result == 4)
                                {
                                    SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[WQueen]);
                                    SpritePieces[0][n].Type = WQueen;
                                    Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                                }
                                if (del != -1)
                                {
                                    SpritePieces[0].erase(SpritePieces[0].begin() + del);
                                    if (n >= 1)
                                    {
                                        n--;
                                        CaptureeSound.play();
                                    }
                                }
                                else
                                {
                                    MoveSound.play();
                                }
                                WorB = 0;
                            }
                            else
                            {
                                int del = -1;
                                if (result == 5)
                                {
                                    for (size_t i = 0; i < SpritePieces->size(); i++)
                                    {
                                        if (SpritePieces[0][i].Pos == lastmove.to) {
                                            del = i;
                                            break;
                                        }
                                    }
                                    Board.board[lastmove.to.x][lastmove.to.y] = EMPTYPiece;
                                }
                                lastmove = LastMove(SpritePieces[0][n].Pos, sf::Vector2i(xx, yy), Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y]);
                               
                                
                                Moves[Moves.size() - 1].Black.from = SpritePieces[0][n].Pos;
                                Moves[Moves.size() - 1].Black.to = sf::Vector2i(xx, yy);
                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = EMPTYPiece;
                                if (result != 5)
                                for (size_t i = 0; i < SpritePieces->size(); i++)
                                {
                                    if (SpritePieces[0][i].Pos == sf::Vector2i(xx, yy)) {
                                        del = i;
                                        break;
                                    }
                                }
                                SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);

                                Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                                if (result == 2)
                                {
                                    SpritePieces[0][n].Piece.setTexture(ChessPicesTexture[BQueen]);
                                    SpritePieces[0][n].Type = BQueen;
                                    Board.board[SpritePieces[0][n].Pos.x][SpritePieces[0][n].Pos.y] = SpritePieces[0][n].Type;
                                }
                                cout << ChessPieceStr(SpritePieces[0][n].Type) << endl;
                                WorB = 1;
                                if (del != -1)
                                {
                                    SpritePieces[0].erase(SpritePieces[0].begin() + del);
                                    if (n >= 1)
                                    {
                                        n--;
                                        CaptureeSound.play();
                                    }
                                   
                                }
                                else
                                {
                                    MoveSound.play();
                                }
                            }
                        }
                        else
                            SpritePieces[0][n].Piece.setPosition(oldPos);
                    }
                    else
                        SpritePieces[0][n].Piece.setPosition(oldPos);

                    //if (oldPos != newPos) //position += str + " ";
                }
            }
    
    }
  
    
    void Draw(sf::RenderWindow* window)
    {
        if (isMove) SpritePieces[0][n].Piece.setPosition(pos.x - dx, pos.y - dy);
        for (int i = 0; i < Board.XMax; ++i)
        {
            for (int j = 0; j < Board.YMax; ++j)
            {
                

                sf::RectangleShape square(sf::Vector2f(RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale));
                square.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                // Чередование цветов клеток
                if (Rotation == 2 || Rotation == 3)
                {
                    if ((i + j) % 2 == 0)
                    {
                        ChessText.setFillColor(sf::Color(209, 139, 71));// Коричневый
                        square.setFillColor(sf::Color(255, 206, 158)); // Бежевый
                    }
                    else
                    {
                        ChessText.setFillColor(sf::Color(255, 206, 158));// Бежевый
                        square.setFillColor(sf::Color(209, 139, 71)); // Коричневый

                    }
                }
                else
                {
                    if ((i + j) % 2 != 0)
                    {
                        ChessText.setFillColor(sf::Color(209, 139, 71));// Коричневый
                        square.setFillColor(sf::Color(255, 206, 158)); // Бежевый
                    }
                    else
                    {
                        ChessText.setFillColor(sf::Color(255, 206, 158));// Бежевый
                        square.setFillColor(sf::Color(209, 139, 71)); // Коричневый

                    }
                }
                window->draw(square);
                    #pragma region Исправить
                //            switch (Rotation)
                //{
               
                //            case 1:
                //                if ((Board.YMax - 1 - j == 0) || (Board.XMax - 1 - i == 0))
                //                {
                //                    ChessText.setPosition((Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    if (j == Board.YMax - 1)
                //                    {
                //                        ChessText.setString(std::to_string((i + 1)));
                //                        ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                        window->draw(ChessText);
                //                    }
                //                    if ((i == Board.YMax - 1) && j != Board.YMax - 1)
                //                    {
                //                        ChessText.setString(std::string(1, 'A' + Board.YMax - 1 - j));
                //                        ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                        window->draw(ChessText);
                //                    }
                //                }
                //                break;
                //            case 3:
                //                if ((j == 0) || (i == 0))
                //                {
                //                    ChessText.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }


                //                break;
                //            case 4:
                //                if ((j == 0) || (i == 0))
                //                {
                //                    ChessText.setPosition(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }
                //                break;
                //            case 2:
                //                if (j == Board.YMax - 1)
                //                {
                //                    ChessText.setString(std::to_string((Board.XMax - i)));
                //                    ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.YMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }
                //                if ((i == Board.XMax - 1) && j != Board.YMax - 1)
                //                {
                //                    ChessText.setString((char)(Board.YMax - 1 - j + 'A'));
                //                    ChessText.setPosition((Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.YMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                //                    window->draw(ChessText);
                //                }

                //                break;
                //            default:
                //                break;
                //            }
                //            ////исправить
            

                        #pragma endregion
                
            }
        }
        
        for (SpritePiece value : *SpritePieces)
        {
            window->draw(value.Piece);
        }
        window->draw(SpritePieces[0][n].Piece);
    }
    void Rotate(int Rotation)
    {
        if (Rotation > 0 && Rotation < 5)
            this->Rotation = Rotation;
        else
            this->Rotation = 1;
        for (int i =0;i< SpritePieces->size();i++)
        {
            switch (Rotation)
            {
            case 4:
                SpritePieces[0][i].Piece.setPosition((Board.XMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 3:
                SpritePieces[0][i].Piece.setPosition((Board.XMax -1 - SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 2:
                
                SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            case 1:
                SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            }
        }
    }
    int isValidMove(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        __int8 piece = Board.board[from.first][from.second];
        __int8 piece2 = Board.board[to.first][to.second];
        cout << ChessPieceStr(piece) << " (" << from.first << ", " << from.second << ")\n";
        cout << ChessPieceStr(piece2) << " (" << to.first << ", " << to.second << ")\n";
        //Огонь по своим
        if (((piece>=0&&piece<=5)&& (piece2 >= 0 && piece2 <= 5))|| ((piece >= 6 && piece <= 11) && (piece2 >= 6 && piece2 <= 11)))
        {
            return false;
        }
        bool p = false;//препядствие
        switch (piece)
        {
            ///Белая пешка
        case WPawn:
            return isValidMovePawn(from, to);
            break;
        case BPawn:
            return isValidMovePawn(from, to);
            break;
            case WBishop:
                return isValidMoveDiag(from, to);
                break;
            case BBishop:
                return isValidMoveDiag(from, to);
                break;
            case WKnight:
                return isValidMoveHorse(from, to);
                break;
            case BKnight:
                return isValidMoveHorse(from, to);
                break;
            case WQueen:
                return (isValidMoveHeavy(from, to)|| isValidMoveDiag(from, to));
                break;
            case BQueen:
                return (isValidMoveHeavy(from, to)|| isValidMoveDiag(from, to));
                break;
            case WRook:
                return isValidMoveHeavy(from, to);
                break;
            case BRook:
                return isValidMoveHeavy(from, to);
                break;
            case WKing:
                return isValidMoveKing(from, to);
                break;
            case BKing:
                return isValidMoveKing(from, to);
                break;
        default:
            break;
        }
     

        return false; 
    }
    int isValidMoveHeavy(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        //moves = new std::vector<sf::Vector2i>;
        bool p = false;
        //  ↓
        for (int i = from.first - 1; i >= 0; i--)
        {

            if (Board.board[i][from.second] != EMPTYPiece)
            {
                if (i != to.first || from.second != to.second)
                    p = true;
            }
            if (!p && (i == to.first && from.second == to.second))
            {
                return true;
            }
        }
        p = false;
        // ↑
        for (int i = from.first + 1; i < Board.XMax; i++)
        {

            if (Board.board[i][from.second] != EMPTYPiece)
            {
                if ((i != to.first || from.second != to.second))
                    p = true;
            }
            if (!p && (i == to.first && from.second == to.second))
            {
                return true;
            }
        }
        p = false;
        // ->
        for (int i = from.second + 1; i < Board.YMax; i++)
        {

            if (Board.board[from.first][i] != EMPTYPiece)
            {
                if ((from.first != to.first || i != to.second))
                    p = true;
            }
            if (!p && (from.first == to.first && i == to.second))
            {
                return true;
            }
        }
        p = false;
        // <-
        for (int i = from.second - 1; i >= 0; i--)
        {

            if (Board.board[from.first][i] != EMPTYPiece)
            {
                if ((from.first != to.first || i != to.second))
                    p = true;
            }
            if (!p && (from.first == to.first && i == to.second))
            {
                return true;
            }
        }
        return false;
    }
    int isValidMoveDiag(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        bool p = false;
        //  ↙
        for (int i = from.first - 1, j = from.second-1; i >= 0&&j>=0; i--,j--)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                    p = true;
            }
            if (!p && (i == to.first && j == to.second))
            {
                return true;
            }
        }
        p = false;
        // ↗
        for (int i = from.first + 1,  j = from.second + 1; i < Board.XMax && j < Board.XMax; i++, j++)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                    p = true;
            }
            if (!p && (i == to.first && j == to.second))
            {
                return true;
            }
        }
        
        p = false;
        // ↘
        for (int i = from.first - 1,  j = from.second + 1; i >= 0 && j < Board.YMax; i--, j++)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                    p = true;
            }
            if (!p && (i == to.first && j == to.second))
            {
                return true;
            }
        }
        p = false;
        // ↖
        for (int i = from.first + 1,  j = from.second - 1; i < Board.XMax && j >= 0; i++, j--)
        {

            if (Board.board[i][j] != EMPTYPiece)
            {
                if (i != to.first || j != to.second)
                    p = true;
            }
            if (!p && (i == to.first && j == to.second))
            {
                return true;
            }
        }
        return false;
    }
    int isValidMoveHorse(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        moves = new std::vector<sf::Vector2i>;
        if (from.first+2<Board.XMax&&from.second+1< Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first + 2, from.second + 1));
        }
        if (from.first + 1 < Board.XMax && from.second + 2 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first + 1, from.second + 2));
        }
        if (from.first - 1 >= 0 && from.second + 2 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first - 1, from.second + 2));
        }
        if (from.first - 2 >= 0 && from.second + 1 < Board.YMax)
        {
            moves->push_back(sf::Vector2i(from.first - 2, from.second + 1));
        }
        if (from.first - 2 >= 0 && from.second - 1 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first - 2, from.second - 1));
        }
        if (from.first - 1 >= 0 && from.second - 2 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first - 1, from.second - 2));
        }
        if (from.first + 1 < Board.XMax && from.second - 2 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first + 1, from.second - 2));
        }
        if (from.first + 2 < Board.XMax && from.second - 1 >= 0)
        {
            moves->push_back(sf::Vector2i(from.first + 2, from.second - 1));
        }
        for (size_t i = 0; i < moves->size(); i++)
        {
            if ((moves[0][i].x==to.first)&& (moves[0][i].y == to.second))
            {
                delete moves;
                return true;
            }
        }
        return false;
    }
    int isValidMoveKing(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        __int8 piece = Board.board[from.first][from.second];
        //moves = new std::vector<sf::Vector2i>;
        if ((((from.first-to.first<=1) && (from.first - to.first) >=-1))&& ((from.second - to.second <= 1) && (from.second - to.second) >= -1))
        {

            __int8 tto = Board.board[to.first][to.second];
            

            if (piece == WKing)
            {
                Board.board[to.first][to.second] = WKing;
                Board.board[from.first][from.second] = EMPTYPiece;

                for (size_t i = 0; i < Board.XMax; i++)
                {
                    for (size_t j = 0; j < Board.YMax; j++) {
                        if ((Board.board[i][j] != EMPTYPiece && Board.board[i][j] != BKing)&& Board.board[i][j]>=6)
                        {
                            int result = isValidMove(std::pair(i,j), to);
                            if (result!=0)
                            {
                                Board.board[to.first][to.second] = tto;
                                Board.board[from.first][from.second] = WKing;
                                return false;
                            }
                        }
                    }
                }
            }
            if (piece == BKing)
            {
                for (size_t i = 0; i < Board.XMax; i++)
                {
                    for (size_t j = 0; j < Board.YMax; j++) {
                        if ((Board.board[i][j] != EMPTYPiece && Board.board[i][j] != WKing) && Board.board[i][j] < 6)
                        {
                            int result = isValidMove(std::pair(i, j), to);
                            if (result != 0 || result == -1)
                            {
                                return false;
                            }
                        }
                    }
                }
            }
            return true;
        }
        return false;
    }
    int isValidMovePawn(std::pair<int, int> from, std::pair<int, int> to, std::vector<sf::Vector2i>* moves = nullptr)
    {
        moves = new std::vector<sf::Vector2i>;
        __int8 piece = Board.board[from.first][from.second];
        __int8 piece2 = Board.board[to.first][to.second];
        switch (piece)
        {
        case WPawn:
            if (from.first == 1)
            {
                if ((to.first - from.first) == 2 && from.second - to.second == 0)
                {
                    //Если 2 клетки пусты, можно идти
                    if (piece2 == EMPTYPiece && Board.board[to.first - 1][to.second] == EMPTYPiece)
                    {
                        return 3;
                    }

                }

            }
            if ((to.first - from.first) == 1 && (from.second - to.second) <= 1 && (from.second - to.second) >= -1)
            {
                
                if (from.second - to.second != 0 && (piece2 != EMPTYPiece))
                {
                    if (to.first == (Board.XMax - 1))
                    {
                        return 4;
                    }
                    return true;
                }

                /*Взятие на проходе*/
                if (lastmove.piece == BPawn)
                {
                    if ((lastmove.from.x - lastmove.to.x) == 2)
                    {
                        if (to.first< lastmove.from.x&& to.first > lastmove.to.x)
                        {
                            if (to.second == lastmove.to.y)
                            {
                                return 5;
                            }
                        }
                    }
                }
                if (from.second - to.second == 0 && piece2 == 12)
                {
                    if (to.first == (Board.XMax - 1))
                    {
                        return 2;
                    }
                    return true;
                }


            }
            break;
        case BPawn:
            if ((Board.XMax - 1 - from.first) == 1)
            {
                if ((to.first - from.first) == -2 && from.second - to.second == 0)
                {
                    //Если 2 клетки пусты, можно идти
                    if (piece2 == EMPTYPiece && Board.board[to.first + 1][to.second] == EMPTYPiece)
                    {
                        return 3;
                    }

                }

            }
            if ((to.first - from.first) == -1 && (from.second - to.second) <= 1 && (from.second - to.second) >= -1)
            {
                if (from.second - to.second != 0 && (piece2 != EMPTYPiece))
                {
                    if (to.first == 0)
                    {
                        return 4;
                    }
                    return true;
                }
                /*Взятие на проходе*/
                if (lastmove.piece == WPawn)
                {
                    if ((lastmove.to.x- lastmove.from.x) == 2)
                    {
                        if (to.first> lastmove.from.x && to.first < lastmove.to.x)
                        {
                            if (to.second == lastmove.to.y)
                            {
                                return 5;
                            }
                        }
                    }
                }
                if (from.second - to.second == 0 && piece2 == 12)
                {
                    if (to.first == 0)
                    {
                        return 2;
                    }
                    return true;
                }


            }
        }
        return 0;
    }
    void play()
    {
        for (size_t i = 0; i < Moves.size(); i++)
        {
            cout << "#" << i << endl;
            cout << "White: from (" << Moves[i].White.from.x << ", " << Moves[i].White.from.y << ")to (" << Moves[i].White.to.x << ", " << Moves[i].White.to.y << ")\n";
            cout << "Black: from (" << Moves[i].Black.from.x << ", " << Moves[i].Black.from.y << ")to (" << Moves[i].Black.to.x << ", " << Moves[i].Black.to.y << ")\n";

        }
    }
    ~RenderClassicChess()
    {
       delete[] ChessPicesTexture;
    }
};

