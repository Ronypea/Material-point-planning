
#ifndef INDIVIDUALPROJECT_CHROMOSOME_HPP
#define INDIVIDUALPROJECT_CHROMOSOME_HPP

#include <cstddef>
#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>

using angle = double;
using force = double;

struct allele
{
    double type;
    double angle;
    double force;
};



class Chromosome
{
public:
    Chromosome(force maxForce, double mutationLevel);

    Chromosome(std::size_t size_, force maxForce);

    void addRandomAllele();

    void eraseRandomAllele();

    void randomMutation();

    double getMutationLevel() const;

    double getMaxForce() const;
    const std::vector<std::pair<force, angle>>& getAlleles() const;
private:

    friend Chromosome operator+(const Chromosome &first, const Chromosome &second);

    std::vector<std::pair<force, angle>> alleles_;
    force maxForce_;
    double mutationLevel_;
};

#endif //INDIVIDUALPROJECT_CHROMOSOME_HPP
