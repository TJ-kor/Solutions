#include <string>
#include <iostream>
#include <vector>

using namespace std;
//2021.4.3 16:45 시작 17:15 종료

/*
 - 전역 변수 : N(길이), 

 - N >= 3 && N <= 15
 - 특수문자는 - _ ,
 - . 는 첫,끝,연속 X


*/

string solution(string new_id) {
	string answer = "";
	
	// 2. 특수문자 제거
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] >= 'A' &&new_id[i] <= 'Z') {
			// 1. 소문자 치환
			new_id[i] += ('a'-'A');
		}
		else if( (new_id[i] >='0'&& new_id[i] <= '9') ||
			(new_id[i] >= 'a' && new_id[i] <= 'z') ||
			(new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.') ){
			continue;
		}
		else {
			new_id.erase(new_id.begin() + i);
			i--;
		}
	}

	// 3. 중복 . 제거
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {
			
			while (true) {
				if (i+1 == new_id.size())
					break;
				
				//다음 인덱스의 값이 중복이면 제거
				if (new_id[i + 1] == '.') {
					new_id.erase(new_id.begin() + i + 1);
				}
				else {
					// 중복이 아니면 break.
					break;
				}
			}
		}
	}

	// 4. 처음과 끝의 . 제거
	while (new_id[0] == '.') {
		new_id.erase(new_id.begin());
	}
	while (new_id[new_id.size()-1] == '.') {
		new_id.erase(new_id.begin() + new_id.size() - 1);
	}

	// 5. 빈문자열이면 "a" 추가
	if (new_id.size() == 0) {
		new_id = "a";
	}

	// 6. 앞문자 15개 빼고 뒤로 전부 제거
	if (new_id.size() >= 16)
	{
		new_id = new_id.substr(0, 15);
	}

	// 4.
	while (new_id[new_id.size() - 1] == '.') {
		new_id.erase(new_id.begin() + new_id.size() - 1);
	}

	// 7. 길이가 2 이하면 3이 될 때 까지 뒤로 늘리기
	while (new_id.size() < 3) {
		new_id.insert(new_id.begin() + new_id.size() - 1, new_id[new_id.size() - 1]);
	}

	//cout << new_id;

	return answer;
}

int main() {
	string new_id = "...!@BaT#*..y.abcdefghijklm";

	cout << solution(new_id) << endl;

	return 0;
}