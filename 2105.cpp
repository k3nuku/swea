#include <iostream>
#include <set>
#include <algorithm>

#define MAX(a, b) a > b ? a : b
#define CHECK_MOVE(a, b, n) a > -1 && b > -1 && a < n && b < n
#define MAXN 20

using namespace std;

int map[MAXN][MAXN];
set<int> temp;
bool found;

//           우하 좌하 좌상 우상
int dx[4] = { 1, -1, -1, 1 };
int dy[4] = { 1, 1, -1, -1 };

// true if insert was succeeded
bool insert(int x, int y) {
    return temp.insert(map[y][x]).second;
}

int dfs(int x, int y, int n, int direction, int depth, int r0, int r1, int origx, int origy) {
    if (depth > (n - 1) * 2 || direction > 3 || found)
        return -1; // 최대 길이 초과, 3번 초과 회전, 이미 찾음: -1 리턴
    
    if (x == origx && y == origy && direction == 3) {
        if ((n - 1) * 2 == depth)
            found = true;

        return depth;
    }

    if (!insert(x, y))
        return -1; // 중복: -1 리턴

    int result = -1, rresult = -1;
    set<int> current_set = temp; // backing up

    if (CHECK_MOVE(x + dx[direction], y + dy[direction], n))// 직진 가능하면
        result = dfs(x + dx[direction], y + dy[direction],
                     n, direction, depth + 1,
                     r0, r1,
                     origx, origy); // 직진

    temp = current_set; // restore it
    
    if (CHECK_MOVE(x + dx[direction + 1], y + dy[direction + 1], n))// 꺾기 가능하면
        rresult = dfs(x + dx[direction + 1], y + dy[direction + 1],
                      n, direction + 1, depth + 1,
                      direction == 0 ? depth + 1 : r0, direction == 1 ? depth + 1 - r0 : r1,
                      origx, origy); // 꺾기

    if (result == -1 && rresult == -1) {
        temp.erase(map[y][x]);
        return -1;
    }
    else return MAX(result, rresult);
}

int solution(int n) {
    int global_max = -1;
    found = false;

    for (int y = 0; y < n - 1; y++) {
        for (int x = 1; x < n - 1; x++) {
            int local_max = dfs(x, y, n, 0, 0, 0, 0, x, y);
            global_max = MAX(local_max, global_max); // 시작점을 넣어줌
            temp.clear();
        }
    }

    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            map[y][x] = 0;

    return global_max;
}

int main(int argc, char** argv) {
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        int n;
        int ret;

        cin >> n;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> map[i][j];
        
        ret = solution(n);
        cout << "#" << test_case << " " << ret << '\n';
	}

	return 0;
}
