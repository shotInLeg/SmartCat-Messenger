#include "vkapi.h"

using namespace QtJson;
using namespace vkAPI;

Message::Message()
{
    User a;
    user_from = a;
    message_id = "null";
    message_text = "null";
    message_attachment = "null";
}
Message::Message(const Message& a)
{
    user_from = a.user_from;

    message_id = a.message_id;
    message_text = a.message_text;
    message_attachment = a.message_attachment;
}
Message::Message(const User& a)
{
    user_from = a;
}


// Getters //
User& Message::from()
{
    return user_from;
}
QString Message::id() const
{
    return message_id;
}
QString Message::text() const
{
    return message_text;
}
QString Message::attachment() const
{
    return message_attachment;
}

// Setters //
Message& Message::setFrom(const User& a)
{
    user_from = a;
    return *this;
}
Message& Message::setId(QString id)
{
    message_id = id;
    return *this;
}
Message& Message::setText(QString text)
{
    message_text = text;
    return *this;
}
Message& Message::setAttachment(QString attachment)
{
    message_attachment = attachment;
    return *this;
}
