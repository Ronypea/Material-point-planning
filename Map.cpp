
#include "Map.hpp"

Map::Map(size_t amountOfSpecies, const std::vector<circle> &circles):species_(amountOfSpecies, std::make_pair(std::make_pair(0.0,0.0),std::make_pair(0.0,0.0))), circles_(circles)
{

}
