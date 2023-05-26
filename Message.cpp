#include "Message.h"

//Создание сообщения с заданными параметрами
Message::Message(const std::string& from, const std::string& to, const std::string& text) : _from(from), _to(to), _text(text)
{
}

//Возврат логина отправителя сообщения
const std::string Message::getFrom() const
{
    return _from;
}

//Возврат логина получателя сообщения
const std::string Message::getTo() const
{
    return _to;
}

//Возврат текста сообщения
const std::string Message::getText() const
{
    return _text;
}
