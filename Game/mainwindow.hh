#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "interfaces/icity.hh"

#include <QMainWindow>
#include <QTimer>
#include <QPushButton>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//    void setClock(QTime clock);
//    void setBackGround(QImage& basicbackground, QImage& bigbackground);
    void addStop(std::shared_ptr<Interface::IStop> stop);
    void startGame();

private:
    Ui::MainWindow *ui;

    QTimer timer_;
    QGraphicsView* view_;

    static const QString S_START;
    static const QString S_STOP;

};

#endif // MAINWINDOW_HH
