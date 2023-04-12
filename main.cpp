#include "baselib.h"
#include "1.h"

int main() {
    int n = 100;
    double h;
    ofstream out;

    // cin >> n;
    
    First f(n);
    f.findFunction(20);
    
    out.open("p1.txt");
    for (int i = 0; i < n; i ++) {
        out << i*f.h << " " << f.u[10][i] << endl;
    }
}
