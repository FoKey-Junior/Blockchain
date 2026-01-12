#include "../../include/Api.h"
#include "../../include/core/Wallet.h"
#include "../../include/core/Transaction.h"
#include "../../include/core/Mempool.h"
#include "../../include/core/Miner.h"

void Api::start_server(unsigned short const port) {
    crow::SimpleApp app;
    Mempool mempool;
    app.loglevel(crow::LogLevel::Warning);

    CROW_ROUTE(app, "/favicon.ico")([]() {
        return crow::response(200, "");
    });


    CROW_ROUTE(app, "/api/new/transaction")([&mempool](){
        Wallet alice;
        Wallet bob;
        uint64_t amount = 250;

        Transaction tx(alice.get_address_bytes(), bob.get_address_bytes(), amount);
        tx.sign(alice.get_private_key());

        if (tx.verify(alice.get_public_key())) {
            alice.balance -= amount;
            bob.balance += amount;
            mempool.add_transaction(tx); // ✅ теперь работает
            std::cout << "Signature valid!\n";
        }

        tx.print();
        return "server working properly";
    });

    CROW_ROUTE(app, "/api/new/miner")([&mempool](){
        std::thread th([&mempool](){
            Miner miner(mempool.pool); // ✅ теперь pool виден
            miner.run();
        });
        th.detach();

        return "miner started";
    });


    CROW_ROUTE(app, "/api/new/wallet")([](){
        Wallet wallet;
        return "the new wallet has been successfully created";
    });

    app.port(port).run();
}