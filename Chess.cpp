#include "Chess.h"
#include <iterator>

using std::map;
using std::pair;

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
	// Get a pointer to the first piece
	const Piece* first_piece = _board(start);

	// Get a pointer to the end piece
	const Piece* end_piece = _board(end);

	// Check if first_piece is NULL
	if(first_piece == NULL) {
		return false;
	}

	// Check if first_piece makes a legal move assuming no pieces around
	if(!(first_piece->legal_move_shape(start, end))) {
		return false;
	}
	
	// Check if path is clear

	// Check endpoint 
	
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

	map<pair<char, char>, Piece*> occurences = _board.occ();
	std::pair<char, char> end;
	std::pair<char, char> start;
	// Finds where the king in question is
	for(map<pair<char, char>, Piece*>::const_iterator it = occurences.cbegin(); it != occurences.cend(); ++it) {
		if(it->second->to_ascii() == king) {
			end = it->first;
			break;
		}	
	}
	// Runs through the rest of the map
	for(map<std::pair<char, char>, Piece*>::const_iterator it = occurences.cbegin(); it != occurences.cend(); ++it) {
		// Ensures not the same king again
		if(it->second->to_ascii() != king) {
			start = it->first;
			// If possible move by the piece, check if the path is clear
			if(it->second->legal_move_shape(start, end)) {
				if(it->second->to_ascii() == 'n' || it->second->to_ascii() == 'N') {
					return true;
				} // else if(_board.INSERT_CLEAR_MOVE_HERE) {
				//	return true;
				// }
			}
		}
	}		
	return false;
}

bool Chess::in_mate( bool white ) const
{
	// Checks all of the one space around the king to see if king can move one space away to avoid check. 
	// Maybe move this into King class later?
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
	/*
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
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return false;
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
	// Loading: Must Fix
	return is;
}
