//
// Created by Amida on 2021/06/25.
//

#ifndef SOCIALDISTANCE_CAMPUS_H
#define SOCIALDISTANCE_CAMPUS_H

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>

#include "Position.h"

class Campus {
public:
    Campus() {
        this->green_northMap = getMapData("green_north.csv");
        this->east_west_southMap = getMapData("east_west_south.csv");
        this->stoneMap = getMapData("stone.csv");
    }

    bool is_InCampus(int x, int y);
    bool is_InCampus(Position* position);
    bool is_InBuilding(Position* position);

private:
    std::vector<Position*> green_northMap;
    std::vector<Position*> east_west_southMap;
    std::vector<Position*> stoneMap;

    std::vector<std::vector<Position*>*> buildings;

    static bool is_InObject(Position* position, std::vector<Position*>* map);

    static std::vector<Position*> getMapData(const std::string& mapFileName);

};


#endif //SOCIALDISTANCE_CAMPUS_H
