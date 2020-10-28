#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QMainWindow>

namespace Ui {
class scoreWindow;
}

class scoreWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit scoreWindow(QWidget *parent = 0);
    ~scoreWindow();

private:
    Ui::scoreWindow *ui;
};

#endif // SCOREWINDOW_H
