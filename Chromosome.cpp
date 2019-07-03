
#include "Chromosome.hpp"

namespace func
{
    double fRand(double fMin, double fMax)
    {
        double f = (double) std::rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }

    size_t iRand(size_t min, size_t max)
    {
        return rand() % max + min;
    }
}
Chromosome operator+(const Chromosome &first, const Chromosome &second)
{
    Chromosome res(first.getMaxForce(), first.getMutationLevel());
    res.alleles_.clear();
    if(first.getAlleles().size() == 0){
        return second;
    }
    if(second.getAlleles().size() == 0){
        return first;
    }
    size_t minimalSize = std::min(first.alleles_.size(), second.alleles_.size());
    size_t breakingPoint = func::iRand(0, minimalSize);
    for (size_t i = 0; i < breakingPoint; i++)
    {
        res.alleles_.emplace_back(first.alleles_[i]);
    }
    for (size_t i = breakingPoint; i < second.alleles_.size(); i++)
    {
        res.alleles_.emplace_back(second.alleles_[i]);
    }
    return res;
}

Chromosome::Chromosome(force maxForce, double mutationLevel): maxForce_(maxForce), mutationLevel_(mutationLevel){
    alleles_.push_back(std::make_pair(func::fRand(0.0, maxForce), func::fRand(0.0, 90.0)));
}

Chromosome::Chromosome(std::size_t size_, force maxForce)
{

}

void Chromosome::addRandomAllele()
{
    if(alleles_.size()){
        alleles_.emplace_back(std::make_pair(func::fRand(0.0, maxForce_), func::fRand(0.0, 360.0)));
    }
    size_t place = func::iRand(0, alleles_.size());
    alleles_.insert(alleles_.begin() + place, std::make_pair(func::fRand(0.0, maxForce_), func::fRand(0.0, 360.0)));
}

void Chromosome::eraseRandomAllele()
{
    if(alleles_.size()){
        return;
    }
    size_t place =func::iRand(0, alleles_.size());
    alleles_.erase(alleles_.begin()+place);
}

void Chromosome::randomMutation()
{
    if(alleles_.size() == 0){
        return;
    }
    size_t place = func::iRand(0, alleles_.size());
    alleles_[place].first += func::fRand(0.0, maxForce_)*mutationLevel_;
    if(alleles_[place].first > maxForce_){
        alleles_[place].first -= maxForce_;
    }
    alleles_[place].second += func::fRand(0.0, 360.0)*mutationLevel_;
    if(alleles_[place].second > 360.0){
        alleles_[place].second -= 360.0;
    }
}

double Chromosome::getMutationLevel() const
{
    return mutationLevel_;
}

double Chromosome::getMaxForce() const
{
    return maxForce_;
}

const std::vector<std::pair<force, angle>> &Chromosome::getAlleles() const
{
    return alleles_;
}
