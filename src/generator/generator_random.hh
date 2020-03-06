//
// Created by Patrick Wu on 06/03/2020.
//

#ifndef GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_RANDOM_HH
#define GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_RANDOM_HH

#include<random>
#include<iterator>


template <typename RandomGenerator = std::default_random_engine>
class random_selector {
public:
    //On most platforms, you probably want to use std::random_device("/dev/urandom")()
    explicit random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
            : gen(g) {}

    template <typename Iter>
    Iter select(Iter start, Iter end) {
        std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
        std::advance(start, dis(gen));
        return start;
    }

    //convenience function
    template <typename Iter>
    Iter operator()(Iter start, Iter end) {
        return select(start, end);
    }

    //convenience function that works on anything with a sensible begin() and end(), and returns with a ref to the value type
    template <typename Container>
    auto operator()(const Container& c) -> decltype(*begin(c))& {
        return *select(begin(c), end(c));
    }

private:
    RandomGenerator gen;
};

#endif //GOSH_FHIRWORKS2020_DATAMASKER_GENERATOR_RANDOM_HH
