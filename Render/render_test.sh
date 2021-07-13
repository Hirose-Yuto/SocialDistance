rm -r videos
mkdir videos
clang++ -std=c++14 render.cpp \
 ../Modules/Student.cpp \
 ../Modules/Campus.cpp \
 ../Modules/Field.cpp \
 ../Modules/Utilities.cpp \
 ../Modules/EvaluateFunctions.cpp \
 ../Modules/Operation.cpp \
 ../Search/HillClimbing.cpp \
 ../Search/RemodeledSimulatedAnnealing.cpp \
 ../Search/Shortest.cpp \
 ../Search/Random.cpp \
 `pkg-config --cflags opencv4` `pkg-config --libs opencv4`
 ./a.out
 rm a.out