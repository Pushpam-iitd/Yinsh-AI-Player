#include <stdlib.h>

#include "Board.h"



// class Point{
// 	int x;
// 	int y;
// 	public:
// 	int getx(){
// 		return this.x;
// 	}
// 	int gety(){
// 		return this.x;	
// 	}
// 	void setx(int x1){
// 		this.x = x1;
// 	}
// 	void sety(int y1){
// 		this.y = y1;
// 	}

// }


int Point::getx(){
		return this->x;
	}
int Point::gety(){
		return this->y;	
	}
void Point::setx(int x1){
		this->x = x1;
	}
void Point::sety(int y1){
		this->y = y1;
	}
void Point::set(int x1,int y1){
		this->x = x1; this->y = y1;
	}




Point twod_from_hex (Point p){
		int h = p.getx();  // the hexagon number. center point is hexagon numbered 0.
		int c = p.gety();  // the point clockwise, first being 0.
		Point twod;
		if(c <= h){
			twod.setx(5+c);
			twod.sety(5+h);
		}
		else if(c<=2*h){
			twod.setx(5+h);
			twod.sety(5+2*h-c);
		}
		else if(c<=3*h){
			twod.setx(5+3*h-c);
			twod.sety(5-h+3*h-c);
		}
		else if(c<=4*h){
			twod.setx(5-(c-3*h));
			twod.sety(5-h);
		}
		else if(c<=5*h){
			twod.setx(5-h);
			twod.sety(5-h+c-4*h);
		}
		else{
			twod.setx(5-h+c-5*h);
			twod.sety(5+c-5*h);
		}

		// Point out;
		// out.setx(h);
		// out.sety(c);
		return twod;

}


Point hex_from_twod (Point p){
	int px = p.getx();
	int py = p.gety();
	int h = max(abs(px-5),abs(py-5));  
	int c;

	if(py == 5+h){
		c=px-5;	
	}
	else if(px == 5+h){
		c = 2*h - (py-5);
	}
	else if(py == 5-h){
		c = 3*h + 5-px; 
	}
	else if(px == 5-h ){
		c= 5*h - (5-py);
	}
	else if(px >= 5 && py <= 5){
		c= 3*h - (px-5);
	}
	else if(px <= 5 && py >= 5){
		c= 6*h - (5-px);
	}
	Point out;
	out.setx(h);
	out.sety(c);
	return out;
}



Board::Board ( )
{	

    // int boardArray [11] [11];
    // bool validArray [11] [11];

    // refer to the coordinate system : a,b,c... are represented by the first dimension of the array.
    for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		boardArray[i][j] = -1;
    	}
    }

    for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		validArray[i][j] = false;
    	}
    }



    for(int j =1; j<=4;j++){
    	validArray[0][j] = true;
    }
    for(int j =0; j<=6;j++){
    	validArray[1][j] = true;
    }
    for(int j =0; j<=7;j++){
    	validArray[2][j] = true;
    }
    for(int j =0; j<=8;j++){
    	validArray[3][j] = true;
    }
    for(int j =0; j<=9;j++){
    	validArray[4][j] = true;
    }
    for(int j =1; j<=9;j++){
    	validArray[5][j] = true;
    }
    for(int j =1; j<=10;j++){
    	validArray[6][j] = true;
    }
    for(int j =2; j<=10;j++){
    	validArray[7][j] = true;
    }
    for(int j =3; j<=10;j++){
    	validArray[8][j] = true;
    }
    for(int j =4; j<=10;j++){
    	validArray[9][j] = true;
    }
    for(int j =6; j<=9;j++){
    	validArray[10][j] = true;
    }
}


Board Board::clone(){
	Board newboard;
	for(int i = 0;i<=10;i++){
    	for(int j =0;j<=10;j++){
    		newboard.boardArray[i][j] = this->boardArray[i][j] ;
    		newboard.validArray[i][j] = this->validArray[i][j] ;
    	}
    }
}


void Board::setRing(int ringcolor,int px, int py){

	if(boardArray[px][py] == -1 && validArray[px][py] == true )  
		{	boardArray[px][py] = ringcolor;
			validArray[px][py] = false;       // CHECK THIS !!!!!!!
		}

}


void Board::moveRing(int ringcolor, int from_x, int from_y, int to_x, int to_y){

	// 	ASSUMING THAT THE TO AND FROM COORDINATES ARE VALID.
	boardArray[from_x][from_y] = ringcolor +2;
	boardArray [to_x][to_y] = ringcolor;
	validArray[from_x][from_y] = false;
	validArray[to_x][to_y] = false;

	if(from_x == to_x){
		int miy = from_y,mxy  = to_y;
		if(from_y>to_y){miy = to_y; mxy = from_y;}  
		for(int i = miy+1; i< mxy ;i++){
			if (boardArray[from_x][i] != -1 ) boardArray[from_x][i] = 5-boardArray[from_x][i]; // CHECK THIS IF CONDITION
		}
	}

	else if(from_y == to_y){
		int mix = from_x,mxx  = to_x;
		if(from_x>to_x){mix = to_x; mxx = from_x;}  
		for(int i = mix+1; i< mxx ;i++){
			if (boardArray[i][from_y] != -1 ) boardArray[i][from_y] = 5-boardArray[i][from_y]; 
		}
	}

	else{
		if(from_x < to_x){
		int s = to_x - from_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x+i][from_y+i] != -1 ) boardArray[from_x+i][from_y+i] = 5-boardArray[from_x+i][from_y+i]; 
		}
		}

		else{
		int s =from_x -  to_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x-i][from_y-i] != -1 ) boardArray[from_x-i][from_y-i] = 5-boardArray[from_x-i][from_y-i]; 
		}
		}
	}

}


