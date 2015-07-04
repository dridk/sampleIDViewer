#ifndef FSAINFOWIDGET_H
#define FSAINFOWIDGET_H

#include <QWidget>
#include "abifreader.h"
#include <QTreeWidget>
class FsaInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FsaInfoWidget(QWidget *parent = 0);

signals:

public slots:
    void setFileName(const QString& filename);

protected:
    QTreeWidgetItem *createItem(const QString &label, const QVariant &value);


private:
    QTreeWidget * mView;
};

#endif // FSAINFOWIDGET_H
