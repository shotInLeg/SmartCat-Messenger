#ifndef VKAPI_H
#define VKAPI_H


#include <QString>
#include <QWebView>

#include <QUrl>
#include <QUrlQuery>

#include <QMap>
#include <QList>

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

    // Структуры данных //
    class User
    {
    protected:
        QString user_id;
        QString user_first_name;
        QString user_last_name;
        QString user_avatar_50;
        QString user_last_seen;
        QString user_relationship;

    public:
            User();
            User(const User&);

            QString id() const;
            QString firstName() const;
            QString lastName() const;
            QString avatar50px() const;
            QString lastSeen() const;
            QString relationship() const;

            User& setId(QString);
            User& setFirstName(QString);
            User& setLastName(QString);
            User& setAvatar50px(QString);
            User& setLastSeen(QString);
            User& setRelationship(QString);

            // Перегруженные операторы //

            bool operator==(User &user2); // Сравнение id пользователей на равенство
            bool operator!=(User &user2); // Сравнение id пользователей на неравенство
    };

    class Friend: public User
    {
        QString friend_status_string;
        QString friend_current_town;
        QString friend_born_date;
        QString friend_avatar_100;
        QString friend_avatar_full;

    public:
            Friend();
            Friend(const Friend&);
            Friend(const User&);

            QString statusString() const;
            QString currentTown() const;
            QString bornDate() const;
            QString avatar100px() const;
            QString avatarFull() const;

            Friend& setStatusString(QString);
            Friend& setCurrentTown(QString);
            Friend& setBornDate(QString);
            Friend& setAvatar100px(QString);
            Friend& setAvatarFull(QString);
    };

    class Dialog
    {
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

            // Перегрузка операторов
    };

    class Message
    {
        QString from_id;
        QString from_first_name;
        QString from_last_name;
        QString from_avatar;

        QString message_id;
        QString message_text;
        QString message_attachment;
    public:
            Message();
            Message(const Message&);
            Message(const User&);

            QString fromId() const;
            QString fromFirstName() const;
            QString fromLastName() const;
            QString fromAvatar() const;

            QString id() const;
            QString text() const;
            QString attachment() const;


            Message& setFromId(QString);
            Message& setFromfName(QString);
            Message& setFromlName(QString);
            Message& setFromAvatar(QString);

            Message& setId(QString);
            Message& setText(QString);
            Message& setAttachment(QString);
    };

    class LongPoll: public QThread
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

    };

    class VKontakte
    {
        static QString access_token;



        static User current_user;

    public:
        static QMap<QString, User> users;
        static QMap<QString, Friend> friends;
        static QMap<int, Dialog> chats;
        static QMap<int, Message> history;


            static QString accessToken();
            static User& currentUser();

            static void setAccessToken(QString);
            static void setCurrentUser(User&);

            // Методы API //

            static QByteArray GET(QUrl); // Отправка Get запросов //
            static int autenthication(QString appID, QString scope, QWebView*); // Запуск авторизации в указанном QWebView //
            static int getAccessToken(QUrl); // Получение токена из авторизации //
            static bool checkAccessToken(); // Проверка валидности токена //

            static int loadFriendsList(); // Закгрузка списка друзей //
            static int loadDialogsList(); // Загрузка списка диалогов //
            static int loadHistory(QString idDialog); // Загрузка истории переписки указанного диалога //
            static int sendMessage(QString idDialog, QString textMessage); // Отпрака сообщения //


            static int loadData(QString fileName = "config.txt");
            static int saveData(QString fileName = "config.txt");

    };



    /*class userData
    {
    public:
            userData();

            static QString access_token;
            static QMap<int, Friend> friends;
            static QMap<int, Dialog> dialogs;
            static QMap<int, Message> history;
            static QMap<QString,QString> longPollArray;

            static int loadData(QString fileName = "settings.txt");
            static int saveData(QString fileName = "settings.txt");


    };*/
}


#endif // VKAPI_H
