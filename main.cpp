#include "baselib.h"
#include "1.h"
#include "2.h"
#include "3.h"

int main() {
    int n = NUM_OF_POINTS;
    double delta = 0;
    ofstream out1, out2, out3;

    // cin >> n;

    First f(n, TAU_STEPS);
    Second s(n, TAU2_STEPS);
    Third t(n, TAU_STEPS);
    f.findFunction(TAU_STEPS);
    s.findFunction(TAU2_STEPS);
    t.findFunction(TAU_STEPS);

    cout << "TAU_STEPS: " << TAU_STEPS << ", tau: " << f.tau << ", n: " << n << "" << endl;
    
    out1.open("p1.txt", ios::out);
    // for (int i = 0; i < n; i ++) {
    //     out1 << i*f.h << " ";
    // }
    // out1 << endl;
    // for (int i = 0; i < TAU_STEPS; i ++) {
    //     out1 << i*tau << " ";
    // }
    // out1 << endl;
    // for (int i = 0; i < TAU_STEPS; i ++) {
    //     for (int j = 0; j < n; j ++) {
    //         out1 << f.u[i][j] << " ";
    //     }
    // } 
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < TAU_STEPS; j ++) {
            out1 << i*f.h << " " << j*f.tau << " " << f.u[j][i] << endl;
        }
        // out1 << i*f.h << " " << f.u[TAU_STEPS - 1][i] << endl;
    }

    cout << "Без итерации: " << f.errorRate(f.u[TAU_STEPS - 1], f.u[TAU_STEPS - 2]) << endl;

    out2.open("p2.txt", ios::out);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < TAU2_STEPS; j ++) {
            out2 << i*s.h << " " << j*s.tau << " " << s.u[j][i] << endl;
        }
    }

    cout << "Явная схема: " << s.errorRate(s.u[TAU2_STEPS - 1], s.u[TAU2_STEPS - 2]) << endl;

    out3.open("p3.txt", ios::out);
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < TAU_STEPS; j ++) {
            out3 << i*t.h << " " << j*t.tau << " " << t.u[j][i] << endl;
        }
        // out3 << i*t.h << " " << t.u[TAU_STEPS - 1][i] << endl;
    }

    cout << "С итериацией: " << t.errorRate(t.u[TAU_STEPS - 1], t.u[TAU_STEPS - 2]) << endl;

    for (int i = 0; i < n; i ++) {
        delta += (f.u[TAU_STEPS - 1][i] - t.u[TAU_STEPS - 1][i])*(f.u[TAU_STEPS - 1][i] - t.u[TAU_STEPS - 1][i]);
    }
    
    cout << "Разница:" << sqrt(delta / n) << endl;
}
