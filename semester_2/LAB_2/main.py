import math

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __sub__(self, other) -> Point:
        return Point(self.x - other.x, self.y - other.y)

def cross(a, b) -> int:
    """Векторное произведение"""
    return a.x * b.y - a.y * b.x

def orient(a, b, c) -> int:
    """Ориентация тройки точек"""
    return cross(b - a, c - a)

# 1.1 Пересечение двух прямых
def line_intersection(p1, p2, p3, p4) -> Point:
    A1 = p2.y - p1.y
    B1 = p1.x - p2.x
    C1 = A1 * p1.x + B1 * p1.y
    
    A2 = p4.y - p3.y
    B2 = p3.x - p4.x
    C2 = A2 * p3.x + B2 * p3.y
    
    det = A1 * B2 - A2 * B1
    
    if det == 0:
        return None  # прямые параллельны
    
    x = (C1 * B2 - C2 * B1) / det
    y = (A1 * C2 - A2 * C1) / det
    return Point(x, y)

# 1.2 Пересечение прямой и отрезка
def point_on_segment(p, a, b):
    """Проверка принадлежности точки отрезку"""
    if orient(a, b, p) != 0:
        return False
    return (min(a.x, b.x) <= p.x <= max(a.x, b.x) and
            min(a.y, b.y) <= p.y <= max(a.y, b.y))

def line_segment_intersection(p1, p2, a, b) -> Point:
    pt = line_intersection(p1, p2, a, b)
    if pt and point_on_segment(pt, a, b):
        return pt
    return None

# 1.3 Пересечение двух отрезков
def segments_intersection(a, b, c, d) -> int:
    v1 = orient(a, b, c)
    v2 = orient(a, b, d)
    v3 = orient(c, d, a)
    v4 = orient(c, d, b)

    if v1 * v2 < 0 and v3 * v4 < 0:
        return line_intersection(a, b, c, d)
    
    if v1 == 0 and point_on_segment(c, a, b):
        return c
    if v2 == 0 and point_on_segment(d, a, b):
        return d
    if v3 == 0 and point_on_segment(a, c, d):
        return a
    if v4 == 0 and point_on_segment(b, c, d):
        return b
    return None

# 1.4 Пересечение прямой и окружности
def line_circle_intersection(p1, p2, center, r) -> list:
    dx = p2.x - p1.x
    dy = p2.y - p1.y
    
    a = dx*dx + dy*dy
    b = 2 * (dx * (p1.x - center.x) + dy * (p1.y - center.y))
    c = (p1.x - center.x)**2 + (p1.y - center.y)**2 - r**2
    
    disc = b*b - 4*a*c
    
    if disc < 0:
        return []
    if disc == 0:
        t = -b / (2*a)
        return [Point(p1.x + t * dx, p1.y + t * dy)]
    
    t1 = (-b + math.sqrt(disc)) / (2 * a)
    t2 = (-b - math.sqrt(disc)) / (2 * a)
    return [Point(p1.x + t1 * dx, p1.y + t1 * dy), Point(p1.x + t2 * dx, p1.y + t2 * dy)]

# 1.5 Пересечение отрезка и окружности
def segment_circle_intersection(a, b, center, r) -> list:
    points = line_circle_intersection(a, b, center, r)
    return [p for p in points if point_on_segment(p, a, b)]

# 1.6 Пересечение двух окружностей
def circles_intersection(c1, r1, c2, r2) -> list:
    dx = c2.x - c1.x
    dy = c2.y - c1.y
    d = math.hypot(dx, dy)
    
    if d > r1 + r2 or d < abs(r1 - r2):
        return []
    if d == 0 and r1 == r2:
        return []
    
    a = (r1**2 - r2**2 + d**2) / (2 * d)
    h2 = r1**2 - a**2
    
    if h2 < 0:
        return []
    
    px = c1.x + a * dx / d
    py = c1.y + a * dy / d
    
    if h2 == 0:
        return [Point(px, py)]
    
    h = math.sqrt(h2)
    return [Point(px - dy * h / d, py + dx * h / d), Point(px + dy * h / d, py - dx * h / d)]

# 2. Поиск вложенных треугольников
def point_in_triangle(p, a, b, c) -> bool:
    """Проверка, лежит ли точка внутри треугольника"""
    o1 = orient(a, b, p)
    o2 = orient(b, c, p)
    o3 = orient(c, a, p)

    if o1 == 0 or o2 == 0 or o3 == 0:
        return False

    return (o1 > 0 and o2 > 0 and o3 > 0) or (o1 < 0 and o2 < 0 and o3 < 0)

def has_nested_triangles(points):
    n = len(points)
    if n < 6:
        return False
    for i in range(n):
        for j in range(i + 1, n):
            for k in range(j + 1, n):
                a, b, c = points[i], points[j], points[k]
                if orient(a, b, c) == 0:
                    continue
                inner = []
                for p in points:
                    if p not in (a, b, c):
                        if point_in_triangle(p, a, b, c):
                            inner.append(p)
                if len(inner) >= 3:
                    if orient(inner[0], inner[1], inner[2]) != 0:
                        return True
    return False

if __name__ == "__main__":
    n = int(input())
    points = []
    for i in range(n):
        print("Введите координаты точки: ")
        x, y = map(int, input().split())
        points.append(Point(x, y))
    
    print(has_nested_triangles(points))