#include <iostream>
#include <string>
using namespace std;

const int MAX_BUCKETS = 10;
const int MAX_TRACKS = 10;
const int INFO_FIELDS = 4;

class MusicLibrary {
private:
    string library[MAX_BUCKETS][MAX_TRACKS][INFO_FIELDS];
    int trackCount[MAX_BUCKETS] = {0};
    int hashSize;

    // Hash function
    int getHash(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % hashSize;
    }

public:
    MusicLibrary(int size) {
        hashSize = size <= MAX_BUCKETS ? size : MAX_BUCKETS;
    }

    // Add a track to the library
    void addTrack() {
        if (isFull()) {
            cout << "Library is full!\n";
            return;
        }

        string title, artist, album, duration;
        cout << "Enter track title: ";
        getline(cin >> ws, title); // Fix added here
        cout << "Enter artist: ";
        getline(cin, artist);
        cout << "Enter album: ";
        getline(cin, album);
        cout << "Enter duration (seconds): ";
        getline(cin, duration);

        int bucket = getHash(title);
        int originalBucket = bucket;

        while (trackCount[bucket] >= MAX_TRACKS) {
            bucket = (bucket + 1) % hashSize;
            if (bucket == originalBucket) {
                cout << "No space available after rehashing!\n";
                return;
            }
        }

        int idx = trackCount[bucket];
        library[bucket][idx][0] = title;
        library[bucket][idx][1] = artist;
        library[bucket][idx][2] = album;
        library[bucket][idx][3] = duration;
        trackCount[bucket]++;
        cout << "Track added at bucket " << bucket << "!\n";
    }

    // Display all tracks in the library
    void displayAll() {
        cout << "\nMusic Library Contents:\n";
        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < trackCount[i]; j++) {
                cout << "Bucket " << i << ": "
                    << library[i][j][0] << " - "
                    << library[i][j][1] << " ("
                    << library[i][j][3] << "s)\n";
            }
        }
    }

    // Check if the library is full
    bool isFull() {
        for (int i = 0; i < hashSize; i++) {
            if (trackCount[i] < MAX_TRACKS) return false;
        }
        return true;
    }
};

int main() {
    int size;
    cout << "Enter hash table size (max " << MAX_BUCKETS << "): ";
    cin >> size;
    cin.ignore();

    MusicLibrary lib(size);
    int choice;

    do {
        cout << "\nMenu:\n1. Add\n2. Display\n3. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: lib.addTrack(); break;
            case 2: lib.displayAll(); break;
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
