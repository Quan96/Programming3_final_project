#ifndef BULLET_HH
#define BULLET_HH

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QString>

#include "city.h"
#include "setting.h"

namespace StudentSide {

class Bullet : public QGraphicsPixmapItem
{

public:
    explicit Bullet(QString direction, std::shared_ptr<City> city, int hero, QGraphicsItem *parent=nullptr);

//    Bullet(QString direction, bool isHero, QGraphicsItem *parent=nullptr);

    /**
     * @brief return the type of the QGraphicsItem
     * @return graphicType
     */
    enum {graphicType = 1};
    int type() const override;

    /**
     * @brief move the bullet
     * @exception no throw
     */
    void move();

    /**
     * @brief scene-controlled animation
     * @param step 0 or 1
     */
    void advance(int step) override;

private:
    QString direction_ = "UP";
    std::shared_ptr<City> city_;
    int coef_ = 10;
    const QString BEAMLOGO = ":/images/images/beam.png";
    const QString SHIELDLOGO = ":/images/images/shield.png";
    const QString AXELOGO = ":/images/images/axe.png";
};

}
#endif // BULLET_HH
