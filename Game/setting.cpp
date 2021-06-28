#include "setting.h"
#include "ui_setting.h"

namespace StudentSide {
Setting::Setting(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    for (QString label : LEVEL_LABELS) {
        ui->levelComboBox->addItem(label);
    }
    ui->levelComboBox->setCurrentIndex(0);
    for (QString label : MAPSIZE_LABELS) {
        ui->mapComboBox->addItem(label);
    }
    ui->mapComboBox->setCurrentIndex(0);
    for (QString label : HERO_LABELS) {
        ui->characterComboBox->addItem(label);
    }
    ui->characterComboBox->setCurrentIndex(0);
}

Setting::~Setting()
{
    delete ui;
}

void Setting::on_buttonBox_accepted()
{
    level_ = Level(ui->levelComboBox->currentIndex());
    mapsize_ = MapSize(ui->mapComboBox->currentIndex());
    hero_ = Hero(ui->characterComboBox->currentIndex());
    emit okButtonPressed(level_, mapsize_, hero_);
}
}
