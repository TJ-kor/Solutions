#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.3 17:45 시작 19:13 종료 (1시간반..)

/*
 - 코스요리 구성 조건
   - 코스요리는 최소 2이상의 길이의 메뉴들로 구성
   - 그리고 2번 이상 주문 되었던 메뉴로만 구성.

 - 많이 주문 했던 메뉴 먼저 출력
 - 구성 조건에 맞지 않으면 꼭 course 길이에 맞는 메뉴 출력 하지 않아도 됨
 - 출력시 알파벳 순으로 출력
 - 중복되는 길이의 메뉴가 여러개라면 전부 출력
  

 - A ~ Z 까지의 bool 타입 배열을 만들고 
 - true 인 값들을 이용하여 조합 만들고 DFS 탐색, pair<string, int> 타입으로 저장
 - 많이 시킨순으로 정렬
*/

vector<char> list_menu;							// 한번 이상 주문 됬던 메뉴
vector <char> menu_selected;					// DFS 탐색 중, 조합된 메뉴
vector<pair<vector<char>, int>> list_ordered;	// 선택 된 조합의 주문 횟수 
vector<string> orders_;							// 문제 입력의 임시 전역 변수 
int max_count_order[11];						// 확인 된 조합의 최대 주문 횟수

void check_menu(vector<string> orders) {
	bool menu[26];
	memset(menu, false, sizeof(menu));

	for (int i = 0; i < orders.size(); i++) {
		for (int j = 0; j < orders[i].size(); j++) {
			int idx = orders[i][j] - 'A';

			menu[idx] = true;
		}
	}

	for (int i = 0; i < 26; i++) {
		if (menu[i] == true) {
			list_menu.push_back('A'+i);
		}
	}
}

void count_order() {
	int count = 0;
	for (int j = 0; j < orders_.size(); j++) {
		bool state;

		for (int i = 0; i < menu_selected.size(); i++) {
			state = false;
			for (int k = 0; k < orders_[j].size(); k++) {
				if (orders_[j][k] == menu_selected[i]) {
					state = true;
					break;
				}
			}

			if (!state)
				break;
		}

		if (state) {
			count++;
		}
	}
	
	if (count >= 2) {
		list_ordered.push_back(pair<vector<char>, int>(menu_selected, count));

		if (max_count_order[menu_selected.size()] < count) {
			max_count_order[menu_selected.size()] = count;
		}
	}
}

void DFS(int idx_start, int cnt_selected) {

	if (cnt_selected == 0) {
		// 해당 갯수 만큼 메뉴 조합이 선택 되었으면, 주문한 기록 확인
		count_order();
	}
	else {
		for (int i = idx_start; i <= list_menu.size() - cnt_selected; i++) {
			menu_selected.push_back(list_menu[i]);

			DFS(i + 1, cnt_selected - 1);

			menu_selected.erase(menu_selected.begin() + menu_selected.size() - 1);
		}
	}

}

void sort_menu(vector<int> course) {
	orders_.clear();

	for (int i = 0; i < course.size(); i++) {
		int sz_course = course[i];

		for (int j = 0; j < list_ordered.size(); j++) {

			if (list_ordered[j].first.size() == sz_course && max_count_order[sz_course] == list_ordered[j].second) {

				string tmp(list_ordered[j].first.begin(), list_ordered[j].first.end());


				if (orders_.size() == 0) {
					orders_.push_back(tmp);
				}
				else {
					int k = 0;

					while ( k < orders_.size()){
						if (strcmp(tmp.c_str(), orders_[k].c_str()) < 0) {
							break;
						}
						k++;
					}
					orders_.insert(orders_.begin() + k, tmp);
				}
				
			}
		}

	}
}


vector<string> solution(vector<string> orders, vector<int> course) {
	orders_ = orders;
	memset(max_count_order, 0, sizeof(max_count_order));
	vector<string> answer;

	check_menu(orders);

	int max_sz_course = course.size();

	for (int n = 2; n <= course[max_sz_course - 1]; n++) {
		DFS(0, n); // 확인 된 첫번째 메뉴부터, 끝에서 n번째까지 메뉴 확인
	}
	sort_menu(course);

	return orders_;
}

int main() {
	vector<string> orders = { "XYZ", "XWY", "WXA" };
	vector<int> course = { 2,3,4 };

	vector<string> answer = solution(orders, course);

	for (int i = 0; i < answer.size(); i++) {
		cout << answer[i] << endl;
	}

	return 0;
}