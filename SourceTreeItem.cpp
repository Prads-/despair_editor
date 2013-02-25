/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "SourceTreeItem.h"

SourceTreeItem::SourceTreeItem(QTreeWidget *parent, int itemType, QString name) : QTreeWidgetItem(parent) {
    initialize(itemType, name);
}

SourceTreeItem::SourceTreeItem(int itemType, QString name) {
    initialize(itemType, name);
}

void SourceTreeItem::initialize(int itemType, QString name) {
    this->itemType = itemType;
    this->name = name;
    this->setText(0, name);
    if (itemType == SRC_TREE_ITEM_FOLDER) {
        this->setIcon(0, QIcon(":/icons/icons/folder.png"));
    } else {
        this->setIcon(0, QIcon(":/icons/icons/source.png"));
    }
}

int SourceTreeItem::getItemType() {
    return itemType;
}

QString SourceTreeItem::getName() {
    return name;
}
