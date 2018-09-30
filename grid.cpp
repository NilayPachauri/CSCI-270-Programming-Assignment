/*
	CSCI 270 Fall 2018
	Programming Assignment
	Name   : Nilay Pachauri
	Email  : pachauri@usc.edu
	USC ID : 3787351614
*/
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
//	Feel free to include any other C++ standard library if necessary.

using namespace std;
//	You can add any custom classes / helper functions here.

struct CELL {
	int value = numeric_limits<int>::max();
	int min_life = 1;
};

int opt_iterative(int N, vector <vector <string> > G)	{
	CELL M[N][N];

	int min_life = 1;

	cout << endl;

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)	{

			int curr = stoi(G[i][j]);

			// Base Case: Set the Minimum Health at the Start as the
			// maximum of 1 and 1 - current value 
			if ((i == 0) && (j == 0)){
				if (curr < 0)	{
					M[i][j].value = 1 - curr;
					M[i][j].min_life -= curr;
				} else	{
					M[i][j].value = 1 + curr;
				}
			} else 	{

				// Store the theoretical values that you would get if you took
				// the top or the left path to get to this square
				int top = numeric_limits<int>::max();
				int left = numeric_limits<int>::max();

				// Store the minimum life increase necessary to pass that tile
				int min_top = numeric_limits<int>::max();
				int min_left = numeric_limits<int>::max();

				// Find the life value and the potential increase if coming from top
				if (i != 0) {
					if ((curr + M[i - 1][j].value) < 1)	{
						top = 1 - curr;
						min_top = (top - M[i - 1][j].value) + M[i - 1][j].min_life;
					} else	{
						top = M[i - 1][j].value;
						min_top = M[i - 1][j].min_life;
					}

					top += curr;
				}

				// Find the life value and the potential increase if coming from left
				if (j != 0)	{
					if ((curr + M[i][j - 1].value) < 1)	{
						left = 1 - curr;
						min_left = (left - M[i][j - 1].value) + M[i][j - 1].min_life;
					} else	{
						left = M[i][j - 1].value;
						min_left = M[i][j - 1].min_life;
					}

					left += curr;
				}

				// Determine what the minimum life necessary to get past this
				// point and if an increase is necessary
				int min_to_add = 0;
				if (min(min_top, min_left) != numeric_limits<int>::max())
					min_to_add = min(min_top, min_left);

				// Store the minimum life value and the minimum life increase
				M[i][j].value = min(top, left);
				M[i][j].min_life += min_to_add;
			}
		}
	}

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)
			cout << M[i][j].value << " ";
		cout << endl;
	}

	cout << endl;

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)
			cout << M[i][j].min_life << " ";
		cout << endl;
	}

	return min_life;
}

/*
 * 	Purpose:
 *		Recursively determine the minimum amount of life Brian needs to
 *		paint his message
 *
 * 	Parameters:
 * 		m:	the current minimum life value it took to get to G[x,y]
 * 		x:	the x-coordinate of your location in the vector
 * 		y:	the y-coordinate of your location in the vector
 * 		N:	the number of rows/columns in G
 * 		G:	the array containing the values of the grid
 *
 *	Returns:
 *		The minimum life Brian needs in order to paint his message
 */
int opt_recursive(int m, int x, int y, int N, vector <vector <string> > G)	{

	// Let curr be the current value of the cell
	int curr = stoi(G[x][y]);

	// If we've reached the bottom right corner,
	// simply output it's value
	if ((x == (N - 1)) && (y == (N - 1))){
		int min_val = 0;
		if (m + curr < 1)
			min_val = 1 - curr;

		return min_val;
	} else {

		// Initialize the minimum value of Brian's health needed to traverse
		// from G[x,y] to the end
		int bottom = numeric_limits<int>::max();
		int right = numeric_limits<int>::max();
		int min_val = 0;

		// Update the minimum life necessary depending on the current cell
		if (m + curr < 1)
			min_val = 1 - (m + curr);

		// Update bottom and the right based on the optimal value of their
		// recursive subcalls
		if (x != (N - 1))
			bottom = min_val + opt_recursive(min_val + m + curr, x + 1, y, N, G);
		if (y != (N - 1))
			right = min_val + opt_recursive(min_val + m + curr, x, y + 1, N, G);

		// Return the minimum life value betweeen the bottom and the right path
		return min(bottom, right);
	}

}


int solve(int N, vector<vector<string> > G) {
/*
	Please complete this function.
	N: Number of rows / columns of the grid.
	G: A 2d vector (N*N) indicating the grid.
		G[0][0] is the top left corner
		G[N-1][N-1] is the bottom right corner
	Return: the minimum life Brain needs to complete his task.
*/

	// Recursive Solution
	// int initial_min_life = 1;
	// return initial_min_life + opt_recursive(initial_min_life, 0, 0, N, G);

	// Iterative Solution
	return opt_iterative(N, G);
}

//	The main function reads the input and outputs your answer.
//	Please do not modify it. (Assume the input is well-formed;
//	You don't need to do any error-check)
int main(int argc, char **argv) {
	int N;
	vector<vector<string> > G;
	cin >> N;
	G.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			string tmp;
			cin >> tmp;
			G[i].push_back(tmp);
		}
	}
	cout << solve(N, G) << endl;
	return 0;
}