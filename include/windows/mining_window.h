#ifndef MINING_WINDOW_H
#define MINING_WINDOW_H

#include <QMainWindow>

#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Blockchain.h"
#include "../../include/blockchain/Miner.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/network/Node.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MiningWindow;
}
QT_END_NAMESPACE

class MiningWindow : public QMainWindow
{
    Q_OBJECT

public:
    MiningWindow(QWidget *parent = nullptr);
    ~MiningWindow();

private:
    Ui::MiningWindow *ui;
    std::unique_ptr<asio::io_context> io_context;
    std::unique_ptr<Node> node;
    std::unique_ptr<std::vector<Transaction>> mempool_vec;
    std::unique_ptr<Blockchain> blockchain;
    std::unique_ptr<Miner> miner;
};
#endif // MINING_WINDOW_H
