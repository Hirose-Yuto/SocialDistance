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
 Search/SimulatedAnnealing.cpp
./main.out 5
rm ./main.out