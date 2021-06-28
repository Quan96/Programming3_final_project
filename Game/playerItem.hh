#ifndef PLAYERITEM_HH
#define PLAYERITEM_HH

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QString>

#include "bullet.hh"
#include "playeractor.h"

namespace StudentSide {

class PlayerItem : public QGraphicsPixmapItem
{
public:
    explicit PlayerItem(std::shared_ptr<PlayerActor> player,
                        int hero,
                        QGraphicsItem *parent = 0);

    void setCoord();

    /**
     * @brief get the current direction of playerItem
     * @return QString direction
     * @exception no throw
     */
    QString getDirection() const;

    /**
     * @brief set a new direction for playerItem
     * @param new_direction
     * @exception no throw
     */
    void setDirection(QString new_direction);

    /**
     * @brief return the type of the QGraphicsItem
     * @return graphicType
     * @exception no throw
     */
    enum {graphicType = 0};
    int type() const override;

    /**
     * @brief sent to the widget with keyboard input focus when keys are pressed or released.
     * @param event
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief get the shared_pointer to the actor in the ActorItem
     * @pre the shared pointer not null
     * @return the shared_pointer to the actor
     */
    std::shared_ptr<PlayerActor> getRelatedObj();

    /**
     * @brief set the cityIF
     * @pre the shared pointer not null
     * @param city shared pointer to cityIF
     */
    void setCity(std::shared_ptr<City> city);

private:
    int x_;
    int y_;
    QString direction_;
    const QString IRONMAN = ":/images/images/ironman.png";
    const QString CAPTAIN = ":/images/images/captain.png";
    const QString THOR = ":/images/images/thor.png";
    int coef_ = 40;
    int origin_ = coef_ / 2;
    int step = 10;
    std::shared_ptr<StudentSide::City> city_;
    std::shared_ptr<StudentSide::PlayerActor> player_;
    std::pair<int, int> mapSize;
    int hero_;
};

}

#endif // PLAYERITEM_HH
