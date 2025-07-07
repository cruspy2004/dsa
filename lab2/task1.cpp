#include <iostream>
using namespace std;

int main() {
    int size;

    // Ask user for array size
    cout << "Enter the size of the array: ";
    cin >> size;

    // Dynamically allocate memory for the array
    int* arr = new int[size];

    // Fill the array with values from 1 to size
    for (int i = 0; i < size; ++i) {
        arr[i] = i + 1;
    }

    // Calculate sum
    int sum = 0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    // Calculate average
    float average = static_cast<float>(sum) / size;

    // Display the array elements
    cout << "Array elements: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Print sum and average
    cout << "Sum = " << sum << endl;
    cout << "Average = " << average << endl;

    // Free dynamically allocated memory
    delete[] arr;

    return 0;
}
