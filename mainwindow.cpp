#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mAnimLabel = new QLabel();
    mListWidget = new SampleIDListWidget;
    mPlot       = new FsaViewer;
    mTabWidget  = new QTabWidget;
    mSplitter   = new QSplitter(Qt::Vertical);
    mBrowserWidget = new FileBrowserWidget();
            mSampleIdInfoWidget = new SampleIDInfoWidget;
    mFsaInfoWidget      = new FsaInfoWidget;

    mAnimLabel->setMovie(new QMovie(":/ajax-loader.gif"));

    QDockWidget * leftDock = new QDockWidget;
    leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    leftDock->setWidget(mListWidget);



    QDockWidget * leftDock2 = new QDockWidget;
    leftDock2->setFeatures(QDockWidget::NoDockWidgetFeatures);
    leftDock2->setWidget(mBrowserWidget);




    mTabWidget->addTab(mSampleIdInfoWidget, "Sample ID");
    mTabWidget->addTab(mFsaInfoWidget,"FSA Info");


    mSplitter->addWidget(mPlot);
    mSplitter->addWidget(mTabWidget);


    addDockWidget(Qt::LeftDockWidgetArea, leftDock);
    addDockWidget(Qt::LeftDockWidgetArea, leftDock2);

    createToolBar(mListWidget->actions());
    createToolBar(mPlot->actions());
    QAction * openAction = ui->mainToolBar->addAction("Open");

    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

    resize(800, 500);

    setCentralWidget(mSplitter);


    connect(mListWidget,SIGNAL(sampleIDClicked(SampleID)),mSampleIdInfoWidget,SLOT(setSampleID(SampleID)));
    connect(mListWidget,SIGNAL(stateChanged(QString)),this,SLOT(setStatus(QString)));


    statusBar()->insertPermanentWidget(0,mAnimLabel);
    mAnimLabel->movie()->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::open()
{
    QString filename =  QFileDialog::getOpenFileName(this, tr("Open File"), "", tr(""));

    mPlot->setFileName(filename);
    mFsaInfoWidget->setFileName(filename);

}

void MainWindow::setStatus(const QString &message)
{

    mAnimLabel->setVisible(mListWidget->isLoading());
    mListWidget->setEnabled(!mListWidget->isLoading());
    if (!mListWidget->isLoading()) {
        mAnimLabel->hide();

    }
    else {
        mAnimLabel->show();


    }
    statusBar()->showMessage(message);
}

void MainWindow::createToolBar(const QList<QAction*>& actionsList)
{
    QToolBar * bar = new QToolBar;
    bar->addActions(actionsList);
    addToolBar(bar);
}
