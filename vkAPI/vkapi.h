#ifndef VKAPI_H
#define VKAPI_H


#include <QString>
#include <QWebView>

#include <QUrl>
#include <QUrlQuery>

#include <QMap>
#include <QList>
#include <QPair>

#include <QFile>
#include <QDataStream>
#include <QVariantMap>

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QEventLoop>
#include <QTimer>

#include <QThread>

#include "Json/json.h"

namespace vkAPI
{


    class User
    {
        protected:
            QString user_id;
            QString user_first_name;
            QString user_last_name;
            QString user_sex;
            QString user_avatar_50;
            QString user_avatar_100;
            QString user_avatar_MAX;
            QString user_relationship;
            QString user_born;
            QString user_city;
            QString user_county;
            QString user_home_town;
            QString user_online;
            QString user_school_id;
            QString user_school_country;
            QString user_school_city;
            QString user_school_year_from;
            QString user_school_year_to;
            QString user_school_year_graduated;
            QString user_school_class_letter;
            QString user_university;
            QString user_university_name;
            QString user_university_faculty;
            QString user_university_faculty_name;
            QString user_university_graduation;
            QString user_status;
            QString user_last_seen_time;
            QString user_last_seen_platform;
            QString user_followers_count;
            QString user_common_count;
            QString user_count_albums;
            QString user_count_videos;
            QString user_count_audios;
            QString user_count_photos;
            QString user_count_friends;
            QString user_count_groups;
            QString user_exports;

        public:
            User();
            User(const User&);
            User(QString);

            QString id() const;
            QString firstName() const;
            QString lastName() const;
            QString sex() const;
            QString avatar50px() const;
            QString avatar100px() const;
            QString avatarMAXpx() const;
            QString lastSeen() const;
            QString relationship() const;
            QString born() const;
            QString city() const;
            QString country() const;
            QString homeTown() const;
            QString online() const;
            //School
            //University
            QString status() const;//
            QString followersCount() const;//
            QString commonCount() const;//

            User& setId(QString);
            User& setFirstName(QString);
            User& setLastName(QString);
            User& setSex(QString);
            User& setAvatar50px(QString);
            User& setAvatar100px(QString);
            User& setAvatarMAXpx(QString);
            User& setLastSeen(QString last_seen_time, QString last_seen_platform);
            User& setRelationship(QString);
            User& setBorn(QString);
            User& setCity(QString);
            User& setCountry(QString);
            User& setHomeTown(QString);
            User& setOnline(QString);
            User& setSchool(QString id, QString country, QString city, QString year_from, QString year_to, QString year_graduated, QString class_letter);
            User& setUniversity(QString university, QString university_name, QString university_faculty, QString university_faculty_name, QString university_graduation);
            User& setStatus(QString);
            User& setFollowersCount(QString);
            User& setCommonCount(QString);//

            bool operator==(User &user2); // Сравнение id пользователей на равенство
            bool operator!=(User &user2); // Сравнение id пользователей на неравенство
    };

    class Dialog
    {
        protected:
            QString dialog_id;
            QString dialog_title;
            QString dialog_body;
            QString dialog_state;
            QString dialog_date;
            QString dialog_avatar;
            QList<QString> dialog_members;

        public:
            Dialog();
            Dialog(const Dialog&);
            Dialog(const User&);

            QString id() const;
            QString title() const;
            QString body() const;
            QString state() const;
            QString date() const;
            QString avatar() const;
            QList<QString> members() const;

            Dialog& setId(QString);
            Dialog& setTitle(QString);
            Dialog& setBody(QString);
            Dialog& setState(QString);
            Dialog& setDate(QString);
            Dialog& setAvatar(QString);
            Dialog& setMembers(QList<QString>);
    };

    class Photo
    {
    protected:
        QString album_id;
        QString photo_75;
        QString photo_130;
        QString photo_1280;
        QString photo_width;
        QString photo_height;
        QString photo_date;

    public:
        Photo();
        Photo(const Photo&);

        QString albumID() const;
        QString photo75() const;
        QString photo130() const;
        QString photo1280() const;
        QString photoWidth() const;
        QString photoHeight() const;
        QString photoDate() const;

        Photo& setAlbumID(QString id);
        Photo& setPhoto75(QString url);
        Photo& setPhoto130(QString url);
        Photo& setPhoto1280(QString url);
        Photo& setPhotoWidth(QString width);
        Photo& setPhotoHeight(QString height);
        Photo& setPhotoDate(QString date);
    };

    class Attachment : public Photo
    {
    protected:
        QString attachment_id;
        QString attachment_type;
        QString owner_id;

    public:
        Attachment();
        Attachment(const Attachment&);

        QString id() const;
        QString type() const;
        QString ownerID() const;



        Attachment& setID(QString id);
        Attachment& setType(QString type);
        Attachment& setOwnerID(QString owner_id);
    };



    class Message
    {
    protected:
        User user_from;
        QString message_id;
        QString message_text;
        QList< QPair<QString, Attachment> > message_attachments;
        QString message_date;
        QString message_state;
    public:

            Message();
            Message(const Message&);
            Message(const User&);

            User& from();
            QString id() const;
            QString text() const;
            QList< QPair<QString, Attachment> > attachment() const;
            QString date() const;
            QString state() const;

            Message& setFrom(const User&);
            Message& setId(QString);
            Message& setText(QString);
            Message& setAttachment( QList< QPair<QString, Attachment> > );
            Message& setDate(QString);
            Message& setState(QString);
    };

    class VKontakte
    {
        protected:
            QString access_token;
            vkAPI::User current_user;

        public:
            QMap<QString, User> users;
            QMap<int, Dialog> chats;
            QMap<int, Message> history;

        protected:
            int loadData(QString fileName = "config.txt");
            int saveData(QString fileName = "config.txt");

        public:
            QString accessToken();
            vkAPI::User& currentUser();

            void setAccessToken(QString);
            void setCurrentUser(vkAPI::User&);

            static QByteArray GET(QUrl); // Отправка Get запросов //

            // Методы API //

            int autenthication(QString appID, QString scope, QWebView*); // Запуск авторизации в указанном QWebView //
            int getAccessToken(QUrl); // Получение AccessToken из авторизации //
            bool checkAccessToken(); // Проверка валидности AccessToken //
            User& getUsers(QString ids_users = "null");
          //int loadFriendsList(); // Закгрузка списка друзей //
            int loadDialogsList(); // Загрузка списка диалогов //
            int loadHistory(QString idDialog); // Загрузка истории переписки указанного диалога //
            int sendMessage(QString idDialog, QString textMessage); // Отпрака сообщения //
    };



    /*class LongPoll: public QThread
    {
        Q_OBJECT

        QString long_poll_key;
        QString long_poll_server;
        QString long_poll_ts;
        QString long_poll_pts;
        QString long_poll_mode;

    public:
            int getInfoLongPoll(const QString ssl, const QString needPts); // Получения данных для Long Poll //
            int longPoll(); // Отправка Long Poll запроса //
            void run();

    signals:
            void finishLongPoll();

    };*/


}
#endif // VKAPI_H
