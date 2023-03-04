#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <windows.h>

using namespace std;

void CreateWindowFromConsole(SHORT width, SHORT height){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void getData(int& m, int& n, int& k){
    cout << "Enter matrix's rows: ";
    cin >> m;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << endl;
    cout << "Enter matrix's columns: ";
    cin >> n;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << endl;
    cout << "Enter number of bombs: ";
    cin >> k;
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    cout << endl;
    system("cls");
}

void addCount (vector <vector<int>>& arr, int& i, int& j, int& m, int& n){
    if (i-1 >= 0){
        if (arr[i-1][j-1] != -1 && j-1 >= 0) arr[i-1][j-1]++;
        if (arr[i-1][j] != -1) arr[i-1][j]++;
        if (arr[i-1][j+1] != -1 && j+1 <= n-1) arr[i-1][j+1]++;
    }
    if (arr[i][j-1] != -1 && j-1 >= 0) arr[i][j-1]++;
    if (arr[i][j+1] != -1 && j+1 <= n-1) arr[i][j+1]++;
    if (i+1 <= m-1){
        if (arr[i+1][j-1] != -1 && j-1 >= 0) arr[i+1][j-1]++;
        if (arr[i+1][j] != -1) arr[i+1][j]++;
        if (arr[i+1][j+1] != -1 && j+1 <= n-1) arr[i+1][j+1]++;
    }
}

template <class T> void printMap(vector <vector<T>> arr){
    int counts = 0;
    for (auto x:arr){
        for (auto y:x) cout << setw(4) << y;
        cout << setw(2) << "     " << counts;
        cout << endl << endl;
        counts++;
    }
    cout << endl;
    for (int i = 0; i < counts; i++) cout << setw(4) << i;
    cout << endl << endl;
}

bool IsAlive(vector <vector<int>>& mine_map,vector <vector<string>>& player_map , int i, int j){
    stringstream ss;
    ss << mine_map[i][j];
    ss >> player_map[i][j];
    if (mine_map[i][j] == -1) return false;
    return true;
}

void generateMap(vector<vector<int>>& mine_map, int& m, int& n, int& k){
    srand(time(NULL));
    while (k){
        int i = rand() % m , j = rand() % n;
        if (mine_map[i][j] != -1) {
            mine_map[i][j] = -1;
            k--;
            addCount(mine_map, i, j, m, n);
        }
    }
}

void game(vector<vector<int>>& mine_map, vector<vector<string>>& player_map, int& m, int& n, int& k){
    bool alive = true;
    for (int box = 0; box < n*m-k; box++) {
        printMap(player_map);
        cout << "Enter a coordinate: ";
        int i, j;
        cin >> i >> j;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        system("cls");
        while (i < 0 || j < 0 || i-1 < 0 || j-1 < 0 || i+1 > m || j+1 > n || player_map[i][j] != "#"){
            printMap(player_map);
            cout << "Coordinate not valid, please enter again: ";
            cin >> i >> j;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl;
            system("cls");
        }

        if (!IsAlive(mine_map, player_map, i, j)){
            alive = false;
            break;
        }
    }
    if (!alive) cout << "YOU'RE DEAD!";
    else cout << "YOU WON!";
}

int main()
{
    //CreateWindowFromConsole(50, 50);
    int m, n ,k;
    getData(m, n, k);

    vector <vector<int>> mine_map(m, vector<int>(n, 0));
    vector <vector<string>> player_map(m, vector<string>(n, "#"));

    generateMap(mine_map, m, n, k);
    game(mine_map, player_map, m, n, k);

    return 0;
}
