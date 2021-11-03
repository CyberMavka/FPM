#include "employee.h"

Employee::Employee(){

}


Employee::Employee(QString line){
    QStringList listEmployee;
    listEmployee = line.split(",");
    this->pizzaName = listEmployee[0];
    this->name = listEmployee[1];
    this->currentTime = listEmployee[17];
    this->penaltyTime = listEmployee[16];
    this->finalTime = listEmployee[2];
    this->time = Time(this->finalTime);
}

void sortedsortedByMillisecond(QVector<Employee>& empls){
    int emplMin;
    Employee tempEmpl;
    for(int i = 0; i < empls.size(); i++){
        emplMin = i;

        for(int j = i+1; j<empls.size(); j++){
          if (empls[j].time.getMillisecond() < empls[emplMin].time.getMillisecond()){
              emplMin = j;
          } if (i != emplMin){
              tempEmpl = empls[i];
              empls[i] = empls[emplMin];
             empls[emplMin] = tempEmpl;
          }
        }
    }
}
