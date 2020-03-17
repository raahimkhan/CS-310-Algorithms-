/**WORKING OF ALGORITHM**/

/*I have used the concept of depth first search to visit each node. When visiting a node or vertex
I assign two values to it : 1) time when that vertex was discovered 2) low value which basically indicates
whether some early vertex exixts or not that can be visited by the subtree rooted with that node and it is
based on discovery time. Basically checks if any alternate way. So for instance just as an example we have
1 2 3 .. n vertices connected graph. discovery time and low value of 1 would be 1. For 2 it will be 2 and so 
on and we keep doing this until we reach some vertex which has no further connected nodes. Here we do 2 things
Firstly we compare low values of node with dead end and the node before it and assign min value to node
that comes before. Secondly, we compare low value of node with dead end with discovery time of node before
it. Now this decides whether the edge connecting both nodes is a cut edge or not.*/

/**DATA STRUCTURES USED**/

/*classes to represent edges and graph. Vector to store strings for concatenation and a list
to represent adjacency list representation of graph*/

/**TIME COMPLEXITY**/

/*This algorithm runs in linear time. Complexity of dfs is O(v+e) where v are number of vertices and e is number
of edges and since e=v-1 complexity becomes O(2v-1) = O(v). Traversal of adjacency list takes O(v+e) time in the
worst case. Rest of the if statements are primitive operations and hence take constant time. So overall complexity
is O(v).*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <list>
using namespace std ;

string final ; // variable to concat all the cut edges (if any) as a string

vector <string> e ; // vector of all the strings (cut edges) if any

class edge
{
    public:
        int src , dest ;
} ;

class graph
{
    public:
		int vertices ;

		list <int> *adjacency_list ;

        graph(int vertices)
        {
			this -> vertices = vertices ;
			adjacency_list = new list<int>[vertices] ; 
		}

		void create_graph(vector <edge*> edges)
		{
			for (auto &edge: edges)
            {
				adjacency_list[edge -> src].push_back(edge -> dest) ; 
            }
		} 
} ;

int Min(int a , int b)
{
	if (a < b)
		return a ;

	else
		return b ;
}

//d_time = discoverty_time and to_visit = vertex to be visited 
void dfs(graph g , int to_visit , vector <bool> &visited , vector <int> &d_time , vector <int> &l_v
, vector <int> &ancester , int &cut_edges , int& visit_time) 
{
	visited[to_visit] = true ; // mark the currently being visited node as visited
	d_time[to_visit] = l_v[to_visit] = ++visit_time ; /* if first node then time and low would be 1
	then 2 3 and so on will be updated accordingly once we reach a node with no further
	connections*/

	list<int>::iterator itr ; 

	for (itr = g.adjacency_list[to_visit].begin() ; itr != g.adjacency_list[to_visit].end() ; ++itr) 
	{ 
		int neighbor = *itr ; 

		if (!visited[neighbor]) 
		{ 
			ancester[neighbor] = to_visit ; 

			// now recursively call helper on every vertex (dfs traversal)
			dfs(g , neighbor , visited , d_time , l_v , ancester , cut_edges , visit_time) ; 

			/*Check if the subtree rooted with current_adjacent has a 
			connection to one of the ancestors of to_visit (backtrack/alternate way)*/ 
			l_v[to_visit] = Min(l_v[to_visit], l_v[neighbor]) ; 

			/*If the lowest vertex reachable from subtree 
			under current_adjacent is below to_visit in dfs tree, then bridge has been found*/
			if (d_time[to_visit] < l_v[neighbor]) 
			{
				final = "(" + to_string(to_visit) + "," + to_string(neighbor) + ")" + "\n" ;
				e.push_back(final) ;
				cut_edges++ ; 
			}
		} 

		else if (neighbor != ancester[to_visit]) 
			l_v[to_visit] = Min(l_v[to_visit], d_time[neighbor]) ; // Update low value of to_visit 

		else
			continue ;  
	} 
}

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

int main(int argc, char** argv)
{
	vector <edge*> edges ;  
    char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , vertices ;
    fin >> trash >> vertices ; 
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
                initial = str_to_int(ptr) ;
            }

            else
            {
                final = str_to_int(ptr) ;
            }

            check = true ;

            if (flag == false)
            {
                // do nothing
            }

            else
            {
                edge *new_edge = new edge ;
                new_edge -> src = initial ;
                new_edge -> dest = final ;

                edges.push_back(new_edge) ;
            }

            ptr = strtok(NULL , " :") ;

            flag = true ;
        }

        flag = false ;
    }

    fin.close() ;

    int n = str_to_int(vertices) ;

	graph g(n) ;
	g.create_graph(edges) ;

	vector <bool> visited ; // tracks visited vertices
	visited.assign(n,false) ;
	
	vector <int> d_time(n) ; // time when a vertex was visited

	/*Low value indicates whether there's some early node (based on discovery_time
	that can be visited by the subtree rooted with that node*/
	vector <int> l_v(n) ; 
	
	vector <int> ancester ; // Parent vertices in the dfs tree
	ancester.assign(n,-1) ;

	int cut_edges = 0 ; // counter for number of vulnerable edges

	int to_visit = 0 ;
	int visit_time = 0 ; 

	while (to_visit < n)
	{
		if (visited[to_visit] == false)
		{
			dfs(g , to_visit , visited , d_time , l_v , ancester , cut_edges , visit_time) ; 
		} 

		to_visit += 1 ;
	}
	
	string final_ans = "" ; // final concatenated string to be output

	for (unsigned i = 0 ; i < e.size() ; i++)
	{
		final_ans = final_ans + e.at(i) ;
	}
	
	cout << cut_edges <<endl << final_ans ;

	return 0;
}
