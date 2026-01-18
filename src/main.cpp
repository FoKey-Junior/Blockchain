#include "../include/api/Api.h"
#include "../include/windows/start_window.h"

#include <thread>
#include <QApplication>

int main(int argc, char *argv[]) {
    std::thread local_api([](){
        (Api::start_server(4000));
    });
    local_api.detach();

    QApplication app(argc, argv);
    StartWindow window;
    window.show();

    return app.exec();
}
