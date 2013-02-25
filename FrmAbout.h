/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMABOUT_H
#define FRMABOUT_H

#include <QDialog>

namespace Ui {
class FrmAbout;
}

class FrmAbout : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmAbout(QWidget *parent = 0);
    ~FrmAbout();
    
private:
    Ui::FrmAbout *ui;
};

#endif // FRMABOUT_H
