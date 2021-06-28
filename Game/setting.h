#ifndef SETTING_H
#define SETTING_H

#include "mainwindow.h"

#include <QDialog>

namespace Ui {
class Setting;
}

namespace StudentSide {
class Setting : public QDialog
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();

signals:
    void okButtonPressed(Level, MapSize, Hero);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Setting *ui;
    Level level_;
    MapSize mapsize_;
    Hero hero_;
};

}


#endif // SETTING_H
