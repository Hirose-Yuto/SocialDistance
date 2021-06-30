//
// Created by Amida on 2021/06/25.
//

#include<string>
#include <utility>
#include<vector>
#include<iostream>

#include "Modules/Student.h"
#include "Modules/Campus.h"
#include "Modules/Field.h"

#include "./Search/Algorithm.h"
#include "./Search/HillClimbing.h"
#include "./Search/SimulatedAnnealing.h"
#include "./Search/RemodeledSimulatedAnnealing.h"
#include "./Search/Shortest.h"
#include "./Search/Random.h"

#include "Modules/EvaluateFunctions.h"

void printResult(const std::string& message, const std::string& relative_file_path="Result/result.txt", bool show=true);
void printResult(int value, const std::string& relative_file_path="Result/result.txt", bool show=true);

void printResultPostScript(const std::string& message, const std::string& relative_file_path="Result/result.txt", bool show=true);
void printResultPostScript(int value, const std::string& relative_file_path="Result/result.txt", bool show=true);

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
    Campus::Init();

    auto algorithm = Algorithm<RemodeledSimulatedAnnealing>();

    for(int i = 0; i < numOfTimes; i++) {
        Field::Init();

        /*
        // 感染者の周りはとりあえず動かす
        std::vector<int> a = {};//{458, 542, 499, 501, 416, 457, 459, 498, 502, 541, 543, 584}; //{458, 542, 499, 501}; //
        for(int student_id : a) {
            auto nextStep = Utilities::generateOperationCandidates(1)[0];
            int x = nextStep->x;
            int y = nextStep->y;
            Field::moveStudent(student_id, x, y);

            Field::regularEvent();
        }
        */

        algorithm.Init();

        auto start = clock();
        while (!Utilities::is_SocialDistanced()) {
            auto nextStep = algorithm.nextStep(EvaluateFunctions::f1);
            int x = nextStep->x;
            int y = nextStep->y;
            int student_id = nextStep->student_id;

            delete nextStep;
            nextStep = nullptr;

            Field::moveStudent(student_id, x, y);

            Field::regularEvent();

            // std::cout << "waitingStudents.size() : " << Field::waitingStudents.size() << std::endl;
            // std::cout << "sumOfSatisfaction : " << (int) Utilities::getSumOfSatisfaction() << std::endl;
            printResultPostScript((int) Utilities::getSumOfSatisfaction(), "Result/satis"+std::to_string(i)+".txt", false);
        }

        printResultPostScript("infectedStudents.size() : " + std::to_string(Field::infectedStudents.size()),
                              "Result/satis"+std::to_string(i)+".txt");

        std::cout << "sumOfSatisfaction : " << (int) Utilities::getSumOfSatisfaction() << std::endl;
        std::cout << i << "th Step Complete!" << std::endl;

        printResultPostScript(std::to_string((double)((clock()-start))/CLOCKS_PER_SEC) + "sec.",
                              "Result/satis"+std::to_string(i)+".txt");

        algorithm.registerResult(clock()-start, (int)Field::infectedStudents.size());

        std::cout << std::endl;
        }

    std::string result = algorithm.showResult(numOfTimes);
    printResult(result);
}

void printResult(const std::string& message, const std::string& relative_file_path, bool show) {
    if(show) {
        std::cout << message << std::endl;
    }
    // 書き込むファイル
    std::string output_file_path = "/Users/amida/書類/東工大講義資料/2021/2Q/Tu2_人工知能/プロジェクト課題/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path);

    ofs_file << message;
}

void printResult(int value, const std::string& relative_file_path, bool show) {
    printResult(std::to_string(value), relative_file_path, show);
}

void printResultPostScript(const std::string& message, const std::string& relative_file_path, bool show) {
    if(show) {
        std::cout << message << std::endl;
    }
    // 書き込むファイル
    std::string output_file_path = "/Users/amida/書類/東工大講義資料/2021/2Q/Tu2_人工知能/プロジェクト課題/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path, std::ios::app);

    ofs_file << message << std::endl;
}

void printResultPostScript(int value, const std::string& relative_file_path, bool show) {
    printResultPostScript(std::to_string(value) + ",", relative_file_path, show);
}