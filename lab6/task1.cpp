#include <iostream>
#include <string>
using namespace std;

#define MAX 100 // Maximum patients allowed

class Patient {
public:
    int id;
    string name;

    Patient() : id(0), name("") {}
    Patient(int id, string name) : id(id), name(name) {}
};

class WaitingRoom {
private:
    Patient queue[MAX];
    int front, rear;
    int nextId;

public:
    WaitingRoom() {
        front = rear = -1;
        nextId = 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    bool isFull() {
        return rear == MAX - 1;
    }

    void RegisterPatient() {
        if (isFull()) {
            cout << "Waiting room is full! Cannot register more patients." << endl;
            return;
        }

        string name;
        cout << "Enter patient's name: ";
        cin.ignore();
        getline(cin, name);

        Patient p(nextId, name);
        if (isEmpty()) {
            front = rear = 0;
        } else {
            rear++;
        }
        queue[rear] = p;
        cout << "Patient registered with ID: " << nextId << endl;
        nextId++;
    }

    void ServePatient() {
        if (isEmpty()) {
            cout << "No patients to serve!" << endl;
            return;
        }

        cout << "Serving Patient ID: " << queue[front].id
             << ", Name: " << queue[front].name << endl;
        front++;
    }

    void CancelAll() {
        if (isEmpty()) {
            cout << "No patients to cancel." << endl;
            return;
        }

        front = rear = -1;
        cout << "All appointments cancelled." << endl;
    }

    bool CanDoctorGoHome() {
        return isEmpty();
    }

    void ShowAllPatient() {
        if (isEmpty()) {
            cout << "No patients in the waiting room." << endl;
            return;
        }

        // Copy current patients to temporary array for sorting
        int count = rear - front + 1;
        Patient temp[MAX];
        for (int i = 0; i < count; i++) {
            temp[i] = queue[front + i];
        }

        // Simple Bubble Sort by name (can be replaced with better sort if allowed)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (temp[j].name > temp[j + 1].name) {
                    swap(temp[j], temp[j + 1]);
                }
            }
        }

        cout << "Patients in sorted order (by name):" << endl;
        for (int i = 0; i < count; i++) {
            cout << "ID: " << temp[i].id << ", Name: " << temp[i].name << endl;
        }
    }
};

// Main function to test
int main() {
    WaitingRoom wr;
    int choice;

    do {
        cout << "\n--- Emergency Ward Waiting Room Management ---" << endl;
        cout << "1. Register Patient" << endl;
        cout << "2. Serve Patient" << endl;
        cout << "3. Cancel All" << endl;
        cout << "4. Can Doctor Go Home?" << endl;
        cout << "5. Show All Patients (Sorted by Name)" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                wr.RegisterPatient();
                break;
            case 2:
                wr.ServePatient();
                break;
            case 3:
                wr.CancelAll();
                break;
            case 4:
                if (wr.CanDoctorGoHome())
                    cout << "Yes, the doctor can go home." << endl;
                else
                    cout << "No, there are still patients waiting." << endl;
                break;
            case 5:
                wr.ShowAllPatient();
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
