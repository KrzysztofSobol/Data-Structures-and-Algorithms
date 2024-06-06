#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    int number;
    int weight;
    Node* right;
    Node* left;
};

typedef struct Node Node;

int weight(Node* node) {
    if (node == nullptr)
        return 0;
    return node->weight;
}

int GetBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return weight(node->left) - weight(node->right);
}

Node* RR(Node* A) {
    Node* B = A->left;
    Node* temp = B->right;
    B->right = A;
    A->left = temp;
    A->weight = max(weight(A->left), weight(A->right)) + 1;
    B->weight = max(weight(B->left), weight(B->right)) + 1;
    return B;
}

Node* LL(Node* B) {
    Node* A = B->right;
    Node* temp = A->left;
    A->left = B;
    B->right = temp;
    B->weight = max(weight(B->left), weight(B->right)) + 1;
    A->weight = max(weight(A->left), weight(A->right)) + 1;
    return A;
}

bool Search(int number, Node*& root) {
    if (root == nullptr) {
        return false;
    }
    else if (number > root->number)
        Search(number, root->right);
    else if (number < root->number)
        Search(number, root->left);
    else
        return true;
}

Node* Insert(int number, Node*& root) {
    if (root == nullptr)
        return new Node{ number, 1, nullptr, nullptr };
    if (number > root->number)
        root->right = Insert(number, root->right);
    else if (number < root->number)
        root->left = Insert(number, root->left);

    root->weight = 1 + max(weight(root->left), weight(root->right));
    int balance = GetBalance(root);


    if (balance == 2 && GetBalance(root->left) == 1)
        return RR(root);

    if (balance == -2 && GetBalance(root->right) == -1)
        return LL(root);

    if (balance == 2 && GetBalance(root->left) == -1) {
        root->left = LL(root->left);
        return RR(root);
    }

    if (balance == -2 && GetBalance(root->right) == 1) {
        root->right = RR(root->right);
        return LL(root);
    }

    return root;
}

Node* findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

Node* Delete(int number, Node*& root) {
    if (root == nullptr)
        return root;
    if (number > root->number)
        root->right = Delete(number, root->right);
    else if (number < root->number)
        root->left = Delete(number, root->left);
    else {
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
                delete temp;
            }
            else {
                root = temp;
                delete temp;
            }
        }
        else {
            Node* temp = findMin(root->right);
            root->number = temp->number;
            root->right = Delete(temp->number, root->right);
        }
    }
    if (root == nullptr)
        return root;

    root->weight = 1 + max(weight(root->left), weight(root->right));
    int balance = GetBalance(root);

    if (balance == 2 && GetBalance(root->left) >= 0)
        return RR(root);

    if (balance == -2 && GetBalance(root->right) <= 0)
        return LL(root);

    if (balance == 2 && GetBalance(root->left) == -1) {
        root->left = LL(root->left);
        return RR(root);
    }

    if (balance == -2 && GetBalance(root->right) == 1) {
        root->right = RR(root->right);
        return LL(root);
    }

    return root;
}

void Print(Node* root, int space = 0, int type = 1, int count = 6) {
    if (root == nullptr) {
        space += count;
        for (int i = count; i < space; i++)
            cout << " ";
        if (type == 1)
            printf("P: null");
        else if (type == 0)
            printf("L: null");
    }
    else {
        space += count;

        Print(root->right, space, 1);
        cout << endl;

        for (int i = count; i < space; i++)
            cout << " ";

        if (type == 1)
            printf("P: %d\n", root->number);
        else if (type == 0)
            printf("L: %d\n", root->number);

        Print(root->left, space, 0);
    }
}

int Count(int a, int b, Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int count = 0;

    if (root->number >= a && root->number <= b) {
        count = 1;
    }
    if (root->number > a) {
        count += Count(a, b, root->left);
    }
    if (root->number < b) {
        count += Count(a, b, root->right);
    }

    return count;
}

void InputData(string input, Node*& root) {
    input += ".txt";
    ifstream in(input);
    ofstream out("out.txt");

    if (!in.is_open()) {
        cout << "ERROR: Nie mozna otworzyc pliku!" << endl;
        return;
    }

    int l;
    in >> l;
    for (int i = 0; i < l; i++) {
        char command;
        int x, y;

        in >> command;

        switch (command) {
        case 'W':
            in >> x;
            root = Insert(x, root);
            break;
        case 'U':
            in >> x;
            root = Delete(x, root);
            break;
        case 'S':
            in >> x;
            out << (Search(x, root) ? "TAK" : "NIE") << endl;
            break;
        case 'L':
            in >> x >> y;
            out << Count(x, y, root) << endl;
            break;
        default:
            break;
        }
    }

}

int main() {

    Node* root = nullptr;

    string input;
    int option, l, l2;
    while (1) {
        printf(" 1. Wstaw liczbe\n 2. Usun liczbe\n 3. Wyszukaj liczbe\n 4. Liczby z przedzialu\n 5. Wyswietl drzewo \n 6. Wykonaj skrypt\n\n\n");
        Print(root);
        printf("\n\n\n");
        cin >> option;
        switch (option) {
            case 1:
                cout << "Podaj liczbe do dodania: ";
                cin >> l;
                root = Insert(l, root);
                system("cls");
                break;
            case 2:
                cout << "Podaj liczbe do usuniencia: ";
                cin >> l;
                root = Delete(l, root);
                system("cls");
                break;
            case 3:
                cout << "Podaj liczbe do usuniencia: ";
                cin >> l;
                system("cls");
                cout << (Search(l, root) ? "TAK, ZNALEZIONO\n" : "NIE ZNALEZIONO\n") << endl;
                break;
            case 4:
                cout << "Podaj liczby (od,do): ";
                cin >> l;
                cin >> l2;
                system("cls");
                printf("Z przedzialu (%d,%d) znaleziono %d liczb\n\n", l, l2, Count(l, l2, root));
                break;
            case 5:
                system("cls");
                Print(root);
                printf("\n\n");
                break;
            case 6:
                cout << "Podaj nazwe pliku: ";
                cin >> input;
                InputData(input, root);
                system("cls");
                break;
        }
    }
    return 0;
}
