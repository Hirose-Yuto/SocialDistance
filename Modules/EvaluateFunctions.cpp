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
        //std::cout << "move: " << value << std::endl;

        // 会話考慮
        value += Utilities::howManyPeople(operation->position, 2) * 1000;
        //std::cout << "conv: " << value << std::endl;

        // SocialDistance考慮
        // value += (1 - exp(-(Utilities::howManyPeople(student->getPosition(), 2) - Utilities::howManyPeople(operation->position, 2)))) * 1000;
        value += (12 - Utilities::howManyPeople(operation->position, 2)) * 80;
        // std::cout << "social: " << value << std::endl;

    } else {
        value = 0;
    }

    return Utilities::getSumOfSatisfaction() + value;
}
