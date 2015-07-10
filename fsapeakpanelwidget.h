#ifndef PEAKPANELWIDGET_H
#define PEAKPANELWIDGET_H

#include <QtWidgets>
#include "abstractfsapanelwidget.h"

class FsaPeakPanelWidget : public AbstractFsaPanelWidget
{
    Q_OBJECT
public:
    explicit FsaPeakPanelWidget(QWidget *parent = 0);

    virtual void init();
    virtual void beforeReplot();
    virtual void setActive(bool enabled);
public slots:


private:
    QComboBox * mRefCombo;
    QComboBox * mSizeMarkCombo;
    QSlider * mXMinBox;
    QSlider * mYMinBox;
    QSlider * mYMaxBox;


    QPushButton * mStartButton;

};

#endif // PEAKPANELWIDGET_H
