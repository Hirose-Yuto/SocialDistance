//
// Created by Amida on 2021/06/29.
//

#ifndef SOCIALDISTANCE_ALGORITHM_H
#define SOCIALDISTANCE_ALGORITHM_H

#include "../Modules/Operation.h"
#include "../Modules/EvaluateFunctions.h"

template<class T>
class Algorithm {
public:
    void Init(){T::Init();};
    Operation* nextStep(const std::function<double(Operation*)>& fn){
        return T::nextStep(fn);
    };

    unsigned long clock_diff_sum = 0;
    double scoreSum = 0;
    double squaredScoreSum = 0;
    int infectedPeopleSum = 0;
    void registerResult(unsigned long clock_diff, int infectedPeople) {
        double score = Utilities::getSumOfSatisfaction();
        clock_diff_sum += clock_diff;
        scoreSum += score;
        squaredScoreSum += std::pow(score, 2);
        infectedPeopleSum += infectedPeople;
    }

    std::string showResult(int numOfTimes) {
        return T::class_name + " & "
        + std::to_string((int)(scoreSum/numOfTimes)) + " & "
        + std::to_string((int)std::pow(squaredScoreSum/numOfTimes - std::pow(scoreSum/numOfTimes, 2), 0.5)) + " & "
        + std::to_string(((double)clock_diff_sum/CLOCKS_PER_SEC/numOfTimes)) + "sec & "
        + std::to_string((double)infectedPeopleSum/numOfTimes) + " \\\\";
    }

    std::string className() {
        return T::class_name;
    }
};

#endif //SOCIALDISTANCE_ALGORITHM_H
