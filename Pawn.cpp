#include <iostream>
#include "Pawn.h"
#include "Piece.h"
#include <cmath>

using std::cout;
using std::endl;
using std::pair;
using std::abs;

// Checks to make sure that the move entered fits the piece
bool Pawn::legal_move_shape( pair< char , char > start , pair< char , char > end ) const {
        if(start.first < 'A' || start.first > 'H' ||
                        end.first < 'A' || end.first > 'H') {
                // Not a legal move. Too far horizontal off board
                return false;
        }
        if(start.second < '1' || start.second > '8' ||
                        end.second < '1' || end.second > '8') {
                // Not a legal move.  Too far vertical off board
                return false;
        }
        if(start.first == end.first && start.second == end.second) {
                // Pawn did not move at all
		return false;
        }
	if(is_white() == true) {
		// White pawn
		if(start.second == '2') {
			if((end.second - start.second) != 2 && 
					(end.second - start.second) != 1) {
				// Pawn does not move forward two spaces from start position
				return false;
			}
			if((end.second - start.second) == 2 && end.first != start.first) {
				// Pawn cannot move forward two spaces + horizontal too
				return false;
			}
			if(abs(end.first-start.first) != 1 && abs(end.first-start.first) != 0) {
				// Horizontal movement not 1 or 0
				return false;
			}
			return true;
		}
		else {
			if((end.second - start.second) != 1) {
				// Pawn does not move forward one space
				return false;
			}
			if(abs(end.first-start.first) != 1 && abs(end.first-start.first) != 0) {
				// Horizontal movement not 1 or 0
				return false;
			}
			return true;
		}
	}
	else {
		// Black pawn
                if(start.second == '7') {
                        if((start.second - end.second) != 2 && 
					(start.second - end.second) != 1) {
                                // Pawn does not move forward two spaces from start position
                                return false;
                        }
			if((start.second - end.second) == 2 && end.first != start.first) {
				// Pawn cannot move forward two spaces + horizontal too
				return false;
			}
			if(abs(end.first-start.first) != 1 && abs(end.first-start.first) != 0) {
				// Horizontal movement not 1 or 0
				return false;
			}
                        return true;
                }
                else {
                        if((start.second - end.second) != 1) {
                                // Pawn does not move forward one space
                                return false;
                        }
			if(abs(end.first-start.first) != 1 && abs(end.first-start.first) != 0) {
				// Horizontal movement not 1 or 0
				return false;
			}
                        return true;
                }
        }
}
