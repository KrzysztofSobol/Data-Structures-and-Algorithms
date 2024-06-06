#include <iostream>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;
int max_depth_t = 0;
int max_cave_t;
int max_depth, max_row, max_col;

long long int v;

void mole(char ***block, int k, int i, int j){
    block[k][i][j] = 'x';
    if(max_depth_t < k+1)
        max_depth_t = k+1;

    //down vertical
    if(k<max_depth && block[k+1][i][j]=='o'){
        max_cave_t++;
        v++;
        mole(block, k+1, i, j);
    }
    //up vertical
    if(k>0 && block[k-1][i][j]=='o'){
        max_cave_t++;
        v++;
        mole(block, k-1, i, j);
    }
    //up horizontal
    if(i>0 && block[k][i-1][j]=='o'){
        max_cave_t++;
        v++;
        mole(block, k, i-1, j);
    }
    //down horizontal
    if(i<max_row && block[k][i+1][j]=='o'){
        max_cave_t++;
        v++;
        mole(block, k, i+1, j);
    }
    //left horizontal
    if(j>0 && block[k][i][j-1]=='o'){
        max_cave_t++;
        v++;
        mole(block, k, i, j-1);
    }
    //right horizontal
    if(j<max_col && block[k][i][j+1]=='o'){
        max_cave_t++;
        v++;
        mole(block, k, i, j+1);
    }
}

void cave_scan(char ***block, int depth, int row, int col){
    int max_cave=0, isolated=0, max_depth;
    // x * y * z = n
    for(int i=0; i<col; i++){
        for(int j=0; j<row; j++){
            if(block[0][i][j]=='o'){
                max_cave_t++;
                v++;
                mole(block, 0, i ,j);
                if(max_cave < max_cave_t)
                    max_cave = max_cave_t;
            }
            max_cave_t = 0;
        }
    }
    max_depth = max_depth_t;

    for (int k = 1; k < depth; k++) {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if(block[k][i][j]=='o'){
                    max_cave_t++;
                    isolated++;
                    v++;
                    mole(block, k, i ,j);
                    if(max_cave < max_cave_t)
                        max_cave = max_cave_t;
                }
                max_cave_t = 0;
            }
        }
    }
    printf("%d %d %d", max_depth, max_cave, isolated);
    printf("\n%lld\n", v);
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

    int depth,row,col;
    in >> col >> row >> depth;

    /// dynamiczna alokacja 3d tablicy
    /// block[depth][row][col]
    auto*** block = new char**[depth];
    for(int i=0; i<depth; i++){
        block[i] = new char *[col];
        for(int j=0; j<col; j++){
            block[i][j] = new char[row];
        }
    }

    /// input danych
    string temp;
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < row; j++) {
            in >> temp;
            for (int k = 0; k < col; k++) {
                block[i][j][k] = temp[k];
            }
        }
    }

    max_depth = depth-1;
    max_row = row-1;
    max_col = col-1;
    high_resolution_clock::time_point start, stop;
    double time;

    start = high_resolution_clock::now();
    cave_scan(block, depth, row, col);
    stop = high_resolution_clock::now();
    time = duration_cast<duration<double>>(stop - start).count();
    cout << "Czas wykonania algorytmu: " << time << " sekund" << endl;

    // Zwolnienie zaalokowanej pamięci
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < row; j++) {
            delete[] block[i][j];
        }
        delete[] block[i];
    }
    delete[] block;

    return 0;
}
