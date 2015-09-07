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


//QMap<QString, User> VKontakte::users;
//QMap<int, Dialog> VKontakte::chats;
//QMap<int, Message> VKontakte::history;

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
        current_user = getUsers();
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
        qDebug() << "Пустой ответ в VKontakte::getAccessToken";
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

        QUrl url_avatar(photo50);
        QByteArray photo_avatar = GET(url_avatar);
        QImage img = QImage::fromData(photo_avatar);
        img.save("vk_avatars/"+id_user+".jpg");
        photo50 = "vk_avatars/"+id_user+".jpg";

        current_user.setFirstName(fname).setLastName(lname).setAvatar50px(photo50);
    }
    saveData();

    return 0;
}



/*
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
*/

User& VKontakte::getUsers(QString ids_users)
{
    QUrlQuery request("https://api.vk.com/method/users.get?access_token="+access_token);
    if( ids_users != "null")
    {
        request.addQueryItem("user_ids", ids_users);
    }
    request.addQueryItem("fields","first_name,last_name,sex,photo_50,photo_100,photo_max_orig,blacklisted,bdate,city,country,home_town,online,education,status,last_seen,followers_count,common_count,counters,relation,exports,schools");
    QString urlString = request.toString();
    QUrl url(urlString);
    QByteArray answer = GET(url);

    if(answer.isEmpty())
    {
        qDebug() << "Пустой ответ в VKontakte::getUsers";
    }

    QVariantList usersList = parse(answer).toMap().value("response").toList();
    User cache;
    for(int i = 0; i < usersList.size(); i++)
    {
        QVariantMap user = usersList[i].toMap();
        QString id = user.value("uid").toString();
        QString fname = user.value("first_name").toString();
        QString lname = user.value("last_name").toString();
        QString sex = user.value("sex").toString();
        QString photo50 = user.value("photo_50").toString();
        QString photo100 = user.value("photo_100").toString();
        QString photoMAX = user.value("photo_max_orig").toString();
        QString born = user.value("bdate").toString();
        QString city = user.value("city").toString();
        QString country = user.value("country").toString();
        QString home_town = user.value("home_town").toString();
        QString online = user.value("online").toString();
        //QVariantList schools = user.value("school").toList();
            //QVariantMap school = schools[1].toMap();
                //QString id_school = school.value("id").toString();
                //QString country_school  = school.value("country").toString();
                //QString city_school = school.value("city").toString();
                //QString year_from = school.value("year_from").toString();
                //QString year_to = school.value("year_to").toString();
                //QString year_graduated = school.value("year_graduated").toString();
                //QString class_letter = school.value("class").toString();
        QVariantMap education = user.value("education").toMap();
            QString university = education.value("university").toString();
            QString university_name  = education.value("university_name").toString();
            QString faculty = education.value("faculty").toString();
            QString faculty_name = education.value("faculty_name").toString();
            QString graduation = education.value("graduation").toString();
         QString status = user.value("status").toString();
         QVariantMap last_seen = user.value("last_seen").toMap();
            QString time = last_seen.value("time").toString();
            QString platform = last_seen.value("platform").toString();
         QString followers_count = user.value("followers_count").toString();
         QString common_count = user.value("common_count").toString();
         QVariantMap counters = user.value("counters").toMap();
             QString albums = counters.value("albums").toString();
             QString videos = counters.value("videos").toString();
             QString audios = counters.value("audios").toString();
             QString photos = counters.value("photos").toString();
             QString friends = counters.value("friends").toString();
             QString groups = counters.value("groups").toString();
         QString relation = user.value("relation").toString();
         QString exports = user.value("exports").toString();

         QUrl url_avatar(photo50);
         QByteArray photo_avatar = GET(url_avatar);
         QImage img = QImage::fromData(photo_avatar);
         img.save("vk_avatars/"+id+".jpg");
         photo50 = "vk_avatars/"+id+".jpg";

         User new_user;
         new_user.setId(id);
         new_user.setFirstName(fname);
         new_user.setLastName(lname);
         new_user.setSex(sex);
         new_user.setAvatar50px(photo50);
         new_user.setAvatar100px(photo100);
         new_user.setAvatarMAXpx(photoMAX);
         new_user.setBorn(born);
         new_user.setCity(city);
         new_user.setCountry(country);
         new_user.setCommonCount(common_count);
         new_user.setFollowersCount(followers_count);
         new_user.setHomeTown(home_town);
         new_user.setLastSeen(time, platform);
         new_user.setOnline(online);
         new_user.setRelationship(relation);
         //new_user.setSchool(id_school, country_school, city_school, year_to, year_from, year_graduated, class_letter);
         new_user.setUniversity(university, university_name, faculty, faculty_name, graduation);
         new_user.setStatus(status);

         users[id] = new_user;
         cache = users[id];
    }

    return cache;
}

int VKontakte::loadDialogsList()
{
    if( checkAccessToken() == true )
    {
        QString dialogIds = "1";

        QUrlQuery request("https://api.vk.com/method/messages.getDialogs?access_token=" + access_token);
        request.addQueryItem("offset","0");
        request.addQueryItem("count","30");
        request.addQueryItem("preview_length","25");


        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);

        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в VKontakte::loadDialogsList";
            return 0x000002;
        }


        QVariantList dialogsList = parse(answer).toMap().value("response").toList();

        chats.clear();

        for(int i = 0; i < dialogsList.size(); i++)
        {
            QVariantMap currentDialog = dialogsList[i].toMap();

            QString date = currentDialog.value("date").toString();
            QString id = currentDialog.value("uid").toString();
            QString state = currentDialog.value("read_state").toString();
            QString title = currentDialog.value("title").toString();
            QString body = currentDialog.value("body").toString();
            dialogIds += "," + id;

            Dialog dialog;
            dialog.setDate(date).setId(id).setState(state).setTitle(title).setBody(body);

            int key = date.toInt();
            chats[key] = dialog;

        }

        // Запрос на получение данных о пользователе //
        getUsers(dialogIds);


        // Замена title в списке диалогов //
        QMap<int, Dialog>::iterator itr;
        for(itr = chats.begin(); itr != chats.end(); itr++)
        {
            Dialog dialog;
            dialog = itr.value();

            if(dialog.title() == "" ||  dialog.title() == " ... " ||  dialog.title() == "...")
            {
                // Имя и Фамилия записываются в название диалога //
                dialog.setTitle(users[dialog.id()].firstName() + " " + users[dialog.id()].lastName());
                dialog.setAvatar(users[dialog.id()].avatar50px());
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
    if( checkAccessToken() == true )
    {
        QUrlQuery request("https://api.vk.com/method/messages.getHistory?access_token=" + access_token);
        request.addQueryItem("user_id", idUser);

        QString urlString = request.toString();
        QUrl url(urlString);
        QByteArray answer = GET(url);


        if(answer.isEmpty())
        {
            qDebug() << "Пустой ответ в VKonatkte::loadHistory";
            return 0x000002;
        }

        QVariantList messageList = parse(answer).toMap().value("response").toList();
        history.clear();

        for(int i = 0; i < messageList.size(); i++)
        {
            QVariantMap currentMessage = messageList[i].toMap();

            QString texMsg = currentMessage.value("body").toString();
            QString from = currentMessage.value("from_id").toString();
            User from_user;

            if(from == current_user.id())
            {
                from_user = current_user;
            }
            else
            {
                if(from == users[from].id())
                {
                    from_user = users[from];
                }
            }


            Message message;
            message.setText(texMsg).setFrom(from_user);

            history[i] = message;
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
/*
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

*/







