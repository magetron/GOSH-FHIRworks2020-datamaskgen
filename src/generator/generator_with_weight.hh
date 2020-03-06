//
// Created by Patrick Wu on 05/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_WITH_WEIGHT_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_WITH_WEIGHT_HH

#include <vector>
#include <unordered_map>
#include <random>

using namespace std;

template<class T>
class generator_with_weight {
public:
    bool activate = true;
    vector<pair<const T&, int>> weights;
    vector<int> ps;
    uniform_int_distribution<int> dist;

    generator_with_weight () = default;

    explicit generator_with_weight (unordered_map<T, int>& i_map) {
        if (i_map.size() == 0) {
            activate = false;
            return;
        }
        for (const auto& p : i_map) weights.push_back({p.first, p.second});
        ps = vector<int>(weights.size());
        int s = 0;
        for (size_t i = 0; i < weights.size(); i++) {
            s += weights[i].second;
            ps[i] = s;
        }
        dist = uniform_int_distribution<int>(0, ps.back() - 1);
    }

    T generate () {
        if (!activate) return T();
        static random_device dev;
        static mt19937 rng(dev());

        int r = dist(rng);
        auto it = upper_bound(ps.begin(), ps.end(), r);
        return weights[it - ps.begin()].first;
    }

};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_WITH_WEIGHT_HH
