//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

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
        // On attend qu'une locomotive arrive sur le contact 1.
        // Pertinent de faire ça dans les deux threads? Pas sûr...
        attendre_contact(contactBeforeShared);
        loco.afficherMessage("Je vais entrer en critique");
        sharedSection->access(this->loco);

        for (size_t x = 0; x < trainSwitchMap.size(); ++x) {
            diriger_aiguillage(trainSwitchMap.at(x).first, trainSwitchMap.at(x).second, 0);
        }

        attendre_contact(contactAfterShared);
        sharedSection->leave(this->loco);
        loco.afficherMessage("Je sors de critique");
    }
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
