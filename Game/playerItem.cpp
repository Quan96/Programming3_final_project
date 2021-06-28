#include "playerItem.hh"

#include <QDebug>

namespace StudentSide {

StudentSide::PlayerItem::PlayerItem(std::shared_ptr<PlayerActor> player,
                       int hero,
                       QGraphicsItem *parent) :
    QGraphicsPixmapItem(parent),
    player_(player),
    hero_(hero)
{
    // draw the player
    if (hero == 0) {
        setPixmap(QPixmap(IRONMAN).scaled(coef_, coef_));
    }
    else if (hero == 1) {
        setPixmap(QPixmap(CAPTAIN).scaled(coef_, coef_));
    }
    else if (hero == 2) {
        setPixmap(QPixmap(THOR).scaled(coef_, coef_));
    }

    direction_ = "UP";
    x_ = player_.get()->giveLocation().giveX();
    y_ = player_.get()->giveLocation().giveY();
    setPos(x_, y_);

}

void StudentSide::PlayerItem::setCoord()
{
    x_ = player_.get()->giveLocation().giveX();
    y_ = player_.get()->giveLocation().giveY();
}

//QString PlayerGraphic::getDirection() const
//{
//    return direction_;
//}

void StudentSide::PlayerItem::setDirection(QString new_direction)
{
    direction_ = new_direction;
}

int StudentSide::PlayerItem::type() const
{
    return graphicType;
}


void StudentSide::PlayerItem::keyPressEvent(QKeyEvent *event)
{
    Interface::Location dest = player_.get()->giveLocation();
    if ((event->key() == Qt::Key_Left || event->key() == Qt::Key_A) && x() > 0)
    {
        setTransformOriginPoint(origin_, origin_);
        setRotation(-90);
        setDirection("LEFT");
        dest.setXY(x_ - step, y_);
    }
    else if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_D) && x() < mapSize.first-coef_){
        setTransformOriginPoint(origin_, origin_);
        setRotation(90);
        setDirection("RIGHT");
        dest.setXY(x_ + step, y_);
    }
    else if ((event->key() == Qt::Key_Up || event->key() == Qt::Key_W) && y() > 0) {
        setTransformOriginPoint(origin_, origin_);
        setRotation(0);
        setDirection("UP");
        dest.setXY(x_, y_ - step);
    }
    else if ((event->key() == Qt::Key_Down || event->key() == Qt::Key_S) && y() < mapSize.second-coef_) {
        setTransformOriginPoint(origin_, origin_);
        setRotation(180);
        setDirection("DOWN");
        dest.setXY(x_, y_ + step);
    }
    else if (event->key() == Qt::Key_Space) {
//        qDebug() << pos().x() << pos().y();
        if (!event->isAutoRepeat()){
            Bullet *bullet = new Bullet(direction_, city_, hero_);
            if (direction_ == "UP") {
                bullet->setPos(pos().x()+20, pos().y()-10);
            }
            else if (direction_ == "DOWN") {
                bullet->setPos(pos().x()+20, pos().y()+coef_+10);
            }
            else if (direction_ == "RIGHT") {
                bullet->setPos(pos().x()+coef_+10, pos().y()+20);
            }
            else if (direction_ == "LEFT") {
                bullet->setPos(pos().x()-10, pos().y()+20);
            }
            scene()->addItem(bullet);
        }
    }
    player_->move(dest);
    setCoord();
    setPos(x_, y_);
}

std::shared_ptr<PlayerActor> StudentSide::PlayerItem::getRelatedObj()
{
    return player_;
}

void StudentSide::PlayerItem::setCity(std::shared_ptr<City> city)
{
    city_ = city;
    mapSize = city_->getBGsize();
}

}
