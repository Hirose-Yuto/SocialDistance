//
// Created by Amida on 2021/06/29.
//

#ifndef SOCIALDISTANCE_SIMULATEDANNEALING_H
#define SOCIALDISTANCE_SIMULATEDANNEALING_H

#include "Algorithm.h"

class SimulatedAnnealing: public Algorithm {
public:
    static void Init();
    static Operation* nextStep(const std::function<double(Operation*)>& fn);
    static bool OK(Operation* operation, const std::function<double(Operation*)>& fn);

    static double probability(double eval_before, double eval_next, double temperature);
    static double temperature(double r);
    constexpr static const double alpha = 0.5;
    static int counter;
    constexpr static const double maxCount = 5000.0;
};

#endif //SOCIALDISTANCE_SIMULATEDANNEALING_H
