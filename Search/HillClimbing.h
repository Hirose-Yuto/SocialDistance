//
// Created by Amida on 2021/06/28.
//

#ifndef SOCIALDISTANCE_HILLCLIMBING_H
#define SOCIALDISTANCE_HILLCLIMBING_H

#include "Algorithm.h"

class HillClimbing : public Algorithm{
public:
    static void Init(){};
    static Operation* nextStep(const std::function<double(Operation*)>& fn);
    static Operation* choose(const std::vector<Operation*>& operationCandidates, const std::function<double(Operation*)>& fn);
};

#endif //SOCIALDISTANCE_HILLCLIMBING_H
