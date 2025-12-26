#pragma once

#include <random>
#include <string>
#include <utility>
#include <vector>

#include "tools.h"

namespace bluenebula {
    namespace crypto {
        namespace lowlevel {
            void* parsepubkey(const char* pubstr);

            void genchallenge(void* pubkey, const void* seed, int seedlen, ::std::vector<char>& challengestr,
                              ::std::vector<char>& answerstr);

            void genprivkey(const char* seed, ::std::vector<char>& privstr, ::std::vector<char>& pubstr);

            void genpubkey(const char* privstr, ::std::vector<char>& pubstr);

            void freepubkey(void* pubkey);

            void answerchallenge(const char* privstr, const char* challenge, ::std::vector<char>& answerstr);

            template<typename T>
            ::std::vector<T> make_seed(const size_t len) {
                static_assert(::std::is_integral<T>::value, "integral type required");

                ::std::vector<T> seed(len);

                ::std::random_device rd;
                ::std::mt19937 mt(rd());
                ::std::uniform_int_distribution<T> dist(::std::numeric_limits<T>::min(), ::std::numeric_limits<T>::max());

                for (T& i : seed) {
                    i = dist(mt);
                }

                return seed;
            }
        }

        ::std::pair<::std::string, ::std::string> generate_auth_challenge(const ::std::string& pubkey);

        ::std::pair<::std::string, ::std::string> generate_key_pair();

        ::std::string generate_pubkey(const ::std::string& privkey);

        ::std::string answer_challenge(const ::std::string& privkey, const ::std::string& challenge);
    }
}
