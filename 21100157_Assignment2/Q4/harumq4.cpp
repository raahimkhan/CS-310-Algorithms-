#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;

struct Door{

	int number;
	bool anti; 
	int count;
	Door(int number1,int count2, bool anti1)
	{
		number = number1;
		anti = anti1;
		count = count2;
	}
	Door(int number1, bool anti1)
	{
		number = number1;
		anti = anti1;
	}
	Door(){}
};

struct Room{

	Door door1;
	Door door2;
	bool opened;
};

struct compareD{

	bool operator()(Door const& d1, Door const& d2) 
	{ 
    	return d1.count < d2.count; 
	} 

};


int main(int argc, char** argv)
{
	char* filename = argv[1];
	ifstream testfile(filename);
	string answer = "";
	if(testfile.is_open())
	{

		int total_number_of_rooms = 0;
		string kkkkkkk;
		testfile>>kkkkkkk>>total_number_of_rooms;
		
		int total_number_of_labels;
		testfile>>kkkkkkk>>total_number_of_labels;
		int* Anti = new int[total_number_of_labels];
		int* notAnti = new int[total_number_of_labels];
		for(int i = 0; i < total_number_of_labels; i++)
		{
			Anti[i] = 0;
			notAnti[i] = 0;
		}
		int	 countt = total_number_of_rooms;
		Room* rooms = new Room[total_number_of_rooms];
		vector <Door> ans;

		for(int i = 0; i < total_number_of_rooms; i++)
		{
			string random_bakwas = "";
			string random_bakwas2 = "";

			testfile>>random_bakwas>>random_bakwas2;
			int Door1Number;
			if(random_bakwas[1] == 'a')
			{
				Door1Number = stoi(random_bakwas.substr(2,1));
				Anti[Door1Number] = Anti[Door1Number] + 1;
				Door k1(Door1Number, true);
				rooms[i].door1 = k1;
			}
			else
			{
				Door1Number = stoi(random_bakwas.substr(1,1));
				notAnti[Door1Number] = notAnti[Door1Number] + 1;
				Door k2(Door1Number, false);
				rooms[i].door1 = k2;
			}

			int Door2Number;
			if(random_bakwas2[1] == 'a')
			{
				Door2Number = stoi(random_bakwas2.substr(2,1));
				if(Door1Number != Door2Number || random_bakwas2.length() != random_bakwas.length())
					Anti[Door2Number] = Anti[Door2Number] + 1;
				Door k3(Door2Number, true);
				rooms[i].door2 = k3;
			}
			else
			{
				Door2Number = stoi(random_bakwas2.substr(1,1));
				if(Door1Number != Door2Number || random_bakwas2.length() != random_bakwas.length())
					notAnti[Door2Number] = notAnti[Door2Number] + 1;
				Door k4(Door2Number, false);
				rooms[i].door2 = k4;
			}

			rooms[i].opened = false;
			

		}

		for(int i = 0; i < total_number_of_rooms; i++)
		{
			if(rooms[i].opened == false && rooms[i].door1.number == rooms[i].door2.number && rooms[i].door1.anti == rooms[i].door2.anti)
			{
				rooms[i].opened = true;
				bool find = false;
				for(int j = 0; j < ans.size(); j++)
				{
					if(rooms[i].door1.number == ans[j].number)
					{
						find = true;
						break;
					}
				}

				if(find == false)
				{
					ans.push_back(rooms[i].door1);
				}
				if(rooms[i].door1.anti == true)
				{
					if(Anti[rooms[i].door1.number] > 0)
					{
						Anti[rooms[i].door1.number] -= 1;
					}

					notAnti[rooms[i].door1.number] = 0;
				}
				else
				{
					if(notAnti[rooms[i].door1.number] > 0)
					{
						notAnti[rooms[i].door1.number] -= 1;
					}

					Anti[rooms[i].door1.number] = 0;
				}
				countt--;
			}
		}

		priority_queue<Door, vector<Door>, compareD> doors;
		for(int i = 0; i < total_number_of_labels; i++)
		{
			Door k1(i, notAnti[i], false);
			doors.push(k1);
			Door k2(i, Anti[i], true);
			doors.push(k2);
		}

		bool check = true;
		
		bool noAnswer = false;
		bool wentIn = false;
		while(countt > 0)
		{
			wentIn = true;
			priority_queue<Door, vector<Door>, compareD> doors;
			for(int i = 0; i < total_number_of_labels; i++)
			{
				Door k1(i, notAnti[i], false);
				doors.push(k1);
				Door k2(i, Anti[i], true);
				doors.push(k2);
			}

			Door topmost = doors.top();
			if(topmost.count == 0)
			{
				noAnswer = true;
				break;
			}
			ans.push_back(topmost);
			check = false;
			
			for(int i = 0; i < total_number_of_rooms; i++)
			{
				if(rooms[i].opened == false && rooms[i].door1.number == topmost.number && rooms[i].door1.anti == topmost.anti)
				{
					rooms[i].opened = true;
					countt--;
					if(rooms[i].door1.anti == true)
					{
						if(Anti[rooms[i].door1.number] > 0)
							Anti[rooms[i].door1.number] -= 1;
						notAnti[rooms[i].door1.number] = 0;
					}
					else
					{
						if(notAnti[rooms[i].door1.number] > 0)
							notAnti[rooms[i].door1.number] -= 1;
						Anti[rooms[i].door1.number] = 0;
					}

					
					if(rooms[i].door2.anti == true)
					{
						if(Anti[rooms[i].door2.number] > 0)
							Anti[rooms[i].door2.number] -= 1;
					}
					else
					{
						if(notAnti[rooms[i].door2.number] > 0)
							notAnti[rooms[i].door2.number] -= 1;
					}
					check = true;

				}
				else if(rooms[i].opened == false && rooms[i].door2.number == topmost.number && rooms[i].door2.anti == topmost.anti)
				{
					rooms[i].opened = true;
					countt--;
					if(rooms[i].door2.anti == true)
					{
						if(Anti[rooms[i].door2.number] > 0)
							Anti[rooms[i].door2.number] -= 1;
						notAnti[rooms[i].door2.number] = 0;
					}
					else
					{
						if(notAnti[rooms[i].door2.number] > 0)
							notAnti[rooms[i].door2.number] -= 1;
						Anti[rooms[i].door2.number] = 0;
					}

					
					if(rooms[i].door1.anti == true)
					{
						if(Anti[rooms[i].door1.number] > 0)
							Anti[rooms[i].door1.number] -= 1;
					}
					else
					{
						if(notAnti[rooms[i].door1.number] > 0)
							notAnti[rooms[i].door1.number] -= 1;
					}
					check = true;
				}
			}
		}


		
		if(noAnswer == true || wentIn == false)
		{
			answer += "No\n";
		}
		else
		{
			answer += "Yes\n";
			for(int i = 0; i < total_number_of_labels; i++)
			{
				bool c = false;
				for(int j = 0; j < ans.size(); j++)
				{
					if(ans[j].number == i && ans[j].anti == false)
					{
						c = true;
					}

				}

				if(c == true)
				{
					answer += "1\n";
				}
				else if(c == false)
				{
					answer += "0\n";
				}
			}
		}

	}
	cout<<answer;

}