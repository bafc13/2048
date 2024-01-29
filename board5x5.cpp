#include "board5x5.h"
#include "ui_board5x5.h"
#include <QMessageBox>
#include <random>
#include <QDebug>
#include <QLineEdit>
#include <QRect>
#include <QMovie>

std::default_random_engine Generator;
std::uniform_int_distribution<int>
randIndexGenerator(0,24);

int WinCounter = 0; //счётчик, для контроля выйгрыша(единовременного)

board5x5::board5x5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::board5x5)
{
    QMovie *movie = new QMovie(":/new/prefix1/img/4Cb2.gif");
    QLabel *processLabel = new QLabel(this);
    processLabel->setMovie(movie);
//    processLabel->
    movie->start();
    ui->setupUi(this);
    setWindowTitle("board5x5");
    ui->liveScore->setText(QString::number(0));//обнуление очков
    qleadd();//добавление плашек в список
    stepBackAdd();//добавление плашек в список, для восстановления значений на шаг назад
    qle_list.at(randIndexGenerator(Generator))->setText("2");
    qle_list.at(randIndexGenerator(Generator))->setText("2");
    setStyleSheet();

}

void board5x5::setStyleSheet()
{
    for(int i = 0; i < 25; i++){
        qle_list.at(i)->setStyleSheet("border-radius: 20px; opacity: 0.5; font-size: 35px;");
    }
}

board5x5::~board5x5()
{
    delete ui;
}

void board5x5::plateMoveAnimation(QLineEdit *lineedit)
{
    if(speedMode_toogle == 0){
    animation = new QPropertyAnimation(lineedit, "geometry");/*new QPropertyAnimation(lineedit, "geometry");*/
    animation->setDuration(30);
    animation->setStartValue(lineedit->geometry());
    animation->setKeyValueAt(0.5,QRect(lineedit->x()-50, lineedit->y()-50,lineedit->width()-25,lineedit->height()-25));
    animation->setEndValue(lineedit->geometry());
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    }
}


void board5x5::qleadd()
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
    qle_list.append(ui->plate17);
    qle_list.append(ui->plate18);
    qle_list.append(ui->plate19);
    qle_list.append(ui->plate20);
    qle_list.append(ui->plate21);
    qle_list.append(ui->plate22);
    qle_list.append(ui->plate23);
    qle_list.append(ui->plate24);
    qle_list.append(ui->plate25);

    for(int i = 0; i < 25; i++){
        qle_list.at(i)->setStyleSheet("font-size: 41px;");
        qle_list.at(i)->setReadOnly(true);
    }
}

void board5x5::setAllOnDefaultPos()
{
    for(int i = 0; i < 25; i++){
        qle_list.at(i)->setGeometry(qle_list.at(i)->x(), qle_list.at(i)->y(), 100,100);
    }
}

void board5x5::on_exitButton_clicked()
{
    close();
}

void board5x5::on_resetButton_clicked()
{
    score = 0;
    ui->liveScore->setText(QString::number(score));
    for(int i = 0; i < 25; i++){
        qle_list.at(i)->setText("");
    }
    qle_list.at(randIndexGenerator(Generator))->setText("2");
    qle_list.at(randIndexGenerator(Generator))->setText("2");
}

void board5x5::on_stepBackButton_clicked()
{
    for(int i = 0; i < 25; i++){
        qle_list.at(i)->setText(QString::number(stepBack_list[i]));
        if(stepBack_list[i] == 0){
            qle_list.at(i)->setText("");
        }
    }
}

bool board5x5::isEnd()
{
    int k = 0;
    for(int i = 0; i < 25; i++){
        if(qle_list.at(i)->text() != ""){
            k++;}}
    if(k == 25){
        return 1;
    } else {return 0;}
}

