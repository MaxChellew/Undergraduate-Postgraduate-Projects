#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// System Functions

// Inputs:
// (v) - vector that is to be summed
// (j) - number of elements in vector (v)
double cumulativeSum(vector<double> v, int j) {
    // create a subset of vector v containing elements from position 0 to j of vector v
    vector<double> vec(v.begin(), v.begin() + j);
    // calculate the cumlative sum of the the new subset of vector v
    double sum = 0;
    for (double i : vec) {
        sum += i;
    }
    return sum;
} // this function outputs the cumulative sum of a vectors elements from position 0 to j

// Inputs:
// (n) - number of random numbers in vector
// (mu) - mean of gussian normal distribution 
// (sigma) - standard devation of gussian normal distribution
vector<double> gaussianRandomVector(int n, double mu, double sigma) {
    // create empty vector space
    vector<double> v;
    // initialise random gussian random number generator 
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distN(mu, sigma);
    // fill vector space with gussian random numbers
    for (int i = 0; i < n; i++) {
        v.push_back(distN(gen));
    }
    return v;
} // this function outputs a vector containing mutiple gaussian random numbers

// Inputs:
// (n) - number of time periods
// (N) - number of random walk reperations
// (r) - risk-free rate
// (delta) - implied volatility
// (T) - time period (years)
// (S0) - starting stock price
vector<vector<double>> blackScholesMerton(int n, int N, double r, double delta, double T, double S0) {
    // calculate the length of each time step (dt)
    double dt = T / n;
    // create empty matrix (vector of vectors) space
    vector<vector<double>> S;
    // application of Black-Scholes-Metron algorithm 
    for (int i = 0; i < N; i++) {
        vector<double> v = gaussianRandomVector(n + 1, 0, 1);
        vector<double> SN;
        for (int j = 0; j < n + 2; j++) {
            double Sj = log(S0) + ((r - 0.5 * pow(delta, 2)) * dt * j) + (delta * sqrt(dt) * cumulativeSum(v, j));
            SN.push_back(exp(Sj));
        }
        S.push_back(SN);
    }
    return S;
} // this function outputs the stochastic path of a stock over a given period 

