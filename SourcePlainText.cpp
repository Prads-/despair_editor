/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#include "SourcePlainText.h"
#include "FrmFindAndReplace.h"

SourcePlainText::SourcePlainText(QWidget *parent = 0) : QPlainTextEdit(parent) {
    findAndReplaceDialog = new FrmFindAndReplace(this);
    findAndReplaceDialog->setModal(false);
}

SourcePlainText::~SourcePlainText() {
    delete findAndReplaceDialog;
}

void SourcePlainText::returnKeyIdent() {
    QTextCursor cursor = this->textCursor();
    int position = cursor.position();
    QString sourceCode = this->toPlainText();
    QString upper = sourceCode.mid(0, position), tabs = "";
    int lineStart;

    for (lineStart = position - 2; lineStart >= 0; --lineStart) {
        if (sourceCode[lineStart] == '\n') {
            ++lineStart;
            break;
        }
    }

    if (lineStart > 0) {
        while(sourceCode[lineStart++] == '\t') {
            tabs.push_back('\t');
        }
    }

    this->insertPlainText(tabs);
}

void SourcePlainText::keyPressEvent(QKeyEvent *event) {
    QPlainTextEdit::keyPressEvent(event);
    if (event->key() == Qt::Key_Return) {
        returnKeyIdent();
    }
}

void SourcePlainText::findAndReplace() {
    findAndReplaceDialog->show();
}
