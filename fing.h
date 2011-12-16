#ifndef FING_H
#define FING_H

#include <QMainWindow>

namespace Ui {
    class fing;
}

class fing : public QMainWindow
{
    Q_OBJECT

public:
    explicit fing(QWidget *parent = 0);
    ~fing();

private:
    Ui::fing *ui;
};
#endif // FING_H
