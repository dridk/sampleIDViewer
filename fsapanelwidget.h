#ifndef FSAPANELWIDGET_H
#define FSAPANELWIDGET_H
#include <QTabWidget>
#include <QtWidgets>
class FsaPanelWidget : public QTabWidget
{
public:
    FsaPanelWidget(QWidget * parent = 0);



private:
    QComboBox * mRefCombo;
    QComboBox * mSizeMarkCombo;
    QSpinBox * mXMinBox;
    QSpinBox * mYMinBox;
    QSpinBox * mYMaxBox;


    QPushButton * refStartButton;
    QPushButton * peakStartButton;
};

#endif // FSAPANELWIDGET_H
