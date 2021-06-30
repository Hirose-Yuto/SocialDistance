//
// Created by Amida on 2021/06/29.
//

#include "Shortest.h"

std::string Shortest::class_name = "Shortest";

Operation * Shortest::nextStep(const std::function<double(Operation *)> &fn) {
    Operation* step;
    do{
        step = Utilities::nextStep();
    } while (!Utilities::thereIsNoOne(step->position));
    return step;
}