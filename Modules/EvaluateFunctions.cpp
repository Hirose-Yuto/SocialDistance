//
// Created by Amida on 2021/06/28.
//

#include "EvaluateFunctions.h"

// 高いほどいい
double EvaluateFunctions::f1(Operation* operation) {
    int x = operation->x;
    int y = operation->y;
    Student* student = Field::students[operation->student_id];
    // 高いほどいい
    double value = 0;

    if(x != DEFAULT_X) {
        // 移動コスト
        value -= Field::satisfactionDiff(Field::distance(operation->position, student->getPosition()));

        int currentHowMany = Utilities::howManyPeople(student->getPosition(), 2);
        int nextHowMany = Utilities::howManyPeople(operation->position, 2);

        // 会話考慮
        value += (double) (nextHowMany - currentHowMany)/(currentHowMany+1) * 100;

        // SocialDistance考慮
        value += 1000 + (currentHowMany - nextHowMany) * 80;
    } else {
        value = 0;
    }

    return Utilities::getSumOfSatisfaction() + value;
}

// 高いほどいい
double EvaluateFunctions::f2(Operation* operation) {
    int x = operation->x;
    int y = operation->y;
    Student* student = Field::students[operation->student_id];
    // 高いほどいい
    double value = 0;

    if(x != DEFAULT_X) {
        // 移動コスト
        value -= Field::satisfactionDiff(Field::distance(operation->position, student->getPosition()));

        int alpha = 10;
        // 会話考慮
        value += Utilities::howManyPeople(operation->position, 2) * 3 * alpha;

        // SocialDistance考慮
        value += 70 * alpha - std::pow(Utilities::howManyPeople(operation->position, 2), 2) * alpha;
    } else {
        value = 0;
    }

    return Utilities::getSumOfSatisfaction() + value;
}