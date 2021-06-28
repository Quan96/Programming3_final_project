#include "stopItem.h"

StudentSide::StopItem::StopItem(int x, int y, std::shared_ptr<Interface::IStop> stop, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), x_(x), y_(y), relatedStopObj_(stop)
{
    setPixmap(QPixmap(BUSSTOPLOGO).scaled(WIDTH, HEIGHT));
    setPos(x_, y_);
}

void StudentSide::StopItem::advance(int step)
{
    if (!step) {
        return;
    }
    // Get number of passengers in the stop
    int numPassenger = int(relatedStopObj_->getPassengers().size());
    setToolTip(QString::number(numPassenger));
}

std::shared_ptr<Interface::IStop> StudentSide::StopItem::getRelatedObj()
{
    return relatedStopObj_;
}
