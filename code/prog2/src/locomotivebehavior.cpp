//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"
#include <unistd.h>

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :
    //sharedSection->access(loco);
    //sharedSection->leave(loco);

    while(true) {
        attendre_contact(stationID);
        if (toursDone >= nbTourMax) {
            loco.arreter();
            loco.afficherMessage("Je m'arrête en gare !");
            station->arrives();
            toursDone = 0;
            loco.inverserSens();
            setRandomPriority();
            sharedSection->togglePriorityMode();
            sleep(2);
            std::swap(contactBeforeShared, contactAfterShared);
            std::swap(contactRequest, contactRequestAfter);
            loco.demarrer();
            loco.afficherMessage("Je repart !");
        } else {
            ++toursDone;
        }

        attendre_contact(contactRequest);
        sharedSection->request(loco, loco.priority);

        attendre_contact(contactBeforeShared);
        sharedSection->access(loco, loco.priority);

        for (size_t x = 0; x < trainSwitchMap.size(); ++x) {
            diriger_aiguillage(trainSwitchMap.at(x).first, trainSwitchMap.at(x).second, 0);
        }

        attendre_contact(contactAfterShared);
        sharedSection->leave(loco);
    }
}

void LocomotiveBehavior::setRandomPriority() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    this->loco.priority = dis(gen);
}

void LocomotiveBehavior::addSwitch(int switchID, int direction) {
    trainSwitchMap.emplace_back(std::make_pair(switchID, direction));
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}

LocomotiveBehavior::LocomotiveBehavior(Locomotive& loco,
                                       std::shared_ptr<SharedSectionInterface> sharedSection,
                                       int nBefore,
                                       int nAfter,
                                       int rBefore,
                                       int rAfter,
                                       std::shared_ptr<SharedStation> station,
                                       int nbTours,
                                       int stationID
                                       ) : loco(loco), sharedSection(sharedSection), contactBeforeShared(nBefore), contactAfterShared(nAfter), contactRequest(rBefore), contactRequestAfter(rAfter), station(station), nbTourMax(nbTours), stationID(stationID) {
    toursDone = 0;
    setRandomPriority();
}
