#include "enemy.hh"

#include <random>
#include <QDebug>

namespace StudentSide {

Enemy::Enemy(Interface::Location loc, std::vector<std::shared_ptr<CourseSide::Nysse>> buses) :
    loc_(loc),
    buses_(buses),
    removed_(false)
{
//    qDebug() << "Successfully created";
}

Interface::Location Enemy::giveLocation() const
{
    return loc_;
}

bool Enemy::isRemoved() const
{
    return removed_;
}

void Enemy::remove()
{
    removed_ = true;
}

void Enemy::move(Interface::Location location)
{
    loc_ = location;
}

std::vector<std::shared_ptr<CourseSide::Nysse> > Enemy::getBuses()
{
    return buses_;
}

}
