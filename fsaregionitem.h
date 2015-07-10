#ifndef FSASELECTORITEM_H
#define FSASELECTORITEM_H

#include <QtCore>
class FsaRegionItem {
public:
    FsaRegionItem(const QString& n, int s, int r) {
        name = n;
        size = s;
        range = r;
    }

    QString name;
    int size;
    int range;
};

#endif // FSASELECTORITEM_H
