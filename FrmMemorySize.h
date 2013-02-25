#ifndef FRMMEMORYSIZE_H
#define FRMMEMORYSIZE_H

#include <QDialog>

namespace Ui {
class FrmMemorySize;
}

class FrmMemorySize : public QDialog
{
    Q_OBJECT
    
public:
    explicit FrmMemorySize(QWidget *parent = 0, int dataSpaceSize = 0, int stackSpaceSize = 0);
    ~FrmMemorySize();

    int getDataSpaceSize();
    int getStackSpaceSize();
    
private:
    Ui::FrmMemorySize *ui;
    int dataSpaceSize, stackSpaceSize;

private slots:
    void ok();
};

#endif // FRMMEMORYSIZE_H
