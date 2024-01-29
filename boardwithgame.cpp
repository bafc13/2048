#include "boardwithgame.h"
#include "ui_boardwithgame.h"
#include <QMessageBox>
#include <random>
#include <QDebug>
#include <QLineEdit>
#include <QRect>
#include <QMovie>
#include <QPalette>
#include <QColor>

std::default_random_engine generator;
std::uniform_int_distribution<int>
randPlateIndexGenerator(0,15);

int winCounter = 0; //счётчик, для контроля выйгрыша(единовременного)

boardWithgame::boardWithgame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::boardWithgame)
{
    QMovie *movie = new QMovie(":/new/prefix1/img/4Cb2.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
    movie->start();
    ui->setupUi(this);
    setWindowTitle("board");
    ui->liveScore->setText(QString::number(0));//обнуление очков
    qleadd();//добавление плашек в список
    stepBackAdd();//добавление плашек в список, для восстановления значений на шаг назад
    qle_list.at(randPlateIndexGenerator(generator))->setText("2");
    qle_list.at(randPlateIndexGenerator(generator))->setText("2");
    setStyleSheet();
    setcolor();

}

void boardWithgame::plateMoveAnimation(QLineEdit *lineedit)
{
    if(speedMode_toogle == 0){
    animation = new QPropertyAnimation(lineedit, "geometry");
    animation->setDuration(30);
    animation->setStartValue(lineedit->geometry());
    animation->setKeyValueAt(0.5,QRect(lineedit->x()-50, lineedit->y()-50,lineedit->width()-25,lineedit->height()-25));
    animation->setEndValue(lineedit->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

boardWithgame::~boardWithgame()
{
    delete ui;
}

void boardWithgame::qleadd()
{
    qle_list.append(ui->plate1);
    qle_list.append(ui->plate2);
    qle_list.append(ui->plate3);
    qle_list.append(ui->plate4);
    qle_list.append(ui->plate5);
    qle_list.append(ui->plate6);
    qle_list.append(ui->plate7);
    qle_list.append(ui->plate8);
    qle_list.append(ui->plate9);
    qle_list.append(ui->plate10);
    qle_list.append(ui->plate11);
    qle_list.append(ui->plate12);
    qle_list.append(ui->plate13);
    qle_list.append(ui->plate14);
    qle_list.append(ui->plate15);
    qle_list.append(ui->plate16);
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setStyleSheet("font-size: 41px;");
        qle_list.at(i)->setReadOnly(true);
    }
}

void boardWithgame::setAllOnDefaultPos()
{
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setGeometry(qle_list.at(i)->x(), qle_list.at(i)->y(), 100,100);
    }
}

void boardWithgame::on_exitButton_clicked()
{
    close();
}

void boardWithgame::on_resetButton_clicked()
{
    score = 0;
    ui->liveScore->setText(QString::number(score));
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setText("");
    }
    qle_list.at(randPlateIndexGenerator(generator))->setText("2");
    qle_list.at(randPlateIndexGenerator(generator))->setText("2");
}

void boardWithgame::on_stepBackButton_clicked()
{
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setText(QString::number(stepBack_list[i]));
        if(stepBack_list[i] == 0){
            qle_list.at(i)->setText("");
        }
    }
}


bool boardWithgame::isEnd()
{
    int k = 0;
    for(int i = 0; i < 16; i++){
        if(qle_list.at(i)->text() != ""){
            k++;}}
    if(k == 16){
        return 1;
    } else {return 0;}
}

void boardWithgame::gameEnd()
{
    if(rearrangmentCounter == 0 && boardWithgame::isEnd() == 1){
        for(int i = 0; i < 16; i++){
            stepBack_list[i] = reserveStepBack_list[i];
        }
        QMessageBox *mes = new QMessageBox;
        mes->setText("You lost! Restart da game! Or try the other side ;)");
        mes->exec();
        fout.open(name.toStdString(),std::ios_base::app);
        fout << score << "\n";
        fout.close();
    }
}

