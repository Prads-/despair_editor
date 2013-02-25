/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include <stdexcept>
#include <stack>
#include <QHeaderView>
#include "SourceTreeWidget.h"
using namespace std;

SourceTreeWidget::SourceTreeWidget(QWidget *parent) : QTreeWidget(parent) {
    this->header()->setStretchLastSection(false);
    this->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void SourceTreeWidget::dropEvent(QDropEvent *event) {
    SourceTreeItem *droppedOn = (SourceTreeItem*)this->itemAt(event->pos());
    if (droppedOn) {
        if (droppedOn->getItemType() == SRC_TREE_ITEM_FOLDER) {
            QTreeWidget::dropEvent(event);
        } else {
            event->setDropAction(Qt::IgnoreAction);
            event->accept();
        }
    } else {
        QTreeWidget::dropEvent(event);
    }
}

void SourceTreeWidget::addItem(SourceTreeItem *parent, QString name, int itemType) {
    if (parent) {
        SourceTreeItem *item = new SourceTreeItem(itemType, name);
        parent->addChild(item);
    } else {
        SourceTreeItem *item = new SourceTreeItem(this, itemType, name);
    }
}

void SourceTreeWidget::addItem(SourceTreeItem *parent, SourceTreeItem *item) {
    if (parent) {
        parent->addChild(item);
    } else {
        this->addTopLevelItem(item);
    }
}

void SourceTreeWidget::populateTreeString(QString treeString) {
    QTextStream tStrStream(&treeString, QIODevice::ReadOnly);
    stack<SourceTreeItem*> folderStack;
    SourceTreeItem *currentFolder = 0;

    while (true) {
        QString line = tStrStream.readLine();
        if (line == "[folder]") {
            folderStack.push(currentFolder);
            line = tStrStream.readLine();
            currentFolder = new SourceTreeItem(SRC_TREE_ITEM_FOLDER, line);
        } else if (line == "[source]") {
            line = tStrStream.readLine();
            addItem(currentFolder, line, SRC_TREE_ITEM_SOURCE);
        } else if (line == "[/folder]") {
            if (currentFolder == 0) {
                throw runtime_error("Invalid project tree string: Too many [/folder]");
            }
            SourceTreeItem *parentFolder = folderStack.top();
            folderStack.pop();
            addItem(parentFolder, currentFolder);

            currentFolder = parentFolder;
        } else if (line == "") {
            break;
        } else {
            throw runtime_error("Invalid project tree string: Project file seems to be corrupted");
        }
    }
}

void SourceTreeWidget::createFolderChildString(SourceTreeItem *item, QString *strOut) {
    *strOut += "[folder]\n" + item->getName() + "\n";

    for (int i = 0; i < item->childCount(); ++i) {
        SourceTreeItem *child = (SourceTreeItem*)item->child(i);
        if (child->getItemType() == SRC_TREE_ITEM_FOLDER) {
            createFolderChildString(child, strOut);
        } else {
            *strOut += "[source]\n" + child->getName() + "\n";
        }
    }

    *strOut += "[/folder]\n";
}

QString SourceTreeWidget::createTreeString() {
    QString treeString = "";
    for (int i = 0; i < this->topLevelItemCount(); ++i) {
        SourceTreeItem *item = (SourceTreeItem*)this->topLevelItem(i);
        if (item->getItemType() == SRC_TREE_ITEM_FOLDER) {
            createFolderChildString(item, &treeString);
        } else {
            treeString += "[source]\n" + item->getName() + "\n";
        }
    }
    return treeString;
}
