#include <iostream>
#include <vector> 
#include <climits>
using namespace std;



void adjacency_lists(vector < pair<int,int> > *list, int dot, int side)
{
    for (int i=0; i<dot; ++i) list[i].clear();
 
    int dot1, dot2, sidelen;   
    char comma1, comma2;
    
    while (side--){
        cin >> dot1 >> comma1 >> dot2 >> comma2 >> sidelen;
        //cout << dot1 << comma2 << dot2 << comma2 << sidelen;
        list[dot1-1].push_back( make_pair(dot2-1,sidelen) );
        list[dot2-1].push_back( make_pair(dot1-1,sidelen) );
        //cout << "\n"<< list[dot1-1][list[dot1-1].size()-1].first << ' ' << list[dot1-1][list[dot1-1].size()-1].second << "\n";
    }
        
}

void dijkstra(int dot, int root, vector < pair<int,int> > *list, int range, bool *flag_array){
    int shortest_dis[dot], parents[dot];
    bool visits[dot];

    for (int i=0; i<dot ; i++){
        shortest_dis[i] = INT32_MAX;
        visits[i] = false;
    }

    shortest_dis[root] = 0;
    parents[root] = root;

    for (int i=0 ; i<dot ; i++){
        int start_point = -1, end_point = -1, min = INT32_MAX; 
        for (int j=0 ; j<dot ; j++){
            if(!visits[j] && shortest_dis[j] < min){
                start_point = j;
                min = shortest_dis[j];
            }
        }

        if (start_point == -1) break;
        visits[start_point] = true;

        for(int i = 0 ; i<list[start_point].size() ; i++){
            int end_point = list[start_point][i].first;
            int testside_len = list[start_point][i].second;
            if(!visits[end_point] && shortest_dis[start_point]+testside_len < shortest_dis[end_point]){
               shortest_dis[end_point] =  shortest_dis[start_point]+testside_len;
               parents[end_point] = start_point;
            }
        }
    }
/*
    for (int i=0 ; i<dot ; i++){
        cout << shortest_dis[i] << " ";
    }
    */
    for (int i=0 ; i<dot ; i++){
        if(range - shortest_dis[i] >= 0 ) flag_array[i] = 1;
    }
    
}

int main(){
    int side = 0, dot = 0;
    char comma;
    cin >> dot >> comma >> side;

    vector < pair<int,int> > list[dot];
    adjacency_lists(list, dot, side);
/*
    for (int i=0 ; i<dot ; i++){
        for (int j=0 ; j<list[i].size() ; j++){
            cout << list[i][j].first << " " << list[i][j].second << ",";
        }
        cout << "\n";
    }
*/
    int site=0, range=0;
    cin >> site >> comma >> range;


    bool flag_array[dot];
    for (int i=0 ; i<dot ; i++){
        flag_array[i] = 0;
    }

    dijkstra(dot, --site, list, range, flag_array);

    int final_one = -1;
    for(int i=0 ; i<dot ; i++){ //find end element
        (flag_array[i]==1 && i != site) ? final_one = i : final_one = final_one;
    }
    if (final_one != -1){
        for(int i=0 ; i<dot ; i++){
            if (flag_array[i]==1 && i != site){
                cout << i+1 ;
                (i != final_one) ? cout << "," : cout <<"\n";
            }
        }
    }
    else{
        cout << "None\n";
    }

}