Point Board::twod_from_hex (Point p){
		int h = p.getx();  // the hexagon number. center point is hexagon numbered 0.
		int c = p.gety();  // the point clockwise, first being 0.
		Point twod;
		if(c <= h){
			twod.setx(5+c);
			twod.sety(5+h);
		}
		else if(c<=2*h){
			twod.setx(5+h);
			twod.sety(5+2*h-c);
		}
		else if(c<=3*h){
			twod.setx(5+3*h-c);
			twod.sety(5-h+3*h-c);
		}
		else if(c<=4*h){
			twod.setx(5-(c-3*h));
			twod.sety(5-h);
		}
		else if(c<=5*h){
			twod.setx(5-h);
			twod.sety(5-h+c-4*h);
		}
		else{
			twod.setx(5-h+c-5*h);
			twod.sety(5+c-5*h);
		}

	// Point out;
	// out.setx(h);
	// out.sety(c);
	return twod;

}


Point Board::hex_from_twod (Point p){
	int px = p.getx();
	int py = p.gety();
	int h = max(abs(px-5),abs(py-5));  
	int c;

	if(py == 5+h){
		c=px-5;	
	}
	else if(px == 5+h){
		c = 2*h - (py-5);
	}
	else if(py == 5-h){
		c = 3*h + 5-px; 
	}
	else if(px == 5-h ){
		c= 5*h - (5-py);
	}
	else if(px >= 5 && py <= 5){
		c= 3*h - (px-5);
	}
	else if(px <= 5 && py >= 5){
		c= 6*h - (5-px);
	}
	Point out;
	out.setx(h);
	out.sety(c);
	return out;
}


vector<Board> Board::getNeighbours(int px,int py, int ringcolor){
		// HAVE TO ADD THE CASE IN WHICH THERE IS -1 IN A DIRECTION SO ALL THE -1 IN THAT LINE
	// CORRESPOND TO NEIGHBOURS. 

	vector <Board> neighbours;
	// in direction 0
	int i=1;int flag =0; Board p0 = this->clone(); 
	while(py+i<=10 && boardArray[px][py+i] == ringcolor+2){
		i++;
		if(boardArray[px][py+i]==0||boardArray[px][py+i]==1) flag=1;
	}
	if(boardArray[px][py+1]==0||boardArray[px][py+1]==1)flag =1;
	if(flag==0){ p0.moveRing(ringcolor,px,py,px,py+i);
				 cout<<"in neighbour function : "<<"i is "<<i;
				 neighbours.push_back(p0);}
		// neighbours.push_back(p0.set(px,py+i));

	// in direction 1
	i=1;flag =0;Board p1 = this->clone(); 
	while(py+i<=10 && px+i<=10 && boardArray[px+i][py+i] == ringcolor+2){
		i++;
		if(boardArray[px+i][py+i]==0||boardArray[px+i][py+i]==1) flag=1;
	}
	if(boardArray[px+1][py+1]==0||boardArray[px+1][py+1]==1)flag =1;
	if(flag==0){ p1.moveRing(ringcolor,px,py,px+i,py+i);
				 neighbours.push_back(p1);}
		// neighbours.push_back(p1.set(px+i,py+i));

	// in direction 2
	i=1;flag =0;Board p2 = this->clone(); 
	while(py-i>=0 && px+i<=10 && boardArray[px+i][py-i] == ringcolor+2){
		i++;
		if(boardArray[px+i][py-i]==0||boardArray[px+i][py-i]==1) flag=1;
	}
	if(boardArray[px+1][py-1]==0||boardArray[px+1][py-1]==1)flag =1;
	if(flag==0) { p2.moveRing(ringcolor,px,py,px+i,py-i);
				  neighbours.push_back(p2);}
		// neighbours.push_back(p2.set(px+i,py-i));

	// in direction 3
	i=1;flag =0; Board p3 = this->clone(); 
	while(py-i<=0 && boardArray[px][py-i] == ringcolor+2){
		i++;
		if(boardArray[px][py-i]==0||boardArray[px][py-i]==1) flag=1;
	}
	if(boardArray[px][py-1]==0||boardArray[px][py-1]==1)flag =1;
	if(flag==0){ p3.moveRing(ringcolor,px,py,px,py-i);
				 neighbours.push_back(p3); }
		// neighbours.push_back(p3.set(px,py-i));

	// in direction 4
	i=1;flag =0;Board p4 = this->clone(); 
	while(py-i>=0 && px-i>=0 && boardArray[px-i][py-i] == ringcolor+2){
		i++;
		if(boardArray[px-i][py-i]==0||boardArray[px-i][py-i]==1) flag=1;
	}
	if(boardArray[px-1][py-1]==0||boardArray[px-1][py-1]==1)flag =1;
	if(flag==0) {p4.moveRing(ringcolor,px,py,px-i,py-i);
				 neighbours.push_back(p4);}
		// neighbours.push_back(p4.set(px-i,py-i));	

	// in direction 5
	i=1;flag =0; Board p5 = this->clone(); 
	while(py+i<=10 && px-i>=0 && boardArray[px-i][py+i] == ringcolor+2){
		i++;
		if(boardArray[px-i][py+i]==0||boardArray[px-i][py+i]==1) flag=1;
	}
	if(boardArray[px-1][py+1]==0||boardArray[px-1][py+1]==1)flag =1;
	if(flag==0){ p5.moveRing(ringcolor,px,py,px-i,py+i);
				 neighbours.push_back(p5);}
		// neighbours.push_back(p5.set(px-i,py+i));	


return neighbours; 
	
}


