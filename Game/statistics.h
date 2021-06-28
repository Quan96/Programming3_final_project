#ifndef STATISTICS_H
#define STATISTICS_H

#include "interfaces/istatistics.hh"
#include "core/logic.hh"
#include "errors/initerror.hh"

#include <QObject>
#include <random>

namespace StudentSide {
class Statistics : public Interface::IStatistics {

public:
    explicit Statistics(int nysses, int passengers);
    ~Statistics();
    // StatisticIF interface
    void morePassengers(int num) override;
    void nysseRemoved() override;
    void newNysse() override;
    void nysseLeft() override;

    /**
     * @brief add score to current score
     * @param score added score
     */
    void nysseDestroyed(int score);

    /**
     * @brief Decrease the total number of passengers
     * @param num The number of passengers to remove
     */
    void lessPassengers(int num);

    /**
     * @brief get the number of passengers in real time
     * @return numPassenger_
     */
    int getPassengerNumber();

    /**
     * @brief get the number of buses in real time
     * @return numBuses_
     */
    int getNysseNumber();

    /**
     * @brief get the score in real time
     * @return score_
     */
    int getScore();

private:
   int numNysses_;
   int numPassengers_;
   int score_;
};
}
#endif // STATISTICS_H
