#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextDocument>
#include <QScrollBar>
#include <QFontDialog>
#include <QColorDialog>
#include <QColor>
#include <QUrl>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buildFindWidget();  //创建查找窗口

    //创建帮助对话框
    createHelpDialog();

    QFont font; //初始化设置字体大小
    font.setPointSize(12);
    ui->textEdit->setFont(font);
//    ui->textEdit->verticalScrollBar()->show();

    //文件菜单
    connect(ui->newFileAction,SIGNAL(triggered()),this,SLOT(newFileSlot()));
    connect(ui->openFileAction,SIGNAL(triggered()),this,SLOT(openFileSlot()));
    connect(ui->saveFileAction,SIGNAL(triggered()),this,SLOT(saveFileSlot()));
    connect(ui->printFileAction,SIGNAL(triggered()),this,SLOT(printFileSlot()));
    connect(ui->exitAction,SIGNAL(triggered()),this,SLOT(exitSlot()));

    //编辑菜单
    connect(ui->undoAction,SIGNAL(triggered()),ui->textEdit,SLOT(undo()));
    connect(ui->cutAction,SIGNAL(triggered()),ui->textEdit,SLOT(cut()));
    connect(ui->copyAction,SIGNAL(triggered()),ui->textEdit,SLOT(copy()));
    connect(ui->pasteAction,SIGNAL(triggered()),ui->textEdit,SLOT(paste()));
    connect(ui->deleteAction,SIGNAL(triggered()),this,SLOT(deleteSlot()));
    connect(ui->findAction,SIGNAL(triggered()),this,SLOT(findSlot()));
    connect(ui->replaceAction,SIGNAL(triggered()),this,SLOT(replaceSlot()));
    connect(ui->selecteAllAction,SIGNAL(triggered()),ui->textEdit,SLOT(selectAll()));
    connect(ui->datetimeAciton,SIGNAL(triggered()),this,SLOT(datetimeSlot()));

    //格式
    connect(ui->fontAction,SIGNAL(triggered()),this,SLOT(fontSlot()));
    connect(ui->colorAction,SIGNAL(triggered()),this,SLOT(colorSlot()));

    //帮助
    connect(ui->helpAction,SIGNAL(triggered()),this,SLOT(aboutHelpSlot()));
    connect(ui->aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));    //关于QT
    connect(ui->aboutWebsiteAction,SIGNAL(triggered()),this,SLOT(aboutWebsiteSlot()));
    connect(ui->updateAction,SIGNAL(triggered()),this,SLOT(updateDialogSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete findWidget;
}

void MainWindow::newFileSlot()
{
    ui->textEdit->clear();
    saveFileName = "";
}

void MainWindow::openFileSlot()
{
    saveFileName = QFileDialog::getOpenFileName(this,tr("打开文件"));
    if(saveFileName.isEmpty())
        return;

    //打开文件
    QFile file(saveFileName);
    if(file.open(QFile::ReadOnly))  //只读方式打开
    {
        ui->textEdit->clear();  //首先将text控件清空
        QTextStream stream(&file);
        ui->textEdit->setText(stream.readAll());
//        while(!stream.atEnd())
//        {
//              text.append(stream.readLine()); //在text追加文件内容
//        }
        file.close();
    }
    else
    {
        //打开失败
        QMessageBox::critical(this,tr("error"),file.errorString());
        exit(0);
    }
}

void MainWindow::saveFileSlot()
{
    if(ui->textEdit->toPlainText().isEmpty())   //内容为空 不保存
        return;
    if(saveFileName.isEmpty())  //如果saveFileName为空 ,说明是新建的文件
    {
        this->saveAsFileSlot();
    }
    else
    {
        QFile file(saveFileName);
        if(file.open(QFile::WriteOnly | QFile::Truncate))   //以写的方式打开文件 若文件有内容 则追加内容
        {
            QTextStream stream(&file);
            stream<<ui->textEdit->toPlainText();    //将text的内容转换为QString后，写入文件
            file.close();
        }
        else
        {
            QMessageBox::critical(this,tr("error"),file.errorString());
            exit(0);
        }
    }
}

void MainWindow::saveAsFileSlot()
{
    QString filename = QFileDialog::getSaveFileName(this,tr("另存为"));
    if(filename.isEmpty())
        return;
    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate))   //以写的方式打开文件 若文件有内容 则追加内容
    {
        QTextStream stream(&file);
        stream<<ui->textEdit->toPlainText();    //将text的内容转换为QString后，写入文件
        file.close();
    }
    else
    {
        QMessageBox::critical(this,tr("error"),file.errorString());
        exit(0);
    }
}

void MainWindow::exitSlot()
{
    this->close();
}

void MainWindow::printFileSlot()
{
    //QPrintDialog
}

void MainWindow::deleteSlot()
{
}

void MainWindow::findSlot()
{
    findWidget->show();
}

void MainWindow::replaceSlot()
{

}

void MainWindow::datetimeSlot()
{
    QDateTime current = QDateTime::currentDateTime();
    QString time = current.toString("hh:mm yyyy/M/dd");
    ui->textEdit->append(time);
}

