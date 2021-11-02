#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QStringList"
#include "QMessageBox"

#include <QTextStream>
#include <QFile>
#include <QVector>
#include <windows.h>

#include <fstream>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::on_pushButton_2_clicked(){
    QString countFail = QString::number(getPenalty());
    ui->textPenalty->setText(countFail);
    Time penalty = convertSecondsToMinute(getPenaltyTimeForMiss(getPenalty()));
    ui->textPenaltyTime->setText(convertTimeToStr(penalty));

    setDifferenceCheese();
    setDifferenceMushroom();
    setDifferencePapperoni();
    try {
       Time final = parseTimeToMSM(ui->inputFinalTime->toPlainText());
        ui->FinalTimeWithPenalty->setText(convertTimeToStr(sumTime(final, penalty)));
    }  catch (...) {
        //QMessageBox msgBox;
        //msgBox.setText("Финальное время заполнено не правильно");
    }
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

MainWindow::Time MainWindow::convertSecondsToMinute(int seconds = 0){
    int minute = (seconds - seconds%60) / 60;
    seconds = seconds%60;
    Time time = {minute,seconds,0};
    return time;
}

void MainWindow::setDifferenceCheese(){
    int currentCheeseWeight = ui->cheeseWeight->toPlainText().toInt();
    int idealCheeseWeight = ui->idealCheeseWeight->toPlainText().toInt();
    ui->differenceCheese->setText(QString::number(idealCheeseWeight-currentCheeseWeight));
}

void MainWindow::setDifferencePapperoni(){
    int currentPapperoniWeight = ui->papperoniWeight->toPlainText().toInt();
    int idealPapperoniWeight = ui->idealPapperoniWeight->toPlainText().toInt();
    ui->differencePapperoni->setText(QString::number(idealPapperoniWeight-currentPapperoniWeight));
}

void MainWindow::setDifferenceMushroom(){
    int currentMushroomWeight = ui->mushroomWeight->toPlainText().toInt();
    int idealMushroomWeight = ui->idealMushroomWeight->toPlainText().toInt();
    ui->differenceMushroom->setText(QString::number(idealMushroomWeight-currentMushroomWeight));
}


QString MainWindow::convertTimeToStr(MainWindow::Time time){
    return QString::number(time.minute)+"."+QString::number(time.seconds)+"."+QString::number(time.millisecond);
}

MainWindow::Time MainWindow::parseTimeToMSM(QString time){
    Time timeMSM;
    QStringList listTime = time.split('.');
    timeMSM.minute = listTime[0].toInt();
    timeMSM.seconds = listTime[1].toInt();
    timeMSM.millisecond = listTime[2].toInt();
    return timeMSM;
}

MainWindow::Time MainWindow::sumTime(Time first, Time second){
   int seconds = first.minute*60 + second.minute*60 + first.seconds + second.seconds;
   Time finalTime = convertSecondsToMinute(seconds);
   finalTime.millisecond = first.millisecond+second.millisecond;
   return finalTime;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = "work.csv";
    QFile file(filename);

    if (file.open(QIODevice::Append)) {
      QTextStream out(&file);
      out.setAutoDetectUnicode(true);
      out << ui->comboBoxPizza->currentText() << ',';
      out << ui->inputName->toPlainText() << ',';
      out << ui->FinalTimeWithPenalty->toPlainText() << ',';

      QString tempPapperoni = "";
      if(ui->checkBoxPapperoniDoughAndSauce->isChecked()){
          tempPapperoni = "X,";
      } else {
          tempPapperoni = " ,";
      } if(ui->checkBoxPapperoniDistribution->isChecked()){
          tempPapperoni = tempPapperoni + "X,";
      } else {
          tempPapperoni = tempPapperoni + " ,";
      } if(ui->checkBoxPapperoniWeight->isChecked()){
          tempPapperoni = tempPapperoni + "X,";
      } else {
          tempPapperoni = tempPapperoni + " ,";
      }

      out << tempPapperoni << ui->papperoniWeight->toPlainText()<<",";

      QString tempMushroom = "";
      if(ui->checkBoxMushroomDoughAndSauce->isChecked()){
          tempMushroom = "X,";
      } else {
          tempMushroom = " ,";
      } if(ui->checkBoxMushroomDistribution->isChecked()){
          tempMushroom = tempMushroom + "X,";
      } else {
          tempMushroom = tempMushroom + " ,";
      } if(ui->checkBoxMushroomWeight->isChecked()){
          tempMushroom = tempMushroom + "X,";
      } else {
          tempMushroom = tempMushroom + " ,";
      }
      out << tempMushroom<< ui->mushroomWeight->toPlainText()<<",";

      QString tempCheese = "";
      if(ui->checkBoxCheeseDoughAndSauce->isChecked()){
          tempCheese = "X,";
      } else {
          tempCheese = " ,";
      } if(ui->checkBoxCheeseDistribution->isChecked()){
          tempCheese = tempCheese + "X,";
      } else {
          tempCheese = tempCheese + " ,";
      } if(ui->checkBoxMushroomWeight->isChecked()){
          tempCheese = tempCheese + "X,";
      } else {
          tempCheese = tempCheese + " ,";
      }
      out << tempCheese<< ui->cheeseWeight->toPlainText()<<",";
      out << ui->textPenalty->toPlainText() << ",";
      out << ui->textPenaltyTime->toPlainText() << ",";
      out << ui->inputFinalTime->toPlainText() << ",";
      out << ui->idealPapperoniWeight->toPlainText() << ",";
      out << ui->idealMushroomWeight->toPlainText() << ",";
      out << ui->idealCheeseWeight->toPlainText();
      out << '\n';

    } else {

      qWarning("Could not open file");
    }

    // Закрываем файл
    file.close();
}


