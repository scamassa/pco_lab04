#ifndef SHARED_STATION_H
#define SHARED_STATION_H

#include <pcosynchro/pcosemaphore.h>

class SharedStation
{
public:
    SharedStation(int _nbTrains);

    /* Implémentez toute la logique que vous avez besoin pour que les locomotives
     * s'attendent correctement à la station */
    int getTrains();
    int getTrainsWaiting();

    void waitingAtStation();
    void leavingStation();
private:
    /* TODO */
    PcoSemaphore mutex;

    int nbTrainsWaiting;
    const int nbTrains;
};

#endif // SHARED_STATION_H
