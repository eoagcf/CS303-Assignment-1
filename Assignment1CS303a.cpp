#include <iostream>
#include <fstream>
#include <stdexcept> // For std::out_of_range and std::runtime_error
using namespace std;

const int MAX_SIZE = 100; // Define a maximum size for the array

// Function prototypes
int checkInteger(const int arr[], int size, int target);
void modifyValue(int arr[], int index, int& oldValue, int& newValue);
void safeModifyValue(int arr[], int size, int index, int newValue);
int addInteger(int arr[], int& size, int value);
void safeAddInteger(int arr[], int& size, int value);
void replaceOrRemove(int arr[], int& size, int index, bool remove);
void displayArray(const int arr[], int size);

int main() {
    int arr[MAX_SIZE];
    int size = 0; // Initial size of the array

    // Reading data from a file into the array
    ifstream inputFile("C:\\Users\\ernes\\Desktop\\CS303\\data.txt");
    if (!inputFile) {
        cout << "Error: Unable to open file!\n";
        return 1;
    }

    while (size < MAX_SIZE && inputFile >> arr[size]) {
        size++;
    }
    inputFile.close();

    cout << "Array loaded from file:\n";
    displayArray(arr, size);

    // Using try-catch for modifying values
    try {
        safeModifyValue(arr, size, 1, 42); // Modify the value at index 1
    }
    catch (const out_of_range& e) {
        cout << "Error: " << e.what() << "\n";
    }

    // Using try-catch for adding a new integer
    try {
        safeAddInteger(arr, size, 99); // Add the integer 99
    }
    catch (const runtime_error& e) {
        cout << "Error: " << e.what() << "\n";
    }

    cout << "Final array:\n";
    displayArray(arr, size);

    return 0;
}

// Function to check if a certain integer exists in the array
int checkInteger(const int arr[], int size, int target) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Not found
}

// Function to safely modify the value at a specific index using exceptions
void safeModifyValue(int arr[], int size, int index, int newValue) {
    if (index < 0 || index >= size) {
        throw out_of_range("Invalid index for modification.");
    }

    int oldValue = arr[index];
    arr[index] = newValue;
    cout << "Modified index " << index << ": Old Value = " << oldValue
        << ", New Value = " << newValue << "\n";
}

// Function to safely add a new integer to the array using exceptions
void safeAddInteger(int arr[], int& size, int value) {
    if (size >= MAX_SIZE) {
        throw runtime_error("Array is full, cannot add new integer.");
    }
    arr[size++] = value;
    cout << "Added " << value << " to the array.\n";
}

// Function to modify the value at a specific index
void modifyValue(int arr[], int index, int& oldValue, int& newValue) {
    oldValue = arr[index];
    arr[index] = newValue;
}

// Function to add a new integer to the array
int addInteger(int arr[], int& size, int value) {
    if (size < MAX_SIZE) {
        arr[size++] = value;
        return 1; // Successfully added
    }
    return 0; // Array is full
}

// Function to replace the value with 0 or remove it
void replaceOrRemove(int arr[], int& size, int index, bool remove) {
    if (index >= 0 && index < size) {
        if (remove) {
            for (int i = index; i < size - 1; ++i) {
                arr[i] = arr[i + 1];
            }
            --size; // Decrease size after removal
        }
        else {
            arr[index] = 0;
        }
    }
    else {
        cout << "Invalid index." << endl;
    }
}

// Function to display the array
void displayArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}
