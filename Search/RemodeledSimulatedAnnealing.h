//
// Created by Amida on 2021/06/29.
//

#ifndef SOCIALDISTANCE_REMODELEDSIMULATEDANNEALING_H
#define SOCIALDISTANCE_REMODELEDSIMULATEDANNEALING_H

#include "Algorithm.h"

class RemodeledSimulatedAnnealing {
public:
    static std::string class_name;

    static void Init();
    static Operation* nextStep(const std::function<double(Operation*)>& fn);
    static bool OK(Operation* operation, const std::function<double(Operation*)>& fn);

    static double probability(double eval_before, double eval_next, double temperature);
    static double temperature(double r);
    constexpr static const double alpha = 0.9;
    static int counter;
    constexpr static const double maxCount = 10000.0;

    static int debugCounter;
};


#endif //SOCIALDISTANCE_REMODELEDSIMULATEDANNEALING_H
