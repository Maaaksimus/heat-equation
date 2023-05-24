#include "baselib.h"

class Second
{
public:
    int n, m;
    double h, tau;
    vector<vector<double> > A, u;
    vector<double> B;

    Second(int N, int T);
    ~Second() = default;

    void createMatrixForTimeStep(int m);
    void TridiagMatrixAlg();
    void findFunction(int T);

    double errorRate(vector<double> last, vector<double> prev);
};
