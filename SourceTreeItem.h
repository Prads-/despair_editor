/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef _SOURCE_TREE_ITEM_H
#define _SOURCE_TREE_ITEM_H

#include <QtGui>
#include <QTreeWidgetItem>

#define SRC_TREE_ITEM_FOLDER            0
#define SRC_TREE_ITEM_SOURCE            1

class SourceTreeItem : public QTreeWidgetItem {
private:
    int itemType;
    QString name;
    void initialize(int itemType, QString name);

public:
    SourceTreeItem(QTreeWidget *parent, int itemType, QString name);
    SourceTreeItem(int itemType, QString name);

    int getItemType();
    QString getName();
};

#endif // _SOURCE_TREE_ITEM_H
