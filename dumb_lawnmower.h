#pragma once

#include<iostream>
#include<vector>

struct NED {
    double north, east, down;

    NED operator*(const double &a) 
    {
        return NED{north * a, east * a, down * a};
    }

    NED operator/(const double &a) 
    {
        return NED{north / a, east / a, down / a};
    }

    void operator+=(const NED &other)
    {
        north += other.north;
        east += other.east;
        down += other.down;
    }

    friend std::ostream& operator <<(std::ostream &o, NED &i)
    {
        return o << i.north << " " << i.east << " " << i.down; 
    }
};

std::vector<NED> generate_path(NED starting_position, NED end_vector, NED path_vector, int resolution);
