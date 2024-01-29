#ifndef BOARD5X5_H
#define BOARD5X5_H
#include <iostream>
#include <QDialog>
#include <QLineEdit>
#include <QKeyEvent>
#include <fstream>
#include <QDebug>
#include <QPropertyAnimation>
#include <QPixmap>


namespace Ui {
class board5x5;
}

class board5x5 : public QDialog
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *e) override; //управление игрой с клавиатуры


public:
    explicit board5x5(QWidget *parent = 0);
    ~board5x5();
    bool isEnd();
    void plateMoveAnimation(QLineEdit *lineedit);
    void setAllOnDefaultPos();
    void qleadd();
    void winCheck();
    void moveWithoutAddition(int lineGenerator, int j);
    void moveWithAddition(int lineGenerator, int j);
    void spawnPlate(int lineGenerator);
    void spawnAllPlates();
    void gameEnd();
    void stepBackAdd();
    void stepBackBack();
    void moveLeft(int k);
    void moveRight(int k);
    void moveDown(int k);
    void moveUp(int k);
    int speedMode_toogle = 0;
    void setStyleSheet();

private slots:
    void on_exitButton_clicked();
    void on_resetButton_clicked();
    void on_stepBackButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::board5x5 *ui;
    int score = 0;
    QList<QLineEdit*> qle_list;
    int stepBack_list[16];
    int reserveStepBack_list[16];
    int rearrangmentCounter = 0; //счётчик, отвечающий за перестановки плашек
    int spawnCounter = 0; //счётчик, отвечающий за рандомный спавн плашек
    const QString name = "highscore.txt";  //название файла с максимальным счётом
    std::ofstream fout;    //поток вывода
    QPropertyAnimation *animation;

};


#endif // BOARD5X5_H
