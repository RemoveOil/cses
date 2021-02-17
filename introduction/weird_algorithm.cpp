#include <iostream>
#include <stdio.h>

using namespace std;

void weird_alg(unsigned long long int n) {
    while (n > 1) {
        printf("%llu ", n);
        if (n % 2)
            n = n * 3 + 1;
        else
            n = n / 2;
    }
    cout << n << endl;
}

int main() {
    unsigned long long int n; 
    cin >> n;
    weird_alg(n);

    return 0;
}
