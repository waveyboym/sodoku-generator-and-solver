import java.io.PrintWriter;
import java.util.Random;
public class puzzleGenerator {
    private final int ROWSIZE = 9, COLSIZE = 9;
    private int[][] sodokuBoard;
    private Random rand;
    private int numOfZerosToPlace;
    private String filePath;

    public puzzleGenerator(int num, String filepath){
        this.numOfZerosToPlace = num;
        this.filePath = filepath;
        this.sodokuBoard = new int[this.ROWSIZE][this.COLSIZE];
        this.rand = new Random();
    }

    public void generatePuzzle() throws Exception{
        this.fillInDiagonal();
        this.fillInEmptySpots();
        this.placeZerosOnGrid();
        this.writeToFile();
    }

    private int randomNum(){    return (this.rand.nextInt(9) + 1);}

    private void fillInDiagonal(){
        for(int i = 0; i < this.ROWSIZE; ++i){
            for(int j = 0; j < this.COLSIZE; ++j){
                if(((i >= 0) && (i <= 2)) && ((j >= 0) && (j <= 2))){
                    this.fillInGrid(i, j);
                }
                else if(((i >= 3) && (i <= 5)) && ((j >= 3) && (j <= 5))){
                    this.fillInGrid(i, j);
                }
                else if(((i >= 6) && (i <= 8)) && ((j >= 6) && (j <= 8))){
                    this.fillInGrid(i, j);
                }
            }
        }
    }

    private void fillInGrid(int y_co_ord, int x_co_ord){
        if(this.placesTaken(y_co_ord, x_co_ord) <= 6){
            int potentialNum = this.randomNum();

            while(!(this.checkGrid(potentialNum, y_co_ord, x_co_ord))){
                potentialNum = this.randomNum();
            }
            this.sodokuBoard[y_co_ord][x_co_ord] = potentialNum;   return;
        }
        else{
            for(int i = 1; i <= 9; ++i){
                if(this.checkGrid(i, y_co_ord, x_co_ord)){
                    this.sodokuBoard[y_co_ord][x_co_ord] = i;   return;
                }
            }
        }
    }

    private Boolean checkGrid(int potentialNum, int y_co_ord, int x_co_ord){
        int sqrt = (int)Math.sqrt(9);
        int row = y_co_ord - y_co_ord%sqrt, col = x_co_ord - x_co_ord%sqrt;

        for(int i = row; i < row + sqrt; ++i){
            for(int j = col; j < col + sqrt; ++ j){
                if(this.sodokuBoard[i][j] == potentialNum)return false;
            }
        }
        return true;
    }

    private int placesTaken(int y_co_ord, int x_co_ord){
        int toReturn = 0;
        int sqrt = (int)Math.sqrt(9);
        int row = y_co_ord - y_co_ord%sqrt, col = x_co_ord - x_co_ord%sqrt;

        for(int i = row; i < row + sqrt; ++i){
            for(int j = col; j < col + sqrt; ++ j){
                if(this.sodokuBoard[i][j] != 0)++toReturn;
            }
        }
        return toReturn;
    }

    private Boolean fillInEmptySpots(){
        int[] co_ordsArr = this.findfreeXandYCo_Ords();
        int y_co_ord = co_ordsArr[0], x_co_ord = co_ordsArr[1];
        if(y_co_ord == -1 && x_co_ord == -1)return true;
                
        for(int potentialNum = 1; potentialNum <= 9; ++potentialNum){
            if(this.isSafeForPlacement(potentialNum, y_co_ord, x_co_ord)){
                //System.out.println("potential: " + potentialNum + " x-co-ords: " + x_co_ord + " y-co-ords: " + y_co_ord);
                this.sodokuBoard[y_co_ord][x_co_ord] = potentialNum;
                if(this.fillInEmptySpots()) return true;
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
        if(!this.checkGrid(potentialNum, y_co_ord, x_co_ord)) return false;

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

    private void placeZerosOnGrid(){
        for(int i = 0; i < this.numOfZerosToPlace; ++i){
            int x_co_ord = this.randomNum() - 1;
            int y_co_ord = this.randomNum() - 1;

            while(this.sodokuBoard[y_co_ord][x_co_ord] == 0){
                x_co_ord = this.randomNum() - 1;
                y_co_ord = this.randomNum() - 1;
            }
            this.sodokuBoard[y_co_ord][x_co_ord] = 0;
        }
    }

    private void writeToFile() throws Exception{
        PrintWriter writer = new PrintWriter(this.filePath, "UTF-8");
        String oneRowVal = "";

        for(int i = 0; i < this.ROWSIZE; ++i){
            for(int j = 0; j < this.COLSIZE; ++j){
                oneRowVal += Integer.toString(this.sodokuBoard[i][j]);
            }
            if(i != this.ROWSIZE - 1)   writer.println(oneRowVal);
            else writer.print(oneRowVal);
            oneRowVal = "";
        }
        writer.close();
    }
}
