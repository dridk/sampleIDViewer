#ifndef TOOLS_H
#define TOOLS_H
#include <QtCore>
#include <QColor>
#include <QIcon>

#define TRUE_COLOR "#77DD77"
#define FALSE_COLOR "#779ECB"
#define ERROR_COLOR "#C23B22"
#define MIDDLE_COLOR "#FFB347"

class Tools
{

public:

    static int matchId(const QChar& letter, int index);
    static QColor matchColor(const QChar& letter, int index);
    static QIcon iconFromId(const QString& id);
    static QString ref();



private:
    Tools();




};

#endif // TOOLS_H
