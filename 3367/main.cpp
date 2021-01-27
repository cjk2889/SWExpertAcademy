#include <stdlib.h>
#include <iostream>
#include <limits>

#define INF 999999

using namespace std;

int* input;
int* sum;
int** d;

int solution(int s, int e);

int main(int argc, char **argv) {
    int test_case;
    int T;

    freopen("input.txt", "r", stdin);
    cin >> T;
    cout << T << endl;

    for (test_case = 1; test_case <= T; ++test_case) {
        int k = 0;

        cin >> k;
        
        input = (int*)malloc(sizeof(int) * k);
        sum = (int*)malloc(sizeof(int) * k);

        d = (int**)malloc(sizeof(int*) * k);

        for (int i = 0; i < k; i++) {
            cin >> input[i];
            sum[i] = (i != 0) ? sum[i - 1] + input[i] : input[i];

            d[i] = (int*)malloc(sizeof(int) * k);

            for (int j = 0; j < k; j++) {
                d[i][j] = INF;
            }
        }

// -- input test -- 
        cout << "input Test " << k << " ::";
        for (int i = 0; i < k; i++) {
            cout << ' ' << input[i];
        }
        cout << endl;

// -- output --
        cout << "#" << test_case << " " << solution(0, k - 1) << endl;

// -- free --
        for (int i = 0; i < k; i++) {
            free(*(d + i));
        }
        free(d);
        free(sum);
        free(input);
    }
    return 0; 
}

int solution(int s, int e) {
    if(s >= e)
        return 0;
    if( s + 1 == e)
        return input[s] + input[e];
    
    for( int i = s; i < e; i++){
        int tmp = solution(s,i) + solution(i+1, e) + sum[e] - sum[s-1];
        d[s][e] = (d[s][e] > tmp) ? tmp : d[s][e];
    }

    return d[s][e];
}
