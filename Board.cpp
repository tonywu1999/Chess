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
	int h_move = start.first - end.first;
	int v_move = start.second - end.second;
	// For counting reasons
	int h_abs = std::abs(h_move) - 1;
	int v_abs = std::abs(v_move) - 1;

	pair<char, char> cur_pt = start;
	
	string dir;
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
	// Checks vertical movement
	if(h_move == 0) {
		if(v_move > 0) {
			for(int i = 0; i < v_abs; i++) {
				cur_pt.second += 1;
				if(_occ.find(cur_pt) != _occ.end()) {
					return false;
				}
			}
		} else {
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
