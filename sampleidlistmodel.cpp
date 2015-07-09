#include "sampleidlistmodel.h"
#include <QSettings>
#include <QDebug>
#include <QUrl>
#include <QPainter>
#include <QEventLoop>
#include <QJsonDocument>
#include <QTemporaryFile>
#include "tools.h"

SampleIDListModel::SampleIDListModel(QObject *parent)
{

    QString base = "/rundb/api/v1/";
    QSettings settings;
    settings.beginGroup("server/pgm");
    mUrl.setScheme("http");
    mUrl.setHost(settings.value("host").toString());
    mUrl.setUserName(settings.value("username").toString());
    mUrl.setPassword(settings.value("password").toString());
    mUrl.setPath(base);
    settings.endGroup();


    mQuery.addQueryItem("format","json");
    mQuery.addQueryItem("plugin__name__exact","sampleID");
    mQuery.addQueryItem("limit","1");
    mQuery.addQueryItem("order_by","-endtime");

    mUrl.setPath(base + "pluginresult/");
    mUrl.setQuery(mQuery);

//    loadAll();
}

//================================================================

int SampleIDListModel::rowCount(const QModelIndex &parent) const
{
    return mDatas.count() ;
}
//================================================================
QVariant SampleIDListModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

    if ( role == Qt::DisplayRole)
        return mDatas.at(index.row()).sample;

    if (role == Qt::DecorationRole)
        return Tools::iconFromId(mDatas.at(index.row()).id);

    return QVariant();

}
//================================================================
SampleID SampleIDListModel::sampleID(const QModelIndex &index)
{

    if (index.isValid())
        return mDatas.at(index.row());
    else
        return SampleID();

}

bool SampleIDListModel::isLoading()
{
    return mLoading;
}
//================================================================
void SampleIDListModel::loadAll()
{
    setLoading(true);
    beginResetModel();
    mDatas.clear();
    endResetModel();


    loadMeta();
    connect(this,SIGNAL(metaLoaded()),this, SLOT(loadData()));
    connect(this,SIGNAL(dataLoaded()),SLOT(parseFile()));
}
//================================================================
void SampleIDListModel::loadData()
{
    emit stateChanged("Loading data ...");

    mQuery.removeQueryItem("limit");
    mQuery.addQueryItem("limit",QString::number(mTotalCount));

    mUrl.setQuery(mQuery);


    QNetworkRequest request(mUrl);
    QNetworkReply * reply = NetworkManager::instance()->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(dataReceived()));



}
//================================================================
void SampleIDListModel::loadMeta()
{
    emit stateChanged("Loading data size ...");

    mQuery.removeQueryItem("limit");
    mQuery.addQueryItem("limit","1");
    mUrl.setQuery(mQuery);

    qDebug()<<mUrl;

    QNetworkRequest request(mUrl);
    QNetworkReply * reply = NetworkManager::instance()->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(metaReceived()));

}
//================================================================

void SampleIDListModel::parseFile(const QString& filename)
{

    QString fname = filename;

    if (fname.isEmpty())
        fname = mFile.fileName();

    QFile file(fname);

    if (!file.open(QIODevice::ReadOnly))
        return;

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    QJsonArray all = document.object().value("objects").toArray();

    beginResetModel();

    mDatas.clear();

    foreach (QJsonValue root ,all)
    {
        if (root.toObject().contains("store"))
        {
            QJsonObject store = root.toObject().value("store").toObject();

            if (store.contains("barcodes"))
            {
                QJsonObject barcodes = store.value("barcodes").toObject();

                foreach (QString key, barcodes.keys() )
                {
                    SampleID item;
                    item.barcode = key;
                    item.sample  = barcodes.value(key).toObject().value("Sample Name").toString();
                    item.id  = barcodes.value(key).toObject().value("Sample ID").toString();

                    QUrl url = mUrl;
                    url.setQuery(QUrlQuery());
                    item.url     = url;
                    item.url.setPath(root.toObject().value("path").toString().remove("results/analysis/").append("/").append(key).append("/sampleID.html"));

                    item.alleleUrl = url;
                    item.alleleUrl.setPath(root.toObject().value("path").toString().remove("results/analysis/").append("/").append(key).append("/allele_counts.xls"));

                    if (!item.id.isEmpty())
                        mDatas.append(item);

                }
            }

        }

    }

    endResetModel();
    emit layoutChanged();
    setLoading(false);
    emit stateChanged(QString("%1 Loaded").arg(mDatas.count()));
}

void SampleIDListModel::setLoading(bool enable)
{
    mLoading = enable;
}
//================================================================

void SampleIDListModel::dataReceived()
{
    emit stateChanged("write temporary file ...");

    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());

    if (mFile.open())
        mFile.write(reply->readAll());
    else
        qDebug()<<"cannot write file";

    mFile.close();

    emit dataLoaded();

}
//================================================================
void SampleIDListModel::metaReceived()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());

    mTotalCount = document.object().value("meta").toObject().value("total_count").toInt();

    qDebug()<<mTotalCount;

    emit metaLoaded();

    reply->deleteLater();

}

//================================================================


//================================================================
