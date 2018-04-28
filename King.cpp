#include "Piece.h"
#include "King.h"

using std::pair;

bool King::legal_move_shape(pair< char , char > start , pair< char , char > end ) const {
	if(start.first < 'A' || start.first > 'H' ||
                        end.first < 'A' || end.first > 'H') {
                // Not a legal move. Too far horizotal off board
                return false;
        }
        if(start.second < '1' || start.second > '8' ||
                        end.second < '1' || end.second > '8') {
                // Not a legal move. Too far vertical off board
                return false;
        }
	// Finds the movement of the piece
	char h_move = start.first - end.first;
	char v_move = start.second - end.second;
	// Checks to make sure that the piece moved
	if(h_move == 0 && v_move == 0) {
		return false;
	}
	// Checks to see that it has only moved one spot
	if(h_move >= -1 && h_move <= 1) {
		if(v_move >= -1 && v_move <= 1) {
			return true;
		}
	}
	return false;
}
