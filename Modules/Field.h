//
// Created by Amida on 2021/06/25.
//

#ifndef SOCIALDISTANCE_FIELD_H
#define SOCIALDISTANCE_FIELD_H

#include<string>
#include<vector>
#include<iostream>
#include<array>
#include<set>

#include "Campus.h"
#include "Student.h"
#include "Utilities.h"

// マップ
#define MAP_SIZE 710, 540
#define MAP_SIZE_X 710
#define MAP_SIZE_Y 540
#define NUM_OF_STUDENTS 1172
// 42*28 = 1176
#define TAKI_LEFT_TOP_X 527
#define TAKI_LEFT_TOP_Y 454
#define TAKI_LEFT_TOP TAKI_LEFT_TOP_X, TAKI_LEFT_TOP_Y
#define TAKI_RIGHT_BOTTOM_X 568
#define TAKI_RIGHT_BOTTOM_Y 481
#define TAKI_RIGHT_BOTTOM TAKI_RIGHT_BOTTOM_X, TAKI_RIGHT_BOTTOM_Y
#define TAKI_WIDTH 42
#define TAKI_HEIGHT 28

// 生徒の配置情報用
#define NO_ONE -1

// 1メートルでの感染確率(マスクあり) <= マスクありなら9割以上カット (https://square.umin.ac.jp/nosmoke/material/amabie2.pdf)
#define ONE_METER_INFECTION_PROB (1*0.03)
// 2メートルでの感染確率(マスクあり)
#define TWO_METER_INFECTION_PROB (0.1*0.03)
// 3メートルでの感染確率(マスクあり) ※使うか不明
#define THREE_METER_INFECTION_PROB (0.001*0.05)

// 発症して重症化する確率(https://www.mhlw.go.jp/stf/seisakunitsuite/newpage_00011.html)
#define ONSET_PROB 0.2
// 室内のときの感染率上昇倍率
#define PROB_MAGNIFICATION_IF_IN_BUILDING 1.5

class Student;

class Field{
public:
    /** @var キャンパス情報 */
    static Campus* campus;
    /** @var 生徒たち */
    static std::vector<Student*> students;
    /** @var 感染した生徒たち */
    static std::set<Student*> infectedStudents;
    /** @var 感染してない生徒たち */
    static std::set<Student*> notInfectedStudents;
    /** @var Social Distanceをとった生徒たち */
    static std::set<Student*> socialDistancedStudents;
    /** @var Social Distanceをとってない生徒たち */
    static std::set<Student*> notSocialDistancedStudents;
    /** @var 移動待ちの(=感染しておらず、Social Distanceをとってない)生徒たち*/
    static std::set<Student*> waitingStudents;
    /** @var 生徒の配置情報 */
    static std::array<std::array<int, MAP_SIZE_Y>, MAP_SIZE_X> studentPosition;

    /**
     * 初期化
     */
    static void Init();

    /**
     * 生徒の配置情報をゲット
     * @return
     */
    static std::array<std::array<int, MAP_SIZE_Y>, MAP_SIZE_X> getStudentPosition();

    /**
     * 2点間の距離を取得。マンハッタン距離。
     * @param p1
     * @param p2
     * @return
     */
    static double distance(Position* p1, Position* p2);

    /**
     * 満足度の減少具合。距離の関数で与えられる。
     * @param distance
     * @return
     */
    static double satisfactionDiff(double distance);

    static void moveStudent(int student_id, int x, int y);
    /**
     * 生徒を移動させる。
     * @param student_id
     * @param position
     */
    static void moveStudent(int student_id, Position* position);

    /**
     * 定期的なイベントを発生させる。<br><br>
     * <b> 起こるイベント </b>
     * <ul>
     * <li> 感染確率の計算 : calculateInfectionProbability() </li>
     * <li> 感染発生抽選 : drawInfectionLotteries() </li>
     * <li> 会話による満足度の向上 : increaseSatisfactionLevel() </li>
     * </ul>
     */
    static void regularEvent();
    /**
     * 感染確率の計算。
     */
    static void calculateInfectionProbability();
    /**
     * 感染発生抽選。
     */
    static void drawInfectionLotteries();
    /**
     * 会話による満足度の向上。
     */
    static void increaseSatisfactionLevel();

    /**
     * 周りの人の感染確率を変動させる。
     * @param student 中心の生徒
     * @param distance 距離(マンハッタン距離)
     * @param probability 感染確率
     */
    static void changeInfectionProbability(Student* student,int distance , double probability);

    /**
     * 会話による満足度の上昇値。
     * 1 - exp(-num_of_people)
     * @param num_of_people 周りにいる人の人数。
     * @return
     */
    static double satisfactionDiffByConversation(int num_of_people);


};



#endif //SOCIALDISTANCE_FIELD_H
