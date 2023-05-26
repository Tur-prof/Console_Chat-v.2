#pragma once
#include <map>
#include <vector>
#include "Message.h"
#include "User.h"

class Chat {

public:
    Chat() = default;
    void start();
    bool chatOn() const;
    void loginOn();
    bool checkLogin() const;
    void showLoginMenu();
    void showUserMenu();

    bool login();
    void registrUser();
    void showMenuChatPrivate();
    void showMenuChatPublic();
    void showUsersList();
    void addMessage(Message&& message);

    ~Chat() = default;

private:
    bool _chatOn = false;
    bool _checkLogin = false;
    std::string _user_online;
   
    std::vector<User> _users;
    std::vector<Message> _messages;
    std::map<std::string, bool> _active_user;  
};