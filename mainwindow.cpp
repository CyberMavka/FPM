#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(on_pushButton_2_clicked()));
}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_2_clicked(){
    QString countFail = QString::number(getPenalty());
    ui->textPenalty->setPlaceholderText(countFail);
    ui->textPenaltyTime->setPlaceholderText(convertSecondsToMinute(getPenaltyTimeForMiss(getPenalty())));

    setDifferenceCheese();
    setDifferenceMushroom();
    setDifferencePapperoni();
}

int MainWindow::getPenaltyTimeForMiss(int countPenalty){
   return countPenalty*15;
}

int MainWindow::getPenalty(){
    int count = 0;
    if(ui->checkBoxCheeseDistribution->isChecked()){
        count++;
    }
    if(ui->checkBoxCheeseDoughAndSauce->isChecked()){
        count++;
    }
    if(ui->checkBoxCheeseWeight->isChecked()){
       count++;
    }
    if(ui->checkBoxMushroomDistribution->isChecked()){
        count++;
    }
    if(ui->checkBoxMushroomDoughAndSauce->isChecked()){
        count++;
    }
    if(ui->checkBoxMushroomWeight->isChecked()){
       count++;
    }
    if(ui->checkBoxPapperoniDistribution->isChecked()){
        count++;
    }
    if(ui->checkBoxPapperoniDoughAndSauce->isChecked()){
        count++;
    }
    if(ui->checkBoxPapperoniWeight->isChecked()){
       count++;
    }
    return count;
}

QString MainWindow::convertSecondsToMinute(int seconds = 0){
    int minute = (seconds - seconds%60) / 60;
    seconds = seconds%60;
    QString ms = QString::number(minute) + ':' + QString::number(seconds) + ":00";
    return ms;
}

void MainWindow::setDifferenceCheese(){
    int currentCheeseWeight = ui->cheeseWeight->toPlainText().toInt();
    int idealCheeseWeight = ui->idealCheeseWeight->toPlainText().toInt();
    ui->differenceCheese->setPlaceholderText(QString::number(idealCheeseWeight-currentCheeseWeight));
}

void MainWindow::setDifferencePapperoni(){
    int currentPapperoniWeight = ui->papperoniWeight->toPlainText().toInt();
    int idealPapperoniWeight = ui->idealPapperoniWeight->toPlainText().toInt();
    ui->differencePapperoni->setPlaceholderText(QString::number(idealPapperoniWeight-currentPapperoniWeight));
}

void MainWindow::setDifferenceMushroom(){
    int currentMushroomWeight = ui->mushroomWeight->toPlainText().toInt();
    int idealMushroomWeight = ui->idealMushroomWeight->toPlainText().toInt();
    ui->differenceMushroom->setPlaceholderText(QString::number(idealMushroomWeight-currentMushroomWeight));
}

