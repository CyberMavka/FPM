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
    void setDataTable(QString data);

private:
    Ui::Score *ui;

signals:
    void firstWindow();
private slots:
    // Слот-обработчик нажатия кнопки
    void on_pushButton_clicked();
};

#endif // SCORE_H
