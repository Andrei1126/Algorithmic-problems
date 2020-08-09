
//Nume: Micut Andrei-Ion
//Grupa: 321CB

#include <fstream>
#include <vector>

static const int KMOD = 1000000007;
static const int TYPE_1 = 1, TYPE_2 = 2;

enum Money_types {
    LEU_10 = 0,
    LEU_50,
    LEU_100,
    LEU_200,
    LEU_500,
    MONEY_SIZE,
};

int solve_type1(int N) {
    // Numarul ce se doreste calculat este:
    // (((2 ^ (N - 1)) % KMOD) * MONEY_SIZE) % KMOD
    // Se aplica ridicarea la putere in timp logaritmic
    int power = 1, base = 2;

    for (-- N; N > 0; N /= 2) {
        if (N % 2 == 1) {
            // exponent impar
            power = (int)((1LL * power * base) % KMOD);
            -- N;
        }

        base = (int)((1LL * base * base) % KMOD);
    }

    return (int)((1LL * power * MONEY_SIZE) % KMOD);
}

int solve_type2(int N) {
    // vector cu regulile de aranjare a bancnotelor
    const std::vector<int> rules[MONEY_SIZE] = {
        {LEU_50, LEU_100, LEU_500},
        {LEU_10, LEU_200},
        {LEU_10, LEU_100, LEU_200},
        {LEU_50, LEU_500},
        {LEU_200},
    };
    // e indeajuns doar linia precedenta pentru dinamica
    std::vector<int> dp[2] = {
        std::vector<int>(MONEY_SIZE, 1),
        std::vector<int>(MONEY_SIZE, 0)
    };
    int line_ind = 0, sol = 0;

    for (int i = 1; i < N; ++ i) {
        line_ind = 1 - line_ind;

        // se determina cate metode de aranjare a i + 1 bancnote exista,
        // cu ultima bancnota de tipul j
        for (size_t j = 0; j < dp[line_ind].size(); ++ j) {
            int tmp = 0;

            // se calculeaza numarul de aranjari (se insumeaza numarul
            // de aranjari a i-1 bancnote ce pot preceda bancnota te tip j)
            for (size_t k = 0; k < rules[j].size(); ++ k) {
                tmp = (tmp + dp[1 - line_ind][rules[j][k]]) % KMOD;
            }

            // se salveaza numarul aranjarilor cu ultima bancnota de tip j
            dp[line_ind][j] = tmp;
        }
    }

    for (size_t i = 0; i < dp[line_ind].size(); ++ i) {
        sol = (sol + dp[line_ind][i]) % KMOD;
    }

    return sol;
}

int solve(int N, int ins_set) {
    switch (ins_set) {
    case TYPE_1:
        // pentru setul 1 de instructiuni, se aplica ridicarea la putere
        return solve_type1(N);
    case TYPE_2:
        // pentru setul 2 de instructiuni, se aplica algoritmul
        // de numarare descoperit
        return solve_type2(N);
    default:
        break;
    }

    return -1;
}

int main() {
    int N, ins_set;
    std::ifstream fin("bani.in");
    std::ofstream fout("bani.out");

    // citire date de intrare
    fin >> ins_set >> N;
    fin.close();

    // scriere rezultat
    fout << solve(N, ins_set) << "\n";
    fout.close();

    return 0;
}