void removeRing(int opponentID ,int from_x ,int from_y , int to_x ,int  to_y ,int ring_removeX ,int ring_removeY){
	int ringcolor = opponentID;
	int mcolor = ringcolor+2;
	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(boardArray[j][i] == mcolor && boardArray[j][i+1] == mcolor && boardArray[j][i+2] == mcolor && boardArray[j][i+3] == mcolor  
				&& boardArray[j][i+4] == mcolor){
				// do something.
			}
		}
	}

	for(int j = 0; j<11;j++){
		for(int i= 0; i<=6;i++ ){
			if(boardArray[i][j] == mcolor && boardArray[i+1][j] == mcolor && boardArray[i+2][j] == mcolor && boardArray[i+3][j] == mcolor  
				&& boardArray[i+4][j] == mcolor){
				// do something.
			}
		}
	}

	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(boardArray[k+i][i] == mcolor && boardArray[k+i+1][i+1] == mcolor && boardArray[k+i+2][i+2] == mcolor && boardArray[k+i+3][i+3] == mcolor  
				&& boardArray[k+i+4][i+4] == mcolor){
				// do something.
			}
		}  
	}	


	// for line going to up-right in the middle. has to be written
	for (int i=1;i<=5;i++){
		if(boardArray[i][i] == mcolor && boardArray[i+1][i+1] == mcolor && boardArray[i+2][i+2] == mcolor && boardArray[i+3][i+3] == mcolor  
				&& boardArray[i+4][i+4] == mcolor){
				// do something.
			}
	}



	for(int k = 4; k>=1;k--){
		for (int i = 0; i<7-k ;i++){
			if(boardArray[i][k+i] == mcolor && boardArray[i+1][k+i+1] == mcolor && boardArray[i+2][k+i+2] == mcolor && boardArray[i+3][k+i+3] == mcolor  
				&& boardArray[i+4][k+i+4] == mcolor){
				// do something.
			}
		}  
	}

};

// given the string of turn of the opponent remove his markers from the board. 
void Board::removeRingOpponent(int opponentID ,int from_x ,int from_y , int to_x ,int  to_y ,int ring_removeX ,int ring_removeY){

	this->opponentnumberofrings --;
	boardArray[ring_removeX][ring_removeY] = -1;
	validArray[ring_removeX][ring_removeY] = true;

	if(from_x == to_x){
		int miy = from_y,mxy  = to_y;
		if(from_y>to_y){miy = to_y; mxy = from_y;}  
		for(int i = miy+1; i< mxy ;i++){
			if (boardArray[from_x][i] != -1 ) {boardArray[from_x][i] = -1; validArray[from_x][i]= true;}// CHECK THIS IF CONDITION
		}
	}

	else if(from_y == to_y){
		int mix = from_x,mxx  = to_x;
		if(from_x>to_x){mix = to_x; mxx = from_x;}  
		for(int i = mix+1; i< mxx ;i++){
			if (boardArray[i][from_y] != -1 ) {boardArray[i][from_y] = -1;boardArray[i][from_y]=true;} 
		}
	}

	else{
		if(from_x < to_x){
		int s = to_x - from_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x+i][from_y+i] != -1 ) {boardArray[from_x+i][from_y+i] = -1; boardArray[from_x+i][from_y+i] = true;} 
		}
		}

		else{
		int s =from_x -  to_x ;
		for(int i = 1; i< s ;i++){
			if (boardArray[from_x-i][from_y-i] != -1 ) {boardArray[from_x-i][from_y-i] = -1; boardArray[from_x-i][from_y-i] = true;} 
		}
		}
	}
}



// do something like storing a board and evaluationg the racursing on actions in minimax. 
vector<Board> Board::getSuccesors(int ringcolor){
	vector<Board> succ;
	// ringcolor == 
	for(int i =0;i<=10;i++){
		for(int j =0;j<=10;j++){
			if(boardArray[i][j] == ringcolor){
				vecor<Board> n = getNeighbours(i,j,ringcolor);
				succ.insert(succ.end(),n.begin(),n.end());
			}
		}
	}
	return succ;
}

// this is old one

