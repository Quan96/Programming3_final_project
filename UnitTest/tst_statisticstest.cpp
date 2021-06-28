#include <QString>
#include <QtTest>

#include "statistics.h"
#include "core/logic.hh"
#include "errors/initerror.hh"


class statisticsTest : public QObject
{
    Q_OBJECT

public:
    statisticsTest();

private Q_SLOTS:
    void testMorePassenger_data();
    void testMorePassenger();
    void testNysseLeft_data();
    void testNysseLeft();
    void testLessPassenger_data();
    void testLessPassenger();
};

statisticsTest::statisticsTest()
{
}

void statisticsTest::testMorePassenger_data()
{
    QTest::addColumn<int>("init");
    QTest::addColumn<int>("num");
    QTest::addColumn<int>("expect");

    QTest::addRow("Normal") << 0 << 16 << 16;
    QTest::addRow("Init negative") << -2 << 10 << 10;
}

void statisticsTest::testMorePassenger()
{
    QFETCH(int, init);
    QFETCH(int, num);
    QFETCH(int, expect);

    StudentSide::Statistics stats_(init, 0);
    stats_.morePassengers(num);

    QVERIFY2(stats_.getPassengerNumber() == expect, "Incorrect result");
}

void statisticsTest::testNysseLeft_data()
{
    QTest::addColumn<int>("init");
    QTest::addColumn<int>("expect");

    QTest::addRow("Normal") << 50 << 49;
    QTest::addRow("No bus") << 0 << 0;
    QTest::addRow("Negative bus") << -10 << 0;
}

void statisticsTest::testNysseLeft()
{
    QFETCH(int, init);
    QFETCH(int, expect);

    StudentSide::Statistics stats_(init, 0);
    stats_.nysseLeft();

    QVERIFY2(stats_.getNysseNumber() == expect, "Incorrect result");
}

void statisticsTest::testLessPassenger_data()
{
    QTest::addColumn<int>("init");
    QTest::addColumn<int>("num");
    QTest::addColumn<int>("expect");

    QTest::addRow("Normal") << 50 << 16 << 34;
    QTest::addRow("Init negative") << -2 << 10 << 0;
    QTest::addRow("Remove more than exist") << 10 << 12 << 10;
}

void statisticsTest::testLessPassenger()
{
    QFETCH(int, init);
    QFETCH(int, num);
    QFETCH(int, expect);

    StudentSide::Statistics stats_(0, init);
    stats_.lessPassengers(num);

    QVERIFY2(stats_.getPassengerNumber() == expect, "Incorrect result");
}

QTEST_APPLESS_MAIN(statisticsTest)

#include "tst_statisticstest.moc"
