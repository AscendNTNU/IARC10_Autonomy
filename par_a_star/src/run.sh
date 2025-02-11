
clang++ main.cpp astar.cpp generate_mine_map.cpp -o main.out -std=gnu++20 -Wall -O2 && ./main.out && python3.12 visualise.py