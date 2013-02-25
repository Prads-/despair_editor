/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include <fstream>
#include <stdexcept>
#include <QFileDialog>
#include <QMessageBox>
#include "ProjectManager.h"
#include "FrmNewSource.h"
#include "FrmAddFolder.h"
#include "FrmNewProject.h"
#include "FrmFrameLength.h"
#include "FrmCompilerError.h"
#include "FrmMemorySize.h"
using namespace std;

ProjectManager::ProjectManager(SourceTreeWidget *srcTreeWidget, SourcePlainText *srcPlainText) {
    this->srcTreeWidget = srcTreeWidget;
    this->srcPlainText = srcPlainText;
    projectIsOpen = false;
    currentSourceName = "";
}

QString ProjectManager::getSourceFromFile(QString path) {
    ifstream sourceFile(path.toStdString().c_str());
    if (!sourceFile.is_open()) {
        string errMsg = "Cannot find source file: ";
        errMsg += path.toStdString().c_str();
        throw runtime_error(errMsg);
    }

    string source = "", srcLine;
    while(getline(sourceFile, srcLine)) {
        source += srcLine + "\n";
    }
    sourceFile.close();

    return QString::fromStdString(source);
}

void ProjectManager::getSourcesFromTreeString(QString treeString) {
    QTextStream tStrStream(&treeString, QIODevice::ReadOnly);
    while (true) {
        QString line = tStrStream.readLine();
        if (line == "[source]") {
            line = tStrStream.readLine();

            QString sourcePath = projectFolder + "/" + line;
            QString source = getSourceFromFile(sourcePath);

            pair<SourceFiles::iterator, bool> insertedSource = sourceFiles.insert(SourceFiles::value_type(line, source));

            if (!insertedSource.second) {
                throw runtime_error("Invalid project tree string: Duplicate source file");
            }
        } else if (line == "") {
            break;
        }
    }
}

void ProjectManager::deleteSourcesFromFolder(SourceTreeItem *folder) {
    for (int i = 0; i < folder->childCount(); ++i) {
        SourceTreeItem *child = (SourceTreeItem*)folder->child(i);
        if (child->getItemType() == SRC_TREE_ITEM_FOLDER) {
            deleteSourcesFromFolder(child);
        } else {
            deleteSource(child->getName());
        }
    }
}

QString ProjectManager::addExistingSource(QString destName, QString srcPath) {
    QString destPath = projectFolder + "/" + destName;
    QString source = getSourceFromFile(srcPath);

    ofstream destFile(destPath.toStdString().c_str());

    if (!destFile.is_open()) {
        throw runtime_error("Couldn't create destination file");
    }

    destFile << source.toStdString();
    destFile.close();

    return source;
}

void ProjectManager::saveCurrentSourceToMemory() {
    if (currentSourceName != "") {
        SourceFiles::iterator it = sourceFiles.find(currentSourceName);
        if (it != sourceFiles.end()) {
            it->second = srcPlainText->toPlainText();
        }
    }
}

void ProjectManager::saveProjectTreeString() {
    QString treeString = srcTreeWidget->createTreeString();
    ofstream projFile(projectPath.toStdString().c_str());
    if (!projFile.is_open()) {
        throw runtime_error("Saving Project file failed");
    }
    projFile << frameWidth << "\n" << frameHeight << "\n";
    projFile << dataSpaceSize << "\n" << stackSpaceSize << "\n";
    projFile << treeString.toStdString();
    projFile.close();
}

void ProjectManager::createProject(QWidget *parent) {
    FrmNewProject newProjectDialog(parent);
    newProjectDialog.setModal(true);
    if (newProjectDialog.exec() == QDialog::Accepted) {
        //Make Project Directory
        QString projDir = newProjectDialog.getProjectDirectory();
        QDir qDir(projDir);
        if (!qDir.exists()) {
            throw runtime_error("Directory doesn't exist");
        }
        if (!qDir.mkdir(newProjectDialog.getProjectName())) {
            throw runtime_error("Couldn't create project folder");
        }
        projectFolder = projDir + "/" + newProjectDialog.getProjectName();

        //Close currently open project
        closeProject(parent);

        //Default frame width and height
        frameHeight = 512;
        frameWidth = 512;

        //Default data and stack size (1 MB)
        dataSpaceSize = 1048576;
        stackSpaceSize = 1048576;

        //Make Project File
        projectPath = projectFolder + "/" + newProjectDialog.getProjectName() + ".dpro";
        ofstream projectFile(projectPath.toStdString().c_str());
        projectFile << frameHeight << "\n" << frameWidth << "\n";
        projectFile.close();

        projectIsOpen = true;
        parent->setWindowTitle(newProjectDialog.getProjectName() + " - despairEditor");
    }
}

