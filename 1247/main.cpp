#include <iostream>

using namespace std;

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define INF 100000

int G[13][13];

int dfs(int v, int N, bool visit[], int cnt) {
    bool copy_visit[13] = {false};

    copy(visit, visit + 13, copy_visit);

    copy_visit[v] = true;
    if (cnt == N - 1) {
        return G[v][1];
    }

    int min = INF;
    for (int i = 2; i < N; i++)
        if (G[v][i] != INF && !copy_visit[i]) {
            copy_visit[v] = true;
            int sum = G[v][i] + dfs(i, N, copy_visit, cnt + 1);
            if (sum < min) min = sum;
        }
    copy_visit[v] = false;
    return min;
}

int main(int argc, char** argv) {
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        int N, x[12], y[12];

        cin >> N;
        for (int i = 0; i < N + 2; i++) {
            cin >> x[i];
            cin >> y[i];
        }

        bool visit[13] = {false};
        for (int i = 0; i < 13; i++) {
            visit[i] = false;
            for (int j = 0; j < 13; j++) {
                if (i == j || i >= N + 2 || j >= N + 2)
                    G[i][j] = INF;
                else
                    G[i][j] = ABS(x[i] - x[j]) + ABS(y[i] - y[j]);
            }
        }

        printf("#%d %d\n", test_case, dfs(0, N + 2, visit, 1));
    }
    return 0;
}