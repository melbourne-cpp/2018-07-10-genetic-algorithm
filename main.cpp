#include "Population.hpp"
#include <iostream>

class Simulator {
private:
    unsigned m_num_generations;
    unsigned m_num_args;
    unsigned m_num_genes;
    unsigned m_pop_size;
    unsigned m_mutation_rate;
    std::vector<std::vector<double>> m_args_list;
    std::vector<double> m_expected_vals;

public:
    Simulator(unsigned num_generations, unsigned num_args, unsigned num_genes, unsigned pop_size, unsigned mutation_rate) :
            m_num_generations(num_generations),
            m_num_args(num_args),
            m_num_genes(num_genes),
            m_pop_size(pop_size),
            m_mutation_rate(mutation_rate)
    {
        m_args_list.push_back({7.0, 2.0});
        m_args_list.push_back({3.0, 4.0});

        for (const auto& args : m_args_list) {
            m_expected_vals.push_back(mistery_func(args[0], args[1]));
        }

        Individual::init(num_args, num_genes);
        Gene::init(num_args, num_genes);
    }

    void printGenNum(int i)
    {
        std::string prev = std::to_string(i);
        for (unsigned i {0}; i<prev.length(); ++i) {
            std::cout << "\b";
        }
        std::cout << (i+1);
        fflush(stdout);
    }

    void run()
    {
        // initialise
        std::cout << "Processing generation :  ";
        Population pop(m_pop_size, m_mutation_rate);

        unsigned i;
        for (i = 0; ; ++i) {
            printGenNum(i);

            for (unsigned j {0}; j < m_expected_vals.size(); ++j) {
                pop.fitness(m_args_list[j], m_expected_vals[j]);
            }
            //   |
            //   V
            if (pop.checkEndCondition() || i>=m_num_generations-1) {
                break; // Stop
            }
            //   | No stop
            //   V
            pop.select();
            //   |
            //   V
            pop.crossover();
            //   |
            //   V
            pop.mutate();
            //   |
            //   V
        }

        std::cout << std::endl << std::endl;
        std::cout << "Stopped after " << (i+1) << " generations." << std::endl;
        std::cout << "Fitness best individual: " << pop.getTopScore() << std::endl;
        pop.printTopIndividual();
    }

private:
    double mistery_func(double x0, double x1)
    {
        return ((1.5*x0) + x1)/x0;
    }
};

int main() {
    unsigned num_generations {20};
    unsigned num_args  {2};
    unsigned num_genes {8};
    unsigned pop_size  {15000};
    unsigned mutation_rate {5}; // 5%

    Simulator s(num_generations, num_args, num_genes, pop_size, mutation_rate);
    s.run();

    return 0;
}
