#include <string>
#include <iostream>
#include <vector>

using namespace std;
//2021.4.3 16:45 ���� 17:15 ����

/*
 - ���� ���� : N(����), 

 - N >= 3 && N <= 15
 - Ư�����ڴ� - _ ,
 - . �� ù,��,���� X


*/

string solution(string new_id) {
	string answer = "";
	
	// 2. Ư������ ����
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] >= 'A' &&new_id[i] <= 'Z') {
			// 1. �ҹ��� ġȯ
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

	// 3. �ߺ� . ����
	for (int i = 0; i < new_id.size(); i++) {
		if (new_id[i] == '.') {
			
			while (true) {
				if (i+1 == new_id.size())
					break;
				
				//���� �ε����� ���� �ߺ��̸� ����
				if (new_id[i + 1] == '.') {
					new_id.erase(new_id.begin() + i + 1);
				}
				else {
					// �ߺ��� �ƴϸ� break.
					break;
				}
			}
		}
	}

	// 4. ó���� ���� . ����
	while (new_id[0] == '.') {
		new_id.erase(new_id.begin());
	}
	while (new_id[new_id.size()-1] == '.') {
		new_id.erase(new_id.begin() + new_id.size() - 1);
	}

	// 5. ���ڿ��̸� "a" �߰�
	if (new_id.size() == 0) {
		new_id = "a";
	}

	// 6. �չ��� 15�� ���� �ڷ� ���� ����
	if (new_id.size() >= 16)
	{
		new_id = new_id.substr(0, 15);
	}

	// 4.
	while (new_id[new_id.size() - 1] == '.') {
		new_id.erase(new_id.begin() + new_id.size() - 1);
	}

	// 7. ���̰� 2 ���ϸ� 3�� �� �� ���� �ڷ� �ø���
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