package sudoku.constants;

/**
 * This enum exists to provide better legibility for the sudoku.userinterface.sudoku.userinterface.logic required to check if each Square in the
 * sudoku puzzle contains a valid value. See GameLogic.java for usage.
 *
 * Top, Middle, and Bottom rows for each square (a square is comprised of 3x3 "tiles", with 9 squares total in a
 * sudoku puzzle).
 *
 * The values represent the Y coordinates of each tile.
 */
public enum Rows {
    TOP,
    MIDDLE,
    BOTTOM
}