void MainWindow::findCancelSlot()
{
    findWidget->close();
}

void MainWindow::fontSlot()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok);
    if(ok)
        ui->textEdit->setFont(font);

}

void MainWindow::colorSlot()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if(color.isValid())
    {
        //如果颜色有效的话，
        ui->textEdit->setTextColor(color);
    }
}

void MainWindow::aboutHelpSlot()
{
    aboutDialog->exec();    //非模式对话框
//    aboutDialog->show();    //模式对话框
}

void MainWindow::aboutButtonSlot()
{
    aboutDialog->close();
}

void MainWindow::aboutWebsiteSlot()
{
    //QDesktopService 桌面服务
    QDesktopServices::openUrl(QUrl("http://www.baidu.com"));
}

void MainWindow::updateDialogSlot()
{
    updateDialog1 = new updateDialog(this);
    updateDialog1->exec();
}

void MainWindow::findNextSlot()
{
    QString str = findLineEdit->text();
    ui->textEdit->find(str);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //查看qt助帮文档 QMessageBox
    if(ui->textEdit->document()->isModified())  //textEdit内容已经被修改
    {
        QMessageBox msgBox;
        msgBox.setText("文件已经变更了");
        msgBox.setInformativeText("您是否要保存文件");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();    //执行QMessageBox

        switch (ret) {
          case QMessageBox::Save:
              // Save was clicked
            this->saveFileSlot();
              break;
          case QMessageBox::Discard:
              // Don't Save was clicked
            event->accept();
              break;
          case QMessageBox::Cancel:
              // Cancel was clicked
            event->ignore();
              break;
          default:
              // should never be reached
            event->ignore();
              break;
        }
    }
    else
    {
        event->accept();
    }
}

void MainWindow::buildFindWidget()
{
    findWidget = new QWidget;
    findWidget->hide();
    QLabel *findLabel = new QLabel(tr("查找内容："));
    findLineEdit = new QLineEdit;
    QPushButton *findnextButton = new QPushButton(tr("查找下一个"));
    QPushButton *findcancelButton = new QPushButton(tr("取消"));
    checkBox = new QCheckBox(tr("区分大小写"));
    radioButton1 = new QRadioButton(tr("向上"));
    radioButton2 = new QRadioButton(tr("向下"));
    radioButton2->setEnabled(true);
    QHBoxLayout *findLayout = new QHBoxLayout;
    findLayout->addWidget(findLabel);
    findLayout->addWidget(findLineEdit);
    QVBoxLayout *btnLayout = new QVBoxLayout;
    btnLayout->addWidget(findnextButton);
    btnLayout->addWidget(findcancelButton);
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(checkBox); hboxLayout->addWidget(radioButton1); hboxLayout->addWidget(radioButton2);
    QGridLayout *mainLayout = new QGridLayout(findWidget);
    mainLayout->addLayout(findLayout,0,0);
    mainLayout->addLayout(btnLayout,0,1);
    mainLayout->addLayout(hboxLayout,1,0);
    connect(findnextButton,SIGNAL(clicked()),this,SLOT(findNextSlot()));
    connect(findcancelButton,SIGNAL(clicked()),this,SLOT(findCancelSlot()));
}

void MainWindow::createHelpDialog()
{
    aboutDialog = new QDialog(this);    //使用模式对话框
    aboutDialog->resize(500,300);
    aboutDialog->setWindowTitle(tr("关于“记事本”"));
    QVBoxLayout *layout = new QVBoxLayout(aboutDialog); //整体布局
    QHBoxLayout *layout1 = new QHBoxLayout; //第一个布局
    QLabel *label1 = new QLabel(tr("Windows10"));
    QFont font;
    font.setBold(true);
    font.setPointSize(20);
    label1->setFont(font);  //设置字体
    layout->setMargin(10);  //布局总各窗体的显示边距
    layout1->addWidget(label1);
    layout1->setAlignment(Qt::AlignHCenter);    //调为居中
    layout->addLayout(layout1);

//    QSplitter *split = new QSplitter;
//    layout->addWidget(split);

    QLabel *label2 = new QLabel;
    label2->setText(tr("Microsoft Windows\r\n版本 1709\r\n@ 2017 Microsoft Corporation。保留所有权利。\r\nWindows 10专业版 操作系统极其用户界面受美国和其他国家/地区的商标和\r\n其他待颁布或已颁布的知识产权法保护。\r\n\r\n\r\n\r\n\r\n\r\n根据 Microsoft 软件许可条款，许可如下用户使用本产品：\r\n\r\n  Windows 用户"));
    QHBoxLayout *layout2 = new QHBoxLayout;
    layout2->addStretch();  //加入占位符
    aboutButton = new QPushButton(tr("确定"));
    connect(aboutButton,SIGNAL(clicked()),this,SLOT(aboutButtonSlot()));
    layout2->addWidget(aboutButton);
    layout->addWidget(label2);
    layout->addStretch();
    layout->addLayout(layout2);
}


