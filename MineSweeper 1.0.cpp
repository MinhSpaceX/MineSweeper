#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <stdlib.h>
#include <sstream>

using namespace std;

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
    for (auto x:arr){
        for (auto y:x) cout << setw(2) << y << ' ';
        cout << endl;
    }
}

bool IsAlive(vector <vector<int>>& mine_map,vector <vector<string>>& player_map , int i, int j){
    stringstream ss;
    ss << mine_map[i][j];
    ss >> player_map[i][j];
    if (mine_map[i][j] == -1) return false;
    return true;
}

int main()
{
    int m, n ,k;
    cin >> m >> n >> k;
    cin.clear();
    cin.ignore();
    vector <vector<int>> mine_map(m, vector<int>(n, 0));
    vector <vector<string>> player_map(m, vector<string>(n, "#"));
    srand(time(NULL));
    while (k){
        int i = rand() % m , j = rand() % n;
        if (mine_map[i][j] != -1) {
            mine_map[i][j] = -1;
            k--;
            addCount(mine_map, i, j, m, n);
        }
    }

    bool alive = true;

    for (int box = 0; box < n*m-k; box++) {
        cout << "Enter a coordinate: ";
        int i, j;
        cin >> i >> j;
        cin.clear();
        cin.ignore();
        if (!IsAlive(mine_map, player_map, i, j)) alive = false;
        printMap(player_map);
        if (!alive) break;
    }
    if (!alive) cout << "YOU'RE DEAD!";
    else cout << "YOU WON!";
    return 0;
}
