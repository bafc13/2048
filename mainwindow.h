#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <form.h>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QColor>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     setOpen();


protected:
    void paintEvent(QPaintEvent *e) override;


private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    Form h;


};

#endif // MAINWINDOW_H
