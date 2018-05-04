#include <iostream>
using namespace std;

int bitManipulation1(int n, int m, int i) {
    return ((m >> i) & 0x1) > 0 ?
           n | (1 << i) ://m的第i位为1，置1操作，或
           n & ~(1 << i);//m的第i位为0，清0操作，与
}

int main() {
    int n, m, i, t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> i;
        cout << bitManipulation1(n, m, i) << endl;
    }
    return 0;
}