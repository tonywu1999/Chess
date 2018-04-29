#include <iostream>
#include <utility>
#include <map>
#include <vector>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Piece.h"
#include <algorithm>
#include <string>

using std::cout;
using std::endl;
using std::map;
using std::vector;
using std::pair;
using std::find;
using std::make_pair;
using std::string;

// DO NOT MODIFY THIS FUNCTION!!!! //
Board::Board( void ){}

const Piece* Board::operator()( pair< char , char > position ) const
{		
	if(_occ.find(position) != _occ.end()) {
		// This position is occupied by a piece
		Piece* my_pointer = (_occ.find(position))->second;
		return my_pointer;
	}
	return NULL;
}




bool Board::add_piece( pair< char , char > position , char piece_designator )
{
	
	if(_occ.find(position) != _occ.end()) {
		// Piece already exists
		return false;
	}
	if(position.first < 'A' || position.first > 'H') {
		// Wrong Letter
		return false;
	}
	if(position.second < '1' || position.second > '8') {
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
// Checks path is clear, does not check if the 
// Returns true if path is clear
// Returns true if not moving in a line
bool Board::path_is_clear(std::pair<char, char> start, std::pair<char, char> end) {
	char h_move = end.first - start.first;
	char v_move = end.second - start.second;
	// For counting reasons
	int h_abs = std::abs(h_move) - 1;
	int v_abs = std::abs(v_move) - 1;

	pair<char, char> cur_pt = start;
	
	string dir;
	// Checks vertical movement
	if(h_move == 0) {
		if(v_move > 0) {
			for(int i = 0; i < v_abs; i++) {
				cur_pt.second += 1;
				if(_occ.find(cur_pt) != _occ.end()) {
					return false;
				}
			}
		} 
		else {
			for(int i = 0; i < v_abs; i++) {
				cur_pt.second -= 1;
				if(_occ.find(cur_pt) != _occ.end()) {
					return false;
				}
			}
		}
		return true;
	}

	// Checks horizontal movement
	if(v_move == 0) {
		if(h_move > 0) {
			for(int i = 0; i < h_abs; i++) {
				cur_pt.first += 1;
				if(_occ.find(cur_pt) != _occ.end()) {
					return false;
				}
			}	
		} else {
			for(int i = 0; i < h_abs; i++) {
				cur_pt.first -= 1;
				if(_occ.find(cur_pt) != _occ.end()) {
					return false;
				}
			}

		}
		return true;
	}
	if(h_move > 0) {
		if(v_move > 0) {
			dir = "ne";
		} else {
			dir = "se";
		}
	} else {
		if(v_move > 0) {
			dir = "nw";
		} else {
			dir = "sw";
		}
	}
	// Checks for diagonal movement
	if(dir == "ne") {
		for(int i = 0; i < h_abs; i++) {
			cur_pt.first += 1;
			cur_pt.second += 1;
			if(_occ.find(cur_pt) != _occ.end()) {
				return false;
			}
		}
		return true;
	}	
	else if(dir == "nw") {
		for(int i = 0; i < h_abs; i++) {
			cur_pt.first -= 1;
			cur_pt.second += 1;
			if(_occ.find(cur_pt) != _occ.end()) {
				return false;
			}
		}
		return true;	
	}
	else if(dir == "se") {
		for(int i = 0; i < h_abs; i++) {
			cur_pt.first += 1;
			cur_pt.second -= 1;
			if(_occ.find(cur_pt) != _occ.end()) {
				return false;
			}
		}
		return true;	
	}
	else if(dir == "sw") {
		for(int i = 0; i < h_abs; i++) {
			cur_pt.first -= 1;
			cur_pt.second -= 1;
			if(_occ.find(cur_pt) != _occ.end()) {
				return false;
			}
		}
		return true;
	}
	// Checks for non-line shape
	if(h_move != 0 && v_move != 0 && h_move != v_move) {
		return true;
	}
	return false;
}	

// Checks end position piece to see if it is empty or if it is the same color as the piece
// Adds piece to end location if true
// Returns false if same piece
bool Board::check_end_location(pair<char, char> start, pair<char, char> end) {
	// Movement for pawn
	if((_occ[start]->to_ascii() == 'P') || (_occ[start]->to_ascii() == 'p')) {
		if(abs(start.first - end.first) == 1 && abs(start.second - end.second) == 1) {
			// Pawn tries to move diagonally but there is no piece there
			if(_occ.find(end) == _occ.end()) {
				return false;
			}
			// Pawn tries to move diagnoally and there is a piece there
			else {
				return true;
			}
		}
		else if(abs(start.second - end.second) == 1) {
			// Pawn tries to move vertically but piece is there
			if(_occ.find(end) != _occ.end()) {
				return false;
			}
			// Pawn tries to move vertically and space is empty
			else {
				return true;
			}	
		}
	}
	// End spot is empty, piece is able to move to spot
        if(_occ.find(end) == _occ.end()) {
                return true;
        }
        // Piece tries capturing piece of same color
        if(abs(_occ[start]->to_ascii() - _occ[end]->to_ascii()) < 26) {
                return false;
        }
        // Piece tries capturing piece of different color
        else {
                return true;
        }
}

void Board::execute_move(pair<char, char> start, pair<char, char> end) {
	if((_occ[start]->to_ascii() == 'P') || (_occ[start]->to_ascii() == 'p')) {
		if(end.second == '8') {
		 	_occ.erase(start);
			_occ.erase(end);
			add_piece(end, 'Q');
		}
		else if(end.second == '1') {
			_occ.erase(start);
			_occ.erase(end);
			add_piece(end, 'q');
		}
		else {
			_occ[end] = _occ[start];
			_occ.erase(start);
		}
		return;
	}
	_occ[end] = _occ[start];
	_occ.erase(start);
}


// Loops through map to see if there's either 'K' or 'k'
// If there's one each, return true, else return false
bool Board::has_valid_kings( void ) const
{
	int black_king = 0;
	int white_king = 0;
	for(map<pair<char, char>, Piece*>::const_iterator it = _occ.cbegin();
			it != _occ.cend(); ++it) {
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
			const Piece* piece = board( pair< char , char >( c , r ) );
			if( piece ) os << piece->to_ascii();
			else        os << '-';
		}
		os << std::endl;
	}
	return os;
}
