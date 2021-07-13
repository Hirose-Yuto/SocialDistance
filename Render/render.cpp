#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "../Modules/Field.h"

void drawPoint(cv::Mat img, int x, int y, bool is_infected = false);
void renderCurrentState(int counter);

int main() {
    std::cout << "program start" << std::endl;

    cv::VideoWriter writer("mapVideo.mov", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 5, cv::Size(MAP_SIZE_X, MAP_SIZE_Y));
    //動画ファイルがちゃんと作れたかの判定。
    if (!writer.isOpened()){
        std::cout << "not Open!" << std::endl;
        return -1;
    }
    for(int i = 0; i <= 40; i++) {
        cv::Mat img;
        img = cv::imread("pictures/map_" + std::to_string(i) + ".jpg");

        writer.write(img);

        //cv::imshow("title", img);
        //cv::waitKey(0);
    }
    std::cout << "finish" << std::endl;
}


void drawPoint(cv::Mat img, int x, int y, bool is_infected) {
    if(is_infected) {
        cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 0, 255), 1);
    } else {
        cv::circle(img, cv::Point(x, y), 1, cv::Scalar(0, 255, 0), 1);
    }
}

void renderCurrentState(int counter) {
    cv::Mat img;
    img = cv::imread("map.png");

    for(auto student: Field::students) {
        drawPoint(img, student->getPosition()->x, student->getPosition()->y, student->getIsInfected());
    }

    cv::imshow("title", img);
    cv::waitKey(0);
}

void createVideo(int counter) {
    cv::VideoWriter writer("videos/mapVideo.mov", cv::VideoWriter::fourcc('m', 'p', '4', 'v'), 5, cv::Size(MAP_SIZE_X, MAP_SIZE_Y));
    //動画ファイルがちゃんと作れたかの判定。
    if (!writer.isOpened()){
        std::cout << "not Open!" << std::endl;
        return -1;
    }
    for(int i = 0; i <= counter; i++) {
        cv::Mat img;
        img = cv::imread("pictures/map_" + std::to_string(i) + ".jpg");

        writer.write(img);

        //cv::imshow("title", img);
        //cv::waitKey(0);
    }
}
