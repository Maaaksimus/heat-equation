#include "1.h"

First::First(int N)
{
    vector<double> buff;
    n = N;
    h = 1. / (n - 1);
    
    for (int i = 0; i < n; i ++) {
        buff.push_back(0);
    }
    u.push_back(buff);
}

void First::createMatrixForTimeStep(int m) // create matrix for 
{
    vector<double> buff;

    buff.push_back(1);
    buff.push_back(0);

    A.push_back(buff);
    B.push_back(0);

    for (int i = 1; i < n - 1; i ++) {
        buff.clear();
        // cout << m << endl;
        buff.push_back(nu / (h*h) - u[m][i] / (2*h));
        buff.push_back( - 2*nu / (h*h) - 1./tau);
        buff.push_back(nu / (h*h) + u[m][i] / (2*h));

        A.push_back(buff);
        B.push_back( - u[m][i] / tau);

        // cout << u[m][i] / (2*h) << endl;
    }

    buff.clear();
    buff.push_back(0);
    buff.push_back(1);

    A.push_back(buff);
    B.push_back(1);
}

void First::TridiagMatrixAlg() // finding function values for m-th time step
{
    // vector<double> p, q, step;
    // p.push_back((-1) * A[0][1] / A[0][0]);
    // q.push_back(B[0] / A[0][0]);
    // for (int i = 1; i < n; i++) {
    //     p.push_back((-1) * A[i][2] / (A[i][1] + A[i][0] * p[i - 1]));
    //     q.push_back((-1) * (A[i][0] * q[i - 1] - B[i]) /
    //                 (A[i][1] + A[i][0] * p[i - 1]));
    // }
    // step.push_back((-1) * (A[n - 1][0] * q[n - 2] - B[n - 1]) /
    //                   (A[n - 1][1] + A[n - 1][0] * p[n - 2]));
    // for (int i = n - 2; i >= 0; i--) {
    //     step.emplace(step.begin(), p[i] * step[0] + q[i]);
    // }

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

    u.push_back(step);
}

void First::findFunction(int T)
{
    for (int i = 0; i < T - 1; i ++) {
        // cout << i << endl;
        createMatrixForTimeStep(i);
        // printAMatrix();
        TridiagMatrixAlg();

        // for (int j = 0; j < n; j ++) {
        //    cout << u[i + 1][j] << " ";
        // }
        // cout << endl;

        A.clear();
        B.clear();
    }
}

double First::errorRate(vector<double> last, vector<double> prev)
{
    double err = 0, right, left;
    for (int i = 1; i < n - 1; i ++) {
        left = (last[i] - prev[i]) / tau;
        right = nu*(last[i + 1] - 2*last[i] + last[i - 1]) / (h*h) + last[i]*(last[i + 1] - last[i - 1]) / (2*h);
        err += (right - left)*(right - left);
    }

    return sqrt(err / (NUM_OF_POINTS - 2));
}

void First::printAMatrix() {
    cout << "==========" << endl;
    cout << scientific;
    cout << A[0][0] << " " << A[0][1] << " | " << B[0] << endl;
    for (int i = 1; i < n - 1; i ++) {
        cout << A[i][0] << " " << A[i][1] << " " << A[i][2] << " | " << B[i] << endl;
    }
    cout << A[n - 1][0] << " " << A[n - 1][1] << " | " << B[n - 1] << endl;
}