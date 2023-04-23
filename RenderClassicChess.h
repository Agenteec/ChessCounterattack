#pragma once
#include "ChessBoard.h"
#include "RenderMenu.h"
#include <SFML/Graphics.hpp>
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
    
    bool isMove;
    int n;
    float dx, dy;
    sf::Vector2f oldPos, newPos;
    sf::Vector2f offset;
    sf::Vector2i pos;

    bool WorB;

    std::vector<MoveWB> Moves;
    
    RenderClassicChess():Board(ChessBoard()),Rotation(1), offset(sf::Vector2f(25 * RenderMenu::CGlobalSettings.chess.scale, 25 * RenderMenu::CGlobalSettings.chess.scale)), isMove(0),n(0), dx(0), dy(0),WorB(1){
        Rotation = 4;
        ChessText.setFillColor(sf::Color::Green);
        if (!font.loadFromFile("source\\Fonts\\arial.ttf"))
        {
            std::cout << "Unable to load font!\n";
        }
        ChessText.setFont(font);
        ChessText.setCharacterSize(14* RenderMenu::CGlobalSettings.chess.scale*0.7);
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
                switch (Rotation)
                {
                case 4:
                    temp.setPosition((Board.XMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    break;
                case 3:
                    temp.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    break;
                case 2:
                    temp.setPosition((Board.XMax - 1 - j) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (Board.YMax - 1 - i) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    break;
                case 1:
                    temp.setPosition(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    break;
                }
                SpritePieces->push_back(SpritePiece(temp, sf::Vector2i(i, j), (int)Board.board[j][i]));
            }
        }
    }
}
    void Mover(sf::Event event,sf::RenderWindow* window)
    {

        pos = sf::Mouse::getPosition(*window) - sf::Vector2i(offset);
        /////drag and drop///////
        if (event.type == sf::Event::MouseButtonPressed)
            if (event.key.code == sf::Mouse::Left)
                for (int i = 0; i < SpritePieces->size(); i++)
                    if (SpritePieces[0][i].Piece.getGlobalBounds().contains(pos.x+ 25 * RenderMenu::CGlobalSettings.chess.scale, pos.y+ 25 * RenderMenu::CGlobalSettings.chess.scale))
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
                    #pragma region Бинарный поиск расстояния
                    std::vector<int> xCoords;
                    for (int i = 0; i < Board.XMax-1; ++i)
                    {
                        xCoords.push_back(i * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale);
                    }
                    std::sort(xCoords.begin(), xCoords.end());

                    std::vector<int> yCoords;
                    for (int j = 0; j < Board.YMax-1; ++j)
                    {
                        yCoords.push_back(j * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                    }
                    std::sort(yCoords.begin(), yCoords.end());

                    int xx = std::distance(xCoords.begin(), std::lower_bound(xCoords.begin(), xCoords.end(), pos.x));
                    if (xx > 0 && pos.x - xCoords[xx - 1] < xCoords[xx] - pos.x)
                    {
                        xx--;
                    }

                    int yy = std::distance(yCoords.begin(), std::lower_bound(yCoords.begin(), yCoords.end(), pos.y));
                    if (yy > 0 && pos.y - yCoords[yy - 1] < yCoords[yy] - pos.y)
                    {
                        yy--;
                    }
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
                        
                        yy = Board.YMax - yy -1;
                        xx = Board.XMax - xx -1;
                        break;
                    default:
                        break;
                    }
                    std::cout <<"(" << SpritePieces[0][n].Pos.x << ", " << SpritePieces[0][n].Pos.y << ")" << "--> (" <<  xx << ", " << yy << ") - 1" << std::endl;//1
                    
                    if (0 < isValidMove(std::pair(SpritePieces[0][n].Pos.x, SpritePieces[0][n].Pos.y), std::pair(xx, yy)))
                    {
                       
                        newPos = sf::Vector2f(x * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, y * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                        SpritePieces[0][n].Piece.setPosition(newPos);  
                        if (WorB)
                        {
                            Moves.push_back(MoveWB(MoveFrTo(SpritePieces[0][n].Pos,sf::Vector2i(xx,yy)), MoveFrTo(sf::Vector2i(0,0), sf::Vector2i(0,0))));
                            SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);
                            WorB = 0;
                        }
                        else
                        {
                            WorB = 1;
                            Moves[Moves.size() - 1].Black.from = SpritePieces[0][n].Pos;
                            Moves[Moves.size() - 1].Black.to = sf::Vector2i(xx,yy);
                            SpritePieces[0][n].Pos = sf::Vector2i(xx, yy);
                             
                        }
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
                //std::cout << "(" << SpritePieces[0][i].Pos.x << ";" << SpritePieces[0][i].Pos.x << ") >> (" << (SpritePieces[0][i].Pos.y) << ";" << (Board.YMax - 1 - SpritePieces[0][i].Pos.x) << ")\n";
                break;
            case 1:
                SpritePieces[0][i].Piece.setPosition((SpritePieces[0][i].Pos.x) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinW / 2 - Board.XMax / 2 * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale, (SpritePieces[0][i].Pos.y) * RenderMenu::CGlobalSettings.chess.cellSize * RenderMenu::CGlobalSettings.chess.scale + RenderMenu::CGlobalSettings.video.WinH / 10);
                break;
            }
        }
    }
    int isValidMove(std::pair<int, int> from, std::pair<int, int> to)
    {
        __int8 piece = Board.board[from.first][from.second];
        __int8 piece2 = Board.board[to.first][to.second];
        cout << ChessPieceStr(piece) << " (" << from.first << ", " << from.second << ")\n";
        cout << ChessPieceStr(piece2) << " (" << to.first << ", " << to.second << ")\n";
        switch (piece)
        {
        case WPawn:
            if(from.first == 1)
            {
                if (to.first- from.first>0&& to.first - from.first<=2)
                {
                    return true;
                }
            }
            break;
        default:
            break;
        }
     

        return false; 
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

