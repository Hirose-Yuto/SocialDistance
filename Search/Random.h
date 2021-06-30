//
// Created by Amida on 2021/06/30.
//

#ifndef SOCIALDISTANCE_RANDOM_H
#define SOCIALDISTANCE_RANDOM_H

#include "Algorithm.h"

class Random{
public:
    static std::string class_name;
    static void Init(){};
    static Operation* nextStep(const std::function<double(Operation*)>& fn);
};

#endif //SOCIALDISTANCE_RANDOM_H
