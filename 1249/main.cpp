#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <queue>

#define INF 100000

// typedef unsigned char int;

using namespace std;

int** matrix;
int** dist;

int solution(int N);

int main(int argc, char** argv) {
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
// -- get input --
        int N = 0;
        char buffer[256] = {
            0,
        };

        cin >> N;
        matrix = (int**)malloc(sizeof(int*) * N);
        for (int i = 0; i < N; i++) {
            cin >> buffer;
            matrix[i] = (int*)malloc(sizeof(int) * N);
            for (int j = 0; j < N; j++) {
                matrix[i][j] = (int)buffer[j] - '0';
            }
        }
// -- get result --
        cout << "#" << test_case << " " << solution(N) << endl;

// -- input test --
        // for(int i = 0; i < N; i++){
        //     for(int j = 0; j < N; j++){
        //         printf("%d ",matrix[i][j]);
        //     }
        //     printf("\n");
        // }

// -- free --
        for (int i = 0; i < N; i++) {
            free(*(matrix + i));
        }
        free(matrix);
    }
    return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}

int solution(int N) {
    int dir_r[4] = {-1, 1, 0, 0};
    int dir_c[4] = {0, 0, -1, 1};

    int ret = 0;

    queue<pair<int,int>> q;

// -- init data --
    dist = (int**)malloc(sizeof(int*) * N);
    for (int i = 0; i < N; i++) {
        dist[i] = (int*)malloc(sizeof(int) * N);
        for (int j = 0; j < N; j++) {
            dist[i][j] = INF;
        }
    }
    dist[0][0] = 0;
    q.push(pair<int,int>(0,0));

// -- dijkstra algorithm --
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();

        //        (-1,0)
        // (0,-1) ( 0,0) (0,1)
        //        ( 1,0)
        for (int i = 0; i < 4; i++) {
            int tmp_r = r + dir_r[i];
            int tmp_c = c + dir_c[i];

            if ( tmp_r >= 0 && tmp_r < N && tmp_c >= 0 && tmp_c < N ){
                int tmp_dist = matrix[tmp_r][tmp_c] + dist[r][c];
                if(tmp_dist < dist[tmp_r][tmp_c]){
                    q.push(pair<int, int>(tmp_r, tmp_c));
                    dist[tmp_r][tmp_c] = tmp_dist;
                }
            }
        }
    }
    ret = dist[N-1][N-1];

// -- test code
    // for (int x = 0; x < N; x++) {
    //     for (int y = 0; y < N; y++) {
    //         if (dist[x][y] == 100000)
    //             printf("x ");
    //         else
    //             printf("%d ", dist[x][y]);
    //     }
    //     printf("\n");
    // }
    
// -- free --
    for (int i = 0; i < N; i++) {
        free(*(dist + i));
    }
    free(dist);

    return ret;
}