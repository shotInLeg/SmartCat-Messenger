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
<<<<<<< HEAD
QString Message::date() const
{
    return message_date;
}
QString Message::state() const
{
    return message_state;
=======
QString Message::typeAttachment() const
{
    return message_type_attachment;
>>>>>>> origin/master
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
<<<<<<< HEAD
Message& Message::setDate(QString date)
{
    message_date = date;
    return *this;
}

Message& Message::setState(QString state)
{
    message_state = state;
=======

Message& Message::setTypeAttachment(QString type)
{
    message_type_attachment = type;
>>>>>>> origin/master
    return *this;
}
