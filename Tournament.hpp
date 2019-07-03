
#ifndef INDIVIDUALPROJECT_TOURNAMENT_HPP
#define INDIVIDUALPROJECT_TOURNAMENT_HPP


#include "Map.hpp"
#include "Chromosome.hpp"
#include <cmath>
#include <algorithm>
constexpr double totalPathWeight = 10;
constexpr double toTerminalWeight = 90;
class Tournament
{
public:
    Tournament(const std::vector<Chromosome>& chromosomes, const Map &map, double time);
    void start(size_t iteration);
    void step();
    void printResults();
private:
    double fitness(Chromosome& chromosome);
    bool distanceToDestinationOnTerminalPoint(const Chromosome& chromosome, double& toTerminal, double& totalPath,std::pair<double, double>& speed);
    Map map_;
    size_t populationSize_;
    std::vector<std::pair<double, Chromosome>> stepResults_;
    double time_;
};


#endif //INDIVIDUALPROJECT_TOURNAMENT_HPP