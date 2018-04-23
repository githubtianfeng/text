#include "updatedialog.h"
#include "ui_updatedialog.h"
#include <QDebug>

updateDialog::updateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("更新");
    //加载动画
    movie = new QMovie("fengjing.gif");
 //   qDebug()<<movie->frameCount();    //输出帧数
    ui->label->setMovie(movie);
    movie->start();
    connect(ui->confirmButton,SIGNAL(clicked()),this,SLOT(confirmButtonSlot()));
}

updateDialog::~updateDialog()
{
    delete ui;
}

void updateDialog::confirmButtonSlot()
{
    this->close();
}
