//
// Created by Amida on 2021/06/28.
//

#include"Utilities.h"

std::random_device Utilities::seed_gen;
std::default_random_engine Utilities::engine(Utilities::seed_gen());
std::uniform_real_distribution<> Utilities::dist(0.0, 1.0);
double Utilities::sumOfSatisfaction;

std::vector<Operation*> Utilities::generateOperationCandidates(int quantity = 1) {
    std::vector<Operation*> operationCandidates;
    operationCandidates.reserve(quantity);
    for(int i = 0; i < quantity; i++) {
        operationCandidates.push_back(nextStep());
    }
    return operationCandidates;
}

Operation* Utilities::nextStep() {
    int x, y, student_id;
    do {
        x = Utilities::random_int(0, MAP_SIZE_X-1);
        y = Utilities::random_int(0, MAP_SIZE_Y-1);
    } while(!Field::campus->is_InCampus(x, y));

    auto itr = Field::waitingStudents.begin();
    auto random_int = Utilities::random_int(0, Field::waitingStudents.size() - 1);
    for (int i = 0; i < random_int; i++) {
        itr++;
    }

    student_id = (*(itr))->getStudentID();

    return new Operation(x, y, student_id);
}

bool Utilities::is_SocialDistanced() {
    bool result = true;
    for(Student* student : Field::notInfectedStudents) {
        if(!thereIsNoOneElse(student)) {
            Field::notSocialDistancedStudents.insert(student);
            Field::socialDistancedStudents.erase(student);
            Field::waitingStudents.insert(student);
            result = false;
        }
    }
    return result;
}

// 12回
bool Utilities::thereIsNoOneElse(Student* student) {
    int range = 2;
    // 自身も含むため-1として始める。
    int counter = Utilities::howManyPeople(student->getPosition(), range);
    counter--;
    return counter == 0;
}

bool Utilities::thereIsNoOne(int x, int y) {
    return thereIsNoOne(new Position(x, y));
}

bool Utilities::thereIsNoOne(Position* position) {
    int range = 2;
    int counter = Utilities::howManyPeople(position, range);
    return counter == 0;
}

std::vector<Student*> Utilities::peopleAround(Position *position, int range,
                                               const std::function<bool(Student *)> &fn) {
    std::vector<Student*> result;
    int x = position->x;
    int y = position->y;
    // マンハッタン距離で2以内
    for (int i = -range; i <= range; i++) {
        for (int j = -(range - abs(i)); j <= (range - abs(i)); j++) {
            if(0 <= x+i && x+i < MAP_SIZE_X && 0 <= y+j && y+j < MAP_SIZE_Y) {
                if (Field::studentPosition[x + i][y + j] != NO_ONE) {
                    Student* student = Field::students[Field::studentPosition[x + i][y + j]];
                    if(fn(student)) {
                        result.push_back(student);
                    }
                }
            }
        }
    }
    return result;
}

std::vector<Student *> Utilities::infectedPeopleAround(Position *position, int range) {
    return peopleAround(position, range, [](Student* student) {
        return Field::infectedStudents.find(student) != Field::infectedStudents.end();
    });
}

std::vector<Student *> Utilities::notInfectedPeopleAround(Position *position, int range) {
    return peopleAround(position, range, [](Student* student) {
        return Field::notInfectedStudents.find(student) != Field::notInfectedStudents.end();
    });
}

int Utilities::howManyPeople(Position *position, int range, const std::function<bool(Student*)>& fn) {
    return (int) peopleAround(position, range, fn).size();
}

int Utilities::howManyInfectedPeople(Position *position, int range) {
    return howManyPeople(position, range, [](Student* student) {
        return Field::infectedStudents.find(student) != Field::infectedStudents.end();
    });
}

int Utilities::howManyNotInfectedPeople(Position *position, int range) {
    return howManyPeople(position, range, [](Student* student) {
        return Field::notInfectedStudents.find(student) != Field::notInfectedStudents.end();
    });
}


double Utilities::calculateSumOfSatisfaction() {
    double sum = 0;
    for(Student* student: Field::students) {
        sum += student->getSatisfactionLevel();
    }
    return sumOfSatisfaction = sum;
}


double Utilities::random_0_to_1() {
    return dist(engine);
}

int Utilities::random_int(int from, int to) {
    // 0.0以上1.0未満の値を等確率で発生させる
    std::uniform_int_distribution<> dist_int(from, to);
    return dist_int(engine);
}