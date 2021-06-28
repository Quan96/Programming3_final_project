#include "actorItem.h"
#include "stopItem.h"

#include <QDebug>

namespace StudentSide {

StudentSide::ActorItem::ActorItem(int swidth, int sheight, int type, std::shared_ptr<Interface::IActor> actor, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), scenewidth_(swidth), sceneheight_(sheight), type_(type), actor_(actor), hasIndicator_(false)
{
    x_ = actor_.get()->giveLocation().giveX();
    y_ = actor_.get()->giveLocation().giveY();
    setPos(x_, sceneheight_-y_);

    if (type_ == 1) {
        setPixmap(QPixmap(BUSLOGO).scaled(WIDTH+10, HEIGHT+10));
        std::shared_ptr<CourseSide::Nysse> busObj = std::dynamic_pointer_cast<CourseSide::Nysse> (actor_);
        int numPassenger = int(busObj.get()->getPassengers().size());

        // Add number indicator
        numberIndicator_ = new QGraphicsTextItem();
        numberIndicator_->setPlainText(QString::number(numPassenger));
        numberIndicator_->setDefaultTextColor(Qt::green);
        numberIndicator_->setFont(QFont("times", 12));
        numberIndicator_->setPos(x_, sceneheight_-y_);
    }
    else if (type_ == 2){
        setPixmap(QPixmap(ENEMYLOGO).scaled(WIDTH+25, HEIGHT+25));
    }
}

void StudentSide::ActorItem::setCoord()
{
    x_ = actor_.get()->giveLocation().giveX();
    y_ = actor_.get()->giveLocation().giveY();
}

void ActorItem::advance(int step)
{
    if (!step) {
        return;
    }
    if (actor_->isRemoved()) {
        if (hasIndicator_){
            scene()->removeItem(numberIndicator_);
        }
        scene()->removeItem(this);
    }
    else {
        setPos(x_, sceneheight_- y_);
        if (type_ == 1) {
            std::shared_ptr<CourseSide::Nysse> busObj = std::dynamic_pointer_cast<CourseSide::Nysse> (actor_);
            int numPassenger = int(busObj.get()->getPassengers().size());
            setToolTip(QString::number(numPassenger));
            numberIndicator_->setPlainText(QString::number(numPassenger));
            numberIndicator_->setPos(x_, sceneheight_-y_);
            if (!hasIndicator_) {
                scene()->addItem(numberIndicator_);
                hasIndicator_ = true;
            }
        }else if (type_ == 2){
            timer--;
            Enemy *enemy = dynamic_cast<Enemy *>(actor_.get());
            if (timer == 0){
                Interface::Location dest;
                dest.setXY(rand()%(scenewidth_-10)+5, rand()%(sceneheight_-10)+5);
                enemy->move(dest);
                setCoord();
                timer = 100;
                loop++;
            }
            if (loop == 3){
                std::vector<std::shared_ptr<CourseSide::Nysse>> buses = enemy->getBuses();
                int n = buses.size();
                for(int i=0; i < n; i++){
                    int chance = rand()%2;
                    if (chance){
                        auto getPassengers = buses.at(i).get()->getPassengers();
                        for (auto passenger : getPassengers) {
                            passenger->remove();
                        }
                        buses.at(i).get()->remove();
                    }
                }
                enemy->remove();
            }
        }
    }
}

std::shared_ptr<Interface::IActor> StudentSide::ActorItem::getRelatedObj()
{
    return actor_;
}
}

