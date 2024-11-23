//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include <chrono>
#include <thread>

#include "sharedstation.h"

SharedStation::SharedStation(int _nbTrains) : mutex(1), wait(0), nbTrains(_nbTrains) {
}

int SharedStation::getTrains() { return nbTrains; }
int SharedStation::getTrainsWaiting() { return nbTrainsWaiting; }

void SharedStation::arrives() {
    mutex.acquire();
    if (nbTrainsWaiting < nbTrains - 1) {
        ++nbTrainsWaiting;
        mutex.release();
        wait.acquire();
    } else {
        while (nbTrainsWaiting) {
            wait.release();
            --nbTrainsWaiting;
        }
        mutex.release();
    }
}