// Inputs:
// (S) - random walk of stock price (blackScholesMerton)
// (n) - number of time periods 
// (N) - number of monte-carlo repertitions
// (K) - strike price
// (type) - call (C) or put (P)
// (style) - non exotic (non), asian fixed price (AS_FP), asian fixed strike price (AS_FS), barrier up and in (BA_UI), barrier up and out (BA_UO), barrier down and in (BA_DI), barrier down and out (BA_DO)
double payoffFunctions(vector<vector<double>> S, int n, int N, double K, double r, string type, string style, string exotic, double add_info) {
    vector<double> payoff;
    // identifies payoff functions type (call)
    if (type == "C") {
        // identifies payoff functions style (european)
        if (style == "EU") {
            // identifies payoff functions exoticness (non)
            if (exotic == "non") {
                // calculate payoffs for non exotic european call options
                for (int i = 0; i < N; i++) {
                    double payoff_i = max(S[i][n] - K, 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (asian - fixed price)
            else if (exotic == "AS_FP") {
                // calcuate payoff for asian euopean fixed price call options
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    double average_price = cumulativeSum(v, n) / n;
                    double payoff_i = max(S[i][n] - average_price, 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (asian - fixed strike price)
            else if (exotic == "AS_FS") {
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    double average_price = cumulativeSum(v, n) / n;
                    double payoff_i = max(average_price - K, 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (barrier - up and in)
            else if (exotic == "BA_UI") {
                // calculate payoff for up and in barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        double payoff_i = max(S[i][n] - K, 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                    else {
                        payoff.push_back(0);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - up and out)
            else if (exotic == "BA_UO") {
                // calculate payoff for up and in barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        payoff.push_back(0);
                    }
                    else {
                        double payoff_i = max(S[i][n] - K, 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and in)
            else if (exotic == "BA_DI") {
                // calculate payoff for up and in barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        double payoff_i = max(S[i][n] - K, 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                    else {
                        payoff.push_back(0);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and out)
            else if (exotic == "BA_DO") {
                // calculate payoff for up and in barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        payoff.push_back(0);
                    }
                    else {
                        double payoff_i = max(S[i][n] - K, 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                }
            }
        }
        // identifiy payoff functions style (american) 
        else if (style == "AM") { 
            // identifiy payoff functions exoticness (non)
            if (exotic == "non") {
                for (int i = 0; i < N; i++) {
                    // calculate payoffs for non exotic american put option
                    for (int j = 1; j < n + 1; j++) {
                        double payoff_k = max(S[i][j] - K, 0.0);
                        double discounted_payoff_k = payoff_k / pow(1 + r, j);
                        payoff.push_back(discounted_payoff_k);
                    }
                }
            }
            // identifiy payoff functions exoticness (asian - fixed price)
            else if (exotic == "AS_FP") {
                // calcuate payoff for asian american fixed price call options
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    for (int j = 1; j < n + 1; j++) {
                        double average_price = cumulativeSum(v, j) / j;
                        double payoff_k = max(S[i][j] - average_price, 0.0);
                        double discounted_payoff_k = payoff_k / pow(1 + r, j);
                        payoff.push_back(discounted_payoff_k);
                    }
                }
            }
            // identifiy payoff functions exoticness (asian - fixed strike price)
            else if (exotic == "AS_FS") {
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    for (int j = 1; j < n + 1; j++) {
                        double average_price = cumulativeSum(v, j) / j;
                        double payoff_k = max(average_price - K, 0.0);
                        double discounted_payoff_k = payoff_k / pow(1 + r, j);
                        payoff.push_back(discounted_payoff_k);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - up and in)
            else if (exotic == "BA_UI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(S[i][j] - K, 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - up and out)
            else if (exotic == "BA_UO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(S[i][j] - K, 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and in)
            else if (exotic == "BA_DI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(S[i][j] - K, 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and out)
            else if (exotic == "BA_DO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(S[i][j] - K, 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                }
            }
        }
    }
    // identify payoff function type (put)
    else if (type == "P") {
        // identifiy payoff functions style (european)
        if (style == "EU") {
            // identifiy payoff functions exoticness (non)
            if (exotic == "non") {
                // calculate payoffs for non exotic european put option
                for (int i = 0; i < N; i++) {
                    double payoff_i = max(K - S[i][n], 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (asian - fixed price)
            else if (exotic == "AS_FP") {
                // calculate payoffs for asian european fixed price put option
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    double average_price = cumulativeSum(v, n) / n;
                    double payoff_i = max(average_price - S[i][n], 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (asian - fixed strike price)
            else if (exotic == "AS_FS") {
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    double average_price = cumulativeSum(v, n) / n;
                    double payoff_i = max(K - average_price, 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (barrier - up and in)
            else if (exotic == "BA_UI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        double payoff_i = max(K - S[i][n], 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                    else {
                        payoff.push_back(0);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - up and out)
            else if (exotic == "BA_UO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        payoff.push_back(0);
                    }
                    else {
                        double payoff_i = max(K - S[i][n], 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and in)
            else if (exotic == "BA_DI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        double payoff_i = max(K - S[i][n], 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                    else {
                        payoff.push_back(0);
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and out)
            else if (exotic == "BA_DO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = 1;
                        }
                    }
                    if (barrier_met != 0) {
                        payoff.push_back(0);
                    }
                    else {
                        double payoff_i = max(K - S[i][n], 0.0);
                        double discounted_payoff_i = payoff_i / pow(1 + r, n);
                        payoff.push_back(discounted_payoff_i);
                    }
                }
            }
        }
        // identifiy payoff functions style (american)
        else if (style == "AM") {
            // identifiy payoff functions exoticness (non)
            if (exotic == "non") {
                // calculate payoffs for non exoptic american put option
                for (int i = 0; i < N; i++) {
                    for (int j = 1; j < n + 1; j++) {
                        double payoff_k = max(K - S[i][j], 0.0);
                        double discounted_payoff_k = payoff_k / pow(1 + r, j);
                        payoff.push_back(discounted_payoff_k);
                    }
                }
            }
            // identifiy payoff functions exoticness (asian - fixed price)
            else if (style == "AS_FP") {
                // calculate payoffs for asian american fixed price put option
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    for (int j = 1; j < n + 1; j++) {
                        double average_price = cumulativeSum(v, j) / j;
                        double payoff_k = max(average_price - S[i][j], 0.0);
                        double discounted_payoff_k = payoff_k / pow(1 + r, j);
                        payoff.push_back(discounted_payoff_k);
                    }
                }
            }
            // identifiy payoff functions exoticness (asian - fixed stike price)
            else if (exotic == "AS_FS") {
                // 
                for (int i = 0; i < N; i++) {
                    vector<double> v;
                    for (int j = 1; j < n + 1; j++) {
                        v.push_back(S[i][j]);
                    }
                    double average_price = cumulativeSum(v, n) / n;
                    double payoff_i = max(K - average_price, 0.0);
                    double discounted_payoff_i = payoff_i / pow(1 + r, n);
                    payoff.push_back(discounted_payoff_i);
                }
            }
            // identifiy payoff functions exoticness (barrier - up and in)
            else if (exotic == "BA_UI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(K - S[i][j], 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - up and out)
            else if (exotic == "BA_UO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] >= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(K - S[i][j], 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and in)
            else if (exotic == "BA_DI") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(K - S[i][j], 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                }
            }
            // identifiy payoff functions exoticness (barrier - down and out)
            else if (exotic == "BA_DO") {
                // calculate payoff for barrier euopean call options
                for (int i = 0; i < N; i++) {
                    int barrier_met = 0;
                    for (int j = 1; j < n + 1; j++) {
                        if (S[i][j] <= add_info) {
                            barrier_met = j;
                            break;
                        }
                    }
                    if (barrier_met != 0) {
                        for (int j = 1; j < n + 1; j++) {
                            payoff.push_back(0);
                        }
                    }
                    else {
                        for (int j = 1; j < n + 1; j++) {
                            if (j < barrier_met) {
                                payoff.push_back(0);
                            }
                            else {
                                double payoff_k = max(K - S[i][j], 0.0);
                                double discounted_payoff_k = payoff_k / pow(1 + r, j);
                                payoff.push_back(discounted_payoff_k);
                            }
                        }
                    }
                }
            }
        }
    }
    return cumulativeSum(payoff, payoff.size()) / payoff.size();
} // this function outputs the averaged payoff for different styles and types of options 

// UI Functions

// Output Menu
int outMenu() {
    cout << "MENU:" << endl;
    cout << "Monte-Carlo Algorithm Settings (MC)" << endl;
    cout << "Market Settings (M)" << endl;
    cout << "Option Settings (O)" << endl;
    cout << "Price Option (P)" << endl;
    cout << "End Program (E)" << endl << endl;
    cout << "Please enter one of the following to procced: (MC, M, O, P, E) " << endl << endl;
    return 0;
}

// Output Monte-Carlo Alogthigm Settings
int outMCS(int N, int n) {
    cout << "MONTE-CARLO ALGORITHM SETTINGS:" << endl;
    cout << "Number of Monte-Carlo Repettitions (" << N << ")" << endl;
    cout << "Number of time steps (" << n << ")" << endl << endl;
    return 0;
}

// Ouput Market Settings 
int outMS(double r, double delta, double S0) {
    cout << "MARKET SETTINGS" << endl;
    cout << "Risk-Free Rate (" << r << ")" << endl;
    cout << "Implied Volatility (" << delta << ")" << endl;
    cout << "Inital value of underlying security (" << S0 << ")" << endl << endl;
    return 0;
}

// Output Option Settings 
int outOS(double T, double K, string type, string style, string exotic, double add_info) {
    cout << "OPTION SETTINGS:" << endl;
    cout << "Option Duration (" << T << ")" << endl;
    cout << "Option Strike Price (" << K << ")" << endl;
    cout << "Option Type (" << type << ")" << endl;
    cout << "Option Style (" << style << ")" << endl;
    cout << "Option Exotic (" << exotic << ")" << endl;
    cout << "Option Additional Info (" << add_info << ")" << endl << endl;
    return 0;
}

// Output Option Price
double outOptionPrice(int n, int N, double r, double delta, double S0, double T, double K, string type, string style, string exotic, double add_info) {
    // create stock price path
    vector<vector<double>> S = blackScholesMerton(n, N, r, delta, T, S0);
    // outputs
    cout << "Monte-Carlo Option Pricer" << endl << endl;
    outMCS(N, n);
    outMS(r, delta, S0);
    outOS(T, K, type, style, exotic, add_info);
    // output price option
    cout << "Option Price: ";
    cout << payoffFunctions(S, n, N, K, r, type, style, exotic, add_info) << endl << endl;
    cout << "____________________________________" << endl << endl;
    cout << "Input C to continue: ";
    string con;
    cin >> con;
    return 0;
}

// UI

// Main (UI)
int main() {
    // Output Title
    cout << "Monte Carlo Option Pricer" << endl << endl;
    cout << "____________________________________" << endl << endl;
    // Initalize UI variables
    int dictator = 0;
    string input_s;
    int input_i;
    double input_d;
    // Intialize Monte-Carlo Algorithm Settings 
    int N = 0;
    int n = 0;
    // Intialize Market Settings
    double r = 0;
    double delta = 0;
    double S0 = 0;
    // Initalize Option Settings
    double T = 0;
    double K = 0;
    string type = "NA";
    string style = "NA";
    string exotic = "NA";
    double add_info = 0;
    // Initalize satrting variable
    int startEnd = 1;
    // UI
    while (1) {
        // UI Option -1 (MENU UI)
        if (dictator == -1) {
            while (1) {
                outMenu();
                cin >> input_s;
                if (input_s == "MC" || input_s == "M" || input_s == "O" || input_s == "P" || input_s == "E") {
                    if (input_s == "MC") {
                        dictator = 1;
                    }
                    if (input_s == "M") {
                        dictator = 2;
                    }
                    if (input_s == "O") {
                        dictator = 3;
                    }
                    if (input_s == "P") {
                        dictator = 4;
                    }
                    if (input_s == "E") {
                        startEnd = -1;
                    }
                    break;
                }
                else {
                    cout << endl << "Incorrect input, please try again" << endl << endl;
                }
            }
            // Ouput 
            cout << "____________________________________" << endl << endl;
        }
        // UI Option 0 (Start UI)
        if (dictator == 0) {
            // Output MENU
            outMenu();
            // Output empty settings
            cout << "Settings are empty!" << endl << endl;
            cout << "____________________________________" << endl << endl;
            // change UI path
            dictator ++;
        }
        // UI option 1 (monte-Carlo algorithm settings UI)
        if (dictator == 1) {
            // Set Monte-Carlo Settings
            while (1) {
                cout << "Please enter, number of Monte-Carlo repettitions required: ";
                cin >> input_i;
                if (cin.fail() == false) {
                    cout << endl;
                    N = input_i;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, number of time steps requires: ";
                cin >> input_i;
                if (cin.fail() == false) {
                    cout << endl;
                    n = input_i;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            // Output Monte-Carlo algorithm Settings
            outMCS(n, N);
            cout << "____________________________________" << endl << endl;
            // change UI path
            if (startEnd == 1) {
                dictator ++;
            }
            else {
                dictator = -1;
            }
        }
        // UI Option 2 (Market settings UI)
        if (dictator == 2) {
            // Set Market settings 
            while (1) {
                cout << "Please enter, the risk-free rate: ";
                cin >> input_d;
                if (cin.fail() == false) {
                    cout << endl;
                    r = input_d;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, the implied volatility: ";
                cin >> input_d;
                if (cin.fail() == false) {
                    cout << endl;
                    delta = input_d;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, The inital value of the security: ";
                cin >> input_d;
                if (cin.fail() == false) {
                    cout << endl;
                    S0 = input_d;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            // Output Market Settings
            outMS(r, delta, S0);
            cout << "____________________________________" << endl << endl;
            // change UI path
            if (startEnd == 1) {
                dictator ++;
            }
            else {
                dictator = -1;
            }
            
        }
        // UI Option 3 (
        if (dictator == 3) {
            // Set Option Settings 
            while (1) {
                cout << "Please enter, the option duration: ";
                cin >> input_d;
                if (cin.fail() == false) {
                    cout << endl;
                    T = input_d;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, the option stike price: ";
                cin >> input_d;
                if (cin.fail() == false) {
                    cout << endl;
                    K = input_d;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, the option type i.e. Call (C) or Put (P): ";
                cin >> input_s;
                if (cin.fail() == false) {
                    cout << endl;
                    type = input_s;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, the option style i.e. european (EU) or american (AM): ";
                cin >> input_s;
                if (cin.fail() == false) {
                    cout << endl;
                    style = input_s;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                cout << "Please enter, the option exoticness i.e. N/A (non), asian fixed price (AS_FP), asian fixed srike price (AS_FS), barrier up and in (BA_UI), barrier up and out (BA_UO), barrier down and in (BA_DI) or barrier down and out (BA_DO): ";
                cin >> input_s;
                if (cin.fail() == false) {
                    cout << endl;
                    exotic = input_s;
                    break;
                }
                cout << endl << "Incorrect input, please try again" << endl << endl;
                cin.clear();
                cin.ignore(99999, '\n');
            }
            while (1) {
                if (exotic == "BA_UI") {
                    cout << "Please enter, the barrier options up and in point: " << endl;
                    cin >> input_d;
                    if (cin.fail() == false) {
                        cout << endl;
                        add_info = input_d;
                        break;
                    }
                    cout << endl << "Incorrect input, please try again" << endl << endl;
                    cin.clear();
                    cin.ignore(99999, '\n');
                }
                if (exotic == "BA_UO") {
                    cout << "Please enter, the barrier options up and out point: " << endl;
                    cin >> input_d;
                    if (cin.fail() == false) {
                        cout << endl;
                        add_info = input_d;
                        break;
                    }
                    cout << endl << "Incorrect input, please try again" << endl << endl;
                    cin.clear();
                    cin.ignore(99999, '\n');
                }
                if (exotic == "BA_DI") {
                    cout << "Please enter, the barrier options down and in point: " << endl;
                    cin >> input_d;
                    if (cin.fail() == false) {
                        cout << endl;
                        add_info = input_d;
                        break;
                    }
                    cout << endl << "Incorrect input, please try again" << endl << endl;
                    cin.clear();
                    cin.ignore(99999, '\n');
                }
                if (exotic == "BA_DO") {
                    cout << "Please enter, the barrier options down and out point: " << endl;
                    cin >> input_d;
                    if (cin.fail() == false) {
                        cout << endl;
                        add_info = input_d;
                        break;
                    }
                    cout << endl << "Incorrect input, please try again" << endl << endl;
                    cin.clear();
                    cin.ignore(99999, '\n');
                }
                double add_info = 0;
                break;
            }
            // Output Option Settings
            outOS(T, K, type, style, exotic, add_info);
            cout << "____________________________________" << endl << endl;
            // change UI path
            if (startEnd == 1) {
                dictator ++;
            }
            else {
                dictator = -1;
            }
        }
        // UI Option 4 (
        if (dictator == 4) {
            // Output Option price
            cout << "Please wait ..." << endl << endl;
            cout << "____________________________________" << endl << endl;
            outOptionPrice(n, N, r, delta, S0, T, K, type, style, exotic, add_info);
            cout << "____________________________________" << endl << endl;
            // chnage UI path 
            if (startEnd == 1) {
                startEnd = 0;
                dictator = -1;
            } 
            else {
                dictator = -1;
            }
        }
        // End Program
        if (startEnd == -1) {
            break;
        }
    }
    return 0;
}
