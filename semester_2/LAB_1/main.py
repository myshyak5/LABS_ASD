def rotate(A, B, C) -> float:
    return (B[0] - A[0]) * (C[1] - B[1]) - (B[1] - A[1]) * (C[0] - B[0])

def jarvismarch(A) -> list:
    n = len(A)
    P = list(range(n))
    for i in range(1, n):
        if A[P[i]][0] < A[P[0]][0]: 
            P[i], P[0] = P[0], P[i]  
    H = [P[0]]
    del P[0]
    P.append(H[0])
    while True:
        right = 0
        for i in range(1, len(P)):
            if rotate(A[H[-1]], A[P[right]], A[P[i]]) < 0:
                right = i
        if P[right] == H[0]: 
            break
        else:
            H.append(P[right])
            del P[right]
    return H

def main():
    n = int(input("Введите кооличество точек: "))
    points = []
    print("Введите координаты точкек:")
    for _ in range(n):
        x, y = map(float, input().split())
        if x == int(x): x = int(x)
        if y == int(y): y = int(y)
        points.append((x, y))

    hull = jarvismarch(points)

    print("Точки:", points)
    print("Точки оболочки:", [points[i] for i in hull])
    print(f"Оболочка существует: {len(hull) >= 3}")


if __name__ == "__main__":
    main()