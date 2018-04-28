#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece
{
public:
	bool legal_move_shape( std::pair< char , char > start , std::pair< char , char > end ) const;	
	
	bool legal_capture_shape( std::pair< char , char > start , std::pair< char , char > end ) const {
                return legal_move_shape(start, end);
        }

        ~Knight() { }
	
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	char to_ascii( void ) const { return is_white() ? 'N' : 'n'; }

private:
	/////////////////////////////////////
	// DO NOT MODIFY THIS FUNCTION!!!! //
	/////////////////////////////////////
	Knight( bool is_white ) : Piece( is_white ) {}

	friend Piece* create_piece( char );
};

#endif // KNIGHT_H
