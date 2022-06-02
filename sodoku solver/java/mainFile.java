public class mainFile{
    public static void main(String[] args) throws Exception{
        String filePath = "puzzlefile2.txt";//the file name can be changed to any name so long as it ends in ".txt"
        int numOfZerosToPlace = 61;//this number can be any value between 0 and 81
        puzzleGenerator newPuzzle = new puzzleGenerator(numOfZerosToPlace, filePath);
        newPuzzle.generatePuzzle();

        solver puzzle = new solver(filePath);
        puzzle.startSolver();
    }
}