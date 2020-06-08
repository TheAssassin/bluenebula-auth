#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "tools.h"
#include "crypto.h"

namespace bncrypto = bluenebula::crypto;

void reqauth(char* pubkey) {
    std::cout << bncrypto::generate_auth_challenge(pubkey) << std::endl;
}

void confauth(char* arg) {
    (void) arg;
    std::cerr << "TODO" << std::endl;
}

void genkey() {
    const auto key_pair = bncrypto::generate_key_pair();

    std::cout << "privkey: " << key_pair.first.data() << std::endl;
    std::cout << "pubkey : " << key_pair.second.data() << std::endl;
}

void pubkey(char* privkey) {
    std::cout << "pubkey: " << bncrypto::generate_pubkey(privkey)  << std::endl;
}

void show_usage(char** argv) {
    std::cout << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
}

void show_help(char** argv) {
    show_usage(argv);
    std::cout << "  help                - show this help text and exit" << std::endl
              << "  reqauth <pubkey>    - generate challenge for given pubkey" << std::endl
              << "  confauth <response> - validate client reply" << std::endl
              << "  genkey              - generate key pair" << std::endl
              << "  pubkey <privkey>    - generate (derive) public from private key" << std::endl;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        show_usage(argv);
        return 2;
    }

    std::string command{argv[1]};

    if (command == "help") {
        show_help(argv);
        return 0;
    } else if (argc >= 3 && command == "reqauth") {
        reqauth(argv[2]);
        return 0;
    } else if (argc >= 3 && command == "confauth") {
        confauth(argv[2]);
        return 0;
    } else if (argc >= 3 && command == "pubkey") {
        pubkey(argv[2]);
        return 0;
    } else if (command == "genkey") {
        genkey();
        return 0;
    }

    show_usage(argv);
    return 2;
}
