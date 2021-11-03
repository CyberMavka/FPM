#ifndef TIME_H
#define TIME_H
#include <QString>
#include <QStringList>
#include <QChar>
class Time
{
public:
    Time();
    Time(int seconds);
    Time(QString time);
    Time(const Time& other);
    int minute = 0;
    int seconds = 0;
    int millisecond = 0;
    void convertSecondsToMinute(int seconds = 0);
    QString getTextTime();
    Time operator+ (Time& time1);
    void operator= (const Time& other);
    int getMillisecond();
private:
    QChar findSeparatorSymbolTime(QString time);
};

#endif // TIME_H
