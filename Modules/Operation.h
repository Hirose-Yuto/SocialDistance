//
// Created by Amida on 2021/06/28.
//

#ifndef SOCIALDISTANCE_OPERATION_H
#define SOCIALDISTANCE_OPERATION_H

#include "Field.h"
#include "Position.h"
#include "Student.h"

class Operation{
public:
    int x;
    int y;
    Position* position;

    int student_id;

    Operation(int x, int y, int student_id): x(x), y(y), student_id(student_id) {
        this->position = new Position(x, y);
    }

    Operation(Position* position, int student_id): position(position), student_id(student_id) {
        this->x = position->x;
        this->y = position->y;
    }
};

#endif //SOCIALDISTANCE_OPERATION_H
