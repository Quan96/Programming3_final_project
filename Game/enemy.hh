#ifndef ENEMY_HH
#define ENEMY_HH
#include <vector>
#include <memory>

#include "interfaces/iactor.hh"
#include "actors/nysse.hh"

namespace StudentSide {

class Enemy : public Interface::IActor

{
public:
    /**
     * @brief Constructor of the OwnActor class
     */
    Enemy(Interface::Location loc,
          std::vector<std::shared_ptr<CourseSide::Nysse>> buses);
    // ActorIF interface
    Interface::Location giveLocation() const override;
    bool isRemoved() const override;
    void remove() override;
    void move(Interface::Location loc) override;

    /**
     * @brief get the vector of buses
     * @return the vector contained shared pointer of current busses
     */
    std::vector<std::shared_ptr<CourseSide::Nysse>> getBuses();

private:
    Interface::Location loc_; 
    std::vector<std::shared_ptr<CourseSide::Nysse>> buses_;
    bool removed_;
};

}

#endif // ENEMY_HH
