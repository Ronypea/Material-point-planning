
#ifndef INDIVIDUALPROJECT_MAP_HPP
#define INDIVIDUALPROJECT_MAP_HPP

#include <utility>
#include <vector>
using speed = std::pair<double, double> ;
using position = std::pair<double, double> ;
using specie = std::pair<position, speed> ;
using circle = std::pair<position, double> ;
class Map
{
public:
    Map(size_t amountOfSpecies, const std::vector<circle>& circles);
    std::vector<circle> getCircles(){
        return circles_;
    }
private:
    std::vector <specie> species_;
    std::vector <circle> circles_;
};


#endif //INDIVIDUALPROJECT_MAP_HPP
