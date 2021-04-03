#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.3 17:45 ���� 19:13 ���� (1�ð���..)

/*
 - �ڽ��丮 ���� ����
   - �ڽ��丮�� �ּ� 2�̻��� ������ �޴���� ����
   - �׸��� 2�� �̻� �ֹ� �Ǿ��� �޴��θ� ����.

 - ���� �ֹ� �ߴ� �޴� ���� ���
 - ���� ���ǿ� ���� ������ �� course ���̿� �´� �޴� ��� ���� �ʾƵ� ��
 - ��½� ���ĺ� ������ ���
 - �ߺ��Ǵ� ������ �޴��� ��������� ���� ���
  

 - A ~ Z ������ bool Ÿ�� �迭�� ����� 
 - true �� ������ �̿��Ͽ� ���� ����� DFS Ž��, pair<string, int> Ÿ������ ����
 - ���� ��Ų������ ����
*/

vector<char> list_menu;							// �ѹ� �̻� �ֹ� ��� �޴�
vector <char> menu_selected;					// DFS Ž�� ��, ���յ� �޴�
vector<pair<vector<char>, int>> list_ordered;	// ���� �� ������ �ֹ� Ƚ�� 
vector<string> orders_;							// ���� �Է��� �ӽ� ���� ���� 
int max_count_order[11];						// Ȯ�� �� ������ �ִ� �ֹ� Ƚ��

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
		// �ش� ���� ��ŭ �޴� ������ ���� �Ǿ�����, �ֹ��� ��� Ȯ��
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
		DFS(0, n); // Ȯ�� �� ù��° �޴�����, ������ n��°���� �޴� Ȯ��
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