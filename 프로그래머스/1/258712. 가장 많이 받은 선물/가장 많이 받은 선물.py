def solution(friends, gifts):
    n = len(friends)
    gift_table = [[0] * n for _ in range(n)]
    friend_index = {friends[i]: i for i in range(n)}
    gift_counts = [0] * n

    for gift in gifts:
        giver, receiver = gift.split()
        giver_idx = friend_index[giver]
        receiver_idx = friend_index[receiver]
        gift_table[giver_idx][receiver_idx] += 1
        gift_counts[giver_idx] += 1
        gift_counts[receiver_idx] -= 1

    next_month_gifts = [0] * n
    for i in range(n):
        for j in range(i + 1, n):
            give_count = gift_table[i][j]
            receive_count = gift_table[j][i]

            if give_count > receive_count:
                next_month_gifts[i] += 1
            elif receive_count > give_count:
                next_month_gifts[j] += 1
            else:
                if gift_counts[i] > gift_counts[j]:
                    next_month_gifts[i] += 1
                elif gift_counts[j] > gift_counts[i]:
                    next_month_gifts[j] += 1

    return max(next_month_gifts)
