#ifndef FSAPANELWIDGET_H
#define FSAPANELWIDGET_H
#include <QTabWidget>
#include <QtWidgets>
#include "fsaplot.h"
#include "fsaselectorwidget.h"
class FsaPanelWidget : public QTabWidget
{
    Q_OBJECT
public:
    FsaPanelWidget(QWidget * parent = 0);


    void setPlot(FsaPlot * plot);

    void update();

public slots:
    void axisUpdated();


private:
    QComboBox * mRefCombo;
    QComboBox * mSizeMarkCombo;
    QSlider * mXMinBox;
    QSlider * mYMinBox;
    QSlider * mYMaxBox;


    QPushButton * refStartButton;
    QPushButton * peakStartButton;

    FsaSelectorWidget * mSelectorWidget;

    FsaPlot * mPlot;
};

#endif // FSAPANELWIDGET_H
