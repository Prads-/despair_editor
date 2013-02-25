#include "FrmMemorySize.h"
#include "ui_FrmMemorySize.h"

FrmMemorySize::FrmMemorySize(QWidget *parent, int dataSpaceSize, int stackSpaceSize) :
    QDialog(parent),
    ui(new Ui::FrmMemorySize)
{
    ui->setupUi(this);
    this->dataSpaceSize = dataSpaceSize;
    this->stackSpaceSize = stackSpaceSize;
    ui->txtDataSpaceSize->setText(QString::number(dataSpaceSize));
    ui->txtStackSpaceSize->setText(QString::number(stackSpaceSize));

    connect(ui->btnOk, SIGNAL(clicked()), this, SLOT(ok()));
    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
}

FrmMemorySize::~FrmMemorySize()
{
    delete ui;
}

int FrmMemorySize::getDataSpaceSize() {
    return dataSpaceSize;
}

int FrmMemorySize::getStackSpaceSize() {
    return stackSpaceSize;
}

void FrmMemorySize::ok() {
    dataSpaceSize = ui->txtDataSpaceSize->text().toInt();
    stackSpaceSize = ui->txtStackSpaceSize->text().toInt();
    accept();
}
