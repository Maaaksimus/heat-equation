#include "baselib.h"

#define STEP_ITERATIONS 10

class Third
{
public:
    int n, m;
    double h, tau;
    vector<vector<double> > A, u;
    vector<double> B;

    Third(int N);
    ~Third() = default;

    void createMatrixForTimeStep(int m);
    vector<double> TridiagMatrixAlg();
    vector<double> TridiagMatrixAlg2();
    void stepIterations(int K, int m);
    void findFunction(int T);

    void printAMatrix();

    double errorRate(vector<double> iter, vector<double> start);
};
