import java.io.File;
import java.util.Scanner;
public class solver{
    private final int ROWSIZE = 9, COLSIZE = 9;
    private int[][] sodokuBoard;

    public solver(String filepath) throws Exception{
        String[] stringArray = new String[this.ROWSIZE];
        File myObj = new File(filepath);
        if(myObj.canRead()){
            this.sodokuBoard = new int[this.ROWSIZE][this.COLSIZE];
            Scanner FileReading = new Scanner(myObj);
            int row = 0;
            while(FileReading.hasNextLine()){
                if(row < this.ROWSIZE){
                    stringArray[row] = FileReading.nextLine();
                    ++row;
                }
            }
            FileReading.close();
        }
        else if(!myObj.canRead()){System.out.println("cannot find file path");   return;}

        for(int i = 0; i < this.ROWSIZE; ++i){
            String IDnames = stringArray[i];
            for(int j = 0; j < this.COLSIZE; ++j)
                this.sodokuBoard[i][j] = Integer.parseInt(String.valueOf(IDnames.charAt(j)));
        }


        System.out.println();
        System.out.println("unsolved board is: ");
        System.out.println();
        this.displayBoard();
    }

    public void displayBoard(){
        if(this.sodokuBoard == null)return;
        for(int i = 0; i < this.ROWSIZE; ++i){
            for(int j = 0; j < this.COLSIZE; ++j){
                System.out.print(this.sodokuBoard[i][j] + " ");
            }
            System.out.println();
        }
    }

    public void startSolver(){
        if(this.SolveRecursively()){
            System.out.println();
            System.out.println("Successfully solved the puzzle!");
            System.out.println();
            this.displayBoard();
        }
        else{
            System.out.println();
            System.out.println("No solution found");
            System.out.println();
            this.displayBoard();
        }
    }

    /*solver code*/

    private Boolean SolveRecursively(){
        int[] co_ordsArr = this.findfreeXandYCo_Ords();
        int y_co_ord = co_ordsArr[0], x_co_ord = co_ordsArr[1];
        if(y_co_ord == -1 && x_co_ord == -1)return true;
                
        for(int potentialNum = 1; potentialNum <= 9; ++potentialNum){
            if(this.isSafeForPlacement(potentialNum, y_co_ord, x_co_ord)){
                this.sodokuBoard[y_co_ord][x_co_ord] = potentialNum;
                if(this.SolveRecursively()) return true;
                else this.sodokuBoard[y_co_ord][x_co_ord] = 0;
            }

            if(potentialNum == 9){
                this.sodokuBoard[y_co_ord][x_co_ord] = 0;
                return false;
            }
        }
        return true;
    }

    private int[] findfreeXandYCo_Ords(){
        int[] toReturn = new int[2];    toReturn[0] = -1;   toReturn[1] = -1;
        for(int y_co_ord = 0; y_co_ord < this.ROWSIZE; ++y_co_ord){
            for(int x_co_ord = 0; x_co_ord < this.COLSIZE; ++x_co_ord){
                if(this.sodokuBoard[y_co_ord][x_co_ord] == 0){
                    toReturn[0] = y_co_ord;
                    toReturn[1] = x_co_ord;
                    return toReturn;
                }
            }
        }
        return toReturn;
    }

    private Boolean isSafeForPlacement(int potentialNum, int y_co_ord, int x_co_ord){
        if(!this.checkXAxis(potentialNum, y_co_ord)) return false;
        if(!this.checkYAxis(potentialNum, x_co_ord)) return false;
        if(!this.checkGrid(potentialNum, x_co_ord, y_co_ord)) return false;

        return true;
    }

    private Boolean checkXAxis(int potentialNum, int y_co_ord){
        for(int i = 0; i < this.COLSIZE; ++i)
            if(this.sodokuBoard[y_co_ord][i] == potentialNum)return false;
        return true;
    }

    private Boolean checkYAxis(int potentialNum, int x_co_ord){
        for(int i = 0; i < this.ROWSIZE; ++i)
            if(this.sodokuBoard[i][x_co_ord] == potentialNum)return false;
        return true;
    }

    private Boolean checkGrid(int potentialNum, int x_co_ord, int y_co_ord){
        int sqrt = (int)Math.sqrt(9);
        int row = y_co_ord - y_co_ord%sqrt, col = x_co_ord - x_co_ord%sqrt;

        for(int i = row; i < row + sqrt; ++i){
            for(int j = col; j < col + sqrt; ++ j){
                if(this.sodokuBoard[i][j] == potentialNum)return false;
            }
        }
        return true;
    }

}