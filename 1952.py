'''
    this code has been failed in testcase #7, #10
'''
import sys


def main():
    sys.stdin = open("inputs/1952.txt", "r")

    T = int(input())

    # 여러개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
    for test_case in range(1, T + 1):
        daily, monthly, t_monthly, yearly = map(int, input().split())

        ret = solution(usage_data=list(map(int, input().split())),
                       daily=daily,
                       monthly=monthly,
                       t_monthly=t_monthly,
                       yearly=yearly)

        print("#%d %d" % (test_case, ret))


def solution(usage_data, daily, monthly, t_monthly, yearly):
    value_data = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    # 1. 일간 vs 월간해서 해당하는건 다 월간으로 치환 v
    for i in range(0, 12):
        if usage_data[i] == 0:
            continue
        value_data[i] = monthly if usage_data[i] * daily > monthly else usage_data[i] * daily

    f_sum = sum(value_data)

    if f_sum > yearly:
        return yearly

    #            1  2  3  4  5  6  7  8  9 10 11 12
    local_max = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

    # 3. 일.월간 포함해서 3씩 window 로 밀면서 합산한 값 vs 세달이용권값 해당하는건 세달이용권으로 치환
    for i in range(0, 12):
        l_sum = sum(value_data[i: i + 3])

        if l_sum > t_monthly:
            local_max[i] = l_sum

    max_count = 12 - local_max.count(0)

    if max_count > 9:  # 3달권 4개 결합
        for i in range(0, 12):
            local_max[i] = 0
            value_data[i] = t_monthly if i % 3 == 0 else 0
    elif 6 < max_count <= 9:  # 3달권 3개 결합
        pass
    elif 3 < max_count <= 6:  # 3달권 2개 결합
        find_bestfit(local_max, value_data, t_monthly)
    elif 0 < max_count <= 3:  # 3달권 1개 결합
        find_bestfit(local_max, value_data, t_monthly)
    else:  # 3달권으로 치환할 데이터가 없음
        pass

    s_sum = sum(value_data)

    if s_sum > yearly:
        return yearly

    return sum(value_data)


def find_bestfit(local_max, value_data, t_monthly):
    while sum(local_max) != 0:
        # find the bestfit (localmax)
        l_max = max(local_max)
        idx = local_max.index(l_max)

        lower_bound = idx - 2 if idx > 3 else 0
        upper_bound = idx + 3 if idx < 12 else 12

        for x in range(lower_bound, upper_bound):
            local_max[x] = 0
            value_data[x] = 0

        value_data[idx] = t_monthly

if __name__ == "__main__":
    main()
