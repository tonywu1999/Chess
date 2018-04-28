#include <iostream>
#include "Queen.h"
#include "Piece.h"

using std::pair;

bool Queen::legal_move_shape( pair< char , char > start , pair< char , char > end ) const {
	if(start.first < 'A' || start.first > 'H' ||
                        end.first < 'A' || end.first > 'H') {
                // Not a legal move. Too far horizotal off board
                return false;
        }
        if(start.second < '1' || start.second > '8' ||
                        end.second < '1' || end.first > '8') {
                // Not a legal move. Too far vertical off board
                return false;
        }
        if(start.first == end.first && start.second == end.second) {
                // Queen did not move at all
                return false;
        }
        int m = abs(start.first - end.first);
        int n = abs(start.second - end.second);
        if(abs(m/n) == 1) {
                // Queen moves in a diagonal direction
                return true;
        }
        else if(start.first == end.first && start.second != end.second) {
		// Queen moves horizontally
		return true;
	}
	else if(start.first != end.first && start.second == end.second) {
		// Queen moves vertically
		return true;
	}
	else {
		// Queen does not move in a valid way
		return false;
	}	
}

