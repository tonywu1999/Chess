#include "Board.h"
#include "Piece.h"
#include "King.h"

using std::pair;

bool King::legal_move_shape(pair< char , char > start , pair< char , char > end, Board& b ) const {
	// Finds the movement of the piece
	h_move = start.first - end.first;
	v_move = start.second - end.second;
	// Checks to make sure that the piece moved
	if(h_move == 0 && v_move == 0) {
		return false;
	}
	// Checks to see that it has only moved one spot
	if(h_move >= -1 && h_move <= 1) {
		if(v_move >= -1 && v_move <= 1) {
			return true;
			// Piece* check = b(end);
			// if( check ) {
			//	return legal_capture_shape( is_white() , check );
			// }
		}
	}
	return false;
}
/* 
bool King::legal_capture_shape( pair< char, char > start, pair< char, char > end ) const {
	
	if ( legal_move_shape( start, end ) ) {
		

	}

	if( color ) {
		// If color is white and end piece is black
		if( *end >= 'a' && *end <= 'z') { return true; }
	} else {
		// Else color is black and if end piece is white
		if( *end >= 'A' && *end <= 'Z') { return true; }
	}
	// If nothing goes through just return false
	return false;
}
*/
