#include "time.h"
#include <iostream>

Time::Time(){
}

Time::Time(int milliseconds){
    this->millisecond = milliseconds % 1000;
    this->seconds = ((milliseconds - this->millisecond)/1000)%60;
    this->minute = (milliseconds - this->millisecond)/1000/60;

}

Time::Time(QString time){
    QStringList listTime;
    listTime = time.split(findSeparatorSymbolTime(time));
    this->minute = listTime[0].toInt();
    this->seconds = listTime[1].toInt();
    this->millisecond = listTime[2].toInt();
}

QChar Time::findSeparatorSymbolTime(QString time){
    for(auto sym: time){
        if(!sym.isDigit()){
            return sym;
        }
    }
    return ' ';
}

QString Time::getTextTime(){
    QString minuteTemp = QString::number(this->minute), secondTemp = QString::number(this->seconds), millisecondTemp = QString::number(this->millisecond);
    if(minuteTemp.length() == 1){
        minuteTemp = "0" + minuteTemp;
    } if (secondTemp.length() == 1){
        secondTemp = "0" + secondTemp;
    } if (millisecondTemp.length()==1){
        millisecondTemp = "0" + millisecondTemp;
    }
    return minuteTemp + ":" + secondTemp + ":" + millisecondTemp;
}
int Time::getMillisecond(){
    return((this->minute*60+this->seconds)*1000+this->millisecond);
}

Time Time::operator+ (Time& time){
    int millisecondsFirst = (this->minute*60 + this->seconds)*1000 + this->millisecond;
    int millisecondsSecond = (time.minute*60 + time.seconds)*1000 + time.millisecond;
    int sum = millisecondsFirst + millisecondsSecond;
    return Time(sum);
}

void Time::operator= (const Time& other){
    this->millisecond = other.millisecond;
    this->minute = other.minute;
    this->seconds = other.seconds;

}

Time::Time(const Time& other){
    this->millisecond = other.millisecond;
    this->minute = other.minute;
    this->seconds = other.seconds;
}

bool auditTimeStr(QString time){
    int countNumbers = 0;
    if(time.size()<5 || time.size()> 8){
        return false;
    }
    for(int i = 0; i < time.size(); ++i){
        if(!time[i].isDigit() || i+1 == time.size()){
            //потрібно для того якщо ми будемо в кінці рядка перемістити і
            //на символ закінчення рядка \0 для коректної роботи алгоритма
            //інакше звернення контейнера [i] буде до кінцевої цифри і воно не зможе пройти перевірку
            if(i + 1 == time.size()){
                i = i + 1;
            }
            if(countNumbers == 2 &&
              (!time[i-1].isDigit() || !time[i-2].isDigit())){
                return false;
            } else if (countNumbers == 1 && !time[i-1].isDigit()) {
                return false;
            }
            //при проходженні другого кола, якщо формат 00:0:00 countNumbers буде 2 що зіб'є алгоритм
            countNumbers = -1;
        }
        countNumbers++;
    }
    return true;
}
