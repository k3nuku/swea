import sys


def main():
    sys.stdin = open("inputs/1949.txt", "r")

    T = int(input())

    # 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    for test_case in range(1, T + 1):
        map_data = []

        N, K = map(int, input().split())

        for x in range(0, N):
            map_data.append(list(map(int, input().split())))

        ret = solution(map_data, N, K)
        print("#%d %d" % (test_case, ret))


def solution(map_data, N, K):
    temp_max = 0

    # find max value
    for y in range(0, N):
        for x in range(0, N):
            if map_data[y][x] > temp_max:
                temp_max = map_data[y][x]

    max_bong_pos = []

    # find max value position
    for y in range(0, N):
        for x in range(0, N):
            if temp_max == map_data[y][x]:
                max_bong_pos.append({'x': x, 'y': y, 'length': -1})

    # find a way from maxbongnam
    for x in range(0, N):
        for y in range(0, N):
            for k in range(0, K + 1):
                map_data[y][x] -= k

                for bong in max_bong_pos:
                    length = move(map_data, bong['x'], bong['y'], N)
                    bong['length'] = length if length > bong['length'] else bong['length']

                map_data[y][x] += k

    max_bong_pos.sort(key=lambda e: e['length'], reverse=True)

    return max_bong_pos[0]['length']


def capable(map_data, x, y, k):
    result = []

    if x > 0 and map_data[y][x - 1] < map_data[y][x]:  # 좌
        result.append(2)
    if y > 0 and map_data[y - 1][x] < map_data[y][x]:  # 상
        result.append(3)
    if x < k - 1 and map_data[y][x + 1] < map_data[y][x]:  # 우
        result.append(0)
    if y < k - 1 and map_data[y + 1][x] < map_data[y][x]:  # 하
        result.append(1)

    return result


def move(map_data, x, y, N):
    dx = [1, 0, -1, 0]
    dy = [0, 1, 0, -1]

    way = capable(map_data, x, y, N)
    move_result = 0

    for move_index in way:
        result = move(map_data, x + dx[move_index], y + dy[move_index], N)
        move_result = result if result > move_result else move_result

    return move_result + 1


if __name__ == "__main__":
    main()
