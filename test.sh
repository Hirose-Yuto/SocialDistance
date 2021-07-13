rm -r Result
rm -r Render/pictures
rm -r Render/videos
mkdir Result
mkdir Render/pictures
mkdir Render/videos
echo "compile start"
clang++ -o main.out -std=c++14 main.cpp \
 Modules/Student.cpp \
 Modules/Campus.cpp \
 Modules/Field.cpp \
 Modules/Utilities.cpp \
 Modules/EvaluateFunctions.cpp \
 Modules/Operation.cpp \
 Search/HillClimbing.cpp \
 Search/SimulatedAnnealing.cpp \
 Search/RemodeledSimulatedAnnealing.cpp \
 Search/Shortest.cpp \
 Search/Random.cpp \
 `pkg-config --cflags opencv4` `pkg-config --libs opencv4`
./main.out
rm ./main.out