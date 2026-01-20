#include "../include/api/Api.h"
#include "../include/windows/start_window.h"

#include <QApplication>
#include <sodium.h>
#include <thread>
#include <asio.hpp>

int main(int argc, char *argv[]) {
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium init failed");
    }

    std::thread local_api([](){
        (Api::start_server(4000));
    });
    local_api.detach();

    QApplication app(argc, argv);
    StartWindow window;
    window.show();

    return app.exec();
}
