#pragma once
#include <SFML/Network.hpp>
#include "RenderMenu.h"
#include <iostream>
#include <string>

class NetServer
{
    sf::TcpListener listener;
    sf::TcpSocket socket;

public:
    NetServer()
    {
        socket.setBlocking(false);
        listener.listen(RenderMenu::CGlobalSettings.network.port);
    }

    bool Connector()
    {
        std::cout << "Ожидание... " << std::endl;

        if (listener.accept(socket) == sf::Socket::Done)
        {
            std::cout << "Кто-то подключился: " << socket.getRemoteAddress() << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string Receiver()
    {
        std::string message;
        //listener.accept(socket);
            // Сокет готов к чтению
            char buffer[2048];
            std::size_t received;

            // Читаем данные из сокета
            sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);
            if (status == sf::Socket::Done)
            {
                // Данные получены успешно
                std::cout << "Получены данные: " << buffer << std::endl;
                message = buffer;
            }
            else if (status == sf::Socket::Disconnected)
            {
                // Соединение разорвано сервером
                std::cout << "Соединение разорвано сервером" << std::endl;
                message = "-1";
            }
            else
            {
                // Произошла ошибка
                std::cout << "Ошибка чтения данных: " << status << std::endl;
                message = "-";
            }
        

        return message;
    }

    void SendMessenge(const std::string& messenge)
    {
        socket.send(messenge.c_str(), messenge.size() + 1);
    }
};
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

//class NetServer {
//private:
//    sf::TcpListener listener;
//    std::vector<sf::TcpSocket*> clients;
//public:
//    NetServer() {
//        listener.listen(sf::Socket::AnyPort);
//        listener.setBlocking(false);
//    }
//
//    bool acceptNewClient() {
//        sf::TcpSocket* client = new sf::TcpSocket();
//        if (listener.accept(*client) == sf::Socket::Done) {
//            std::cout << "New client connected: " << client->getRemoteAddress() << std::endl;
//            client->setBlocking(false);
//            clients.push_back(client);
//            return true;
//        }
//        else {
//            delete client;
//            return false;
//        }
//    }
//
//    void sendToAll(const std::string& message) {
//        std::vector<sf::TcpSocket*>::iterator it;
//        for (it = clients.begin(); it != clients.end();) {
//            if ((*it)->send(message.c_str(), message.size() + 1) == sf::Socket::Done) {
//                ++it;
//            }
//            else {
//                std::cout << "Client disconnected: " << (*it)->getRemoteAddress() << std::endl;
//                delete (*it);
//                it = clients.erase(it);
//            }
//        }
//    }
//
//    std::vector<sf::TcpSocket*>& getClients() {
//        return clients;
//    }
//};