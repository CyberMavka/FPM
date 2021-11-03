#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "source/time.h"
#include "source/employee.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int getPenalty();
    int getPenaltyTimeForMiss(int countPenalty);

    void setDifferenceCheese();
    void setDifferenceMushroom();
    void setDifferencePapperoni();

    void writeTableScore(QVector<Employee>& employee);
    QString convertTimeToStr(Time time);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
