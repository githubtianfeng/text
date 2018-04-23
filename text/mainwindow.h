#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QCheckBox>
#include <QDialog>
#include "updatedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    void buildFindWidget();
    void createHelpDialog();
private:
    Ui::MainWindow *ui;
    QString saveFileName;   //要保存文件的名字


private:
    QWidget *findWidget;    //查找窗口
    QLineEdit *findLineEdit;
    QCheckBox *checkBox;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;

    QDialog *aboutDialog;   //帮助关于对话框
    QPushButton *aboutButton;  //帮助关于按钮
    updateDialog *updateDialog1;
private slots:
    void newFileSlot();
    void openFileSlot();
    void saveFileSlot();
    void saveAsFileSlot();
    void exitSlot();
    void printFileSlot();

    void deleteSlot();
    void findSlot();
    void replaceSlot();
    void datetimeSlot();

    void findNextSlot();
    void findCancelSlot();

    void fontSlot();
    void colorSlot();

    void aboutHelpSlot();   //帮助
    void aboutButtonSlot(); //帮助按钮
    void aboutWebsiteSlot();    //打开一个网站，使用默认浏览器
    void updateDialogSlot();    //更新
};

#endif // MAINWINDOW_H
