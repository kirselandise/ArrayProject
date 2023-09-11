#include "ArrayProject.h"

int dataArray[10][10];
char mode;
char ans;
int add;
int mod;
int row;
int col;
int checkNum;

int checkEntry(int num) { //Checks if a value exists within the data and prints its index.
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (dataArray[i][j] == num) {
                cout << num << " is an entry that exists. It is at the location " << i + 1 << ", " << j + 1 << endl;
                return 1;
            }
        }
    }
    cout << num << " is not an entry that exists." << endl;
    return 1;
}

int addEntry(int num) { //Adds a new entry at the end of the array
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (dataArray[i][j] == 0) {
                dataArray[i][j] = num;
                cout << num << " was successfully added in at location " << i + 1 << ", " << j + 1 << endl;
                return 1;
            }
        }
    }
    cout << "You have hit the maximum capacity of 100 entries. Please delete entries before adding more." << endl;
    return 1;
}

void modEntry(int num) { //Replaces desired entry with a new value and prints both the old and new value
    cout << "What row for the entry would you like to replace?" << endl;
    cin >> row;
    cout << "What column for the entry would you like to replace?" << endl;
    cin >> col;
    cout << "Your old entry at " << row << ", " << col << " is " << dataArray[row][col] << " and replaced with " << num << "." << endl;
    dataArray[row-1][col-1] = num;
}

void removeEntry() { //Removes desired entry and replaces it with a zero
    cout << "What is the row for the entry you would like to delete?" << endl;
    cin >> row;
    cout << "What is the column for the entry you would like to delete?" << endl;
    cin >> col;
    dataArray[row-1][col-1] = 0;
    cout << "The entry at " << row - 1 << ", " << col - 1 << " was sucessfully deleted." << endl;
}

void endProgram() { //Shuts down program with a goodbye mesage
    cout << "Goodbye!" << endl;
}

void promptUser() { //Asks the user if they would like to Check, Modify, Add, or Delete an entry
    cout << "What would you like to do with your data? Check, Add, Modify, or Delete? (c, a, m, d)" << endl;
    cin >> mode;
    if (tolower(mode) == 'c') {
        cout << "Which number would you like to check for?" << endl;
        cin >> checkNum;
        checkEntry(checkNum);
    }
    else if (tolower(mode) == 'a') {
        cin.exceptions(istream::failbit); //Sets up an exception to identify non-integers
        while (true) {
            try {
                cout << "Which number would you like to add?" << endl;
                cin >> add;
                if (cin.fail() || add < 0) {
                    throw ios_base::failure("Invalid input");
                }
                else {
                    break;
                }
            }
            catch (ios_base::failure &fail) {
                cout << "Please insert an integer." << endl; //Handles non-integer values
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        addEntry(add);
    }
    else if (tolower(mode) == 'm') {
        cin.exceptions(istream::failbit); //Sets up an exception to identify non-integers
        while (true) {
            try {
                cout << "What is your new number?" << endl;
                cin >> mod;
                if (cin.fail() || mod < 0) {
                    throw ios_base::failure("Invalid input");
                }
                else {
                    break;
                }
            }
            catch (ios_base::failure& fail) { 
                cout << "Please insert an integer." << endl; //Handles non-integer values
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        modEntry(mod);
    }
    else if (tolower(mode) == 'd') {
        removeEntry();
    }
    else {
        cout << "Sorry, I did not understand your response. Try again.";
        promptUser();
    }

    cout << "Would you like to continue? (y or n)" << endl;
    cin >> ans;

    if (tolower(ans) == 'y') {
        promptUser();
    }
    else if (tolower(ans) == 'n') {
        endProgram();
    }
    else {
        "Sorry, I did not understand your response. Try again.";
    }
}

int main() {

    ifstream file("Data.txt"); //Opens file for reading

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            file >> dataArray[i][j]; //Assigns the file contents to an array
            cout << dataArray[i][j] << " "; //Prints file contents for user readability
        }
        cout << endl;
    }

    cout << "Welcome!" << endl;
    promptUser(); //Begins the assignment

    file.close();
    return 0; 
}