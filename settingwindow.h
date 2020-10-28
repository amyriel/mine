#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QMainWindow>

namespace Ui {
class settingWindow;
}

class settingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit settingWindow(QWidget *parent = 0);
    ~settingWindow();

private slots:

    void on_setting_button_cancel_clicked();

    void on_setting_button_ok_clicked();

signals:
    void cancelSignal();
    void yesSignal(int row,int col,int boom);

private:
    Ui::settingWindow *ui;
};

#endif // SETTINGWINDOW_H
