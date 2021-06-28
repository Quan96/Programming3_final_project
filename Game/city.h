#ifndef CITY_H
#define CITY_H

#include "interfaces/icity.hh"
//#include "interfaces/istop.hh"
#include "graphics/simpleactoritem.hh"
#include "stopItem.h"
#include "actorItem.h"
#include "statistics.h"

#include <QTime>
#include <utility>
#include <QObject>

namespace StudentSide {

class City: public QGraphicsScene, public Interface::ICity{
    Q_OBJECT
public:
    explicit City();
    ~City();

    // CityIF interface
    void setBackground(QImage& basicbackground, QImage& bigbackground) override;
    void setClock(QTime clock) override;
    void addStop(std::shared_ptr<Interface::IStop> stop) override;
    void startGame() override;
    void addActor(std::shared_ptr<Interface::IActor> newactor) override;
    void removeActor(std::shared_ptr<Interface::IActor> actor) override;
    void actorRemoved(std::shared_ptr<Interface::IActor> actor) override;
    bool findActor(std::shared_ptr<Interface::IActor> actor) const override;
    void actorMoved(std::shared_ptr<Interface::IActor> actor) override;
    std::vector<std::shared_ptr<Interface::IActor>> getNearbyActors(Interface::Location loc) const override;
    bool isGameOver() const override;

    /**
     * @brief get the IActor type
     * @param actor The shared pointer to the actor
     * @return the integer match the type of actor
     */
    int getActorType(std::shared_ptr<Interface::IActor> actor);

    /**
     * @brief init cityif
     * @param level The difficulty of the game
     * @param mapsize The size of the map
     */
    void cityInit(int level, int mapsize);

    /**
     * @brief get the map background size
     * @return a pair of width and height
     */
    std::pair<int, int> getBGsize();

    /**
     * @brief set the statisticIF
     * @param statistics shared pointer to StatisticIF
     */
    std::shared_ptr<Statistics> getStats() const;

    /**
     * @brief set the gamestate_ and gameover_ status
     */
    void setGameOver();

public slots:
    /**
     * @brief update the QGraphicsScene
     */
    void advance();

signals:
    /**
     * @brief signal for update score
     * @param score Added score
     */
    void actorDestroyed(int score);

private:
    const std::vector<std::string> ACTOR_NAMES = {"Passenger", "Nysse", "Enemy"};
    QImage background_;
    QTime clock_;
    std::vector<StopItem*> stops_;
    std::list<ActorItem*> actors_;
    bool gamestate_;
    bool gameOver_;
    int level_;
    int mapsize_;
    int width_;
    int height_;
    int tictac_;
    std::shared_ptr<Statistics> statisticsif_;
    std::vector<ActorItem*> temp_actors_;
    std::vector<std::shared_ptr<CourseSide::Nysse>> buses_;
};
}

#endif // CITY_H
