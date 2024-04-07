#include <iostream>
#include <random>
#include <vector>
#include <cstdlib>
#include <fstream>

using namespace std;

void wordle_afis_start_menu() {
    cout <<endl<<"\tWelcome to Wordle!" << endl<<endl<< endl<<endl;
    cout<<"1. Add a word"<<endl;
    cout<<"2. Play Wordle"<<endl;
    cout<<"3. Exit"<<endl<<endl;
}

void press_any_key() {
    cout << "Press any key to continue...";
    cin.get();
    cin.get();
}

void delete_first_word() {
    string line;


    // we get the words from the first file, except the first line (the word that we will use) and put them in the second file
    ifstream fin("./files/words.txt"); 
    ofstream fout2("./files/secundary.txt"); 

    if (!fin|| !fout2) {
        cout << "Error opening file";
        return;
    }

    getline(fin, line); // Skip first line
    while (getline(fin, line)) {
        fout2 << line << endl;
    }
    fin.close();
    fout2.close();


    // we put the words from the second file in the first file
    ifstream fin2("./files/secundary.txt");
    ofstream fout("./files/words.txt"); 

    if (!fout || !fin2) {
        cout << "Error opening file";
        return;
    }

    while (getline(fin2, line)) {
        // cout<<line<<endl;
        fout << line << endl;
    }

    fout.close();
    fin2.close();
}

void first_command() {
        ofstream fout("./files/words.txt", ios::app);
        if (!fout) {
            cout << "Error opening file";
            return ;
        }

        string word;
    
        while(1) {

            cout << "Enter a word (tap \"e\"end enter to exit): ";
            cin >> word;

            if (word == "e") {
                break;
            }
            fout << word << endl;
            cout<<endl<<"Word added successfully! Do you want to add another word?  (y/n): ";
            char choice;
            cin >> choice;
            if (choice == 'n') {
                break;
            }
        }
        fout.close();
}


void play_Wordle() {
    ifstream fin("./files/words.txt");


    if (!fin) {
        cout << "Error opening file";
        return;
    }
    system("cls");

    string result = "", word, guess, letters = "", l;
    int tries = 5;

    getline(fin, word);
    fin.close();

    cout<<"All the letters are in lowercase!"<<endl<<endl;
    for(int i = 0; i < word.size(); i++) {
        result += "_";
    }
    while(word != result) {
        tries--;

        cout<<result<<endl;
        cout<<"\t\tLetters: "<<letters<<endl;
        cout<<"\t\tTries: "<<tries + 1<<endl;
        cin>>guess;

        bool ok = false, found_one = false;
        l = "";

        if (guess.size() != word.size()) {
            cout<<endl<<"\tInvalid word!"<<endl;
            continue;
        }else {
            for (int i = 0; i < guess.size(); i++) {
                if (word[i] == guess[i]) {
                    result[i] = guess[i];
                    found_one = true;
                    l = guess[i];
                } else {
                    for (int j = 0; j < word.size(); j++) {
                        if (word[j] == guess[i]) {
                            found_one = true;
                            l = guess[i];
                            
                        }
                    }
                }
                ok = false;
                if (found_one == true) {
                    found_one = false;
                    for (char c: letters) {
                        if (c == l[0]) {
                            ok = true;
                            // break;
                        }
                    }
                    if (ok == false) 
                        letters += l[0];    
                }
            }
        }

        if (word == result) {
            cout<<endl<<"\tCongratulations! You guessed the word!"<<endl;
            delete_first_word();
            press_any_key();
            break;
        }
        if (tries == 0) {
            cout<<endl<<"\tYou lost!"<<endl;
            press_any_key();
            break;
        }
        
    }

}

int main() {


    int command;
    bool invalid_command = false;

    while (1) {
        system("cls");
        if (invalid_command == true) {
            cout << "Invalid command!!" << endl;
            invalid_command = false;
        }
        wordle_afis_start_menu();
        cout << "Enter a command: ";

        cin >> command;

        if (command == 1) {
            // first command 
            first_command();

        } else if (command == 2) {
            // second command
            play_Wordle();

        } else if (command == 3) {
            // third command
            break;

        } else {
            invalid_command = true;
        }
    }
    return 0;
}