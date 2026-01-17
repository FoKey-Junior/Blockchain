#ifndef BLOCKCHAIN_API_H
#define BLOCKCHAIN_API_H

#include <thread>
#include <vector>
#include "crow.h"

class Api {
public:
    static void start_server(unsigned short const port);
};

#endif