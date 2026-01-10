#include "../../include/Api.h"
#include "../../include/core/Wallet.h"
#include "../../include/core/Transaction.h"
#include "../../include/core/Mempool.h"

void Api::start_server(unsigned short const port) {
    Mempool mempool;
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/favicon.ico")([]() {
        return crow::response(200, "");
    });

    CROW_ROUTE(app, "/api")([&mempool](){
        const Wallet alice;
        const Wallet bob;

        uint64_t amount = 250;

        const auto transaction = std::make_shared<Transaction>(
            alice.get_address_bytes(),
            bob.get_address_bytes(),
            amount
        );

        transaction->sign(alice.get_private_key());

        if (!transaction->verify(alice.get_public_key())) {
            return "Invalid signature";
        }

        if (!mempool.add_transaction(transaction)) {
            return "Transaction rejected by mempool";
        }

        transaction->print();
        return "Transaction added to mempool";
    });

    CROW_ROUTE(app, "/api/new/wallet")([](){
        Wallet wallet;
        return "the new wallet has been successfully created";
    });

    app.port(port).run();
}