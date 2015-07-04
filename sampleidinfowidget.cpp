#include "sampleidinfowidget.h"
#include <QVBoxLayout>
#include <QWebView>
#include <QMenu>
#include <QAction>
#include <QHeaderView>
#include <QDesktopServices>
#include "tools.h"
#include "networkmanager.h"
SampleIDInfoWidget::SampleIDInfoWidget(QWidget *parent) :
    QWidget(parent)
{
    mView = new QTreeWidget;
    mManager = new QNetworkAccessManager;
    mToolBar = new QToolBar;

    mView->setIconSize(QSize(20,20));

    QVBoxLayout * cLayout = new QVBoxLayout;
    cLayout->addWidget(mToolBar);
    cLayout->addWidget(mView);
    cLayout->setContentsMargins(0,0,0,0);
    cLayout->setSpacing(0);
    setLayout(cLayout);

    mView->setAlternatingRowColors(true);

    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);


    QAction * browserAction = mToolBar->addAction("View on Torrent");
    mToolBar->insertWidget(0,spacerWidget);


    mSortGroup = new QActionGroup(this);
    mSortGroup->setExclusive(true);
    mSortGroup->addAction(mToolBar->addAction("SID order"));
    mSortGroup->addAction(mToolBar->addAction("FSA order"));

    mSortGroup->actions().at(0)->setCheckable(true);
    mSortGroup->actions().at(1)->setCheckable(true);

    mSortGroup->actions().at(0)->setObjectName("SID");
    mSortGroup->actions().at(1)->setObjectName("FSA");

    mSortGroup->actions().at(0)->setChecked(true);

    connect(mSortGroup,SIGNAL(triggered(QAction*)),this,SLOT(sortClicked(QAction*)));
    connect(browserAction,SIGNAL(triggered(bool)),this,SLOT(openBrowser()));

}
//================================================================
void SampleIDInfoWidget::setSampleID(const SampleID &sampleId)
{
    setEnabled(false);
    qDebug()<<sampleId.barcode;

    mView->clear();
    qDebug()<<sampleId.alleleUrl;

    mSortGroup->actions().at(0)->setChecked(true);


    //    QTreeWidgetItem * barcodeItem = new QTreeWidgetItem();
    //    barcodeItem->setText(0,"barcode");
    //    barcodeItem->setText(1,sampleId.barcode);
    //    mView->addTopLevelItem(barcodeItem);

    //    QTreeWidgetItem * sampleItem = new QTreeWidgetItem();
    //    sampleItem->setText(0,"sample");
    //    sampleItem->setText(1,sampleId.sample);
    //    mView->addTopLevelItem(sampleItem);

    //load alleles
    QUrl url = sampleId.alleleUrl;

    // set Web page url
    mCurrentUrl = sampleId.url;

    QNetworkReply * reply = NetworkManager::instance()->get(QNetworkRequest(url));
    connect(reply,SIGNAL(finished()),this,SLOT(alleleReceived()));


}
//================================================================
void SampleIDInfoWidget::sort(QList<int> order)
{

    QList<QTreeWidgetItem*> items;

    while (!order.isEmpty())
    {
        if (mView->topLevelItemCount() == 0)
            break;



        for (int i=0; i< mView->topLevelItemCount(); ++i)
        {
            int name = mView->topLevelItem(i)->text(2).split("#").at(1).toInt();
            qDebug()<<name<<" "<<order;

            if (name == order.first())
            {
                items.append(mView->takeTopLevelItem(i));
                order.removeFirst();
                break;
            }

            if (i == mView->topLevelItemCount()-1)
                order.removeFirst();
        }


    }

    mView->addTopLevelItems(items);
}

void SampleIDInfoWidget::openBrowser()
{
    qDebug()<<mCurrentUrl;
    QDesktopServices::openUrl(mCurrentUrl);

}
//================================================================
void SampleIDInfoWidget::alleleReceived()
{
    QNetworkReply * reply = qobject_cast<QNetworkReply*>(sender());



    QTextStream stream(reply->readAll());
    QStringList headers = stream.readLine().split("\t");
    mView->setColumnCount(headers.count());

    mView->setHeaderLabels(headers);

    QString line;
    do {
        line = stream.readLine();
        QStringList rows = line.split("\t");


        if (rows.size() == 15)
        {
            QTreeWidgetItem * item = new QTreeWidgetItem;



            for (int i=0; i<rows.count(); ++i){
                item->setText(i, rows[i]);
                mView->resizeColumnToContents(i);

            }

            QFont font;
            font.setBold(true);
            item->setFont(2, font);
            mView->addTopLevelItem(item);


        }



    } while (!line.isNull());


    for (int i=0; i<mView->topLevelItemCount(); ++i)
    {
        QTreeWidgetItem * item = mView->topLevelItem(i);

        QPixmap pix(mView->iconSize());

        QPainter painter(&pix);

       painter.setPen(QPen(Qt::white));

        QChar ref = item->text(4).at(0);
        QChar alt = item->text(5).at(0);

        double af = QString(item->text(6)).toDouble();
        qDebug()<<af;

        QColor col;

        if (!ref.isLetter() || !alt.isLetter()) {
            col = QColor(ERROR_COLOR);
            pix.fill(col);
            painter.drawText(pix.rect(),Qt::AlignCenter, "!");
        }


        else {
            if (ref == alt){
                col=QColor(TRUE_COLOR);
                pix.fill(col);
                painter.drawText(pix.rect(),Qt::AlignCenter, "W");

            }

            else {

                if (af > 70){
                    col = QColor(FALSE_COLOR);
                    pix.fill(col);
                    painter.drawText(pix.rect(),Qt::AlignCenter, "V");

                }
                else
                {

                    QPolygon pA;

                    pA << pix.rect().bottomLeft() << pix.rect().topLeft() << pix.rect().topRight();


                    QPolygon pB;
                    pB << pix.rect().topRight() << pix.rect().bottomRight() << pix.rect().bottomLeft();

                     painter.setPen(Qt::black);

                    col = QColor(MIDDLE_COLOR);
                    pix.fill(Qt::white);

                    painter.setBrush(QColor(TRUE_COLOR));
                    painter.drawPolygon(pA);

                    painter.setBrush(QColor(FALSE_COLOR));
                    painter.drawPolygon(pB);

                    painter.setPen(Qt::white);

                    painter.drawText(pix.rect(),Qt::AlignCenter, "H");

                }

            }

        }

//        item->setBackgroundColor(4, col);
//        item->setBackgroundColor(5, col);
//        item->setTextColor(4, Qt::white);
//        item->setTextColor(5, Qt::white);

        item->setIcon(0, QIcon(pix));

    }



    setEnabled(true);


}
//================================================================
void SampleIDInfoWidget::sortClicked(QAction *action)
{

    QList<int> order;


    if (action->objectName()=="SID")
    {
        order<<1<<2<<3<<4<<5<<6<<7<<8;
        sort(order);
    }

    if (action->objectName()=="FSA")
    {
        order<<4<<3<<7<<2<<1<<8<<6<<5;
        sort(order);
    }




}

