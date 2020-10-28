#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settingwindow.h"
#include "block.h"
#include "scorewindow.h"
#include <QTimer>
#include <QLCDNumber>

enum gameMode{Beginner,Intermediate,Expert};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    int size = 20;
    int offSet = 5;
    block *blk;
    QTimer *runTime;
    gameMode mode;
    QLCDNumber *mine_lcd;
    QLCDNumber *time_lcd;

public:
    settingWindow *setting;
    scoreWindow *score;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void costomSet(int row,int col,int boom);

public slots:
    void secTime();

private slots:
    void on_action_New_triggered();

    void on_action_Beginner_triggered();

    void on_action_Intermediate_triggered();

    void on_action_Expert_triggered();

    void on_action_Custom_triggered();

    void on_action_Exit_triggered();

    void on_action_Rules_triggered();

    void on_action_About_triggered();

    void on_action_score_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
