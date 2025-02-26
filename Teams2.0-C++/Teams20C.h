#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Teams20C.h"

class Teams20C : public QMainWindow
{
    Q_OBJECT

public:
    Teams20C(QWidget *parent = nullptr);
    ~Teams20C();

private:
    Ui::Teams20CClass ui;
};
