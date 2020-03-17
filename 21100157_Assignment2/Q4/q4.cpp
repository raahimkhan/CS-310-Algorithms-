/*I made structs to represent rooms and doors inside them. I just check all rooms one by one to
see possibility. It takes nlogn time sometimes.*/

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

struct Door
{
	char number ;
	bool isAnti ;
	string name ;

	Door(int n, bool i)
	{
		number = n ;
		isAnti = i ;
	}

	Door()
	{

	}
} ;

struct room
{
	Door door1 ;
	Door door2 ;

	room(Door d1, Door d2)
	{
		door1 = d1 ;
		door2 = d2 ;
	}

	room()
	{
		
	}
} ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

bool checkdoor(vector <Door> d, Door given)
{
	for (int i = 0 ; i < d.size() ; i++)
	{
		if (d[i].name == given.name)
			return true ;
	}

	return false ;
}

bool checkIsAnti(vector <Door> d, Door given)
{
	for (int i = 0 ; i < d.size() ; i++)
	{
		if (d[i].number == given.number)
		{
			if (d[i].isAnti != given.isAnti)
				return true ;
		}
	}

	return false ;
}

void sortvector(vector <Door> &d)
{
	Door temp ;
	for(int i = 0 ; i < d.size() ; i++)
	{		
		for(int j = i+1 ; j < d.size() ; j++)
		{
			if(d[i].number > d[j].number)
			{
				temp = d[i] ;
				d[i] = d[j] ;
				d[j] = temp ;
			}
		}
	}
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;

	int n , k ;

	string trash1, trash2, readn, readk ;

	fin >> trash1 >> readn ;

	n = str_to_int(readn) ;

	fin >> trash2 >> readk ;

	k = str_to_int(readk) ;

	string line ;
	string part1 , part2 ;

	room *rooms = new room [n] ;
	int room_counter = 0 ;
	bool flag = false ;

	while (getline(fin , line))
	{
		string stream ;
		bool donefirst = false ;
		stringstream iss(line) ;

		while (iss >> stream) 
		{
			if (donefirst == false)
				part1 = stream ;

			else
				part2 = stream ;

			donefirst = true ;
		}

		if (flag == false)
		{
			flag = true ;
		}

		else
		{
			int part1length = part1.length() ;
			int part2length = part2.length() ;
			Door door1 ;
			Door door2 ;

			if (part1length == 2)
			{
				door1.number = part1[1] ;
				door1.isAnti = false ;
				string s(1, door1.number) ; 
				door1.name = "d" + s ;
			}

			else if (part1length == 3)
			{
				door1.number = (part1[2]) ;
				door1.isAnti = true ;
				string s(1, door1.number) ; 
				door1.name = "da" + s ;
			}

			if (part2length == 2)
			{
				door2.number = (part2[1]) ;
				door2.isAnti = false ;
				string s(1, door2.number) ; 
				door2.name = "d" + s ;
			}

			else if (part2length == 3)
			{
				door2.number = (part2[2]) ;
				door2.isAnti = true ;
				string s(1, door2.number) ; 
				door2.name = "da" + s ;
			}

			rooms[room_counter].door1 = door1 ;
			rooms[room_counter].door2 = door2 ;

			room_counter++ ;
		}
	}

	vector <Door> opened ;
	bool starting = false ;
	bool notpossible = false ;

	for (int i = 0 ; i < n ; i++)
	{
		room r = rooms[i] ;

		if (starting == false)
		{
			opened.push_back(r.door1) ;
			starting = true ;
		}

		else
		{
			Door firstdoor = rooms[i].door1 ;
			Door seconddoor = rooms[i].door2 ;

			bool present = checkdoor(opened, firstdoor) ;
			if (present == true) // if door already opened e.g room1 d1 and room2 d1 (goto next room)
				continue ;
			else
			{
				bool anti = checkIsAnti(opened, firstdoor) ;
				if (anti == false)
				{
					opened.push_back(firstdoor) ;
					continue ;
				}

				else // if it is anti door skip it and check second door
				{
					bool present2 = checkdoor(opened, seconddoor) ;
					if (present2 == true)
						continue ;
					else
					{
						bool anti2 = checkIsAnti(opened, seconddoor) ;
						if (anti2 == false)
						{
							opened.push_back(seconddoor) ;
							continue ;
						}

						else
						{
							notpossible = true ;
							break ;
						}
					}

				}

			}
		}
	}

	string output = "" ;
	
	if (notpossible == true)
		output = output + "No" + "\n" ;

	else
	{
		output = output + "Yes" + "\n" ;
		sortvector(opened) ;
		for (int i = 0 ; i < opened.size() ; i++)
		{
			if (opened[i].isAnti == false)
				output = output + "1" + "\n" ;

			else
				output = output + "0" + "\n" ;
		}
	}

	cout << output ;

	return 0 ;
}
