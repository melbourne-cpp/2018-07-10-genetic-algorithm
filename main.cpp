#include "Population.hpp"
#include <iostream>

int main() {
    int num_generations {3};
    std::vector<double> expected {4.0};

    int i {0};
    Population pop; // initialise
    do {
        pop.evaluate(expected);

        if (pop.getTopScore() == 0) {
            pop.printTopIndividual();
            break;
        }

        pop.select(); // dummy call for now
        pop.crossover();
        pop.mutate();
        std::cout << "----------" << std::endl;
    } while (i++ < num_generations);

    return 0;
}