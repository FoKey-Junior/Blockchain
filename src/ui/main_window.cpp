#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QTimer>
#include <iomanip>
#include <sstream>

#include "main_window.h"
#include "ui_main_window.h"
#include "../file_sharing/Sending.h"

#include <thread>
#include <chrono>
#include <iostream>
#include "../../include/blockchain/Block.h"

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
    , local_blockchain(user.get_address_bytes())
{
    ui->setupUi(this);

    ui->line_sender_address->setHtml(
        "<div style='text-align: center;'>Ваш адрес: " +
        QString::fromStdString(user.get_address()) +
        "</div>"
    );

    // Устанавливаем блокчейн в Node
    node.set_blockchain(&local_blockchain);
    
    // Устанавливаем callback для обновления view при получении новых блоков
    node.set_on_blockchain_updated([this]() {
        // Обновляем view в главном потоке через QTimer::singleShot
        QTimer::singleShot(0, this, [this]() {
            update_blockchain_view();
        });
    });

    // Запускаем Node (своё слушание)
    node.start();

    // Запускаем io_context в отдельном потоке
    std::thread([this]() {
        io_context.run();
    }).detach();

    // Подключаемся к серверу через публичный метод Node
    node.connect_to_server("213.176.117.68", 12345);

    // Настройка таймера для обновления отображения блокчейна
    blockchain_update_timer = new QTimer(this);
    connect(blockchain_update_timer, &QTimer::timeout, this, &MainWindow::update_blockchain_view);
    blockchain_update_timer->start(2000); // Обновление каждые 2 секунды
    
    // Первоначальное обновление
    update_blockchain_view();

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

QString MainWindow::address_to_hex(const unsigned char* addr, size_t len) const {
    QString hex;
    hex.reserve(len * 2);
    for (size_t i = 0; i < len; ++i) {
        hex.append(QString::number(addr[i], 16).rightJustified(2, '0'));
    }
    return hex;
}

QString MainWindow::format_block_html(const Block& block, size_t index) const {
    QString html;
    QString block_address = address_to_hex(block.get_address(), crypto_generichash_BYTES);
    QString sender_address = address_to_hex(block.get_sender(), crypto_generichash_BYTES);
    QString receiver_address = address_to_hex(block.get_receiver(), crypto_generichash_BYTES);
    
    // Преобразуем время в строку
    auto time = block.get_time();
    auto time_t = std::chrono::system_clock::to_time_t(time);
    std::tm tm_buf;
#ifdef _WIN32
    localtime_s(&tm_buf, &time_t);
#else
    localtime_r(&time_t, &tm_buf);
#endif
    std::ostringstream time_stream;
    time_stream << std::put_time(&tm_buf, "%H:%M %d.%m.%Y");
    QString time_str = QString::fromStdString(time_stream.str());
    
    // Форматируем блок в красивый HTML
    html += "<div style='margin-bottom: 15px; padding: 12px; border: 2px solid #4a90e2; border-radius: 8px; background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%);'>";
    html += "<div style='font-size: 14px; font-weight: bold; color: #2c3e50; margin-bottom: 8px;'>";
    html += "Блок #" + QString::number(index + 1);
    html += "</div>";
    html += "<div style='font-size: 11px; color: #555; margin-bottom: 6px;'>";
    html += "<strong>Адрес:</strong> <span style='font-family: monospace; color: #27ae60;'>" + block_address + "</span>";
    html += "</div>";
    html += "<div style='font-size: 11px; color: #555; margin-bottom: 6px;'>";
    html += "<strong>Отправитель:</strong> <span style='font-family: monospace; color: #3498db;'>" + sender_address.mid(0, 16) + "...</span>";
    html += "</div>";
    html += "<div style='font-size: 11px; color: #555; margin-bottom: 6px;'>";
    html += "<strong>Получатель:</strong> <span style='font-family: monospace; color: #e74c3c;'>" + receiver_address.mid(0, 16) + "...</span>";
    html += "</div>";
    html += "<div style='font-size: 11px; color: #555; margin-bottom: 4px;'>";
    html += "<strong>Время:</strong> <span style='color: #8e44ad;'>" + time_str + "</span>";
    html += "</div>";
    
    // Показываем количество файлов
    const auto& files = block.get_files();
    if (!files.empty()) {
        html += "<div style='font-size: 11px; color: #555;'>";
        html += "<strong>Файлов в блоке:</strong> <span style='color: #16a085; font-weight: bold;'>" + QString::number(files.size()) + "</span>";
        html += "</div>";
    }
    
    html += "</div>";
    
    return html;
}

void MainWindow::update_blockchain_view() {
    // Получаем блокчейн от Node (если есть) или используем локальный
    Blockchain* blockchain_to_show = node.get_blockchain();
    if (!blockchain_to_show) {
        blockchain_to_show = &local_blockchain;
    }
    
    const auto& chain = blockchain_to_show->get_chain();
    
    QString html1, html2;
    html1 += "<!DOCTYPE HTML><html><head><meta charset='utf-8'>";
    html1 += "<style>body { font-family: 'Segoe UI', Arial, sans-serif; padding: 10px; background: #f8f9fa; }</style>";
    html1 += "</head><body>";
    
    html2 += "<!DOCTYPE HTML><html><head><meta charset='utf-8'>";
    html2 += "<style>body { font-family: 'Segoe UI', Arial, sans-serif; padding: 10px; background: #f8f9fa; }</style>";
    html2 += "</head><body>";
    
    // Разделяем блоки на две части
    size_t mid = chain.size() / 2;
    
    if (chain.empty()) {
        html1 += "<div style='text-align: center; padding: 20px; color: #999;'>Блокчейн пуст</div>";
        html2 += "<div style='text-align: center; padding: 20px; color: #999;'>Блокчейн пуст</div>";
    } else {
        // Первая половина в blockchain_viewing_1
        for (size_t i = 0; i < mid && i < chain.size(); ++i) {
            html1 += format_block_html(chain[i], i);
        }
        
        // Вторая половина в blockchain_viewing_2
        for (size_t i = mid; i < chain.size(); ++i) {
            html2 += format_block_html(chain[i], i);
        }
        
        // Если нет блоков во второй половине, показываем сообщение
        if (mid >= chain.size()) {
            html2 += "<div style='text-align: center; padding: 20px; color: #999;'>Продолжение блокчейна будет здесь</div>";
        }
    }
    
    html1 += "</body></html>";
    html2 += "</body></html>";
    
    ui->blockchain_viewing_1->setHtml(html1);
    ui->blockchain_viewing_2->setHtml(html2);
}
