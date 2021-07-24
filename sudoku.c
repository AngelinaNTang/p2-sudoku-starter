// Sudoku puzzle verifier and solver

#include <assert.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
	int row;
	int column;
  int psize;
  int **grid;
  bool complete;
  bool valid;
  int sq;
  int numOfThreads;
} parameters;

void containsSubgrid(int psize)
{
  double sq;
  sq = sqrt(psize);
  sq *= 10.00;
  if ((int)sq % 10 != 0)
  {
    fprintf(stderr, "Grid does not contain subgrids. Exiting.\n\n");
    exit(-1);
  }
}

void* validateVertical(void* param)
{
  parameters *data = (parameters *) param;
  int startRow = data->row;
  int startColumn = data->column;
  int psize = data->psize;
  int **grid = data->grid;

  int validityArray[psize];

  for (int a = 0; a < psize; a++)
  {
    validityArray[a] = 0;
  }

  for(int i = startRow; i <= psize; i++)
  {
    int x = grid[startColumn][i];
    if (x == 0)
    {
      data->complete = false;
      pthread_exit(param);
    }
    else if (validityArray[x - 1] == 0)
    {
      validityArray[x - 1]++;
    }
  }

  for (int y = 0; y < psize; y++)
  {
    if (validityArray[y] != 1)
    {
      data->valid = false;
    }
  }
  pthread_exit(param);
}

void* validateHorizontal(void* param)
{
  parameters *data = (parameters *) param;
  int startRow = data->row;
  int startColumn = data->column;
  int psize = data->psize;
  int **grid = data->grid;

  int validityArray[psize];

  for (int a = 0; a < psize; a++)
  {
    validityArray[a] = 0;
  }

  for(int i = startColumn; i <= psize; i++)
  {
    int x = grid[i][startRow];
    if (x == 0)
    {
      data->complete = false;
      pthread_exit(param);
    }
    else if (validityArray[x - 1] == 0)
    {
      validityArray[x - 1]++;
    }
  }

  for (int y = 0; y < psize; y++)
  {
    if (validityArray[y] != 1)
    {
      data->valid = false;
    }
  }
  pthread_exit(param);
}

void* validateSubgrids(void* param)
{
  parameters *data = (parameters *) param;
  int startRow = data->row;
  int startColumn = data->column;
  int psize = data->psize;
  int **grid = data->grid;
  int sq = data->sq;

  int validityArray[psize];

  for (int a = 0; a < psize; a++)
  {
    validityArray[a] = 0;
  }

  for (int i = startRow; i < startRow + sq; i++)
  {
    for (int j = startColumn; j < startColumn + sq; j++)
    {
      int x = grid[i][j];
      if (x == 0)
      {
        data->complete = false;
        pthread_exit(param);
      }
      else if (validityArray[x - 1] == 0)
      {
        validityArray[x - 1]++;
      }
    }
  }
 
  for (int y = 0; y < psize; y++)
  {
    if (validityArray[y] != 1)
    {
      data->valid = false;
    }
  }
  pthread_exit(param);
}

void validate(int psize, int **grid, bool *complete, bool *valid)
{
  int sq = (int)sqrt(psize);
  int numberOfThreads = psize*3;
  pthread_t threads[numberOfThreads];
  int threadCount = 0;

  parameters *data;

  for (int i = 1; i <= psize; i++) 
  {
		for (int j = 1; j <= psize; j++) 
    {						
			if ((i-1) % sq == 0 && (j-1) % sq == 0) 
      {
				data = (parameters *) malloc(sizeof(parameters));
				data->row = i;
				data->column = j;
        data->numOfThreads = numberOfThreads;
        data->psize = psize;
        data->grid = grid;
        data->complete = complete;
        data->valid = valid;
        data->sq = sq;
				pthread_create(&threads[threadCount], NULL, validateSubgrids, data);
        pthread_join(threads[threadCount], NULL);
        if (*complete == true && data->complete == false)
        {
          *complete = false;
        }
        if (*valid == true && data->valid == false)
        {
          *valid = false;
        }
        threadCount++;
			}
			if (i == 1) 
      {
				data = (parameters *) malloc(sizeof(parameters));	
			  data->row = i;
				data->column = j;
        data->numOfThreads = numberOfThreads;
        data->psize = psize;
        data->grid = grid;
        data->complete = complete;
        data->valid = valid;
        data->sq = sq;
				pthread_create(&threads[threadCount], NULL, validateVertical, data);
        pthread_join(threads[threadCount], NULL);
        if (*complete == true && data->complete == false)
        {
          *complete = false;
        }
        if (*valid == true && data->valid == false)
        {
          *valid = false;
        }
        threadCount++;
			}
			if (j == 1) 
      {
				data = (parameters *) malloc(sizeof(parameters));	
				data->row = i;
				data->column = j;
        data->numOfThreads = numberOfThreads;
        data->psize = psize;
        data->grid = grid;
        data->complete = complete;
        data->valid = valid;
        data->sq = sq;
				pthread_create(&threads[threadCount], NULL, validateHorizontal, data);
        pthread_join(threads[threadCount], NULL);
        if (*complete == true && data->complete == false)
        {
          *complete = false;
        }
        if (*valid == true && data->valid == false)
        {
          *valid = false;
        }
        threadCount++;
			}
		}
	}
}

