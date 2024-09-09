// Put in a prologue

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const unsigned MAX_MATRIX_SIZE   = 20;
const unsigned WIDTH_DISPLAY     = 12;

bool    readMatrixFromFile (int [][MAX_MATRIX_SIZE], unsigned&, unsigned&, ifstream&);
void         displayMatrix (int [][MAX_MATRIX_SIZE], unsigned,  unsigned);
void displayCalcMatrixSums (int [][MAX_MATRIX_SIZE], unsigned,  unsigned,  int[MAX_MATRIX_SIZE]);
void   symmetryCheckMatrix (int [], unsigned,  unsigned);
void        sortMatrixRows (int [][MAX_MATRIX_SIZE], unsigned,  unsigned);
void testSort();

int main() {
  unsigned height,
           width;
  int      matrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE],
           colSums[MAX_MATRIX_SIZE];
  string   INPUT_FILE_NAME = "matrixes.txt";
  ifstream inputFileStreamObj(INPUT_FILE_NAME);

  if (inputFileStreamObj.fail()) {
     cout << "File " << INPUT_FILE_NAME << "could not be opened !" << endl; 
     cout << endl << "Press the enter key once or twice to leave..." << endl; cin.ignore(); cin.get();
     exit(EXIT_FAILURE); 
  }

   do {  

     if (readMatrixFromFile(matrix, height, width, inputFileStreamObj))
       break;

     cout << "Input:" << endl;
     displayMatrix        (matrix, height, width);
     displayCalcMatrixSums(matrix, height, width, colSums);
     symmetryCheckMatrix  (colSums, width, height);
     sortMatrixRows       (matrix,  width, height);
     cout << "Sorted:" << endl;
     displayMatrix        (matrix, height, width);

     cout << endl << "Press the enter key once or twice to continue..." << endl; 
     cin.ignore(); 
     cin.get(); 
   } while (true);

   cout << "Program Done" << endl; 
   exit(EXIT_SUCCESS);
}

bool readMatrixFromFile(int matrix[][MAX_MATRIX_SIZE], unsigned& height, unsigned& width, ifstream& inputFileStreamObj) {
  int rows;
  int cols;
  if (!(inputFileStreamObj >> rows))
    return true;
  inputFileStreamObj >> cols;
  height = rows;
  width = cols;

  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      inputFileStreamObj >> matrix[row][col];
    }
  }

  return(false);
}


void displayMatrix(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width) {
  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      cout << setw(WIDTH_DISPLAY) << matrix[row][col];
    }
    cout << endl;
  }
}


void displayCalcMatrixSums(int matrix[][MAX_MATRIX_SIZE], unsigned height, unsigned width, int colSums[MAX_MATRIX_SIZE]) {
  cout << "Sums:" << endl;
  for (int col = 0; col < width; col++) {
    int sum = 0;
    for (int row = 0; row < height; row++) {
      sum += matrix[row][col];
    }

    colSums[col] = sum;
    cout << setw(WIDTH_DISPLAY) << sum;
  }
  cout << "\n" << endl;
}
 

void symmetryCheckMatrix(int colSums[], unsigned width, unsigned height) {
  cout << "Vertical additive symmetry: ";
  for (int left = 0, right = width - 1; left < right; left++, right--) {
    if (colSums[left] != colSums[right]) {
      cout << "No" << "\n" << endl;
      return;
    }
  }

  cout << "Yes" << "\n" << endl;
}

void sortMatrixRows(int matrix[][MAX_MATRIX_SIZE], unsigned width, unsigned height) {
    for (int row = 0; row < height; row++) {
      for (int col = 1; col < width; col++) {
        int key = matrix[row][col];
        int insertor;
        for (insertor = col; insertor > 0 && key < matrix[row][insertor - 1]; insertor--) {
          matrix[row][insertor] = matrix[row][insertor - 1];
        }
        matrix[row][insertor] = key;
      }      
    }
}
