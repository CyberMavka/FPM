#include "score.h"
#include "ui_score.h"

Score::Score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Score)
{
    ui->setupUi(this);
}

Score::~Score()
{
    delete ui;
}

void Score::on_pushButton_clicked(){
    this->close();// Закрываем окно
    emit firstWindow();
}

void Score::setDataTable(QVector<Employee> &empl){
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;

    QStringList horizontalHeader;
    horizontalHeader.append("Місце");
    horizontalHeader.append("Піцерія");
    horizontalHeader.append("Ім'я");
    horizontalHeader.append("Актуальний час");
    horizontalHeader.append("Доданий час");
    horizontalHeader.append("Фінальний час");

    model->setHorizontalHeaderLabels(horizontalHeader);
    int count = 1;
    int i = 0;
    std::string tempCount, pizzaNameTemp, nameTemp, currentTimeTemp, penaltyTimeTemp, finalTimeTemp;
    for(auto it: empl){
        item = new QStandardItem(QString::number(count));
        model->setItem(i, 0, item);

        item = new QStandardItem(it.pizzaName);
        model->setItem(i, 1, item);

        item = new QStandardItem(it.name);
        model->setItem(i, 2, item);

        item = new QStandardItem(it.currentTime);
        model->setItem(i, 3, item);

        item = new QStandardItem(it.penaltyTime);
        model->setItem(i, 4, item);

        item = new QStandardItem(it.finalTime);
        model->setItem(i, 5, item);
        count++;
        i++;
    }

    ui->tableScore->setModel(model);
    ui->tableScore->verticalHeader()->setVisible(false);
    ui->tableScore->resizeRowsToContents();
    ui->tableScore->resizeColumnsToContents();
}