void boardWithgame::stepBackAdd()
{
    for(int i = 0; i < 16; i++){
        reserveStepBack_list[i] = stepBack_list[i];
    }
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = qle_list.at(i)->text().toInt();
    }
}

void boardWithgame::stepBackBack()
{
    for(int i = 0; i < 16; i++){
        stepBack_list[i] = reserveStepBack_list[i];
    }
}


void boardWithgame::winCheck()
{
    for(int i = 0; i < 16; i++){
        ui->liveScore->setText(QString::number(score));
        if(qle_list.at(i)->text() == "2048" && winCounter == 0){
            for(int i = 0; i < 16; i++){
                stepBack_list[i] = reserveStepBack_list[i];
            }
            QMessageBox *mes = new QMessageBox;
            mes->setText("You won! Congratilations! You can continue, u play endless mode");
            mes->exec();winCounter++;
        }}
}

void boardWithgame::moveWithoutAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    qle_list.at(k)->setText(qle_list.at(j)->text());
    qle_list.at(j)->setText("");
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
}

void boardWithgame::moveWithAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    score += qle_list.at(k)->text().toInt() * 2;
    qle_list.at(k)->setText(QString::number(qle_list.at(k)->text().toInt() + qle_list.at(j)->text().toInt()));
    qle_list.at(j)->setText("");
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
}

void boardWithgame::spawnPlate(int k)
{
    qle_list.at(k)->setText("2");
    spawnCounter++;
}

void boardWithgame::spawnAllPlates()
{
    if(rearrangmentCounter > 0){
        int k;
        while(spawnCounter == 0){
            k = randPlateIndexGenerator(generator);
            if(qle_list.at(k)->text() == ""){
                spawnPlate(k);
            }
        }
    }
}

void boardWithgame::moveLeft(int k) // 1 строка
{
    if(k == 2){
        k = 5;
    } else if(k == 3){
        k = 9;
    } else if(k == 4){
        k = 13;
    }
    if(qle_list.at(k)->text() != ""){//для первой строки
                if(qle_list.at(k - 1)->text() == ""){ //перестановка элементов влево на пустое место
                    moveWithoutAddition(k, k + 1);}
                else if (qle_list.at(k - 1)->text() == qle_list.at(k)->text()){ //перестановка с сложением
                    moveWithAddition(k, k + 1);}}

             if(qle_list.at(k + 1)->text() != "" && qle_list.at(k)->text() == ""){
                if(qle_list.at(k - 1)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k, k + 2);}
                else if(qle_list.at(k - 1)->text() == qle_list.at(k + 1)->text()){ //перестановка с сложением влево
                     moveWithAddition(k, k + 2);}}

             if(qle_list.at(k + 1)->text() != ""){//перестановка на пустое влево
                 if(qle_list.at(k)->text() == ""){
                     moveWithoutAddition(k + 1, k +2);}
                 else if(qle_list.at(k)->text() == qle_list.at(k + 1)->text()){ //перестановка с сложением влево
                      moveWithAddition(k + 1, k + 2);}}

              if(qle_list.at(k + 2)->text() != "" && qle_list.at(k)->text() == "" && qle_list.at(k + 1)->text() == ""){
                  if(qle_list.at(k - 1)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k, k + 3);}
                  else if(qle_list.at(k - 1)->text() == qle_list.at(k + 2)->text()){//перестановка с сложением влево
                    moveWithAddition(k, k + 3);}}

              if(qle_list.at(k + 2)->text() != "" && qle_list.at(k + 1)->text() == ""){
                  if(qle_list.at(k)->text() == ""){ //перестановка на пустое влево
                     moveWithoutAddition(k + 1, k + 3);}
                  else if(qle_list.at(k)->text() == qle_list.at(k + 2)->text()){ //перестановка с сложением  влево
                     moveWithAddition(k + 1, k + 3);}}

            if(qle_list.at(k + 2)->text() != ""){
                if(qle_list.at(k + 1)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k + 2, k + 3);}                                 //6 if`ov
                else if(qle_list.at(k + 1)->text() == qle_list.at(k + 2)->text()){ //перестановка с сложение влево
                    moveWithAddition(k + 2, k + 3);}}
}

