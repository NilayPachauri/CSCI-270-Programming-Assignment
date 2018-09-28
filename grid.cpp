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

/*
 * 	Purpose:
 *		Recursively determine the minimum amount of life Brian needs to
 *		paint his message
 *
 * 	Parameters:
 * 		min:	the current minimum life value it took to get to G[x,y]
 * 		x:	the x-coordinate of your location in the vector
 * 		y:	the y-coordinate of your location in the vector
 * 		N:	the number of rows/columns in G
 * 		G:	the array containing the values of the grid
 *
 *	Returns:
 *		The minimum life Brian needs in order to paint his message
 */
int opt(int min, int x, int y, int N, vector <vector <string> > G)	{

	// Let curr be the current value of the cell
	int curr = stoi(G[x][y]);

	// If we've reached the bottom right corner,
	// simply output it's value
	if ((x == (N - 1)) && (y == (N - 1))){
		return curr;
	} else {

		// Initialize the minimum value of Brian's health needed to traverse
		// from G[x,y] to the end
		int bottom = 0;
		int right = 0;

		// Update bottom and the right based on the value if they were picked
		// summed with the optimal value of getting to the current index
		if (x != (N - 1))
			bottom = opt(x + 1, y, N, G);
		if (y != (N - 1))
			right = opt(x, y + 1, N, G);

		// Check to make sure neither of the paths result in the death of Brian
		// and if they do, make them the max value so the other will be smaller
		if (bottom < 1)
			bottom = numeric_limits<int>::max();
		if (right < 1)
			right = numeric_limits<int>::max();

		// Return the minimum of the two values for the optimal path
		// calling index x and y
		return (curr + min(bottom, right));
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
	return opt(1, 0, 0, N, G);
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