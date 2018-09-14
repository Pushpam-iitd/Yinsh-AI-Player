

#ifndef BOARD_H
#define	BOARD_H

#include<iostream>
#include<fstream>
using namespace std;

class Point{
	int x;
	int y;
	public:
	int getx();
	int gety();
	void setx(int x1);
	void sety(int y1);
	void set(int x1,int y1);
	string getxystring();
} ;


Point twod_from_hex (Point p);
	
Point hex_from_twod (Point p);

class Board{
	public:
	int boardsize = 11;
	int mynumberOfRings;
	int opponentnumberOfRings;
	//double 
	int boardArray [11] [11];
    bool validArray [11] [11];

	/**
     * Constructor : Creates the empty board with default size corresponding to 5 rings
     * 
     */
	Board();

	/**
     * Constructor : Creates the empty board with default size corresponding to 5 rings
     * 
     */

	Board( int boardsize);

	Point twod_from_hex (Point p);
	
	Point hex_from_twod (Point p);

	/**
     * to set the position of a ring on the board.
     * 
     */
	/**
     * -1 :  empty , 0 : whitering , 1 :blackring , 2 : whitemarker , 3 : blackmarker  
     * 
     */


	void setRing(int ringcolor,int px, int py);

	/**
     * to move the position of a ring on the board, and set the board accordingly.
     * 
     */
	void moveRing(int ringcolor, int from_x,int from_y, int to_x,int to_y);

	/**
     * to remove a ring from the board, and set the board accordingly.
     * 
     */
 	void removeRing(int opponentID );
	
	/**
     * to calculate the evaluation function.
     * 
     */
	float evaluate();

	void getNeighbours(int px,int py, int ringcolor);



}
;


#endif	/* BOARD_H */


