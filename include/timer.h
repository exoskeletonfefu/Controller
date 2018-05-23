#pragma once
#include <QThread>
#include <memory>

class Timer: public QThread {
    Q_OBJECT
public:
    void run();
private:
    int ticks = 0;
signals:
    void signTimed();
public slots:
};
typedef std::shared_ptr<Timer> PTimer;
