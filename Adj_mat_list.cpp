#include <iostream>
using namespace std;

struct Node {
    string city;
    int time;
    Node* next;
};

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    string cities[20];
    Node* cityList[20] = {nullptr};

    // Input city names
    for(int i = 0; i < n; i++) {
        cout << "Enter city " << i+1 << ": ";
        cin >> cities[i];
    }

    int matrix[20][20] = {0};

    char choice;
    do {
        string from, to;
        int time, fromIdx = -1, toIdx = -1;

        // Input from, to cities and the travel time
        cout << "From city: ";
        cin >> from;
        cout << "To city: ";
        cin >> to;
        cout << "Time: ";
        cin >> time;

        // Find indices of from and to cities
        for(int i = 0; i < n; i++) {
            if(cities[i] == from) fromIdx = i;
            if(cities[i] == to) toIdx = i;
        }

        // Add to adjacency list and matrix if cities are found
        if(fromIdx != -1 && toIdx != -1) {
            // Adjacency List
            Node* newNode = new Node{to, time, nullptr};
            if(cityList[fromIdx] == nullptr) {
                cityList[fromIdx] = newNode;
            } else {
                Node* temp = cityList[fromIdx];
                while(temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }

            // Adjacency Matrix (undirected graph)
            matrix[fromIdx][toIdx] = time;
            matrix[toIdx][fromIdx] = time;

            cout << "Added!\n";
        } else {
            cout << "City not found!\n";
        }

        cout << "Add more? (y/n): ";
        cin >> choice;
    } while(choice == 'y' || choice == 'Y');

    // Ask the user for the type of representation to display
    char representationChoice;
    cout << "\nChoose the representation to display:\n";
    cout << "1. Adjacency List\n";
    cout << "2. Adjacency Matrix\n";
    cout << "Enter your choice (1/2): ";
    cin >> representationChoice;

    if (representationChoice == '1') {
        // Display the adjacency list
        cout << "\nAdjacency List:\n";
        for(int i = 0; i < n; i++) {
            cout << cities[i] << " -> ";
            Node* temp = cityList[i];
            while(temp != nullptr) {
                cout << temp->city << "(" << temp->time << ") ";
                temp = temp->next;
            }
            cout << endl;
        }
    } else if (representationChoice == '2') {
        // Display the adjacency matrix
        cout << "\nAdjacency Matrix:\n\t";
        for(int i = 0; i < n; i++) 
            cout << cities[i] << "\t";
        cout << endl;

        for(int i = 0; i < n; i++) {
            cout << cities[i] << "\t";
            for(int j = 0; j < n; j++) 
                cout << matrix[i][j] << "\t";
            cout << endl;
        }
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
