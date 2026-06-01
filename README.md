<div align="center">
  
# Blockchain File Transfer (Qt Quick + C++23)

Production-ready pet project: key-based registration/authorization, file transfer, and origin verification via a custom blockchain.

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/CMake-3.25+-green.svg)](https://cmake.org/)
[![libsodium](https://img.shields.io/badge/libsodium-✓-success.svg)](https://libsodium.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

## Features
- User registration (Ed25519 key generation)
- Address-based authorization
- Node-to-node file transfer (TCP)
- Blockchain storage: SHA-256 hash and metadata
- File verification: sender, recipient, block
- Feeless FIFO mempool
- PoA consensus (local validator)
- Light and dark UI themes

**Secure decentralized blockchain-based file transfer system**

*Professional blockchain implementation with a fair FIFO transaction queue*

<div style="margin-top: 20px; font-style: italic; color: #8a2be2; font-size: 0.95em;">
✨ Securing your data with elegance and reliability ✨ <br><br>

> ⚠️ Project under development ⚠️  
> This project is under active development. Features are subject to change, but it already demonstrates a fully functional C++23 backend and a Qt-based frontend.
</div>
</div>

---

## Table of Contents

- [About the Project](#about-the-project)
- [Key Features](#key-features)
- [Architecture](#architecture)
- [Tech Stack](#tech-stack)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Project Structure](#project-structure)
- [Security](#security)
- [Contributing](#contributing)

---

## About the Project

**Blockchain File Transfer System** is a high-performance blockchain system designed for secure file transfer and verification within a decentralized network. The project is built using modern C++23 standards and adheres to production-ready development principles.

### Core Principles

- **Fairness:** FIFO transaction queue with no hidden priorities.
- **Security:** Full memory safety (RAII) and cryptographic validation.
- **Reliability:** Thread safety, with zero data races or memory leaks.
- **Performance:** Highly optimized architecture designed for heavy workloads.
- **Transparency:** Deterministic transaction processing order.

---

## Key Features

### Cryptography
- **Ed25519** signatures for transactions.
- **SHA-256** file hashing.
- **BLAKE2b** hashing for addresses and blocks.
- Comprehensive data integrity verification.

### Mempool
- **Fair FIFO Queue:** First in, first out processing.
- **Thread Safety:** Robust execution in multi-threaded environments.
- **Deterministic Order:** Predictable transaction handling.
- **Duplicate Protection:** Automatic uniqueness validation.

### Mining / Validation
- **Feeless:** Transactions are processed completely free of charge.
- **Protocol Rewards:** Miners are incentivized through a built-in protocol mechanism.
- **Fast Confirmation:** Highly efficient transaction processing.

### Networking
- **P2P Architecture:** Decentralized node network.
- **Asynchronous Processing:** Powered by ASIO for high-performance I/O.
- **Auto-Discovery:** Dynamic network connection and peer routing.

### File Transfer
- **Integrity Checks:** Automatic hash validation.
- **Metadata:** Comprehensive information attached to transferred files.
- **Secure Transfer:** Cryptographically protected data exchange.

---

## Architecture

<div align="center"> <img src="https://github.com/user-attachments/assets/9b64c70b-871d-494e-9310-a4ecf0a3cfaf" alt="Blockchain Network" width="700"/> </div>

### System Components

- **`user`:** Key and address management.
- **`transaction`:** Transaction creation and validation.
- **`mempool`:** Fair FIFO transaction queue.
- **`miner`:** Block mining and validation.
- **`block`:** Block structure carrying files.
- **`blockchain`:** Block sequence with built-in validation.
- **`node`:** P2P network node.
- **`file_sender`:** File transmission via the blockchain.

---

## Tech Stack

### Languages and Standards
- **C++23:** Modern C++ standard.
- **CMake 3.25+:** Build system.

### Libraries
- **libsodium:** Cryptographic operations.
- **ASIO:** Asynchronous network I/O.
- **Catch2:** Unit testing framework.

### Development Principles
- **RAII:** Strict resource management.
- **constexpr:** Compile-time evaluations.
- **noexcept:** Exception safety guarantees.
- **std::optional:** Safe handling of optional values.
- **enum class:** Type-safe enumerations.

---

## Installation

### Prerequisites

- **Compiler** with C++23 support (GCC 13+, Clang 16+).
- **CMake** 3.25 or higher.
- **libsodium:** Cryptographic library.
- **pkg-config:** For dependency resolution.

## Architecture Modules
- `core/` - Blockchain, cryptography, mempool.
- `network/` - TCP node and file transfer protocol.
- `storage/` - SQLite storage for users, blocks, and transactions.
- `gui/` - Qt Quick UI, models, and controllers.

## Build Instructions (Linux/macOS)
```bash
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . -j
