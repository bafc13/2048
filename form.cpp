#include "form.h"
#include "ui_form.h"


void Form::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Left){
        ui->label_2->setText("2");
        score+=2;
        score_setter();
    }
    if(e->key() == Qt::Key_Right){
        ui->label_5->setText("2");
        score+=2;
        score_setter();
    }
    if(e->key() == Qt::Key_Down){
        ui->label_15->setText("2");
        score+=2;
        score_setter();
    }
    if(e->key() == Qt::Key_Up){
        ui->label_3->setText("2");
        score+=2;
        score_setter();
    }
}

Form::Form(QOpenGLWidget *parent) :
    QOpenGLWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    score_setter();
}

Form::~Form()
{
    delete ui;
}

void Form::score_setter(){
        ui->label->setText((QString)score);
}

void Form::set_vec(){    QList <QList <QLabel>> a[4] {
    {ui->label_2, ui->label_3, ui->label_4, ui->label_5},
    {ui->label_6, ui->label_7, ui->label_8, ui->label_9},
    {ui->label_10,ui->label_11, ui->label_12, ui->label_13},
    {ui->label_14,ui->label_15,ui->label_16,ui->label_17}};
}

void Form::on_label_3_linkActivated(const QString &link)
{
    }



void Form::on_pushButton_clicked()
{
    this->hide();
}

void Form::on_pushButton_2_clicked()
{
    score = 0;
    for(int i = 2; i < 18; i++){

    }
}
