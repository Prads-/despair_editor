/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMCOMPILERERROR_H
#define FRMCOMPILERERROR_H

#include <QDialog>

namespace Ui {
class FrmCompilerError;
}

class FrmCompilerError : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmCompilerError(QWidget *parent = 0);
    ~FrmCompilerError();
      
    void setErrorString(QString errorString);
private:
    Ui::FrmCompilerError *ui;
};

#endif // FRMCOMPILERERROR_H
