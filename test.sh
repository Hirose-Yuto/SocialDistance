rm -r Result
mkdir Result
clang++ -o main.out -std=c++14 main.cpp \
 Modules/Student.cpp \
 Modules/Campus.cpp \
 Modules/Field.cpp \
 Modules/Utilities.cpp \
 Modules/EvaluateFunctions.cpp \
 Modules/Operation.cpp \
 Search/HillClimbing.cpp \
 Search/RemodeledSimulatedAnnealing.cpp \
 Search/Shortest.cpp \
 Search/Random.cpp
./main.out
rm ./main.out