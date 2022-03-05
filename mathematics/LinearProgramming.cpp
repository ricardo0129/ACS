#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>
using namespace std;

const int MAXCHEESES = 50;
const int MAXBLENDS = 50;
const int MAXROWS = MAXCHEESES+1;
const int MAXCOLS = MAXCHEESES+MAXBLENDS+1;
const double TOL = 0.000000001;

int getPivotCol(int ncols, double row0[])
{
    for(int i=0; i<ncols-1; i++)
        if (row0[i] > 0.0)
        return i;
    return -1;
}

double printArray(int nrows, int ncols, double array[][MAXCOLS])
{
    for(int i=0; i<nrows; i++) {
        for(int j=0; j<ncols; j++) {
            cout << setw(6) << array[i][j] << ' ';
        }
        cout << endl;
    }
}

double simplex(int nrows, int ncols, double array[][MAXCOLS])
{
    int pcol, prow;
    while((pcol = getPivotCol(ncols, array[0])) != -1) {
//cout << "pcol = " << pcol << endl;
        prow = -1;
        double minval;
        for(int i=1; i<nrows; i++) {
            if (array[i][pcol] <= 0.0)
                continue;
            if (prow == -1 || array[i][ncols-1]/array[i][pcol] < minval) {
                prow = i;
                minval = array[i][ncols-1]/array[i][pcol];
            }
        }
        assert(prow != -1);
        for(int i=0; i<nrows; i++) {
            if (i == prow) {
                double factor = array[prow][pcol];
                for(int j=0; j<ncols; j++)
                    array[i][j] /= factor;
            }
            else {
                double factor = array[i][pcol]/array[prow][pcol];
                for(int j=0; j<ncols; j++) {
                    array[i][j] -= array[prow][j]*factor;
                    if (fabs(array[i][j]) < TOL)
                        array[i][j] = 0.0;
                }
            }
        }
//printArray(nrows, ncols, array);
//cout << endl;
    }
    return array[0][ncols-1];
}

int main()
{
    double array[MAXROWS][MAXCOLS];
    int n, m;

    cout << setprecision(2);
    cout << fixed;
    cin >> n >> m;
    for(int i=0; i<n+1; i++)
        for(int j=0; j<n+m+1; j++)
            array[i][j] = 0.0;
    for(int i=1; i<=n; i++)
        cin >> array[i][n+m];
    for(int j=0; j<m; j++) {
        for(int i=1; i<=n; i++) {
            cin >> array[i][j];
			array[i][j] /= 100.0;
        }
        cin >> array[0][j];
    }
    for(int j=m; j<n+m; j++)
        array[j-m+1][j] = 1.0;
//printArray(n+1, n+m+1, array);
//cout << endl;
    double max = simplex(n+1, n+m+1, array);
    cout << -max << endl;
}
