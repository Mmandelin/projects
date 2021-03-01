package sudoku;


import java.io.File;

public class Main {
    public static void main(String[] args){
        SudokuApplication.main(new String[]{});

        //poistaa gamedata tiedoston, jos sellainen on jo
        File existingFile = new File("E:\\\\appi projektit\\\\Java\\\\Sudoku\\\\gamedata.txt");

        if (existingFile.exists() && existingFile.isFile()) {
            existingFile.delete();
        }

    }
}