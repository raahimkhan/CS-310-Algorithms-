/*
I have used gale-shapley algorithm. I made a preference grid for teams. Grid has locations
ranked for each team from least to most desired. I have then used the approach of comparing indices
of each location and i stored these indices and travel routes for each team in separate arrays.
In the end I simply compared who came first or later at that position using those arrays.

Complexity = O(n^2) 
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <list>
#include <utility> 
#include <set>
#include <algorithm>

using namespace std ;

struct schedule
{
    int name ; // team name
    vector <int> sch ; // stores travelling and current location info
} ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

void gale_shapley(int **pref, vector <bool> &done, vector <int> &dest_final, vector <bool> &took_dest, int n, int counter)
{
    while(!(counter < 0 || counter > n * 2))
    {
        int i = 0 ;
        while(i < n)
        {
            if (pref[i][(n * 2) - counter] != -1 && took_dest[(pref[i][(n * 2) - counter]) - 1] == false)
            {
                done[i] = true ; // found final destination of a particular team
                took_dest[(pref[i][(n * 2) - counter]) - 1] = true ; // storing the path taken
                dest_final[i] = pref[i][(n * 2) - counter] ; // stores final destination of team
            }

            i++ ;
        }

        int flag = counter % 2 ;

        if (flag == 0)
            counter = counter - 1 ;

        else
            counter = counter + 2 ;
    }
}

int *helper ;

void gale_helper(vector <int> &dest_final, int n)
{
    int counter = 0 ;
    while(counter < n)
    {
        int counter2 = 0 ;
        while(counter2 < n)
        {
            int to_check = helper[counter] ;
            int compare_with = helper[counter2] ;
            if (dest_final[to_check] < dest_final[compare_with])
            {
                int temp = helper[counter] ;
                helper[counter] = helper[counter2] ;
                helper[counter2] = temp ;
            }

            counter2++ ;
        }

        counter++ ;
    }
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , useful ;
    fin >> trash >> useful ;
	int n = str_to_int(useful) ; 

    helper = new int[n] ;
    for(int i = 0 ; i < n ; i++)
        helper[i] = i ;

	schedule *S = new schedule [n] ;
    int curr = 0 ;
    int curr_loc ;
    bool done = false ;
    string line ;
    getline(fin , line) ;

    while (getline(fin , line))
    {
        stringstream s(line) ;
        string part ;
        
        while (s >> part)
        {
            if (done == false)
            {
                S[curr].name = curr + 1 ;
                done = true ;
            }

            else
            {
                if (part == ":")
                    continue ;

                else
                {
                    if (part == "-")
                        S[curr].sch.push_back(-1) ; // travelling
                    else
                    {
                        curr_loc = stoi(part.substr(1)) ;
                        S[curr].sch.push_back(curr_loc) ;
                    }
                }
            }
        }
        
        done = false ;
        curr++ ;
    }

    int **pref = new int* [n] ; // location preferences for teams

    for(int i = 0 ; i < n ; i++)
		pref[i] = new int[n*2] ;

    vector <bool> donee ; // found final destination
    donee.assign(n, false) ;

    vector <int> dest_final ; // final destination of teams
    dest_final.assign(n, -1) ;

    vector <bool> took_dest ; // destination taken by teams
    took_dest.assign(n, false) ;

    for (int i = 0 ; i < n ; i++)
    {
       int t = S[i].name ;

       for (int j = 0 ; j < S[i].sch.size() ; j++)
       {
           pref[t - 1][j] = S[i].sch[j] ;
       }
    }

    gale_shapley(pref, donee, dest_final, took_dest, n, 2) ;

    gale_helper(dest_final, n) ;

    string output = "" ;

    output = output + "Final Destinations: " ;

    for (int i = 0 ; i < n ; i++)
    {
        int sol = helper[i] ;
        output = output + "L" + to_string(dest_final[sol]) + " T" + to_string(sol + 1) + ", " ;
    }

    output = output.substr(0, output.length()-2) ;
	output = output + "\n" ;

    cout << output ;

	return 0 ;
}