#include "tools.h"
#include <QPainter>
#include <QDebug>
int Tools::matchId(const QChar& letter, int index)
{

    if (!letter.isLetter())
        return -1;

    return int(ref().at(index) == letter);
}

QColor Tools::matchColor(const QChar &letter, int index)
{
    int match = matchId(letter, index);

    if (match == -1)
        return Qt::lightGray;

    return match ? Qt::lightGray : Qt::darkGray;

}



QIcon Tools::iconFromId(const QString &id)
{

    QPixmap pix(121,11);
    pix.fill(Qt::white);
    QPainter painter(&pix);

    if (ref().size() != id.size()){
        QBrush brush(Qt::white);
        painter.setBrush(brush);
        QRect r = pix.rect().adjusted(0,0,-1,-1);
        painter.drawRect(r);
        painter.drawText(r,Qt::AlignCenter, id);
        return QIcon(pix);
    }


    int step = pix.width() / ref().size();

    for (int i= 0; i <  ref().size(); ++i)
    {

        QColor col = matchColor(id.at(i),i);

        painter.setBrush(QBrush(col));
        painter.setPen(QPen(Qt::gray));

        QRect r = QRect(i*step, 0, step-2, step-2);

        painter.drawRect(r);
        painter.setPen(QPen(Qt::white));

        QFont font;
        font.setPixelSize(9);
        painter.setFont(font);

        painter.drawText(r, Qt::AlignCenter, QString(id[i]));



    }

    return QIcon(pix);

}

QString Tools::ref()
{
    return "M-TTGTACGT";

}



Tools::Tools()
{

}

