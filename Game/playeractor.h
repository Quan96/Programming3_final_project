#ifndef PLAYERACTOR_H
#define PLAYERACTOR_H

#include "interfaces/iactor.hh"

namespace StudentSide {

class PlayerActor : public virtual Interface::IActor
{
public:
    PlayerActor(Interface::Location);
    // ActorIF interface
    Interface::Location giveLocation() const override;
    void move(Interface::Location loc) override;
    bool isRemoved() const override;
    void remove() override;

private:
    Interface::Location loc_;
    bool removed_;
    int step = 10;
};

}

#endif // PLAYERACTOR_H
