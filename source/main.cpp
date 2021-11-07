#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QComboBox>

#include <QApplication>
class Application final : public QApplication {
public:
    Application(int& argc, char** argv) : QApplication(argc, argv) {}
    virtual bool notify(QObject *receiver, QEvent *event) override {
        try {
                return QApplication::notify(receiver, event);
            } catch (std::exception &e) {
                qFatal("Error %s sending event %s to object %s (%s)",
                    e.what(), typeid(*event).name(), qPrintable(receiver->objectName()),
                    typeid(*receiver).name());
            } catch (...) {
                qFatal("Error <unknown> sending event %s to object %s (%s)",
                    typeid(*event).name(), qPrintable(receiver->objectName()),
                    typeid(*receiver).name());
            }

            // qFatal aborts, so this isn't really necessary
            // but you might continue if you use a different logging lib
            return false;
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
