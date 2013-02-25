/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMADDFOLDER_H
#define FRMADDFOLDER_H

#include <QDialog>

namespace Ui {
class FrmAddFolder;
}

class FrmAddFolder : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmAddFolder(QWidget *parent = 0);
    ~FrmAddFolder();
    
    QString getName();

private:
    Ui::FrmAddFolder *ui;
    QString name;

private slots:
    void ok();
};

#endif // FRMADDFOLDER_H
