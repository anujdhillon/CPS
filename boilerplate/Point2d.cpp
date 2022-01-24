template <typename ftype>
struct point2d
{
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y) : x(x), y(y) {}
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
    friend ftype cross(point2d a, point2d b)
    {
        return a.x * b.y - a.y * b.x;
    }
    ftype norm(point2d a)
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
};