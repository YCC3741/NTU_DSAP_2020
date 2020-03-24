#include <iostream>
#include <string>
#include <fstream>

using namespace std;
int main(){
    int training_set, actual_set;

    cin >> training_set >> actual_set;
    cin.ignore();

    int gender[training_set];
    for (int i=0 ; i<training_set ; i++){
        gender[i] = 0;
    }
    double word[training_set];
    for (int i=0 ; i<training_set ; i++){
        word[i] = 0;
    }

    int row_count = 0;
    int min_len = 10000, max_len = 0;
    int trian_run_num = training_set;

    /*training part: count every sentence words*/
    while( trian_run_num--){

        cin >> gender[row_count];
        cin.ignore();
        
        string temp_row;
        getline(cin, temp_row);
        int sentence = 0; // to record how many sentence in a row
        
        for(int pos=0 ; pos< temp_row.length() ; pos++){
            if (temp_row[pos] == ' ') word[row_count]++;
            else if(temp_row[pos] == ',' || temp_row[pos] == '.' || temp_row[pos] == '?' || temp_row[pos] == ';' || temp_row[pos] == '!'){
                word[row_count]++;
                pos++; // jump over the space after the dot
                sentence++;
            }
        }
        word[row_count] = word[row_count]/sentence;

        if (word[row_count] >= max_len) max_len = word[row_count]+1; //because max_len is int, so +1 to make sure it bigger that word[row_count]
        else if (word[row_count] <= min_len) min_len = word[row_count];

        row_count++;
    }

    /*training part: find out the best classifier*/
    int num_error = 0, best_error = training_set;
    int train_gender = 0;
    int best_classifier = min_len;
    for (int temp_classifier=min_len ; temp_classifier<=max_len ; temp_classifier++){
        for (int row=0 ; row<training_set ; row++){
            train_gender = word[row] >= temp_classifier ? 2 : 1;
            if (train_gender != gender[row]) num_error++;
        }
        
        if(num_error < best_error){
            best_classifier = temp_classifier;
            best_error = num_error;
        }
        num_error = 0;
    }

    /*testing part: count every sentence words*/
    int actual_run_num = actual_set;
    int actual_gender[actual_set];
    for (int i=0 ; i<actual_set ; i++){
        actual_gender[i] = 0;
    }
    double actual_word[actual_set];
    for (int i=0 ; i<actual_set ; i++){
        actual_gender[i] = 0;
    }

    row_count = 0;
    while( actual_run_num--){
        cin >> actual_gender[row_count];
        cin.ignore();

        string temp_row;
        getline(cin, temp_row);
        int sentence = 0; // to record how many sentence in a row
        
        for(int pos=0 ; pos< temp_row.length() ; pos++){
            if (temp_row[pos] == ' ') actual_word[row_count]++;
            else if(temp_row[pos] == ',' || temp_row[pos] == '.' || temp_row[pos] == '?' || temp_row[pos] == ';' || temp_row[pos] == '!'){
                actual_word[row_count]++;
                pos++; // jump over the space after the dot
                sentence++;
            }
        }
        actual_word[row_count] = actual_word[row_count]/sentence;
        row_count++;
    }

    /*testing part: count errors*/
    int actual_error = 0;
    int actual_train_outcome_gender = 0;
    for (int row=0 ; row<actual_set ; row++){
        actual_train_outcome_gender = actual_word[row] >= best_classifier ? 2 : 1;
        if (actual_train_outcome_gender != actual_gender[row]) actual_error++;
    }
    cout << best_classifier << "," << actual_error << "\n";
}