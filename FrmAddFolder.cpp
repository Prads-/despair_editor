/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "FrmAddFolder.h"
#include "ui_FrmAddFolder.h"

FrmAddFolder::FrmAddFolder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmAddFolder)
{
    ui->setupUi(this);
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(ok()));
}

FrmAddFolder::~FrmAddFolder()
{
    delete ui;
}

void FrmAddFolder::ok() {
    name = ui->txtFolderName->text();
    accept();
}

QString FrmAddFolder::getName() {
    return name;
}
