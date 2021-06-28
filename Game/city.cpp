#include "city.h"

#include <QDebug>
#include <QMessageBox>

namespace StudentSide {

City::City():gamestate_(false), gameOver_(false), tictac_(0){
}

City::~City()
{
}

void City::setBackground(QImage& basicbackground, QImage& bigbackground) {
    if (mapsize_ == 0) {
        background_ = basicbackground;
    }
    else {
        background_ = bigbackground;
    }
    width_ = background_.width();
    height_ = background_.height();

    setBackgroundBrush(background_);
    setSceneRect(0, 0, width_, height_);
}

void City::setClock(QTime clock)
{
    clock_ = clock;
}

void City::addStop(std::shared_ptr<Interface::IStop> stop)
{
    int x = stop.get()->getLocation().giveX();
    int y = stop.get()->getLocation().giveY();
    StopItem* stopGraph = new StopItem(x, height_- y, stop);
    stops_.push_back(stopGraph);
    addItem(stopGraph);

    std::shared_ptr<CourseSide::Stop> stop_ = std::dynamic_pointer_cast<CourseSide::Stop>(stop);
}

void City::startGame()
{
    gamestate_ = true;
    int numNysse = buses_.size();
    int numPassenger = 0;
    for (auto bus : buses_) {
        numPassenger += bus.get()->getPassengers().size();
    }
    for (auto stop : stops_) {
        numPassenger += stop->getRelatedObj().get()->getPassengers().size();
    }
    statisticsif_ = std::make_shared<Statistics>(numNysse, numPassenger);

}

void City::addActor(std::shared_ptr<Interface::IActor> newactor)
{
    int dataType = getActorType(newactor);
    if (dataType != 0) {
        ActorItem* actorGraph = new ActorItem(width_, height_, dataType, newactor);
        actors_.push_back(actorGraph);
        if (gamestate_) {
            statisticsif_->newNysse();
            // Store them in a "temporary" vector to fire in the QGraphicsScene::advance()
            temp_actors_.push_back(actorGraph);
        }
        else {
            addItem(actorGraph);
        }
        if (dataType == 1){
            std::shared_ptr<CourseSide::Nysse> newBus = std::dynamic_pointer_cast<CourseSide::Nysse>(newactor);
            buses_.push_back(newBus);
//            statisticsif_->newNysse();
        }
    }
    else {
        if (gamestate_) {
            statisticsif_->morePassengers(1);
        }
    }
}

void City::removeActor(std::shared_ptr<Interface::IActor> actor)
{
//    int dataType = getActorType(actor);
    for (auto it = actors_.begin(); it != actors_.end(); it++) {
        if ((*it)->getRelatedObj().get() == actor.get()) {
            if (getActorType(actor) == 1) {
                // This has two scenarios:
                // 1. Delete a bus which bus.isRemoved() == false (bus at final stop)
                // 2. Delete a bus which bus.isRemoved() == true (bus is shot)
                std::shared_ptr<CourseSide::Nysse> bus = std::dynamic_pointer_cast<CourseSide::Nysse>(actor);
                int passengerNum = bus->getPassengers().size();
                bool isShot = bus->isRemoved();
                if (isShot) {
                    // Score because is got destroyed
                    statisticsif_->nysseDestroyed(passengerNum+1);
                }
                else {
                    statisticsif_->nysseLeft();
                    bus->remove();
                }
                // Either way, reduce passengers in statistics
                statisticsif_->lessPassengers(passengerNum);
            }
            else {
                statisticsif_->lessPassengers(1);
            }
//            (*it)->remove();
            it = actors_.erase(it);
            break;
        }
    }
}

void City::actorRemoved(std::shared_ptr<Interface::IActor> actor)
{

}

bool City::findActor(std::shared_ptr<Interface::IActor> actor) const
{
    for (auto it = actors_.begin(); it != actors_.end(); it++) {
        if ((*it)->getRelatedObj().get() == actor.get()) {
            if ((*it)->getRelatedObj().get()->isRemoved()) {
                return true;
            }
            else {
                return false;
            }
        }
    }
    return false;
}

void City::actorMoved(std::shared_ptr<Interface::IActor> actor)
{
    for (auto it = actors_.begin(); it != actors_.end(); it++) {
        if ((*it)->getRelatedObj().get() == actor.get()) {
            (*it)->setCoord();
        }
    }
}

std::vector<std::shared_ptr<Interface::IActor> > City::getNearbyActors(Interface::Location loc) const
{
    std::vector<std::shared_ptr<Interface::IActor>> nearbyActors;
    for (auto const& actor : actors_) {
        if (actor->getRelatedObj().get()->giveLocation().isClose(loc)) {
            nearbyActors.push_back(actor->getRelatedObj());
        }
    }
    return nearbyActors;
}

bool City::isGameOver() const
{
    return gameOver_;
}

int City::getActorType(std::shared_ptr<Interface::IActor> actor)
{
    if (actor.get()) {
        auto& r = *actor.get();
        std::string typeName = typeid(r).name();
        for (int i = 0; i < int(ACTOR_NAMES.size()); i++) {
            auto found = typeName.find(ACTOR_NAMES[i]);
            if (found != std::string::npos) {
                return i;
            }
        }
        return 0;
    }
    return 0;
}

void City::cityInit(int level, int mapsize)
{
    level_ = level;
    mapsize_ = mapsize;
}

std::pair<int, int> City::getBGsize()
{
    return std::make_pair(width_, height_);
}

std::shared_ptr<Statistics> City::getStats() const
{
    return statisticsif_;
}

void City::setGameOver()
{
    gamestate_ = false;
    gameOver_ = true;

}

void City::advance()
{
    if (gamestate_) {
        tictac_++;

        // Add passengers randomly from 1-10 at every 500 tictac (about 15 second)
        if (tictac_ % 500 == 0) {
            int num = rand() % 10 + 1;
            statisticsif_->morePassengers(num);  
            // if normal
            if (level_ == 1){
                Interface::Location actorLocation;
                actorLocation.setXY(rand()%(width_-10)+5, rand()%(height_-10)+5); // random on the screen
                std::shared_ptr<Interface::IActor> newActor = std::make_shared<Enemy>( actorLocation, buses_ );
                addActor(newActor);
            }
            // if easy
            Interface::Location actorLocation;
            actorLocation.setXY(rand()%(width_-10)+5, rand()%(height_-10)+5); // random on the screen
            std::shared_ptr<Interface::IActor> newActor = std::make_shared<Enemy>( actorLocation, buses_ );
            addActor(newActor);
            tictac_ = 0;
        }

        // Add buses graphics
        for (auto elem : temp_actors_) {
            addItem(elem);
        }
        temp_actors_.clear();

        // Advance to QQgraphicItem
        QGraphicsScene::advance();
        update();
    }
}

}
