/*
	base cases : dynamic(-1) = 0 , dynamic(-2) = 0 

	recurrence relation : dynamic(weeks) = max(rh[weeks] + dynamic(weeks - 2), rl[weeks] + dynamic(weeks - 1))

	What recurrence relation defines : the dynamic function calculates the maximum revenue for a
                                       particular week. We pass the value of the last 
                                       week (n-1) to compute this. Its kind of bottom up.

	Parameters that it takes : weeks, memo array, struct containing rh/rl values, selection array

	Complexity : O(n) 

	Subproblems : n weeks so there are n sub-problems

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

using namespace std ;

struct factory
{
	int weeks ; // total number of weeks
	vector <int> rh ; // high revenues
	vector <int> rl ; // low revenues
} ;

void assign(int rh, int rl, int weeks, int memo[], int selection[])
{
	int final ;

	if (rh > rl)
		final = rh ;

	else
		final = rl ;

	if(final == rh)
	{
		memo[weeks] = final ;
		selection[weeks] = 2 ;
	}

	else
	{
		memo[weeks] = rl ;
		selection[weeks] = 0 ;
	}
}

int dynamic(int weeks, int memo[], factory fac, int selection[])
{
	if (memo[weeks] != -1)
		return memo[weeks] ; // using memoization. Results of sub problems already stored

	else
	{
		int rh ;
		if (weeks > 1)
		{
			rh = fac.rh[weeks] + dynamic((weeks - 2), memo, fac, selection) ;
		}

		else
		{
			rh = fac.rh[weeks] ;
		}

		int currently = fac.rl[weeks] ; 

		int rl = currently + dynamic((weeks - 1), memo, fac, selection) ;

		assign(rh, rl, weeks, memo, selection) ;

		return memo[weeks] ;
	}
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
	factory fac ;
    string trash , weeks ;
    fin >> trash >> weeks ;
	fac.weeks = stoi(weeks) ; 
	int selection[fac.weeks] ; // 0 for low, 1 for priming, 2 for high
    string line ;

	getline(fin, line) ;
	getline(fin, line) ;

	stringstream s(line) ;
	string part1 ;
	bool done = false ;
	while (s >> part1)
	{
		if (done == false)
		{
			done = true ;
		}

		else
		{
			fac.rh.push_back(stoi(part1)) ; 
		}
	}

	getline(fin, line) ;
	getline(fin, line) ;

	stringstream s1(line) ;
	string part2 ;
	done = false ;
	while (s1 >> part2)
	{
		if (done == false)
		{
			done = true ;
		}

		else
		{
			fac.rl.push_back(stoi(part2)) ; 
		}
	}

	int memo[fac.weeks] ; // for memoization

	for (int i = 0 ; i < fac.weeks ; i++)
		memo[i] = -1 ;

	/*Since machines are already primed we can select either high or low revenue
	for week1. Preferred to pick which ever one is the larger of the two*/

	if (fac.rh[0] > fac.rl[0])
	{
		memo[0] = fac.rh[0] ;
		selection[0] = 2 ; // high revenue at first index
	}

	else
	{
		memo[0] = fac.rl[0] ;
		selection[0] = 0 ; // low revenue at first index
	}

	// Starting from the last week to compute maximum revenue
	int total = dynamic(((fac.weeks) - 1), memo, fac, selection) ; 

	/*Here suppose we have selected high for some particular week so I am just
	assigning priming to the week before it. E.g if week2 is high then week1 == priming*/

	int start = fac.weeks - 1 ;
	int end = 0 ;
	while (start >= end)
	{
		if (selection[start] == 2)
		{
			selection[start - 1] = 1 ;
			start-- ; 
		}

		start-- ;
	}
	
	string output = "" ;

	for (int i = 0 ; i < fac.weeks ; i++)
	{
		output = output + "Week " + to_string(i + 1) + " : " ;
		if (selection[i] == 2)
		{
			output = output + "High " + to_string(fac.rh[i]) + "\n" ;
		}

		else if (selection[i] == 0)
		{
			output = output + "Low " + to_string(fac.rl[i]) + "\n" ;
		}

		else
		{
			output = output + "Priming" + "\n" ;
		}
	}

	output = output + "Total Revenue : " + to_string(total) + "\n" ;

	cout << output ;

	return 0 ;
}
