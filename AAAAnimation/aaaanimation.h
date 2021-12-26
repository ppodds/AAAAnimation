#pragma once

#include <QtWidgets/QWidget>
#include "ui_aaaanimation.h"

class AAAAnimation : public QWidget
{
    Q_OBJECT

public:
    AAAAnimation(QWidget *parent = Q_NULLPTR);

private:
    Ui::AAAAnimationClass ui;
};
