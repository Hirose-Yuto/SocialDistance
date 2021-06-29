//
// Created by Amida on 2021/06/25.
//

#include "Student.h"

void Student::move(Position* p) {
    if(is_infected) return;
    double distance = Field::distance(this->position, p);
    this->position = p;
    this->addSatisfactionLevel(-Field::satisfactionDiff(distance));
}

bool Student::drawInfectionLottery() {
    if(Utilities::random_0_to_1() <= infection_probability) {
        this->is_infected = true;
        this->satisfaction_level /= 2;
        if(Utilities::random_0_to_1() < ONSET_PROB) {
            this->is_onset = true;
            this->satisfaction_level = 0;
        }
    }
    return this->is_infected;
}