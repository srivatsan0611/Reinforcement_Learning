#include "grid_env.h"
#include <cmath>
#include <algorithm>

const double DISCOUNT_FACTOR = 0.9;
const double THRESHOLD = 0.1;

double value_iteration(GridEnvironment &env) {
    std::vector<std::vector<double>> values(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
    double delta;
    do {
        delta = 0.0;
        for (int x = 0; x < GRID_SIZE; ++x) {
            for (int y = 0; y < GRID_SIZE; ++y) {
                Point p(x, y);
                if (!env.isValid(p)) continue;

                double maxValue = -1e9;
                for (const auto &action : {Point(1, 0), Point(0, 1), Point(-1, 0), Point(0, -1)}) {
                    Point next(p.x + action.x, p.y + action.y);
                    if (env.isValid(next)) {
                        maxValue = std::max(maxValue, env.getReward(next) + DISCOUNT_FACTOR * values[next.x][next.y]);
                    }
                }

                delta = std::max(delta, std::fabs(maxValue - values[x][y]));
                values[x][y] = maxValue;
            }
        }
    } while (delta > THRESHOLD);

    std::cout << "Value Iteration completed.\n";
    return values[env.getStart().x][env.getStart().y];
}

int main() {
    GridEnvironment env;
    double start_value = value_iteration(env);
    std::cout << "Optimal value from start: " << start_value << std::endl;
    return 0;
}
