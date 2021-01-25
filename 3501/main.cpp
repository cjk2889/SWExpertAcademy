#include <math.h>

#include <iostream>

using namespace std;

void solution(int num, int den);
int getGCD(int a, int b) {
    return b ? getGCD(b, a % b) : a;
}

int main(int argc, char** argv) {
    int test_case;
    int T;

    //freopen("test.txt", "r", stdin);
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        int num = 0;  // numerator
        int den = 0;  // denominator
        int gcd = 0;

        cin >> num;
        cin >> den;
        gcd = getGCD(num, den);

        num /= gcd;
        num /= gcd;

        // cout << "input:: " << num << "/" << den << endl;
        cout << "#" << test_case << " ";
        solution(num, den);
    }
    return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}

void solution(int num, int den) {
    int div__[2] = {
        0,
    };  // [ 2^div__[0], 5^div__[1] ]
    int q = den;

    while (q != 1 && q % 2 == 0) {
        q /= 2;
        div__[0]++;
    }

    while (q != 1 && q % 5 == 0) {
        q /= 5;
        div__[1]++;
    }

    if (q == 1) {
        cout << (float)num / den << endl;
        return;
    }

    int P = 0;  // 순환소수 시작 위치
    int make_ten = 0;

    if (div__[0] > div__[1]) {
        div__[1] = div__[0];
        make_ten = div__[0] - div__[1];
        num *= pow(5, make_ten);
        den *= pow(5, make_ten);
    } else if (div__[0] < div__[1]) {
        div__[0] = div__[1];
        make_ten = div__[1] - div__[0];
        num = (num << make_ten);  // 2^make_ten
        den = (den << make_ten);
    }

    // 10^k === 1 mod q
    // k = 순환 마디 길이
    int k = 1;
    int power_of_n = 10;
    while (true) {
        if (power_of_n % q == 1) {
            break;
        }
        power_of_n = (power_of_n * 10) % q;
        k++;
    }
    //cout << endl << k << endl;

    cout << num / den << ".";
    num = num - (num / den) * den;

    int n = num * 10;
    for (int i = 0; i < div__[0]; i++) {
        cout << (n / den);
        n = (n % den) * 10;
    }

    // 순환 소수 구하기
    cout << "(";
    for (int i = 0; i < k; i++) {
        cout << (n / den);
        n = (n % den) * 10;
    }
    cout << ")" << endl;
}