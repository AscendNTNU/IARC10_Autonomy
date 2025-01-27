#pragma once

#include "bt_drone/poseNED.hpp"

std::vector<NED> generate_path(NED starting_position, NED end_vector, NED path_vector, int resolution);
