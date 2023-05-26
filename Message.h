#pragma once
#include <string>

class Message
{
    const std::string _from;
    const std::string _to;
    const std::string _text;

public:
    Message(const std::string& from, const std::string& to, const std::string& text);
    const std::string getFrom() const;
    const std::string getTo() const;
    const std::string getText() const;

    ~Message() = default;
};


