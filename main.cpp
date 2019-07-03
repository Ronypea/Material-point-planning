#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include "Chromosome.hpp"
#include "Map.hpp"
#include "Tournament.hpp"

int main()
{
    std::srand(time(0));
    std::fstream input("data.txt");
    std::pair<double, double> startPosition;
    input >> startPosition.first;
    input >> startPosition.second;
    double maxForce;
    input >> maxForce;
    size_t amountOfObstacle;
    input >> amountOfObstacle;
    std::vector<std::pair<std::pair<double, double>, double>> obstacles;
    for (int i = 0; i < amountOfObstacle; i++)
    {
        std::pair<std::pair<double, double>, double> obstacle;
        input >> obstacle.first.first >> obstacle.first.second >> obstacle.second;
        obstacles.emplace_back(obstacle);
    }
    size_t populationSize = 30;
    std::vector<Chromosome> chromosomes_;
    for(int i = 0; i < populationSize; i++){
        chromosomes_.emplace_back(Chromosome(maxForce, 0.2));
    }
    Map map(populationSize, obstacles);
    double time;
    input >> time;
    Tournament tournament(chromosomes_, map, time);
    double pathLenght  = 0;
    double toTerminal = 0;
    tournament.start(15000);

    return 0;
}