void ProjectManager::openProject(QWidget *parent) {
    QString newProjectPath = QFileDialog::getOpenFileName(parent, "Open Project", "", "despairProject(*.dpro)");
    if (newProjectPath != "") {
        closeProject(parent);

        projectPath = newProjectPath;
        int folderPathLength;
        for (folderPathLength = projectPath.size() - 1; folderPathLength >= 0; --folderPathLength) {
            if (projectPath[folderPathLength] == '/') {
                break;
            }
        }
        projectFolder = projectPath.left(folderPathLength);

        ifstream projectFile(projectPath.toStdString().c_str());
        if (!projectFile.is_open()) {
            throw runtime_error("Couldn't open the project file");
        }

        string sTreeString = "", line;

        //Get the frame length
        getline(projectFile, line);
        frameWidth = atoi(line.c_str());
        getline(projectFile, line);
        frameHeight = atoi(line.c_str());

        //Get data and stack size
        getline(projectFile, line);
        dataSpaceSize = atoi(line.c_str());
        getline(projectFile, line);
        stackSpaceSize = atoi(line.c_str());

        //Then get the project's tree string
        while(getline(projectFile, line)) {
            sTreeString += line + "\n";
        }
        QString treeString = QString::fromStdString(sTreeString);

        getSourcesFromTreeString(treeString);
        srcTreeWidget->populateTreeString(treeString);
        projectIsOpen = true;

        int nameOffset;
        for (nameOffset = projectPath.size() - 1; nameOffset >= 0; -- nameOffset) {
            if (projectPath[nameOffset] == '/') {
                ++nameOffset;
                break;
            }
        }
        QString projectName = projectPath.mid(nameOffset, projectPath.size() - nameOffset - 5);

        parent->setWindowTitle(projectName + " - despairEditor");
    }
}

QString ProjectManager::getProjectPath() {
    return projectPath;
}

QString ProjectManager::getProjectFolder() {
    return projectFolder;
}

