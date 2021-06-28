#include "playeractor.h"

namespace StudentSide {

PlayerActor::PlayerActor(Interface::Location loc) : loc_(loc), removed_(false)
{
}

Interface::Location PlayerActor::giveLocation() const
{
    return loc_;
}

bool PlayerActor::isRemoved() const
{
    return removed_;
}

void PlayerActor::remove()
{
    removed_ = true;
}

void PlayerActor::move(Interface::Location loc)
{
    loc_ = loc;
}



}
