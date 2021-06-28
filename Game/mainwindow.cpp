#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting.h"
#include "playerItem.hh"

#include <QDebug>
#include <QElapsedTimer>
#include <QMessageBox>
#include <QVBoxLayout>

const int PADDING = 10;

namespace StudentSide {

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), basicbg_(QImage(SMALL_MAP_IMG)), bigbg_(QImage(LARGE_MAP_IMG)){

    // Initial window
    QWidget *wdg = new QWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout(wdg);
    QLabel *welcomeLabel = new QLabel("Avenger Game");
    welcomeLabel->setFont(QFont("times", 20));
    welcomeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    vlayout->addWidget(welcomeLabel);
    QPushButton *startButton = new QPushButton(tr("&Setting"));
    vlayout->addWidget(startButton);
    QPushButton *exitButton = new QPushButton(tr("&Exit"));
    vlayout->addWidget(exitButton);
    wdg->setLayout(vlayout);
    setCentralWidget(wdg);

    connect(startButton, &QPushButton::clicked, this, &MainWindow::goToSetting);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::close);
}

MainWindow::~MainWindow() {
    delete ui;
    gameLogic_ = nullptr;
    cityif_ = nullptr;
    statistics_ = nullptr;
}

void MainWindow::initGameWindow(Level level, MapSize mapsize, Hero hero)
{
    // Initalize all the variables
    ui = new Ui::MainWindow;
    cityif_ = nullptr;
    gameLogic_ = nullptr;
    statistics_ = nullptr;
    elapsed_ = 0;

    ui->setupUi(this);
    connect(ui->exitButton, &QPushButton::clicked, this, &MainWindow::close);
    level_ = level;

    cityif_ = std::make_shared<City>();
    cityif_->cityInit(level, mapsize);
    cityif_->setBackground(basicbg_, bigbg_);
    std::pair<int, int> backgroundSize = cityif_->getBGsize();
    width_ = backgroundSize.first;
    height_ = backgroundSize.second;
    ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->gameView->setScene(cityif_.get());
    ui->gameView->setFixedSize(width_, height_);
    //    ui->centralwidget->setFixedSize(width_ + ui->exitButton->width() + PADDING, height_ + PADDING);
        ui->centralwidget->setFixedSize(width_ + ui->passengerCountLabel->width() + ui->passengerCountLCD->width() + PADDING*3, height_ + PADDING);

    // add player to cityif_
    Interface::Location playerLocation;
    playerLocation.setXY(width_/2, height_-40); // bottom center of the scene
    std::shared_ptr<StudentSide::PlayerActor> playerActor = std::make_shared<StudentSide::PlayerActor>(playerLocation);
    StudentSide::PlayerItem *playerItem = new StudentSide::PlayerItem(playerActor, hero);
    playerItem->setCity(cityif_);
    playerItem->setFlags(QGraphicsItem::ItemIsFocusable);
    playerItem->setFocus();
    cityif_->addItem(playerItem);

    ui->timerLCD->setPalette(Qt::black);
    ui->scoreLCD->setPalette(Qt::black);
    ui->busCountLCD->setPalette(Qt::red);
    ui->passengerCountLCD->setPalette(Qt::blue);

    ui->busCountLabel->move(width_ + PADDING, PADDING);
    ui->busCountLCD->move(width_ + PADDING*2 + ui->passengerCountLabel->width(), PADDING);
    ui->passengerCountLabel->move(width_ + PADDING, 50);
    ui->passengerCountLCD->move(width_ + PADDING*2 + ui->passengerCountLabel->width(), 50);
    ui->scoreLabel->move(width_ + PADDING, 100);
    ui->scoreLCD->move(width_ + PADDING, 120);
    ui->timerLabel->move(width_ + PADDING, 180);
    ui->timerLCD->move(width_ + PADDING, 200);
    ui->exitButton->move(width_ + PADDING, 300);

    resize(minimumSizeHint());


    gameLogic_ = std::make_shared<CourseSide::Logic>();

    // Init steps to ready for game state
    if (gameLogic_->readOfflineData(CourseSide::DEFAULT_BUSES_FILE, CourseSide::DEFAULT_STOPS_FILE)) {
        gameLogic_->takeCity(cityif_);
        gameLogic_->setTime(15,0);
        gameLogic_->finalizeGameStart();
        statistics_ = cityif_->getStats();
    }
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, cityif_.get(), &City::advance);
    connect(timer, &QTimer::timeout, this, &MainWindow::increasePlayTime);
    timer->start(1000/33); // 30 fps
}


void MainWindow::goToSetting()
{
    Setting gameSetting(this);
    gameSetting.setModal(true);
    connect(&gameSetting, &Setting::okButtonPressed, this, &MainWindow::initGameWindow);
    gameSetting.exec();
}

void MainWindow::increasePlayTime()
{
    ui->scoreLCD->display(statistics_.get()->getScore());
    ui->busCountLCD->display(statistics_.get()->getNysseNumber());
    ui->passengerCountLCD->display(statistics_.get()->getPassengerNumber());
    // Configure play time
    int playTime;
    if (!level_) {
        // 3 minute play
        playTime = 3;
    }
    else {
        // 1 minute play
        playTime = 1;
    }
    elapsed_++;
    if (elapsed_ == 60*33*playTime) {
        cityif_->setGameOver();
//        playTimeTimer->stop();
        timer->stop();

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Congratulation", "Game over,\n Do you want to quit?",
                                        QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            MainWindow::close();
        }
        else {
            goToSetting();
        }

    }
    else {
        ui->timerLCD->display(int(elapsed_/33));
    }
}
}