void completePuzzle(int psize, int **grid)
{
  int validityArray[psize];

  for (int a = 0; a < psize; a++)
  {
    validityArray[a] = 0;
  }

  int whichRow = 0;
  int whichCol = 0;

  for (int row = 1; row <= psize; row++) {
    for (int col = 1; col <= psize; col++) {
      int x = grid[row][col];
      if (x == 0)
      {
        whichRow = row;
        whichCol = col;
      }
      else if (validityArray[x - 1] == 0)
      {
        validityArray[x - 1]++;
      }
    }
  }

  for (int y = 1; y <= psize; y++)
  {
    if (validityArray[y] == 0)
    {
      grid[whichRow][whichCol] = y;
    }
  }
}

// takes puzzle size and grid[][] representing sudoku puzzle
// and tow booleans to be assigned: complete and valid.
// row-0 and column-0 is ignored for convenience, so a 9x9 puzzle
// has grid[1][1] as the top-left element and grid[9]9] as bottom right
// A puzzle is complete if it can be completed with no 0s in it
// If complete, a puzzle is valid if all rows/columns/boxes have numbers from 1
// to psize For incomplete puzzles, we cannot say anything about validity
void checkPuzzle(int psize, int **grid, bool *complete, bool *valid) {
  containsSubgrid(psize);
  validate(psize, grid, complete, valid);
}

// takes filename and pointer to grid[][]
// returns size of Sudoku puzzle and fills grid
int readSudokuPuzzle(char *filename, int ***grid) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Could not open file %s\n", filename);
    exit(EXIT_FAILURE);
  }
  int psize;
  fscanf(fp, "%d", &psize);
  int **agrid = (int **)malloc((psize + 1) * sizeof(int *));
  for (int row = 1; row <= psize; row++) {
    agrid[row] = (int *)malloc((psize + 1) * sizeof(int));
    for (int col = 1; col <= psize; col++) {
      fscanf(fp, "%d", &agrid[row][col]);
    }
  }
  fclose(fp);
  *grid = agrid;
  return psize;
}

// takes puzzle size and grid[][]
// prints the puzzle
void printSudokuPuzzle(int psize, int **grid) {
  printf("%d\n", psize);
  for (int row = 1; row <= psize; row++) {
    for (int col = 1; col <= psize; col++) {
      printf("%d ", grid[row][col]);
    }
    printf("\n");
  }
  printf("\n");
}

// takes puzzle size and grid[][]
// frees the memory allocated
void deleteSudokuPuzzle(int psize, int **grid) {
  for (int row = 1; row <= psize; row++) {
    free(grid[row]);
  }
  free(grid);
}

// expects file name of the puzzle as argument in command line
int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: ./sudoku puzzle.txt\n");
    return EXIT_FAILURE;
  }
  // grid is a 2D array
  int **grid = NULL;
  // find grid size and fill grid
  int sudokuSize = readSudokuPuzzle(argv[1], &grid);
  bool valid = true;
  bool complete = true;
  printf(argv[1]);
  printf(":\n");
  checkPuzzle(sudokuSize, grid, &complete, &valid);
  printf("Complete puzzle? ");
  printf(complete ? "true\n" : "false\n");
  if (complete) {
    printf("Valid puzzle? ");
    printf(valid ? "true\n" : "false\n");
  }
  else
  {
    printSudokuPuzzle(sudokuSize, grid);
    printf("Complete version: \n");
    completePuzzle(sudokuSize, grid);
  }
  printSudokuPuzzle(sudokuSize, grid);
  deleteSudokuPuzzle(sudokuSize, grid);
  return EXIT_SUCCESS;
}
