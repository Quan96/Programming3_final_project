#ifndef STOPITEM_H
#define STOPITEM_H

#include "interfaces/istop.hh"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPixmap>

namespace StudentSide {

const int WIDTH = 15;
const int HEIGHT = 15;

class StopItem : public QGraphicsPixmapItem
{
public:
    explicit StopItem(int x, int y, std::shared_ptr<Interface::IStop> stop,
                           QGraphicsItem* parent = 0);
    void advance(int step) override;

    std::shared_ptr<Interface::IStop> getRelatedObj();

private:
    const QString BUSSTOPLOGO = ":/images/images/busstoplogo.png";
    int x_;
    int y_;
    std::shared_ptr<Interface::IStop> relatedStopObj_;
};
}

#endif // STOPITEM_H
