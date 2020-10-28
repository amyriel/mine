#include "settingwindow.h"
#include "ui_settingwindow.h"

settingWindow::settingWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::settingWindow)
{
    ui->setupUi(this);
}

settingWindow::~settingWindow()
{
    delete ui;
}

void settingWindow::on_setting_button_cancel_clicked()
{
    this->close();
    emit cancelSignal();
}

void settingWindow::on_setting_button_ok_clicked()
{
    emit yesSignal(ui->spinBox_row->value(),ui->spinBox_col->value(),ui->spinBox_m->value());
    this->close();
}
