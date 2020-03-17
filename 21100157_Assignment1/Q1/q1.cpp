/*DATA STRUCTURES USED*/
/*I have used adjacency list to represent my graph and stack and queue for traversals*/

/*ALGORITHM*/
/*I have used bfs using a queue to traverse the vertices of the graph and as I traverse them
I assign colors to them (opposite colors to adjacent vertices) and if at any point a visited
vertex is encountered having same color as that of adjacent false is returned else true is returned.
For finding cycles I applied dfs using a stack assigning visited status to each node and if at any
point an already visited node is encountered from some source and that source is not its parent
then a cycle is encountered. Then we check if its odd. If yes we return that cycle else we keep popping
nodes and repeating the above procedure until odd cycle found*/

/*COMPLEXITY*/
/*BFS traversal runs in O(V+E) time since every node is visited once. And traversing adj list
takes O(V+E) time as well. Rest are just the for loops which run n+1 times hence in O(n) time so
overall complexity is O(V). Same is the logic for finding cycle using stack and DFS traversal. Hence
total complexity is linear*/


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

class edge
{
    public:
        int src , dest ;
} ;

vector <int> box1 ;
vector <int> box2 ;

class graph
{
    public:
		int vertices ;
        list <int> *adjacency_list ;
        
        graph(vector <edge*> edges , int vertices)
        {
			this -> vertices = vertices ;
			adjacency_list = new list<int>[vertices] ; 	

			for (auto &edge: edges)
            {
				adjacency_list[edge -> src].push_back(edge -> dest) ; 
            }
        }
} ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

bool bfs(graph g , int source , int vertices)
{
	bool *visited = new bool[vertices] ; 
	int *color = new int[vertices] ;
	list<int>::iterator itr ;

	for (int i = 0 ; i < vertices ; i++)
	{
		visited[i] = false ;
	}

	for (int i = 0 ; i < vertices ; i++)
	{
		color[i] = -1 ;
	}

	queue <int> q ;

	visited[source] = true ;
	color[source] = 0 ;

    q.push(source) ;
	
	while (!q.empty()) 
    {
		int vertex_pointer = q.front() ;

        if (color[vertex_pointer] == 0)
        {
            box1.push_back(vertex_pointer) ;
        }

        else
        {
            box2.push_back(vertex_pointer) ;
        }
				
		q.pop() ;

		for(itr = g.adjacency_list[vertex_pointer].begin() ; itr != g.adjacency_list[vertex_pointer].end() ; ++itr)
		{
			int curr_adjacent = *itr ;
			if(!visited[curr_adjacent])
            {
                visited[curr_adjacent] = true ;
				color[curr_adjacent] = !color[vertex_pointer] ;
                q.push(curr_adjacent) ;
            }

			else if(color[curr_adjacent] == color[vertex_pointer]) // if visited and same color of neighbour
			{ 	
				return false ;
			}
		}
	}

	return true ;
}

vector <int> vec1 ; // 4 0
vector <int> vec2 ;

void find_cycle(graph g , int vertices)
{
    bool *visited = new bool [vertices] ;
    int *parent = new int [vertices] ;

    for (int i = 0 ; i < vertices ; i++)
    {
        visited[i] = false ;
        parent[i] = -1 ;
    }

    stack <int> s ;
    list<int>::iterator itr ;
    int source_vertex ;
    bool cycle_found = false ;
    int cycle_counter = 0 ;

    repeat : for (int i = 0 ; i < vertices ; i++)
    {
        if (visited[i] == false)
        {
            visited[i] = true ;
            s.push(i) ;
            goto jump ;
        }
    }

    jump : while (!s.empty())
    {
        source_vertex = s.top() ;
        f : for(itr = g.adjacency_list[source_vertex].begin() ; itr != g.adjacency_list[source_vertex].end() ; ++itr)
        {
            int current_adjacent = *itr ;
            if (current_adjacent != parent[source_vertex])
            {
                if (!visited[current_adjacent])
                {
                    visited[current_adjacent] = true ;
                    parent[current_adjacent] = source_vertex ;
                    s.push(current_adjacent) ;
                    source_vertex = s.top() ;
                    goto f ;
                }

                else if (visited[current_adjacent] && parent[current_adjacent] == source_vertex)
                {
                    continue ;
                }

                else if (visited[current_adjacent] && parent[current_adjacent] != source_vertex) // cycle found
                {
                    int newsource = source_vertex ; // 4
                    int newdest = current_adjacent ; // 0
                    vec1.push_back(newsource) ;
                    vec1.push_back(newdest) ;

                    int parenttraceback ;

                    /*Now trace back steps until current_adjacent found*/
                    t : parenttraceback = parent[newsource] ;
                    vec2.push_back(parenttraceback) ;
            
                    if (parenttraceback != newdest)
                    {
                        newsource = parenttraceback ;
                        goto t ;
                    }

                    cycle_counter = 1 + (vec2.size() - 1) + 1 ;
                    
                    if (cycle_counter % 2 != 0)
                    {
                        cycle_found = true ;
                        break ;
                    }
                    
                    vec1.clear() ;
                    vec2.clear() ;
                    cycle_counter = 0 ;
                }
            }
            
            else
                continue ;
        }

        s.pop() ;

        if (cycle_found == true)
            break ;
    }

    if (cycle_found == false)
        goto repeat ;
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
    
    graph g(edges , n) ;

	bool bipartite = bfs(g , 0 , n) ;
	
	string finalans = "" ;
    string finalans2 = "" ;

    if (bipartite)
    {
        for (unsigned i = 0 ; i < box1.size() ; i++)
		{
			if (i == box1.size() - 1)
			{
				finalans = finalans + to_string(box1.at(i)) + " " + "\n" ;
			}

			else
			{
				finalans = finalans + to_string(box1.at(i)) + " " ;
			}
		}

        for (unsigned i = 0 ; i < box2.size() ; i++)
		{
			if (i == box2.size() - 1)
			{
				finalans = finalans + to_string(box2.at(i)) + " " + "\n" ;
			}

			else
			{
				finalans = finalans + to_string(box2.at(i)) + " " ;
			}
		}

        finalans2 = finalans2 + "Yes" + "\n" + finalans ;
    }

    else
    {
        find_cycle(g , n) ;
        reverse(begin(vec2) , end(vec2)) ; 
        for (unsigned i = 0 ; i < vec2.size() ; i++)
        {
            finalans = finalans + to_string(vec2.at(i)) + "->" ; 
        }

        for (unsigned i = 0 ; i < vec1.size() ; i++)
        {
            if (i == vec1.size() - 1)
            {
                finalans = finalans + to_string(vec1.at(i)) ;
            }

            else
            {
                finalans = finalans + to_string(vec1.at(i)) + "->" ;
            }
        }

        finalans2 = finalans2 + "no" + "\n" + finalans ;
    }

    cout << finalans2 ;


	return 0 ;
}
