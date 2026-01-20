#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>

#include "main_window.h"
#include "ui_main_window.h"
#include "../file_sharing/Sending.h"

#include <thread>
#include <chrono>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
    , user()
    , io_context()
    , node(
        io_context,
        12345, // локальный порт клиента (можно любой свободный)
        user.get_public_key(),
        user.get_private_key()
      )
{
    ui->setupUi(this);

    ui->line_sender_address->setHtml(
        "<div style='text-align: center;'>Ваш адрес: " +
        QString::fromStdString(user.get_address()) +
        "</div>"
    );

    // Запускаем Node (своё слушание)
    node.start();

    // Запускаем io_context в отдельном потоке
    std::thread([this]() {
        io_context.run();
    }).detach();

    // Подключаемся к серверу через публичный метод Node
    node.connect_to_server("4.tcp.eu.ngrok.io", 12204);

    std::cout << "Client node started and connecting to server\n";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_file_selection_clicked()
{
    QStringList selected_files = QFileDialog::getOpenFileNames(
        this,
        "Выберите файлы",
        QString(),
        "Все файлы (*.*)"
    );

    ui->label->setText(selected_files.join("\n"));

    file_names.clear();
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
    QByteArray receiver_address_bytes = QByteArray::fromHex(receiver_address_text.toLatin1());

    if (receiver_address_bytes.size() != crypto_generichash_BYTES) {
        QMessageBox::warning(this, "Ошибка", "Неверный адрес получателя");
        return;
    }

    if (file_paths.empty()) {
        QMessageBox::information(this, "Файлы", "Сначала выберите файлы");
        return;
    }

    std::memcpy(sender_address, user.get_address_bytes(), crypto_generichash_BYTES);
    std::memcpy(receiver_address, receiver_address_bytes.constData(), crypto_generichash_BYTES);

    Sending sending(
        sender_address,
        receiver_address,
        std::move(file_names),
        std::move(file_paths),
        user,
        node
    );

    // Маленькая пауза, чтобы TCP соединение успело установиться
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    sending.prepare_and_send();

    std::cout << "Transaction sent to server\n";
}