void ProjectManager::closeProject(QWidget *parent) {
    if (projectIsOpen) {
        if (QMessageBox::question(parent, "Save Changes", "Do you want to save changes to current project?", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes) {
            saveProject();
        }
        srcTreeWidget->clear();
        sourceFiles.clear();
        srcPlainText->clear();
        projectIsOpen = false;
        currentSourceName = "";
        projectFolder = "";
        projectPath = "";
        parent->setWindowTitle("despairEditor");
    }
}

void ProjectManager::saveProject() {
    if (projectIsOpen) {
        saveCurrentSourceToMemory();

        for (SourceFiles::iterator it = sourceFiles.begin(); it != sourceFiles.end(); ++it) {
            QString path = projectFolder + "/" + it->first;
            ofstream srcFile(path.toStdString().c_str());

            if (!srcFile.is_open()) {
                string errMsg = "Couldn't save: ";
                errMsg += it->first.toStdString();
                throw runtime_error(errMsg);
            }

            srcFile << it->second.toStdString().c_str();
            srcFile.close();
        }

        saveProjectTreeString();
    }
}

void ProjectManager::addItem(QWidget *parent, int itemType) {
    if (projectIsOpen) {
        QString name;

        if (itemType == SRC_TREE_ITEM_SOURCE) {
            QString source = "";

            FrmNewSource newSourceDialog(parent);
            newSourceDialog.setModal(true);

            if (newSourceDialog.exec() == QDialog::Accepted) {
                name = newSourceDialog.getName() + ".dsrc";

                if (newSourceDialog.addExistingFile()) {
                    QString srcPath = newSourceDialog.getSrcPath();
                    source = addExistingSource(name, srcPath);
                }

                pair<SourceFiles::iterator, bool> addedSource = sourceFiles.insert(SourceFiles::value_type(name, source));
                if (addedSource.second == false) {
                    throw runtime_error("Duplicate source name is not allowed");
                }
                srcTreeWidget->addItem(0, name, SRC_TREE_ITEM_SOURCE);
            }
        } else {
            FrmAddFolder addFolderDialog(parent);
            addFolderDialog.setModal(true);

            if (addFolderDialog.exec() == QDialog::Accepted) {
                name = addFolderDialog.getName();
                srcTreeWidget->addItem(0, name, SRC_TREE_ITEM_FOLDER);
            }
        }
    }
}

void ProjectManager::deleteItem(QWidget *parent) {
    SourceTreeItem *item = (SourceTreeItem*)srcTreeWidget->currentItem();
    if (item) {
        QMessageBox::StandardButton msgBoxBtn = QMessageBox::question(parent, "Delete Source", "Do you want to delete the source permanently from the disk?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::No);
        if (msgBoxBtn == QMessageBox::Cancel) {
            return;
        } else if (msgBoxBtn == QMessageBox::Yes) {
            if (item->getItemType() == SRC_TREE_ITEM_FOLDER) {
                deleteSourcesFromFolder(item);
            } else {
                deleteSource(item->getName());
            }
        }
        if (item->getItemType() == SRC_TREE_ITEM_SOURCE) {
            SourceFiles::iterator it = sourceFiles.find(item->getName());
            sourceFiles.erase(it);
        }
        delete item;
        saveProjectTreeString();
    }
}

void ProjectManager::setFrameLength(QWidget *parent) {
    if (projectIsOpen) {
        FrmFrameLength frameLengthDialog(parent, frameWidth, frameHeight);
        frameLengthDialog.setModal(true);
        if (frameLengthDialog.exec() == QDialog::Accepted) {
            frameWidth = frameLengthDialog.getWidth();
            frameHeight = frameLengthDialog.getHeight();
        }
    }
}

void ProjectManager::setMemorySize(QWidget *parent) {
    if (projectIsOpen) {
        FrmMemorySize memorySizeDialog(parent, dataSpaceSize, stackSpaceSize);
        memorySizeDialog.setModal(true);
        if (memorySizeDialog.exec() == QDialog::Accepted) {
            dataSpaceSize = memorySizeDialog.getDataSpaceSize();
            stackSpaceSize = memorySizeDialog.getStackSpaceSize();
        }
    }
}

void ProjectManager::run(QWidget *parent) {
    QStringList vmArgument;
    vmArgument.push_back(projectFolder + "/" + "build.dbin");
    int retVal = QProcess::execute(QCoreApplication::applicationDirPath() + "/vm/despairVM.exe", vmArgument);
    if (retVal == -2) {
        QMessageBox::warning(parent, "Build Error", "VM could not be started");
    } else if (retVal == -1) {
        QMessageBox::warning(parent, "Build Error", "VM crashed");
    }
}

void ProjectManager::build(QWidget *parent, int buildCode) {
    if (projectIsOpen) {
        saveProject();
        if (buildCode & 0x80) { //Build
            QString caption = parent->windowTitle();
            parent->setWindowTitle(caption + " Building Project [Please Wait...]");

            QStringList compilerArgument;
            compilerArgument.push_back(projectPath);
            compilerArgument.push_back(projectFolder + "/" + "build.dbin");
            int cRetVal = QProcess::execute(QCoreApplication::applicationDirPath() + "/compiler/despairCompiler.exe", compilerArgument);
            parent->setWindowTitle(caption);

            if (cRetVal == 0) {    //Run
                if (buildCode & 1) {
                    run(parent);
                }
            } else if (cRetVal == 1) {    //Error
                ifstream buildLogFile;
                QString buildLogPath;

                buildLogPath = QCoreApplication::applicationDirPath() + "/buildLog.txt";
                buildLogFile.open(buildLogPath.toStdString().c_str());
                string buildLog = "";

                if (buildLogFile.is_open()) {
                    string line;
                    while (getline(buildLogFile, line)) {
                        buildLog += line + "\n";
                    }
                } else {
                    QMessageBox::warning(parent, "Build Error", "Compiler returned an error but couldn't open the build log");
                    return;
                }

                FrmCompilerError compilerErrorDialog;

                compilerErrorDialog.setErrorString(QString::fromStdString(buildLog));
                compilerErrorDialog.exec();
            } else if (cRetVal == -2) {
                QMessageBox::warning(parent, "Build Error", "Compiler could not be started");
            } else if (cRetVal == -1) {
                QMessageBox::warning(parent, "Build Error", "Compiler crashed");
            } else {
                QMessageBox::warning(parent, "Build Error", "Trying to run compiler failed");
            }
        } else {    //Run
            run(parent);
        }
    }
}

void ProjectManager::sourceSelectionChanged() {
    SourceTreeItem *item = (SourceTreeItem*)srcTreeWidget->currentItem();
    if (item) {
        if (item->getItemType() != SRC_TREE_ITEM_SOURCE) {
            return;
        }
        saveCurrentSourceToMemory();
        currentSourceName = item->getName();

        SourceFiles::iterator it = sourceFiles.find(currentSourceName);
        srcPlainText->setPlainText(it->second);
    }
}

bool ProjectManager::isProjectOpen() {
    return projectIsOpen;
}

void ProjectManager::deleteSource(QString sourceName) {
    string srcPath = projectFolder.toStdString() + "/" + sourceName.toStdString();
    remove(srcPath.c_str());
}
