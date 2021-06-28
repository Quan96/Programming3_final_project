#include "bullet.hh"
#include "actorItem.h"
//#include "playeractor.h"
#include "playerItem.hh"

#include <signal.h>
#include <QTimer>
#include <QList>
#include <QGraphicsScene>
//#include <QGraphicsTextItem>
#include <QDebug>

namespace StudentSide {

Bullet::Bullet(QString direction, std::shared_ptr<City> city, int hero, QGraphicsItem *parent):
    QGraphicsPixmapItem(parent),
    direction_(direction),
    city_(city)
{
    if (hero == 0) {
        setPixmap(QPixmap(BEAMLOGO).scaled(coef_, coef_));
    }
    if (hero == 1) {
        setPixmap(QPixmap(SHIELDLOGO).scaled(coef_, coef_));
    }
    else if (hero == 2) {
        setPixmap(QPixmap(AXELOGO).scaled(coef_, coef_ + 10));
    }

    if (direction_ == "DOWN") {
        setRotation(180);
    }
    else if (direction_ == "RIGHT") {
        setRotation(90);
    }
    else if (direction_ == "LEFT"){
        setRotation(-90);
    }

}

void Bullet::move(){
    QList<QGraphicsItem *> collidedItems = collidingItems();
    int n = collidedItems.size();
    // if bullet collided with another bullet or player
    for (int i=0; i<n; i++) {
        int type = collidedItems[i]->type();
        if (type == 0 || type == 1 ) {
            continue;
        }
        // if collided with bus
        else {
            if (typeid (*(collidedItems[i])) == typeid (ActorItem)) {
                ActorItem *actorItem = qgraphicsitem_cast<ActorItem *>(collidedItems[i]);
                int actorType = city_->getActorType(actorItem->getRelatedObj());
                if (actorType != 0) {
                    actorItem->getRelatedObj().get()->remove();
                    city_->removeActor(actorItem->getRelatedObj());

                    scene()->removeItem(this);

                    delete this;
                    return;
                }
            }
        }
    }
    // set move direction for bullet
    if (direction_ == "UP"){
        setPos(x(), y()-coef_);
    }
    else if (direction_ == "DOWN"){
        setPos(x(), y()+coef_);
    }
    else if (direction_ == "RIGHT"){
        setPos(x()+coef_, y());
    }
    else if (direction_ == "LEFT"){
        setPos(x()-coef_, y());
    }
    // if bullet of the scene, delete
    std::pair<int, int> bgSize = city_->getBGsize();
    if (pos().y() < 0 || pos().y() > bgSize.second || pos().x() < 0 || pos().x() > bgSize.first) {
        scene()->removeItem(this);
        delete this;
    }
}


int Bullet::type() const
{
    return graphicType;
}

void Bullet::advance(int step)
{
    if (!step) {
        return;
    }
    else {
        move();
    }
}

}
