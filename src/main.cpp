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


#include "network/Node.h"
#include <asio.hpp>
#include <sodium.h>
#include <iostream>

int main() {
    if (sodium_init() < 0) {
        std::cerr << "Failed to init libsodium\n";
        return 1;
    }

    unsigned char pub_key[crypto_sign_PUBLICKEYBYTES];
    unsigned char priv_key[crypto_sign_SECRETKEYBYTES];
    crypto_sign_keypair(pub_key, priv_key);

    asio::io_context io;

    Node node(io, 12345, pub_key, priv_key);
    node.start();

    std::cout << "Node running on port 12345\n";

    io.run();
}
