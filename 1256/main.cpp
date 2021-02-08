#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

vector<string> str;

int main(int argc, char** argv)
{
	int test_case;
	int T;
	freopen("input.txt", "r", stdin);
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
    string s = "";
    int n = 0;
    cin >> n;
    cin >> s;
    str.clear();

    for(int i = 0; i < s.length(); i++){
      str.push_back(s.substr(i));
    }
    sort(str.begin(),str.end());

    cout << "#" << test_case << " " << str[n-1] << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}