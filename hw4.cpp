#include<iostream>
#include<fstream>
#include<cmath>
#include<string.h>
#include<vector>
#include<queue>
#include <stdlib.h>
#include <climits>
using namespace std;

double distance(float x1, float y1, float x2, float y2)
{
	return sqrt( pow(y2-y1, 2) + pow(x2-x1, 2) );
}


struct point{
		float x;
		float y;
		point(float a, float b) { x = a; y =b;}
	};


bool BFS (vector <vector<float> > graph , int s , int t ,int n , int path[], float d){

    bool visited[n];
	int i;
	for(i=0; i<n;i++)
		visited[i] = 0;
    std :: queue <int> q;
    q.push(s);
    visited[s] = true;
    path[s]=-1;

    while (!q.empty()){
        int y = q.front();
        q.pop();
        for (i = 0 ; i < n ; i++){
            if (visited[i]==false &&graph[y][i] <= d )
            {
                q.push(i);
                path[i] = y;
               visited[i] = 1;
            }
        }
    }

    return (visited[t] == true);
}

int randomindex( int k )
{ return(  rand() % k );
}

void quicksort(float *a, int length)
{  int i, j1, j2;
	float pivot, tmp;
   if(length>1)
     {  i = randomindex(length);
        pivot = a[i]; a[i] = a[length-1]; a[length-1] = pivot;
        j1 = 0; j2 = length-1;
        while(j1 < j2 )
	  {  for(; a[j1] < pivot ; j1++)
	        ;
 	     for(; a[j2] >= pivot && j2 > j1 ; j2-- )
	        ;
             if( j1 != j2 )
	       {  tmp = a[j1]; a[j1] = a[j2]; a[j2] = tmp;
               }
          }
        a[length-1] = a[j1]; a[j1] = pivot;
        quicksort( a, j1);
        quicksort( a +j1+1, length -j1 -1);
     }
}




int main(int argc, char* argv[])
{

	if(argc > 1)
		cout << "argv[1] = "<<argv[1]<<endl;
	else{
		cout<<"Nothing is entered...";
		return -1;
	}

	ifstream input(argv[1]);

	vector<string> a;
	string line;
	while(input>>line)
	{
		a.push_back(line);
	}
	input.close();

	vector<string> b;

	// get numbers out of string
	for(int i=0; i<a.size(); i++)
	{

		int l = a[i].length();
		b.push_back("");

		for(int j=1; j< l-1; j++)
		{
			if(a[i][j] != ',')
			{
				if(b.size() ==0)
					b[0] = b[0] + a[i][j];
				else
					b[b.size()-1] = b[b.size()-1] +a[i][j];

			}
			else
				b.push_back("");
		}
	}

	vector<point> bot; //vector that stores ALL coordinates

	for(int i=0; i<b.size(); i= i+2)
	{
		point p(stof(b[i]) ,stof(b[i+1]) );
		bot.push_back(p);
	}

	int n = bot.size();
	int num_of_distances = n*n;
	float edge[num_of_distances]; //array that stores all distance
	vector <vector<float> > graph;

	vector<float>	temp;

	for(int i=0; i<n; i++)
	{
			for(int j=0; j<n; j++)
			{
				float tmp = distance(bot[i].x,bot[i].y,bot[j].x,bot[j].y);
				edge[i* n+ j ] = tmp;
				temp.push_back(tmp);
			}
			graph.push_back( temp );
			temp.clear();
	}

	int path[n];
	quicksort(edge, num_of_distances);



	int begin = 0 , end = num_of_distances-1, mid;
	float bottleneck = INT_MAX;
	while(begin <= end )
	{
		mid = (begin + end)/2;
		//cout <<edge[mid]<<endl;
		if( BFS(graph, 0, 1, n, path, edge[mid]))
		{
			if(edge[mid] < bottleneck)
				bottleneck = edge[mid];
			end = mid - 1;
		}
		else{
				begin = mid +1;
			}
	}

	vector<int> result;
	for(int j = 1; j != 0; j= path[j])
	{
		int i= path[j];
		result.push_back(i);
	}

	for(int i=result.size()-1; i>=0; i--)
		cout<<"(" <<bot[result[i] ].x<<"," << bot[result[i] ].y <<")" <<endl;
	cout<<"(" <<bot[1].x<<"," << bot[1].y <<")" <<endl;

	cout << bottleneck<<endl;


	return 0;

}


