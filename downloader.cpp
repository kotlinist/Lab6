#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &Downloader::onResult);
}

void Downloader::getData() {
    QUrl url("https://mocktarget.apigee.net/xml");
    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
}

void Downloader::onResult(QNetworkReply *reply) {
    if(reply->error()) {
        qDebug() << "ERROR";
        qDebug() << reply->errorString();
    } else {
        QFile *file = new QFile("/Users/kotlinist/Downloads/file.xml");
        if(file->open(QFile::WriteOnly)) {
            file->write(reply->readAll());
                file->close();
            qDebug() << "Downloading is completed";
            emit onReady();
        }
    }
}
