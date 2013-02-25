/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ProjectManager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionInfo_triggered();

    void on_actionAddNewSource_triggered();

    void on_actionNewProject_triggered();

    void on_actionAddNewVirtualFolder_triggered();

    void on_actionSave_triggered();

    void on_actionDeleteSource_triggered();

    void on_actionOpen_triggered();

    void sourceSelectionChanged();

    void on_actionCloseProject_triggered();

    void on_actionExit_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionFindAndReplace_triggered();

    void on_actionFrameLength_triggered();

    void on_actionRun_triggered();

    void on_actionBuildAndRun_triggered();

    void on_actionBuild_triggered();

    void on_actionMemorySize_triggered();

private:
    Ui::MainWindow *ui;
    ProjectManager *projectManager;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
