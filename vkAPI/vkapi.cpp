/*
 * Коды ошибок
 * <0x000001> - Не действительный токен
 * <0x000002> - Пустой ответ на GET запрос
 * <0x000003> - Не найден разделитель сообщения
 * <0x000004> - Сообщение не отправлено
 * <0x000005> - Сервер не вернур токен
 * <0x000006> - Ошибка открытия файла
*/

#include "vkapi.h"

using namespace QtJson;
using namespace vkAPI;

//Статические переменные //

QString VKontakte::access_token = "null";

User VKontakte::current_user;

QMap<QString, User> VKontakte::users;
QMap<QString, Friend> VKontakte::friends;
QMap<QString, Dialog> VKontakte::chats;
QMap<int, Message> VKontakte::history;


// Выгрузка данных //
int VKontakte::loadData(QString fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::ReadOnly))
    {
        return 0x000006;
    }

    QVariantMap parametrs;
    QDataStream stream(&f);

    parametrs.insert("access_token_vk", access_token);

    stream >> parametrs;

    f.close();

    if(parametrs.contains("access_token_vk"))
    {
        access_token = parametrs.value("access_token_vk").toString();

        if(checkAccessToken == false)
        {
            return 0x000001;
            access_token = "null";
        }
    }
    if(parametrs.contains("id_vk"))
    {
        current_user.setId( parametrs.value("id_vk").toString() );
    }
    if(parametrs.contains("first_name_vk"))
    {
        current_user.setFirstName( parametrs.value("first_name_vk").toString() );
    }
    if(parametrs.contains("last_name_vk"))
    {
        current_user.setLastName( parametrs.value("last_name_vk").toString() );
    }
    if(parametrs.contains("avatar_vk"))
    {
        current_user.setAvatar50px( parametrs.value("avatar_vk").toString() );
    }

    return 0;
}

int VKontakte::saveData(QString fileName)
{
    QFile f(fileName);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return 0x000006;
    }

    QVariantMap parametrs;
    QDataStream stream(&f);

    parametrs.insert("access_token_vk", access_token);
    parametrs.insert("id_vk", current_user.id());
    parametrs.insert("first_name_vk", current_user.firstName());
    parametrs.insert("last_name_vk", current_user.lastName());
    parametrs.insert("avatar_vk", current_user.avatar50px());

    stream << parametrs;

    f.close();

    return 0;
}

QString VKontakte::accessToken()
{
    QUrlQuery getInfo("https://api.vk.com/method/account.getInfo?access_token=" + access_token);
    QString urlString = getInfo.toString();
    QUrl url(urlString);
    QByteArray answer = GET(url);

    if(!answer.contains("response"))
    {
        access_token = "null";
    }

    return access_token;
}
void VKontakte::setAccessToken(QString token)
{
    access_token = token;
}


User& VKontakte::currentUser()
{
    return current_user;
}
void VKontakte::setCurrentUser(User& a)
{
    current_user = a;
}



QByteArray VKontakte::GET(QUrl uri) // Отправка GET запросов
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkReply* reply = manager->get(QNetworkRequest(uri));
    QEventLoop wait;
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), &wait, SLOT(quit()));
    QTimer::singleShot(300000, &wait, SLOT(quit()));
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), manager, SLOT(deleteLater()));
    wait.exec();
    QByteArray answer = reply->readAll();
    reply->deleteLater();

    return answer;
}

bool VKontakte::checkAccessToken() // Проверка валидности токена //
{
    loadData();
    //Проверка токена на валидность
    QUrlQuery getInfo("https://api.vk.com/method/account.getInfo?access_token=" + access_token);
    QString urlString = getInfo.toString();
    QUrl url(urlString);
    QByteArray answer = GET(url);

    if(!answer.contains("response"))
    {
        access_token = "null";
        saveData();
        return false;
    }

    return true;
}



int VKontakte::autenthication(QString appID, QString scope, QWebView* web) /* Запрос авторизации в окне QWebView */
{
    QUrl uri = "https://oauth.vk.com/authorize?client_id=" + appID + "&scope=" + scope + " &redirectscopehttps://oauth.vk.com/blank.html&display=popup&response_type=token";
    web->load(uri);
    return 0;
}

