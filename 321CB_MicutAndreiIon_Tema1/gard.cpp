
//Nume: Micut Andrei-Ion
//Grupa: 321CB

#include <fstream>
#include <vector>
#include <algorithm>

bool my_cmp(const std::pair<int, int> &i, const std::pair<int, int> &j) {
    if (i.first == j.first) {
        return i.second > j.second;
    }

    return i.first < j.first;
}

int solve(std::vector<std::pair<int, int>> V) {
    int left = -1, right = -1;
    int sol = 0;

    // se sorteaza intervalele crescator dupa Xstart, iar in caz de
    // egalitate descrescator dupa Xend
    std::sort(V.begin(), V.end(), my_cmp);

    // se parcurge vectorul sortat pentru a afla intervalele redundante
    for (size_t i = 0; i < V.size(); ++ i) {
        if (V[i].first >= left && V[i].second <= right) {
            // bucata de gard este inclusa in alta, deci e redundanta
            ++ sol;
        } else {
            // facem update valorilor intervalului maxim curent
            left = V[i].first;
            right = V[i].second;
        }
    }

    return sol;
}

int main() {
    int N;
    std::vector<std::pair<int, int>> V;
    std::ifstream fin("gard.in");
    std::ofstream fout("gard.out");

    // se citesc datele de intrare
    fin >> N;
    for (int i = 0; i < N; ++ i) {
        int a, b;

        fin >> a >> b;
        V.push_back(std::make_pair(a, b));
    }

    fin.close();

    // se afiseaza rezultatul
    fout << solve(V) << "\n";
    fout.close();

    return 0;
}
