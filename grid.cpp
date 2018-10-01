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
	int value = 1;
	int min_life = 1;
	bool is_p = false;
	bool is_d = false;
};

int opt_iterative(int N, vector <vector <string> > G)	{
	CELL M[N][N];

	for (int i = 0; i < N; i++)	{
		for (int j = 0; j < N; j++)	{

			try {
				int curr = stoi(G[i][j]);

				// Base Case: Set the Minimum Health at the Start as the
				// maximum of 1 and 1 - current value 
				if ((i == 0) && (j == 0)){
					if (curr < 0)	{
						M[i][j].value = 1;
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

					// Initialize storage of using bonuses
					int top_p = false;
					int top_d = false;
					int left_p = false;
					int left_d = false;

					// Find the life value and the potential increase if coming from top
					if (i != 0) {

						if (M[i - 1][j].is_p && (curr < 0))	{
							curr = 0;
							top_p = false;
							top_d = M[i - 1][j].is_d;
						} else if (M[i - 1][j].is_d && (curr > 0))	{
							curr *= 2;
							top_p = M[i - 1][j].is_p;
							top_d = false;
						}

						if ((curr + M[i - 1][j].value) < 1)	{
							top = 1 - curr;
							min_top = (top - M[i - 1][j].value) + M[i - 1][j].min_life;
						} else	{
							top = M[i - 1][j].value;
							min_top = M[i - 1][j].min_life;
						}

						top += curr;
					}

					// Reset curr in case top has power up but left doesn't
					curr = stoi(G[i][j]);

					// Find the life value and the potential increase if coming from left
					if (j != 0)	{

						if (M[i][j - 1].is_p && (curr < 0))	{
							curr = 0;
							left_p = false;
							left_d = M[i][j - 1].is_d;
						} else if (M[i][j - 1].is_d && (curr > 0))	{
							curr *= 2;
							left_p = M[i][j - 1].is_p;
							left_d = false;
						}

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
					M[i][j].min_life = min_to_add;
					if (min_top < min_left)
						M[i][j].value = top;
					else if (min_top > min_left)
						M[i][j].value = left;
					else
						M[i][j].value = max(top, left);
				}
			} catch (const std::invalid_argument& ia)	{

				if ((i != 0) && (j != 0))	{

					if (M[i - 1][j].min_life < M[i][j - 1].min_life){

						M[i][j].value = M[i - 1][j].value;
						M[i][j].min_life = M[i - 1][j].min_life;
					} else	{

						M[i][j].value = M[i][j - 1].value;
						M[i][j].min_life = M[i][j - 1].min_life;
					}
				} else if (i != 0)	{

					M[i][j].value = M[i - 1][j].value;
					M[i][j].min_life = M[i - 1][j].min_life;
				} else if (j != 0)	{

					M[i][j].value = M[i][j - 1].value;
					M[i][j].min_life = M[i][j - 1].min_life;
				} else	{

					M[i][j].value = 1;
					M[i][j].min_life = 1;
				}

				if (G[i][j].compare("P") == 0)
					M[i][j].is_p = true;

				if (G[i][j].compare("D") == 0)
					M[i][j].is_d = true;
			}
		}
	}

	return M[N - 1][N - 1].min_life;
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