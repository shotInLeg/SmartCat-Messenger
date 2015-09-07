#include "vkapi.h"

using namespace QtJson;
using namespace vkAPI;

User::User()
{
    user_id = "null";
    user_first_name  = "fnull";
    user_last_name  = "lnull";
    user_avatar_50  = "null";
    user_last_seen_time  = "null";
    user_relationship  = "null";
}
User::User(const User& a)
{
    user_id = a.user_id;
    user_first_name  = a.user_first_name;
    user_last_name  = a.user_last_name;
    user_avatar_50  = a.user_avatar_50;
    user_last_seen_time  = a.user_last_seen_time;
    user_relationship  = a.user_relationship;
}
User::User(QString id_user)
{
    QUrlQuery request("https://api.vk.com/method/users.get?user_ids="+id_user);
    request.addQueryItem("fields","first_name,last_name,sex,photo_50,photo_100,photo_max_orig,blacklisted,bdate,city,country,home_town,online,education,status,last_seen,followers_count,common_count,counters,relation,exports,schools");
    QString urlString = request.toString();
    QUrl url(urlString);
    QByteArray answer = VKontakte::GET(url);

    if(answer.isEmpty())
    {
        qDebug() << "Пустой ответ в Constructor User(QString)";
    }

    QVariantList usersList = parse(answer).toMap().value("response").toList();
    QVariantMap user = usersList[0].toMap();

    user_id = user.value("uid").toString();
    user_first_name = user.value("first_name").toString();
    user_last_name = user.value("last_name").toString();
    user_sex = user.value("sex").toString();
    user_avatar_50 = user.value("photo_50").toString();
    user_avatar_100 = user.value("photo_100").toString();
    user_avatar_MAX = user.value("photo_max_orig").toString();
    user_born = user.value("bdate").toString();
    user_city = user.value("city").toString();
    user_county = user.value("country").toString();
    user_home_town = user.value("home_town").toString();
    user_online = user.value("online").toString();
    //QVariantList schools = user.value("school").toList();
        //QVariantMap school = schools[0].toMap();
            //user_school_id = school.value("id").toString();
            //user_school_country  = school.value("country").toString();
            //user_school_city = school.value("city").toString();
            //user_school_year_from = school.value("year_from").toString();
            //user_school_year_to = school.value("year_to").toString();
            //user_school_year_graduated = school.value("year_graduated").toString();
            //user_school_class_letter = school.value("class").toString();
    QVariantMap education = user.value("education").toMap();
        user_university = education.value("university").toString();
        user_university_name  = education.value("university_name").toString();
        user_university_faculty = education.value("faculty").toString();
        user_university_faculty_name = education.value("faculty_name").toString();
        user_university_graduation = education.value("graduation").toString();
     user_status = user.value("status").toString();
     QVariantMap last_seen = user.value("last_seen").toMap();
        user_last_seen_time = last_seen.value("time").toString();
        user_last_seen_platform = last_seen.value("platform").toString();
     user_followers_count = user.value("followers_count").toString();
     user_common_count = user.value("common_count").toString();
     QVariantMap counters = user.value("counters").toMap();
         user_count_albums = counters.value("albums").toString();
         user_count_videos = counters.value("videos").toString();
         user_count_audios = counters.value("audios").toString();
         user_count_photos = counters.value("photos").toString();
         user_count_friends = counters.value("friends").toString();
         user_count_groups = counters.value("groups").toString();
     user_relationship = user.value("relation").toString();
     user_exports = user.value("exports").toString();

     QUrl url_avatar(user_avatar_50);
     QByteArray photo_avatar = VKontakte::GET(url_avatar);
     QImage img = QImage::fromData(photo_avatar);
     img.save("vk_avatars/"+user_id+".jpg");
     user_avatar_50 = "vk_avatars/"+user_id+".jpg";


}

// Getters //
QString User::id() const
{
    return user_id;
}
QString User::firstName() const
{
    return user_first_name;
}
QString User::lastName() const
{
    return user_last_name;
}
QString User::sex() const
{
    return user_sex;
}
QString User::avatar50px() const
{
    return user_avatar_50;
}
QString User::avatar100px() const
{
    return user_avatar_100;
}
QString User::avatarMAXpx() const
{
    return user_avatar_MAX;
}
QString User::lastSeen() const
{
    return user_last_seen_time;
}
QString User::relationship() const
{
    return user_relationship;
}
QString User::born() const
{
    return user_born;
}
QString User::city() const
{
    return user_city;
}
QString User::country() const
{
    return user_county;
}
QString User::homeTown() const
{
    return user_home_town;
}
QString User::online() const
{
    return user_online;
}
QString User::status() const
{
    return user_status;
}
QString User::followersCount() const
{
    return user_followers_count;
}
QString User::commonCount() const
{
    return user_common_count;
}

// Setters //
User& User::setId(QString id)
{
    user_id = id;
    return *this;
}
User& User::setFirstName(QString fname)
{
    user_first_name = fname;
    return *this;
}
User& User::setLastName(QString lname)
{
    user_last_name = lname;
    return *this;
}
User& User::setSex(QString sex)
{
    user_sex = sex;
    return *this;
}
User& User::setAvatar50px(QString avatar)
{
    user_avatar_50 = avatar;
    return *this;
}
User& User::setAvatar100px(QString avatar_100)
{
    user_avatar_100 = avatar_100;
    return *this;
}
User& User::setAvatarMAXpx(QString avatar_max)
{
    user_avatar_MAX = avatar_max;
    return *this;
}
User& User::setLastSeen(QString last_seen_time, QString last_seen_platform)
{
    user_last_seen_time = last_seen_time;
    user_last_seen_platform = last_seen_platform;
    return *this;
}
User& User::setRelationship(QString relationship)
{
    user_relationship = relationship;
    return *this;
}
User& User::setBorn(QString born)
{
    user_born = born;
    return *this;
}
User& User::setCity(QString city)
{
    user_city = city;
    return *this;
}
User& User::setCountry(QString country)
{
    user_county = country;
    return *this;
}
User& User::setHomeTown(QString home_town)
{
    user_home_town = home_town;
    return *this;
}
User& User::setOnline(QString online)
{
    user_online = online;
    return *this;
}
User& User::setSchool(QString id, QString country, QString city, QString year_from, QString year_to, QString year_graduated, QString class_letter)
{
    user_school_id = id;
    user_school_country = country;
    user_school_city = city;
    user_school_year_from= year_from;
    user_school_year_to = year_to;
    user_school_year_graduated = year_graduated;
    user_school_class_letter = class_letter;
    return *this;
}
User& User::setUniversity(QString university, QString university_name, QString university_faculty, QString university_faculty_name, QString university_graduation)
{
    user_university = university;
    user_university_name = university_name;
    user_university_faculty = university_faculty;
    user_university_faculty_name = university_faculty_name;
    user_university_graduation = university_graduation;
    return *this;
}
User& User::setStatus(QString status)
{
    user_status = status;
    return *this;
}
User& User::setFollowersCount(QString followers_count)
{
    user_followers_count = followers_count;
    return *this;
}
User& User::setCommonCount(QString common_count)
{
    user_common_count = common_count;
    return *this;
}

// Operators //
bool User::operator==(User &user2)
{
    return id() == user2.id();
}
bool User::operator!=(User &user2)
{
    return this->id() != user2.id();
}
