//
// Created by Amida on 2021/06/25.
//

#include<string>
#include<vector>
#include<iostream>

#include "Modules/Student.h"
#include "Modules/Campus.h"
#include "Modules/Field.h"

#include "./Search/HillClimbing.h"
#include "./Search/SimulatedAnnealing.h"

#include "Modules/EvaluateFunctions.h"

void printResult(std::string message, std::string relative_file_path = "Result/result.txt");
void printResult(int value, std::string relative_file_path = "Result/result.txt");

void printResultPostScript(std::string message, std::string relative_file_path = "Result/result.txt");
void printResultPostScript(int value, std::string relative_file_path = "Result/result.txt");

void solve(int numOfTimes);

int main(int argc, char **argv) {
    int numOfTimes;
    if(argc >= 2) {
        numOfTimes = std::stoi(argv[1]);
    } else {
        numOfTimes = 1;
    }

    solve(numOfTimes);

}

void solve(int numOfTimes) {
    double scoreSum = 0;

    for(int i = 0; i < numOfTimes; i++) {
        Field::Init();
        // 感染者の周りはとりあえず動かす
        std::vector<int> a = {458, 542, 499, 501};
        for(int student_id : a) {
            auto nextStep = Utilities::generateOperationCandidates(1)[0];
            int x = nextStep->x;
            int y = nextStep->y;
            Field::moveStudent(student_id, x, y);

            Field::regularEvent();
        }

        SimulatedAnnealing::Init();

        while (!Utilities::is_SocialDistanced()) {
            auto nextStep = SimulatedAnnealing::nextStep(EvaluateFunctions::f1);//HillClimbing::nextStep(EvaluateFunctions::f1);
            int x = nextStep->x;
            int y = nextStep->y;
            int student_id = nextStep->student_id;

            delete nextStep;
            nextStep = nullptr;

            Field::moveStudent(student_id, x, y);

            Field::regularEvent();

            std::cout << "waitingStudents.size() : " << Field::waitingStudents.size() << std::endl;
            std::cout << "sumOfSatisfaction : " << (int) Utilities::getSumOfSatisfaction() << std::endl;
            printResultPostScript((int) Utilities::getSumOfSatisfaction(), "Result/satis"+std::to_string(i)+".txt");
        }

        std::cout << "infectedStudents.size() : " << Field::infectedStudents.size() << std::endl;
        std::cout << i << "th Step Complete!" << std::endl << std::endl;
        scoreSum += Utilities::getSumOfSatisfaction();

        printResultPostScript("infectedStudents.size() : " + std::to_string(Field::infectedStudents.size()),
                              "Result/satis"+std::to_string(i)+".txt");
        printResultPostScript("annealingCounter: " + std::to_string(SimulatedAnnealing::counter),
                              "Result/satis"+std::to_string(i)+".txt");
        printResultPostScript("debugCounter: " + std::to_string(SimulatedAnnealing::debugCounter),
                              "Result/satis"+std::to_string(i)+".txt");
    }

    printResult((int)(scoreSum/numOfTimes));
}

void printResult(std::string message, std::string relative_file_path) {
    // 書き込むファイル
    std::string output_file_path = "/Users/amida/書類/東工大講義資料/2021/2Q/Tu2_人工知能/プロジェクト課題/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path);

    ofs_file << message;
}

void printResult(int value, std::string relative_file_path) {
    printResult(std::to_string(value), relative_file_path);
}

void printResultPostScript(std::string message, std::string relative_file_path) {
    // 書き込むファイル
    std::string output_file_path = "/Users/amida/書類/東工大講義資料/2021/2Q/Tu2_人工知能/プロジェクト課題/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path, std::ios::app);

    ofs_file << message << std::endl;
}

void printResultPostScript(int value, std::string relative_file_path) {
    printResultPostScript(std::to_string(value) + ",", relative_file_path);
}