#include "../bt_drone/include/bt_drone/poseNED.hpp"
#include <vector>
#include <cmath>

/*

CONSTANTS SHOULD NOT BE STORED HERE. USE BLACKBOARD INSTEAD.

*/
constexpr int 
RESOLUTION = 6;

constexpr int 
RES_X = 40 * RESOLUTION, 
RES_Y = 40 * RESOLUTION;
constexpr double 
EXLPORATION_RADIUS = 5; // The "viewdistance" 



/*
Generates the map showing which areas are discovered. Assumes the inputs are in map-pixel coordinates. 
*/
std::vector<std::vector<bool>> make_discovered_map(std::vector<NED> positions);