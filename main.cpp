#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

// ================= SCREEN CLEAR =================
void clearScreen() {
    system("cls");
}

// ================= CONSTANT =================
const int MAX = 100;

//UNIQUE ID GENERATOR
int globalID = 1000;

// ================= ITEM STRUCT =================
struct Item {
    int id;
    string name;
    string owner;
    string location;
};

// ================= LINKED LIST =================
struct Node {
    Item data;
    Node* next;
};

Node* head = NULL;

// ================= LOST ITEMS =================
void addLostItem(Item item) {
    Node* newNode = new Node;
    newNode->data = item;
    newNode->next = NULL;

    if (head == NULL)
        head = newNode;
    else {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    cout << "Lost item added successfully!\n";
}

void displayLostItems() {
    Node* temp = head;

    cout << "\n--- LOST ITEMS ---\n";
    while (temp != NULL) {
        cout << temp->data.id << " | "
             << temp->data.name << " | "
             << temp->data.owner << " | "
             << temp->data.location << endl;
        temp = temp->next;
    }
}

// ================= SEARCH =================
void searchItem(string name) {
    Node* temp = head;
    bool found = false;

    cout << "\n--- SEARCH RESULT ---\n";

    while (temp != NULL) {
        if (temp->data.name == name) {
            cout << temp->data.id << " | "
                 << temp->data.name << " | "
                 << temp->data.owner << " | "
                 << temp->data.location << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
        cout << "Item not found!\n";
}

// ================= FILE =================
void saveToFile() {
    ofstream file("lost.txt");
    Node* temp = head;

    while (temp != NULL) {
        file << temp->data.id << " "
             << temp->data.name << " "
             << temp->data.owner << " "
             << temp->data.location << endl;

        temp = temp->next;
    }

    file.close();
}

void loadFromFile() {
    ifstream file("lost.txt");
    if (!file) return;

    Item item;
    while (file >> item.id >> item.name >> item.owner >> item.location) {
        addLostItem(item);
    }
}

// ================= QUEUE =================
Item queueArr[MAX];
int front = -1, rear = -1;

void enqueue(Item item) {
    if (rear < MAX - 1) {
        if (front == -1)
            front = 0;

        queueArr[++rear] = item;
        cout << "Found item submitted!\n";
    }
}

Item dequeue() {
    return queueArr[front++];
}

bool isEmptyQueue() {
    return (front == -1 || front > rear);
}

void displayQueue() {
    cout << "\n--- FOUND ITEMS ---\n";

    if (isEmptyQueue()) {
        cout << "No found items!\n";
        return;
    }

    for (int i = front; i <= rear; i++) {
        cout << queueArr[i].id << " | "
             << queueArr[i].name << " | "
             << queueArr[i].owner << " | "
             << queueArr[i].location << endl;
    }
}

// ================= STACK =================
Item stackArr[MAX];
int top = -1;

void push(Item item) {
    if (top < MAX - 1)
        stackArr[++top] = item;
}

void displayStack() {
    cout << "\n--- HISTORY STACK ---\n";

    if (top == -1) {
        cout << "No history!\n";
        return;
    }

    for (int i = top; i >= 0; i--) {
        cout << stackArr[i].id << " | "
             << stackArr[i].name << " | "
             << stackArr[i].owner << " | "
             << stackArr[i].location << endl;
    }
}

// ================= LOGIN =================
bool login(string role) {
    string u, p, r;
    string username, password;

    cout << "\n--- " << role << " LOGIN ---\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    ifstream file("users.txt");

    while (file >> u >> p >> r) {
        if (u == username && p == password && r == role)
            return true;
    }

    return false;
}

// ================= MAIN =================
int main() {
    srand(time(0));
    loadFromFile();

    while (true) {

        clearScreen();

        int choice;
        string role;

        cout << "\n===== LOST & FOUND SYSTEM =====\n";
        cout << "1. Admin\n";
        cout << "2. Student\n";
        cout << "3. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting system...\n";
            break;
        }

        role = (choice == 1) ? "admin" : "student";

        bool success = false;
        int attempts = 0;

        while (!success && attempts < 3) {
            if (login(role)) {
                cout << "Login successful!\n";
                success = true;
            } else {
                cout << "Incorrect login.\n";
                attempts++;
            }
        }

        if (!success) {
            cout << "Returning to main menu...\n";
            system("pause");
            clearScreen();
            continue;
        }

        // ================= ADMIN =================
        if (role == "admin") {
            while (true) {
                int choice;

                cout << "\n===== ADMIN MENU =====\n";
                cout << "1. Add Lost Item\n";
                cout << "2. View Lost Items\n";
                cout << "3. Process Found Item\n";
                cout << "4. View Queue\n";
                cout << "5. View History\n";
                cout << "6. Logout\n";
                cin >> choice;

                if (choice == 6) {
                    cout << "Logging out...\n";
                    system("pause");
                    clearScreen();
                    break;
                }

                if (choice == 1) {
                    Item item;

                    item.id = globalID++;

                    cout << "Name: ";
                    cin >> item.name;
                    cout << "Owner: ";
                    cin >> item.owner;
                    cout << "Location: ";
                    cin >> item.location;

                    addLostItem(item);
                }
                else if (choice == 2) displayLostItems();
                else if (choice == 3) {
                    if (!isEmptyQueue()) {
                        Item item = dequeue();
                        push(item);
                        cout << "Processed: " << item.name << endl;
                    }
                }
                else if (choice == 4) displayQueue();
                else if (choice == 5) displayStack();
            }
        }

        // ================= STUDENT =================
        else {
            while (true) {
                int choice;

                cout << "\n===== STUDENT MENU =====\n";
                cout << "1. Add Lost Item\n";
                cout << "2. Search Item\n";
                cout << "3. Add Found Item\n";
                cout << "4. Logout\n";
                cin >> choice;

                if (choice == 4) {
                    cout << "Logging out...\n";
                    system("pause");
                    clearScreen();
                    break;
                }

                if (choice == 1) {
                    Item item;

                    item.id = globalID++;
                    item.owner = "UNKNOWN";

                    cout << "Name: ";
                    cin >> item.name;
                    cout << "Location: ";
                    cin >> item.location;

                    addLostItem(item);
                }

                else if (choice == 2) {
                    string name;
                    cout << "Name: ";
                    cin >> name;
                    searchItem(name);
                }

                else if (choice == 3) {
                    Item item;

                    item.id = globalID++;
                    item.owner = "UNKNOWN";

                    cout << "Name: ";
                    cin >> item.name;
                    cout << "Location: ";
                    cin >> item.location;

                    enqueue(item);
                    cout << "Found item submitted!\n";
                }
            }
        }
    }

    return 0;
}
