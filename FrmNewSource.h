/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMNEWSOURCE_H
#define FRMNEWSOURCE_H

#include <QDialog>

namespace Ui {
class FrmNewSource;
}

class FrmNewSource : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmNewSource(QWidget *parent = 0);
    ~FrmNewSource();

    QString getName();
    QString getSrcPath();
    bool addExistingFile();

private:
    Ui::FrmNewSource *ui;
    QString name, srcPath;
    bool addExisting;

private slots:
    void ok();
    void browse();
};

#endif // FRMNEWSOURCE_H
