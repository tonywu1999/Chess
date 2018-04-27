#include <iostream>
#include "Rook.h"
#include "Board.h"
#include "Piece.h"

using std::pair;
using std::cout;
using std::endl;


bool Rook::legal_move_shape( pair< char , char > start , pair< char , char > end ) const {	
	
	if(start.first < 'A' || start.first > 'H' || 
			end.first < 'A' || end.first > 'H') {
		// Not Legal Move. Too far horizontal off board
		return false;
	}
	if(start.second < '1' || start.second > '8' || 
                        end.second < '1' || end.first > '8') {
		// Not Legal Move.  Too far vertical off board
		return false;
	}
	if(start.first != end.first && start.second != end.second) {
		// Rook did not move in a straight line
		return false;
	}
	if(start.first == end.first && start.second == end.second) {
		// Rook did not move at all
		return false;
	}
	// Scenario 1: Rook moves vertically
	if(start.first != end.first) {
		
	}
	// Scenario 2: Rook moves horizontally
	else {

	}
	
	return true;

}

bool Rook::legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end) const {
	
	return false;

}
