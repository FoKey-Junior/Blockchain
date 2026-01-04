#include "../../include/Api.h"
#include "../../include/core/Wallet.h"
#include "../../include/core/Transaction.h"

void Api::start_server(unsigned short const port) {
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/favicon.ico")([]() {
        return crow::response(200, "");
    });

    CROW_ROUTE(app, "/api")([](){
        Wallet alice;
        Wallet bob;

        float amount = 250;

        Transaction tx(alice.get_address_bytes(), bob.get_address_bytes(), 100);
        tx.sign(alice.get_private_key());

        if (tx.verify(alice.get_public_key())) {
            alice.balance -= amount;
            bob.balance += amount;
            std::cout << "Signature valid!\n";
        } else {
            std::cout << "Signature INVALID!\n";
        }
        tx.print();
        std::cout << "Balance " << alice.get_address() << ": " << alice.balance << std::endl;
        std::cout << "Balance " << bob.get_address() << ": " << bob.balance << std::endl;

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