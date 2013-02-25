/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMFRAMELENGTH_H
#define FRMFRAMELENGTH_H

#include <QDialog>

namespace Ui {
class FrmFrameLength;
}

class FrmFrameLength : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmFrameLength(QWidget *parent = 0, int width = 512, int height = 512);
    ~FrmFrameLength();

    int getWidth();
    int getHeight();
    
private:
    Ui::FrmFrameLength *ui;
    int width, height;

private slots:
    void ok();
};

#endif // FRMFRAMELENGTH_H
