# python3
from collections import deque


def max_sliding_window_naive(sequence: list[int], m: int) -> list[int]:
    maximums = []
    for i in range(len(sequence) - m + 1):
        maximums.append(max(sequence[i:i + m]))

    return maximums


def max_sliding_window(sequence: list[int], m: int) -> list[int]:
    def fill_deque(dq, s, i):
        """
        Remove items from right side of the deque
        that are not greater than s[i]
        """
        while dq and s[i] >= s[ dq[-1] ]:
            #print("\twhile ", dq)
            dq.pop()
        dq.append(i)

    maximus = []
    dq = deque(maxlen=m)
    
    # Initial window from 0 to m-1
    for i in range(m):
        fill_deque(dq, sequence, i)

    maximus.append(sequence[ dq[0] ])
    for index in range(m, len(sequence)):
        #print(dq, maximus)
        fill_deque(dq, sequence, index)
        while dq and dq[0] <= index - m:
            dq.popleft()

        maximus.append(sequence[ dq[0] ])
    return maximus

  
if __name__ == '__main__':
    n = int(input()) #sequence size
    input_sequence = [int(i) for i in input().split()]
    assert len(input_sequence) == n
    window_size = int(input())

    #print(*max_sliding_window_naive(input_sequence, window_size))
    print(*max_sliding_window(input_sequence, window_size))
