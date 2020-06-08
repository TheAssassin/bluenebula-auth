#include <pybind11/pybind11.h>

#include "crypto.h"

namespace py = pybind11;
namespace bncrypto = bluenebula::crypto;


PYBIND11_MODULE(MODULE_NAME, m) {
    m.doc() = "Blue Nebula crypto";

    m.def("generate_key_pair", &bncrypto::generate_key_pair, "Generate privkey/pubkey pair");
    m.def("generate_auth_challenge", &bncrypto::generate_auth_challenge, "Create auth challenge for given pubkey");
    m.def("generate_pubkey", &bncrypto::generate_pubkey, "Generate pubkey for given privkey");
    m.def("check_auth_reply", &bncrypto::check_auth_reply, "Check whether reply matches challenge");
}
