/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include <QtGui>
#include <exception>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "FrmAbout.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    projectManager = new ProjectManager(ui->treeSource,ui->txtSource);

    connect(ui->treeSource, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(sourceSelectionChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete projectManager;
}

void MainWindow::on_actionInfo_triggered()
{
    FrmAbout aboutDialog(this);
    aboutDialog.setModal(true);
    aboutDialog.exec();
}

void MainWindow::on_actionAddNewSource_triggered()
{
    try {
        projectManager->addItem(this, SRC_TREE_ITEM_SOURCE);
    } catch (exception &e) {
        QMessageBox::warning(this, "New Source Error", QString(e.what()));
    }
}

void MainWindow::on_actionNewProject_triggered()
{
    try {
        projectManager->createProject(this);
    } catch (exception &e) {
        QMessageBox::warning(this, "New Project Error", QString(e.what()));
    }
}

void MainWindow::on_actionAddNewVirtualFolder_triggered()
{
    projectManager->addItem(this, SRC_TREE_ITEM_FOLDER);
}

void MainWindow::on_actionSave_triggered()
{
    try {
        projectManager->saveProject();
    } catch (exception &e) {
        QMessageBox::warning(this, "Save Project Error", QString(e.what()));
    }
}

void MainWindow::on_actionDeleteSource_triggered()
{
    projectManager->deleteItem(this);
}

void MainWindow::on_actionOpen_triggered()
{
    try {
        projectManager->openProject(this);
    } catch (exception &e) {
        QMessageBox::warning(this, "Open Project Error", QString(e.what()));
    }
}

void MainWindow::sourceSelectionChanged() {
    projectManager->sourceSelectionChanged();
}

void MainWindow::on_actionCloseProject_triggered()
{
    projectManager->closeProject(this);
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (projectManager->isProjectOpen()) {
        QMessageBox::StandardButton msgBoxBtn = QMessageBox::question(this, "Save Changes", "Do you want to save changes to this project?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
        if (msgBoxBtn == QMessageBox::Cancel) {
            event->ignore();
            return;
        } else if (msgBoxBtn == QMessageBox::Yes) {
            projectManager->saveProject();
        }
        event->accept();
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->txtSource->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->txtSource->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->txtSource->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->txtSource->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->txtSource->paste();
}

void MainWindow::on_actionFindAndReplace_triggered()
{
    ui->txtSource->findAndReplace();
}

void MainWindow::on_actionFrameLength_triggered()
{
    projectManager->setFrameLength(this);
}

void MainWindow::on_actionRun_triggered()
{
    projectManager->build(this, BUILD_CODE_RUN);
}

void MainWindow::on_actionBuildAndRun_triggered()
{
    projectManager->build(this, BUILD_CODE_BUILD_AND_RUN);
}

void MainWindow::on_actionBuild_triggered()
{
    projectManager->build(this, BUILD_CODE_BUILD);
}

void MainWindow::on_actionMemorySize_triggered()
{
    projectManager->setMemorySize(this);
}
