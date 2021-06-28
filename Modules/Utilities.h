//
// Created by Amida on 2021/06/28.
//

#ifndef SOCIALDISTANCE_UTILITIES_H
#define SOCIALDISTANCE_UTILITIES_H

#include<tuple>

#include"Field.h"
class Student;

class Utilities{
private:
    static std::random_device seed_gen;
    static std::default_random_engine engine;
    // 0.0以上1.0未満の値を等確率で発生させる
    static std::uniform_real_distribution<> dist;
public:

    static std::tuple<int, int, int> nextStep(int counter);

    static bool is_SocialDistanced();

    static bool thereIsNoOneElse(Student* student);
    static bool thereIsNoOne(int x, int y);
    static bool thereIsNoOne(Position* position);

    /**
     * 満足度の合計値を返す。
     * @return 満足度の合計値
     */
    static double sumOfSatisfaction();

    /**
     * 0.0以上1.0未満の値を等確率で発生させる
     * @return 乱数
     */
    static double random_0_to_1();

    static int random_int(int from, int to);
};

#endif //SOCIALDISTANCE_UTILITIES_H
