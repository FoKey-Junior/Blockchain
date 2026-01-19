#include <QFileDialog>
#include <QMessageBox>
#include <QByteArray>
#include <QFileInfo>
#include <QString>

#include "main_window.h"
#include "ui_main_window.h"
#include "../file_sharing/Sending.h"

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
    QStringList selected_files = QFileDialog::getOpenFileNames(
        this,
        "Выберите файлы",
        QString(),
        "Все файлы (*.*)"
        );

    ui->label->setText(selected_files.join("\n"));

    file_paths.clear();

    for (const auto& file : selected_files) {
        QFileInfo info(file);
        file_names.push_back(info.fileName().toStdString());
        file_paths.push_back(file.toStdString());
    }
}

void MainWindow::on_sending_files_clicked()
{
    QString receiver_address_text = ui->line_receiver_address->text().trimmed();
    QByteArray receiver_address_swap = QByteArray::fromHex(receiver_address_text.toLatin1());

    if (receiver_address_swap.size() != crypto_generichash_BYTES) {
        QMessageBox::warning(this, "Неверный адрес", "Адрес получателя должен состоять из 32 символов");
        return;
    }

    if (file_paths.empty()) {
        QMessageBox::information(this, "Выберите файлы", "Сначала выберите файлы!");
        return;
    }

    std::memcpy(sender_address, user.get_address_bytes(), sizeof(sender_address));
    std::memcpy(receiver_address, receiver_address_swap.constData(), crypto_generichash_BYTES);
    Sending sending(sender_address, receiver_address, std::move(file_names), std::move(file_paths), user);
}

MainWindow::~MainWindow() {
    delete ui;
}
