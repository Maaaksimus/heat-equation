#include "baselib.h"
#include "1.h"
#include "2.h"
#include "3.h"

int main() {
    int n = NUM_OF_POINTS;
    double h;
    ofstream out1, out2, out3;

    // cin >> n;a

    First f(n);
    Second s(n);
    Third t(n);
    f.findFunction(TAU_STEPS);
    s.findFunction(TAU2_STEPS);
    t.findFunction(TAU_STEPS);
    
    out1.open("p1.txt");
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
        // for (int j = 0; j < TAU_STEPS; j ++) {
        //     out1 << i*f.h << " " << j*tau << " " << f.u[j][i] << endl;
        // }
        out1 << i*f.h << " " << f.u[TAU_STEPS - 1][i] << endl;
    }

    out2.open("p2.txt");
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < TAU2_STEPS; j ++) {
            out2 << i*s.h << " " << j*tau2 << " " << s.u[j][i] << endl;
        }
    }

    out3.open("p3.txt");
    for (int i = 0; i < n; i ++) {
        // for (int j = 0; j < TAU_STEPS; j ++) {
        //     out3 << i*t.h << " " << j*tau << " " << t.u[j][i] << endl;
        // }
        out3 << i*t.h << " " << t.u[TAU_STEPS - 1][i] << endl;
    }
}
