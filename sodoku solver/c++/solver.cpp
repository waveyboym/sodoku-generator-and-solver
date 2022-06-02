#include "solver.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
int** initialize2DArray(int row, int col, int** array);
std::string* initialize1DArray(int length, std::string* array);

solver::solver(std::string filepath){
    std::ifstream infile;
    this->sodokuBoard = NULL;
    std::string* rowValues = NULL;
    rowValues = initialize1DArray(this->ROWSIZE, rowValues);

    infile.open(filepath.c_str());
    if(infile){
        std::string filestring;
        int row = 0;
        while(getline(infile, filestring, '\n')){
            rowValues[row] = filestring;
            ++row;
        }
    }
    else{
        delete [] rowValues;
        rowValues = NULL;
        std::cout << "cannot find file path" << std::endl; 
        return;
    }
    infile.close();

    this->sodokuBoard = initialize2DArray(this->ROWSIZE, this->COLSIZE, this->sodokuBoard);
    
    for(int i = 0; i < this->ROWSIZE; ++i){
        std::string oneRow = rowValues[i];
        for(int j = 0; j < this->COLSIZE; ++j){
            std::stringstream stringVal;
            stringVal << oneRow[j]; int temp; stringVal >> temp;
            this->sodokuBoard[i][j] = temp;
        }
    }
    //deallocate the rowvalues array
    delete [] rowValues;
    rowValues = NULL;
    std::cout << "unsolved board is: " << std::endl;
    this->displayBoard();
}

solver::~solver(){
    if(this->sodokuBoard == NULL)return;

    for(int i = 0; i < this->ROWSIZE; ++i) delete [] this->sodokuBoard[i];
    delete [] this->sodokuBoard;
}

void solver::displayBoard(){
    if(this->sodokuBoard == NULL)return;
        for(int i = 0; i < this->ROWSIZE; ++i){
            for(int j = 0; j < this->COLSIZE; ++j){
                std::cout << sodokuBoard[i][j] << " ";
            }
            std::cout << std::endl;
        }
}

void solver::startSolver(){
    if(this->solveRecursively()){
        std::cout << std::endl;
        std::cout << "Successfully solved the puzzle!" << std::endl;
        std::cout << std::endl;
        this->displayBoard();
    }
    else{
        std::cout << std::endl;
        std::cout << "No solution found" << std::endl;
        std::cout << std::endl;
        this->displayBoard();
    }
}

bool solver::solveRecursively(){
    int * co_ordsArr = new int[2]; co_ordsArr[0] = -1; co_ordsArr[1] = -1;
    co_ordsArr = this->findfreeXandYCo_Ords(co_ordsArr);
    int y_co_ord = co_ordsArr[0], x_co_ord = co_ordsArr[1];
    if(y_co_ord == -1 && x_co_ord == -1){
        //deallocate the rowvalues array
        delete [] co_ordsArr;
        co_ordsArr = NULL;
        return true;
    }
                
    for(int potentialNum = 1; potentialNum <= 9; ++potentialNum){
        if(this->isSafeForPlacement(potentialNum, y_co_ord, x_co_ord)){
            this->sodokuBoard[y_co_ord][x_co_ord] = potentialNum;
            if(this->solveRecursively()){ 
                //deallocate the rowvalues array
                delete [] co_ordsArr;
                co_ordsArr = NULL;
                return true;
            }
            else this->sodokuBoard[y_co_ord][x_co_ord] = 0;
        }

        if(potentialNum == 9){
            this->sodokuBoard[y_co_ord][x_co_ord] = 0;
            //deallocate the rowvalues array
            delete [] co_ordsArr;
            co_ordsArr = NULL;
            return false;
        }
    }
    //deallocate the rowvalues array
    delete [] co_ordsArr;
    co_ordsArr = NULL;
    return true;
}

int* solver::findfreeXandYCo_Ords(int* array){
    for(int y_co_ord = 0; y_co_ord < this->ROWSIZE; ++y_co_ord){
        for(int x_co_ord = 0; x_co_ord < this->COLSIZE; ++x_co_ord){
            if(this->sodokuBoard[y_co_ord][x_co_ord] == 0){
                array[0] = y_co_ord;
                array[1] = x_co_ord;
                return array;
            }
        }
    }
    return array;
}

bool solver::isSafeForPlacement(int potentialNum, int y_co_ord, int x_co_ord){
    if(!this->checkXAxis(potentialNum, y_co_ord)) return false;
    if(!this->checkYAxis(potentialNum, x_co_ord)) return false;
    if(!this->checkGrid(potentialNum, x_co_ord, y_co_ord)) return false;

    return true;
}

bool solver::checkXAxis(int potentialNum, int y_co_ord){
    for(int i = 0; i < this->COLSIZE; ++i)
        if(this->sodokuBoard[y_co_ord][i] == potentialNum)return false;
    return true;
}

bool solver::checkYAxis(int potentialNum, int x_co_ord){
    for(int i = 0; i < this->ROWSIZE; ++i)
        if(this->sodokuBoard[i][x_co_ord] == potentialNum)return false;
    return true;
}

bool solver::checkGrid(int potentialNum, int x_co_ord, int y_co_ord){
    //not my code-> sourced from https://www.javatpoint.com/sudoku-in-java#:~:text=Sudoku%20is%20a%20logic%2Dbased,(1%20and%209%20inclusive).
        int sqrtNum = sqrt(9);
        int row = y_co_ord - y_co_ord%sqrtNum, col = x_co_ord - x_co_ord%sqrtNum;

        for(int i = row; i < row + sqrtNum; ++i){
            for(int j = col; j < col + sqrtNum; ++ j){
                if(this->sodokuBoard[i][j] == potentialNum)return false;
            }
        }
        /////////
        return true;
}

int** initialize2DArray(int row, int col, int** array){
    array = new int*[row];
    for(int i = 0; i < row; ++i) array[i] = new int[col];

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            array[i][j] = 0;
        }
    }
    return array;
}

std::string* initialize1DArray(int length, std::string* array){
    array = new std::string[length];
    for(int i = 0; i < length; ++i) array[i] = "";
    return array;
}