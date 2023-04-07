#include "baselib.h"

class First
{
public:
    int n;
    double h;
    vector<vector<double> > A, u;
    vector<double> B;

    First(int N);
    ~First() = default;

    void createMatrixForStep(int m);
};
