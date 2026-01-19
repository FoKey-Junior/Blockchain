#include "../../include/api/Api.h"
#include "../../include/blockchain/User.h"
#include "../../include/blockchain/Transaction.h"
#include "../../include/blockchain/Mempool.h"
#include "../../include/blockchain/Miner.h"

void Api::start_server(unsigned short const port) {
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);
    Mempool mempool;

    CROW_ROUTE(app, "/favicon.ico")([]() {
        return crow::response(200, "");
    });
    //
    // CROW_ROUTE(app, "/api/new/miner")([&mempool, &alice, &bob](){
    //     Transaction transaction(alice.get_address_bytes(), bob.get_address_bytes());
    //     transaction.sign(alice.get_private_key());
    //
    //     if (transaction.verify(alice.get_public_key())) {
    //         mempool.add_transaction(transaction);
    //         std::cout << "Signature valid!\n";
    //     }
    //
    //     transaction.print();
    //
    //     return "miner started";
    // });
    //
    // CROW_ROUTE(app, "/api/mempool/pop")
    // ([&mempool](const crow::request& req) {
    //     auto txid = req.url_params.get("txid");
    //     if (!txid) {
    //         return crow::response(400, "txid required");
    //     }
    //
    //     bool removed = mempool.remove_transaction(
    //         reinterpret_cast<const unsigned char*>(txid)
    //     );
    //
    //     return removed
    //         ? crow::response(200, "transaction removed")
    //         : crow::response(404, "transaction not found");
    // });
    //
    // CROW_ROUTE(app, "/api/new/user")([](){
    //     User user;
    //     return "the new wallet has been successfully created";
    // });

    app.port(port).run();
}
