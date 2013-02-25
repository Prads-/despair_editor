/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include <QtGui>
#include <QFileDialog>
#include "FrmNewProject.h"
#include "ui_FrmNewProject.h"

FrmNewProject::FrmNewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmNewProject)
{
    ui->setupUi(this);
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));
}

FrmNewProject::~FrmNewProject()
{
    delete ui;
}

QString FrmNewProject::getProjectName() {
    return projectName;
}

QString FrmNewProject::getProjectDirectory() {
    return projectDirectory;
}

void FrmNewProject::ok() {
    projectName = ui->txtProjectName->text();
    projectDirectory = ui->txtProjectDirectory->text();
    accept();
}

void FrmNewProject::browse() {
    projectDirectory = QFileDialog::getExistingDirectory(this, "Project Directory");
    if (projectDirectory != "") {
        ui->txtProjectDirectory->setText(projectDirectory);
    }
}
