#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphics/simplemainwindow.hh"
#include "core/logic.hh"
#include "city.h"
#include "statistics.h"

#include <vector>
#include <memory>
#include <QString>
#include <utility>
#include <QGraphicsPixmapItem>
#include <QLabel>

namespace Ui {
class MainWindow;
}

namespace StudentSide {

enum Level {EASY, NORMAL};
const std::vector<QString> LEVEL_LABELS = {
    "Easy", "Normal"
};

enum MapSize {SMALL, ZOOMABLE};
const std::vector<QString> MAPSIZE_LABELS = {
    "Small", "Zoomable"
};

enum Hero {IRONMAN, CAPTAINAMERICA, THOR};
const std::vector<QString> HERO_LABELS = {
    "Iron Man", "Captain America", "Thor"
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief initGameWindow
     * @param level dificulty
     * @param mapsize Small or Zoomable
     * @param hero hero type
     */
    void initGameWindow(Level level, MapSize mapsize, Hero hero);

    /**
     * @brief increase Play Time
     */
    void increasePlayTime();
    // Slots from statistics


    void goToSetting();

private:
    const QString SMALL_MAP_IMG = ":/offlinedata/offlinedata/kartta_pieni_500x500.png";
    const QString LARGE_MAP_IMG = ":/offlinedata/offlinedata/kartta_iso_1095x592.png";

    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *playTimeTimer;
    int width_ = 500; //pxls
    int height_ = 500;

    QImage basicbg_;
    QImage bigbg_;
    std::shared_ptr<City> cityif_;
    std::shared_ptr<CourseSide::Logic> gameLogic_;
    std::shared_ptr<Statistics> statistics_;
    int level_;

    double elapsed_;
};

} //namespace
#endif // MAINWINDOW_H
