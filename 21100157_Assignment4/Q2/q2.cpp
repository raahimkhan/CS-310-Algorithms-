/*
	base cases : if (root == Null) {return 0}
				 if (leaf) {return 0}
				 if (only 1 vertex) {return 0}

	recurrence relation : lights(node, null) = 1 + min(lights(root, parent), lights(children, parent))

	What recurrence relation defines : It determines how many minimum lights we need to illuminate
									   all corridors

	Parameters that it takes : Start node and its parent

	Complexity : O(n) or O(V + E)

	Subproblems : n sub problems since there are n vertexes

	Time to solve each sub problem : O(1) due to memoization 
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

struct edge ;

struct node
{
	int value ;
	int lighted ;
	int parent ; 

	vector <edge> edges ;

	node()
	{	
		value = -1 ;
		lighted = 0 ;
		parent = -1 ;
	}

	node(int v)
	{
		parent = -1 ;
		value = v ;
		lighted = 0 ;
	}
} ;

vector <node*> nodes ; // contains all the nodes parent 0 to n along with edges

struct edge
{
	node *source ;
	node *dest ;

	edge()
	{
		source = NULL ;
		dest = NULL ;
	}

	edge(node *start, node *ending)
	{
		source = start ;
		dest = ending ;
	}
} ;

vector <node*> output ; // final ans

int lights(node *root, node *parent) ;

void include(node *root, node *parent, int &including)
{
	for (auto e : root -> edges)
	{
		if(e.dest != parent)
		{
			including += lights(e.dest, e.source) ;
		}
	}
}

int lights(node *root, node *parent) 
{
	if (root == NULL) // empty graph
		return 0 ;

	if (root -> parent == -1 && root -> edges.size() == 0) // if only one vertex
		return 0 ;

	// leaf nodes
	if (root -> edges.size() == 1 && parent)
		return 0 ;

	// memoization proved helful here!
	if (root -> lighted > 0)
		return root -> lighted ;

	// Case 1 
	int including = 1 ;

	include(root, parent, including) ;

	// Case 2
	int excluding = 0 ;

	for (auto e : root -> edges)
	{
		bool truth = e.dest != parent ;
		if (truth == true) 
		{
			excluding += 1 ;

			for (auto c : e.dest -> edges)
			{
				bool truth2 = e.source != c.dest ;
				if (truth2 == true) 
				{
					excluding += lights(c.dest, c.source) ;
				}
			}
		}	
	}

	if (including > excluding)
		root -> lighted = excluding ;

	else
	{
		root -> lighted = including ;
		output.push_back(root) ;
	}

	return root -> lighted ;
} ;

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , v ;
    fin >> trash >> v ;
	int vertices = stoi(v) ;

	for (int i = 0; i < vertices ; i++)
	{
		node *temp = new node(i) ;
		nodes.push_back(temp) ;
	}

	string line ;
	
    bool check , flag = false ;
    int initial , final ;
    while (getline(fin , line))
    {
        int n = line.length() ;
        char arr[n+1] ;
        strcpy(arr , line.c_str()) ; 
        check = false ;
        char *ptr ;
        ptr = strtok(arr , " :") ;
 
        while (ptr != NULL)
        {
            if (check == false)
            {
                initial = stoi(ptr) ;
            }

            else
            {
                final = stoi(ptr) ;
            }

            check = true ;

            if (flag == false)
            {
                // do nothing
            }

            else
            {
				node *d = new node ;

				for (int i = 0; i < nodes.size(); i++) // finding destination node
				{
					if (nodes[i] -> value == final)
					{
						d = nodes[i] ;
						break ;
					}
				}

				edge e(nodes[initial], d) ; // edge between src and dest

				nodes[initial] -> edges.push_back(e) ;
            }

            ptr = strtok(NULL , " :") ;

            flag = true ;
        }

        flag = false ;
    }

    fin.close() ;

	node *root = nodes[0] ;
	
	int ans = lights(root, NULL) ;

	string out = "" ;

	out = out + "Minimum Lights " + to_string(ans) + "\n" + "{" ;

	for (int i = 0 ; i < output.size() ; i++)
	{
		int v = output[i] -> value ;

		if (i == output.size() - 1)
			out = out + to_string(v) + "}" + "\n" ;

		else
			out = out + to_string(v) + ", " ;
	}

	cout << out ;

	return 0 ;
}
