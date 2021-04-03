#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// 2021.4.3 13:50 ����, 15:40�� ����

/*
- ���� ���� : N, map, list_ball(��ģ ��ġ ���)
- ���̾ : m,d,s (����,����,�ӷ�)

- ���̾ �̵�, ��ġ�� ����(map���� ����Ʈ ���·� ����).
- ����
  - �̵� > ��ü > 4���� �ٽ� ���� > ������ 0�̸� �Ҹ�

  - �̵� ��, 2�� ���������� list_ball�� ��ǥ �߰�.
    - 2���϶��� �߰��ص� ��, �� �̻� ��� ������ �ߺ� ��ǥ �߰�.
  - ���ƴٰ� �ٽ� 4���� ���������� ���ڸ��� �״�� ���������� 

*/

typedef struct info_fireball {
	int m, d, s;
} fireball;

int N, M, K;
int dd[][8] = { {-1,-1,0,1,1,1,0,-1},{0,1,1,1,0,-1,-1,-1} };

vector < vector< vector<fireball> > > map, map_next;
vector< pair<int, int> > list_merge;


void print_map(int val) {
	cout << "==========================================" << endl;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			cout.width(2);
			cout.fill(' ');
			if(val ==0)
				cout << map[c][r].size() << " ";
			else if(val == 1)
				cout << map_next[c][r].size() << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool check_dir(int c, int r) {
	if (c < 0 || c >= N) {
		return false;
	}
	if (r < 0 || r >= N) {
		return false;
	}

	return true;
}

void moving(int c, int r, fireball ball) {

	// �ӵ� s�� N���� Ŭ���� �ֱ� ������ N�� ��������ŭ �̵�
	int c_next = c + (dd[0][ball.d] * ball.s) % N;	
	int r_next = r + (dd[1][ball.d] * ball.s) % N;

	// �̵��ߴµ� �ε����� ��� ���̸� �ٽ� ����
	if (c_next < 0) {
		c_next = N + c_next;
	}
	else if (c_next >= N) {
		c_next = c_next - N;;
	}

	if (r_next < 0) {
		r_next = N + r_next;
	}
	else if (r_next >= N) {
		r_next = r_next - N;;
	}

	// ��� �� ��ġ�� ���̾ �߰�
	map_next[c_next][r_next].push_back(ball);


	// �ش� ��ġ�� ���̾�� 2���� �Ǹ� ���ľ� �� ��ġ ����Ʈ�� ��ǥ �߰�
	// 3�� �̻���ʹ� �� �ʿ� ����, ������ �ߺ� ó�� ���� �߻�
	if (map_next[c_next][r_next].size() == 2) {
		list_merge.push_back(pair<int, int>(c_next, r_next));
	}
}

void move_ball() {
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			//���̾�� ������ �н�
			if (map[c][r].size() == 0) {
				continue; 
			}

			// ���̾�� ������ next_map���� �̵��� ��ġ�� ���
			
			while(map[c][r].size()>0){
				fireball ball_cur = map[c][r].front();
				map[c][r].erase(map[c][r].begin());

				moving(c, r, ball_cur);
			}
		}
	}
}

void merge_ball() {

	while (list_merge.size() > 0) {
		// �̵��ϸ鼭 ������ ��ģ ��ǥ�� �Ѱ��� �ҷ����� ó��
		int c = list_merge.front().first;
		int r = list_merge.front().second;
		list_merge.erase(list_merge.begin());

		bool same = true;
		int d, m, s;
		m = s = 0;
		d = map_next[c][r][0].d % 2;

		for (int i = 0; i < map_next[c][r].size(); i++) {
			//��ġ�� ��ġ���� ���̾�� �ϳ��� ������ ���� ���.
			m += map_next[c][r][i].m;
			s += map_next[c][r][i].s;

			if (map_next[c][r][i].d % 2 != d) {
				//�ϳ��� Ȧ¦�� Ʋ���� ������ üũ
				same = false;
			}
		}

		m = m / 5;
		s = s / map_next[c][r].size();

		map_next[c][r].clear();

		if (m > 0) {
			//������ ���� �ϸ� 4���� fireball �߰�
			for (int i = 0; i < 4; i++) {
				fireball tmp;
				tmp.m = m;
				tmp.s = s;
				if (same) {
					// ���� Ȧor¦�̿��ٸ�, ¦�� ����
					tmp.d = i * 2;
				}
				else {
					// �ƴϸ� Ȧ�� ����
					tmp.d = i * 2 + 1;
				}				

				map_next[c][r].push_back(tmp);
			}
		}

	}
}

int count_mass() {
	int sum = 0;
	for (int c = 0; c < N; c++) {
		for (int r = 0; r < N; r++) {
			// �������ִ��� Ȯ�� �ʿ�
			for (int i = 0; i < map[c][r].size(); i++) {
				sum += map[c][r][i].m;
			}
		}
	}

	return sum;
}

int solution() {

	while (K > 0) {
		map_next = vector < vector< vector<fireball> > >(N, vector< vector<fireball> >(N)); 

		move_ball();	// ���̾ �̵�
		//print_map(1);
		merge_ball();	// ��ģ ���̾ ��ġ�� & �й�
		
		K--;
		map = map_next;	// �� ����
		//print_map(0);
	}

	return count_mass();// �� ���� ���
}

int main() {
	cin >> N >> M >> K;
	map = vector < vector< vector<fireball> > >(N, vector< vector<fireball> >(N));

	for (int m = 0; m < M; m++) {
		fireball tmp;
		int c, r;

		cin >> c >> r >> tmp.m >> tmp.s >> tmp.d;
		map[c-1][r-1].push_back(tmp);
	}
	//print_map(0);
	cout << solution();


	return 0;
}