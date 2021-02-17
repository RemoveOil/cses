#include <iostream>

using namespace std;



int main() {
    ios_base::sync_with_stdio(false);

    int longest_repetition = 1, current_run = 1;
    string dna_sequence;
    cin >> dna_sequence;

    for (int i = dna_sequence.length() - 2; i > -1; --i) {
        if (dna_sequence[i] == dna_sequence[i + 1]) {
            current_run += 1;
        }
        else {
            longest_repetition = max(longest_repetition, current_run);
            current_run = 1;
        }
    }
    longest_repetition = max(longest_repetition, current_run);

    cout << longest_repetition << endl;
    return 0;
}
