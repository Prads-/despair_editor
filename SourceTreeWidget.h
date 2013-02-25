/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef _SOURCE_TREE_WIDGET_H
#define _SOURCE_TREE_WIDGET_H

#include <QtGui>
#include "SourceTreeItem.h"

class SourceTreeWidget : public QTreeWidget {
private:
    void createFolderChildString(SourceTreeItem *item, QString *strOut);

protected:
    void dropEvent(QDropEvent *event);

public:
    SourceTreeWidget(QWidget *parent = 0);

    void addItem(SourceTreeItem *parent, QString name, int itemType);
    void addItem(SourceTreeItem *parent, SourceTreeItem *item);

    void populateTreeString(QString treeString);
    QString createTreeString();
};

#endif // _SOURCE_TREE_WIDGET_H
