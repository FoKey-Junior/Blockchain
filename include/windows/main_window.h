#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <sodium.h>
#include <string>
#include <vector>

#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Blockchain.h"
#include "../../include/network/Node.h"
#include <QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;

    User user;

    asio::io_context io_context;
    Node node;
    Blockchain local_blockchain;

    unsigned char sender_address[crypto_generichash_BYTES]{};
    unsigned char receiver_address[crypto_generichash_BYTES]{};

    std::vector<std::string> file_names;
    std::vector<std::string> file_paths;
    
    QTimer* blockchain_update_timer;
    
    void update_blockchain_view();
    QString format_block_html(const Block& block, size_t index) const;
    QString address_to_hex(const unsigned char* addr, size_t len) const;

private slots:
    void on_file_selection_clicked();
    void on_sending_files_clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif
