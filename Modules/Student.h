//
// Created by Amida on 2021/06/25.
//

#ifndef SOCIALDISTANCE_STUDENT_H
#define SOCIALDISTANCE_STUDENT_H

#include<random>
#include<algorithm>

#include "Position.h"
#include "Field.h"

// 満足度の最大値
#define MAX_SATISFACTION 10000.0
// 最初の感染者&重症者
#define FIRST_PATIENT 500

class Field;

class Student {
private:
    int student_id;
    Position* position;
    double satisfaction_level;
    double infection_probability;
    bool is_infected;
    bool is_onset;

public:
    Student(int x, int y, int id) {
        this->position = new Position(x, y);
        this->student_id = id;
        this->satisfaction_level = MAX_SATISFACTION;
        this->infection_probability = 0;
        this->is_infected = false;
        this->is_onset = false;
        if(id == FIRST_PATIENT) {
            this->is_infected = true;
            this->is_onset = true;
        }
    }

    int getStudentID() const {return this->student_id;}
    Position* getPosition() const {return this->position;}
    double getSatisfactionLevel() const {return this->satisfaction_level;};
    double getInfectionProbability() const {return this->infection_probability;}
    bool getIsInfected() const {return this->is_infected;}
    bool getIsOnset() const {return this->is_onset;}

    void  setInfectionProbability(double infection_probability){
        this->infection_probability = std::max(infection_probability, this->infection_probability);
    }

    void resetInfectionProbability() { this->infection_probability = 0;}

    /**
     * 満足度を加算。
     * @param diff 差分。マイナスも可。
     */
    void addSatisfactionLevel(double diff) {
        this->satisfaction_level = std::max(std::min(MAX_SATISFACTION, this->satisfaction_level + diff), 0.0);
    }

    /**
     * 生徒の移動。距離に応じて満足度が減る。
     * @param position 移動先。
     */
    void move(Position* position);

    /**
     * 感染発生抽選。
     * 重症化するかどうかも決定。
     * @return
     */
    bool drawInfectionLottery();



};

#endif //SOCIALDISTANCE_STUDENT_H
