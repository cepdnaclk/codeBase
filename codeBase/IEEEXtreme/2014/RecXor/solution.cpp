'''
    Copyright (C) 2020, Sathira Silva
    
    Link to the problem: https://csacademy.com/ieeextreme-practice/task/f8d68dbb0c844910797ce64354c66143/
'''

// XOR sum over first n whole numbers
def xor(n):
    m = n & 3
    if m == 0: return n
    if m == 1: return 1
    if m == 2: return n + 1
    return 0
    
t = int(input())
for _ in range(t):
    l, h, n, d1, d2 = map(int, input().split())
    // XOR over the numbers in the given rectangle
    // Since the rectangle starts with n, we have to take the XOR sum over number s from 1 to n + l * h - 1 and XOR that with the XOR sum over numbers from 1 to (n - 1)
    // (Because x ^ y ^ x = y)
    res = xor(n - 1) ^ xor(n + l * h - 1)
    // Each cell is mapped to a number by its 0-based indices (x, y) where top-left cell is (0, 0) and bottom-right cell is (h - 1, l - 1): n + y * l + x
    // Therefore, find the indices of the diagonal end points of the inner rectangle using the given d1 and d2
    // For example: d1 = n + y1 * l + x1
    // Thus, x1 = (d1 - n) % l and y1 = (d1 - n - x1) // l
    x1 = (d1 - n) % l
    y1 = (d1 - n - x1) // l
    x2 = (d2 - n) % l
    y2 = (d2 - n - x2) // l
    // The given diagonal can be either the main diagonal or the off diagonal
    if x1 > x2:
        x1, x2 = x2, x1
    // Find the XOR of the remaining part of the rectangle
    for y in range(y1, y2 + 1):
        res ^= xor(n + y * l + x1 - 1) ^ xor(n + y * l + x2)
    print(res)
