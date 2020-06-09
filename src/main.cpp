#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "tools.h"
#include "crypto.h"

namespace bncrypto = bluenebula::crypto;

void reqauth(const char* pubkey) {
    auto rv = bncrypto::generate_auth_challenge(pubkey);
    std::cout << "challenge:       " << rv.first << std::endl
              << "expected answer: " << rv.second << std::endl;
}

void genkey() {
    const auto key_pair = bncrypto::generate_key_pair();

    std::cout << "privkey: " << key_pair.first.data() << std::endl;
    std::cout << "pubkey : " << key_pair.second.data() << std::endl;
}

void pubkey(const char* privkey) {
    std::cout << "pubkey: " << bncrypto::generate_pubkey(privkey)  << std::endl;
}

void show_usage(char* const* argv) {
    std::cout << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
}

void show_help(char* const* argv) {
    show_usage(argv);
    std::cout << "  help             - show this help text and exit" << std::endl
              << "  reqauth <pubkey> - generate challenge for given pubkey" << std::endl
              << "  genkey           - generate key pair" << std::endl
              << "  pubkey <privkey> - generate (derive) public from private key" << std::endl;
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
