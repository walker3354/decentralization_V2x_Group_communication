#include <iostream>
#include <unordered_map>
#include <vector>

#include "bls.hpp"
using namespace std;
using namespace bls;

vector<uint8_t> pre_set_seed = {
    0,   50, 6,   244, 24,  199, 1,  25, 52, 88,  192, 19, 18, 12, 89,  6,
    220, 18, 102, 58,  209, 82,  12, 62, 89, 110, 182, 9,  44, 20, 254, 22};

class Vehicle {
    private:
        int vehicle_id;
        G1Element vehicle_pk;
        unordered_map<int, G1Element> id_pk_set;
        vector<uint8_t> vehicle_sk_bytes;
        vector<uint8_t> vehicle_pk_bytes;

        vector<G2Element> pop_received_signs;
        G2Element pop_aggregate_sign;

    public:
        Vehicle(int vehicle_id, uint8_t seed) {
            this->vehicle_id = vehicle_id;
            pre_set_seed[0] = seed;
            PrivateKey vehicle_sk = AugSchemeMPL().KeyGen(pre_set_seed);
            this->vehicle_pk = vehicle_sk.GetG1Element();
            this->vehicle_sk_bytes = vehicle_sk.Serialize();
            this->vehicle_pk_bytes = this->vehicle_pk.Serialize();
            this->print_vehicle_info();
        }

        void print_vehicle_info() {
            cout << "\tVehicle id: " << this->vehicle_id << endl;
            cout << "\tVehicle pk(Bytes): "
                 << Util::HexStr(this->vehicle_pk_bytes) << endl;
            cout << "\tVehicle sk(Bytes): "
                 << Util::HexStr(this->vehicle_sk_bytes) << endl;
        }

        G1Element get_vehicle_pk() { return this->vehicle_pk; }

        int get_vehicle_id() { return this->vehicle_id; }

        void receive_vehicle_info(int vehicle_id, G1Element vehicel_pk) {
            this->id_pk_set[vehicle_id] = vehicel_pk;
        }
        // pop scheme(aggregrate)
        G2Element pop_sign_message(vector<uint8_t> message) {
            return PopSchemeMPL().Sign(
                PrivateKey::FromByteVector(this->vehicle_sk_bytes), message);
        }

        void pop_receive_aggregate_sign(G2Element aggregate_sign) {
            this->pop_aggregate_sign = aggregate_sign;
        }

        void pop_receive_sign(G2Element sign) {
            this->pop_received_signs.push_back(sign);
        }

        G2Element pop_aggregating_signs() {
            this->pop_aggregate_sign =
                PopSchemeMPL().Aggregate(this->pop_received_signs);
            return this->pop_aggregate_sign;
        }

        bool pop_verify_aggregate_sign(vector<uint8_t> message) {
            vector<G1Element> pks;
            for (const auto &i : this->id_pk_set) {
                pks.push_back(i.second);
            }
            return PopSchemeMPL().FastAggregateVerify(pks, message,
                                                      this->pop_aggregate_sign);
        }
};