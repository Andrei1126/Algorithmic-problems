
//Nume: Micut Andrei-Ion
//Grupa: 321CB

#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

long long solve(int M, std::vector<std::pair<int, int>> V) {
    // structura pentru a retine sortat in ordine crescatoare
    // greutatile ganterelor alese
    std::multiset<int> S;
    long long currSum = 0;
    long long sol = 0;

    // se sorteaza crescator perechile, dupa greutate
    std::sort(V.begin(), V.end());

    // se aleg ganterele in ordine descrescatoare dupa greutate
    for (int i = (int)V.size() - 1; i >= 0; -- i) {
        bool flag = false;

        if (S.size() < (size_t)M) {
            // nu au fost alese M gantere, ne putem antrena si cu aceasta
            S.insert(V[i].second);
            currSum += 1LL * V[i].second;
            flag = true;
        } else if (*(S.begin()) < V[i].second) {
            // deja au fost alese M gantere, si am ales una cu greutatea mai
            // mica decat greutatea acestei gantere
            auto it = S.begin();
            currSum = currSum - *it + V[i].second;
            S.erase(it);
            S.insert(V[i].second);
            flag = true;
        }

        if (flag) {
            // am ales aceasta gantera, verificam daca imbunatateste suma
            sol = std::max(sol, 1LL * V[i].first * currSum);
        }
    }

    return sol;
}

int main() {
    int N, M;
    std::vector<std::pair<int, int>> V;
    std::ifstream fin("sala.in");
    std::ofstream fout("sala.out");

    // se citesc datele de intrare
    fin >> N >> M;
    for (int i = 0; i < N; ++ i) {
        int a, b;

        fin >> a >> b;
        V.push_back(std::make_pair(a, b));
    }

    fin.close();

    // se afiseaza rezultatul
    fout << solve(M, V) << "\n";
    fout.close();

    return 0;
}
