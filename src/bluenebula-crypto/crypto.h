#include "tools.h"

namespace bluenebula {
    namespace crypto {
        void* parsepubkey(const char* pubstr);

        void* genchallenge(void* pubkey, const void* seed, int seedlen, std::vector<char>& challengestr);

        void genprivkey(const char* seed, std::vector<char>& privstr, std::vector<char>& pubstr);

        void genpubkey(const char* privstr, std::vector<char>& pubstr);

        bool checkchallenge(const char* answerstr, void* correct);
    }
}
