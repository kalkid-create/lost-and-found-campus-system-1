#include <iostream>
#include <fstream>
using namespace std;

// ================= CONSTANT =================
const int MAX = 100;

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

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    cout << "Item added successfully!\n";
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
    Item item;

    file >> item.id >> item.name >> item.owner >> item.location;

    while (!file.fail()) {
        addLostItem(item);
        file >> item.id >> item.name >> item.owner >> item.location;
    }

    file.close();
}

// ================= QUEUE =================
Item queueArr[MAX];
int front = -1, rear = -1;

void enqueue(Item item) {
    if (rear < MAX - 1) {
        if (front == -1)
            front = 0;

        rear = rear + 1;
        queueArr[rear] = item;

        cout << "Item added to queue!\n";
    }
}

Item dequeue() {
    Item item = queueArr[front];
    front = front + 1;
    return item;
}

bool isEmptyQueue() {
    return (front == -1 || front > rear);
}

void displayQueue() {
    cout << "\n--- FOUND ITEMS (QUEUE) ---\n";

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
    if (top < MAX - 1) {
        top = top + 1;
        stackArr[top] = item;
    }
}

void displayStack() {
    cout << "\n--- HISTORY STACK ---\n";

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

    file >> u >> p >> r;

    while (!file.fail()) {

        if (u == username && p == password && r == role) {
            return true;
        }

        file >> u >> p >> r;
    }

    return false;
}

// ================= MAIN =================
int main() {
    loadFromFile();

    int choice;

    cout << "1. Admin Login\n2. Student Login\nChoice: ";
    cin >> choice;

    bool success = false;
    int attempts = 0;

    if (choice == 1) {
        while (!success && attempts < 3) {
            if (login("admin")) {
                cout << "Login successful!\n";
                success = true;
            } else {
                cout << "Incorrect login. Try again.\n";
                attempts++;
            }
        }
    } else {
        while (!success && attempts < 3) {
            if (login("student")) {
                cout << "Login successful!\n";
                success = true;
            } else {
                cout << "Incorrect login. Try again.\n";
                attempts++;
            }
        }
    }

    if (!success) {
        cout << "Too many failed attempts. Exiting...\n";
        return 0;
    }

    while (true) {
        cout << "\n===== LOST & FOUND SYSTEM =====\n";
        cout << "1. Add Lost Item\n";
        cout << "2. Search Item\n";
        cout << "3. View Lost Items\n";
        cout << "4. Add Found Item\n";
        cout << "5. Process Found Item\n";
        cout << "6. View Queue\n";
        cout << "7. View Stack History\n";
        cout << "8. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Item item;
            cout << "ID: ";
            cin >> item.id;
            cout << "Name: ";
            cin >> item.name;
            cout << "Owner: ";
            cin >> item.owner;
            cout << "Location: ";
            cin >> item.location;

            addLostItem(item);
        }

        else if (choice == 2) {
            string name;
            cout << "Enter name: ";
            cin >> name;
            searchItem(name);
        }

        else if (choice == 3) {
            displayLostItems();
        }

        else if (choice == 4) {
            Item item;
            cout << "ID: ";
            cin >> item.id;
            cout << "Name: ";
            cin >> item.name;
            cout << "Owner: ";
            cin >> item.owner;
            cout << "Location: ";
            cin >> item.location;

            enqueue(item);
        }

        else if (choice == 5) {
            if (!isEmptyQueue()) {
                Item item = dequeue();
                cout << "Processing: " << item.name << endl;
                push(item);
            } else {
                cout << "No found items!\n";
            }
        }

        else if (choice == 6) {
            displayQueue();
        }

        else if (choice == 7) {
            displayStack();
        }

        else if (choice == 8) {
            saveToFile();
            cout << "Data saved. Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
