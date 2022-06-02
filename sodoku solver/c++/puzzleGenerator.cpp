#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include "puzzleGenerator.h"

int** initialise2DArray(int row, int col, int** array);

puzzleGenerator::puzzleGenerator(int num, std::string filepath){
    srand(time(0));
    this->numOfZerosToPlace = num;
    this->filePath = filepath;
    this->sodokuBoard = initialise2DArray(this->ROWSIZE, this->COLSIZE, this->sodokuBoard);
}

puzzleGenerator::~puzzleGenerator(){
    if(this->sodokuBoard == NULL)return;

    for(int i = 0; i < this->ROWSIZE; ++i) delete [] this->sodokuBoard[i];
    delete [] this->sodokuBoard;
}

void puzzleGenerator::generatePuzzle(){
    this->fillInDiagonal();
    this->fillInEmptySpots();
    this->placeZerosOnGrid();
    this->writeToFile();
}

int puzzleGenerator::randomNum(){   return rand()%10;}

void puzzleGenerator::fillInDiagonal(){
    for(int i = 0; i < this->ROWSIZE; ++i){
        for(int j = 0; j < this->COLSIZE; ++j){
            if(((i >= 0) && (i <= 2)) && ((j >= 0) && (j <= 2))){
                this->fillInGrid(i, j);
            }
            else if(((i >= 3) && (i <= 5)) && ((j >= 3) && (j <= 5))){
                this->fillInGrid(i, j);
            }
            else if(((i >= 6) && (i <= 8)) && ((j >= 6) && (j <= 8))){
                this->fillInGrid(i, j);
            }
        }
    }
}

void puzzleGenerator::fillInGrid(int y_co_ord, int x_co_ord){
    if(this->placesTaken(y_co_ord, x_co_ord) <= 6){
        int potentialNum = this->randomNum();
        if(potentialNum == 0) ++potentialNum;

        while(!(this->checkGrid(potentialNum, y_co_ord, x_co_ord))){
            potentialNum = this->randomNum();
        }
        this->sodokuBoard[y_co_ord][x_co_ord] = potentialNum;   return;
    }
    else{
        for(int i = 1; i <= 9; ++i){
            if(this->checkGrid(i, y_co_ord, x_co_ord)){
                this->sodokuBoard[y_co_ord][x_co_ord] = i;   return;
            }
        }
    }
}

bool puzzleGenerator::checkGrid(int potentialNum, int y_co_ord, int x_co_ord){
    int sqrtNum = sqrt(9);
    int row = y_co_ord - y_co_ord%sqrtNum, col = x_co_ord - x_co_ord%sqrtNum;

    for(int i = row; i < row + sqrtNum; ++i){
        for(int j = col; j < col + sqrtNum; ++ j){
            if(this->sodokuBoard[i][j] == potentialNum)return false;
        }
    }
    return true;
}

int puzzleGenerator::placesTaken(int y_co_ord, int x_co_ord){
    int toReturn = 0;
    int sqrtNum = sqrt(9);
    int row = y_co_ord - y_co_ord%sqrtNum, col = x_co_ord - x_co_ord%sqrtNum;

    for(int i = row; i < row + sqrtNum; ++i){
        for(int j = col; j < col + sqrtNum; ++ j){
            if(this->sodokuBoard[i][j] != 0)++toReturn;
        }
    }
    return toReturn;
}

bool puzzleGenerator::fillInEmptySpots(){
    int * co_ordsArr = new int[2]; co_ordsArr[0] = -1; co_ordsArr[1] = -1;
    co_ordsArr = this->findfreeXandYCo_Ords(co_ordsArr);
    int y_co_ord = co_ordsArr[0], x_co_ord = co_ordsArr[1];
    if(y_co_ord == -1 && x_co_ord == -1){
        //deallocate the co_ords array
        delete [] co_ordsArr;
        co_ordsArr = NULL;
        return true;
    }
                
    for(int potentialNum = 1; potentialNum <= 9; ++potentialNum){
        if(this->isSafeForPlacement(potentialNum, y_co_ord, x_co_ord)){
            this->sodokuBoard[y_co_ord][x_co_ord] = potentialNum;
            if(this->fillInEmptySpots()){ 
                //deallocate the co_ords array
                delete [] co_ordsArr;
                co_ordsArr = NULL;
                return true;
            }
            else this->sodokuBoard[y_co_ord][x_co_ord] = 0;
        }

        if(potentialNum == 9){
            this->sodokuBoard[y_co_ord][x_co_ord] = 0;
            //deallocate the co_ords array
            delete [] co_ordsArr;
            co_ordsArr = NULL;
            return false;
        }
    }
    //deallocate the co_ords array
    delete [] co_ordsArr;
    co_ordsArr = NULL;
    return true;
}

int* puzzleGenerator::findfreeXandYCo_Ords(int* array){
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

bool puzzleGenerator::isSafeForPlacement(int potentialNum, int y_co_ord, int x_co_ord){
    if(!this->checkXAxis(potentialNum, y_co_ord)) return false;
    if(!this->checkYAxis(potentialNum, x_co_ord)) return false;
    if(!this->checkGrid(potentialNum, y_co_ord, x_co_ord)) return false;

    return true;
}

bool puzzleGenerator::checkXAxis(int potentialNum, int y_co_ord){
    for(int i = 0; i < this->COLSIZE; ++i)
        if(this->sodokuBoard[y_co_ord][i] == potentialNum)return false;
    return true;
}

bool puzzleGenerator::checkYAxis(int potentialNum, int x_co_ord){
    for(int i = 0; i < this->ROWSIZE; ++i)
        if(this->sodokuBoard[i][x_co_ord] == potentialNum)return false;
    return true;
}

void puzzleGenerator::placeZerosOnGrid(){
    for(int i = 0; i < this->numOfZerosToPlace; ++i){
        int x_co_ord = this->randomNum();
        int y_co_ord = this->randomNum();
        if(x_co_ord == 9) --x_co_ord;
        if(y_co_ord == 9) --y_co_ord;

        while(this->sodokuBoard[y_co_ord][x_co_ord] == 0){
            x_co_ord = this->randomNum();
            y_co_ord = this->randomNum();
            if(x_co_ord == 9) --x_co_ord;
            if(y_co_ord == 9) --y_co_ord;
        }
        this->sodokuBoard[y_co_ord][x_co_ord] = 0;
    }
}

void puzzleGenerator::writeToFile(){
    std::ofstream filestream;
    filestream.open((this->filePath).c_str());
    if(!filestream.is_open()){  std::cout << "cannot find file" << std::endl;return;}

    for(int i = 0; i < this->ROWSIZE; ++i){
        std::string tempLine;
        for(int j = 0; j < this->COLSIZE; ++j){
            std::stringstream os;
            std::string tempStore;
            os << this->sodokuBoard[i][j];
            os >> tempStore;
            tempLine += tempStore;
        }
        if(i != this->ROWSIZE - 1)tempLine += "\n";
        filestream << tempLine;
    }
    filestream.close();
}

int** initialise2DArray(int row, int col, int** array){
    array = new int*[row];
    for(int i = 0; i < row; ++i) array[i] = new int[col];

    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            array[i][j] = 0;
        }
    }
    return array;
}