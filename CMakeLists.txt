cmake_minimum_required(VERSION 3.19)
project(SocialDistance)

set(CMAKE_CXX_STANDARD 14)

add_executable(SocialDistance
        main.cpp Modules/Student.h Modules/Student.cpp Modules/Campus.cpp Modules/Campus.h Modules/Field.cpp Modules/Field.h Modules/Position.h Modules/Utilities.cpp Modules/Utilities.h Modules/EvaluateFunctions.cpp Modules/EvaluateFunctions.h Modules/Operation.cpp Modules/Operation.h Search/HillClimbing.cpp Search/HillClimbing.h Search/SimulatedAnnealing.cpp Search/SimulatedAnnealing.h Search/Algorithm.h Search/RemodeledSimulatedAnnealing.cpp Search/RemodeledSimulatedAnnealing.h Search/Shortest.cpp Search/Shortest.h Search/Random.cpp Search/Random.h)
