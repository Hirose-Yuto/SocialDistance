//
// Created by Amida on 2021/06/29.
//

#include "SimulatedAnnealing.h"

int SimulatedAnnealing::counter;

void SimulatedAnnealing::Init() {
    counter = 0;
}

Operation* SimulatedAnnealing::nextStep(const std::function<double(Operation *)> &fn) {
    Operation* step;
    do{
        step = Utilities::generateOperationCandidates(1)[0];
        counter++;
    } while (!OK(step, fn));
    return step;
}

bool SimulatedAnnealing::OK(Operation* operation, const std::function<double(Operation *)> &fn) {
    double currentEval = fn(new Operation(DEFAULT_X, DEFAULT_Y, DEFAULT_STUDENT));
    double nextEval = fn(operation);

    if(currentEval < nextEval) {
        return true;
    } else {
        if(Utilities::random_0_to_1() < probability(currentEval, nextEval, temperature(counter))) {
            return true;
        } else {
            return false;
        }
    }
}

double SimulatedAnnealing::probability(double eval_before, double eval_next, double temperature) {
    if(eval_before <= eval_next) {
        return 1.0;
    } else {
        return exp((eval_before-eval_next)/temperature);
    }
}

double SimulatedAnnealing::temperature(double r) {
    return std::pow(alpha, r/maxCount);
}