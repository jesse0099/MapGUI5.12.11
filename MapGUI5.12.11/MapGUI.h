#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MapGUI.h"

class MapGUI : public QMainWindow
{
    Q_OBJECT

public:
    MapGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::MapGUIClass ui;
};
