#include "fing.h"
#include "ui_fing.h"

fing::fing(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fing)
{
    ui->setupUi(this);

}

fing::~fing()
{
    delete ui;
}

