n = eval(input())

for i in range(n):
    nums = []
    nn, k = map(int, input().split(" "))
    nums = list(map(int, input().split(" ")))
    Min = 0
    ans = nn + 1
    start, end = 0, 0
    total = 0
    while end < nn:
        total += nums[end]
        while total >= k:
            ans = min(ans, end - start + 1)
            total -= nums[start]
            start += 1
        end += 1

    Min = -1 if ans == nn + 1 else ans
    
    print(Min)