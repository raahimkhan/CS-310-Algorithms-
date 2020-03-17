
/*I have used priority queue to select columns based on max column values. I made structs
for rows and columns to store row indexes and pieces allowed at each index. Worst case time 
complexity is n^2*log(n) if all pieces are placed on the game board.*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <queue>

using namespace std ;

struct column
{
	int col_index ;
	int pieces ; // total game pieces in a column
} ;

struct row
{
	int row_index ;
	int pieces ; // total game pieces in a row
} ;

struct column_capacity
{

	bool operator()(column const& c1, column const& c2) 
	{ 
    	return c1.pieces < c2.pieces ; 
	} 

} ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
	string trash , num ;
    fin >> trash >> num ; 
	int n = str_to_int(num) ;
	bool flag = true ;

    string line ;
	string temp ; // for row line
	string temp2 ; // for col line

    getline(fin , line) ;

	getline(fin , line) ;
	temp = line ; 

	getline(fin , line) ;
	temp2 = line ; 

	int linelen1 = temp.length() ;
    string temp3 = temp.substr(4, linelen1-1) ; // row extracted

	int linelen2 = temp2.length() ;
    string temp4 = temp2.substr(4, linelen2-1) ; // column extracted

	istringstream ss(temp3) ;

	vector <int> r ;
	vector <int> c ;

	while (ss)
	{ 
        string num ; 
        ss >> num ;
		r.push_back(str_to_int(num)) ;
	}  

	istringstream ss1(temp4) ;

	while (ss1)
	{ 
        string num2 ; 
        ss1 >> num2 ;

		c.push_back(str_to_int(num2)) ;
	} 

	column *cols = new column[n] ;
	row *rows = new row[n] ;

	for (int i = 0 ; i < n ; i++)
	{
		column t1 ;
		t1.col_index = (i+1) ;
		t1.pieces = c[i] ;
		cols[i] = t1 ;
	}

	for (int i = 0 ; i < n ; i++)
	{
		row t2 ;
		t2.row_index = (i+1) ;
		t2.pieces = r[i] ;
		rows[i] = t2 ;
	}

	// Min Heap. Column number with maximum capacity is given priority
	priority_queue<column, vector<column>, column_capacity> Col ; 

	int b = 0 ;
	while (b < n)
	{
		Col.push(cols[b]) ;
		b++ ;
	}

	int gameboard[n][n] ;

	for(int i = 0 ; i < n ; i++)
	{
		for(int j = 0 ; j < n ; j++)
		{
			gameboard[i][j] = 0 ;
		}
	}

	for (int i = 0 ; i < n ; i++)
	{
		vector <column> history ;

		while (rows[i].pieces > 0)
		{
			if(Col.empty())
			{
				flag = false ;
				break ;
			}

			else
			{
				column c = Col.top() ;
				Col.pop() ;
				int col_indexx = c.col_index - 1 ;
				gameboard[i][col_indexx] = 1 ;
				rows[i].pieces = rows[i].pieces - 1 ;

				c.pieces = c.pieces - 1 ;
				if(c.pieces != 0)
				{
					history.push_back(c) ;
				}	
			}

			if(rows[i].pieces == 0)
				rows[i].pieces = 0 ;
		}

		for(int k = 0 ; k < history.size() ; k++)
		{
			Col.push(history[k]) ;
		}
	}

	if(!Col.empty())
	{
		flag = false ;
	}

	string output = "" ;

	if(flag == false)
	{
		output = output + "Not Possible" + "\n";
	}

	else
	{
		for(int i = 0 ; i < n ; i++)
		{
			for(int j = 0 ; j < n ; j++)
			{
				if(gameboard[i][j] == 1)
				{
					output = output + "(" + to_string(i+1) + "," + to_string(j+1) + ") " ;
				}
			}
			output = output.substr(0, output.length() - 1) ;
			output = output + "\n" ;
		}
	}
	cout << output ;

	return 0 ;
}
