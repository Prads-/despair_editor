/*
    Written By Pradipna Nepal
    www.pradsprojects.com

    Copyright (C) 2013 Pradipna Nepal
    Please read COPYING.txt included along with this source code for more detail.
    If not included, see http://www.gnu.org/licenses/
*/

#ifndef FRMNEWPROJECT_H
#define FRMNEWPROJECT_H

#include <QDialog>

namespace Ui {
class FrmNewProject;
}

class FrmNewProject : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmNewProject(QWidget *parent = 0);
    ~FrmNewProject();
    
    QString getProjectName();
    QString getProjectDirectory();

private:
    Ui::FrmNewProject *ui;
    QString projectName, projectDirectory;

private slots:
    void ok();
    void browse();
};

#endif // FRMNEWPROJECT_H
