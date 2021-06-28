#ifndef ACTORITEM_H
#define ACTORITEM_H

#include "interfaces/istop.hh"
#include "enemy.hh"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

namespace StudentSide {

class ActorItem : public QGraphicsPixmapItem
{
public:
    explicit ActorItem(int swidth, int sheight, int type, std::shared_ptr<Interface::IActor> actor,
              QGraphicsItem* parent = 0);

    /**
     * @brief set coord position for GraphicsItem
     * @pre the actor given a location
     *
     * @post exception guarantee: strong
     * @exception GameError - actor wasn't given a location.
     */
    void setCoord();

    /**
     * @brief scene-controlled animation
     * @param step 0 or 1
     *
     * @exception no throw
     */
    void advance(int step) override;

    /**
     * @brief get the shared_pointer to the actor in the ActorItem
     * @pre the shared pointer not null
     * @post -
     *
     * @exception GameError - actor not exist
     * @return the shared_pointer to the actor
     *
     */
    std::shared_ptr<Interface::IActor> getRelatedObj();

private:
    int scenewidth_;
    int sceneheight_;
    int type_;
    std::shared_ptr<Interface::IActor> actor_;
    QString BUSLOGO = ":/images/images/buslogo.png";
    QString ENEMYLOGO = ":/images/images/thanos.png";
    int x_;
    int y_;
    int timer = 100;
    int loop = 0;
    QGraphicsTextItem *numberIndicator_;
    bool hasIndicator_;
};

}

#endif // ACTORITEM_H
