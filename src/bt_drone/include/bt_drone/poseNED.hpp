#pragma once

#include <iostream>
#include <vector>
#include <cassert>

struct NED 
{
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

    void operator-=(const NED &other)
    {
        north -= other.north;
        east -= other.east;
        down -= other.down;
    }

    // Makes a copy
    NED operator-(NED other) const {
        other -= *this;
        return other * -1;
    }

    NED operator+(NED other) const {
        other += *this;
        return other ;
    }

    bool operator==(const NED& other) const {
        return north == other.north && east == other.east && down == other.down;
    }

    friend std::ostream& operator <<(std::ostream &o, NED &i)
    {
        return o << i.north << " " << i.east << " " << i.down; 
    }
};
