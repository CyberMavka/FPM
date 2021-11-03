#ifndef SCORE_H
#define SCORE_H

#include <QDialog>

namespace Ui {
class Score;
}

class Score : public QDialog
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    ~Score();

private:
    Ui::Score *ui;
};

#endif // SCORE_H
