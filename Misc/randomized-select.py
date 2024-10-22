import random

def swap(A, i, j):
    temp = A[i]
    A[i] = A[j]
    A[j] = temp

def partition(A , p, r):
    x = A[r]
    i = p
    for k in range(p, r):
        if A[k] < x:
           swap(A, i, k)
           i = i + 1
    i = i + 1
    swap(A, i, r)
    
    return i

def randomized_partition(A, p, r):
    i = random.randint(p, r)
    swap(A, i, r)
    return partition(A, p, r)

def randomized_select(A, p, r, i):
    while (p < r - 1):
        q = randomized_partition(A, p, r)
        k = q - p + 1
        if i == k:
            return A[q]
        elif i < k:
            r = q - 1
        else:
            p = q + 1
            i = i - k
    return A[p]
            
A = [3, 2, 9, 0, 7, 5, 4, 8, 6, 1]

print("Original Array: ", A)

print("Sorted: ", randomized_select(A, 0, len(A) - 1, 5))