void boardWithgame::moveRight(int k)
{
    if(k == 2){
        k = 5;
    } else if(k == 3){
        k = 9;
    } else if(k == 4){
        k = 13;
    }
    if(qle_list.at(k + 1)->text() != ""){//для первой строки
                    if(qle_list.at(k + 2)->text() == ""){
                        moveWithoutAddition(k + 3, k + 2);}
                    else if (qle_list.at(k + 2)->text() == qle_list.at(k + 1)->text()){
                        moveWithAddition(k + 3, k + 2);}}

                 if(qle_list.at(k)->text() != "" && qle_list.at(k + 1)->text() == ""){
                    if(qle_list.at(k + 2)->text() == ""){
                        moveWithoutAddition(k + 3, k + 1);}
                    else if(qle_list.at(k + 2)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 3, k + 1);}}

                 if(qle_list.at(k)->text() != ""){
                     if(qle_list.at(k + 1)->text() == ""){
                        moveWithoutAddition(k + 2, k + 1);}
                     else if(qle_list.at(k + 1)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 2, k + 1);}}

                  if(qle_list.at(k - 1)->text() != "" && qle_list.at(k)->text() == "" && qle_list.at(k + 1)->text() == ""){
                      if(qle_list.at(k + 2)->text() == ""){
                         moveWithoutAddition(k + 3, k);}
                      else if(qle_list.at(k + 2)->text() == qle_list.at(k - 1)->text()){
                          moveWithAddition(k + 3, k);}}

                      if(qle_list.at(k - 1)->text() != "" && qle_list.at(k)->text() == ""){
                          if(qle_list.at(k + 1)->text() == ""){
                             moveWithoutAddition(k + 2, k);}
                          else if(qle_list.at(k + 1)->text() == qle_list.at(k - 1)->text()){
                              moveWithAddition(k + 2, k);}}

                if(qle_list.at(k - 1)->text() != ""){
                    if(qle_list.at(k)->text() == ""){
                        moveWithoutAddition(k + 1, k);}                                 //6 if`ov
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 1, k);}}
}

void boardWithgame::moveDown(int k)
{
    if(qle_list.at(k + 7)->text() != ""){//для первого столбца
                    if(qle_list.at(k + 11)->text() == ""){
                        moveWithoutAddition(k + 12, k + 8);}
                    else if (qle_list.at(k + 11)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k + 12, k + 8);}}

                 if(qle_list.at(k + 3)->text() != "" && qle_list.at(k + 7)->text() == ""){
                    if(qle_list.at(k + 11)->text() == ""){
                        moveWithoutAddition(k + 12, k + 4);}
                    else if(qle_list.at(k + 11)->text() == qle_list.at(k + 3)->text()){
                        moveWithAddition(k + 12, k + 4);}}

                 if(qle_list.at(k + 3)->text() != ""){
                     if(qle_list.at(k + 7)->text() == ""){
                        moveWithoutAddition(k + 8, k + 4);}
                     else if(qle_list.at(k + 7)->text() == qle_list.at(k + 3)->text()){
                        moveWithAddition(k + 8, k + 4);}}

                  if(qle_list.at(k - 1)->text() != "" && qle_list.at(k + 3)->text() == "" && qle_list.at(k + 7)->text() == ""){
                      if(qle_list.at(k + 11)->text() == ""){
                        moveWithoutAddition(k + 12, k);}
                      else if(qle_list.at(k - 1)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k + 12, k);}}

                      if(qle_list.at(k - 1)->text() != "" && qle_list.at(k + 3)->text() == ""){
                          if(qle_list.at(k + 7)->text() == ""){
                             moveWithoutAddition(k + 8, k);}
                          else if(qle_list.at(k - 1)->text() == qle_list.at(k + 7)->text()){
                             moveWithAddition(k + 8, k); }}

                if(qle_list.at(k - 1)->text() != ""){
                    if(qle_list.at(k + 3)->text() == ""){
                        moveWithoutAddition(k + 4, k);}                                 //6 if`ov
                    else if(qle_list.at(k + 3)->text() == qle_list.at(k - 1)->text()){
                        moveWithAddition(k + 4, k);}}
}

