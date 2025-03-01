#include <iostream>
#include <vector>

#include "Vehicle.h"
#include "bls.hpp"

using namespace bls;
using namespace std;

int main() {
    vector<uint8_t> message = {1, 2, 3, 4, 5};
    vector<uint8_t> message2 = {1, 2, 3, 4, 4};

    Vehicle v1(1, 1);
    Vehicle v2(2, 2);
    Vehicle v3(3, 3);
    Vehicle group_leader(4, 4);

    group_leader.pop_receive_sign(v1.pop_sign_message(message));
    group_leader.pop_receive_sign(v2.pop_sign_message(message));
    group_leader.pop_receive_sign(v3.pop_sign_message(message));

    v1.pop_receive_aggregate_sign(group_leader.pop_aggregating_signs());
    v1.receive_vehicle_info(v1.get_vehicle_id(), v1.get_vehicle_pk());
    v1.receive_vehicle_info(v2.get_vehicle_id(), v2.get_vehicle_pk());
    v1.receive_vehicle_info(v3.get_vehicle_id(), v3.get_vehicle_pk());

    cout << "\tSignature verify result: "
         << (v1.pop_verify_aggregate_sign(message) ? "Pass" : "False") << endl;
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