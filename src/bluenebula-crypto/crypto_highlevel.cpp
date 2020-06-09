#include <memory>

#include "crypto.h"

namespace bluenebula {
    namespace crypto {

        /**
         * Generate auth challenge for given pubkey
         * @param pubkey user's public key
         * @return pair of challenge and expected answer
         */
        std::pair<std::string, std::string> generate_auth_challenge(const std::string& pubkey) {
            std::shared_ptr<void> parsed_pubkey(lowlevel::parsepubkey(pubkey.c_str()), &lowlevel::freepubkey);

            std::vector<char> challengestr, answerstr;
            const auto seed = lowlevel::make_seed<int>(3);

            lowlevel::genchallenge(
                parsed_pubkey.get(),
                reinterpret_cast<void const*>(seed.data()),
                static_cast<int>(seed.size()),
                challengestr,
                answerstr
            );

            return std::make_pair(challengestr.data(), answerstr.data());
        }

        std::pair<std::string, std::string> generate_key_pair() {
            // we need a C-string-like array
            // therefore, we have to zero-terminate it
            auto seed = lowlevel::make_seed<char>(128);
            seed.emplace_back('\0');

            std::vector<char> privkey, pubkey;

            lowlevel::genprivkey(seed.data(), privkey, pubkey);

            return std::make_pair(privkey.data(), pubkey.data());
        }

        std::string generate_pubkey(const std::string& privkey) {
            std::vector<char> pubkey;
            lowlevel::genpubkey(privkey.c_str(), pubkey);
            return pubkey.data();
        }

    }
}