void boardWithgame::moveUp(int k)
{
    if(qle_list.at(k + 3)->text() != ""){//для первого столбца
                    if(qle_list.at(k - 1)->text() == ""){
                       moveWithoutAddition(k, k + 4);}
                    else if (qle_list.at(k - 1)->text() == qle_list.at(k + 3)->text()){
                       moveWithAddition(k, k + 4);}}

                 if(qle_list.at(k + 7)->text() != "" && qle_list.at(k + 3)->text() == ""){
                    if(qle_list.at(k - 1)->text() == ""){
                        moveWithoutAddition(k, k + 8);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k, k + 8);}}

                 if(qle_list.at(k + 7)->text() != ""){
                     if(qle_list.at(k + 3)->text() == ""){
                        moveWithoutAddition(k + 4, k + 8);}
                     else if(qle_list.at(k + 3)->text() == qle_list.at(k + 7)->text()){
                        moveWithAddition(k + 4, k + 8);}}

                  if(qle_list.at(k + 11)->text() != "" && qle_list.at(k + 7)->text() == "" && qle_list.at(k + 3)->text() == ""){
                      if(qle_list.at(k - 1)->text() == ""){
                        moveWithoutAddition(k, k + 12);}
                      else if(qle_list.at(k - 1)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k, k + 12);}}

                      if(qle_list.at(k + 11)->text() != "" && qle_list.at(k + 7)->text() == ""){
                          if(qle_list.at(k + 3)->text() == ""){
                             moveWithoutAddition(k + 4, k + 12);}
                          else if(qle_list.at(k + 3)->text() == qle_list.at(k + 11)->text()){
                             moveWithAddition(k + 4, k + 12);}}

                if(qle_list.at(k + 11)->text() != ""){
                    if(qle_list.at(k + 7)->text() == ""){
                        moveWithoutAddition(k + 8, k + 12);}                                 //6 if`ov
                    else if(qle_list.at(k + 7)->text() == qle_list.at(k + 11)->text()){
                        moveWithAddition(k + 8, k + 12);}}
}

void boardWithgame::setStyleSheet()
{
    for(int i = 0; i < 16; i++){
        qle_list.at(i)->setStyleSheet("border-radius: 20px; opacity: 0.5; font-size: 41px;");
    }
}

void boardWithgame::setcolor()
{
    QPalette palette;
//    for(int i = 0; i < 16; i++){
//        if(qle_list.at(i)->text() == ""){
//            palette.setColor(QPalette::Base, QColor::setRgb(50, 160, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "2"){
//            palette.setColor(QPalette::Base, QColor::setRgb(50, 93, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "4"){
//            palette.setColor(QPalette::Base, QColor::setRgb(50, 68, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "8"){
//            palette.setColor(QPalette::Base, QColor::setRgb(139, 50, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "16"){
//            palette.setColor(QPalette::Base, QColor::setRgb(162, 50, 168));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "32"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 137));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "64"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 97));
//            qle_list.at(i)->setPalette(palete);
//        }
//        if(qle_list.at(i)->text() == "128"){
//            palette.setColor(QPalette::Base, QColor::setRgb(168, 50, 81));
//            qle_list.at(i)->setPalette(pallete);
//        }
//        if(qle_list.at(i)->text() == "256"){

//        }
//        if(qle_list.at(i)->text() == "512"){

//        }
//        if(qle_list.at(i)->text() == "1024"){

//        }
//        if(qle_list.at(i)->text() == "2048"){

//        }
//        if(qle_list.at(i)->text() == "4096"){

//        }
//        if(qle_list.at(i)->text() == "8192"){

//        }
//        if(qle_list.at(i)->text() == "16384"){

//        }
//    }
}


void boardWithgame::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        speedMode_toogle = 0;
    } else{
        speedMode_toogle = 1;
    }
}
