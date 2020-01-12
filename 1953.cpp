#include <iostream>

#define MIN(a, b) a < b ? a : b
#define CHECK_L(v) v == 1 || v == 3 || v == 4 || v == 5
#define CHECK_R(v) v == 1 || v == 3 || v == 6 || v == 7
#define CHECK_T(v) v == 1 || v == 2 || v == 5 || v == 6
#define CHECK_D(v) v == 1 || v == 2 || v == 4 || v == 7
#define MAXN 50

int map[MAXN][MAXN];
int visited[MAXN][MAXN];

using namespace std;

void dfs(int tx, int ty, int depth) {
    if (depth == 0)
        return;

    if (visited[ty][tx] < depth)
        visited[ty][tx] = depth;
    else return;

    switch (map[ty][tx])
    {
        case 1:
        if (CHECK_L(map[ty][tx - 1]))
            dfs(tx - 1, ty, depth - 1); // 좌
        if (CHECK_T(map[ty - 1][tx]))
            dfs(tx, ty - 1, depth - 1); // 상
        if (CHECK_R(map[ty][tx + 1]))
            dfs(tx + 1, ty, depth - 1); // 우
        if (CHECK_D(map[ty + 1][tx]))
            dfs(tx, ty + 1, depth - 1); // 하
        break;
        
        case 2:
        if (CHECK_T(map[ty - 1][tx]))
            dfs(tx, ty - 1, depth - 1); // 상
        if (CHECK_D(map[ty + 1][tx]))
            dfs(tx, ty + 1, depth - 1); // 하
        break;
        
        case 3:
        if (CHECK_L(map[ty][tx - 1]))
            dfs(tx - 1, ty, depth - 1); // 좌
        if (CHECK_R(map[ty][tx + 1]))
            dfs(tx + 1, ty, depth - 1); // 우
        break;
        
        case 4:
        if (CHECK_R(map[ty][tx + 1]))
            dfs(tx + 1, ty, depth - 1); // 우
        if (CHECK_T(map[ty - 1][tx]))
            dfs(tx, ty - 1, depth - 1); // 상
        break;
        
        case 5:
        if (CHECK_R(map[ty][tx + 1]))
            dfs(tx + 1, ty, depth - 1); // 우
        if (CHECK_D(map[ty + 1][tx]))
            dfs(tx, ty + 1, depth - 1); // 하
        break;
        
        case 6:
        if (CHECK_L(map[ty][tx - 1]))
            dfs(tx - 1, ty, depth - 1); // 좌
        if (CHECK_D(map[ty + 1][tx]))
            dfs(tx, ty + 1, depth - 1); // 하
        break;
        
        case 7:
        if (CHECK_L(map[ty][tx - 1]))
            dfs(tx - 1, ty, depth - 1); // 좌
        if (CHECK_T(map[ty - 1][tx]))
            dfs(tx, ty - 1, depth - 1); // 상
        break;

        default:
        break;
    }

    return;
}

int solution(int n, int m, int sx, int sy, int t) {
    dfs(sx, sy, t);

    int length = 0;

    for (int y = 0; y < n; y++) {
        for(int x = 0; x < m; x++) {
            length += visited[y][x] > 0 ? 1 : 0;
            visited[y][x] = 0;
            map[y][x] = 0;
        }
    }

    return length;
}

int main(int argc, char** argv) {
	int T;
	cin >> T;

	for (int test_case = 1; test_case <= T; ++test_case)
	{
        int n, m, r, c, l;
        int ret;

        cin >> n >> m >> r >> c >> l;

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> map[i][j];
        
        ret = solution(n, m, c, r, l);
        cout << "#" << test_case << " " << ret << '\n';
	}

	return 0;
}
