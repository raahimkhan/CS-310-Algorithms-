/*DATA STRUCTURES USED*/
/*Adjacency list , stack and queue*/

/*ALGORITHM*/
/*To check whether ordring is possible or not, I first compute indegrees of all the vertices and
then start bfs using queue with the vertex having indegree 0. Then pushing all the vertices one by
one into queue having indegree 0 as we progress. This way we get a linear ordering. And if there is
a cycle I compute it using 3 color algorithm I made. It is described with clear comments alongside its
code.*/

/*COMPLEXITY*/
/*In degrees are computed by traversing the adjacency list in O(V+E) time since it visits
every node and edge once. Overall complexity is O(V)*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <list>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std; 

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

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

void calculate_indegrees(graph g , int vertices , vector <int> &in_d)
{
    in_d.assign(vertices , 0) ; 

    int v = 0 ;
    list<int>::iterator itr ;
    while (v < vertices)
    {
        for(itr = g.adjacency_list[v].begin() ; itr != g.adjacency_list[v].end() ; ++itr)
        {
            int current = *itr ;
            in_d[current]++ ;
        }
        v++ ;
    }
}

vector <int> ordering ;

bool bfs(graph g , int vertices , queue <int> &q , vector <int> &in_d)
{
    int is_visited = 0 ;
    list<int>::iterator itr ;

    while (!q.empty())
    {
        int vertex_pointer = q.front() ;
        q.pop() ;
        ordering.push_back(vertex_pointer) ;

        for(itr = g.adjacency_list[vertex_pointer].begin() ; itr != g.adjacency_list[vertex_pointer].end() ; ++itr)
        {
            int current = *itr ;
            int temp = --in_d[current] ;
            if (temp == 0) 
                q.push(current) ; 
        }
        is_visited += 1 ;
    }

    if (is_visited != vertices)
        return false ;

    else
        return true ;
}

vector <int> vec1 ; // 4 0
vector <int> vec2 ;

void find_cycle(graph g , int vertices)
{
    bool cycle_found = false ;
    int *parent = new int [vertices] ;
    //bool *visited = new bool [vertices] ;

    /*1 for white (unvisited) 2 for gray (in process) 3 for black (explored fully)*/
    int *color = new int [vertices] ; 
    for (int i = 0 ; i < vertices ; i++)
        color[i] = 1 ; // all unvisited initially

    for (int i = 0 ; i < vertices ; i++)
        parent[i] = -1 ; 

    stack <int> s ;
    list<int>::iterator itr ;
    int source_vertex ;

    repeat : for (int i = 0 ; i < vertices ; i++)
    {
        if (color[i] == 1)
        {
            color[i] = 2 ;
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
            if (color[current_adjacent] == 1)
            {
                parent[current_adjacent] = source_vertex ;
                color[current_adjacent] = 2 ;
                s.push(current_adjacent) ;
                source_vertex = s.top() ;
                goto f ;
            }

            else if (color[current_adjacent] == 2)
            {
                int newsource = source_vertex ; // 4
                int newdest = current_adjacent ; // 0
                vec1.push_back(newsource) ;
                vec1.push_back(newdest) ;

                int parenttraceback ;

                /*Now trace back steps until current_adjacent found*/
                t : parenttraceback = parent[newsource] ;
                vec2.push_back(parenttraceback) ;
                if (parenttraceback == newdest)
                {
                    cycle_found = true ;
                    break ;
                }
                    
                else
                {
                    newsource = parenttraceback ;
                    goto t ;
                }
            }

            else if (color[current_adjacent] == 3)
                continue ;
        }

        color[source_vertex] = 3 ;
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

	graph g(n) ;
	g.create_graph(edges) ;

    vector <int> indegrees ;

    calculate_indegrees(g , n , indegrees) ;

    queue <int> q ;

    int i = 0 ;
    while (i < n)
    {
        if (indegrees[i] == 0) 
            q.push(i) ; 
        i++ ;
    }
    bool can_be_ordered = bfs(g , n , q , indegrees) ;

    string finalans = "" ;
    string finalans2 = "" ;

    if (can_be_ordered == false)
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
       
    else
    {
        for (unsigned i = 0 ; i < ordering.size() ; i++)
        {
            finalans = finalans + to_string(ordering.at(i)) + " " ;
        }

        finalans2 = finalans2 + "yes" + "\n" + finalans ;
    }

    cout << finalans2 ;
         
    return 0 ; 
} 
