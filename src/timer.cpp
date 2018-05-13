#include "timer.h"

void Timer::run() {
    while (true) {
        ticks++;
        if (ticks == 30) {
            emit signTimed();
//            qDebug() << "timed()";
            ticks = 0;
        }
        usleep(10000);
    }
    exec();
}
