#ifndef SOLVER_H
#define SOLVER_H
#include <string>
class solver{
    private:
        static const int ROWSIZE = 9, COLSIZE = 9;
        int** sodokuBoard;
    public:
        solver(std::string filepath);
        ~solver();
        void startSolver();
    private:   
        void displayBoard();
        bool solveRecursively();
        int* findfreeXandYCo_Ords(int* array);
        bool isSafeForPlacement(int potentialNum, int y_co_ord, int x_co_ord);
        bool checkXAxis(int potentialNum, int y_co_ord);
        bool checkYAxis(int potentialNum, int x_co_ord);
        bool checkGrid(int potentialNum, int x_co_ord, int y_co_ord);
};

#endif
