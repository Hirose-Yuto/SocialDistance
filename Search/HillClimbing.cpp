//
// Created by Amida on 2021/06/28.
//

#include "HillClimbing.h"

#include "limits"

std::string HillClimbing::class_name = "HillClimbing";

Operation* HillClimbing::nextStep(const std::function<double(Operation*)>& fn) {
    auto step =  choose(Utilities::generateOperationCandidates(50), fn);
    return step;
}

Operation* HillClimbing::choose(const std::vector<Operation *>& operationCandidates, const std::function<double(Operation*)>& fn) {
    double max_score = - std::numeric_limits<double>::infinity();
    Operation* chosen_operation;
    for(Operation* operation : operationCandidates) {
        double score = fn(operation);
        if(max_score < score) {
            max_score = score;
            chosen_operation = operation;
        }
    }

    return chosen_operation;
}