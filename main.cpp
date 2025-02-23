#include <iostream>
#include <vector>

#include "Vehicle.h"
#include "bls.hpp"

using namespace bls;
using namespace std;

int main() {
    vector<uint8_t> seed = {0,  50, 6,  244, 24,  199, 1,  25,  52,  88,  192,
                            19, 18, 12, 89,  6,   220, 18, 102, 58,  209, 82,
                            12, 62, 89, 110, 182, 9,   44, 20,  254, 22};

    vector<uint8_t> message = {1, 2, 3, 4, 5};

    PrivateKey sk = AugSchemeMPL().KeyGen(seed);
    G1Element pk = sk.GetG1Element();

    G2Element sig = AugSchemeMPL().Sign(sk, message);

    bool ok = AugSchemeMPL().Verify(pk, message, sig);
    cout << "Signature verification: " << (ok ? "Passed" : "Failed") << endl;
    return 0;
}

/*
build:
cd build
cmake --build . --config Release

run:
cd build
cd Release
.\V2x.exe
*/