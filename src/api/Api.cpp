#include "../../include/Api.h"
#include "../../include/core/Wallet.h"
#include "../../include/core/Transaction.h"

void Api::start_server(unsigned short const port) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api")([](){
            Wallet alice;
          Wallet bob;

          float amount = 10;

              // 1. Создаём транзакцию
            Transaction tx(
                alice.get_address_bytes(),  // sender
                bob.get_address_bytes(),    // receiver
                amount
            );

            tx.sign(alice.get_private_key());

            if (tx.verify(alice.get_public_key())) {
                std::cout << "Signature valid!\n";
            } else {
                std::cout << "Signature INVALID!\n";
            }

            tx.print();


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