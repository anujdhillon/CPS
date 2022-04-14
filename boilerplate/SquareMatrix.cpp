int n;

template <typename T>
struct Matrix
{
    vector<vector<mint>> a;
    Matrix()
    {
        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            a[i].resize(n);
            for (int j = 0; j < n; j++)
                a[i][j] = 0;
        }
    }

    Matrix(vector<vector<T>> &aa)
    {
        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            a[i].resize(n);
            for (int j = 0; j < n; j++)
                a[i][j] = aa[i][j];
        }
    }
    Matrix(int k)
    {
        a.resize(n);
        for (int i = 0; i < n; i++)
        {
            a[i].resize(n);
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                    a[i][j] = k;
                else
                    a[i][j] = 0;
            }
        }
    }

    Matrix operator+(const Matrix &M2)
    {
        Matrix res;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res.a[i][j] = a[i][j] + M2.a[i][j];
            }
        }
        return res;
    }
    Matrix operator-(const Matrix &M2)
    {
        Matrix res;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res.a[i][j] = a[i][j] - M2.a[i][j];
            }
        }
        return res;
    }
    Matrix operator*(const Matrix &M2)
    {
        Matrix res;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    res.a[i][j] += a[i][k] * M2.a[k][j];
                }
            }
        }
        return res;
    }
    Matrix operator*(int k)
    {
        Matrix res;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res.a[i][j] *= k;
            }
        }
        return res;
    }
    T operator()(int i, int j)
    {
        assert(i < n && i >= 0);
        return a[i][j];
    }
    friend ostream &operator<<(std::ostream &os, const Matrix &x)
    {
        os << "[ ";
        for (int i = 0; i < n; i++)
        {
            os << "[ ";
            for (int j = 0; j < n; j++)
                os << x.a[i][j] << ", ";
            os << "]\n";
        }
        return os << "]\n";
    }
};
