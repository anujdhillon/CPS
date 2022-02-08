template <typename ftype>
struct point2d
{
    ftype x, y;
    point2d() {}
    point2d(ftype _x, ftype _y) : x(_x), y(_y) {}
    point2d &operator+=(const point2d &t)
    {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d &operator-=(const point2d &t)
    {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d &operator*=(ftype t)
    {
        x *= t;
        y *= t;
        return *this;
    }
    point2d &operator/=(ftype t)
    {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const
    {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const
    {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const
    {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const
    {
        return point2d(*this) /= t;
    }
    ftype cross(point2d a, point2d b)
    {
        return (a.x - x) * (b.y - y) - (a.y - y) * (b.x - x);
    }

    friend ftype dot(point2d a, point2d b)
    {
        return a.x * b.x + a.y * b.y;
    }

    friend ftype norm(point2d a)
    {
        return dot(a, a);
    }
    double abs(point2d a)
    {
        return sqrt(norm(a));
    }
    double proj(point2d a, point2d b)
    {
        return dot(a, b) / abs(b);
    }
    double angle(point2d a, point2d b)
    {
        return acos(dot(a, b) / abs(a) / abs(b));
    }
    int quadrant(point2d p)
    {
        point2d dir = p - *this;
        if (dir.x > 0 && dir.y >= 0)
            return 1;
        else if (dir.x <= 0 && dir.y > 0)
            return 2;
        else if (dir.x < 0 && dir.y <= 0)
            return 3;
        else
            return 4;
    }
    template <class X, class Y>
    friend ostream &operator<<(ostream &os, const point2d &p)
    {
        return os << "(" << p.x << ", " << p.y << ") ";
    }
};

using Point = point2d<int>;

Point O{0, 0};