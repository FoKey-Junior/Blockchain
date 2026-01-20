#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>
#include <sodium.h>
#include <string>
#include <vector>

#include "../../include/blockchain/User.h"
#include "../../include/network/Node.h"

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

    unsigned char sender_address[crypto_generichash_BYTES]{};
    unsigned char receiver_address[crypto_generichash_BYTES]{};

    std::vector<std::string> file_names;
    std::vector<std::string> file_paths;

private slots:
    void on_file_selection_clicked();
    void on_sending_files_clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif
