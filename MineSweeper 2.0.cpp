#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <Windows.h>
#include <conio.h>

using namespace std;

void getData(int& m, int& n, int& k){
    cout << "Enter matrix's rows: ";
    cin >> m;
    cout << endl;
    while(cin.rdstate() == 4){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Not valid, please renter matrix's rows: ";
        cin >> m;
        cout << endl;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    system("cls");

    cout << "Enter matrix's columns: ";
    cin >> n;
    cout << endl;
    while(cin.rdstate() == 4){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Not valid, please renter matrix's columns: ";
        cin >> n;
        cout << endl;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    system("cls");

    cout << "Enter number of bombs: ";
    cin >> k;
    cout << endl;
    while(cin.rdstate() == 4){
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cout << "Not valid, please renter number of bombs: ";
        cin >> k;
        cout << endl;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');
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

template <class T>void printMap(vector <vector<T>> arr, int& m, int& n){
    int countN = 0;
    for (auto x:arr){
        for (auto y:x){
            if (y == "0") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0A);
            else if (y == "#") SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0D);
            else if (y == "-1")SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09);
            cout << setw(4) << y;

        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
        cout << setw(2) << "     " << countN;
        cout << endl << endl;
        countN++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0f);
    cout << setw((arr[0].size()) * 4) << " " << "     "  << 'x';
    cout << endl;
    for (int i = 0; i < n; i++) cout << setw(4) << i;
    cout << setw(4) << 'y';
    cout << endl << endl;
}

void open(vector <vector<int>>& mine_map, vector <vector<string>>& player_map , int i, int j, int& countBox){
    stringstream ss;
    //int m = 5, n = 6;
    ss << mine_map[i][j];
    ss >> player_map[i][j];
    countBox--;
    //cout << "Open at: " << i << ' ' << j << " remain: " << countBox << endl;
    //printMap(player_map, m, n);
}

bool IsAlive(vector <vector<int>>& mine_map,vector <vector<string>>& player_map , int& i, int& j, int& countBox){
    open(mine_map, player_map, i, j, countBox);
    if (mine_map[i][j] == -1) return false;
    return true;
}

void generateMap(vector<vector<int>>& mine_map, int& m, int& n, int& k){
    srand(time(NULL));
    int bombs = k;
    while (bombs){
        int i = rand() % m , j = rand() % n;
        if (mine_map[i][j] != -1) {
            mine_map[i][j] = -1;
            bombs--;
            addCount(mine_map, i, j, m, n);
        }
    }
}

void spread_virus(vector<vector<int>>& mine_map, vector<vector<string>>& player_map, int i, int j, int& m, int& n, int& countBox){
    if (i-1 >= 0 && j-1 >= 0 && mine_map[i-1][j-1] != -1 && player_map[i-1][j-1] == "#"){
        open(mine_map, player_map, i-1, j-1, countBox);
        if (mine_map[i-1][j-1] == 0) spread_virus(mine_map, player_map, i-1, j-1, m, n, countBox);
    }
    if (i-1 >= 0 && mine_map[i-1][j] != -1 && player_map[i-1][j] == "#"){
        open(mine_map, player_map, i-1, j, countBox);
        if (mine_map[i-1][j] == 0) spread_virus(mine_map, player_map, i-1, j, m, n, countBox);
    }
    if (i-1 >= 0 && j+1 < n && mine_map[i-1][j+1] != -1 && player_map[i-1][j+1] == "#"){
        open(mine_map, player_map, i-1, j+1, countBox);
        if (mine_map[i-1][j+1] == 0) spread_virus(mine_map, player_map, i-1, j+1, m, n, countBox);
    }
    if (j-1 >= 0 && mine_map[i][j-1] != -1 && player_map[i][j-1] == "#"){
        open(mine_map, player_map, i, j-1, countBox);
        if (mine_map[i][j-1] == 0) spread_virus(mine_map, player_map, i, j-1, m, n, countBox);
    }
    if (j+1 < n && mine_map[i][j+1] != -1 && player_map[i][j+1] == "#"){
        open(mine_map, player_map, i, j+1, countBox);
        if (mine_map[i][j+1] == 0) spread_virus(mine_map, player_map, i, j+1, m, n, countBox);
    }
    if (i+1 < m && j-1 >= 0 && mine_map[i+1][j-1] != -1 && player_map[i+1][j-1] == "#"){
        open(mine_map, player_map, i+1, j-1, countBox);
        if (mine_map[i+1][j-1] == 0) spread_virus(mine_map, player_map, i+1, j-1, m, n, countBox);
    }
    if (i+1 < m && mine_map[i+1][j] != -1 && player_map[i+1][j] == "#"){
        open(mine_map, player_map, i+1, j, countBox);
        if (mine_map[i+1][j] == 0) spread_virus(mine_map, player_map, i+1, j, m, n, countBox);
    }
    if (i+1 < m && j+1 < n && mine_map[i+1][j+1] != -1 && player_map[i+1][j+1] == "#"){
        open(mine_map, player_map, i+1, j+1, countBox);
        if (mine_map[i+1][j+1] == 0) spread_virus(mine_map, player_map, i+1, j+1, m, n, countBox);
    }
}

void game(vector<vector<int>>& mine_map, vector<vector<string>>& player_map, int& m, int& n, int& k){
    bool alive = true;
    int countBox = n*m - k;
    while(countBox){
        //cout << countBox << endl;
        printMap(player_map, m, n);
        cout << "Enter a coordinate: ";
        int i, j;
        cin >> i >> j;
        system("cls");

        while (cin.rdstate() == 4 || i < 0 || j < 0 || i >= m || j >= n || player_map[i][j] != "#"){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            printMap(player_map, m, n);
            cout << "Coordinate not valid, please enter again: ";
            cin >> i >> j;
            cout << endl;
            system("cls");
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        if (!IsAlive(mine_map, player_map, i, j, countBox)){
            alive = false;
            break;
        }
        if (mine_map[i][j] == 0) spread_virus(mine_map, player_map, i, j, m, n, countBox);
    }
    printMap(player_map, m, n);
    if (!alive) cout << "   YOU'RE DEAD!";
    else cout << "YOU WON!";
}

void SetWindowSize(SHORT width, SHORT height)
{

    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
    COORD NewSize;
    NewSize.X = width+1;
    NewSize.Y = height+1;
    SetConsoleScreenBufferSize(hStdout, NewSize);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.dwFontSize.Y = 30;
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

int main()
{
    SetWindowSize(50, 22);
    int m, n ,k;
    getData(m, n, k);

    vector <vector<int>> mine_map(m, vector<int>(n, 0));
    vector <vector<string>> player_map(m, vector<string>(n, "#"));

    generateMap(mine_map, m, n, k);
    game(mine_map, player_map, m, n, k);

    return 0;
}
