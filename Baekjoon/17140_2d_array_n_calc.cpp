#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
// 2021.4.14 14:45 시작 16:45 종료

/*
 - R: 행마다 옆으로 정렬
 - C: 열마다 아래로 정렬
 - 정렬기준
	1. 숫자(val)의 등장 횟수 작은게 먼저
	2. 수(key)의 크기 작은 게 먼저
 - 길이가 안맞는 줄은 0으로 채우기
 - 길이가 100 넘으면 삭제.
 - map 사이즈가 커지면 행렬 대각 변환?


 - 연산
  - 행마다 map 만들기
	- max_sz : 최대 map 사이즈 계산
  - key, val에 따라서 정렬 된 벡터<pair> 생성



  @@ 어차피 결국 sorting 하고 넣는 과정에서 두개로 나뉜 연산을 하게됨.... 
  - 최대 map 사이즈가 열의 길이보다 작으면 열의 방향으로 채우기.
	- 하는 이유 : C연산을 할 필요가 없어짐. 변환상태 체크. 


  @@ sorting_C 함수에서 push_back 할때 사이즈 실수함...
*/

int c_target, r_target, K;
bool state_trans;
vector< vector< int > > arr;
vector<map <int, int>> list_map;

void print_arr() {
	for (int c = 0; c < arr.size(); c++) {
		for (int r = 0; r < arr[c].size(); r++) {
			cout << arr[c][r] << " ";
		}
		cout << endl;
	}
	cout << endl;
}



void sorting_R(int max_sz) {
	

	for (int c = 0; c < list_map.size(); c++) {
		vector<pair<int, int>> list_pair;

		//행 마다 계산된 맵에서 하나씩 꺼내어 벡터 순서대로 삽입
		for (auto elem : list_map[c]) {
			if (elem.first == 0) continue;
			if (list_pair.size() == 0) {
				list_pair.push_back(pair<int, int>(elem.first, elem.second));
			}
			else {
				int i = 0;
				for (i = 0; i < list_pair.size(); i++) {
					if (elem.second > list_pair[i].second) continue;
					if (elem.second == list_pair[i].second 
						&& elem.first > list_pair[i].first) continue;

					//알맞은 자리 i 를 찾으면 for loop 종료
					break;
				}

				// 알맞는 자리 i에 삽입
				list_pair.insert(list_pair.begin() + i, pair<int, int>(elem.first, elem.second));
			}
		}

		// 해당 행의 길이를 최대로 맞춤
		arr[c] = vector<int>(max_sz);
		
		int i = 0;
		while (true) {
			if (i == max_sz / 2) break;

			if (i < list_pair.size()) {
				// 맵에 구성된 키의 갯수 만큼 할당
				arr[c][i * 2] = list_pair[i].first;
				arr[c][i * 2 + 1] = list_pair[i].second;
			}
			else {
				// 나머지는 0으로 채움
				arr[c][i * 2] = 0;
				arr[c][i * 2 + 1] = 0;
			}

			i++;
		}
	}
}
void sorting_C(int max_sz) {
	while (true) {
		//길이 맞추기
		if (arr.size() == max_sz) break;
		arr.push_back(vector<int>(arr[0].size(), 0));
	}

	for (int r = 0; r < list_map.size(); r++) {
		vector<pair<int, int>> list_pair;


		for (auto elem : list_map[r]) {
			if (elem.first == 0) continue;
			if (list_pair.size() == 0) {
				list_pair.push_back(pair<int, int>(elem.first, elem.second));
			}
			else {
				int i = 0;
				for (i = 0; i < list_pair.size(); i++) {
					if (elem.second > list_pair[i].second) continue;
					if (elem.second == list_pair[i].second
						&& elem.first > list_pair[i].first) continue;

					break;
				}
				list_pair.insert(list_pair.begin() + i, pair<int, int>(elem.first, elem.second));
			}
		}


		
		int i = 0;
		
		while (true) {
			if (i == max_sz / 2) break;

			if (i < list_pair.size()) {
				arr[i * 2][r] = list_pair[i].first;
				arr[i * 2 + 1][r] = list_pair[i].second;
			}
			else {
				arr[i * 2][r] = 0;
				arr[i * 2 + 1][r] = 0;
			}

			i++;
		}
	}
}

void R() {

	int max_c = arr.size();
	int max_r = arr[0].size();
	list_map = vector<map <int, int>>(max_c);

	for (int c = 0; c < arr.size(); c++) {
		for (int r = 0; r < arr[c].size(); r++) {
			if (arr[c][r] == 0) continue;

			//각 행 별로 맵을 생성 및 숫자별 횟수 추가
			list_map[c][arr[c][r]] += 1;
		}

		// 행의 최대 길이 반영
		if (max_r < list_map[c].size() * 2)
			max_r = list_map[c].size() * 2;
	}

	if (max_r > 100) max_r = 100;

	// 숫자 크기에 따라 정렬 후 행렬에 반영
	sorting_R(max_r);
}


void C() {
	int max_c = arr.size();
	int max_r = arr[0].size();
	list_map = vector<map <int, int>>(max_r);

	for (int r = 0; r < arr[0].size(); r++) {
		for (int c = 0; c < arr.size(); c++) {
			if (arr[c][r] == 0) continue;

			//각 열 별로 맵을 생성 및 숫자별 횟수 추가
			list_map[r][arr[c][r]] += 1;
		}

		if (max_c < list_map[r].size() * 2)
			max_c = list_map[r].size() * 2;
	}

	if (max_c > 100) max_c = 100;

	sorting_C(max_c);
}

int solution() {
	int t = 0;

	while (t<= 100) {
		// 체크하는 행렬의 요소가 현재 행렬 크기를 안벗어나는지 확인
		if(arr.size() > c_target && arr[0].size() > r_target)
			if (arr[c_target][r_target] == K) return t;
		
		// 행, 열 크기 비교
		if( arr[0].size() <= arr.size())
			R();
		else
			C();
			
		t++;
	}

	return -1;
}

int main() {
	cin >> c_target >> r_target >> K;
	c_target--;
	r_target--;
	arr = vector< vector< int > >(3, vector< int >(3, 0));
	state_trans = false;

	//입력 초기화
	for (int c = 0; c < 3; c++) {
		for (int r = 0; r < 3; r++) {
			cin >> arr[c][r];
		}
	}


	cout << solution();
	
	return 0;
}
