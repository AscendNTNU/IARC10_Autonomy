#include<bits/stdc++.h>

template<typename T>
struct Mine {
    T x,   // mean_x 
    y,          // mean_y
    std;        // standard deviation

    Mine(T xpos, T ypos, T standard_deviation) {
        x = xpos, y = ypos, std = standard_deviation;
    }
} ;

// Constants
constexpr int 
RES_SHORT_SIDE = 20, // Resolution
RES_LONG_SIDE = 40,
START_VALUE = 0;
constexpr double PI = 3.14159265358979;
constexpr long double PIl = 3.14159265358979;

template<typename T>
T distance(T dx, T dy)
{
    long double dist = sqrtl(dx * dx + dy * dy);
    return (T)dist;
}

template<typename T>
T normal_distribution(T mu, T sigma, T x)
{
    return exp(-((x - mu) / sigma) * ((x - mu) / sigma) / 2 ) / (sqrt(2 * PI) * sigma);
    return expl(-((x - mu) / sigma) * ((x - mu) / sigma) / 2 ) / (sqrtl(2 * PIl) * sigma);

    // std::cout << typeid(T).name() << "\n\n\n\n" << std::endl;
    // abort("Unsupported datatype");
    return 1;
}



/*
Input: points corresponding to the observed mine locations. Should be in the coordinate system of the minefield
Output: heatmap of the mines
*/
template<typename T>
std::vector<std::vector<T>> generate_mine_map(std::vector<Mine<T>> recorded_mines)
{
    // The map output; makes the map shape with 
    std::vector<std::vector<T>> output(RES_LONG_SIDE, std::vector<T>(RES_SHORT_SIDE, START_VALUE));

    double GAUSSIAN_BLUR_LIMIT = 2.5;       // Accounts for 99% of the probability

    for (const Mine<T> &mine : recorded_mines)    
    {   
        std::cout << "onteuhoneuho.rucho.nuhoenuth,.un" << std::endl;

        // x will be the short side
        for (int x = (int)(mine.x - GAUSSIAN_BLUR_LIMIT * mine.std); x <= (int)(mine.x + GAUSSIAN_BLUR_LIMIT * mine.std); x++)
        {
            if (x < 0) continue;
            if (x >= RES_SHORT_SIDE) break;

            std::cout << "oeu" << std::endl;

            // y will be the long side
            for (int y = (int)(mine.y - GAUSSIAN_BLUR_LIMIT * mine.std); y <= (int)(mine.y + GAUSSIAN_BLUR_LIMIT * mine.std); y++)
            {
                if (y < 0) continue;
                if (y >= RES_LONG_SIDE) break;

                // std::cout << "onteuhoneuho.rucho.nuhoenuth,.un" << std::endl;
                output[y][x] += normal_distribution(0.0, mine.std, distance(x - mine.x, y - mine.y));
            }
        }
    }
    return output;
}






int main() {

    std::vector<Mine<double>> mines{{12, 9, 1}, {7, 23, 0.5}, {9, 32, 1}, {1, 1, 0.2}};

    std::vector<std::vector<double>> m = generate_mine_map(mines);

    for (int x = 0; x < RES_SHORT_SIDE; x++)
    {
        for (int y = 0; y < RES_LONG_SIDE; y++)
        {
            std::cout << std::setprecision(2) << m[y][x] << "\t";
        }
        std::cout << "\n";
    }
}