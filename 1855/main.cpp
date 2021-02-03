#include <iostream>
#include <queue>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long int uint64;

int parent[100000][23];
int depth[100000];
bool visit[100000];
int n;
vector<vector<int>> w;

void bfs_depth() {
    queue<pair<int,int>> q;
    q.push(make_pair(0,0));
    visit[0] = true;

    while (!q.empty()) {
        int v = q.front().first;
        int dep = q.front().second;
        depth[v] = dep;
        q.pop();
        for (int i = 0; i < w[v].size(); i++) {
            int n = w[v][i];
            if (!visit[n]) {
                visit[n] = true;
                parent[n][0] = v;
                q.push(make_pair(n,dep+1));
            }
        }
    }
}

int lca(int x, int y, int max_height) {
    if(depth[x] > depth[y])
        swap(x,y);
    for(int i = max_height; i >=0; i--) {
        if(depth[y] - depth[x] >= (1 << i))
            y = parent[y][i];
    }
    if(x == y)  return x;
    for(int i = max_height; i >= 0; i--) {
        if(parent[x][i] != parent[y][i]) {
            x = parent[x][i];
            y = parent[y][i];
        }
    }
    return parent[x][0];
}

uint64 solution(int max_height){
    uint64 ret = 0;
    int tmp_v = 0;
    queue<int> q;
    q.push(0);
    visit[0] = true;

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        int lca_ = lca(tmp_v, v, max_height);

        ret += depth[tmp_v] - depth[lca_];
        ret += depth[v] - depth[lca_];

        tmp_v = v;
        for (int i = 0; i < w[v].size(); i++) {
            int n = w[v][i];
            if (!visit[n]) {
                visit[n] = true;
                q.push(n);
            }
        }
    }
    return ret;
}


int main(int argc, char** argv) {
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        cin >> n;

        memset(parent,0,sizeof(parent));
        memset(depth,0,sizeof(depth));
        memset(visit,0,sizeof(visit));  
        w.clear();
        w.resize(n);

        int log2_n = (int)floor(log2(n));

        for(int i = 1; i < n; i++){
            int x = 0;
            cin >> x;
            w[x-1].push_back(i);
        }

        for(int i = 0; i < n; i++){
            sort(w[i].begin(), w[i].end());
        }

        bfs_depth();
        memset(visit,0,sizeof(visit));  

        for(int i = 1 ; i < log2_n; i++){
            for(int j = 0; j < n; j++){
                parent[j][i] = parent[ parent[j][i-1] ][i-1];
            }
        }
        
        cout << "#" << test_case << " " << solution(log2_n) <<endl;
    }
    return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}