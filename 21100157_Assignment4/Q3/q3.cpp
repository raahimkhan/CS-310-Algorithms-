/*
	base case : if (start_index + 1 > end index) {return 0} 

	recurrence relation : bestcost = (mark[end] - mark[start]) + 
						  min(mincost(start, i), mincost(i, end))
						  where i > start && i < end

	What recurrence relation defines : It computes the optimal cost to break down a ruler given
									   certain cut positions

	Parameters that it takes : initial index, final index, 2d memo array, array of broken pieces, 
							   cut locations

	Complexity : O(mlogm)

	Subproblems : log(m) subproblems since tree goes to m levels

	Time to solve each sub problem : O(1) time due to memoization
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
#include <utility>
#include <limits.h>

using namespace std ;

bool base(int a, int b)
{
	if (a >= b)
		return true ;

	return false ;
}

int find_min(int a, int b)
{
	if (a < b)
		return a ;

	return b ;
}

void assign(int &a, int &b, int **broken, int initial, int ending, int index)
{
	if (a < b)
	{
		b = a ;
		broken[initial][ending] = index ;
	}
}

int op_cost(int initial, int ending, int **memo, int **broken, vector <int> &cut_locations)
{
	bool check = base(initial + 1, ending) ;

	if (check == true)
		return 0 ;

	int memoized = memo[initial][ending] ;

	if(memoized == 0) 
	{
		int to_compare = INT_MAX ;

		int new_start = initial + 1 ; 

		for(int i = new_start ; i < ending ; i++)
		{
			int first_half = op_cost(initial, i, memo, broken, cut_locations) ;
			int second_half = op_cost(i, ending, memo, broken, cut_locations) ;

			int total = first_half + second_half ;

			int compare_with = find_min(to_compare, total) ;

			assign(compare_with, to_compare, broken, initial, ending, i) ;
		}

		int part1 = cut_locations[ending] - cut_locations[initial] ;
		int part2 = to_compare ;

		int part3 = part1 + part2 ;

		int to_store = part3 ;

		memo[initial][ending] = to_store ;

		return memo[initial][ending] ;
	}

	return memo[initial][ending] ; // if result already memoized return it
}

bool base2(int a, int b)
{
	if (a >= b)
		return true ;

	return false ;
}

void find_ordering(int initial, int ending, int **broken, vector <int> &cut_locations, bool flag, string &ans)
{
	if (flag == false)
	{
		ans = ans + "Optimal cut ordering: " ;
		flag = true ;
		find_ordering(initial, ending, broken, cut_locations, flag, ans) ;
	}

	else
	{
		if(base2(initial + 1, ending))
			return ;

		int temp = broken[initial][ending] ;

		ans = ans + to_string(cut_locations[temp]) + " " ;

		find_ordering(initial, temp, broken, cut_locations, flag, ans) ;
		find_ordering(temp, ending, broken, cut_locations, flag, ans) ;
	}
}
  
int main(int argc, char** argv) 
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , n ;
    fin >> trash >> n ;
	int ruler_length = stoi(n) ;

	string line ;

	getline(fin, line) ;
	getline(fin, line) ;

	stringstream s(line) ;

	string part ;
	bool done = false ;

	vector <int> cut_locations ; // stores cuts made on the rod at specific positions

	cut_locations.push_back(0) ;

	while(s >> part)
	{
		if (done == false)
		{
			done = true ;
			continue ;
		}

		else
		{
			cut_locations.push_back(stoi(part)) ;
		}
	}

	cut_locations.push_back(ruler_length) ;

	int **memo = new int*[cut_locations.size() + 1] ; ; // stores the cost of breakage of ruler
	int **broken = new int*[cut_locations.size() + 1] ; // separate ruler pieces

	for(int i = 0 ; i < cut_locations.size() + 1 ; i++)
		memo[i] = new int[cut_locations.size() + 1] ;
		

	for(int i = 0 ; i < cut_locations.size() + 1 ; i++)
		broken[i] = new int [cut_locations.size() + 1] ;
	
	
	// Initially memo has all values 0
	for(int i = 0 ; i < cut_locations.size() ; i++)
	{
		for(int j = 0 ; j < cut_locations.size(); j++)
		{
			memo[i][j] = 0 ;
		}
	}

	int optimal_cost = op_cost(0, cut_locations.size() - 1, memo, broken, cut_locations) ;

	bool flag = false ;

	string ans = "" ;

	find_ordering(0, cut_locations.size() - 1, broken, cut_locations, flag, ans) ;

	ans = ans + "\n" ;

	ans = ans+ "Least Cost: " + to_string(optimal_cost) + "\n" ;

	cout << ans ;
	
    return 0 ; 
} 
