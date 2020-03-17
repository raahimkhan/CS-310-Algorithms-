/*DATA STRUCTURES USED*/
/*Queue and Adjacency List*/

/*ALGORITHM*/
/*This is almost the same algorithm as used in q3a with only slight modifications. The only
modification I made was that initially I put all nodes with indegrees = 0 in same row. Then
when the program calculates new nodes with indegrees 0 they are placed in next row and so on.
I also used a separator is just used to tell a program that all the nodes of a single row have 
been added.*/

/*COMPLEXITY*/
/*Complexity is the same as Q3a. i.e O(V)*/

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

struct obj
{
    int val ;
    int ind ;

    obj()
    {
        val = 0 ;
        ind = 0 ;
    }

    obj(int v , int i)
    {
        val = v ;
        ind = i ;
    }
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

void combine(int rows , string &finalans)
{
    stringstream ss ;
    ss << rows ;
    string rows_string = ss.str() ;
    finalans = "Yes\nR " + rows_string + "\n" + finalans + "\n" ;
}

void bfs(graph g , int vertices , queue <obj*> &q , vector <int> &in_d , string &finalans)
{
    int is_visited = 0 ;
    list<int>::iterator itr ;
    vector <obj*> levels ;

    obj *separator = new obj(-500 , -500) ;

    while (!q.empty())
    {
        obj *vertex_pointer = q.front() ;
        int vp = vertex_pointer -> val ;
        q.pop() ;
    
        if ((vertex_pointer -> val == -500) && (vertex_pointer -> ind == -500))
        {
			levels.push_back(vertex_pointer) ;
			continue ;
		}

		else
        {
			levels.push_back(vertex_pointer) ;
		}

		bool sep = false ;

        for(itr = g.adjacency_list[vp].begin() ; itr != g.adjacency_list[vp].end() ; ++itr)
        {
            int current = *itr ;
            --in_d[current] ;

            if (!sep)
            {
                if (in_d[current] == 0)
                {
                    q.push(separator) ;
                    obj *temp = new obj(current , in_d[current]) ;
                    q.push(temp) ;
                    sep = true ;
                }
            }

            else
            {
                if (in_d[current] == 0)
                {
                    obj *temp = new obj(current , in_d[current]) ;
                    q.push(temp) ;
                }
            }
        }

        is_visited += 1 ;
    }

    if (is_visited != vertices)
    {
        finalans = finalans + "No" + "\n" ;
    }
        
    else
    {
        int rows = 1 ;
        for (unsigned i = 0 ; i < levels.size() ; i++)
        {
            if ((levels[i]->val == -500) && (levels[i]->ind == -500))
            {
                rows += 1 ;
                finalans = finalans + "\n" ;
            }

            else
            {
                finalans = finalans + to_string(levels[i] -> val) + " " ;
            }
        }

        combine(rows , finalans) ;
    }
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

    queue <obj*> q2 ;

    int i = 0 ;
    while (i < n)
    {
        if (indegrees[i] == 0) 
        {
            obj *temp = new obj (i , indegrees[i]) ;
            q2.push(temp) ;
        }

        i++ ;
    }

    string finalans = "" ;

    bfs(g , n , q2 , indegrees , finalans) ;

    cout << finalans ;
         
    return 0; 
} 
