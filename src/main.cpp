#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "tools.h"
#include "crypto.h"

namespace bncrypto = bluenebula::crypto;

template<typename T>
std::vector<T> make_seed(const size_t len) {
    static_assert(std::is_integral<T>::value, "integral type required");

    std::vector<T> seed(len);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<T> dist(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());

    for (T& i : seed) {
        i = dist(mt);
    }

    return seed;
}

void reqauth(char* arg) {
    auto* parsed_pubkey = bncrypto::parsepubkey(arg);

    std::vector<char> challengestr;
    const auto seed = make_seed<int>(3);

    bncrypto::genchallenge(
        parsed_pubkey,
        reinterpret_cast<void const*>(seed.data()),
        static_cast<int>(seed.size()),
        challengestr
    );

    std::cout << challengestr.data() << std::endl;
}

void confauth(char* arg) {
    (void) arg;
    std::cerr << "TODO" << std::endl;
};

void genkey() {
    // we need a C-string-like array
    // therefore, we have to zero-terminate it
    auto seed = make_seed<char>(128);
    seed.emplace_back('\0');

    std::vector<char> privkey, pubkey;

    bncrypto::genprivkey(seed.data(), privkey, pubkey);

    std::cout << "privkey: " << privkey.data() << std::endl;
    std::cout << "pubkey : " << pubkey.data()  << std::endl;
};

void pubkey(char* privkey) {
    std::vector<char> pubkey;

    bncrypto::genpubkey(privkey, pubkey);

    std::cout << "pubkey : " << pubkey.data()  << std::endl;
};

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
