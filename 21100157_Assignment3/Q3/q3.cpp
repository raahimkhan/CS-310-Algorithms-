/*
Initially I have a complete nxn board. First I assign colors to three quadrants excluding
the one which has a hole in it. After that I recursively keep breaking the board into 4 halfs
and keep assigning colors by excluding the quadrant which has hole. This continues until
base case of size 2x2 is hit. That is 4 tiles with one colored so we color the remaining 3
for the base case and return from the function.
Complexity of my algorithm is O(n^2).

Recurrence relation :
T(1) = b
T(n) = 2T(n/2) + nc
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std ;

int total_boomerangs = 0 ; // counter for placing boomerangs on board

struct Pair // to store x and y indices of each boomerang's and its color (number)
{
    int number, x_coord , y_coord ;

    Pair(){} ;

    Pair(int n , int x , int y)
    {
        number = n ;
        x_coord = x ;
        y_coord = y ;
    }

    Pair(int x , int y)
    {
        x_coord = x ;
        y_coord = y ;
    }
} ;

vector <Pair> finalans ;

void basecase(int **board, int row_s, int column_s, Pair hole, int n)
{
    total_boomerangs = total_boomerangs + 1 ;

    int total = row_s + n ;
    int total2 = column_s + n ;

    for (int i = row_s ; i < total ; i++)
    {
        for (int j = column_s ; j < total2 ; j++)
        {
            if (!(i == hole.x_coord && j == hole.y_coord))
            {
                Pair temp ;
                temp.number = total_boomerangs ;
                temp.x_coord = i ;
                temp.y_coord = j ;
                finalans.push_back(temp) ;
                board[i][j] = total_boomerangs ;
            }
        }
    }
}

int check_quadrant(Pair hole, int xmid, int ymid)
{
    int quad ;

    if (hole.x_coord < xmid && hole.y_coord < ymid)
        quad = 1 ;

    else if (hole.x_coord < xmid && hole.y_coord >= ymid)
        quad = 2 ;

    else if (hole.x_coord >= xmid && hole.y_coord < ymid)
        quad = 3 ;

    else if (hole.x_coord >= xmid && hole.y_coord >= ymid)
        quad = 4 ;

    return quad ;
}

void assign_boomerang(int **board, int xmid, int ymid, int quadrant)
{
    if (quadrant == 1)
    {
        board[xmid-1][ymid] = total_boomerangs ;
        board[xmid][ymid-1] = total_boomerangs ;
        board[xmid][ymid] = total_boomerangs ;
    }

    else if (quadrant == 2)
    {
        board[xmid-1][ymid-1] = total_boomerangs ;
        board[xmid][ymid-1] = total_boomerangs ;
        board[xmid][ymid] = total_boomerangs ;
    }

    else if (quadrant == 3)
    {
        board[xmid-1][ymid-1] = total_boomerangs ;
        board[xmid-1][ymid] = total_boomerangs ;
        board[xmid][ymid] = total_boomerangs ;
    }

    else if (quadrant == 4)
    {
        board[xmid-1][ymid-1] = total_boomerangs ;
        board[xmid-1][ymid] = total_boomerangs ;
        board[xmid][ymid-1] = total_boomerangs ;
    }
}

void boomerang(int **board, int row_s, int column_s, Pair hole, int n)
{
    if (n == 2) // Base Case for a 2x2 board
    { 
        basecase(board, row_s, column_s, hole, n) ;

        Pair temp2(-1, -1, -1) ; // separator for newline in final cout statement
        finalans.push_back(temp2) ;

		return ;
    }

    total_boomerangs = total_boomerangs + 1 ;

    int half = n/2 ;
    int xmid = row_s + half ;
	int ymid = column_s + half ;

    Pair newhole1 ; // hole in first quadrant
    Pair newhole2 ; // hole in second quadrant
    Pair newhole3 ; // hole in third quadrant
    Pair newhole4 ; // hole in fourth quadrant

    int quadrant = check_quadrant(hole, xmid, ymid) ;

    if(quadrant == 1) // if hole in first quadrant
    {
        assign_boomerang(board, xmid, ymid, quadrant) ;
	
        Pair temp3 ;
        temp3.number = total_boomerangs ;
        temp3.x_coord = xmid - 1 ;
        temp3.y_coord = ymid ;
        finalans.push_back(temp3) ;

        Pair temp4 ;
        temp4.number = total_boomerangs ;
        temp4.x_coord = xmid ;
        temp4.y_coord = ymid - 1 ;
        finalans.push_back(temp4) ;

        Pair temp5 ;
        temp5.number = total_boomerangs ;
        temp5.x_coord = xmid ;
        temp5.y_coord = ymid ;
        finalans.push_back(temp5) ;

        Pair temp6(-1, -1, -1) ; // separator for newline in final cout statement
        finalans.push_back(temp6) ;
        
        newhole1.x_coord = hole.x_coord ;
        newhole1.y_coord = hole.y_coord ;

        newhole2.x_coord = xmid - 1 ;
        newhole2.y_coord = ymid ;

        newhole3.x_coord = xmid ;
        newhole3.y_coord = ymid -1 ;

        newhole4.x_coord = xmid ;
        newhole4.y_coord = ymid ; 
    }

    if(quadrant == 2) // if hole in second quadrant
    {
		assign_boomerang(board, xmid, ymid, quadrant) ;

        Pair temp3 ;
        temp3.number = total_boomerangs ;
        temp3.x_coord = xmid - 1 ;
        temp3.y_coord = ymid - 1 ;
        finalans.push_back(temp3) ;

        Pair temp4 ;
        temp4.number = total_boomerangs ;
        temp4.x_coord = xmid ;
        temp4.y_coord = ymid - 1 ;
        finalans.push_back(temp4) ;

        Pair temp5 ;
        temp5.number = total_boomerangs ;
        temp5.x_coord = xmid ;
        temp5.y_coord = ymid ;
        finalans.push_back(temp5) ;

        Pair temp6(-1, -1, -1) ; // separator for newline in final cout statement
        finalans.push_back(temp6) ;
        
        newhole1.x_coord = xmid - 1 ;
        newhole1.y_coord = ymid - 1 ;

        newhole2.x_coord = hole.x_coord ;
        newhole2.y_coord = hole.y_coord ;

        newhole3.x_coord = xmid ;
        newhole3.y_coord = ymid -1 ;

        newhole4.x_coord = xmid ;
        newhole4.y_coord = ymid ; 
    }

    if(quadrant == 3) // if hole in third quadrant
    {
		assign_boomerang(board, xmid, ymid, quadrant) ;

        Pair temp3 ;
        temp3.number = total_boomerangs ;
        temp3.x_coord = xmid - 1 ;
        temp3.y_coord = ymid - 1 ;
        finalans.push_back(temp3) ;

        Pair temp4 ;
        temp4.number = total_boomerangs ;
        temp4.x_coord = xmid - 1 ;
        temp4.y_coord = ymid ;
        finalans.push_back(temp4) ;

        Pair temp5 ;
        temp5.number = total_boomerangs ;
        temp5.x_coord = xmid ;
        temp5.y_coord = ymid ;
        finalans.push_back(temp5) ;

        Pair temp6(-1, -1, -1) ; // separator for newline in final cout statement
        finalans.push_back(temp6) ;

        newhole1.x_coord = xmid - 1 ;
        newhole1.y_coord = ymid - 1 ;

        newhole2.x_coord = xmid - 1 ;
        newhole2.y_coord = ymid ;

        newhole3.x_coord = hole.x_coord ;
        newhole3.y_coord = hole.y_coord ;

        newhole4.x_coord = xmid ;
        newhole4.y_coord = ymid ; 
    }

    if(quadrant == 4) // if hole in fourth quadrant
    {
		assign_boomerang(board, xmid, ymid, quadrant) ;

        Pair temp3 ;
        temp3.number = total_boomerangs ;
        temp3.x_coord = xmid - 1 ;
        temp3.y_coord = ymid - 1 ;
        finalans.push_back(temp3) ;

        Pair temp4 ;
        temp4.number = total_boomerangs ;
        temp4.x_coord = xmid - 1 ;
        temp4.y_coord = ymid ;
        finalans.push_back(temp4) ;

        Pair temp5 ;
        temp5.number = total_boomerangs ;
        temp5.x_coord = xmid ;
        temp5.y_coord = ymid - 1 ;
        finalans.push_back(temp5) ;

        Pair temp6(-1, -1, -1) ; // separator for newline in final cout statement
        finalans.push_back(temp6) ;
        
        newhole1.x_coord = xmid - 1 ;
        newhole1.y_coord = ymid - 1 ;

        newhole2.x_coord = xmid - 1 ;
        newhole2.y_coord = ymid ;

        newhole3.x_coord = xmid ;
        newhole3.y_coord = ymid -1 ;

        newhole4.x_coord = hole.x_coord ;
        newhole4.y_coord = hole.y_coord ; 
    }

    // Recursively break board until 2x2 board reached

    boomerang(board, row_s, column_s, newhole1, half) ; // 1st
    boomerang(board, row_s, column_s + half, newhole2, half) ; // 2nd
    boomerang(board, row_s + half, column_s, newhole3, half) ; // 3rd
    boomerang(board, row_s + half, column_s + half, newhole4, half) ; // 4th
}
  
int main(int argc, char** argv) 
{ 
    char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , useful ;
    fin >> trash >> useful ;
	int n = stoi(useful) ; 
    string line ;
    getline(fin, line) ;
    getline(fin, line) ;

    string removed = line ;
    vector <int> values ;
	
    char line5[removed.length()] ;
    for (int i = 0 ; i < removed.length() ; i++)
        line5[i] = removed[i] ;

    line5[0] = ' ' ;
    line5[removed.length()-1] = ' ' ;
    char separator = ' ' ;
    char* tok4 = strtok(line5, &separator) ;
    char* tok5 = tok4 ;

    char separator2 = ',' ;
    tok5 = strtok(tok5, &separator2) ;

    while(tok5 != NULL)
    {
        values.push_back(atoi(tok5)) ;
        tok5 = strtok(NULL, &separator2) ;
    }

    int row_index = values[0] ;
    int column_index = values[1] ;

    //int board[n][n] ; 
    int **board = new int* [n] ; // n x n square board for tiling
    for (int i = 0 ; i < n ; i++)
        board[i] = new int [n] ;

    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < n ; j++)
        {
            board[i][j] = 0 ; // initially all squares (1x1) unfilled
        }
	}

    board[row_index][column_index] = -1 ; // placement of hole in the board

    Pair hole(row_index, column_index) ;

    boomerang(board, 0, 0, hole, n) ; // 2D-array, rowstart index
    // colstart index in this order

    string output = "" ;
    bool truth = false ;
    int starter = 0 ;

    for (int i = 0 ; i < finalans.size() ; i++)
    {
        if (finalans[i].number == -1 && finalans[i].x_coord == -1 && finalans[i].y_coord == -1)
        {
            output = output + "\n" ;
            starter = 0 ;
            continue ;
        }

        else
        {
            if (truth == false)
            {
                output = output + to_string(finalans[i].number) + " " + "(" + to_string(finalans[i].x_coord) + "," + to_string(finalans[i].y_coord) + ")" ;
                truth = true ;
            }

            else
                output = output + " " + "(" + to_string(finalans[i].x_coord) + "," + to_string(finalans[i].y_coord) + ")" ;
        }

        starter++ ;

        if (starter == 3)
        {
            starter = 0 ;
            truth = false ;
        }
    }

    cout << output ;

    return 0 ; 
} 
