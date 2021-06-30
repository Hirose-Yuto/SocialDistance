//
// Created by Amida on 2021/06/28.
//

#ifndef SOCIALDISTANCE_EVALUATEFUNCTIONS_H
#define SOCIALDISTANCE_EVALUATEFUNCTIONS_H
#include "Field.h"
#include "Utilities.h"

#define DEFAULT_X -1
#define DEFAULT_Y -1
#define DEFAULT_STUDENT -2

class EvaluateFunctions{
public:
    /**
     * 移動コスト、会話、SocialDistanceをとること、感染による満足度の期待値などを考慮する。<br>
     * 操作によるその場の変動を予測し、後のことは考えない。<br>
     * (一回の移動ではそれほど変動しないと想定。)
     * @param operation
     * @return
     */
    static double f1(Operation* operation);

    static double f2(Operation* operation);
};

#endif //SOCIALDISTANCE_EVALUATEFUNCTIONS_H