void board5x5::gameEnd()
{
    if(rearrangmentCounter == 0 && board5x5::isEnd() == 1){
        for(int i = 0; i < 25; i++){
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

void board5x5::stepBackAdd()
{
    for(int i = 0; i < 25; i++){
        reserveStepBack_list[i] = stepBack_list[i];
    }
    for(int i = 0; i < 25; i++){
        stepBack_list[i] = qle_list.at(i)->text().toInt();
    }
}

void board5x5::stepBackBack()
{
    for(int i = 0; i < 25; i++){
        stepBack_list[i] = reserveStepBack_list[i];
    }
}


void board5x5::winCheck()
{
    for(int i = 0; i < 25; i++){
        ui->liveScore->setText(QString::number(score));
        if(qle_list.at(i)->text() == "2048" && WinCounter == 0){
            for(int i = 0; i < 25; i++){
                stepBack_list[i] = reserveStepBack_list[i];
            }
            QMessageBox *mes = new QMessageBox;
            mes->setText("You won! Congratilations! You can continue, u play endless mode");
            mes->exec();WinCounter++;
        }}
}

void board5x5::moveWithoutAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    qle_list.at(k)->setText(qle_list.at(j)->text());
    qle_list.at(j)->setText("");
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
}

void board5x5::moveWithAddition(int k, int j)
{
    k = k - 1; j = j - 1;
    score += qle_list.at(k)->text().toInt() * 2;
    qle_list.at(k)->setText(QString::number(qle_list.at(k)->text().toInt() + qle_list.at(j)->text().toInt()));
    qle_list.at(j)->setText("");
    winCheck();
    rearrangmentCounter++;
    plateMoveAnimation(qle_list.at(k));
}

void board5x5::spawnPlate(int k)
{
    qle_list.at(k)->setText("2");
    spawnCounter++;
}

void board5x5::spawnAllPlates()
{
    if(rearrangmentCounter > 0){
        int k;
        while(spawnCounter == 0){
            k = randIndexGenerator(Generator);
            if(qle_list.at(k)->text() == ""){
                spawnPlate(k);
            }
        }
    }
}

void board5x5::moveLeft(int k) // 1 строка
{
    if(k == 2){
        k = 6;
    } else if(k == 3){
        k = 11;
    } else if(k == 4){
        k = 16;
    } else if(k == 5){
        k = 21;
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



            if(qle_list.at(k + 3)->text() != "" && qle_list.at(k)->text() == "" && qle_list.at(k + 1)->text() == "" && qle_list.at(k + 2)->text() == ""){
                if(qle_list.at(k - 1)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k, k + 4);}                                 //6 if`ov
                else if(qle_list.at(k - 1)->text() == qle_list.at(k + 3)->text()){ //перестановка с сложение влево
                    moveWithAddition(k, k + 4);}}

            if(qle_list.at(k + 3)->text() != "" && qle_list.at(k + 2)->text() == "" && qle_list.at(k + 1)->text() == ""){
                if(qle_list.at(k)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k + 1, k + 4);}                                 //6 if`ov
                else if(qle_list.at(k )->text() == qle_list.at(k + 3)->text()){ //перестановка с сложение влево
                    moveWithAddition(k + 1, k + 4);}}

            if(qle_list.at(k + 3)->text() != "" && qle_list.at(k + 2)->text() == ""){
                if(qle_list.at(k + 1)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k + 2, k + 4);}                                 //6 if`ov
                else if(qle_list.at(k + 1)->text() == qle_list.at(k + 3)->text()){ //перестановка с сложение влево
                    moveWithAddition(k + 2, k + 4);}}

            if(qle_list.at(k + 3)->text() != ""){
                if(qle_list.at(k + 2)->text() == ""){ //перестановка на пустое влево
                    moveWithoutAddition(k + 3, k + 4);}                                 //6 if`ov
                else if(qle_list.at(k + 2)->text() == qle_list.at(k + 3)->text()){ //перестановка с сложение влево
                    moveWithAddition(k + 3, k + 4);}}
}

