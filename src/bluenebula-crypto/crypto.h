#pragma once

#include <random>
#include <string>
#include <utility>

#include "tools.h"

namespace bluenebula {
    namespace crypto {
        namespace lowlevel {
            void* parsepubkey(const char* pubstr);

            void* genchallenge(void* pubkey, const void* seed, int seedlen, std::vector<char>& challengestr);

            void genprivkey(const char* seed, std::vector<char>& privstr, std::vector<char>& pubstr);

            void genpubkey(const char* privstr, std::vector<char>& pubstr);

            bool checkchallenge(const char* answerstr, void* correct);

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
        }

        std::string generate_auth_challenge(const std::string& pubkey);

        std::pair<std::string, std::string> generate_key_pair();

        std::string generate_pubkey(const std::string& privkey);

        bool check_auth_reply(const std::string& reply, const std::string& challenge);
    }
}
