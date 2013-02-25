/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include <QtGui>
#include <QFileDialog>
#include "FrmNewSource.h"
#include "ui_frmNewSource.h"

FrmNewSource::FrmNewSource(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmNewSource)
{
    ui->setupUi(this);
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));
}

FrmNewSource::~FrmNewSource()
{
    delete ui;
}

QString FrmNewSource::getName() {
    return name;
}

QString FrmNewSource::getSrcPath() {
    return srcPath;
}

bool FrmNewSource::addExistingFile() {
    return addExisting;
}

void FrmNewSource::ok() {
    name = ui->txtSourceName->text();
    srcPath = ui->txtSrcPath->text();
    addExisting = ui->chkAddExisting->isChecked();
    accept();
}

void FrmNewSource::browse() {
    QString path = QFileDialog::getOpenFileName(this, "Add Existing Source", "", "despairSource(*.dsrc)");
    if (path != "") {
        ui->txtSrcPath->setText(path);
        ui->chkAddExisting->setChecked(true);
    }
}
