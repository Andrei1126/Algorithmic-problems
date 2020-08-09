
//Nume: Micut Andrei-Ion
//Grupa: 321CB

#include <fstream>
#include <vector>
#include <algorithm>

static const int KMOD = 1000000007;

int solve(int M, std::vector<std::pair<int, int>> V) {
    // vector cu sumele partiale
    std::vector<int> partial_sums(M + 1, 0);
    // dp[j] = numarul de moduri in care pot fi oferite j bomboane, folosind
    //         numere din primele i intervale (aceasta dimensiune de dinamica
    //         nu e necesara - ne folosim de partial_sums pentru asta)
    //         In dp[M] se afla solutia problemei
    std::vector<int> dp(M + 1, 0);

    // cazul de baza e atunci cand suntem la primul interval
    // exista doar o metoda de a acorda bomboane in intervalul [x0, y0]
    for (int i = V[0].first; i <= std::min(V[0].second, M); ++ i) {
        dp[i] = 1;
    }

    // se folosesc si restul intervalelor
    for (size_t i = 1; i < V.size(); ++ i) {
        // se calculeaza vectorul cu sume partiale
        partial_sums[0] = dp[0] % KMOD;
        for (int j = 1; j <= M; ++ j) {
            partial_sums[j] = (partial_sums[j - 1] + dp[j]) % KMOD;
        }

        // vectorul dp este refolosit, se sterg valorile anterioare
        std::fill(dp.begin(), dp.end(), 0);

        // se determina numarul de moduri de a acorda j bomboane, folosind
        // numere din intervalul curent
        for (int j = V[i].first; j <= M; ++ j) {
            int left, right;

            // se scad din numarul curent de bomboane capetele intervalului
            // se afla intervalul cu numere care daca sunt adunate cu numere
            // din intervalul curent se obtine numarul j de bomboane
            left  = std::max(0, j - V[i].second);
            right = std::max(0, j - V[i].first);

            // se determina numarul de moduri de acordare a bomboanelor prin
            // diferenta sumelor partiale; left poate fii si 0!
            dp[j] = partial_sums[right];
            if (left != 0) {
                dp[j] = (dp[j] - partial_sums[left - 1] + KMOD) % KMOD;
                if (dp[j] < 0) {
                    // optimizare; daca avem numar de moduri negativ nu mai
                    // are sens sa continuam
                    dp[j] = 0;
                    break;
                }
            }
        }
    }

    return dp[M];
}

int main() {
    int N, M;
    std::vector<std::pair<int, int>> V;
    std::ifstream fin("bomboane.in");
    std::ofstream fout("bomboane.out");

    // se citesc datele de intrare
    fin >> N >> M;
    for (int i = 0; i < N; ++ i) {
        int a, b;

        fin >> a >> b;
        V.push_back(std::make_pair(a, b));
    }

    fin.close();

    // se scrie rezultatul
    fout << solve(M, V) << "\n";
    fout.close();

    return 0;
}
