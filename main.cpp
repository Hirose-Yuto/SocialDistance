//
// Created by Amida on 2021/06/25.
//

#include<string>
#include <utility>
#include<vector>
#include<iostream>
#include<opencv2/opencv.hpp>

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

//#include "Render/render.cpp"

void printResult(const std::string& message, const std::string& relative_file_path="Result/result.txt", bool show=true);
void printResult(int value, const std::string& relative_file_path="Result/result.txt", bool show=true);

void printResultPostScript(const std::string& message, const std::string& relative_file_path="Result/result.txt", bool show=true);
void printResultPostScript(int value, const std::string& relative_file_path="Result/result.txt", bool show=true);

void drawPoint(cv::Mat img, int x, int y, bool is_infected=false);
void renderCurrentState(int counter);
void createVideo(int counter, std::string algorithmName="");

void solve(int numOfTimes);

int main(int argc, char **argv) {

    std::cout << "program start" << std::endl;

    int numOfTimes;
    if(argc >= 2) {
        numOfTimes = std::stoi(argv[1]);
    } else {
        numOfTimes = 1;
    }

    solve(numOfTimes);

}

void solve(int numOfTimes) {
    int counter = 0;
    Campus::Init();

    auto algorithm = Algorithm<SimulatedAnnealing>();

    for(int i = 0; i < numOfTimes; i++) {
        Field::Init();
        algorithm.Init();
        counter = 0;

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

            std::cout << "waitingStudents.size() : " << Field::waitingStudents.size() << std::endl;
            std::cout << "sumOfSatisfaction : " << (int) Utilities::getSumOfSatisfaction() << std::endl;
            printResultPostScript((int) Utilities::getSumOfSatisfaction(), "Result/satis"+std::to_string(i)+".txt", false);

            if(numOfTimes == 1) {
                renderCurrentState(counter);
            }
            counter++;
        }
        std::cout << std::endl;

        printResultPostScript("infectedStudents.size() : " + std::to_string(Field::infectedStudents.size()),
                              "Result/satis"+std::to_string(i)+".txt");

        std::cout << "sumOfSatisfaction : " << (int) Utilities::getSumOfSatisfaction() << std::endl;
        std::cout << counter << " steps." << std::endl;
        std::cout << i << "th search complete!" << std::endl;

        printResultPostScript(std::to_string((double)((clock()-start))/CLOCKS_PER_SEC) + "sec.",
                              "Result/satis"+std::to_string(i)+".txt");

        algorithm.registerResult(clock()-start, (int)Field::infectedStudents.size());

        std::cout << std::endl;
    }

    std::string result = algorithm.showResult(numOfTimes);
    printResult(result);

    if(numOfTimes == 1) {
        // ????????????
        createVideo(counter, algorithm.className());
    }
}

/**
 * ??????????????????????????????
 * @param message ??????????????????
 * @param relative_file_path ?????????????????????????????????????????????
 * @param show ????????????????????????????????????
 */
void printResult(const std::string& message, const std::string& relative_file_path, bool show) {
    if(show) {
        std::cout << message << std::endl;
    }
    // ????????????????????????
    std::string output_file_path = "/Users/amida/??????/?????????????????????/2021/2Q/Tu2_????????????/??????????????????????????????/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path);

    ofs_file << message;
}

void printResult(int value, const std::string& relative_file_path, bool show) {
    printResult(std::to_string(value), relative_file_path, show);
}

/**
 * ???????????????????????????
 * @param message ??????????????????
 * @param relative_file_path ?????????????????????????????????????????????
 * @param show ????????????????????????????????????
 */
void printResultPostScript(const std::string& message, const std::string& relative_file_path, bool show) {
    if(show) {
        std::cout << message << std::endl;
    }
    // ????????????????????????
    std::string output_file_path = "/Users/amida/??????/?????????????????????/2021/2Q/Tu2_????????????/??????????????????????????????/SocialDistance/" + relative_file_path;
    std::ofstream ofs_file(output_file_path, std::ios::app);

    ofs_file << message << std::endl;
}

void printResultPostScript(int value, const std::string& relative_file_path, bool show) {
    printResultPostScript(std::to_string(value) + ",", relative_file_path, show);
}

/**
 * ??????????????????
 * @param img
 * @param x
 * @param y
 * @param is_infected
 * @param is_onset
 */
void drawPoint(cv::Mat img, int x, int y, bool is_infected, bool is_onset) {
    if(is_onset) {
        cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 0, 255), 1);
    } else if(is_infected) {
        cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 255, 255), 1);
    } else {
        cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 255, 0), 1);
    }
}

/**
 * ??????????????????????????????
 * @param counter
 */
void renderCurrentState(int counter) {
    cv::Mat img;
    img = cv::imread("map/map.png");

    for(auto student: Field::students) {
        drawPoint(img, student->getPosition()->x, student->getPosition()->y, student->getIsInfected(), student->getIsOnset());
    }

    cv::imwrite("Render/pictures/map_" + std::to_string(counter) + ".jpg", img);
}

/**
 * ????????????????????????
 * @param counter
 */
void createVideo(int counter, std::string algorithmName) {
    cv::VideoWriter writer("Render/videos/mapVideo_" + algorithmName + ".mov", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 5, cv::Size(MAP_SIZE_X, MAP_SIZE_Y));
    //?????????????????????????????????????????????????????????
    if (!writer.isOpened()){
        std::cout << "Could not open the video!" << std::endl;
        return;
    }

    std::cout << "Start generating video" << std::endl;

    for(int i = 0; i <= counter; i++) {
        cv::Mat img;
        img = cv::imread("Render/pictures/map_" + std::to_string(i) + ".jpg");

        writer.write(img);

        if(i == (int)(counter/3)) {
            std::cout << "33%...";
        }
        if(i == (int)(counter/3*2)) {
            std::cout << "66%...";
        }
        std::cout << "finish!" << std::endl;

        //cv::imshow("title", img);
        //cv::waitKey(0);
    }
}
