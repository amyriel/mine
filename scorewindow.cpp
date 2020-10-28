#include "scorewindow.h"
#include "ui_scorewindow.h"

scoreWindow::scoreWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::scoreWindow)
{
    ui->setupUi(this);
}

scoreWindow::~scoreWindow()
{
    delete ui;
}
