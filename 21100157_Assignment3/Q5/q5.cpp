/*
My algorithm involved creating an array of size n (photos) and then breaking it 
into equal pieces and then passing these pieces recursively into the 
function. Once the base case of size 1 was hit, it returned the only value
in the array. The call above this recursive call then compared the value
with its sibling value and looked at which of the values was repeated more.
This comparison was an O(n) comparison and since there were an O(log(n))
recursive steps, the run-time complexity of my algorithm was O(n*logn).

Recurrence Relation :
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
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std ;

struct node
{
	int photo ;
	int index ;

	node()
	{
		photo = -1 ;
		index = -1 ;
	}

	node(int p, int i)
	{
		photo = p ;
		index = i ;
	}
} ;

int dominant_species_count = 0 ;

string decode(int pic1, int pic2)
{
	if(pic1 == pic2)
		return "Y" ;

	else
		return "N" ;
}

int merge(int start, int end, vector <node> &photos, int &flag1, int &flag2, int &type, string what)
{
	if (what == "l")
	{
		for(int i = start ; i < end ; i++)
		{
			string d1 = decode(photos[i].photo, type) ;

			if (d1 == "Y")
				flag1++ ;
		}
	}

	else if (what == "r")
	{
		for(int i = start ; i < end ; i++)
		{
			string d2 = decode(photos[i].photo, type) ;

			if (d2 == "Y")
				flag2++ ;
		}
	}
}

int DandC(vector <node> &photos, int start, int end)
{
	if (start == end - 1)
		return photos[start].photo ;

	int middle = (start + end)/2 ;

	int left = DandC(photos, start, middle) ;
	int right = DandC(photos, middle, end) ;

	int flag1 = 0 , flag2 = 0 ;

	merge(start, end, photos, flag1, flag2, left, "l") ;
	merge(start, end, photos, flag1, flag2, right, "r") ;
	
	if(flag1 > flag2)
		return left ;
	else
		return right ;
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , useful ;
    fin >> trash >> useful ;

	int encrypted_photos = stoi(useful) ;

	string trash2 , useful2 ;

	fin >> trash2 >> useful2 ;

	int species = stoi(useful2) ;

	string line ;

	getline(fin, line) ;

	getline(fin, line) ;

	vector <int> store ;

	string extract ;

	stringstream iss(line) ;

	while (iss >> extract) 
	{
		store.push_back(stoi(extract)) ;
	}

	vector <node> photos ; // vector containing photos and their respective indexes

	for (int i = 0 ; i < store.size() ; i++)
	{
		int p = store[i] ;
		node temp ;
		temp.photo = p ;
		temp.index = i ;
		photos.push_back(temp) ;
	}

	int dominant_species = DandC(photos, 0, encrypted_photos) ;

	vector <node> final ;

	for(int i = 0 ; i < encrypted_photos ; i++)
	{
		int p1 = photos[i].photo ;
		string d1 = decode(p1, dominant_species) ;
		if(d1 == "Y")
		{
			dominant_species_count++ ;
			final.push_back(photos[i]) ;
		}
	}

	bool truth ;

	if(dominant_species_count > (encrypted_photos)/2)
	{
		truth = true ;
	}

	else
		truth = false ;

	string output = "" ;

	if (truth == true)
	{
		output = output + "Success" + "\n" + "Dominant Species Count" + " " + to_string(dominant_species_count) + "\n" ;

		output = output + "Dominant Species Indices" + " " ;

		for (int i = 0 ; i < final.size() ; i++)
		{
			if (i == final.size() - 1)
				output = output + to_string(final[i].index) + "\n" ;

			else
				output = output + to_string(final[i].index) + " " ;
		}
	}

	else
	{
		output = output + "Failure" + "\n" ;
	}

	cout << output ;

	return 0 ;
}
