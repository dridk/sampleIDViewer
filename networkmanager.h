#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H
#include <QNetworkAccessManager>

class NetworkManager : public QNetworkAccessManager
{
    Q_OBJECT
private:
    NetworkManager(QObject * parent = 0);

public :
    static NetworkManager * instance() {
        if (NULL == mInstance) {
            mInstance = new NetworkManager();
            return mInstance;
        }
            else
            return mInstance;
    };

public slots:
    void authRequired();
    void logged();

private:
    static NetworkManager * mInstance;
};

#endif // NETWORKMANAGER_H
