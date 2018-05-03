#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <map>
#include "Piece.h"
#include "Pawn.h"
#include "Mystery.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"


class Board
{
	// Throughout, we will be accessing board positions using an std::pair< char , char >.
	// The assumption is that the first value is the row with values in {'A','B','C','D','E','F','G','H'} (all caps)
	// and the second is the column, with values in {'1','2','3','4','5','6','7','8'}

public:
	// Default constructor
	Board( void );

	// Copy Constructor
	Board( const Board& b); 

	~Board();
	// Returns a const pointer to the piece at a prescribed location if it exists, or a NULL pointer if there is nothing there.
	const Piece* operator() ( std::pair< char , char > position ) const;

	// Returns a non_const pointer to the piece at a prescribed location
	Piece* get_piece_pointer ( std::pair< char, char > position ) const;
	
	// Returns a reference to the occurences of the pieces
	const std::map<std::pair<char, char>, Piece*>& occ( void ) const { return _occ; }	

	// Finds if the path is clear
	bool path_is_clear(std::pair<char, char> start, std::pair<char, char> end) const;

	// Attempts to add a new piece with the specified designator, at the given location.
	// Returns false if:
	// -- the designator is invalid,
	// -- the specified location is not on the board, or
	// -- if the specified location is occupied
	bool add_piece( std::pair< char , char > position , char piece_designator );

	// Checks end position piece to see if it is empty or if it is the same color as the piece
	// Returns false if same piece	
	bool check_end_location(std::pair<char, char> start, std::pair<char, char> end) const;
	
	// Adds piece to end location
	void execute_move(std::pair<char, char> start, std::pair<char, char> end);
	
	void reverse_execute(std::pair<char, char> start, 
		std::pair<char, char> end, Piece* first_piece, Piece* end_piece);	
	
	// Displays the board by printing it to stdout
	void display( void ) const;

	// Returns true if the board has the right number of kings on it
	bool has_valid_kings( void ) const;

	void clear_board() { _occ.clear(); }
	
	// Overwrites the board operator to deep copy a board
	Board& operator=(const Board& b);

private:
	// The sparse map storing the pieces, keyed off locations
	std::map< std::pair< char , char > , Piece* > _occ;
};

// Write the board state to an output stream
std::ostream& operator << ( std::ostream& os , const Board& board );

#endif // BOARD_H
