#include "baselib.h"
#include "1.h"
#include "2.h"

int main() {
    int n = 100;
    double h;
    ofstream out1, out2, out3;

    // cin >> n;
    
    First f(n);
    Second s(n);
    f.findFunction(200);
    // s.findFunction(10000);
    
    out1.open("p1.txt");
    for (int i = 0; i < n; i ++) {
        out1 << i*f.h << " " << f.u[199][i] << endl;
    }

    // out2.open("p2.txt");
    // for (int i = 0; i < n; i ++) {
    //     out2 << i*s.h << " " << s.u[9999][i] << endl;
    // }
}