void MainWindow::on_pushButton_3_clicked(){
    ui->checkBoxCheeseDistribution->setChecked(false);
    ui->checkBoxCheeseDoughAndSauce->setChecked(false);
    ui->checkBoxCheeseWeight->setChecked(false);

    ui->checkBoxPapperoniDistribution->setChecked(false);
    ui->checkBoxPapperoniDoughAndSauce->setChecked(false);
    ui->checkBoxPapperoniWeight->setChecked(false);

    ui->checkBoxMushroomDistribution->setChecked(false);
    ui->checkBoxMushroomDoughAndSauce->setChecked(false);
    ui->checkBoxMushroomWeight->setChecked(false);

    ui->papperoniWeight->setText("");
    ui->mushroomWeight->setText("");
    ui->cheeseWeight->setText("");

    ui->differenceCheese->setText("");
    ui->differencePapperoni->setText("");
    ui->differenceMushroom->setText("");

    ui->inputFinalTime->setText("");
    ui->FinalTimeWithPenalty->setText("");

    ui->textPenalty->setText("");
    ui->textPenaltyTime->setText("");

    ui->inputName->setText("");
}


void MainWindow::on_pushButton_4_clicked(){
      QTextStream out(stdout);

      // Создаем объект
      QFile file("work.csv");

      // С помощью метода open() открываем файл в режиме чтения
      if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы

      }

      // Создаем входящий поток, из которого будут считываться данные, и связываем его с нашим файлом
      QTextStream in(&file);
      QVector<Employee> emploees;
      QVector<Employee> currentPizzaEmployee;
      Time time;
      QStringList listEmployee;// Считываем файл строка за строкой
      while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
        QString line = in.readLine();
        // метод readLine() считывает одну строку из потока
        out << line << '\n';
        listEmployee = line.split(",");
        Employee empl;
        empl.pizzaName = listEmployee[0];
        empl.name = listEmployee[1];
        empl.currentTime = listEmployee[17];
        empl.penaltyTime = listEmployee[16];
        empl.finalTime = listEmployee[2];
        time = parseTimeToMSM(empl.finalTime);
        empl.seconds = time.minute*60+time.seconds;
        empl.milliseconds = time.millisecond+empl.seconds*1000;
        emploees.append(empl);
      }

      file.close();

      for(auto it: emploees){
          if(it.pizzaName == ui->comboBoxPizza->currentText()){
              currentPizzaEmployee.append(it);
          }
      }

      int emplMin;
      Employee tempEmpl;

      for(int i = 0; i < currentPizzaEmployee.size(); i++){
          emplMin = i;

          for(int j = i+1; j<currentPizzaEmployee.size(); j++){
            if(currentPizzaEmployee[j].milliseconds < currentPizzaEmployee[emplMin].milliseconds){
                emplMin = j;
            }
            if(i != emplMin){
                tempEmpl = currentPizzaEmployee[i];
                currentPizzaEmployee[i] = currentPizzaEmployee[emplMin];
                currentPizzaEmployee[emplMin] = tempEmpl;
            }
          }
      }


    writeTableScore(currentPizzaEmployee);
}

void MainWindow::writeTableScore(QVector<Employee>& empl){
    QString filename = "score.csv";
    QFile file(filename);

    if (file.open(QIODevice::Append)) {
      QTextStream out(&file);
      out.setAutoDetectUnicode(true);
      int count = 1;
      out << "Місце" << "," << "Піцерія" << "," << "Ім'я" << "," << "Актуальний час" << "," << "Доданий час" << "," << "Фінальний час"<<"\n";
      for(auto it: empl){
        out << count << ',';
        count++;
        out << it.pizzaName << ',';
        out << it.name << ',';
        out << it.currentTime << ',';
        out << it.penaltyTime << ',';
        out << it.finalTime << '\n';

        }
    }

}
