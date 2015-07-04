#ifndef FILEBROWSERWIDGET_H
#define FILEBROWSERWIDGET_H
#include <QListView>
#include <QFileSystemModel>
class FileBrowserWidget : public QListView
{
    Q_OBJECT
public:
    FileBrowserWidget(QWidget * parent = 0);


private:
    QFileSystemModel * mModel;
};

#endif // FILEBROWSERWIDGET_H
