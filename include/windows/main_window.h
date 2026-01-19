#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H


#include <QWidget>
#include <sodium.h>
#include <string>
#include <vector>
#include <unordered_map>

#include "../../include/blockchain/User.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    Ui::MainWindow *ui;

    User user;
    unsigned char sender_address[crypto_generichash_BYTES] = {};
    unsigned char receiver_address[crypto_generichash_BYTES] = {};
    std::vector<std::string> file_names = {};
    std::vector<std::string> file_paths = {};

private slots:
    void on_file_selection_clicked();
    void on_sending_files_clicked();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
};

#endif
