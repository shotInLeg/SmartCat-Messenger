#include "vkapi.h"

using namespace QtJson;
using namespace vkAPI;

Dialog::Dialog()
{
    dialog_id = "null";
    dialog_title = "null";
    dialog_body = "null";
    dialog_state = "null";
    dialog_date = "null";
    dialog_avatar = "null";
    dialog_members.clear();
}
Dialog::Dialog(const Dialog& a)
{
    dialog_id = a.dialog_id;
    dialog_title = a.dialog_title;
    dialog_body = a.dialog_body;
    dialog_state = a.dialog_state;
    dialog_date = a.dialog_date;
    dialog_avatar = a.dialog_avatar;

    dialog_members.clear();
    for(int itr = 0; itr < a.dialog_members.size(); itr++)
    {
        dialog_members.push_back(a.dialog_members.at(itr));
    }
}
Dialog::Dialog(const User& a)
{
    dialog_title = a.firstName() + " " + a.lastName();
    dialog_avatar = a.avatar50px();
}

 // Getters //
QString Dialog::id() const
{
    return dialog_id;
}
QString Dialog::title() const
{
    return dialog_title;
}
QString Dialog::body() const
{
    return dialog_body;
}
QString Dialog::state() const
{
    return dialog_state;
}
QString Dialog::date() const
{
    return dialog_date;
}
QString Dialog::avatar() const
{
    return dialog_avatar;
}
QList<QString> Dialog::members() const
{
    return dialog_members;
}

// Setters //
Dialog& Dialog::setId(QString id)
{
    dialog_id = id;
    return *this;
}
Dialog& Dialog::setTitle(QString title)
{
    dialog_title = title;
    return *this;
}
Dialog& Dialog::setBody(QString body)
{
       dialog_body = body;
       return *this;
}
Dialog& Dialog::setState(QString state)
{
    dialog_state = state;
    return *this;
}
Dialog& Dialog::setDate(QString date)
{
    dialog_date = date;
    return *this;
}
Dialog& Dialog::setAvatar(QString avatar)
{
    dialog_avatar = avatar;
    return *this;
}
Dialog& Dialog::setMembers(QList<QString> members)
{
    dialog_members = members;
    return *this;
}
