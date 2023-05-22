#include "baselib.h"

class First
{
public:
    int n, m;
    double h, tau;
    vector<vector<double> > A, u;
    vector<double> B;

    First(int N, int T);
    ~First() = default;

    void createMatrixForTimeStep(int m);
    void TridiagMatrixAlg();
    void findFunction(int T);

    void printAMatrix();

    double errorRate(vector<double> iter, vector<double> start);
};
