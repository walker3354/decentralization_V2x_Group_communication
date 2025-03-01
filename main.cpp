#include <iostream>
#include <vector>

#include "Vehicle.h"
#include "bls.hpp"

using namespace bls;
using namespace std;

int main() {
    vector<uint8_t> message = {1, 2, 3, 4, 5};
    vector<uint8_t> message2 = {1, 2, 3, 4, 4};
    vector<G2Element> sign_set;
    G2Element aggregatee_sign;
    Vehicle v1(1, 1);
    Vehicle v2(2, 2);
    Vehicle v3(3, 3);
    Vehicle group_leader(4, 4);
    sign_set.push_back(v1.pop_sign_message(message));
    sign_set.push_back(v2.pop_sign_message(message));
    sign_set.push_back(v3.pop_sign_message(message));
    for (int i = 0; i < sign_set.size(); i++) {
        group_leader.pop_receive_sign(sign_set[i]);
    }
    aggregatee_sign = group_leader.pop_aggregating_signs();
    v1.pop_receive_aggregate_sign(aggregatee_sign);
    v1.receive_vehicle_info(v1.get_vehicle_id(), v1.get_vehicle_pk());
    v1.receive_vehicle_info(v2.get_vehicle_id(), v2.get_vehicle_pk());
    v1.receive_vehicle_info(v3.get_vehicle_id(), v3.get_vehicle_pk());
    cout << "\tverify result: " << v1.pop_verify_aggregate_sign(message)
         << endl;
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