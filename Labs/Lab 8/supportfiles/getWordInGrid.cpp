/** This file defines and demonstrates two necessary components for the hash table lab.  
 * The first is the use of the getWordInGrid() function, which is used for 
 * retrieving a word in a grid of letters in one of the cardinal 8 directions 
 * (north, south-east, etc).  
 * The second is the use of file streams to read in input from a file.
 *
 * Written by Aaron Bloomfield, 2009
 * Updated by Imran Rauf, 2024
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>

using std::vector, std::string, std::ifstream, std::cin, std::cout, std::endl;


/** This function will read in a grid file, as per the format in the
 * lab 11 document and return a grid as 2-d vector.  
 * It uses C++ file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columnss as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
vector< vector<char> > readInGrid(string filename) {
    // set up the file stream to read in the file (takes in a C-style
    // char* string, not a C++ string object)
    ifstream fin(filename.c_str());
    
    // upon an error, return empty grid
    if ( !fin.is_open() )
        return vector< vector<char> >();
    
    // the first line is the number of rows: read it in
    int rows, cols;
    fin >> rows >> cols;
    cout << "There are " << rows << " rows." << endl;
    cout << "There are " << cols << " cols." << endl;

    vector<vector<char> > grid(rows, vector<char>(cols));

    // convert the string read in to the 2-D vector format into the grid. 
    // In the process, we'll print the grid to the screen as well.
    for ( int r = 0; r < rows; r++ ) {
        for ( int c = 0; c < cols; c++ ) {
            fin >> grid[r][c];
            cout << grid[r][c];
        }
        cout << endl;
    }

    // close the file
    fin.close();

    // return grid
    return grid;
}



/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned. 
 *
 * @return A string containing the letters in the provided direction
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 */
string getWordInGrid (const vector<vector<char>>& grid, 
                    int startRow, int startCol, int dir, int len) {
    int numRows = grid.size(), numCols = grid[0].size();
    string output;
    // the current row, and the current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for ( int i = 0; i < len; i++ ) {
        // if the current row or column is out of bounds, then break
        if ( (c >= numCols) || (r >= numRows) || (r < 0) || (c < 0) )
            break;
        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];
        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    // return the string we found.
    return output;
}


/** The main() function shows how to call both the readInGrid()
 * function as well as the getWordInGrid() function.
 */
int main() {
    // attempt to read in the file
    vector<vector<char>> grid = readInGrid("5x8.grid.txt");
    
    // if there is an error, report it
    if ( grid.size() == 0 ) {
        cout << "Error reading in file!" << endl;
        exit(1); // requires the <stdlib.h> #include header!
    }

    // Get a word (of length 10), starting at position (2,2) in the
    // array, in each of the 8 directions
    cout << endl;
    for ( int i = 0; i < 8; i++ )
        cout << i << ": " << getWordInGrid(grid, 2, 2, i, 10) << endl;
    // All done!
    return 0;
}
