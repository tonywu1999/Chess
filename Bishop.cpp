#include <iostream>
#include "Bishop.h"
#include "Piece.h"

using std::pair;
<<<<<<< HEAD
using std::cout;
using std::endl;
// Checks to make sure that the move entered fits the piece
=======
>>>>>>> 50c9afc7bb4b9a85889a8d1764a26d1719f97a44

bool Bishop::legal_move_shape( pair< char , char > start , pair< char , char > end ) const {
	if(start.first < 'A' || start.first > 'H' ||
			end.first < 'A' || end.first > 'H') {
		// Not a legal move. Too far horizontal off board
		return false;
	}
	if(start.second < '1' || start.second > '8' ||
			end.second < '1' || end.second > '8') {
		// Not a legal move. Too far vertical off board
		return false;
	}
        if(start.first == end.first && start.second == end.second) {
                // Bishop did not move at all
                return false;
        }
	int m = abs(start.first - end.first);
	int n = abs(start.second - end.second);
	if(m == n) {
		// Bishop moves in a diagonal direction
		return true;
	}
	else {
		// Bishop does not move in a diagnoal direction
		return false;
	}
}


