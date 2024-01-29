#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
#include <QMainWindow>
#include <boardwithgame.h>
#include <board5x5.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void signalOffSpeedMode(int arg1);

private slots:
    void on_startButton_clicked();

    void on_scoreButton_clicked();

    void on_exitButton_clicked();


private:
    Ui::MainWindow *ui;
    boardWithgame *board;
    board5x5 *board5;
    const QString name = "highscore.txt";
    std::ifstream fin;
    std::string line;
    int maxScore = 0;
    int speedMode_toogle = 0;
};

#endif // MAINWINDOW_H
