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
    this->close();
    ui->tableScore->setText("");// Закрываем окно
    emit firstWindow();
}

void Score::setDataTable(QString data){
    ui->tableScore->setText(data);
}
