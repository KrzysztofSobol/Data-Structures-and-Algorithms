#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
vector<int> cashType;
vector<int> cashAmount;


int Min(int &a, int b){
    return a < b ? a : b;
}

int NewAmount(int &a, int &b, int **arr, int &n){
    int minCoins = 20001, remaining, coinsForRemaining;
    for(int k = 1; k <= a / b; k++){
        remaining = a - k * b;
        if (remaining > 0)
            coinsForRemaining = arr[n-1][remaining];
        else
            coinsForRemaining = 0;
        if(k <= cashAmount[n])
            minCoins = Min(minCoins, k + coinsForRemaining);
    }
    return minCoins;
}

int main(){
    // plik
    cout << "Podaj nazwe pliku (bez .txt): " << "\n";
    string file_name;
    cin >> file_name;
    file_name += ".txt";

    ifstream in(file_name);
    if(!in.is_open()){
        cout << "ERROR: nie znaleziono pliku!" << "\n";
        return 1;
    }

    int amount, change;

    in >> amount;
    int c;
    for(int i=0; i<amount; i++){
        in >> c;
        cashType.push_back(c);
    }

    for(int i=0; i<amount; i++){
        in >> c;
        cashAmount.push_back(c);
    }
    in >> change;

    // array for calculations
    auto **arr = new int *[amount];
    for(int i=0; i<cashType.size(); i++){
        arr[i] = new int[change];
    }

    // algorithm
    // filling the first row of the array
    int amountNeeded;
    for(int j=1; j<=change; j++){
        if(j%cashType[0] == 0){
            amountNeeded = j/cashType[0];
            if(amountNeeded<=cashAmount[0])
                arr[0][j] = amountNeeded;
            else
                arr[0][j] = 20001;
        }
        else
            arr[0][j] = 20001;
    }

    // calculate the remaining rows in the array
    for(int i=1; i<amount; i++){
        for(int j=1; j<=change; j++){
            if(cashType[i]>j)
                arr[i][j] = arr[i-1][j];
            else
            arr[i][j] = Min(arr[i-1][j], NewAmount(j,cashType[i],arr,i));
        }
    }

    cout << arr[amount-1][change] << endl;
}

// by krzys ;)