void board5x5::moveRight(int k)
{
    if(k == 2){
        k = 6;
    } else if(k == 3){
        k = 11;
    } else if(k == 4){
        k = 16;
    } else if (k == 5){
        k = 21;
    }
    if(qle_list.at(k + 2)->text() != ""){//для первой строки
                    if(qle_list.at(k + 3)->text() == ""){
                        moveWithoutAddition(k + 4, k + 3);}
                    else if (qle_list.at(k + 3)->text() == qle_list.at(k + 2)->text()){
                        moveWithAddition(k + 4, k + 3);}}

                 if(qle_list.at(k + 1)->text() != "" && qle_list.at(k + 2)->text() == ""){
                    if(qle_list.at(k + 3)->text() == ""){
                        moveWithoutAddition(k + 4, k + 2);}
                    else if(qle_list.at(k + 3)->text() == qle_list.at(k + 1)->text()){
                        moveWithAddition(k + 4, k + 2);}}

                 if(qle_list.at(k + 1)->text() != ""){
                     if(qle_list.at(k + 2)->text() == ""){
                        moveWithoutAddition(k + 3, k + 2);}
                     else if(qle_list.at(k + 2)->text() == qle_list.at(k + 1)->text()){
                        moveWithAddition(k + 3, k + 2);}}

                  if(qle_list.at(k)->text() != "" && qle_list.at(k + 1)->text() == "" && qle_list.at(k + 2)->text() == ""){
                      if(qle_list.at(k + 3)->text() == ""){
                         moveWithoutAddition(k + 4, k + 1);}
                      else if(qle_list.at(k + 3)->text() == qle_list.at(k)->text()){
                          moveWithAddition(k + 4, k + 1);}}

                      if(qle_list.at(k)->text() != "" && qle_list.at(k + 1)->text() == ""){
                          if(qle_list.at(k + 2)->text() == ""){
                             moveWithoutAddition(k + 3, k + 1);}
                          else if(qle_list.at(k + 2)->text() == qle_list.at(k)->text()){
                              moveWithAddition(k + 3, k + 1);}}

                if(qle_list.at(k)->text() != ""){
                    if(qle_list.at(k + 1)->text() == ""){
                        moveWithoutAddition(k + 2, k + 1);}                                 //6 if`ov
                    else if(qle_list.at(k)->text() == qle_list.at(k + 1)->text()){
                        moveWithAddition(k + 2, k + 1);}}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k)->text() == "" && qle_list.at(k + 1)->text() == "" && qle_list.at(k + 2)->text() == ""){
                    if(qle_list.at(k + 3)->text() == ""){
                        moveWithoutAddition(k + 4, k);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 3)->text()){
                        moveWithAddition(k + 4, k);}}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k)->text() == "" && qle_list.at(k + 1)->text() == ""){
                    if(qle_list.at(k + 2)->text() == ""){
                       moveWithoutAddition(k + 3, k);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 2)->text()){
                        moveWithAddition(k + 3, k);}}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k)->text() == ""){
                    if(qle_list.at(k + 1)->text() == ""){
                       moveWithoutAddition(k + 2, k);}
                    else if(qle_list.at(k + 1)->text() == qle_list.at(k - 1)->text()){
                        moveWithAddition(k + 2, k);}}

                if(qle_list.at(k - 1)->text() != ""){
                    if(qle_list.at(k)->text() == ""){
                       moveWithoutAddition(k + 1, k);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k)->text()){
                        moveWithAddition(k + 1, k);}}


}

void board5x5::moveDown(int k) //indexi v qle_list +1 ot real`nogo polojeniya!!!!
{
    if(qle_list.at(k + 14)->text() != ""){//для первого столбца
                    if(qle_list.at(k + 19)->text() == ""){
                        moveWithoutAddition(k + 20, k + 15);}
                    else if (qle_list.at(k + 14)->text() == qle_list.at(k + 19)->text()){
                        moveWithAddition(k + 20, k + 15);}}

                 if(qle_list.at(k + 9)->text() != "" && qle_list.at(k + 14)->text() == ""){
                    if(qle_list.at(k + 19)->text() == ""){
                        moveWithoutAddition(k + 20, k + 10);}
                    else if(qle_list.at(k + 9)->text() == qle_list.at(k + 19)->text()){
                        moveWithAddition(k + 20, k + 10);}}

                 if(qle_list.at(k + 9)->text() != ""){
                     if(qle_list.at(k + 14)->text() == ""){
                        moveWithoutAddition(k + 15, k + 10);}
                     else if(qle_list.at(k + 9)->text() == qle_list.at(k + 14)->text()){
                        moveWithAddition(k + 15, k + 10);}}

                  if(qle_list.at(k + 4)->text() != "" && qle_list.at(k + 9)->text() == "" && qle_list.at(k + 14)->text() == ""){
                      if(qle_list.at(k + 19)->text() == ""){
                        moveWithoutAddition(k + 20, k + 5);}
                      else if(qle_list.at(k + 4)->text() == qle_list.at(k + 19)->text()){
                        moveWithAddition(k + 20, k + 5);}}

                      if(qle_list.at(k + 4)->text() != "" && qle_list.at(k + 9)->text() == ""){
                          if(qle_list.at(k + 14)->text() == ""){
                             moveWithoutAddition(k + 15, k + 5);}
                          else if(qle_list.at(k + 14)->text() == qle_list.at(k + 4)->text()){
                             moveWithAddition(k + 15, k + 5); }}

                if(qle_list.at(k + 4)->text() != ""){
                    if(qle_list.at(k + 9)->text() == ""){
                        moveWithoutAddition(k + 10, k + 5);}                                 //6 if`ov
                    else if(qle_list.at(k + 4)->text() == qle_list.at(k + 9)->text()){
                        moveWithAddition(k + 10, k + 5);}}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k + 4)->text() == "" && qle_list.at(k + 9)->text() == "" && qle_list.at(k + 14)->text() == ""){
                    if(qle_list.at(k + 19)->text() == ""){
                       moveWithoutAddition(k + 20, k);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 19)->text()){
                       moveWithAddition(k + 20, k); }}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k + 4)->text() == "" && qle_list.at(k + 9)->text() == ""){
                    if(qle_list.at(k + 14)->text() == ""){
                       moveWithoutAddition(k + 15, k);}
                    else if(qle_list.at(k + 14)->text() == qle_list.at(k - 1)->text()){
                       moveWithAddition(k + 15, k); }}

                if(qle_list.at(k - 1)->text() != "" && qle_list.at(k + 4)->text() == ""){
                    if(qle_list.at(k + 9)->text() == ""){
                       moveWithoutAddition(k + 10, k);}
                    else if(qle_list.at(k + 9)->text() == qle_list.at(k - 1)->text()){
                       moveWithAddition(k + 10, k); }}

                if(qle_list.at(k - 1)->text() != ""){
                    if(qle_list.at(k + 4)->text() == ""){
                       moveWithoutAddition(k + 5, k);}
                    else if(qle_list.at(k + 4)->text() == qle_list.at(k - 1)->text()){
                       moveWithAddition(k + 5, k); }}
}

