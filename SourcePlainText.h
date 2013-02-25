/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef _SOURCE_PLAIN_TEXT_H
#define _SOURCE_PLAIN_TEXT_H

#include <QtGui>
#include <QPlainTextEdit>

class FrmFindAndReplace;

class SourcePlainText : public QPlainTextEdit {
private:
    FrmFindAndReplace *findAndReplaceDialog;

    void returnKeyIdent();
protected:
    void keyPressEvent(QKeyEvent *event);
public:
    SourcePlainText(QWidget *parent);
    ~SourcePlainText();

    void findAndReplace();
};

#endif // _SOURCE_PLAIN_TEXT_H
