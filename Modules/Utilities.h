//
// Created by Amida on 2021/06/28.
//

#ifndef SOCIALDISTANCE_UTILITIES_H
#define SOCIALDISTANCE_UTILITIES_H

#include<tuple>

#include "Field.h"
#include "Operation.h"

class Student;
class Operation;

class Utilities{
private:
    static std::random_device seed_gen;
    static std::default_random_engine engine;
    // 0.0以上1.0未満の値を等確率で発生させる
    static std::uniform_real_distribution<> dist;
    static double sumOfSatisfaction;
public:

    static std::vector<Operation*> generateOperationCandidates(int quantity);

    static Operation* nextStep();

    static bool is_SocialDistanced();

    static bool thereIsNoOneElse(Student* student);
    static bool thereIsNoOne(int x, int y);
    static bool thereIsNoOne(Position* position);

    static std::vector<Student*> peopleAround(Position* position, int range, const std::function<bool(Student*)>& fn = [](Student* student){return true;});
    static std::vector<Student*> notInfectedPeopleAround(Position* position, int range);
    static std::vector<Student*> infectedPeopleAround(Position* position, int range);

    static int howManyPeople(Position* position, int range, const std::function<bool(Student*)>& fn = [](Student* student){return true;});
    static int howManyNotInfectedPeople(Position* position, int range);
    static int howManyInfectedPeople(Position* position, int range);


    /**
     * 満足度の合計値を返す。
     * @return 満足度の合計値
     */
    static double getSumOfSatisfaction() {return Utilities::sumOfSatisfaction;}
    static double calculateSumOfSatisfaction();


    /**
     * 0.0以上1.0未満の値を等確率で発生させる
     * @return 乱数
     */
    static double random_0_to_1();

    static int random_int(int from, int to);
};

#endif //SOCIALDISTANCE_UTILITIES_H
