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

        // 会話考慮
        value += Utilities::howManyPeople(operation->position, 2) * 100;

        // SocialDistance考慮
        value += (Utilities::howManyPeople(student->getPosition(), 2) - Utilities::howManyPeople(operation->position, 2)) * 15;

        for (Student *infectedStudent : Field::infectedStudents) {
            value -= Utilities::howManyNotInfectedPeople(infectedStudent->getPosition(), 1) * ONE_METER_INFECTION_PROB *
                     MAX_SATISFACTION;
            value -= Utilities::howManyNotInfectedPeople(infectedStudent->getPosition(), 2) * TWO_METER_INFECTION_PROB *
                     MAX_SATISFACTION;
        }
    } else {
        value = 0;
    }

    return Utilities::getSumOfSatisfaction() + value;
}
