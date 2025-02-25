#pragma once

#include<vector>
#include<cmath>
#include<iostream>
#include<iomanip>
#include <random>

constexpr int 
SCALING_FACTOR = 10,                            // Number of points per meter
RES_X = 50 * SCALING_FACTOR,                    // Numebr of points in X direction
RES_Y = 90 * SCALING_FACTOR,                    // Number of points in Y direction

MINES = 600;                                    // For generation of mines


constexpr double 
AREA_X = 50, 
AREA_Y = 90,                    // Area of real world field

THRESHOLD = 0.05,                // Threshold for program to classify point as mine
RADIUS = 1.0,                     // In meters
GAUSSIAN_BLUR_LIMIT = 3.5;        // In standard deviation


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

std::vector<Mine<double>> generate_random_mines(int num);