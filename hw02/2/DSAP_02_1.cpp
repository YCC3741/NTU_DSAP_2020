#include <iostream>
#include <string>

using namespace std;


void input_and_count(int run_num, int *gender, double *word){ //training part: input and count every sentence words
    int row_count = 0; // to count which row we are now at

    while( run_num--){
        cin >> gender[row_count]; //input the gender
        cin.ignore(); // to ignore the "\n"
        
        string temp_row ;
        getline(cin, temp_row);
        int sentence = 0; // to record how many sentence in a row
        
        for(int pos=0 ; pos< temp_row.length() ; pos++){
            bool is_puntutation = (temp_row[pos] == ',' || temp_row[pos] == '.' || temp_row[pos] == '?' || temp_row[pos] == ';' || temp_row[pos] == '!');
            bool last_element = (pos == temp_row.length()-1);
            if (temp_row[pos] == ' ') word[row_count]++;
            else if(!last_element && is_puntutation && temp_row[pos+1] == ' '){
                word[row_count]++;
                pos++; // jump over the space after the dot
                sentence++;
            }
            else if( last_element && is_puntutation ){
                word[row_count]++;
                sentence++;
            }
        }
        word[row_count] = word[row_count]/sentence; // calculate the average word by dividing total word by the sentences in the paragraph

        row_count++; // move to nest row
    }
}

int main(){
    int training_row_num, testing_row_num; // num of rows of training and testing set

    cin >> training_row_num >> testing_row_num;
    cin.ignore(); // to ignore the "\n" at the end of first line

    int *gender = new int [training_row_num]; // training set gender
    for (int i=0 ; i<training_row_num ; i++){ //initialise
        gender[i] = 0;
    }
    double *word = new double [training_row_num]; // training set word num
    for (int i=0 ; i<training_row_num ; i++){ //initialise
        word[i] = 0;
    }

    input_and_count(training_row_num, gender, word); // to input the training data and count the average word of sentence

    int min_len = 10000, max_len = 0; // make min_len large and max_len small, so that they can be replace
    for(int i=0; i<training_row_num ; i++){ // to reduce the range of possible classifier
        if (word[i] >= max_len) max_len = word[i]+1; //because max_len is int, so +1 to make sure it bigger that word[row_count]
        else if (word[i] <= min_len) min_len = word[i];
    }
    
    /*training part: find out the best classifier*/
    int num_error = 0, best_error = training_row_num; 
    int train_gender = 0;
    int best_classifier = min_len;
    for (int temp_classifier=min_len ; temp_classifier<=max_len ; temp_classifier++){
        for (int row=0 ; row<training_row_num ; row++){ // to count the num of error of each classifier
            train_gender = (word[row] >= temp_classifier) ? 2 : 1;
            if (train_gender != gender[row]) num_error++;
        }
        
        if(num_error < best_error){ // if the num of error of the now-considering value is smaller, we replace the best_classifier
            best_classifier = temp_classifier;
            best_error = num_error;
        }
        num_error = 0; //zeroing the num of error
    }

    /*testing part: count every sentence words*/
    int *testing_gender = new int [testing_row_num]; // testing set gender
    for (int i=0 ; i<testing_row_num ; i++){ //initialise
        testing_gender[i] = 0;
    }
    double *testing_word = new double [testing_row_num];// testing set word num
    for (int i=0 ; i<testing_row_num ; i++){ //initialise
        testing_word[i] = 0;
    }

    input_and_count(testing_row_num, testing_gender, testing_word); // to input the testing data and count the average word of sentence

    /*testing part: count errors*/
    int actual_error = 0;
    int testing_outcome_gender = 0;
    for (int row=0 ; row<testing_row_num ; row++){ // to count the num of error of testing data
        testing_outcome_gender = (testing_word[row] >= best_classifier) ? 2 : 1;
        if (testing_outcome_gender != testing_gender[row]){
            actual_error++;
        }
    }

    /*output part*/
    cout << best_classifier << "," << actual_error << "\n";
}