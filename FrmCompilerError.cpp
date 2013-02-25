/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "FrmCompilerError.h"
#include "ui_FrmCompilerError.h"

FrmCompilerError::FrmCompilerError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmCompilerError)
{
    ui->setupUi(this);
}

FrmCompilerError::~FrmCompilerError()
{
    delete ui;
}

void FrmCompilerError::setErrorString(QString errorString) {
     ui->txtError->setPlainText(errorString);
}