void board5x5::moveUp(int k)
{
    if(qle_list.at(k + 4)->text() != ""){//для первого столбца
                    if(qle_list.at(k - 1)->text() == ""){
                       moveWithoutAddition(k, k + 5);}
                    else if (qle_list.at(k - 1)->text() == qle_list.at(k + 4)->text()){
                       moveWithAddition(k, k + 5);}}

                 if(qle_list.at(k + 9)->text() != "" && qle_list.at(k + 4)->text() == ""){
                    if(qle_list.at(k - 1)->text() == ""){
                        moveWithoutAddition(k, k + 10);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 9)->text()){
                        moveWithAddition(k, k + 10);}}

                 if(qle_list.at(k + 9)->text() != ""){
                     if(qle_list.at(k + 4)->text() == ""){
                        moveWithoutAddition(k + 5, k + 10);}
                     else if(qle_list.at(k + 4)->text() == qle_list.at(k + 9)->text()){
                        moveWithAddition(k + 5, k + 10);}}

                  if(qle_list.at(k + 14)->text() != "" && qle_list.at(k + 9)->text() == "" && qle_list.at(k + 4)->text() == ""){
                      if(qle_list.at(k - 1)->text() == ""){
                        moveWithoutAddition(k, k + 15);}
                      else if(qle_list.at(k - 1)->text() == qle_list.at(k + 14)->text()){
                        moveWithAddition(k, k + 15);}}

                      if(qle_list.at(k + 14)->text() != "" && qle_list.at(k + 9)->text() == ""){
                          if(qle_list.at(k + 4)->text() == ""){
                             moveWithoutAddition(k + 5, k + 15);}
                          else if(qle_list.at(k + 4)->text() == qle_list.at(k + 14)->text()){
                             moveWithAddition(k + 5, k + 15);}}

                if(qle_list.at(k + 14)->text() != ""){
                    if(qle_list.at(k + 9)->text() == ""){
                        moveWithoutAddition(k + 10, k + 15);}                                 //6 if`ov
                    else if(qle_list.at(k + 9)->text() == qle_list.at(k + 14)->text()){
                        moveWithAddition(k + 10, k + 15);}}

                if(qle_list.at(k + 19)->text() != "" && qle_list.at(k + 14)->text() == "" && qle_list.at(k + 9)->text() == "" && qle_list.at(k + 4)->text() == ""){
                    if(qle_list.at(k - 1)->text() == ""){
                       moveWithoutAddition(k, k + 20);}
                    else if(qle_list.at(k - 1)->text() == qle_list.at(k + 19)->text()){
                       moveWithAddition(k, k + 20);}}

                if(qle_list.at(k + 19)->text() != "" && qle_list.at(k + 14)->text() == "" && qle_list.at(k + 9)->text() == ""){
                    if(qle_list.at(k + 4)->text() == ""){
                       moveWithoutAddition(k + 5, k + 20);}
                    else if(qle_list.at(k + 4)->text() == qle_list.at(k + 19)->text()){
                       moveWithAddition(k + 5, k + 20);}}

                if(qle_list.at(k + 19)->text() != "" && qle_list.at(k + 14)->text() == ""){
                    if(qle_list.at(k + 9)->text() == ""){
                       moveWithoutAddition(k + 10, k + 20);}
                    else if(qle_list.at(k + 9)->text() == qle_list.at(k + 19)->text()){
                       moveWithAddition(k + 10, k + 20);}}

                if(qle_list.at(k + 19)->text() != ""){
                    if(qle_list.at(k + 14)->text() == ""){
                       moveWithoutAddition(k + 15, k + 20);}
                    else if(qle_list.at(k + 14)->text() == qle_list.at(k + 19)->text()){
                       moveWithAddition(k + 15, k + 20);}}
}

void board5x5::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == 0){
        speedMode_toogle = 0;
    } else{
        speedMode_toogle = 1;
    }
}
