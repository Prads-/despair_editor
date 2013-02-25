/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMFINDANDREPLACE_H
#define FRMFINDANDREPLACE_H

#include <QDialog>

namespace Ui {
class FrmFindAndReplace;
}

class SourcePlainText;

class FrmFindAndReplace : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmFindAndReplace(QWidget *parent = 0);
    ~FrmFindAndReplace();
    
private:
    Ui::FrmFindAndReplace *ui;
    SourcePlainText *srcPlainText;

    bool find();

private slots:
    bool findNext();
    void findAndReplace();
    void replaceAll();
};

#endif // FRMFINDANDREPLACE_H
