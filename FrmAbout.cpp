/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "FrmAbout.h"
#include "ui_FrmAbout.h"

FrmAbout::FrmAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmAbout)
{
    ui->setupUi(this);
    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(accept()));
}

FrmAbout::~FrmAbout()
{
    delete ui;
}
