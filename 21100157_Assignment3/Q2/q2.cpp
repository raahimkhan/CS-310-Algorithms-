/*
My algorithm is basically based on finding invertions in an array that we studied in class.
I made an array of structs containing days and their respective counts. I passed this array
to a modified version of merge sort. Where as in simple merge sort the array is first divided
recursively into left and right parts. We calculate inversions in left and right halfs and then
inversions in the combined sorted part and sum these 3 parts to get total failure values.

Running time is O(nlogn). Recursively dividing would take logn time and merge takes
linear time because we take each element for once so for n elements it would be O(n).
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

struct exp
{
	int day ;
	int cells ;
} ;

vector< pair <int,int> > sorted ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

int join_back(exp experiment[], exp cpy[], int left, int mid, int right) ;

int divider(exp experiment[], exp cpy[], int left, int right) 
{
	int mid = 0 ;
	int failed = 0 ;

	if (right > left)
	{
		mid = (right + left) / 2 ;

		failed = divider(experiment, cpy, left, mid) ; 
		failed += divider(experiment, cpy, mid + 1, right) ;

		failed += join_back(experiment, cpy, left, mid + 1, right) ;  
	}

	return failed ;
}

int count_failures(int &failed, int left, int mid, int right, exp experiment[])
{
	int i = left ;
	int j = mid ;
	int k = left ;

	while ((i <= mid - 1) && (j <= right)) 
    { 
        if (((experiment[i].cells)/ 2) > experiment[j].cells) 
        { 
            failed += (mid - i) ;
			sorted.push_back( make_pair(experiment[j].day, experiment[i].day) ) ; 
            int ptr = i + 1 ;
            while (ptr < mid)
            {
				sorted.push_back( make_pair(experiment[j].day, experiment[ptr].day) ) ;
                ptr++ ;
            }

            j++ ; 
        }

        else 
        { 
            i++ ; 
        } 
    }
}

void first_pass(int left, int mid, int right, exp experiment[], exp cpy[], int &a, int &b, int &c)
{
	while ((a <= mid - 1) && (b <= right)) 
	{ 
        if (experiment[a].cells <= experiment[b].cells) 
		{ 
            cpy[c++] = experiment[a++] ; 
        }

        else 
		{ 
            cpy[c++] = experiment[b++] ; 
        } 
    }
}

int join_back(exp experiment[], exp cpy[], int left, int mid, int right)
{
	int failed = 0 ;

	count_failures(failed, left, mid, right, experiment) ;

	int a = left ;
	int b = mid ;
	int c = left ;

	first_pass(left, mid, right, experiment, cpy, a, b, c) ;

	while (a <= mid - 1) 
        cpy[c++] = experiment[a++];

	while (b <= right) 
        cpy[c++] = experiment[b++] ;

	for (a = left; a <= right; a++) 
        experiment[a] = cpy[a] ; 

	return failed ;  
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , useful ;
    fin >> trash >> useful ;
	int n = str_to_int(useful) ; 
    string line ;
	getline(fin, line) ;
	getline(fin, line) ;
	
	vector <int> data ;
	exp experiment[n] ;

	stringstream s(line) ;
	string part ;
	while (s >> part)
		data.push_back(str_to_int(part)) ; 

	for (int i = 0 ; i < n ; i++)
	{
		experiment[i].day = i ;
		experiment[i].cells = data[i] ;
	}

	exp cpy[n] ; // for keeping sorted elements

	int left = 0 ;
	int right = n - 1 ;

	int failed = divider(experiment, cpy, left, right) ; 

	string finalans = "" ;

	finalans = finalans + "Failed Trials " + to_string(failed) + "\n" ;

	sort(sorted.begin(), sorted.end()) ;

	for (int i= 0 ; i < failed ; i++) 
    {
		if (i == 0)
			finalans = finalans + "(" + to_string(sorted[i].first) + "," + to_string(sorted[i].second) + ")" ;

		else
		{
			if (sorted[i].first > sorted[i-1].first)
			{
				finalans = finalans + "\n" ;
				finalans = finalans + "(" + to_string(sorted[i].first) + "," + to_string(sorted[i].second) + ")" ;
			}

			else
			{
				finalans = finalans + " " + "(" + to_string(sorted[i].first) + "," + to_string(sorted[i].second) + ")" ;
			}
		} 
    }

	finalans = finalans + "\n" ;

	cout << finalans ;  

	return 0 ;
}