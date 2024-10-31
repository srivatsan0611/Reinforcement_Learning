// grid_environment.h
#ifndef GRID_ENVIRONMENT_H
#define GRID_ENVIRONMENT_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

const int GRID_SIZE = 100;
const int OBSTACLE_PROBABILITY = 15; // Percentage chance of any cell being an obstacle
const double REWARD_GOAL = 100.0;
const double PENALTY_OBSTACLE = -10.0;
const double PENALTY_STEP = -1.0;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

class GridEnvironment {
    std::vector<std::vector<int>> grid;
    Point start, goal;

public:
    GridEnvironment() {
        grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
        generateObstacles();
        setRandomPoints();
    }

    void generateObstacles() {
        srand(time(0));
        for (int i = 0; i < GRID_SIZE; ++i) {
            for (int j = 0; j < GRID_SIZE; ++j) {
                if (rand() % 100 < OBSTACLE_PROBABILITY) {
                    grid[i][j] = -1; // Mark as obstacle
                }
            }
        }
    }

    void setRandomPoints() {
        do {
            start = {rand() % GRID_SIZE, rand() % GRID_SIZE};
        } while (grid[start.x][start.y] == -1);

        do {
            goal = {rand() % GRID_SIZE, rand() % GRID_SIZE};
        } while (grid[goal.x][goal.y] == -1 || (goal.x == start.x && goal.y == start.y));
    }

    bool isGoal(const Point &p) const { return p.x == goal.x && p.y == goal.y; }

    bool isValid(const Point &p) const {
        return p.x >= 0 && p.x < GRID_SIZE && p.y >= 0 && p.y < GRID_SIZE && grid[p.x][p.y] != -1;
    }

    const Point &getStart() const { return start; }
    const Point &getGoal() const { return goal; }

    double getReward(const Point &p) const {
        if (isGoal(p)) return REWARD_GOAL;
        if (grid[p.x][p.y] == -1) return PENALTY_OBSTACLE;
        return PENALTY_STEP;
    }
};

#endif
