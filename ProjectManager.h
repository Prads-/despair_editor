/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef _PROJECT_MANAGER_H
#define _PROJECT_MANAGER_H

#include <QtGui>
#include <map>
#include "SourceTreeWidget.h"
#include "SourceTreeItem.h"
#include "SourcePlainText.h"

#define BUILD_CODE_RUN                  1
#define BUILD_CODE_BUILD                0x80
#define BUILD_CODE_BUILD_AND_RUN        0x81

typedef std::map<QString, QString> SourceFiles;

class ProjectManager {
private:
    QString projectPath, projectFolder;
    bool projectIsOpen;
    SourceFiles sourceFiles;
    SourceTreeWidget *srcTreeWidget;
    SourcePlainText *srcPlainText;
    QString currentSourceName;
    int frameWidth, frameHeight;
    int dataSpaceSize, stackSpaceSize;

    QString getSourceFromFile(QString path);    //Get source code from source file in disk
    void getSourcesFromTreeString(QString treeString);  //Get source code from source files in disk
    void deleteSourcesFromFolder(SourceTreeItem *folder);   //Delete source files from disk
    QString addExistingSource(QString destName, QString srcPath);   //Add existing source code to newly created source file
    void saveCurrentSourceToMemory();   //Save the current open source file to SourceFiles map while jumping between source files
    void saveProjectTreeString();   //Save the '.dpro' file
    void run(QWidget *parent);  //Run the build in VM
    void deleteSource(QString sourceName);  //Deletes the source file from disk

public:
    ProjectManager(SourceTreeWidget *srcTreeWidget, SourcePlainText *srcPlainText);

    void createProject(QWidget *parent);
    void openProject(QWidget *parent);
    void closeProject(QWidget *parent);
    void saveProject();

    void addItem(QWidget *parent, int itemType);
    void deleteItem(QWidget *parent);

    void setFrameLength(QWidget *parent);
    void setMemorySize(QWidget *parent);

    void build(QWidget *parent, int buildCode = BUILD_CODE_RUN);

    void sourceSelectionChanged();

    QString getProjectPath();
    QString getProjectFolder();
    bool isProjectOpen();
};

#endif // _PROJECT_MANAGER_H
