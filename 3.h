#include "baselib.h"

#define STEP_ITERATIONS 20

class Third
{
public:
    int n, m;
    double h;
    vector<vector<double> > A, u;
    vector<double> B;

    Third(int N);
    ~Third() = default;

    void createMatrixForTimeStep(int m);
    vector<double> TridiagMatrixAlg();
    vector<double> TridiagMatrixAlg2();
    void stepIterations(int K, int m);
    void findFunction(int T);

    double errorRate(vector<double> iter, vector<double> start);
};
