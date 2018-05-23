#include "timer.h"

void Timer::run() {
    while (true) {
        ticks++;
        if (ticks == 30) {
            emit signTimed();
            ticks = 0;
        }
        usleep(10000);
    }
    exec();
}
