#include "../include/api/Api.h"
#include "../include/windows/start_window.h"

#include <thread>
#include <QApplication>

int main(int argc, char *argv[]) {
    std::thread client_api([](){
        (Api::start_server(4000));
    });

    QApplication a(argc, argv);
    StartWindow window;
    window.show();
    int ret = a.exec();

    client_api.join();
    return ret;
}
