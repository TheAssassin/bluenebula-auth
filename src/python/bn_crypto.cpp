#include <pybind11/pybind11.h>

#include "crypto.h"

namespace py = pybind11;
namespace bncrypto = bluenebula::crypto;


PYBIND11_MODULE(MODULE_NAME, m) {
    m.doc() = "Blue Nebula crypto";

    m.def("generate_key_pair", &bncrypto::generate_key_pair, "Generate privkey/pubkey pair");
    m.def("make_auth_request", &bncrypto::make_auth_request, "Create auth request for given pubkey");
    m.def("generate_pubkey", &bncrypto::generate_pubkey, "Generate pubkey for given privkey");
}
