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
    static void Init();

    static bool is_InCampus(int x, int y);
    static bool is_InCampus(Position* position);
    static bool is_InBuilding(Position* position);

    static std::vector<Position*> positionsInCampus;

private:
    static std::vector<Position*> green_northMap;
    static std::vector<Position*> east_west_southMap;
    static std::vector<Position*> stoneMap;

    static std::vector<std::vector<Position*>*> buildings;

    static bool is_InObject(Position* position, std::vector<Position*>* map);

    static std::vector<Position*> getMapData(const std::string& mapFileName);

};


#endif //SOCIALDISTANCE_CAMPUS_H
