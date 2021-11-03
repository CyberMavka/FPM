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
    QStringList listTime = time.split(findSeparatorSymbolTime(time));
    this->minute = listTime[0].toInt();
    this->seconds = listTime[1].toInt();
    this->millisecond = listTime[2].toInt();
    std::cout << this->millisecond << this->seconds << this->minute;
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
    return QString::number(this->minute)+":"+QString::number(this->seconds)+":"+QString::number(this->millisecond);
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
