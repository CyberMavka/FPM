#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "QStringList"
#include "QMessageBox"

#include <QTextStream>
#include <QFile>
#include <QVector>

#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);

    scoreWindow = new Score();
    connect(scoreWindow, &Score::firstWindow, this,&MainWindow::show);

    connect(ui->btnAddDataInTable, SIGNAL(clicked()), this, SLOT(addDataInTable()));
    connect(ui->btnCalculateData, SIGNAL(clicked()), this, SLOT(calculateData()));
    connect(ui->btnResetData, SIGNAL(clicked()), this, SLOT(resetData()));
    connect(ui->btnGetScore, SIGNAL(clicked()), this, SLOT(getScore()));

}

MainWindow::~MainWindow(){
    delete ui;
}


void MainWindow::calculateData(){
    QString countFail = QString::number(getPenalty());
    ui->textPenalty->setText(countFail);

    Time penalty(getPenaltyTimeForMiss(getPenalty())*1000);
    ui->textPenaltyTime->setText(penalty.getTextTime());

    setDifferenceCheese();
    setDifferenceMushroom();
    setDifferencePapperoni();

    try {
       Time final(ui->inputFinalTime->toPlainText());
       Time test = final+penalty;
       ui->FinalTimeWithPenalty->setText(test.getTextTime());
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

void MainWindow::setDifferenceCheese(){
    int currentCheeseWeight = ui->cheeseWeight->toPlainText().toInt();
    int idealCheeseWeight = ui->idealCheeseWeight->toPlainText().toInt();
    ui->differenceCheese->setText(QString::number(currentCheeseWeight-idealCheeseWeight));
}

void MainWindow::setDifferencePapperoni(){
    int currentPapperoniWeight = ui->papperoniWeight->toPlainText().toInt();
    int idealPapperoniWeight = ui->idealPapperoniWeight->toPlainText().toInt();
    ui->differencePapperoni->setText(QString::number(currentPapperoniWeight-idealPapperoniWeight));
}

void MainWindow::setDifferenceMushroom(){
    int currentMushroomWeight = ui->mushroomWeight->toPlainText().toInt();
    int idealMushroomWeight = ui->idealMushroomWeight->toPlainText().toInt();
    ui->differenceMushroom->setText(QString::number(currentMushroomWeight-idealMushroomWeight));
}




void MainWindow::addDataInTable()
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


void MainWindow::resetData(){
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

QVector<Employee> MainWindow::readAllEmployee(){
     QTextStream out(stdout);

     QFile file("work.csv");

     // С помощью метода open() открываем файл в режиме чтения
     if (!file.open(QIODevice::ReadOnly)) {
       qWarning("Cannot open file for reading"); // если файл не найден, то выводим предупреждение и завершаем выполнение программы
     }

     QTextStream in(&file);
     QVector<Employee> emploees;
    // Считываем файл строка за строкой
     while (!in.atEnd()) { // метод atEnd() возвращает true, если в потоке больше нет данных для чтения
        QString line = in.readLine();
        // метод readLine() считывает одну строку из потока
        out << line << '\n';
        Employee empl(line);
        emploees.append(empl);
     }

     file.close();
     return emploees;
}

QVector<Employee> MainWindow::findNeedEmployeeByPizzaName(QVector<Employee> &empls){
     QVector<Employee> currentPizzaEmployee;
     for(auto it: empls){
         if(it.pizzaName == ui->comboBoxPizza->currentText()){

             currentPizzaEmployee.append(it);
         }
     }
     return currentPizzaEmployee;
}

void MainWindow::getScore(){
    scoreWindow->show();
    this->close();
    QVector<Employee> emplsAll = readAllEmployee();
    QVector<Employee> empls = findNeedEmployeeByPizzaName(emplsAll);
    int emplMin;
    Employee tempEmpl;

    for(int i = 0; i < empls.size(); i++){
        emplMin = i;
        for(int j = 0; j < empls.size(); j++){
          if (empls[j].time.getMillisecond() > empls[emplMin].time.getMillisecond()){
              emplMin = j;
          } if (i != emplMin){
              tempEmpl = empls[i];
              empls[i] = empls[emplMin];
             empls[emplMin] = tempEmpl;
          }
        }
    }
    //sortedByMillisecond(empls);
    writeTableScoreInTextBrowser(empls);
}
void MainWindow::writeTableScoreInTextBrowser(QVector<Employee> &empl){
    scoreWindow->setDataTable(empl);
}
void MainWindow::writeTableScore(QVector<Employee>& empl){
    QString filename = "score.csv";
    QFile file(filename);

    if (file.open(QIODevice::WriteOnly)) {
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
