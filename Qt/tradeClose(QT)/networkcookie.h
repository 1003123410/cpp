#ifndef NETWORKCOOKIE
#define NETWORKCOOKIE

#include <QtNetwork/QNetworkCookie>
#include <QtNetwork/QNetworkCookieJar>

class NetworkCookie : public QNetworkCookieJar
{
    Q_OBJECT

public:
    NetworkCookie(QObject *parent);
    ~NetworkCookie();

    QList<QNetworkCookie> getCookies();
    void setCookies(const QList<QNetworkCookie>& cookieList);
private:

};

#endif // NETWORKCOOKIE

