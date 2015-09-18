#include "vkapi.h"

using namespace QtJson;
using namespace vkAPI;

Attachment::Attachment()
{
    attachment_id = "null";
    attachment_type = "null";
    owner_id = "null";
}
Attachment::Attachment(const Attachment &a):Photo(a)
{
    attachment_id = a.attachment_id;
    attachment_type = a.attachment_type;
    owner_id = a.owner_id;
}

QString Attachment::id() const
{
    return attachment_id;
}
QString Attachment::type() const
{
    return attachment_type;
}
QString Attachment::ownerID() const
{
    return owner_id;
}


Attachment &Attachment::setID(QString id)
{
    attachment_id = id;
    return *this;
}
Attachment &Attachment::setType(QString type)
{
    attachment_type = type;
    return *this;
}
Attachment &Attachment::setOwnerID(QString id)
{
    owner_id = id;
    return *this;
}



Photo::Photo()
{
    album_id = "null";
    photo_75 = "null";
    photo_130 = "null";
    photo_1280 = "null";
    photo_width ="null";
    photo_height = "null";
    photo_date = "null";
}
Photo::Photo(const Photo &a)
{
    album_id = a.album_id;
    photo_75 = a.photo_75;
    photo_130 = a.photo_130;
    photo_1280 = a.photo_1280;
    photo_width = a.photo_width;
    photo_height = a.photo_height;
    photo_date = a.photo_date;
}

QString Photo::albumID() const
{
    return album_id;
}
QString Photo::photo75() const
{
    return photo_75;
}
QString Photo::photo130() const
{
    return photo_130;
}
QString Photo::photo1280() const
{
    return photo_1280;
}
QString Photo::photoWidth() const
{
    return photo_width;
}
QString Photo::photoHeight() const
{
    return photo_height;
}
QString Photo::photoDate() const
{
    return photo_date;
}

Photo& Photo::setAlbumID(QString id)
{
    album_id = id;
    return *this;
}
Photo& Photo::setPhoto75(QString url)
{
    photo_75 = url;
    return *this;
}
Photo& Photo::setPhoto130(QString url)
{
    photo_130 = url;
    return *this;
}
Photo& Photo::setPhoto1280(QString url)
{
    photo_1280 = url;
    return *this;
}
Photo& Photo::setPhotoWidth(QString width)
{
    photo_width = width;
    return *this;
}
Photo& Photo::setPhotoHeight(QString height)
{
    photo_height = height;
    return *this;
}
Photo& Photo::setPhotoDate(QString date)
{
    photo_date = date;
    return *this;
}

