#include "main_window.h"
#include "ui_main_window.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_file_selection_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Выбрать файлы",
        QString(),
        "Все файлы (*.*)"
        );

    ui->label->setText(files.join("\n"));
}
