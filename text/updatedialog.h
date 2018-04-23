#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>
#include <QMovie>

namespace Ui {
class updateDialog;
}

class updateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit updateDialog(QWidget *parent = 0);
    ~updateDialog();

private:
    QMovie *movie;
private:
    Ui::updateDialog *ui;
private slots:
    void confirmButtonSlot();
};

#endif // UPDATEDIALOG_H
