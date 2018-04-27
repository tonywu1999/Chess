#include <iostream>
#include "Pawn.h"
#include "Piece.h"

using std::pair;

bool Pawn::legal_move_shape( pair< char , char > start , pair< char , char > end ) const {
        if(start.first < 'A' || start.first > 'H' ||
                        end.first < 'A' || end.first > 'H') {
                // Not a legal move. Too far horizontal off board
                return false;
        }
        if(start.second < '1' || start.second > '8' ||
                        end.second < '1' || end.first > '8') {
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
			if((end.first - start.first) != 2) {
				// Pawn does not move forward two spaces from start position
				return false;
			}
			else {
				return true;
			}
		}
		else {
			if((end.first - start.first) != 1) {
				// Pawn does not move forward two spaces from start position
				return false;
			}
			else {
				return true;
			}
		}
	}
	else {
		// Black pawn
                if(start.second == '7') {
                        if((start.first - end.first) != 2) {
                                // Pawn does not move forward two spaces from start position
                                return false;
                        }
                        else {
                                return true;
                        }
                }
                else {
                        if((start.first - end.first) != 1) {
                                // Pawn does not move forward two spaces from start position
                                return false;
                        }
                        else {
                                return true;
                        }
                }
        }
}
