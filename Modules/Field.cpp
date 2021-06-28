//
// Created by Amida on 2021/06/25.
//

#include "Field.h"



Campus* Field::campus;
std::vector<Student*> Field::students;
std::set<Student*> Field::infectedStudents;
std::set<Student*> Field::notInfectedStudents;
std::set<Student*> Field::socialDistancedStudents;
std::set<Student*> Field::notSocialDistancedStudents;
std::set<Student*> Field::waitingStudents;
std::array<std::array<int, MAP_SIZE_Y>, MAP_SIZE_X> Field::studentPosition;

void Field::Init() {
    Field::campus = new Campus();
   for(int i = 0; i < MAP_SIZE_X; i++) {
       for(int j = 0; j < MAP_SIZE_Y; j++) {
           Field::studentPosition[i][j] = NO_ONE;
       }
   }

    Field::students.reserve(NUM_OF_STUDENTS);
    // 滝プラザ付近に均等に配置
    for(int i = 0; i < NUM_OF_STUDENTS; i++) {
        auto* student = new Student(i%TAKI_WIDTH + TAKI_LEFT_TOP_X, (int)(i / TAKI_WIDTH) + TAKI_LEFT_TOP_Y, i);
        Field::students.emplace_back(student);
        Field::studentPosition[student->getPosition()->x][student->getPosition()->y] = student->getStudentID();
        Field::notSocialDistancedStudents.insert(student);
        if(i != FIRST_PATIENT) {
            Field::notInfectedStudents.insert(student);
            waitingStudents.insert(student);
        }
    }

    Field::infectedStudents.insert(Field::students[FIRST_PATIENT]);
}

std::array<std::array<int, MAP_SIZE_Y>, MAP_SIZE_X> Field::getStudentPosition() {
    return Field::studentPosition;
}

// Manhattan distance
double Field::distance(Position* p1, Position* p2) {
    return (double) abs(p1->x - p2->x) + abs(p1->y - p2->y);
}

double Field::satisfactionDiff(double distance) {
    return distance;
}

// O(1)
void Field::moveStudent(int student_id, int x, int y) {
    moveStudent(student_id, new Position(x, y));
}

// O(logN) + 12
void Field::moveStudent(int student_id, Position* position) {
    auto student = Field::students[student_id];

    if(student->getIsInfected()) return;

    // 元々いた位置から削除
    Field::studentPosition[student->getPosition()->x][student->getPosition()->y] = NO_ONE;
    // 移動
    Field::students[student_id]->move(position);
    // 移動先に更新
    Field::studentPosition[student->getPosition()->x][student->getPosition()->y] = student_id;

    // 12回
    if(Utilities::thereIsNoOneElse(student)) {
        // O(log N)
        Field::notSocialDistancedStudents.erase(student);
        Field::socialDistancedStudents.insert(student);
        Field::waitingStudents.erase(student);
    } else {
        Field::notSocialDistancedStudents.insert(student);
        Field::socialDistancedStudents.erase(student);
        Field::waitingStudents.insert(student);
    }
}

// O(N) * 12
void Field::regularEvent() {
    // O(N) * 12
    Field::calculateInfectionProbability();
    // O(N)
    Field::drawInfectionLotteries();
    // O(N) * 12
    Field::increaseSatisfactionLevel();
}

// O(N) * 12
void Field::calculateInfectionProbability() {
    // O(N)
    for(Student* student : Field::students) {
        student->resetInfectionProbability();
    }

    // O(N) * 12
    for(Student* infected_student: Field::infectedStudents) {
        Field::changeInfectionProbability(infected_student, 1, ONE_METER_INFECTION_PROB);
        Field::changeInfectionProbability(infected_student, 2, TWO_METER_INFECTION_PROB);
    }
}

// 4*d 回程度
void Field::changeInfectionProbability(Student *student, int distance, double probability) {
    int x = student->getPosition()->x;
    int y = student->getPosition()->y;
    for(int i = -distance; i <= distance; i++) {
        // マンハッタン距離で考える。
        if(Field::studentPosition[x+i][y+(distance-abs(i))] != NO_ONE) {
            Student* changed_student = Field::students[Field::studentPosition[x+i][y+(distance-abs(i))]];
            if(Field::campus->is_InBuilding(changed_student->getPosition())) {
                // 室内だと1.5倍に
                changed_student->setInfectionProbability(probability * PROB_MAGNIFICATION_IF_IN_BUILDING);
            } else {
                changed_student->setInfectionProbability(probability);
            }
        }
        if(Field::studentPosition[x+i][y-(distance-abs(i))] != NO_ONE) {
            Student* changed_student = Field::students[Field::studentPosition[x+i][y-(distance-abs(i))]];
            if(Field::campus->is_InBuilding(changed_student->getPosition())) {
                // 室内だと1.5倍に
                changed_student->setInfectionProbability(probability * PROB_MAGNIFICATION_IF_IN_BUILDING);
            } else {
                changed_student->setInfectionProbability(probability);
            }
        }
    }
}

// O(N)
void Field::drawInfectionLotteries() {
    for(Student* student : Field::students) {
        if(!student->getIsInfected()) {
            // O(1)
            if(student->drawInfectionLottery()) {
                std::cout << student->getStudentID() << " got infected!" << std::endl;
                // O(1)
                // 感染したら登録
                Field::infectedStudents.insert(student);
                Field::notInfectedStudents.erase(student);
                Field::waitingStudents.erase(student);
            }
        }
    }
}

// O(N) * 12
void Field::increaseSatisfactionLevel() {
    int range = 2;
    // O(N)
    for(Student* student : Field::students) {
        // 自身も含むため-1として始める。
        int counter = -1;
        int x = student->getPosition()->x;
        int y = student->getPosition()->y;
        // マンハッタン距離で2以内 12回の計算
        for (int i = -range; i <= range; i++) {
            for (int j = -(range - abs(i)); j <= (range - abs(i)); j++) {
                if (Field::studentPosition[x + i][y + i] != NO_ONE) {
                    counter++;
                }
            }
        }
        // O(1)
        double diff = Field::satisfactionDiffByConversation(counter);
        student->addSatisfactionLevel(diff);
    }
}

double Field::satisfactionDiffByConversation(int num_of_people) {
    return 1 - exp(-num_of_people);
}
