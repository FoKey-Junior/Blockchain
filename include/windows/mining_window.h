#ifndef MINING_WINDOW_H
#define MINING_WINDOW_H

#include <QMainWindow>

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
};
#endif // MINING_WINDOW_H
