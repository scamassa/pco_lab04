//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include "sharedstation.h"

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:
    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco,
                       std::shared_ptr<SharedSectionInterface> sharedSection,
                       int nBefore,
                       int nAfter,
                       int rBefore,
                       int rAfter,
                       std::shared_ptr<SharedStation> station,
                       int nbTours,
                       int stationID
                       );


    /**
     * @brief addSwitch Permet d'ajouter les swtichs concernés par la section partagée.
     * @param switchID  ID du switch
     * @param direction La direction dans laquelle l'orienter
     */
    void addSwitch(int switchID, int direction);

    void setRandomPriority();


protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;

    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */

    int contactBeforeShared, contactAfterShared, contactRequest, contactRequestAfter;

    std::vector<std::pair<int, int>> trainSwitchMap;    // Map of Switch ID to SwitchData
    std::shared_ptr<SharedStation> station;
    int toursDone, nbTourMax;
    int stationID;
};

#endif // LOCOMOTIVEBEHAVIOR_H
