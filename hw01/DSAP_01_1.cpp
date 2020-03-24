#include <iostream>
#include <climits> 
using namespace std;

void test_len(int dot, int site, int range, int **map , bool flag_array[]){
    
    int row = site;
    for (int column=0 ; column<dot ; column++){//???

        bool change = 0;
        if (row > column){
            swap (row,column);
            change = 1;
        }

        /*
        for (int i=0 ; i<dot ; i++){
                for (int j=i ; j<dot ; j++){
                    cout << map[j][i] << ",";
                }
                cout << "\n";
            }
        for (int i=0 ; i<dot ;i++){
            cout << flag_array[i];
        }
        cout << "\n\n" << range << "\n\n";///??????
        */

        if (range - map[column][row] >= 0 && column != row){
            int findside_value = map[column][row];
            map[column][row] = INT_MAX;

            if(change == 1){
                swap(row,column);
            }
            flag_array[column] = 1;
            test_len(dot, column, range - findside_value, map, flag_array);
        }
        else if (change == 1 ){
            swap(row,column);
        }
        
    }

}

int main(){
    int side = 0, dot = 0;
    char comma;
    cin >> dot >> comma >> side;

    int **map = new int *[dot];
    for (int i=0 ; i<dot ; i++){ // dynamic map
        map[i] = new int [i];
    }
    for (int i=0 ; i<dot ; i++){ // initalise map
        for (int j=0 ; j<i ; j++){
            map[i][j] = INT_MAX;
        }
    }
    

    int dot1, dot2, sidelen;
    char comma1, comma2;
    while ( side-- ){              // input map
        cin >> dot1 >> comma1 >> dot2 >> comma2 >> sidelen;
        if (dot1 > dot2) swap(dot1,dot2);
        map[dot2-1][dot1-1] = sidelen;
    }


    int site=0, range=0;
    cin >> site >> comma >> range;
/*
    for (int i=0 ; i<dot ; i++){
        for (int j=i+1 ; j<dot ; j++){
             cout << map[j][i] <<",";
        }
        cout << "\n";
    }
    cout << "\n\n";
*/

    bool flag_array[dot];
    for (int i=0 ; i<dot ; i++){
        flag_array[i] = 0;
    }

    test_len(dot, site-1, range, map ,flag_array);
    //cout << "\n" << map[0][0] <<'\n';

    for(int i = 0; i < dot; i++) {
        delete [] map[i];
    }
    delete [] map; 

    int final_one = -1;
    for(int i=0 ; i<dot ; i++){ //find end element
        (flag_array[i]==1 && i != site-1) ? final_one = i : final_one = final_one;
    }
    if (final_one != -1){
        for(int i=0 ; i<dot ; i++){
            if (flag_array[i]==1 && i != site-1){
                cout << i+1 ;
                (i != final_one) ? cout << "," : cout <<"\n";
            }
        }
    }
    else{
        cout << "None\n";
    }

    

}