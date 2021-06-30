//
// Created by Amida on 2021/06/30.
//

#include "Random.h"

std::string Random::class_name = "Random";

Operation * Random::nextStep(const std::function<double(Operation *)> &fn) {
    return Utilities::nextStep();
}