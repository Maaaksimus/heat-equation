#include "2.h"

Second::Second(int N)
{
    vector<double> buff;
    n = N;
    h = 1. / (n - 1);
    
    for (int i = 0; i < n; i ++) {
        buff.push_back(0);
    }
    u.push_back(buff);
}

void Second::createMatrixForTimeStep(int m) // create matrix for 
{
    vector<double> buff;

    buff.push_back(1);
    buff.push_back(0);

    A.push_back(buff);
    B.push_back(0);

    for (int i = 0; i < n - 1; i ++) {
        buff.clear();
        cout << m << endl;
        buff.push_back(nu / (h*h) - u[m][i] / (2*h));
        buff.push_back( - 2*nu / (h*h) - 1./tau2);
        buff.push_back(nu / (h*h) + u[m][i] / (2*h));

        A.push_back(buff);
        B.push_back( - u[m][i] / tau2);
    }

    buff.clear();
    buff.push_back(0);
    buff.push_back(1);

    A.push_back(buff);
    B.push_back(1);
}

void Second::TridiagMatrixAlg() // finding function values for m-th time step
{
    vector<double> p, q, step;
    p.push_back((-1) * A[0][1] / A[0][0]);
    q.push_back(B[0] / A[0][0]);
    for (int i = 1; i < n; i++) {
        p.push_back((-1) * A[i][2] / (A[i][1] + A[i][0] * p[i - 1]));
        q.push_back((-1) * (A[i][0] * q[i - 1] - B[i]) /
                    (A[i][1] + A[i][0] * p[i - 1]));
    }
    step.push_back((-1) * (A[n][0] * q[n - 1] - B[n]) /
                      (A[n][1] + A[n][0] * p[n - 1]));
    for (int i = n - 1; i >= 0; i--) {
        step.emplace(step.begin(), p[i] * step[0] + q[i]);
    }
    u.push_back(step);
}

void Second::findFunction(int T)
{
    vector<double> step;

    for (int m = 0; m < T; m ++) {
        step.push_back(0);

        // cout << "T " << m << endl;
        for (int i = 1; i < n - 1; i ++) {
            // cout << "check " << i << endl;
            // cout << u[m][i - 1] << " " << u[m][i] << " " << u[m][i + 1] << endl;

            step.push_back(tau2*(u[m][i] / tau2 + nu*(u[m][i + 1] - 2*u[m][i] + u[m][i - 1]) / (h*h) + u[m][i]*(u[m][i + 1] - u[m][i - 1]) / (2*h)));
        }

        step.push_back(1);
        
        // cout << step.size() << endl;

        u.push_back(step);
        step.clear();
    }
}

void Second::errorRate()
{
    // нахождение невязки
}