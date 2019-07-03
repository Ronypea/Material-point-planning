
#include <iostream>
#include "Tournament.hpp"

double fRand(double fMin, double fMax)
{
    double f = (double) std::rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

size_t iRand(size_t min, size_t max)
{
    return rand() % max + min;
}

constexpr double PI = M_PI;
auto compare = [](const std::pair<double, Chromosome> &first, const std::pair<double, Chromosome> &second)
{
    return first.first > second.first;
};

double dist(std::pair<double, double> first, std::pair<double, double> second)
{
    return sqrt((first.first - second.first) * (first.first - second.first) +
                (first.second - second.second) * (first.second - second.second));
}

bool isCircleCrossed(std::pair<double, double> point, std::pair<std::pair<double, double>, double> circle){
    return dist(point, circle.first) <= circle.second;
}

bool isOutOfBox(std::pair<double, double> point){
    return point.first > 1.0 || point.first < 0.0|| point.second > 1.0 || point.second < 0.0;
}

bool isLineCrossCircle(std::pair<double, double> begin, std::pair<double,double> end, std::pair<std::pair<double, double>, double> circle){
    std::pair<double, double> x0 = circle.first;
    double a = begin.second - end.second;
    double b = end.first - begin.first;
    double c = (begin.first- end.first)*begin.second + begin.first*(end.second - begin.second);
    double distance = fabs(a*x0.first + b*x0.second + c)/ sqrt(a*a + b*b);
    return distance <= circle.second;
}
Tournament::Tournament(const std::vector<Chromosome> &chromosomes, const Map &map, double time) : map_(map),
                                                                                                  time_(time),
                                                                                                  populationSize_(
                                                                                                          chromosomes.size())
{
    for (auto &i: chromosomes)
    {
        stepResults_.emplace_back(std::make_pair(0.0, i));
    }
}

void Tournament::start(size_t iterationAmount)
{
    for (size_t i = 0; i < iterationAmount; i++)
    {
        step();
    }
    printResults();
}

void Tournament::step()
{
    for(size_t i = 0; i < stepResults_.size(); i++){
        double res = fitness(stepResults_[i].second);

        stepResults_[i].first = fitness(stepResults_[i].second);
    }
    std::sort(stepResults_.begin(), stepResults_.end(), compare);
    stepResults_.erase(stepResults_.begin() + stepResults_.size() / 2, stepResults_.end());
    size_t amountOfBreeding = stepResults_.size() / 2;
    double chanceOfAdding = fRand(0.0, 1.0);
    for (size_t i = 0; i < amountOfBreeding; i++)
    {
        chanceOfAdding = fRand(0.0, 1.0);
        Chromosome toAdd = stepResults_[i].second + stepResults_[amountOfBreeding + i].second;
        if (chanceOfAdding < 0.1)
        {
            toAdd.eraseRandomAllele();

        } else if (chanceOfAdding >= 0.9)
        {
            toAdd.addRandomAllele();
        }
        stepResults_.emplace_back(
                std::make_pair(0, toAdd));
    }
    size_t amountToAdd = populationSize_ - stepResults_.size();
    for (size_t i = 0; i < amountToAdd; i++)
    {
        Chromosome toAdd = stepResults_[0].second;
        chanceOfAdding = fRand(0.0, 1.0);
        toAdd.randomMutation();
        if (chanceOfAdding < 0.1)
        {
            toAdd.eraseRandomAllele();

        } else if (chanceOfAdding >= 0.9)
        {
            toAdd.addRandomAllele();
        }
        stepResults_.emplace_back(std::make_pair(0, toAdd));
    }
}

double Tournament::fitness(Chromosome &chromosome)
{
    double toTerminal, totalPath;
    std::pair<double, double> speed;
    bool isCrossed = distanceToDestinationOnTerminalPoint(chromosome, toTerminal, totalPath, speed);
    double res = 1 / (totalPathWeight * totalPath + toTerminalWeight * toTerminal);
    return isCrossed? -1 : res;
}

bool
Tournament::distanceToDestinationOnTerminalPoint(const Chromosome &chromosome, double &toTerminal, double &totalPath, std::pair<double, double>& speed)
{
    toTerminal = 0;
    totalPath = 0;
    std::pair<double, double> position(0.0, 0.0), prev(0.0, 0.0);
    speed = std::make_pair(0.0,0.0);
    bool isCrossed;
    for (auto &allele: chromosome.getAlleles())
    {
        isCrossed = false;
        position.first += speed.first * time_;
        position.second += speed.second * time_;
        speed.first += allele.firffst * time_ * std::cos(allele.second * PI / 180.0);
        speed.second += allele.first * time_ * std::sin(allele.second * PI / 180.0);
        totalPath += dist(prev, position);
        for(auto& i: map_.getCircles()){
            isCrossed = isCircleCrossed(position, i);
            if(isCrossed){
                totalPath = 10000000000;
                break;
            }
            isCrossed = isLineCrossCircle(prev, position, i);
            if(isCrossed){
                totalPath = 10000000000;
                break;
            }
        }
        if(isCrossed){
            break;
        }
        if(isOutOfBox(position)){
            totalPath = 10000000000;
            break;
        }
        prev = position;
    }
    toTerminal = dist(position, std::make_pair(1.0, 1.0));
    return isCrossed;
}


void Tournament::printResults()
{
    for(size_t i = 0; i <stepResults_.size(); i++){
        std::cout << "Chromosome #: " << i << std::endl <<  "PathLength: " << stepResults_[i].second.getAlleles().size() << std::endl;
        std::pair<double, double> position(0.0, 0.0), prev(0.0, 0.0);
        std::pair<double, double> speed(0.0, 0.0);
        double totalPath = 0;
        for (auto &allele: stepResults_[i].second.getAlleles())
        {
            position.first += speed.first * time_;
            position.second += speed.second * time_;
            speed.first += allele.first * time_ * std::cos(allele.second * PI / 180.0);
            speed.second += allele.first * time_ * std::sin(allele.second * PI / 180.0);
            totalPath += dist(prev, position);
            //std::cout << "Force: " << allele.first << " Angle: " << allele.second << std::endl;
            //std::cout << "Speed: " << speed.first << " " << speed.second << std::endl;
            std::cout << position.first << " " << position.second << std::endl;
        }
        break;
        std::cout << std::endl;
    }
}
