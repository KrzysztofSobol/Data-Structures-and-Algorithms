#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int amount;

struct crystal{
    int c[3];
};

int combinations[101][101][101];
crystal bestCrystal;
int bestCrystalCount = 999;

crystal AddCrystals(crystal &crystal1, crystal &crystal2){
    crystal sumCrystal;
    for(int i=0; i<3; i++){
        sumCrystal.c[i] = crystal1.c[i] + crystal2.c[i];
    }
    return sumCrystal;
}

bool IsBalanced(crystal &Crystal){
    if(Crystal.c[0] == Crystal.c[1] && Crystal.c[0] == Crystal.c[2])
        return true;
    else
        return false;
}

void SwapCrystal(crystal &Crystal){
        bestCrystal.c[0] = Crystal.c[0];
        bestCrystal.c[1] = Crystal.c[1];
        bestCrystal.c[2] = Crystal.c[2];
}

void SaveCombination(crystal &Crystal,int count){
    combinations[Crystal.c[0]][Crystal.c[1]][Crystal.c[2]] = count;
}

int GetCount(crystal &Crystal){
    return combinations[Crystal.c[0]][Crystal.c[1]][Crystal.c[2]];
}

void deep_rock(vector<crystal> crystals, crystal chosenCrystal, int n, int count){

    crystals.erase(crystals.begin() + n);
    for(int i=0; i<crystals.size(); i++){
        crystal tempCrystal = AddCrystals(crystals[i],chosenCrystal);
        if(tempCrystal.c[0] > 100  || tempCrystal.c[1] > 100 || tempCrystal.c[2] > 100)
            continue;
        if(GetCount(tempCrystal) != NULL && count >= GetCount(tempCrystal)){
            continue;
        }
        else{
            SaveCombination(tempCrystal, count);
            if(IsBalanced(tempCrystal)){
                if (bestCrystal.c[0] <= tempCrystal.c[0]){
                    SwapCrystal(tempCrystal);
                    bestCrystalCount = count;
                }
            }
            deep_rock(crystals, tempCrystal, i, count+1);
        }
    }
}

int main(){
    cout << "Podaj nazwe pliku (bez .txt): " << "\n";
    string file_name;
    cin >> file_name;
    file_name += ".txt";

    ifstream in(file_name);
    if(!in.is_open()){
        cout << "ERROR: nie znaleziono pliku!" << "\n";
        return 1;
    }
    in >> amount;

    vector<crystal> crystals;
    int c;
    for(int i=0; i<amount; i++){
        crystal newCrystal;
        for(int j=0; j<3; j++){
            in >> c;
            newCrystal.c[j] = c;
        }
        crystals.push_back(newCrystal);
    }

    crystal chosenCrystal{};
    crystals.insert(crystals.begin(), chosenCrystal);

    deep_rock(crystals, chosenCrystal, 0, 1);

    cout << endl;
    if(bestCrystal.c[0] == 0)
        cout << "NIE da sie utworzyc paliwa :(\n";
    else{
        cout << bestCrystal.c[0]*3 << endl;
        cout << bestCrystalCount << endl;
    }

    return 0;
}