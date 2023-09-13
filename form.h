#ifndef FORM_H
#define FORM_H
#include <QList>
#include <QWidget>
#include <QOpenGLWidget>
#include <QLabel>
#include <QKeyEvent>


using namespace std;

namespace Ui {
class Form;
}

class Form : public QOpenGLWidget
{
    Q_OBJECT

protected:
    void keyPressEvent(QKeyEvent *e) override;

public:
    explicit Form(QOpenGLWidget *parent = 0);
    ~Form();
    void score_setter();
    void set_vec();



private slots:


    void on_label_3_linkActivated(const QString &link);



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Form *ui;
    int score = 0;


#endif // FORM_H
