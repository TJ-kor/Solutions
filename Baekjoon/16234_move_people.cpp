#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 2021.4.20 13:05 ���� 14:15 ����

int dd[][4] = { {-1,0,1,0},{0,1,0,-1} };

int N, L, R; 
vector <vector <int> > A;

bool check_dd(int c, int r) {
	if (c < 0 || c >= N) return false;
	if (r < 0 || r >= N) return false;
	return true;
}

void print_A() {
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout.width(3);
			cout.fill(' ');
			cout << A[c][r] << " " ;
		}
		cout << endl;
	}
	cout << endl;
}

vector<vector<pair<int,int>>> BFS() {
	vector<vector<pair<int, int>>> list_union;
	vector <vector <int> > visit_map = vector <vector <int> >(N, vector <int>(N, 0));
	vector<pair<int, int>> union_;
	vector<pair<int, int> > queue_;


	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			if (visit_map[c][r] != 0) continue;
			int sum = 0;
			int count = 0;
			queue_.clear();
			union_.clear();

			queue_.push_back(pair<int, int>(c, r));
			union_.push_back(pair<int, int>(c, r));
			visit_map[c][r] = 1;
			sum += A[c][r];
			count++;

			while (queue_.size() > 0) {
				//�湮�� ���� ���� ����� BFS Ž�� ����.
				int c_ = queue_.front().first;
				int r_ = queue_.front().second;
				queue_.erase(queue_.begin());

				for (int dir = 0; dir < 4; dir++) {
					//���� ��ġ���� 4�� ���� ���� üũ
					int c_t = c_ + dd[0][dir];
					int r_t = r_ + dd[1][dir];

					if (check_dd(c_t, r_t) == true
						&& visit_map[c_t][r_t] == 0
						&& abs(A[c_][r_] - A[c_t][r_t]) >= L
						&& abs(A[c_][r_] - A[c_t][r_t]) <= R) {
						// ������ ����� L,R üũ �� union�� �߰�
						queue_.push_back(pair<int, int>(c_t, r_t));
						union_.push_back(pair<int, int>(c_t, r_t));

						visit_map[c_t][r_t] = 1;
						sum += A[c_t][r_t];
						count++;
					}
				}
			}

			//���� �� ����� �߰�.
			if (union_.size() >= 2) {
				union_.push_back(pair<int, int>(sum, count));
				list_union.push_back(union_);
			}
		}
	}

	return list_union;
}

bool move_people(vector<vector<pair<int, int>>> list_union) {
	bool ismoved = false;

	for (auto union_ : list_union) {
		int sum = union_.back().first;
		int count = union_.back().second;
		int ave = sum / count;

		for (int i = 0; i < union_.size() - 1; i++) 
			A[union_[i].first][union_[i].second] = ave;

		ismoved = true;
	}
	return ismoved;
}

int solution() {
	int t = 0;

	bool ismoved = false;
	while (true) {
		// BFS�� ���� ������ ������ �������� Ȯ��.
		// ���� �������� ����Ʈ���� �����Ͽ� ��հ� �Ҵ�.
		ismoved = move_people(BFS());
		if (!ismoved) break;
		t++;
	}

	return t;
}

int main() {
	cin >> N >> L >> R;

	A = vector <vector <int> >(N, vector <int>(N, 0));

	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cin >> A[c][r];
		}
	}

	cout << solution();

	return 0;
}