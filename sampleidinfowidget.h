#ifndef SAMPLEIDWIDGET_H
#define SAMPLEIDWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QActionGroup>
#include "sampleidlistmodel.h"
#include <QTreeWidget>
#include <QNetworkAccessManager>
class SampleIDInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SampleIDInfoWidget(QWidget *parent = 0);

public slots:
    void setSampleID(const SampleID& sampleId );
    void sort(QList<int> order);
    void openBrowser();

protected slots:
    void alleleReceived();
    void sortClicked(QAction * action);


private:
    QTreeWidget * mView;
    QNetworkAccessManager * mManager;
    QToolBar * mToolBar;
    QUrl mCurrentUrl ;
    QActionGroup * mSortGroup ;

};

#endif // SAMPLEIDWIDGET_H
