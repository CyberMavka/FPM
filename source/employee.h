#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <QStringList>
#include "source/time.h"
#include <QVector>
class Employee{
public:
    Employee();
    Employee(QString line);
    QString name;
    QString pizzaName;
    QString currentTime;
    QString penaltyTime;
    QString finalTime = "";
    Time time;
 };

void sortedByMillisecond(QVector<Employee>& empls);
#endif // EMPLOYEE_H
