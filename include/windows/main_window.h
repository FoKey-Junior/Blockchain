#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_file_selection_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAIN_WINDOW_H