int VKontakte::getAccessToken(QUrl url)
{
    if(!url.toString().contains("access_token"))
    {
        return 0x000005;
    }

    url = url.toString().replace("#", "?");
    access_token = QUrlQuery(url).queryItemValue("access_token");
    QString id_user = QUrlQuery(url).queryItemValue("user_id");

    current_user.setId(id_user);

    QUrlQuery request("https://api.vk.com/method/users.get?user_ids=" + id_user);
    request.addQueryItem("fields","first_name,last_name,sex,photo_50,photo_100");
    QString urlString = request.toString();
    QUrl url2(urlString);
    QByteArray answer = GET(url2);

    if(answer.isEmpty())
    {
        qDebug() << "Пустой ответ в loadFriendsList";
        return 0x000002;
    }

    QVariantList user = parse(answer).toMap().value("response").toList();

    for(int i = 0; i < user.size(); i++)
    {
        QVariantMap currentUser = user[i].toMap();

        QString fname = currentUser.value("first_name").toString();
        QString lname = currentUser.value("last_name").toString();
        QString sex = currentUser.value("sex").toString();
        QString photo50 = currentUser.value("photo_50").toString();
        QString photo100 = currentUser.value("photo_100").toString();

        for(int j = 0; j < photo50.size(); j++)
        {
            if(photo50.at(j) == '\\' )
            {
                photo50.remove(j, 1);
            }
        }
        for(int j = 0; j < photo100.size(); j++)
        {
            if(photo100.at(j) == '\\' )
            {
                photo100.remove(j, 1);
            }
        }

        current_user.setFirstName(fname).setLastName(lname).setAvatar50px(photo50);
    }


    saveData();

    return 0;
}

int VKontakte::loadFriendsList()
{
    if(checkAccessToken() == true)
    {
        QUrlQuery request("https://api.vk.com/method/friends.get?access_token=" + access_token);
        request.addQueryItem("fields","first_name,last_name,photo_50,photo_100,photo_200_orig,status,last_seen,");

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в loadFriendsList";
            return 0x000002;
        }

        //qDebug() << "ANSWER >>  " << answer << "  << ANSWER";

        QVariantList friendsList = parse(answer).toMap().value("response").toList();

        friends.clear();
        for(int i = 0; i < friendsList.size(); i++)
        {
            Friend uFriend;

            QVariantMap currentFriend = friendsList[i].toMap();
            QString idFriend = currentFriend.value("uid").toString();

            if(users[idFriend].firstName() == "" || users[idFriend].firstName() == "null")
            {
                QString fname = currentFriend.value("first_name").toString();
                QString lname = currentFriend.value("last_name").toString();
                QString photo50 = currentFriend.value("photo_50").toString();
                QString lastSeen = currentFriend.value("last_seen").toString();

                uFriend.setFirstName(fname).setLastName(lname).setId(idFriend).setAvatar50px(photo50).setLastSeen(lastSeen).setRelationship("3");
            }
            else
            {
                uFriend = users[idFriend];
            }

            QString photo100 = currentFriend.value("photo_100").toString();
            QString photoFull = currentFriend.value("photo_200_orig").toString();
            QString status = currentFriend.value("status").toString();

            uFriend.setStatusString(status).setAvatar100px(photo100).setAvatarFull(photoFull);

            friends[idFriend] = uFriend;
        }
    }
    else
    {
        return 0x000001;
    }

    return 0;
}
int VKontakte::loadDialogsList()
{
    if(checkAccessToken() == true)
    {
        QString dialogIds = "1";

        // Запрос на получение диалогов //

        QUrlQuery request("https://api.vk.com/method/messages.getDialogs?access_token=" + access_token);
        request.addQueryItem("offset","0");
        request.addQueryItem("count","30");
        request.addQueryItem("preview_length","25");


        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в loadFriendsList";
            return 0x000002;
        }

        //qDebug() << "ANSWER >>  " << answer;

        // Извлечение из ответа //
        QVariantList dialogsList = parse(answer).toMap().value("response").toList();

        chats.clear();

        for(int i = 0; i < dialogsList.size(); i++)
        {
            QVariantMap currentDialog = dialogsList[i].toMap();

            QString key = QString::number(i);
            QString date = currentDialog.value("date").toString();
            QString id = currentDialog.value("uid").toString();
            QString state = currentDialog.value("read_state").toString();
            QString title = currentDialog.value("title").toString();
            QString body = currentDialog.value("body").toString();
            dialogIds += "," + id;

            Dialog dialog;
            dialog.setDate(date).setId(id).setState(state).setTitle(title).setBody(body);

            chats[key] = dialog;

        }

        // Запрос на получение данных о пользователе //

        QUrlQuery request2("https://api.vk.com/method/users.get?user_ids=" + dialogIds);
        request2.addQueryItem("fields","photo_50,last_seen,friend_status");
        urlString = request2.toString();
        QUrl url2(urlString);
        answer = GET(url2);

        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в loadFriendsList";
            return 0x000002;
        }

       //qDebug() << answer << " <!\n";

        // Извлечение данных пользователя в Map //
        users.clear();
        QVariantList user = parse(answer).toMap().value("response").toList();

        for(int i = 0; i < user.size(); i++)
        {
            QVariantMap currentUser = user[i].toMap();

            QString id = currentUser.value("uid").toString();
            QString fname = currentUser.value("first_name").toString();
            QString lname = currentUser.value("last_name").toString();
            QString lastSeen = currentUser.value("last_seen").toString();
            QString photo50 = currentUser.value("photo_50").toString();
            QString relationship = currentUser.value("friend_status").toString();

            for(int j = 0; j < photo50.size(); j++)
            {
                if(photo50.at(j) == '\\' )
                {
                    photo50.remove(j, 1);
                }
            }
            User user;
            user.setId(id).setFirstName(fname).setLastName(lname).setAvatar50px(photo50).setLastSeen(lastSeen).setRelationship(relationship);

            users[id] = user;
        }


        // Замена title в списке диалогов //
        QMap<QString, Dialog>::iterator itr;
        for(itr = chats.begin(); itr != chats.end(); itr++)
        {
            Dialog dialog;
            dialog = itr.value();

            if(dialog.title() == "" ||  dialog.title() == " ... " ||  dialog.title() == "...")
            {
                // Имя и Фамилия записываются в название диалога //
                dialog.setTitle(users[dialog.id()].firstName() + " " + users[dialog.id()].lastName());

                // Аватар пользователя записывается как фото диалога //
                QUrl url_avatar(users[dialog.id()].avatar50px());
                QByteArray photo_avatar = GET(url_avatar);
                QImage img = QImage::fromData(photo_avatar);
                img.save("D:\\\\vk_avatars\\"+dialog.id()+".jpg");
                dialog.setAvatar("D:\\\\vk_avatars\\"+dialog.id()+".jpg");
            }
            itr.value() = dialog;
        }

    }
    else
    {
        return 0x000001;
    }

    return 0;
}


