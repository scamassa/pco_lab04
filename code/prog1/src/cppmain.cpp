//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "ctrain_handler.h"

#include "locomotive.h"
#include "locomotivebehavior.h"
#include "sharedsectioninterface.h"
#include "sharedsection.h"
#include "sharedstation.h"

// Locomotives :
// Vous pouvez changer les vitesses initiales, ou utiliser la fonction loco.fixerVitesse(vitesse);
// Laissez les numéros des locos à 0 et 1 pour ce laboratoire

// Locomotive A
static Locomotive locoA(7 /* Numéro (pour commande trains sur maquette réelle) */, 10 /* Vitesse */);
// Locomotive B
static Locomotive locoB(42 /* Numéro (pour commande trains sur maquette réelle) */, 12 /* Vitesse */);

//Arret d'urgence
void emergency_stop()
{
    // TODO
    locoA.arreter();
    locoB.arreter();

    afficher_message("\nSTOP!");
}


//Fonction principale
int cmain()
{
    /************
     * Maquette *
     ************/

    //Choix de la maquette (A ou B)
    selection_maquette(MAQUETTE_A /*MAQUETTE_B*/);

    /**********************************
     * Initialisation des aiguillages *
     **********************************/

    // Initialisation des aiguillages
    // Positiion de base donnée comme exemple, vous pouvez la changer comme bon vous semble
    // Vous devrez utiliser cette fonction pour la section partagée pour aiguiller les locos
    // sur le bon parcours (par exemple à la sortie de la section partagée) vous pouvez l'
    // appeler depuis vos thread des locos par ex.
    diriger_aiguillage(1,  DEVIE, 0);
    diriger_aiguillage(2,  TOUT_DROIT     , 0);
    diriger_aiguillage(3,  DEVIE     , 0);
    diriger_aiguillage(4,  TOUT_DROIT, 0);
    diriger_aiguillage(5,  TOUT_DROIT, 0);
    diriger_aiguillage(6,  TOUT_DROIT, 0);
    diriger_aiguillage(7,  TOUT_DROIT, 0);
    diriger_aiguillage(8,  DEVIE     , 0);
    diriger_aiguillage(9,  TOUT_DROIT, 0);
    diriger_aiguillage(10, DEVIE, 0);
    diriger_aiguillage(11, TOUT_DROIT, 0);
    diriger_aiguillage(12, TOUT_DROIT, 0);
    diriger_aiguillage(13, TOUT_DROIT, 0);
    diriger_aiguillage(14, DEVIE     , 0);
    diriger_aiguillage(15, DEVIE     , 0);
    diriger_aiguillage(16, TOUT_DROIT, 0);
    diriger_aiguillage(17, DEVIE, 0);
    diriger_aiguillage(18, TOUT_DROIT, 0);
    diriger_aiguillage(19, TOUT_DROIT, 0);
    diriger_aiguillage(20, DEVIE     , 0);
    diriger_aiguillage(21, DEVIE     , 0);
    diriger_aiguillage(22, TOUT_DROIT, 0);
    diriger_aiguillage(23, DEVIE, 0);
    diriger_aiguillage(24, TOUT_DROIT, 0);
    // diriger_aiguillage(/*NUMERO*/, /*TOUT_DROIT | DEVIE*/, /*0*/);

    /********************************
     * Position de départ des locos *
     ********************************/

    // Loco 0
    // Exemple de position de départ
    locoA.fixerPosition(23, 16);

    // Loco 1
    // Exemple de position de départ
    locoB.fixerPosition(31, 30);

    /***********
     * Message *
     **********/

    // Affiche un message dans la console de l'application graphique
    afficher_message("Hit play to start the simulation...");

    /*********************
     * Threads des locos *
     ********************/
    int nbTrains = 2;

    // Création de la section partagée
    std::shared_ptr<SharedSectionInterface> sharedSection = std::make_shared<SharedSection>();
    std::shared_ptr<SharedStation> station = std::make_shared<SharedStation>(nbTrains);

    // Création du thread pour la loco 0
    std::unique_ptr<Launchable> locoBehaveA = std::make_unique<LocomotiveBehavior>(locoA, sharedSection, 17, 23, station, 2, 26);
    if (auto ptrLoco = dynamic_cast<LocomotiveBehavior*>(locoBehaveA.get())) {
        ptrLoco->addSwitch(11, DEVIE);
        ptrLoco->addSwitch(9, DEVIE);
    }

    // Création du thread pour la loco 1
    std::unique_ptr<Launchable> locoBehaveB = std::make_unique<LocomotiveBehavior>(locoB, sharedSection, 6, 13, station, 3, 31);
    if (auto ptrLoco = dynamic_cast<LocomotiveBehavior*>(locoBehaveB.get())) {
        ptrLoco->addSwitch(11, TOUT_DROIT);
        ptrLoco->addSwitch(9, TOUT_DROIT);
    }
    // Lanchement des threads
    afficher_message(qPrintable(QString("Lancement thread loco A (numéro %1)").arg(locoA.numero())));
    locoBehaveA->startThread();
    afficher_message(qPrintable(QString("Lancement thread loco B (numéro %1)").arg(locoB.numero())));
    locoBehaveB->startThread();

    // Attente sur la fin des threads
    locoBehaveA->join();
    locoBehaveB->join();

    //Fin de la simulation
    mettre_maquette_hors_service();

    return EXIT_SUCCESS;
}
