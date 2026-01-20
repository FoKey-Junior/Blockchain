#include "start_window.h"
#include "ui_start_window.h"

#include "main_window.h"
#include "mining_window.h"

StartWindow::StartWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartWindow)
{
    ui->setupUi(this);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_participant_clicked()
{
    MainWindow *window = new MainWindow;
    window->show();
    close();
}

void StartWindow::on_miner_clicked()
{
    MiningWindow *window = new MiningWindow;
    window->show();
    close();
}

