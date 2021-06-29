//
// Created by Amida on 2021/06/29.
//

#ifndef SOCIALDISTANCE_ALGORITHM_H
#define SOCIALDISTANCE_ALGORITHM_H

#include "../Modules/Operation.h"
#include "../Modules/EvaluateFunctions.h"

class Algorithm {
public:
    static void Init(){};
    static Operation* nextStep(const std::function<double(Operation*)>& fn){};
};

#endif //SOCIALDISTANCE_ALGORITHM_H
