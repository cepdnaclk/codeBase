'''
    Copyright (C) 2020, Sathira Silva.
    
    Link to the problem: https://csacademy.com/ieeextreme-practice/task/333043935273ab966569971859d1835b/
'''

from collections import defaultdict
from heapq import heappop, heappush

maxn = 55
products = [0]

def sieve():
    global products, maxn
    prime = [True] * (maxn + 1)
    p = 2
    while p * p <= maxn:
        if prime[p]:
            for i in range(p * p, maxn + 1, p):
                prime[i] = False
        p+=1
    prod = 1
    for p in range(2, maxn + 1):
        if prime[p]:
            prod *= p
            products.append(prod)
            
def lower_bound(id):
    global products
    left, right = 0, len(products)
    res = 0
    while left <= right:
        mid = left + (right - left) // 2
        if (id < products[mid]):
            right = mid - 1
        else:
            left = mid + 1
            res = mid
    return res
    
sieve()
n, m = map(int, input().split())
id2label = defaultdict(int)
label2id = [0] * n
s, t = float('inf'), 0
for i in range(n):
    j = int(input())
    id2label[j] = i
    label2id[i] = j
    s = min(s, j)
    t = max(t, j)
graph = defaultdict(list)
for i in range(m):
    x, y, d = map(int, input().split())
    graph[id2label[x]].append((id2label[y], d))
    graph[id2label[y]].append((id2label[x], d))
dist = [float('inf')] * n
kilos = [0] * n
dist[id2label[s]] = 0
kilos[id2label[s]] = lower_bound(s)
q = [(0, id2label[s])]
while q:
    _, u = heappop(q)
    for v, d in graph[u]:
        if dist[u] != float('inf') and dist[v] > dist[u] + d:
            dist[v] = dist[u] + d
            kilos[v] = kilos[u] + lower_bound(label2id[v])
            heappush(q, (dist[v], v))
print(kilos[id2label[t]])
