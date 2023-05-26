#include <iostream>
#include "Chat.h"
#include "BadLoginRegistr.h"
#include "BadLoginMessage.h"


//Функция установки включения программы
void Chat::start() {
    _chatOn = true;
}

//Функция возврата включенного состояния программы
bool Chat::chatOn() const
{
    return _chatOn;
}

//Функция установки авторизации пользователя
void Chat::loginOn()
{
    _checkLogin = true;
}

//Функция возврата режима авторизованного пользователя
bool Chat::checkLogin() const
{
    return _checkLogin;
}

//Функция вывода главного меню
void Chat::showLoginMenu()
{
    char operation;

    while (_chatOn && !_checkLogin)
    {
        std::cout << "(1)Login" << std::endl;
        std::cout << "(2)Regisration" << std::endl;
        std::cout << "(0)Exit" << std::endl;
        std::cout << ">> " << std::endl;
        std::cin >> operation;

        switch (operation)
        {
        case '1':
            if (login())
            {
                _checkLogin = false;
            }
            break;
        case '2':
            registrUser();
            break;
        case '0':
            _chatOn = false;
            break;
        default:
            std::cout << "Choose 1 or 2..." << std::endl;
            break;
        }
    }
}

//Функция авторизации пользователя
bool Chat::login()
{
    std::string login;
    std::string password;
    bool is_found = false;
    char operation;

    while (!is_found)
    {
        std::cout << "login: ";
        std::cin >> login;
        std::cout << "password: ";
        std::cin >> password;

        for (const User& u : _users) {
            if (u.getUserLogin() == login &&
                u.getUserPassword() == password) {
                std::cout << "LOGIN SUCCESS" << std::endl;
                _user_online = login;
                _active_user.at(login) = true;

                loginOn();
                return is_found;
            }
        }

        if (!is_found) {
            std::cout << "LOGIN OR PASSWORD FAILED" << std::endl;
            std::cout << "Press (0) for exit or press any button to try again" << std::endl;
            std::cin >> operation;
            if (operation == '0') {
                break;
            }
        }
    }
    return is_found;
}

//Функция регистрации пользователя
void Chat::registrUser()
{
    std::string login;
    std::string password;

    std::cout << "login: ";
    std::cin >> login;

    if (_users.empty())
    {
        try
        {
            if (login == "All")
            {
                throw BadLoginRegistr();
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }
    }
    else
    {
        try
        {
            for (const auto& u : _users)
            {
                if (u.getUserLogin() == login)
                {
                    throw BadLoginRegistr();
                }
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return;
        }
    }

    std::cout << "password: ";
    std::cin >> password;   

    User user = User(login, password);

    _users.push_back(user);
    _active_user [login] = false;

}

//Функция вывода меню пользователя
void Chat::showUserMenu()
{
    char operation;
    std::cout << "Hi, " << _user_online << std::endl;

    while (_checkLogin) {
        std::cout << "Menu: (1)Chat Public | (2)Chat Private | (3)Users | (0)Logout";

        std::cout << std::endl
            << ">> ";
        std::cin >> operation;

        switch (operation)
        {
        case '1':
            showMenuChatPublic();
            break;
        case '2':
            showMenuChatPrivate();
            break;
        case '3':
            showUsersList();
            break;
        case '0':
            _active_user.at(_user_online) = false;
            _checkLogin = false;
            break;
        default:
            std::cout << "Choose 1 or 2 or 3..." << std::endl;
            break;
        }
    }
    std::cout << "--------------" << std::endl;
}

//Функция вывода меню публичного чата
void Chat::showMenuChatPublic()
{
    bool chat_public_on = true;
    std::string text;
    char operation;

    std::cout << "--- Chat Public ---" << std::endl;
    while (chat_public_on) {
        std::cout << "Menu:  (1) ShowChat |  (2) Add Message |  (0) Back"
            << std::endl
            << ">> ";
        std::cin >> operation;

        switch (operation)
        {
        case '1':
            for (const auto& m : _messages) {
                if (m.getTo() == "All") {
                    std::cout << "From " << m.getFrom() << " To " << m.getTo() << " : " << m.getText();
                    std::cout << std::endl;
                }
            }
            break;
        case '2':
            std::cout << "Text: ";
            std::cin.ignore();
            std::getline(std::cin, text);
            _messages.push_back({ _user_online, "All", text });
            break;
        case '0':
            chat_public_on = false;
            break;
        default:
            std::cout << "Choose 1 or 2..." << std::endl;
            break;
        }
    }
    std::cout << "--------------" << std::endl;
}

//Функция вывода меню приватного чата
void Chat::showMenuChatPrivate()
{
    bool chat_private_on = true;
    std::string to;
    std::string text;
    char operation;

    while (chat_private_on) {
        std::cout << "--- Chat Private ---" << std::endl;
        std::cout << "Menu: (1)ShowChat | (2)Add Message | (0)Back"
            << std::endl
            << ">> ";
        std::cin >> operation;
        int _found = 0;

        switch (operation)
        {
        case '1':
            for (const auto& m : _messages) {
                if (m.getTo() == _user_online || m.getFrom() == _user_online) {
                    std::cout << "From " << m.getFrom() << " To " << m.getTo() << " : " << m.getText();
                    std::cout << std::endl;
                }
            }
            break;
        case '2':
            std::cout << "To: ";
            std::cin >> to;
            try
            {
                for (const auto& u : _users)
                {
                    if (u.getUserLogin() == to)
                    {
                        _found = 1;
                    }
                }
                if (_found == 0) {
                    throw BadLoginMessage();
                }
                else {
                    std::cout << "Text: ";
                    std::cin.ignore();
                    std::getline(std::cin, text);
                    _messages.push_back({ _user_online, to, text });
                    break;
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << e.what() << std::endl;
                break;
            }
            break;
        case '0':
            chat_private_on = false;
            break;
        default:
            std::cout << "Choose 1 or 2..." << std::endl;
            break;
        }
    }
    std::cout << "--------------" << std::endl;
}

//Функция вывода списка пользователей
void Chat::showUsersList()
{
    std::cout << "--- Users ---" << std::endl;
    for (const auto& u : _active_user)
    {
        if (u.first == _user_online) {
            std::cout << u.first << " online" << " (you)" << std::endl;
        }
        else if (u.second == true) {
            std::cout << u.first << " online" << std::endl;
        }
        else {
            std::cout << u.first << " offline" << std::endl;
        }
    }
    std::cout << "--------------" << std::endl;
}

//Функция добавления сообщения в вектор сообщений
void Chat::addMessage(Message&& message) {
    _messages.emplace_back(message);
}