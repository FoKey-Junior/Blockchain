#include <QTextBrowser>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QByteArray>

#include "main_window.h"
#include "ui_main_window.h"
#include "../include/core/Transaction.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->line_sender_address->setHtml(
        "<div style='text-align: center;'>Ваш адрес: " +
        QString::fromStdString(user.get_address()) +
        "</div>"
    );
}

void MainWindow::on_file_selection_clicked() {
    QStringList files = QFileDialog::getOpenFileNames(
        this,
        "Выберите файлы",
        QString(),
        "Все файлы (*.*)"
        );

    ui->label->setText(files.join("\n"));

    file_paths.clear();
    for (const auto& file : files) {
        file_paths.push_back(file.toStdString());
    }
}

void MainWindow::on_sending_files_clicked()
{
    if (!file_paths.empty()) {
        for (const auto& file : file_paths) {
            QString text = ui->line_receiver_address->text().trimmed();
            QByteArray bin = QByteArray::fromHex(text.toLatin1());

            if (bin.size() == crypto_generichash_BYTES) {
                std::memcpy(sender_address, user.get_address_bytes(), sizeof(sender_address));
                std::memcpy(receiver_address, bin.constData(), crypto_generichash_BYTES);

                // Transaction transaction(sender_address, receiver_address);
            } else {
                QMessageBox::warning(this, "Неверный адрес", "Адрес получателя должен состоять из 32 символов");
            }
        }
    } else {
        QMessageBox::information(this, "Выберите файлы", "Сначала выберите файлы!");
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
