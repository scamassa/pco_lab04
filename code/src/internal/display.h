#ifndef DISPLAY_H
#define DISPLAY_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include <pcosynchro/pcosemaphore.h>
#include <QLabel>
#include <QLine>
#include <QPen>

#include "seller.h"

class ResourceItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    public:
        ResourceItem();
        PcoSemaphore sem;
};

class SupplierItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    public:
        SupplierItem();
        PcoSemaphore sem;
};

class ClinicItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    public:
        ClinicItem();
        PcoSemaphore sem;
};

class HospitalItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    public:
        HospitalItem();
        PcoSemaphore sem;
};

class ProductionItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
        Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    public:
        ProductionItem();
        PcoSemaphore sem;
};

class DisplayView : public QGraphicsView
{
    Q_OBJECT
public:
    DisplayView(unsigned int nbSuppliers, unsigned int nbClinic, unsigned int nbHospitals, QWidget *parent);
    //~DisplayView();

    std::vector<QLabel*> funds;
    std::vector<QLabel*> syringes;
    std::vector<QLabel*> pills;
    std::vector<QLabel*> scalpels;
    std::vector<QLabel*> thermometers;
    std::vector<QLabel*> stethoscopes;
    std::vector<QLabel*> patientsSick;
    std::vector<QLabel*> patientsHealed;

    std::vector<ProductionItem*> m_productItem;


    void update_stocks(int idx, std::map<ItemType, int>* stocks);
    void update_fund(int idx, QString fund);

    void set_link(int from, int to);

private:
    QGraphicsScene *m_scene;

    std::vector<std::vector<bool>> resourceAssociations;

    void place_resources(int x, int y, int id, std::vector<bool> resources);
    void createResourceAssociations(unsigned int nbSuppliers, unsigned int nbHospitals, unsigned int nbClinic);
public slots:

};

#endif // DISPLAY_H
