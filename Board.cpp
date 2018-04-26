#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"


// DO NOT MODIFY THIS FUNCTION!!!! //
Board::Board( void ){}

const Piece* Board::operator()( std::pair< char , char > position ) const
{		
	if(_occ.find(position) != _occ.end()) {
		// This position is occupied by a piece
		Piece* my_pointer = (_occ.find(position))->second;
		return my_pointer;
	}
	return NULL;
}

bool Board::add_piece( std::pair< char , char > position , char piece_designator )
{
	
	if(_occ.find(position) != _occ.end()) {
		// Piece already exists
		return false;
	}
	if(position.first < 'A' || position.first > 'H') {
		// Wrong Letter
		return false;
	}
	if(position.second < 1 || position.second > 8) {
		// Wrong Number
		return false;
	}
	vector<char> pieces = {'k', 'K', 'q', 'Q', 'b', 'B', 'N', 'n', 'R',
		'r', 'p', 'P'};
	vector<char>::iterator it;
	it = find(pieces.begin(), pieces.end(), piece_designator);
	if(it != pieces.end()) {
		// Piece designator is found
	}
	else {
		// Piece designator not found
		return false;
	}
	_occ[ position ] = create_piece( piece_designator );
	return true;
}

// Loops through map to see if there's either 'K' or 'k'
// If there's one each, return true, else return false
bool Board::has_valid_kings( void ) const
{
	int black_king = 0;
	int white_king = 0;
	for(map<pair<char, char>, Piece*>::iterator it = _occ.begin();
			it != _occ.end(); ++it) {
		if((it->second)->to_ascii() == 'K') {
			white_king = white_king + 1;
		}
		else if((it->second)->to_ascii() == 'k') {
			black_king = black_king + 1;
		}
	}
	if(black_king == 1 && white_king == 1) {
		return true;
	}
	else {
		return false;

	}
}

void Board::display( void ) const
{
	// Display the board
	cout << *this << endl;
	
}

// DO NOT MODIFY THIS FUNCTION!!!! //
std::ostream& operator << ( std::ostream& os , const Board& board )
{
	for( char r='8' ; r>='1' ; r-- )
	{
		for( char c='A' ; c<='H' ; c++ )
		{
			const Piece* piece = board( std::pair< char , char >( c , r ) );
			if( piece ) os << piece->to_ascii();
			else        os << '-';
		}
		os << std::endl;
	}
	return os;
}
