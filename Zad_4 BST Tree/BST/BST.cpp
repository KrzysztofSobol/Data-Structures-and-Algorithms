#include <iostream>
using namespace std;

struct Node {
    int number;
    Node* right;
    Node* left;
};

typedef struct Node Node;

void Search(int number, Node*& root) {
    if (root == nullptr) {
        printf("Nie znaleziono wartosci %d\n", number);
        return;
    }
    else if (number > root->number)
        Search(number, root->right);
    else if (number < root->number)
        Search(number, root->left);
    else
        printf("Znaleziono wartosc %d\n", number);
}

void Insert(int number, Node*& root) {
    if (root == nullptr)
        root = new Node{ number, nullptr, nullptr };
    else if (number > root->number)
        Insert(number, root->right);
    else if (number < root->number)
        Insert(number, root->left);
}

Node* FindMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void Delete(int number, Node*& root) {
    if (root == nullptr)
        return;
    else if (number > root->number)
        Delete(number, root->right);
    else if (number < root->number)
        Delete(number, root->left);
    else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            free(root);
            root = temp;
        }
        else if (root->right == nullptr) {
            Node* temp = root->left;
            free(root);
            root = temp;
        }
        else {
            Node* temp = FindMin(root->right);
            root->number = temp->number;
            Delete(temp->number, root->right);
        }
    }
}

void PrintTree(Node* root, int space = 0, int type = 1, int count = 6) {
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

        PrintTree(root->right, space, 1);
        cout << endl;

        for (int i = count; i < space; i++)
            cout << " ";

        if (type == 1)
            printf("P: %d\n", root->number);
        else if (type == 0)
            printf("L: %d\n", root->number);

        PrintTree(root->left, space, 0);
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


int main() {

    Node* root = nullptr;

    string input;
    int option, l, l2;
    while (1) {
        printf(" 1. Wstaw liczbe\n 2. Usun liczbe\n 3. Wyszukaj liczbe\n 4. Liczby z przedzialu\n\n");
        PrintTree(root);
        printf("\n\n\n");
        cin >> option;
        switch (option) {
        case 1:
            cout << "Podaj liczbe do dodania: ";
            cin >> l;
            Insert(l, root);
            system("cls");
            break;
        case 2:
            cout << "Podaj liczbe do usuniencia: ";
            cin >> l;
            Delete(l, root);
            system("cls");
            break;
        case 3:
            cout << "Podaj liczbe do usuniencia: ";
            cin >> l;
            system("cls");
            Search(l, root);
            break;
        case 4:
            cout << "Podaj liczby (od,do): ";
            cin >> l;
            cin >> l2;
            system("cls");
            printf("Z przedzialu (%d,%d) znaleziono %d liczb\n\n", l, l2, Count(l, l2, root));
            break;
        }
    }
    return 0;
}
