#pragma once

#include<vector>
#include<cmath>
#include<iostream>
#include<iomanip>


template<typename T>
struct Mine {
    T x,        // mean_x 
    y,          // mean_y
    std;        // standard deviation

    Mine(T xpos, T ypos, T standard_deviation) {
        x = xpos, y = ypos, std = standard_deviation;
    }
} ;


double normalCDF2D(double x, double y, double std);
long double normalCDF2D(long double x, long double y, long double std);

/*
Input: points corresponding to the observed mine locations. Should be in the coordinate system of the minefield
Output: heatmap of the mines
*/
std::vector<std::vector<double>> generateMineMap(std::vector<Mine<double>> recorded_mines);


std::vector<std::vector<int>> dilateMineMap(std::vector<std::vector<double>> mine_map, double threshold, double radius);

void merge_explored_map_into_mine_map(std::vector<std::vector<bool>> &mine_map, const std::vector<std::vector<bool>> &explored_map);

void realworld_to_map(std::vector<Mine<double>> &mines);