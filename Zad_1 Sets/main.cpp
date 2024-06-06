#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void merge(long long int **tab, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;

    auto temp = new long long int*[right - left + 1];
    for (int k = 0; k < right - left + 1; k++) {
        temp[k] = new long long int[2];
    }

    int k = 0;

    while (i <= mid && j <= right) {
        if (tab[i][0] <= tab[j][0]) {
            temp[k][0] = tab[i][0];
            temp[k][1] = tab[i][1];
            i++;
        } else {
            temp[k][0] = tab[j][0];
            temp[k][1] = tab[j][1];
            j++;
        }
        k++;
    }

    while (i <= mid) {
        temp[k][0] = tab[i][0];
        temp[k][1] = tab[i][1];
        i++;
        k++;
    }

    while (j <= right) {
        temp[k][0] = tab[j][0];
        temp[k][1] = tab[j][1];
        j++;
        k++;
    }

    for (k = 0; k <= right - left; k++) {
        tab[left + k][0] = temp[k][0];
        tab[left + k][1] = temp[k][1];
    }

    for (k = 0; k < right - left + 1; k++) {
        delete[] temp[k];
    }
    delete[] temp;
}

void mergeSort(long long int** tab, int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(tab, left, mid);
        mergeSort(tab, mid + 1, right);
        merge(tab, left, mid, right);
    }
}

void Algorytm_dobry(long long int **sets, int number_of_sets){
    long long int start = sets[0][0];
    long long int end = sets[0][1];

    for(int i=1; i<number_of_sets; i++){
        if(sets[i][0]>end){
            cout << start << " " << end << "\n";
            start = sets[i][0];
            end = sets[i][1];
        }
        else if(sets[i][1]>end)
            end = sets[i][1];
    }
    cout << start << " " << end << "\n\n";
}

void Algorytm_wolny(long long int **sets, int number_of_sets){
    long long int start = sets[0][0];
    long long int end = sets[0][1];

    for (int i = 0; i < number_of_sets; i++) {
        for (int j = i + 1; j < number_of_sets; j++) {
            if (sets[j][0] > end) {
                cout << start << " " << end << "\n";
                start = sets[j][0];
                end = sets[j][1];
                break;
            }
            else if (sets[j][1] > end)
                end = sets[j][1];
        }
    }
    cout << start << " " << end << "\n";
}

int main() {
    // podanie pliku
    cout << "Podaj nazwe pliku (bez .txt): " << "\n";
    string file_name;
    cin >> file_name;
    file_name+=".txt";

    ifstream in(file_name);
    //ofstream out("out.txt");
    if(!in.is_open()){
        cout << "ERROR: nie znaleziono pliku!" << "\n";
        return 1;
    }

    // wgranie danych
    int number_of_sets;
    in >> number_of_sets;
    auto** sets = new long long int*[number_of_sets];

    for (int i = 0; i < number_of_sets; i++) {
        sets[i] = new long long int[2];
    }

    for(int i=0; i<number_of_sets; i++){
        in >> sets[i][0]  >> sets[i][1];
    }
    in.close();

    // sort
    high_resolution_clock::time_point start, stop;
    double time;

    start = high_resolution_clock::now();

    mergeSort(sets, 0, number_of_sets-1);

    stop = high_resolution_clock::now();

    time = duration_cast<duration<double>>(stop - start).count();
    cout << "Czas wykonania sortowania: " << time << " sekund\n" << endl;

    /// ALGORYTM
    cout<<"Algorytm dobry: \n";

    start = high_resolution_clock::now();

    Algorytm_dobry(sets, number_of_sets);
    //Algorytm_wolny(sets, number_of_sets);

    stop = high_resolution_clock::now();

    time = duration_cast<duration<double>>(stop - start).count();
    cout << "Czas wykonania algorytmu: " << time << " sekund" << endl;

    for (int i = 0; i < number_of_sets; i++) {
        delete[] sets[i];
    }
    delete[] sets;

    cout << (0+4)/2 << endl;

    return 0;
}