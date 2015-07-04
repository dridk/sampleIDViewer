#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sampleidlistwidget.h"
#include "fsaviewer.h"
#include "fsainfowidget.h"
#include "sampleidinfowidget.h"
#include "filebrowserwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



   public slots:
    void open();

    void setStatus(const QString& message);

protected:
    void createToolBar(const QList<QAction*>& actionsList);

private:
    Ui::MainWindow *ui;
    SampleIDListWidget * mListWidget;
    FsaViewer * mPlot;
    QTabWidget * mTabWidget;
    QSplitter * mSplitter;
    SampleIDInfoWidget * mSampleIdInfoWidget;
    FsaInfoWidget * mFsaInfoWidget;
    FileBrowserWidget * mBrowserWidget;
    QLabel * mAnimLabel;
};

#endif // MAINWINDOW_H
