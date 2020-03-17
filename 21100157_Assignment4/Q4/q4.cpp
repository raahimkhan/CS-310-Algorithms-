/*
	base case : dynamic(0, 0) = true

	recurrence relation : interleaving(0, j) = interleaving(0, j-1) if s2[j-1] == s3[j-1]
						  interleaving(i, 0) = interleaving(i-1, 0) if s1[i-1] == s3[i-1]
						  interleaving(i, j) = interleaving(i-1, j) || interleaving(i, j-1) if top and left match

	What recurrence relation defines : It checks whether a third string is interleaved by first 2

	Parameters that it takes : string1, string2, and string3

	Complexity : O(m*n) where m == length of string1 and n == length of string2 

	Subproblems : mn grid size computed everytime 

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

struct interleaving // i will split strings into its charachters and give each char a bool
{
	char ch ;
	bool done ;
} ;

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;

	string string1 ;
	string string2 ;
	string string3 ;

    fin >> string1 ;
	fin >> string2 ;
	fin >> string3 ;

	string output = "" ;
	vector< pair <int,char> > ordering ; // contains final rows of output
	
	int length1 = strlen(string1.c_str()) ;
	int length2 = strlen(string2.c_str()) ;
	int length3 = strlen(string3.c_str()) ;

	char splitString3[length3 + 1] ;
	strcpy(splitString3, string3.c_str()) ;

	interleaving s3[length3] ;
	for (int i = 0 ; i < length3 ; i++)
	{
		s3[i].ch = splitString3[i] ;
		s3[i].done = false ;
	}

	char splitString1[length1 + 1] ;
	strcpy(splitString1, string1.c_str()) ;

	interleaving s1[length1] ;
	for (int i = 0 ; i < length1 ; i++)
	{
		s1[i].ch = splitString1[i] ;
		s1[i].done = false ;
	} 

	char splitString2[length2 + 1] ;
	strcpy(splitString2, string2.c_str()) ;

	interleaving s2[length2] ;
	for (int i = 0 ; i < length2 ; i++)
	{
		s2[i].ch = splitString2[i] ;
		s2[i].done = false ;
	} 

	// +1 because 0th index as well (0th row and 0th column which will be true) (can say is a memo)
	bool dynamic[length1 + 1][length2 + 1] ; // grid for checking interleaving using memoization

	if (length3 != length1 + length2) // if length of string3 not equal to m + n (string1 + string2)
	{
		output = output + "INVALID" + "\n" ;
	}

	else
	{
		for (int i = 0 ; i <= length1 ; i++)
		{
			for (int j = 0 ; j <= length2 ; j++)
			{
				if (i == 0 && j == 0)
					dynamic[i][j] = true ;

				else if (i == 0) // traversing first row of grid
				{
					// checking whether true present on left of curr index
					bool onLeft = dynamic[i][j - 1] ;

					// taking char of string2 
					char current_s2 = string2[j - 1] ;

					// taking char from string3 to match with char from string2
					char current_s3 = s3[i + j - 1].ch ;

					bool matched = onLeft && (current_s2 == current_s3) ;
					dynamic[i][j] = onLeft && (current_s2 == current_s3) ;

					if (matched == false)
						continue ;

					else // if matched and left index is true
					{
						// if char from string3 already located in either of first 2 strings
						if (s3[i + j - 1].done == true)
							continue ;

						else
						{
							s3[i + j - 1].done = true ;
							s2[j - 1].done = true ;
							pair <int,char> p ;
							p.first = 2 ;
							p.second = current_s2 ;
							ordering.push_back(p) ;
						}
					} 
				}

				else if (j == 0) // first column of grid
				{
					// checking whether true present on top of curr index
					bool onTop = dynamic[i - 1][j] ;

					// taking char of string1
					char current_s1 = string1[i - 1] ;

					// taking char from string3 to match with char from string1
					char current_s3 = s3[i + j - 1].ch ;

					// checking if they both match
					bool matched = onTop && (current_s1 == current_s3) ;

					dynamic[i][j] = onTop && (current_s1 == current_s3) ;

					if (matched == false)
						continue ;

					else // if matched and top index is true
					{
						// if char from string3 already located in either of first 2 strings
						if (s3[i + j - 1].done == true)
							continue ;

						else
						{
							s3[i + j - 1].done = true ;
							s1[i - 1].done = true ;
							pair <int,char> p ;
							p.first = 1 ;
							p.second = current_s1 ;
							ordering.push_back(p) ;
						}
					}
				}

				else // if inbetween grid at any index of i and j
				{
					/*Now this will have 2 cases either much top or right as in
					above 2 cases*/

					// Case 1
					bool onTop = dynamic[i - 1][j] ;
					char current_s1 = string1[i - 1] ;
					char current_s3 = s3[i + j - 1].ch ;
					bool truth1 = (onTop && string1[i - 1] == s3[i + j - 1].ch) ;

					// Case 2
					bool onLeft = dynamic[i][j - 1] ;
					char current_s2 = string2[j - 1] ;
					current_s3 = s3[i + j - 1].ch ;
					bool truth2 = (onLeft && string2[j - 1] == s3[i + j - 1].ch) ;

					dynamic[i][j] = (dynamic[i - 1][j] && string1[i - 1] == s3[i + j - 1].ch) || (dynamic[i][j - 1] && string2[j - 1] == s3[i + j - 1].ch) ;

					if (dynamic[i][j] == true)
					{
						if (onLeft == true && onTop != true)
						{
							if (s3[i + j - 1].done == true)
							{
								continue ;
							}
								
							else
							{
								s3[i + j - 1].done = true ;
								s2[j - 1].done = true ;
								pair <int,char> p ;
								p.first = 2 ;
								p.second = current_s2 ;
								ordering.push_back(p) ;
							}
						}

						else if (onLeft != true && onTop == true)
						{
							if (s3[i + j - 1].done == true)
							{
								continue ;
							}

							else
							{
								s3[i + j - 1].done = true ;
								s1[i - 1].done = true ;
								pair <int,char> p ;
								p.first = 1 ;
								p.second = current_s1 ;
								ordering.push_back(p) ;
							}
						}

						else if (onLeft == true && onTop == true)
						{
							if (s3[i + j - 1].done == true)
							{
								continue ;
							}

							else
							{
								if (s1[i - 1].done == true && s2[j - 1].done == false)
								{
									s3[i + j - 1].done = true ;
									s2[j - 1].done = true ;
									pair <int,char> p ;
									p.first = 2 ;
									p.second = current_s2 ;
									ordering.push_back(p) ;
								}

								else if (s1[i - 1].done == false && s2[j - 1].done == true)
								{
									s3[i + j - 1].done = true ;
									s1[i - 1].done = true ;
									pair <int,char> p ;
									p.first = 1 ;
									p.second = current_s1 ;
									ordering.push_back(p) ;
								}
							}
						}
					} 
				}
			}
		}

		if(dynamic[length1][length2])
		{
			output = output + "VALID" + "\n" ;

			for (int i = 0 ; i < ordering.size() ; i++)
			{
				if (i == 0)
				{
					char temp = ordering[i].second ;
					string s(1, temp);
					output = output + to_string(ordering[i].first) + ":" + s ;
				}
				
				else
				{
					if (ordering[i].first == ordering[i-1].first)
					{
						char temp = ordering[i].second ;
						string s(1, temp);
						output = output + s ;
					}

					else
					{
						output = output + "\n" ;
						char temp = ordering[i].second ;
						string s(1, temp);
						output = output + to_string(ordering[i].first) + ":" + s ;
					}
				}
			}

			output = output + "\n" ;
		}
			
		else
			output = output + "INVALID" + "\n" ;
	}

	cout << output ;
	
	return 0 ;
}
