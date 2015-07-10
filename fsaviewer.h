#ifndef FSAVIEWER_H
#define FSAVIEWER_H

#include <QtWidgets>
#include "fsaplot.h"
#include "fsapanelwidget.h"
class FsaViewer : public QWidget
{
    Q_OBJECT
public:
    explicit FsaViewer(QWidget *parent = 0);

public slots:
    void setFileName(const QString& filename);

  protected slots:
    void setGraphVisible(bool visible);
    void loadDyeActions();

private:
    FsaPlot * mPlot;
    QToolBar * mBar;
    FsaPanelWidget * mPanel;
    QToolButton * mDyeButton;



};

#endif // FSAVIEWER_H
