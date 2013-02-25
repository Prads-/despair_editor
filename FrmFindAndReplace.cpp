/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "FrmFindAndReplace.h"
#include "ui_FrmFindAndReplace.h"
#include "SourcePlainText.h"
#include <QMessageBox>

FrmFindAndReplace::FrmFindAndReplace(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmFindAndReplace)
{
    ui->setupUi(this);
    srcPlainText = (SourcePlainText*)parent;

    connect(ui->btnFindAndReplace, SIGNAL(clicked()), this, SLOT(findAndReplace()));
    connect(ui->btnFindNext, SIGNAL(clicked()), this, SLOT(findNext()));
    connect(ui->btnReplaceAll, SIGNAL(clicked()), this, SLOT(replaceAll()));
}

FrmFindAndReplace::~FrmFindAndReplace()
{
    delete ui;
}

bool FrmFindAndReplace::find() {
    QString findString = ui->txtFind->text();
    int findFlag = 0;

    if (ui->chkCase->isChecked()) {
        findFlag = QTextDocument::FindCaseSensitively;
    }
    if (ui->chkWholeWord->isChecked()) {
        findFlag |= QTextDocument::FindWholeWords;
    }

    if (!srcPlainText->find(findString, (QTextDocument::FindFlag)findFlag)) {
        srcPlainText->moveCursor(QTextCursor::Start);
        if (!srcPlainText->find(findString, (QTextDocument::FindFlag)findFlag)) {
            return false;
        }
    }
    return true;
}

bool FrmFindAndReplace::findNext() {
    if (!find()) {
        QString msg = "Cannot find \"" + ui->txtFind->text() + "\"";
        QMessageBox::information(this, "Find and Replace", msg, QMessageBox::Ok);
        return false;
    }
    return true;
}

void FrmFindAndReplace::findAndReplace() {
    if (findNext()) {
        QString replaceString = ui->txtReplace->text();
        srcPlainText->insertPlainText(replaceString);
    }
}

void FrmFindAndReplace::replaceAll() {
    QString replaceString = ui->txtReplace->text();
    int replaceCount = 0;

    srcPlainText->moveCursor((QTextCursor::Start));
    while(find()) {
        srcPlainText->insertPlainText(replaceString);
        ++replaceCount;
    }

    QString msg;
    msg = msg.setNum(replaceCount) + " occurance replaced";

    QMessageBox::information(this, "Find and Replace", msg, QMessageBox::Ok);
}
