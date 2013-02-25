/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "FrmFrameLength.h"
#include "ui_FrmFrameLength.h"

FrmFrameLength::FrmFrameLength(QWidget *parent, int width, int height) :
    QDialog(parent),
    ui(new Ui::FrmFrameLength)
{
    ui->setupUi(this);

    this->width = width;
    this->height = height;

    ui->txtWidth->setText(QString::number(width));
    ui->txtHeight->setText(QString::number(height));

    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

FrmFrameLength::~FrmFrameLength()
{
    delete ui;
}

void FrmFrameLength::ok() {
    width = ui->txtWidth->text().toInt();
    height = ui->txtHeight->text().toInt();
    accept();
}

int FrmFrameLength::getWidth() {
    return width;
}

int FrmFrameLength::getHeight() {
    return height;
}
