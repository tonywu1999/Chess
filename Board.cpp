#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"


/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
Board::Board( void ){}

const Piece* Board::operator()( std::pair< char , char > position ) const
{
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return NULL;
}

bool Board::add_piece( std::pair< char , char > position , char piece_designator )
{
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	_occ[ position ] = create_piece( piece_designator );
	return true;
}

bool Board::has_valid_kings( void ) const
{
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
	return true;
}

void Board::display( void ) const
{
	/////////////////////////
	// [REPLACE THIS STUB] //
	/////////////////////////
}

/////////////////////////////////////
// DO NOT MODIFY THIS FUNCTION!!!! //
/////////////////////////////////////
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