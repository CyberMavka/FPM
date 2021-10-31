#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
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
    struct Time{
        int minute = 0;
        int seconds = 0;
        int millisecond = 0;
    };
    Time convertSecondsToMinute(int seconds);
    Time parseTimeToMSM(QString value);
    Time sumTime(Time first, Time second);
    QString convertTimeToStr(Time time);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
