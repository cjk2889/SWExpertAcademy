#include <cstring>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

#define INF 999999

int N;
int map[1000][1000];
int dist[1000];

int dij(int s, int e) {
    memset(dist, INF, sizeof(dist));
    priority_queue<int> q;

    q.push(s);
    dist[s] = 0;

    while(!q.empty()){
        int v = q.top();
        q.pop();

        for(int j = 0; j <= e; j++){
            if(dist[j] > dist[v] + map[v][j]){
                dist[j] = dist[v] + map[v][j];
                q.push(j);
            }
        }
    }

    int sum = 0;
    for(int i = 0; i < N; i++)
        sum+= dist[i];
    return sum;
}

int main(int argc, char** argv) {
    int test_case;
    int T;
    freopen("input.txt", "r", stdin);
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case) {
        memset(map, INF, sizeof(map));
        cin >> N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cin >> map[i][j];
                map[i][j] = map[i][j] == 0 ? INF: map[i][j];
            }
        }

        int min_ = INF;
        for(int i = 0; i < N; i++){
            min_ = min(min_,dij(i,N-1));
        }

        cout << "#" << test_case << " " << min_ << endl;
        
    }
    return 0; 
}