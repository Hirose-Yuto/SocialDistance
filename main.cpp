//
// Created by Amida on 2021/06/25.
//

#include<string>
#include<vector>
#include<iostream>

#include "Modules/Student.h"
#include "Modules/Campus.h"
#include "Modules/Field.h"

int main() {
    Field::Init();
    int counter = 0;

    while(!Utilities::is_SocialDistanced()) {
        auto nextStep = Utilities::nextStep(counter);
        int x = std::get<0>(nextStep);
        int y = std::get<1>(nextStep);
        int student_id = std::get<2>(nextStep);

        Field::moveStudent(student_id, x, y);

        Field::regularEvent();

        auto socialDistancedStudents = Field::socialDistancedStudents;
        auto notSocialDistancedStudents = Field::notSocialDistancedStudents;
        auto studentPosition = Field::studentPosition;
        auto infectedStudents = Field::infectedStudents;

        std::cout << "student_id : " << student_id << std::endl;

        std::cout << "notSocialDistancedStudents.size() : " << notSocialDistancedStudents.size() << std::endl;
        std::cout << "sumOfSatisfaction : " << (int)Utilities::sumOfSatisfaction() << std::endl;
        counter++;
    }

    std::cout << "sumOfSatisfaction : " << (int)Utilities::sumOfSatisfaction() << std::endl;
    auto infectedStudents = Field::infectedStudents;
    std::cout << "infectedStudents.size() : " << infectedStudents.size() << std::endl;

}