int VKontakte::loadHistory(QString idUser) // Загрузка истории переписки //
{
    if(checkAccessToken() == true)
    {
        QUrlQuery request("https://api.vk.com/method/messages.getHistory?access_token=" + access_token);
        request.addQueryItem("user_id", idUser);

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);


        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в loadHistory";
            return 0x000002;
        }

        QVariantList messageList = parse(answer).toMap().value("response").toList();
        history.clear();

        for(int i = 0; i < messageList.size(); i++)
        {
            QVariantMap currentMessage = messageList[i].toMap();

            QString texMsg = currentMessage.value("body").toString();
            QString from = currentMessage.value("from_id").toString();
            QString firstName = "null";
            QString lastName = "null";
            QString avatar = "null";

            if(from == current_user.id())
            {
                firstName = current_user.firstName();
                lastName = current_user.lastName();
                avatar = current_user.avatar50px();
            }
            if(from == users[from].id())
            {
                firstName = users[from].firstName();
                lastName = users[from].lastName();
                avatar = users[from].avatar50px();
            }

            Message tmp;
            tmp.setFromId(from).setFromfName(firstName).setFromlName(lastName).setText(texMsg);

            history[i] = tmp;
        }
    }
    else
    {
        return 0x000001;
    }

    return 0;
}

int VKontakte::sendMessage(QString idDialog, QString textMessage) // Отправка сообщения указанному пользователю //
{
    if(checkAccessToken() == true)
    {

        QUrlQuery request("https://api.vk.com/method/messages.send?access_token=" + access_token);
        request.addQueryItem("user_id", idDialog);
        request.addQueryItem("message", textMessage);

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Сообщение не отправлено";
            return 0x000004;
        }

        if(answer.contains("response"))
        {
            qDebug() << "Сообщение успешно отправлено";
        }
    }
    else
    {
        return 0x000001;
    }

    return 0;
}




// LongPoll //
int LongPoll::getInfoLongPoll(const QString ssl, const QString needPts)
{
        QUrlQuery request("https://api.vk.com/method/messages.getLongPollServer?access_token=" + VKontakte::accessToken() );

        request.addQueryItem("use_ssl", "0");
        request.addQueryItem("need_pts", "0");

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = VKontakte::GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Ошибка получения информации LongPoll";
            return 0x000002;
        }

        qDebug() << answer;

        QVariantMap answerPoll = parse(answer).toMap();
        QVariantMap response = answerPoll.value("response").toMap();

        long_poll_key = response.value("key").toString();
        long_poll_server = response.value("server").toString();
        long_poll_ts = response.value("ts").toString();
        long_poll_pts = response.value("pts").toString();
        long_poll_mode = "32";

        //qDebug() << long_poll_key;
        //qDebug() << long_poll_server;
        //qDebug() << long_poll_ts;
        //qDebug() << long_poll_pts;

    return 0;

}


int LongPoll::longPoll()
{

        QUrlQuery request("http://" + long_poll_server + "?act=a_check&key=" + long_poll_key + "&ts=" + long_poll_ts + "&wait=15&mode=" + long_poll_pts);

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = VKontakte::GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Нет событий";
            return 0x000002;
        }

        qDebug() << answer;

        QVariantList longPollAnswer = parse(answer).toMap().value("response").toList();

        for(int i = 0; i < longPollAnswer.size(); i++)
        {
            QVariantMap currentMember = longPollAnswer[i].toMap();

            long_poll_ts = currentMember.value("ts").toString();
        }

    return 0;
}

