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
