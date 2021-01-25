#include<iostream>

using namespace std;

void solution(int num, int den);
int getGCD(int a, int b)
{
	return b ? getGCD(b, a%b) : a;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
    
	freopen("input.txt", "r", stdin);
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
                int num = 0; // numerator
                int den = 0; // denominator
                int gcd = 0;

                cin >> num;
                cin >> den;
                gcd = getGCD(num, den);

                num /= gcd;
                num /= gcd;

                cout << "input:: " << num << "/" << den << endl;
                solution(num,den);
        }
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

void solution(int num, int den){
        int div__[2] = {0,}; // [ 2^div__[0], 5^div__[1] ]

        int tmp_den = den;

        while(tmp_den != 1 && tmp_den%2 == 0 ){
                tmp_den /= 2;
                div__[0]++;
        }

        while(tmp_den != 1 && tmp_den%5 == 0 ){
                tmp_den /= 5;
                div__[1]++;
        }

        if(tmp_den == 1){
                cout << (float)num/den << endl;
                return;
        }

        cout << num/den << ".";
        num = num - (num/den) * den;

        int P = 0; // 순환소수 시작 위치
        int make_ten = 0;

        if( div__[0] > div__[1] ){
                P = div__[0] + 1;
                make_ten = div__[0] - div__[1];
                num *= pow(5,make_ten);
                den = tmp_den;
        }
        else{
                P = div__[1] + 1;
                make_ten = div__[1] - div__[0];
                num = (num << make_ten);
                den = tmp_den;
        }

        for(int i = 0; i < P; i++){
                cout << "0";
        }

        cout << num/den;
        num = num - (num/den) * den;
        cout << "(";

        int ten_power_of_n = 10;

        // 순환 소수의 길이
        int k = 1;
        for (k = 0; k < tmp_den; k++)
        {
                /* code */
        }
        

        // for(int n = 1; n < tmp_den; n++){
                
        //         for(k = 1; k*tmp_den < ten_power_of_n - 1; k++);

        //         if(k*tmp_den == ten_power_of_n - 1){
        //                 printf("k :: %d\n",k*tmp_den);
        //                 break;
        //         }
        //         ten_power_of_n *= 10;
        // }
        //cout << num << "/" << den << endl;
        //cout << "2^" << div__[0] << ":5^" << div__[1] << endl;
        
        cout << endl;
}