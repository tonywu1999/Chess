#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece
{
public:
	bool legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const
	{
		/////////////////////////
		// [REPLACE THIS STUB] //
		/////////////////////////
		return false;
	}

	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii( void ) const { return is_white() ? 'B' : 'b'; }

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Bishop( bool is_white ) : Piece( is_white ) {}

	friend Piece* create_piece( char );
};

#endif // BISHOP_H
