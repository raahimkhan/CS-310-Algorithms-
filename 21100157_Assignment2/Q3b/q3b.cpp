/*I have used adjacency list (vector of vectors) to store edges and their weights. To find mst1
I implemented Kruskal's algorithm using a priority queue. This makes making of mst1 a complexity
of nlog(n). After adding an edge I ran dfs on the resulting graph to find a cycle and just removed
the edge from cycle having max weight to get mst2. This operation took linear time.*/

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

struct edge
{
    int source ;
    int destination ;
    double weight ;

    edge()
    {
        source = -1 ;
        destination = -1 ;
        weight = -1 ;
    }

	edge(int s, int d)
    {
        source = s ;
        destination = d ;
        weight = -1 ;
    }

    edge(int s, int d, double w)
    {
        source = s ;
        destination = d ;
        weight = w ;
    }
} ;

struct compare
{
	bool operator()(edge const& e1, edge const& e2) 
	{ 
        return e1.weight > e2.weight ;
    }
} ;

int str_to_int(string str)
{
    stringstream convert(str) ;
    int x = 0 ;
    convert >> x ;
    return x ;
}

struct Set  
{   
    int parent ;  
    int rank ;  
} ;  

int find(Set sets[], int i)  
{  
    int p = sets[i].parent ;
    if (p != i)  
        p = find(sets, p) ;  
  
    return p ;  
}

void Union(Set sets[], int x, int y)  
{  
    int xr = find(sets, x) ;  
    int yr = find(sets, y) ;  
  
    if (sets[xr].rank < sets[yr].rank)  
        sets[xr].parent = yr ;  
        
    else if (sets[xr].rank > sets[yr].rank)  
        sets[yr].parent = xr;  

    else
    {  
        sets[yr].parent = xr ;  
        sets[xr].rank++ ;  
    }  
} 

int n ;
list <int> *adj_list ;
list <int> *mst2graph ;
vector <int> vec1 ;
vector <int> vec22 ;
vector <edge> c_edg ; // cyclic edges

void find_cycle(int vertices)
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
    //int cycle_counter = 0 ;

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
        f : for(itr = mst2graph[source_vertex].begin() ; itr != mst2graph[source_vertex].end() ; ++itr)
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

                    vec22.push_back(parenttraceback) ;
            
                    if (parenttraceback != newdest)
                    {
                        newsource = parenttraceback ;
                        goto t ;
                    }

                    cycle_found = true ;
					break ;
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

int find_weight(int x, int y, vector <edge> edges)
{
    for (int i = 0 ; i < edges.size() ; i++)
    {
        if (edges[i].source == x && edges[i].destination == y)
            return edges[i].weight ;
    }
}

bool find_edge(int x, int y, vector <edge> edges)
{
    for (int i = 0 ; i < edges.size() ; i++)
    {
        if ((x == edges[i].source && y == edges[i].destination) || (x == edges[i].destination && y == edges[i].source))
            return true ;
    }

    return false ;
}

