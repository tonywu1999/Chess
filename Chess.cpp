#include "Chess.h"
#include <iterator>
#include <cctype>

using std::map;
using std::pair;
using std::make_pair;

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Chess::Chess( void ) : _turn_white( true )
{
	// Add the pawns
	for( int i=0 ; i<8 ; i++ )
	{
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+1 ) , 'P' );
		_board.add_piece( std::pair< char , char >( 'A'+i , '1'+6 ) , 'p' );
	}

	// Add the rooks
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+0 ) , 'R' );
	_board.add_piece( std::pair< char , char >( 'A'+0 , '1'+7 ) , 'r' );
	_board.add_piece( std::pair< char , char >( 'A'+7 , '1'+7 ) , 'r' );

	// Add the knights
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+0 ) , 'N' );
	_board.add_piece( std::pair< char , char >( 'A'+1 , '1'+7 ) , 'n' );
	_board.add_piece( std::pair< char , char >( 'A'+6 , '1'+7 ) , 'n' );

	// Add the bishops
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+0 ) , 'B' );
	_board.add_piece( std::pair< char , char >( 'A'+2 , '1'+7 ) , 'b' );
	_board.add_piece( std::pair< char , char >( 'A'+5 , '1'+7 ) , 'b' );

	// Add the kings and queens
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+0 ) , 'Q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+0 ) , 'K' );
	_board.add_piece( std::pair< char , char >( 'A'+3 , '1'+7 ) , 'q' );
	_board.add_piece( std::pair< char , char >( 'A'+4 , '1'+7 ) , 'k' );
}

bool Chess::make_move( std::pair< char , char > start , std::pair< char , char > end )
{
	// Get const pointers to the first and end piece
	const Piece* first_piece = _board(start);


	// Check if first_piece is NULL
	if(first_piece == NULL) {
		// Starting piece is NULL
		return false;
	}

	if(first_piece->is_white() != _turn_white) {
		// Wrong Color
		return false;
	}

	// Check if first_piece makes a legal move assuming no pieces around
	if(!(first_piece->legal_move_shape(start, end))) {
		// Not a legal move shape
		return false;
	}
	
	// Check if path is clear
	if(!(_board.path_is_clear(start,end))) {
		// Path is NOT clear
		return false;
	}

	// Check endpoint 
	if(!(_board.check_end_location(start, end))) {
		// Cannot place piece at end location
		return false;
	}
	
	// Execute Move on Board Copy
	Board b = _board;
	b.execute_move(start, end);

	// Check if board is in check now
	if(in_p_check(_turn_white, b)) {
		// Move would result in your king in check
		return false;
	}
	
	// Execute Move
	_board.execute_move(start,end);
	
	// Change color of player:
	if(_turn_white) {
		_turn_white = false;
	}
	else {
		_turn_white = true;
	}	
	return true;
}

bool Chess::in_p_check( bool white, const Board& b ) const
{
	char king;
	if( white ) {
		king = 'K';
	} else {
		king = 'k';
	}

	pair<char, char> start;
	pair<char, char> end;
	// Finds where the king in question is
	for(map<pair<char, char>, Piece*>::const_iterator it = b.occ().cbegin(); it != b.occ().cend(); ++it) {
		if(it->second->to_ascii() == king) {
			end = it->first;
			break;
		}	
	}

	// Runs through the rest of the map
	for(map<pair<char, char>, Piece*>::const_iterator it = b.occ().cbegin(); it != b.occ().cend(); ++it) {
		// Make sure piece is opposite color to continue for check
		if(white != (it->second)->is_white()) {
			start = it->first;
			// If possible move by the piece, check if the path is clear
			if(it->second->legal_move_shape(start, end)) {
				if(b.path_is_clear(start, end)) {
					if(b.check_end_location(start, end)) {
						return true;
					}	
				} 
			}
		}
	}	
	return false;
}


bool Chess::in_check( bool white ) const
{
	if(in_p_check(white, _board)) {
		return true;
	}
	return false;
}

bool Chess::in_mate( bool white ) const
{

	// King is not in check, return false
	if(!in_check(white)) {
		return false;	
	}
	pair<char, char> end = std::make_pair('A','1');
	pair<char, char> start;
	
	// Logic Check: Mate = no possible move for anything 
	for(map<pair<char, char>, Piece*>::const_iterator it = _board.occ().cbegin(); it != _board.occ().cend(); ++it) {
		// Checks to make sure that the new piece is the same color
		if(white == it->second->is_white()) {
			start = it->first;
			// Loop through whole 8x8 board to iterate through possible end locations
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					// Check if path is legal, clear, and end location is valid
					if(it->second->legal_move_shape(start, end)) {
						if(_board.path_is_clear(start,end)) {
							if(_board.check_end_location(start, end)) {
								// CHECK TO MAKE SURE THAT THE NEW BOARD STILL RETAINS CHECK
								Board b = _board;
								b.execute_move(start, end);
								if(!in_p_check(white, b)) {
									// If new board not in check, then it is possible to escape check
									return false;
								}
							}
						}
					}
					end.second++;
				}
				end.first++;
				end.second = '1';
			}
			end.first = 'A';
		}
	}

	// No possible moves can be made without getting king in check
	return true;
}


bool Chess::in_stalemate( bool white ) const
{
	
        pair<char, char> start;
        pair<char, char> end;
	
        // Runs through the 8x8 chess board
        for(char i = 'A'; i <= 'H'; i++) {
                for(char j = '1'; j <= '8'; j++) {
                        end = make_pair(i, j);
			// Runs through map of chess pieces on the board
                        for(map<pair<char, char>, Piece*>::const_iterator it =_board.occ().cbegin();
                                        it!= _board.occ().cend(); ++it) {
				// Make sure piece that we check is a piece the current player owns
				if(white == (it->second)->is_white()) {
                                       	start = it->first;
					// Ensure hypothetical path is legal, clear, and end location is valid
					if(it->second->legal_move_shape(start, end)) {
						if(_board.path_is_clear(start, end)) {
							if(_board.check_end_location(start, end)) {                                                        		
								// CHECK TO MAKE SURE THAT THE NEW BOARD STILL RETAINS CHECK
        							Board b = _board;
								b.execute_move(start, end);	
								if(!in_p_check(white, b)) {
									// New board not in check, so there is a move to not have board in stalemate
									return false;
								}
							}
						}
                                        }
                                }
                        }
                }
        }

	// No possible moves can be made without getting king in check
	return true;

}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
std::ostream& operator << ( std::ostream& os , const Chess& chess )
{
	// Write the board out and then either the character 'w' or the character 'b', depending on whose turn it is
	return os << chess.board() << ( chess.turn_white() ? 'w' : 'b' );
}

std::istream& operator >> ( std::istream& is , Chess& chess )
{
	// Clear the map of _board contained in chess
	// clear_board() is a method in the Board class
	chess._board.clear_board();
	
	char piece;
	for(char number = '8'; number >= '1'; number--) {
		for(char letter = 'A'; letter <= 'H'; letter++) {
			is >> piece;
			if(piece != '-') {
				chess._board.add_piece(pair< char , char >( letter , number ) , piece );
			}
		}
	}
	// After 64 characters are read, this last reading
	// reads the last character which determines if the board
	// is at white or black's turn
	is >> piece;
	chess.set_turn_white(piece);
	return is;
}
