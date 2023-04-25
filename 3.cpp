#include "3.h"

Third::Third(int N)
{
    vector<double> buff;
    n = N;
    h = 1. / (n - 1);
    
    for (int i = 0; i < n; i ++) {
        buff.push_back(0);
    }
    u.push_back(buff);
}

void Third::createMatrixForTimeStep(int m) // create matrix for 
{
    vector<double> buff;

    buff.push_back(1);
    buff.push_back(0);

    A.push_back(buff);
    B.push_back(0);

    for (int i = 1; i < n - 1; i ++) {
        buff.clear();
        buff.push_back(nu / (h*h) - u[m][i] / (2*h));
        buff.push_back( - 2*nu / (h*h) - 1./tau);
        buff.push_back(nu / (h*h) + u[m][i] / (2*h));

        A.push_back(buff);
        B.push_back( - u[m][i] / tau);
    }

    buff.clear();
    buff.push_back(0);
    buff.push_back(1);

    A.push_back(buff);
    B.push_back(1);
}

vector<double> Third::TridiagMatrixAlg()
{
    vector<double> p, q, step;
    p.push_back((-1) * A[0][1] / A[0][0]);
    q.push_back(B[0] / A[0][0]);
    for (int i = 1; i < n - 1; i++) {
        p.push_back((-1) * A[i][2] / (A[i][1] + A[i][0] * p[i - 1]));
        q.push_back((-1) * (A[i][0] * q[i - 1] - B[i]) /
                    (A[i][1] + A[i][0] * p[i - 1]));
    }
    step.push_back((-1) * (A[n - 1][0] * q[n - 2] - B[n - 1]) /
                      (A[n - 1][1] + A[n - 1][0] * p[n - 2]));
    for (int i = n - 2; i >= 0; i--) {
        step.emplace(step.begin(), p[i] * step[0] + q[i]);
    }
    return step;
}

vector<double> Third::TridiagMatrixAlg2()
{
    vector<double> aplha, betta, step;
    double y;

    y = A[0][0];
    aplha.push_back(- A[0][1] / y);
    betta.push_back(B[0] / y);

    for (int i = 1; i < n - 1; i ++) {
        y = A[i][1] + A[i][0]*aplha[i - 1];
        aplha.push_back( - A[i][2] / y);
        betta.push_back((B[i] - A[i][0]*betta[i - 1]) / y);
    }

    y = A[n - 1][1] + A[n - 1][0]*aplha[n - 2];
    step.push_back((B[n - 1] - A[n - 1][0]*betta[n - 2]) / y);

    for (int i = n - 2; i >= 0; i --) {
        step.emplace(step.begin(), aplha[i]*step[0] + betta[i]);
    }

    return step;
}

void Third::stepIterations(int K, int m)
{
    ofstream out;
    out.open("err.txt", ios::app);
    out << " ==== Слой " << m + 1 << " ====" << endl;

    vector<double> iter_step;
    iter_step = u[m + 1];
    // cout << "pre iter " << iter_step.size() << endl;
    for (int k = 0; k < K; k ++) {
        for (int i = 1; i < n - 1; i ++) {
            A[i][0] = nu / (h*h) - iter_step[i] / (2*h);
            A[i][2] = nu / (h*h) + iter_step[i] / (2*h);
        }
        iter_step = TridiagMatrixAlg2();

        out << scientific << errorRate(iter_step, u[m + 1]) << endl;
        // for (int j = 0; j < n; j ++) {
        //     cout << iter_step[j] << " ";
        // }
        // cout << endl;
    }

    out.close();
    
    // cout << "after iter " << iter_step.size() << endl;
    u[m + 1] = iter_step;
}

void Third::findFunction(int T)
{
    for (int i = 0; i < T; i ++) {
        // cout << T << endl;
        createMatrixForTimeStep(i);
        // cout << T << endl;
        u.push_back(TridiagMatrixAlg2());
        // cout << T << endl;
        stepIterations(STEP_ITERATIONS, i);
        // cout << T << endl;
        A.clear();
        // cout << "t1" << endl;
        B.clear();
        // cout << "out" << endl;
    }
}

double Third::errorRate(vector<double> iter, vector<double> start)
{
    double err = 0, right, left;
    for (int i = 1; i < n - 1; i ++) {
        left = (iter[i] - start[i]) / tau;
        right = nu*(iter[i + 1] - 2*iter[i] + iter[i - 1]) / (h*h) + iter[i]*(iter[i + 1] - iter[i - 1]) / (2*h);
        err += (right - left)*(right - left);
    }

    return sqrt(err) / NUM_OF_POINTS;
}