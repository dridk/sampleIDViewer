#ifndef PROTONLISTMODEL_H
#define PROTONLISTMODEL_H

#include <QObject>
#include <QIcon>
#include <QAbstractListModel>
#include <QtNetwork>
#include <QTemporaryFile>
#include "networkmanager.h"

class SampleID {
public:
    QString barcode;
    QString sample;
    QUrl url;
    QUrl alleleUrl;
    QString id;

};




class SampleIDListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SampleIDListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;

    SampleID sampleID(const QModelIndex& index);

     bool isLoading();

public slots:
    // Load data
    void loadAll();

protected slots:
    void loadData();
    void loadMeta();

    void parseFile(const QString& filename = QString());

   protected:
    void setLoading(bool enable);






public slots:
    void dataReceived();
    void metaReceived();

signals:
    void metaLoaded();
    void dataLoaded();
    void stateChanged(QString state);


private:
    QList<SampleID> mDatas;
    QUrl mUrl;
    QUrlQuery mQuery;
    int mTotalCount;
    QTemporaryFile mFile;
    bool mLoading;


};

#endif // PROTONLISTMODEL_H