int main(int argc, char** argv) 
{ 
    char *f = argv[1] ;
    ifstream fin(f) ;

    string trash , vertices ;
    fin >> trash >> vertices ; 

    n = str_to_int(vertices) ;

    string line ;

    int looper = 1 ; // to read till second last line of file

    bool check , flag = false ;
    int initial , final ;
    double weight ; 
   
    priority_queue<edge, vector<edge>, compare> graph ;
    vector <edge> vec ; // contains all edges i.e 1-2 and 2-1
	vector <edge> vec2 ; // contains only 1 way edges so no duplications

	adj_list = new list <int> [n] ;
    vector <edge*> adj_list2 ;
	string parts ;

    while (getline(fin , line))
    {
        if (looper > n+1)
		{
			parts = line ;
			break ;
		}

        else
        {
            int n = line.length() ;
            char arr[n+1] ;
            strcpy(arr , line.c_str()) ; 
            check = false ;
            char *ptr ;
            ptr = strtok(arr , " :;") ;
    
            while (ptr != NULL)
            {
                if (check == false)
                {
                    initial = str_to_int(ptr) ;
                }

                else
                {
                    final = str_to_int(ptr) ;
                    ptr = strtok(NULL , " :;") ;
            
                    istringstream ss(ptr) ;
                    ss >> weight ;
                }

                check = true ;

                if (flag == false)
                {
                    // do nothing
                }

                else
                {
                    edge new_edge(initial, final, weight) ;

                    vec.push_back(new_edge) ;

					edge *new_edge2 = new edge ;
                    new_edge2 -> source = initial ;
                    new_edge2 -> destination = final ;
                    new_edge2 -> weight = weight ;
                    adj_list2.push_back(new_edge2) ;
                }

                ptr = strtok(NULL , " :;") ;

                flag = true ;
            }

            flag = false ;

			looper++ ;
        }
    }

	for (auto edge: adj_list2)
    {
        adj_list[edge -> source].push_back(edge -> destination) ;
    }

	string part1 , part2 , part3 ;
	int o = 0 ;

	stringstream iss(parts) ;

	while (iss >> part3) 
	{
		if (o == 1)
			part2 = part3 ;

		else
			part1 = part3 ;

		o++ ;
	}

	int added_weight = str_to_int(part2) ;

    string removed = part1 ;

    char line5[removed.length()] ;
    for (int i = 0 ; i < removed.length() ; i++)
        line5[i] = removed[i] ;

    line5[0] = ' ' ;
    line5[removed.length()-1] = ' ' ;
    char separator = ' ' ;
    char* tok4 = strtok(line5, &separator) ;
    char* tok5 = tok4 ;

    char separator2 = ',' ;
    tok5 = strtok(tok5, &separator2) ;
    vector <int> values ;

    while(tok5 != NULL)
    {
        values.push_back(atoi(tok5)) ;
        tok5 = strtok(NULL, &separator2) ;
    }

    int added_src = values[0] ;
    int added_dest = values[1] ;

    edge added_edge(added_src, added_dest, added_weight) ;

    bool yes = false ;

    for (int i = 0 ; i < vec.size() ; i++)
    {
        edge h = vec[i] ;
        for (int i = 0 ; i < vec2.size() ; i++)
        {
            if (vec2[i].destination == h.source && vec2[i].source == h.destination && vec2[i].weight == h.weight)
            {
                yes = true ;
                break ;
            }
        }

        if (yes == false)
        {
            vec2.push_back(h) ;
        }

        yes = false ;
    }

    for (int i = 0 ; i < vec2.size() ; i++)
    {
        graph.push(vec2[i]) ;
    }

    fin.close() ;

    Set *sets = new Set[n] ;

    for (int i = 0 ; i < n ; ++i)  
    {  
        sets[i].parent = i ;  
        sets[i].rank = 0 ;  
    } 

    int e = 0 ; 
    int total_weight = 0 ;
    vector <edge> mst1 ;

    while (e < n - 1)
    {
        edge t = graph.top() ;
        
        int x = find(sets, t.source) ;  
        int y = find(sets, t.destination) ;

        if (x != y)  
        {
            e++ ;
            mst1.push_back(t) ;  
            total_weight = total_weight + t.weight ;
            Union(sets, x, y) ;  
        }  
        
        graph.pop() ;
    }

    string output = "" ;

    output = output + "MST1: " ;

    for (int i = 0 ; i < mst1.size() ; i++)
    {
        if (i == mst1.size() - 1)
            output = output + "(" + to_string(mst1[i].source) + "," + to_string(mst1[i].destination) + ")" + "\n" ;

        else
            output = output + "(" + to_string(mst1[i].source) + "," + to_string(mst1[i].destination) + ") " ; 
    }   

    output = output + "Sum MST1: " + to_string(total_weight) + "\n" ; 
    output = output + "Added Edge: " + removed + " " + to_string(added_weight) + "\n" ;

	// now for second mst

	vector <edge> mst2 ;
	vector <edge> mst22 ; // final second reconstructed mst
	vector <edge*> mstwith ; 
	for (int i = 0 ; i < mst1.size() ; i++)
	{
		mst2.push_back(mst1[i]) ;
		edge *new_edge = new edge ;
		new_edge -> source = mst1[i].source ;
		new_edge -> destination = mst1[i].destination ;
		new_edge -> weight = mst1[i].weight ;
		mstwith.push_back(new_edge) ;
	}

	mst2.push_back(added_edge) ;
	
	edge *new_edge3 = new edge ;
	new_edge3 -> source = added_edge.source ;
	new_edge3 -> destination = added_edge.destination ;
	new_edge3 -> weight = added_edge.weight ;
	mstwith.push_back(new_edge3) ;

	mst2graph = new list <int> [n] ;
	
	for (auto edge: mstwith)
	{
		mst2graph[edge -> source].push_back(edge -> destination) ;
		mst2graph[edge -> destination].push_back(edge -> source) ; 
	}

	find_cycle(n) ;

	reverse(begin(vec22) , end(vec22)) ; 

	for (int i = 0 ; i < vec1.size() ; i++)
	{
		vec22.push_back(vec1[i]) ;
	}

	for (int i = 0 ; i < vec22.size() ; i++)
	{
		if (i == vec22.size() - 1)
			continue ;

		else
		{
			edge eee(vec22[i], vec22[i+1]) ;
			c_edg.push_back(eee) ;
		}
	}

	int max = -9999 ;
	edge eeee ; // max weight edge
	int ww ;

	for (int i = 0 ; i < c_edg.size() ; i++)
	{
		bool milgai = find_edge(c_edg[i].source, c_edg[i].destination, vec) ;
		if (milgai == false)
			ww = added_weight ;
		else
			ww = find_weight(c_edg[i].source, c_edg[i].destination, vec) ;
		if (ww >= max)
		{
			eeee.source = c_edg[i].source ;
			eeee.destination = c_edg[i].destination ;
			max = ww ;
		}
	}

	for (int i = 0 ; i < mst2.size() ; i++)
	{
		if ((mst2[i].source == eeee.source && mst2[i].destination == eeee.destination) || (mst2[i].source == eeee.destination && mst2[i].destination == eeee.source))
			continue ;
		else
			mst22.push_back(mst2[i]) ;
	}

	int total_weight2 = total_weight + added_weight - max ;

	output = output + "MST2: " ;

    for (int i = 0 ; i < mst22.size() ; i++)
    {
        if (i == mst22.size() - 1)
            output = output + "(" + to_string(mst22[i].source) + "," + to_string(mst22[i].destination) + ")" + "\n" ;

        else
            output = output + "(" + to_string(mst22[i].source) + "," + to_string(mst22[i].destination) + ") " ; 
    }   

    output = output + "Sum MST2: " + to_string(total_weight2) ;

   	cout << output ;

    return 0 ; 
} 
