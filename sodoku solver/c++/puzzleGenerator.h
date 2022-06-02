#ifndef PUZZLEGENERATOR_H
#define PUZZLEGENERATOR_H
#include <string>
class puzzleGenerator{
    private:
        static const int ROWSIZE = 9, COLSIZE = 9;
        int** sodokuBoard;
        int numOfZerosToPlace;
        std::string filePath;
    public:
        puzzleGenerator(int num, std::string filepath);
        ~puzzleGenerator();
        void generatePuzzle();
    private:
        int randomNum();
        void fillInDiagonal();
        void fillInGrid(int y_co_ord, int x_co_ord);
        int* findfreeXandYCo_Ords(int* array);
        int placesTaken(int y_co_ord, int x_co_ord);
        bool fillInEmptySpots();
        bool isSafeForPlacement(int potentialNum, int y_co_ord, int x_co_ord);
        bool checkXAxis(int potentialNum, int y_co_ord);
        bool checkYAxis(int potentialNum, int x_co_ord);
        bool checkGrid(int potentialNum, int y_co_ord, int x_co_ord);
        void placeZerosOnGrid();
        void writeToFile();
};

#endif