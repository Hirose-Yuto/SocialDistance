//
// Created by Amida on 2021/06/28.
//

#include"Utilities.h"

std::random_device Utilities::seed_gen;
std::default_random_engine Utilities::engine(Utilities::seed_gen());
std::uniform_real_distribution<> Utilities::dist(0.0, 1.0);

std::tuple<int, int, int> Utilities::nextStep(int counter) {
    std::vector<int> a = {458, 542, 499, 501};
    int x, y, student_id ;

    do {
        x = Utilities::random_int(0, MAP_SIZE_X-1);
        y = Utilities::random_int(0, MAP_SIZE_Y-1);
    } while(!Field::campus->is_InCampus(x, y) || !Utilities::thereIsNoOne(x, y));

    auto itr = Field::waitingStudents.begin();
    auto random_int = Utilities::random_int(0, Field::waitingStudents.size() - 1);
    for (int i = 0; i < random_int; i++) {
        itr++;
    }

    student_id = (*(itr))->getStudentID();

    if (counter < a.size()) {
        student_id = a[counter];
    }

    return std::make_tuple(x, y, student_id);
}

bool Utilities::is_SocialDistanced() {
    bool result = true;
    for(Student* student : Field::notInfectedStudents) {
        result &= thereIsNoOneElse(student);
    }
    return result;
}

// 12回
bool Utilities::thereIsNoOneElse(Student* student) {
    int range = 2;
    // 自身も含むため-1として始める。
    int counter = -1;
    int x = student->getPosition()->x;
    int y = student->getPosition()->y;
    // マンハッタン距離で2以内
    for (int i = -range; i <= range; i++) {
        for (int j = -(range - abs(i)); j <= (range - abs(i)); j++) {
            if(0 <= x+i && x+1 < MAP_SIZE_X && 0 <= y+j && y+j < MAP_SIZE_Y) {
                if (Field::studentPosition[x + i][y + j] != NO_ONE) {
                    counter++;
                }
            }
        }
    }
    return counter == 0;
}

bool Utilities::thereIsNoOne(int x, int y) {
    return thereIsNoOne(new Position(x, y));
}

bool Utilities::thereIsNoOne(Position* position) {
    int range = 2;
    int counter = 0;
    int x = position->x;
    int y = position->y;
    // マンハッタン距離で2以内
    for (int i = -range; i <= range; i++) {
        for (int j = -(range - abs(i)); j <= (range - abs(i)); j++) {
            if(0 <= x+i && x+1 < MAP_SIZE_X && 0 <= y+j && y+j < MAP_SIZE_Y) {
                if (Field::studentPosition[x + i][y + j] != NO_ONE) {
                    counter++;
                }
            }
        }
    }
    return counter == 0;
}

double Utilities::sumOfSatisfaction() {
    double sum = 0;
    for(Student* student: Field::students) {
        sum += student->getSatisfactionLevel();
    }
    return sum;
}


double Utilities::random_0_to_1() {
    return dist(engine);
}

int Utilities::random_int(int from, int to) {
    // 0.0以上1.0未満の値を等確率で発生させる
    std::uniform_int_distribution<> dist_int(from, to);
    return dist_int(engine);
}