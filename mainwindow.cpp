#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setting = new settingWindow;
    this->setting->setFixedSize(500,400);
    this->setting->setWindowTitle("自定义");
    connect(this->setting,&settingWindow::yesSignal,this,&MainWindow::costomSet);
    //this->setting->hide();

    this->score = new scoreWindow;
    this->score->setFixedSize(300,300);
    this->score->setWindowTitle("最高分");
    //blk = new block(9,9,10);

    costomSet(9,9,10);
    runTime = new QTimer(this);
    connect(runTime,SIGNAL(timeout()),this,SLOT(secTime()));

    mine_lcd = new QLCDNumber(this);
    mine_lcd->setDigitCount(3);
    mine_lcd->setMode(QLCDNumber::Dec);
    //mine_lcd->setStyle("color: red; background: black;");
    time_lcd = new QLCDNumber(this);
    time_lcd->setDigitCount(3);
    time_lcd->setMode(QLCDNumber::Dec);
    //time_lcd->setStyle("color: red; background: black;");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //绘制计时器
    mine_lcd->setGeometry(5,35,50,24);
    mine_lcd->display(blk->boom);
    time_lcd->setGeometry(blk->col*size-45,35,50,24);
    time_lcd->display(blk->timeNum);

    //绘制表情图标
    if(blk->winNum == 1)
    {
        painter.drawPixmap(blk->col*size/2-15,35,QPixmap("../images/face1.jpg"));
    }
    if(blk->winNum == 2)
    {
        painter.drawPixmap(blk->col*size/2-15,35,QPixmap("../images/face4.jpg"));
    }
    if(blk->winNum == 0)
    {
        painter.drawPixmap(blk->col*size/2-15,35,QPixmap("../images/face2.jpg"));
    }
    //绘制雷区
    for(int i=0 ; i<blk->row ; i++)
    {
        for(int j=0 ; j<blk->col ; j++)
        {
            if(blk->p[i][j]>=99)
            {
                painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/unclicked.jpg"));
            }
            if(blk->p[i][j]>=0 && blk->p[i][j]<9)
            {
                switch (blk->p[i][j])
                {

                case 0:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/clicked.jpg"));
                    break;
                case 1:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num1.jpg"));
                    break;
                case 2:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num2.jpg"));
                    break;
                case 3:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num3.jpg"));
                    break;
                case 4:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num4.jpg"));
                    break;
                case 5:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num5.jpg"));
                    break;
                case 6:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num6.jpg"));
                    break;
                case 7:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num7.jpg"));
                    break;
                case 8:
                    painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/num8.jpg"));
                    break;
                default:
                    break;
                }
            }
            if(blk->p[i][j]>=49 && blk->p[i][j]<=58)
            {
                painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/flag.jpg"));
            }
            if(blk->p[i][j] == -1)
            {
                painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/mine.jpg"));
            }
            if(blk->p[i][j] == -2)
            {
                painter.drawPixmap(j*size+offSet,i*size+64,20,20,QPixmap("../images/not_mine.jpg"));
            }
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int px = event->x();
    int py = event->y();
    int m = (py-offSet-64) / size;
    int n = (px-offSet) / size;

    qDebug() << "m" << m;
    qDebug() << "n" << n;

    if(event->buttons() == (Qt::LeftButton|Qt::RightButton))
    {
        if(blk->clicklr(m,n))
            update();
    }
    else if(event->button() == Qt::LeftButton)
    {
        if(blk->click(m,n))
        {
            if(!(runTime->isActive()))
            {
                runTime->start(1000);
            }
            update();
        }
        if(blk->winNum == 0 || blk->winNum == 2)
        {
            if(runTime->isActive())
            {
                runTime->stop();
            }
            if(px>blk->col*size/2-15 && px<blk->row*size/2+15 && py>30 && py<54)
            {
                blk->restart();
                update();
            }
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        if(blk->clickred(m,n))
        {
            update();
        }
    }
}

void MainWindow::costomSet(int row, int col, int boom)
{
    blk = new block(row,col,boom);
    this->setFixedSize(col*size+10,row*size+70);
}

void MainWindow::secTime()
{
    blk->timeNum++;
    update();
}

void MainWindow::on_action_New_triggered()
{
    blk->restart();
}

void MainWindow::on_action_Beginner_triggered()
{
    mode = Beginner;
    costomSet(9,9,10);
}

void MainWindow::on_action_Intermediate_triggered()
{
    mode = Intermediate;
    costomSet(16,16,40);
}

void MainWindow::on_action_Expert_triggered()
{
    mode = Expert;
    costomSet(16,30,99);
}

void MainWindow::on_action_Custom_triggered()
{
    this->setting->show();
}

void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

void MainWindow::on_action_Rules_triggered()
{
    QMessageBox::information(this,"规则","九宫格中间的数字表示周围的格子一共有多少个雷\n"
                                       "左键翻开\n"
                                       "右键标记");
}

void MainWindow::on_action_About_triggered()
{
    QMessageBox::information(this,"关于","made by\n"
                                       "朱铭泽\n"
                                       "薛瑞琦");
}

void MainWindow::on_action_score_triggered()
{

}
