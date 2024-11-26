//    ___  _________    ___  ___  ___ ____ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  / / / //
//  / ___/ /__/ /_/ / / __// // / __/_  _/ //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"
#include <set>

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{
public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection() : criticalSection(1), mutex(1), isUsed(false) {
        // TODO
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée par une autre locomotive.
     * Si la locomotive et son thread ont été mis en attente,
     * le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     */
    void access(Locomotive &loco, int priority) override {
        mutex.acquire();
        auto topPrioLoco = waitingLocos.begin();
        if (&topPrioLoco->loco == &loco && !isUsed) {
            mutex.release();
            criticalSection.acquire();
            mutex.acquire();
            isUsed = true;
            mutex.release();
        } else {
            loco.arreter();
            mutex.release();
            criticalSection.acquire();
            mutex.acquire();
            isUsed = true;
            mutex.release();
            loco.demarrer();
        }
        loco.fixerVitesse(loco.vitesse() * 3);

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
    }

    void request(Locomotive& loco, int priority) override {
        PrioLoco t(loco, priority);
        loco.fixerVitesse(loco.vitesse() / 3);
        waitingLocos.insert(t);
    }

    void togglePriorityMode() override {
        priorityMode = (priorityMode == PriorityMode::HIGH_PRIORITY ? PriorityMode::LOW_PRIORITY : PriorityMode::HIGH_PRIORITY);
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        // TODO
        mutex.acquire();
        isUsed = false;
        waitingLocos.erase(waitingLocos.begin());
        mutex.release();
        criticalSection.release();

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

private:

    /* A vous d'ajouter ce qu'il vous faut */

    // Méthodes privées ...
    // Attribut privés ...
    PcoSemaphore criticalSection, mutex;
    bool isUsed;
    PriorityMode priorityMode = PriorityMode::HIGH_PRIORITY;

    struct PrioLoco {
        Locomotive& loco;
        int priority;       // Priority (1 to 10)

        PrioLoco(Locomotive& n, int p) : loco(n), priority(p) {}

        // Define operator< for ordering in std::set
        bool operator<(const PrioLoco& other) const {
            // Higher priority first; break ties by ID
            if (priority != other.priority)
                return priority > other.priority;
            return loco.numero() < other.loco.numero();
        }
    };

    std::set<PrioLoco> waitingLocos;
};


#endif // SHAREDSECTION_H
