#ifndef START_WINDOW_H
#define START_WINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class StartWindow;
}
QT_END_NAMESPACE

class StartWindow : public QMainWindow
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);
    ~StartWindow() override;

private slots:
    void on_participant_clicked();

    void on_miner_clicked();

private:
    Ui::StartWindow *ui;
};
#endif
