/*
First I made a bst by inserting nodes level wise. This took linear time. After this I found
the leaf node whose ancestory gives maximum value. This also takes linear time since we are
traversing from root to leaf and there are n nodes so O(n).
Next I traversed the leaves excluding the one whose ancestory is maximum and made union of each
of the other leaves ancestory with this maximum one and checked which gives the highest value.
This also runs in linear time.

Hence running time is O(n)

Recurrence relation :
T(1) = b
T(n) = 2T(n/2) + c
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <sstream> 
#include <numeric>   
#include <list>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std ;

int ind = 0 ; // for storing positions of elements in the tree starting from 0

struct node  
{
	int value ;
	int index ;
	int leaf_number ; 
	struct node *left ; 
	struct node *right ;

	node()
	{
		value = -1 ;
		leaf_number = -1 ;
		left = NULL ;
		right = NULL ;
	}

	node(int v, int l_n)
	{
		value = v ;
		leaf_number = l_n ;
		left = NULL ;
		right = NULL ;
	}
} ;

vector <node> nodeleafs ; // to store nodes that are leafs
vector <node> allnodes ; // leafs + nonleaf nodes
vector <node> nonleafs ; // to store nodes that are non-leafs

queue <node*> helper ; // to store children etc for level order insertions
node *root = NULL ; // tree initially empty

vector <int> nonleaf ; // non leaf nodes  (values only)
vector <int> leaf ; // leaf nodes = 2^height (values only)

int difference ;
int isleaf = 0 ; // separator to identify leaf nodes from non leaf nodes
int leaf_number = 1 ; // for numbering the leafs from 1 to 2^h

void tree(int val) // function to insert in bst level wise
{
	if (isleaf >= difference) // insertion of leaf nodes
	{
		node *temp = new node ;
		temp -> value = val ;
		temp -> index = ind ;
		temp -> leaf_number = leaf_number ;

		node tmp ;
		tmp.value = val ;
		tmp.index = ind ;
		tmp.leaf_number = leaf_number ;
		nodeleafs.push_back(tmp) ;

		allnodes.push_back(tmp) ;

		ind++ ;
		
		leaf_number++ ;

		if (root == NULL)
			root = temp ;

		else if (helper.front() -> left == NULL)
			helper.front() -> left = temp ;

		else
		{
			helper.front() -> right = temp ;
			helper.pop() ;
		}

		helper.push(temp) ;
	}

	else // insertion of nonleaf nodes
	{
		node *temp = new node ;
		temp -> value = val ;
		temp -> index = ind ;

		node tmp ;
		tmp.value = val ;
		tmp.index = ind ;
		allnodes.push_back(tmp) ;

		nonleafs.push_back(tmp) ;

		ind++ ;

		if (root == NULL)
			root = temp ;

		else if (helper.front() -> left == NULL)
			helper.front() -> left = temp ;

		else
		{
			helper.front() -> right = temp ;
			helper.pop() ;
		}

		helper.push(temp) ;
	}

	isleaf++ ;
}

// finds ancestors of a given node at given position
bool anc(struct node *root, int val, vector <node*> &vec, int &sum, int pos) 
{
	if (root == NULL)
		return false ;

	if (root -> value == val && root -> index == pos)
	{
		vec.push_back(root) ;
		sum = sum + root -> value ;
		return true ;
	}

	if (anc(root->left, val, vec, sum, pos) || anc(root->right, val, vec, sum, pos)) 
	{ 
		vec.push_back(root) ;
		sum = sum + root -> value ;
		return true ; 
	} 

	return false ;
}

set <pair<int, int>> union_temp ; // helper set containing union of 2 leaf nodes

bool Union(struct node *root, int val, int pos) 
{
	if (root == NULL)
		return false ;

	if (root -> value == val && root -> index == pos)
	{
		pair<int, int> t ;
		t.first = root -> value ;
		t.second = root -> index ;
		union_temp.insert(t) ;
		return true ;
	}

	if (Union(root->left, val, pos) || Union(root->right, val, pos)) 
	{ 
		pair<int, int> t ;
		t.first = root -> value ;
		t.second = root -> index ;
		union_temp.insert(t) ;
		return true ; 
	} 

	return false ;
}

int set_sum(int &sum)
{
	for (auto const &x : union_temp)
	{
		sum = sum + x.first ;
	}

	return sum ;
}

int main(int argc, char** argv)
{
	char *f = argv[1] ;
    ifstream fin(f) ;
    string trash , useful ;
    fin >> trash >> useful ;
	int height = stoi(useful) ; 
	int leaves = pow(2, height) ;
	
    string line ;

	getline(fin, line) ;
    getline(fin, line) ;

	string extract ;

	stringstream iss(line) ;

	vector <int> arr ; // for level wise insertions in tree

	while (iss >> extract) 
	{
		arr.push_back(stoi(extract)) ;
	}

	difference = arr.size() - leaves ;

	int flag = 0 ;

	for (int i = 0 ; i < arr.size() ; i++) // separating non-leaf and leaf nodes
	{
		if (flag >= difference) // last 2^h nodes are leaves
		{
			leaf.push_back(arr[i]) ;
		}

		else
		{
			nonleaf.push_back(arr[i]) ;
		}

		flag++ ;
	}

	int start = 0 ;
	while(start < arr.size())
	{
		int value = arr[start] ;
		tree(value) ; // create tree from given values level wise 
		start++ ;
	}

	// Now find ancestors of leaf nodes (leaf is ancestor of itself as well)

	vector<vector<node*> > all_anc ; // stores ancestors of every leaf node

	int max_number ; // leaf node with maximum ancestory value
	int max = 0 ; // value of ancestory that is maximum
	int sum = 0 ;

	for (int i = 0 ; i < leaf.size() ; i++)
	{
		vector <node*> store ;
		bool b = anc(root, leaf[i], store, sum, nodeleafs[i].index) ;

		if (sum > max)
		{
			max_number = i + 1 ;
			max = sum ;
			sum = 0 ;
		}

		all_anc.push_back(store) ; 
	}

	vector <node*> temporary ;

	// find ancestory of leaf with max ancestory value

	for (int i = 0 ; i < all_anc.size() ; i++)
	{
		if (i + 1 == max_number)
		{
			temporary = all_anc[i] ;
			break ;
		}

		else
			continue ;
	}

	for (int i = 0 ; i < nodeleafs.size() ; i++)
	{
		if ((temporary[1] -> value == nodeleafs[i].value) && (temporary[1] -> index == nodeleafs[i].index))
		{
			max_number = nodeleafs[i].leaf_number ;
			break ;
		}

		else
			continue ;
	}

	// Now create a set with maximum ancestory values
	
	set <pair<int, int>> max_number_ancestory ;

	for (int i = 0 ; i < temporary.size() ; i++)
	{
		pair<int, int> t ;	
		t.first = temporary[i] -> value ;
		t.second = temporary[i] -> index ;
		max_number_ancestory.insert(t) ;
	}

	// Now find which union with max ancestory gives the max union value

	int sum_union = 0 ;
	int sum_helper = 0 ;
	int max_number2 ; 

	for (int i = 0 ; i < leaf.size() ; i++)
	{
		if (i + 1 == max_number)
			continue ;

		else
		{
			union_temp = max_number_ancestory ;

			bool b2 = Union(root, leaf[i], nodeleafs[i].index) ;

			int sum_helper = 0 ;

			sum_helper = set_sum(sum_helper) ; // sums the values in set

			if (sum_helper > sum_union)
			{
				max_number2 = i + 1 ;
				sum_union = sum_helper ;
			}

			sum_helper = 0 ;
			union_temp.clear() ;
		}
	}

	// Ancestors of second leaf whose union with max ancestory gives max union value

	vector <node*> temporary2 ;

	for (int i = 0 ; i < all_anc.size() ; i++)
	{
		if (i + 1 == max_number2)
		{
			temporary2 = all_anc[i] ;
			break ;
		}

		else
			continue ;
	}

	// index of that second leaf

	for (int i = 0 ; i < nodeleafs.size() ; i++)
	{
		if ((temporary2[1] -> value == nodeleafs[i].value) && (temporary2[1] -> index == nodeleafs[i].index))
		{
			max_number2 = nodeleafs[i].leaf_number ;
			break ;
		}

		else
			continue ;
	}

	// max number 1
	// temporary
	// max number 2
	// temporary2

	string output = "" ;

	if (max_number < max_number2)
	{
		output = output + "(xi,xj) = " + "(x" + to_string(max_number) + "," + "x" + to_string(max_number2) + ")" + "\n" ;  
		output = output + "Ancestry x" + to_string(max_number) + " = {" ;

		for (int i = 0 ; i < temporary.size() ; i++)
		{
			if (i == temporary.size() - 1)
				output = output + to_string(temporary[i] -> value) + "}" + "\n" ;
			else
				output = output + to_string(temporary[i] -> value) + ", " ;
		}

		output = output + "Ancestry x" + to_string(max_number2) + " = {" ;

		for (int i = 0 ; i < temporary2.size() ; i++)
		{
			if (i == temporary2.size() - 1)
				output = output + to_string(temporary2[i] -> value) + "}" + "\n" ;
			else
				output = output + to_string(temporary2[i] -> value) + ", " ;
		}

		output = output + "Value of Max Ancestry (x" + to_string(max_number) + ",x" + to_string(max_number2) + ") = " + to_string(sum_union) + "\n" ; 
	}

	else
	{
		output = output + "(xi,xj) = " + "(x" + to_string(max_number2) + "," + "x" + to_string(max_number) + ")" + "\n" ;  
		output = output + "Ancestry x" + to_string(max_number2) + " = {" ;

		for (int i = 0 ; i < temporary2.size() ; i++)
		{
			if (i == temporary2.size() - 1)
				output = output + to_string(temporary2[i] -> value) + "}" + "\n" ;
			else
				output = output + to_string(temporary2[i] -> value) + ", " ;
		}

		output = output + "Ancestry x" + to_string(max_number) + " = {" ;

		for (int i = 0 ; i < temporary.size() ; i++)
		{
			if (i == temporary.size() - 1)
				output = output + to_string(temporary[i] -> value) + "}" + "\n" ;
			else
				output = output + to_string(temporary[i] -> value) + ", " ;
		}

		output = output + "Value of Max Ancestry (x" + to_string(max_number2) + ",x" + to_string(max_number) + ") = " + to_string(sum_union) + "\n" ; 
	}

	cout << output ;

	return 0 ;
}