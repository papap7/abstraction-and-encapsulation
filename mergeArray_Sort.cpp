#include <iostream>
using namespace std;

const int MIN_SIZE = 1;
const int MAX_SIZE = 10;

// Getting the size of each array
int getArraySize (const string& arrayName) {
    int size;
    cout<<"Input the size of the " << arrayName << " Array ("<< MIN_SIZE << " - " << MAX_SIZE <<"): ";
    cin>>size;
    while(cin.fail () || size < MIN_SIZE || size > MAX_SIZE) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout<<"Invalid input. Please input a valid size for the " << arrayName << " Array ("<< MIN_SIZE << " - " << MAX_SIZE <<"): ";
        cin>>size;
    }
    return size;
}

// Function to input an array with validation
void inputArray(float arr[], int size, const string& arrayName) {
    bool validInput = false;
    while (!validInput) {
        cout<<"Input " << size << " numbers for the "<< arrayName << " Array:\n";
        for(int i = 0; i < size; i++){
            cout<<"Input number "<< i + 1 << ": ";
            cin>>arr[i];
            while(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout<<"Invalid input. Please input a valid number for number "<< i + 1 <<": ";
                cin>>arr[i];
            }
        }

        // Ask the user if they want to continue with the entered values
        char confirmation;
        cout << "You entered: ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        } cout<<endl;

        cout << "Do you want to continue with these values? (y/n): ";
        cin>>confirmation;

        if (confirmation == 'y' || confirmation == 'Y') {
            validInput = true; // Proceed if user confirms
        } else { 
            cout<< "Please re-enter the values.\n";
        }
    }
}

// Function to combine two arrays into one
void mergeArrays (const float arr1[], int size1, const float arr2[], int size2, float finalArr[]) {
    for(int i = 0; i < size1; i++){
        finalArr[i] = arr1[i];
    }
    for(int i = 0; i < size2; i++){
        finalArr[size1 + i] = arr2[i];
    }
}

// Sorting Array in Descending Order using Bubble Sort
void sortArray (float arr[], int size) {
    bool swapped;
    int i = 0;
    do {
        swapped = false;
        for(int j = 0; j < size - 1 - i; j++) {
            if(arr[j] < arr[j + 1]) { // Sorting in descending order
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        } i++;
    } while (swapped);
}

// Printing Arrays
void printArray(const float arr[], int size, const string& arrayName) {
    cout<< arrayName << " Array: ";
    for(int i = 0; i < size; i++) {
        cout<<arr[i]<< " ";
    }
    cout<<endl<<endl;
}

// Main function
int main () {
    char restart;

    do {
        cout<<"Sorting 2 Arrays\n";
        cout<<"-------------------------------------------------"<<endl;

        // Get array size
        int size1 = getArraySize("First");
        int size2 = getArraySize("Second");
        cout<<"-------------------------------------------------"<<endl;

        // Dynamically allocate memory for arrays
        float* firstArr = new float [size1];
        float* secondArr = new float [size2];
        float* finalArr = new float [size1 + size2];

        // Input array
        inputArray(firstArr, size1, "First");
        printArray(firstArr, size1, "First");
        inputArray(secondArr, size2, "Second");
        printArray(secondArr, size2, "Second");
        cout<<"-------------------------------------------------"<<endl;

        // Merge Arrays
        mergeArrays(firstArr, size1, secondArr, size2, finalArr);
        int length = size1 + size2;
        printArray(finalArr, length, "Merged");

        // Sort Array
        sortArray(finalArr, length);
        cout<<"(Descending Order)\n";
        printArray(finalArr, length, "Sorted");
        cout<<"-------------------------------------------------"<<endl;

        // Cleanup dynamically allocated memory
        delete[] firstArr;
        delete[] secondArr;
        delete[] finalArr;

        // Ask if the user wants to restart
        cout << "Do you want to restart the program? (y/n): ";
        cin>>restart;
        cout<<endl;

    } while (restart == 'y' || restart == 'Y'); // Repeat if user enters 'y'

    return 0;
}