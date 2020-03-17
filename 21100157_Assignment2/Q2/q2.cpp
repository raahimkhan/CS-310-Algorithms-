/*I have used made a struct to store values of a single rack. Priority queue is used
based on max probability per length unit values which takes logn. The overall complexity of
the algorithm is nlog(n).*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <queue>
#include <cstdlib>

using namespace std ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

struct rack
{
	double length ;
	double probability ;
	int number ;
} ;

struct compare
{
	bool operator()(rack const& r1, rack const& r2) 
	{ 
    	return r1.probability/r1.length < r2.probability/r2.length ;
	} 
} ;

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;

	string trash , num ;
    fin >> trash >> num ; 
	int n = str_to_int(num) ;

	string line ;
	string temp ; // for lengths
	string temp2 ; // for probabilities

	getline(fin , line) ;

	getline(fin , line) ;
	temp = line ;

	getline(fin , line) ;
	temp2 = line ;

	int linelen1 = temp.length() ;
    string temp3 = temp.substr(2, linelen1-1) ; // lengths extracted

	int linelen2 = temp2.length() ;
    string temp4 = temp2.substr(2, linelen2-1) ; // probabilities extracted

	vector <double> l ;
	vector <double> p ;

	istringstream ss(temp3) ;

	while (ss)
	{ 
        string num ; 
        ss >> num ;
		l.push_back(str_to_int(num)) ;
	}

	istringstream ss1(temp4) ;

	while (ss1)
	{ 
        string num2 ; 
        ss1 >> num2 ;

		char str [num2.length() + 1] ;
		strcpy(str, num2.c_str()) ;
		char *end ;
		double number ;

		number = strtod(str, &end) ;

		p.push_back(number) ;
	}

	rack *Rack = new rack[n] ;

	for (int i = 0 ; i < n ; i++)
	{
		rack r ;
		r.number = (i + 1) ;
		r.length = l[i] ;
		r.probability = p[i] ;

		Rack[i] = r ;
	}

	priority_queue<rack, vector<rack>, compare> Racks ; 

	int b = 0 ;
	while (b < n)
	{
		Racks.push(Rack[b]) ;
		b++ ;
	}

	double time = 0 ;
	int total_length = 0 ;
	string output = "" ;

	for (int i = 0 ; i < n ; i++)
	{
		rack crap = Racks.top() ;
		total_length = total_length + crap.length ;
		time = time + (crap.probability * total_length) ;

		if (i == n - 1)
			output = output + to_string(crap.number) + "\n";

		else
			output = output + to_string(crap.number) + " " ;

		Racks.pop() ;
	}

	output = output + "Expected Time " + to_string(time) + "\n" ;

	cout << output ;

	return 0 ;
}