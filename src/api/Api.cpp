#include "../../include/Api.h"
#include "../../include/core/Wallet.h"

void Api::start_server(unsigned short const port) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api")([](){
        return "server working properly";
    });

    CROW_ROUTE(app, "/api/new/wallet")([](){
        Wallet wallet;
        return "the new wallet has been successfully created";
    });

    CROW_ROUTE(app, "/api/new/transaction")([]() {
        return "the transaction was created successfully";
    });

    app.port(port).run();
}