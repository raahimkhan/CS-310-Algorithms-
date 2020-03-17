/*I have used adjacency list (vector of vectors) to store edges and their weights. To find mst1
I implemented Kruskal's algorithm using a priority queue. This makes making of mst1 a complexity
of nlog(n). After removing edge I ran dfs on the resulting graph to find connected components
and found mst2. This operation takes linear time.*/

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
list <int> *mst1graph ;
list <int> *adj_list ;

void dfs(int v, bool visited[], bool &donefirst, vector <int> &comp1, vector <int> &comp2)
{
    visited[v] = true ;
    if (donefirst == false)
    {
        comp1.push_back(v) ;
    }
        
    else
    {
        comp2.push_back(v) ;
    }
        
    list<int>::iterator i ; 
    for(i = mst1graph[v].begin(); i != mst1graph[v].end(); ++i) 
        if(!visited[*i]) 
            dfs(*i, visited, donefirst, comp1, comp2) ; 
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

    mst1graph = new list <int> [n] ;
    
    string line ;

    int looper = 1 ; // to read till second last line of file

    bool check , flag = false ;
    int initial , final ;
    double weight ; 

    adj_list = new list <int> [n] ;
    vector <edge*> adj_list2 ;

    priority_queue<edge, vector<edge>, compare> graph ;
   
    vector <edge> vec ; // contains all edges i.e 1-2 and 2-1
    vector <edge> vec2 ; // contains only 1 way edges so no duplications

    while (getline(fin , line))
    {
        if (looper > n)
            break ;

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
        }
    }

    for (auto edge: adj_list2)
    {
        adj_list[edge -> source].push_back(edge -> destination) ;
    }
    
    getline(fin , line) ;
    string removed = line ;

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

    int removed_src = values[0] ;
    int removed_dest = values[1] ;

    edge removed_edge ;

    for (int i = 0 ; i < vec.size() ; i++)
    {
        if (vec[i].source == removed_src && vec[i].destination == removed_dest)
        {
            removed_edge = vec[i] ;
            break ;
        }
    }

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
    output = output + "Removed Edge: " + removed + "\n" ;

    /**First check if removed edge present in mst**/
    bool truth = find_edge(removed_src, removed_dest, mst1) ;

    if (truth == false)
    {
        output = output + "MST2: " ;

        for (int i = 0 ; i < mst1.size() ; i++)
        {
            if (i == mst1.size() - 1)
                output = output + "(" + to_string(mst1[i].source) + "," + to_string(mst1[i].destination) + ")" + "\n" ;

            else
                output = output + "(" + to_string(mst1[i].source) + "," + to_string(mst1[i].destination) + ") " ; 
        }   

        output = output + "Sum MST2: " + to_string(total_weight) ;
    }

    else
    {
        vector <edge*> mst1without ;  
        vector <edge> mst2 ;
        for (int i = 0 ; i < mst1.size() ; i++)
        {
            if ((mst1[i].source == removed_edge.source && mst1[i].destination == removed_edge.destination) || (mst1[i].source == removed_edge.destination && mst1[i].destination == removed_edge.source))
                continue ;

            else
            {
                mst2.push_back(mst1[i]) ;
                edge *new_edge = new edge ;
                new_edge -> source = mst1[i].source ;
                new_edge -> destination = mst1[i].destination ;
                new_edge -> weight = mst1[i].weight ;
                mst1without.push_back(new_edge) ;
            }
        }
    
        for (auto edge: mst1without)
        {
            mst1graph[edge -> source].push_back(edge -> destination) ;
            mst1graph[edge -> destination].push_back(edge -> source) ; 
        }

        vector <int> comp1 ;
        vector <int> comp2 ;
        bool donefirst = false ;

        bool *visited = new bool[n] ; 
        for(int i = 0 ; i < n ; i++) 
            visited[i] = false ;

        for (int i = 0 ; i < n ; i++) 
        { 
            if (visited[i] == false) 
            { 
                dfs(i, visited, donefirst, comp1, comp2) ; 
    
                donefirst = true ;
            } 
        }  

        int total_weight2 = 0 ;

        int comp_weight = 9999 ;

        int comp2size = comp2.size() ;
        int m = 0 ;
        int added_src ;
        int added_dest ;
    
        for (int i = 0 ; i < comp1.size() ; i++)
        {   
            for(auto itr = adj_list[comp1[i]].begin() ; itr != adj_list[comp1[i]].end() ; ++itr)
            {
                added_src = comp1[i] ;
                if (comp1[i] == removed_edge.source && *itr == removed_edge.destination)
                {
                    continue ;
                }

                int crappy = *itr ;
                if (find(comp2.begin(), comp2.end(), crappy) != comp2.end())
                {
                    added_dest = crappy ;
                    int ww = find_weight(comp1[i], crappy, vec) ;
                    if (ww <= comp_weight)
                        comp_weight = ww ;
                }

                else
                    continue ;
            } 
        }

        total_weight2 = total_weight - removed_edge.weight + comp_weight ;
        edge added_edge ;
        added_edge.weight = comp_weight ;
        added_edge.source = added_src ;
        added_edge.destination = added_dest ;

        mst2.push_back(added_edge) ;

        output = output + "MST2: " ;

        for (int i = 0 ; i < mst1.size() ; i++)
        {
            if (i == mst2.size() - 1)
                output = output + "(" + to_string(mst2[i].source) + "," + to_string(mst2[i].destination) + ")" + "\n" ;

            else
                output = output + "(" + to_string(mst2[i].source) + "," + to_string(mst2[i].destination) + ") " ; 
        }   

        output = output + "Sum MST2: " + to_string(total_weight2) ;

    }

    cout << output ;

    return 0 ; 
} 
