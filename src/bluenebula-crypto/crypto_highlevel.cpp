#include "crypto.h"

namespace bluenebula {
    namespace crypto {

        std::string make_auth_request(const std::string& pubkey) {
            auto* parsed_pubkey = lowlevel::parsepubkey(pubkey.c_str());

            std::vector<char> challengestr;
            const auto seed = lowlevel::make_seed<int>(3);

            lowlevel::genchallenge(
                parsed_pubkey,
                reinterpret_cast<void const*>(seed.data()),
                static_cast<int>(seed.size()),
                challengestr
            );

            return challengestr.data();
        }

        std::pair<std::string, std::string> generate_key_pair() {
            // we need a C-string-like array
            // therefore, we have to zero-terminate it
            auto seed = lowlevel::make_seed<char>(128);
            seed.emplace_back('\0');

            std::vector<char> privkey, pubkey;

            lowlevel::genprivkey(seed.data(), privkey, pubkey);

            std::pair<std::string, std::string> rv{privkey.data(), pubkey.data()};
            return rv;
        }

        std::string generate_pubkey(const std::string& privkey) {
            std::vector<char> pubkey;
            lowlevel::genpubkey(privkey.c_str(), pubkey);
            return pubkey.data();
        }

    }
}