void LongPoll::run()
{
    getInfoLongPoll("0", "1");

    //longPoll();

    //for(int i = 0; i != -1; i++)
        //qDebug() << i <<"From Thread";
    emit finishLongPoll();

}



//Класс User //
User::User()
{
    user_id = "null";
    user_first_name  = "null";
    user_last_name  = "null";
    user_avatar_50  = "null";
    user_last_seen  = "null";
    user_relationship  = "null";
}
User::User(const User& a)
{
    user_id = a.user_id;
    user_first_name  = a.user_first_name;
    user_last_name  = a.user_last_name;
    user_avatar_50  = a.user_avatar_50;
    user_last_seen  = a.user_last_seen;
    user_relationship  = a.user_relationship;
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
QString User::avatar50px() const
{
    return user_avatar_50;
}
QString User::lastSeen() const
{
    return user_last_seen;
}
QString User::relationship() const
{
    return user_relationship;
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
User& User::setAvatar50px(QString avatar)
{
    user_avatar_50 = avatar;
    return *this;
}
User& User::setLastSeen(QString lastSeen)
{
    user_last_seen = lastSeen;
    return *this;
}
User& User::setRelationship(QString relationship)
{
    user_relationship = relationship;
    return *this;
}

// Operators //

bool User::operator==(User &user2)
{
    return id() == user2.id();
}
bool User::operator!=(User &user2)
{
    if( this->id() != user2.id() )
    {
        return true;
    }

    return false;
}



// Class Friend //
Friend::Friend():User()
{
    friend_status_string = "null";
    friend_current_town = "null";
    friend_born_date = "null";
    friend_avatar_100 = "null";
    friend_avatar_full = "null";
}
Friend::Friend(const Friend& a):User(a)
{
    friend_status_string = a.friend_status_string;
    friend_current_town = a.friend_current_town;
    friend_born_date = a.friend_born_date;
    friend_avatar_100 = a.friend_avatar_100;
    friend_avatar_full = a.friend_avatar_full;
}
Friend::Friend(const User& a)
{
    user_id = a.id();
    user_first_name  = a.firstName();
    user_last_name  = a.lastName();
    user_avatar_50  = a.avatar50px();
    user_last_seen  = a.lastSeen();
    user_relationship  = a.relationship();
}

// Getters //
QString Friend::statusString() const
{
    return friend_status_string;
}
QString Friend::currentTown() const
{
    return friend_current_town;
}
QString Friend::bornDate() const
{
    return friend_born_date;
}
QString Friend::avatar100px() const
{
    return friend_avatar_100;
}
QString Friend::avatarFull() const
{
    return friend_avatar_full;
}

// Setters //
Friend& Friend::setStatusString(QString status)
{
    friend_status_string = status;
    return *this;
}
Friend& Friend::setCurrentTown(QString currentTown)
{
   friend_current_town = currentTown;
   return *this;
}
Friend& Friend::setBornDate(QString bornDate)
{
    friend_born_date = bornDate;
    return *this;
}
Friend& Friend::setAvatar100px(QString avatar)
{
    friend_avatar_100 = avatar;
    return *this;
}
Friend& Friend::setAvatarFull(QString avatar)
{
    friend_avatar_full = avatar;
    return *this;
}


// Class Dialog //
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


// Class Message //
Message::Message()
{
    from_id = "null";
    from_first_name = "null";
    from_last_name = "null";
    from_avatar = "null";

    message_id = "null";
    message_text = "null";
    message_attachment = "null";
}
Message::Message(const Message& a)
{
    from_id = a.from_id;
    from_first_name = a.from_first_name;
    from_last_name = a.from_last_name;
    from_avatar = a.from_avatar;

    message_id = a.message_id;
    message_text = a.message_text;
    message_attachment = a.message_attachment;
}
Message::Message(const User& a)
{
    from_id = a.id();
    from_first_name = a.firstName();
    from_last_name = a.lastName();
    from_avatar = a.avatar50px();
}


// Getters //
QString Message::fromId() const
{
    return from_id;
}
QString Message::fromFirstName() const
{
    return from_first_name;
}
QString Message::fromLastName() const
{
    return from_last_name;
}
QString Message::fromAvatar() const
{
    return from_avatar;
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
Message& Message::setFromId(QString id)
{
    from_id = id;
    return *this;
}
Message& Message::setFromfName(QString fname)
{
    from_first_name = fname;
    return *this;
}
Message& Message::setFromlName(QString lname)
{
    from_last_name = lname;
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






