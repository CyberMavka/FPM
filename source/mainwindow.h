#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include "source/time.h"
#include "source/employee.h"
#include "score.h"

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
    QVector<Employee> readAllEmployee();
    QVector<Employee> findNeedEmployeeByPizzaName(QVector<Employee> &empls);
    void writeTableScoreInTextBrowser(QVector<Employee>& empl);
private slots:
    void calculateData();

    void addDataInTable();

    void resetData();

    void getScore();

private:
    Ui::MainWindow *ui;
    Score *scoreWindow;
};

#endif // MAINWINDOW_H
