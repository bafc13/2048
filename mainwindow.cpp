#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(5);
    QBrush brush;
    QColor color;
    color.setRgb(Qt::red,Qt::green,Qt::blue);
    brush.setColor(color);
    brush.setStyle(Qt::SolidPattern);
    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawRect(250,500,100,100);
    painter.end();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    h.show();

}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //ui->openGLWidget->paintEvent(*this);
}

MainWindow::setOpen(){

}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}
