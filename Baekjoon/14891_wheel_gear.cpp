#include <iostream>
#include <string>
#include <vector>
#include <deque>

using namespace std;

//2021.4.21 15:30 시작 16:10 종료

int K;
vector<deque <bool>> gear;

 void rotate(int num_gear, int dir, int prev_num) {
	 bool same_L, same_R;
	 same_L = same_R = true;

	 // 좌,우 회전시켜야 할것이 있는지 체크
	 if (num_gear - 1 >= 0 && prev_num != num_gear - 1) {
		 if (gear[num_gear - 1][2] != gear[num_gear][6])
			 same_L = false;
	 }
	 if (num_gear + 1 < 4 && prev_num != num_gear + 1) {
		 if (gear[num_gear + 1][6] != gear[num_gear][2])
			 same_R = false;
	 }

	 if (dir == 1) {
		 // 시계방향 회전
		 gear[num_gear].push_front(gear[num_gear].back());
		 gear[num_gear].pop_back();
	 }
	 else {
		 gear[num_gear].push_back(gear[num_gear].front());
		 gear[num_gear].pop_front();
	 }

	 if (dir == 1) dir = - 1;
	 else dir = 1;

	 if (!same_L) rotate(num_gear - 1, dir, num_gear);
	 if (!same_R) rotate(num_gear + 1, dir, num_gear);
}

int solution() {
	int score = 0;

	while (K--) {
		int num_gear;
		int dir;
		cin >> num_gear >> dir;
		num_gear--;
		rotate(num_gear, dir, 100);
	}

	if (gear[0].front() == 1) score += 1;
	if (gear[1].front() == 1) score += 2;
	if (gear[2].front() == 1) score += 4;
	if (gear[3].front() == 1) score += 8;
	return score;
}
int main() {
	gear = vector<deque <bool>>(4);
	for (int i = 0; i < 4; i++) {
		string input_;
		cin >> input_;
		for (int j = 0; j < 8; j++) {
			if(input_[j] == '1')
				gear[i].push_back(1);
			else
				gear[i].push_back(0);
		}
	}
	cin >> K;

	cout << solution();;
	return 0;
}