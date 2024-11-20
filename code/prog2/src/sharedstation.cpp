//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include <chrono>
#include <thread>

#include "sharedstation.h"

SharedStation::SharedStation(int _nbTrains) : nbTrains(_nbTrains), mutex(1) {
}

int SharedStation::getTrains() { return nbTrains; }
int SharedStation::getTrainsWaiting() { return nbTrainsWaiting; }

void SharedStation::waitingAtStation() {
    mutex.acquire();
    ++nbTrainsWaiting;
    mutex.release();
}

void SharedStation::leavingStation() {
    mutex.acquire();
    nbTrainsWaiting = 0;
    mutex.release();
}
