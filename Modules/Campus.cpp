//
// Created by Amida on 2021/06/25.
//

#include "Campus.h"
#include "Utilities.h"

std::vector<Position*> Campus::positionsInCampus;

std::vector<Position*> Campus::green_northMap;
std::vector<Position*> Campus::east_west_southMap;
std::vector<Position*> Campus::stoneMap;
std::vector<std::vector<Position*>*> Campus::buildings;

void Campus::Init() {
    green_northMap = getMapData("green_north.csv");
    east_west_southMap = getMapData("east_west_south.csv");
    stoneMap = getMapData("stone.csv");

    for(int i = 0; i < MAP_SIZE_X; i++) {
        for(int j = 0; j < MAP_SIZE_Y; j++) {
            if(is_InCampus(i, j)) {
                positionsInCampus.push_back(new Position(i, j));
            }
        }
    }
}

bool Campus::is_InCampus(int x, int y) {
    return is_InCampus(new Position(x, y));
}

// https://www.nttpc.co.jp/technology/number_algorithm.html
bool Campus::is_InCampus(Position* position) {
    return Campus::is_InObject(position, &green_northMap)
    || Campus::is_InObject(position, &east_west_southMap)
    || Campus::is_InObject(position, &stoneMap);
}

bool Campus::is_InBuilding(Position* position) {
    return false;
}

/**
 * 多角形の中にあるかを判定する。<br>
 * Crossing Number Algorithm (<a href="https://www.nttpc.co.jp/technology/number_algorithm.html">https://www.nttpc.co.jp/technology/number_algorithm.html</a>)<br>
 * x正方向にビームを飛ばし、横切った辺の数の偶奇で判定する。<br>
 * 偶数なら外部、奇数なら内部。
 * <ol>
 * <li> 上向きの辺は開始点を含み、終端を含まない。 </li>
 * <li> 下向きの辺は開始点を含まず、終端を含む。 </li>
 * <li> x軸水平な辺は無視する。 </li>
 * </ol>
 * @param position 点
 * @param map 多角形
 * @return
 */
bool Campus::is_InObject(Position *position, std::vector<Position *>* map) {
    int counter = 0;
    for(int i = 0; i < map->size(); i++) {
        auto p1 = (*map)[i];
        auto p2 = (*map)[(i+1) % map->size()];

        // 上向きの辺と下向きの辺いずれかに引っかかってるか。同時に水平も無視。
        if((p1->y <= position->y && position->y <  p2->y)
        || (p2->y <  position->y && position->y <= p1->y)) {
            // 判定したい点とy座標が等しい点のx座標
            int x = (p2->x - p1->x) * (position->y - p1->y) / (p2->y - p1->y) + p1->x;
            if(position->x < x) {
                counter++;
            }
        }
    }
    return counter % 2 == 1;
}


std::vector<Position*> Campus::getMapData(const std::string &mapFileName) {
    std::string str_buf;
    std::string str_comma_buf;
    //絶対パス
    std::ifstream ifs_csv_file("/Users/amida/書類/東工大講義資料/2021/2Q/Tu2_人工知能/プロジェクト課題/SocialDistance/map/" + mapFileName);

    std::vector<Position*> mapData;
    bool is_x = true;
    std::string tmpX;
    while (getline(ifs_csv_file, str_buf)) {
        // 区切るためistringstreamに
        std::istringstream i_stream(str_buf);

        // カンマ区切りで読む
        while (getline(i_stream, str_comma_buf, ',')) {
            // 交互に読み込む
            if(is_x) {
                tmpX = str_comma_buf;
            } else {
                mapData.push_back(new Position(std::stoi(tmpX), std::stoi(str_comma_buf)));
                // mapData.emplace_back(std::stoi(tmpX), std::stoi(str_comma_buf));
            }
            is_x = !is_x;
        }
    }
    return mapData;
}