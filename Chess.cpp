#include "Chess.h"
#include <iterator>
#include <cctype>

using std::map;
using std::pair;
using std::endl;
using std::cout;

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
	// const Piece* end_piece = _board(end);

	// Get non-const pointers to the first and end piece
	Piece* first = _board.get_piece_pointer(start);
	Piece* last = _board.get_piece_pointer(end);

	// Check if first_piece is NULL
	if(first_piece == NULL) {
		cout << "Starting piece is NULL" << endl;
		return false;
	}

	if(first_piece->is_white() != _turn_white) {
		cout << "Wrong Color" << endl;
		return false;
	}

	// Check if first_piece makes a legal move assuming no pieces around
	if(!(first_piece->legal_move_shape(start, end))) {
		cout << "Not a legal move shape" << endl;
		return false;
	}
	
	// Check if path is clear
	if(!(_board.path_is_clear(start,end))) {
		cout << "Path is NOT clear" << endl;
		return false;
	}

	// Check endpoint 
	if(!(_board.check_end_location(start, end))) {
		cout << "Cannot place piece at end location" << endl;
		return false;
	}
	
	// Execute Move
	_board.execute_move(start, end);

	// Check if board is in check now
	if(in_check(_turn_white)) {
		cout << "Move would result in your king in check" << endl;
		_board.reverse_execute(start, end, first, last);
		return false;
	}

	// Change color of player:
	if(_turn_white) {
		_turn_white = false;
	}
	else {
		_turn_white = true;
	}	
	return true;
}
bool Chess::in_check( bool white ) const
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
	for(map<pair<char, char>, Piece*>::const_iterator it = _board.occ().cbegin(); it != _board.occ().cend(); ++it) {
		if(it->second->to_ascii() == king) {
			end = it->first;
			break;
		}	
	}
	// Runs through the rest of the map
	for(map<pair<char, char>, Piece*>::const_iterator it = _board.occ().cbegin(); it != _board.occ().cend(); ++it) {
		// Ensures not the same king again
		if(it->second->to_ascii() != king) {
			start = it->first;
			// Make sure piece is opposite color to continue for check
			if(white != (it->second)->is_white()) {
				// If possible move by the piece, check if the path is clear
				if(it->second->legal_move_shape(start, end)) {
					if(_board.path_is_clear(start, end)) {
						if(_board.check_end_location(start, end)) {
							return true;
						}
					}	
				} 
			}
		}
	}	
	return false;
}

bool Chess::in_mate( bool white ) const
{
	// King is not in check, return false
	if(!in_check(white)) {
		return false;	
	}
	// Checks all of the one space around the king to see if king can move one space away to avoid check. 
	/*
	char king;
	if( white ) {
		king = 'K';
	} else {
		king = 'k';
	}
	std::pair<char, char> start;
	map<pair<char, char>, Piece*> occurences = _board.occ();
	// Finds where the king in question is
	for(map<pair<char, char>, Piece*>::const_iterator it = occurences.cbegin(); it != occurences.cend(); ++it) {
		if(it->second->to_ascii() == king) {
			start = it->first;
		}
	}
	int h_move = -1;
	int v_move = -1;
	// Check spaces around the king
	
	for(h_move) {

	}
	if(true) {

	}
	*/
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
}

bool Chess::in_stalemate( bool white ) const
{
	char king;
        if( white ) {
                king = 'K';
        } else {
                king = 'k';
        }

	pair<char, char> start;
	pair<char, char> end;

	// Runs through the map
	for(map<pair<char, char>, Piece*>::const_iterator it = _board.occ().cbegin(); 
			it!= _board.occ().cend(); ++it) {
		if(it->second->to_ascii() != king) {
			start = it->first;
			if(white == (it->second)->is_white()) {
				if(it->second->legal_move_shape(start, end)) {
					return false;
				}			
				else if(_board.path_is_clear(start, end)) {
                                	return false;
				}
				if(_board.check_end_location(start, end)) {
                        		return false;
				}
				return true;		
			}
		}
	}
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

	// Erase the _occ board map:
	chess.board2().clear_board();
	
	char piece;
	char number = '8';
	while (number > '0') {
		char letter = 'A';
		while(letter <= 'H') {
			is >> piece;
			if(piece != '-') {
				// I think board() is const	
				chess.board2().add_piece(pair< char , char >( letter , number ) , piece );
			}
			letter = letter + 1;
				
		}
		number = number - 1;
		// is >> piece; // Reads new line character
	}
	is >> piece;
	chess.set_turn_white(piece);
	return is;
}
