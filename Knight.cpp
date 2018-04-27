#include <iostream>
#include "Knight.h"
#include "Piece.h"

using std::pair;

bool Knight::legal_move_shape( pair< char , char > start , pair< char , char > end ) const
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
                // Knight did not move at all
                return false;
        }

	int m = abs(start.first - end.first);
	int n = abs(start.second - end.first);
	if(m = 2 && n = 1) {
		// Knight moves more left or right than up or down
		return true;
	}
	else if(m = 1 && n = 2) {
		// Knight moves more up or down than left or right
		return true;
	}
	else {
		return false;
	}
}
