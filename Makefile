CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)


chess: main.o Board.o Chess.o CreatePiece.o
	$(CC) -o chess main.o Board.o Chess.o CreatePiece.o

#Board.o: Board.cpp Bishop.h Board.h King.h Knight.h Mystery.h Pawn.h Piece.h CreatePiece.h Queen.h Rook.h Terminal.h
#	$(CC) -c Board.cpp $(CFLAGS)


#Chess.o: Chess.cpp Board.h Chess.h Piece.h
#	$(CC) -c Chess.cpp $(CFLAGS)

#CreatePiece.o: CreatePiece.cpp Bishop.h Board.h Chess.h King.h Knight.h Mystery.h Pawn.h Piece.h CreatePiece.h Queen.h Rook.h
#	$(CC) -c CreatePiece.cpp $(CFLAGS)

Chess.o: Chess.cpp Board.cpp Chess.h Piece.h
	$(CC) -c Chess.cpp $(CFLAGS)

CreatePiece.o: CreatePiece.cpp Bishop.cpp Board.cpp Chess.cpp King.cpp Knight.cpp Mystery.h Pawn.cpp Piece.h CreatePiece.h Queen.cpp Rook.cpp
	$(CC) -c CreatePiece.cpp $(CFLAGS)

main.o: main.cpp Bishop.h Board.h Chess.h King.h Knight.h Mystery.h Pawn.h Piece.h CreatePiece.h Queen.h Rook.h
	$(CC) -c main.cpp $(CFLAGS)

Board.o: Board.cpp Bishop.cpp Board.h King.cpp Knight.cpp Mystery.h Pawn.cpp Piece.h CreatePiece.h Queen.cpp Rook.cpp Terminal.h
	$(CC) -c Board.cpp $(CFLAGS)

Queen.o: Queen.cpp Queen.h Piece.h
	$(CC) -c Queen.cpp $(CFLAGS)

Bishop.o: Bishop.cpp Bishop.h Piece.h
	$(CC) -c Bishop.cpp $(CFLAGS)

Knight.o: Knight.cpp Knight.h Piece.h
	$(CC) -c Knight.cpp $(CFLAGS)

Pawn.o: Pawn.cpp Pawn.h Piece.h
	$(CC) -c Pawn.cpp $(CFLAGS)

King.o: King.cpp King.h Piece.h
	$(CC) -c King.cpp $(CFLAGS)

Rook.o: Rook.cpp Rook.h Piece.h
	$(CC) -c Rook.cpp $(CFLAGS)

.PHONY: clean all
clean:
	rm -f *.o chess
