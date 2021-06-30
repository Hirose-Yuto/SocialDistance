//
// Created by Amida on 2021/06/29.
//

#ifndef SOCIALDISTANCE_SHORTEST_H
#define SOCIALDISTANCE_SHORTEST_H

#include "Algorithm.h"

class Shortest {
public:
    static std::string class_name;

    static void Init(){};
    static Operation* nextStep(const std::function<double(Operation*)>& fn);
};

#endif //SOCIALDISTANCE_SHORTEST_H
