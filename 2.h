#include "baselib.h"

class Second
{
public:
    int n, m;
    double h;
    vector<vector<double> > A, u;
    vector<double> B;

    Second(int N);
    ~Second() = default;

    void createMatrixForTimeStep(int m);
    void TridiagMatrixAlg();
    void findFunction(int T);

    void errorRate();
};
