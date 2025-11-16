#include <iostream>
#include <random>
#include <cmath>
#include <vector> 
#include <numeric> //for sums
#include <iomanip> //for formatting

enum class OptionType {Call, Put};
double payoff(double ST, double K, OptionType type){
    switch(type){
        case OptionType::Call: return std::max(ST-K,0.0);
                break;
        case OptionType::Put: return std::max(K-ST,0.0);
                break;
    }
    return 0.0;
};

std::vector<double> MonteCarloPayoffs(std::size_t N, double S0, double K, OptionType type, double drift, double volatility, std::mt19937_64& gen, std::normal_distribution<double>& nd){
    std::vector<double> payoffs;
    payoffs.reserve(N);
    for (int i = 0; i < N; ++i){   
        double normal_random = nd(gen);  
        double ST = S0 * std::exp(drift + volatility * normal_random);
        double Payoff = payoff(ST, K, type);
        payoffs.push_back(Payoff);
    }
    return payoffs;
}

int main(){
    OptionType type = OptionType::Call;
    double S0 = 100.0; //initial underlying price
    double K = 100.0; //strike price
    double r = 0.03; //risk free rate
    double sigma = 0.2; //volatility
    double T = 2.0; //time to maturity in years
    std::size_t N = 10000; //Number of monte carlo paths

    //creating Normally distributed values for Monte Carlo
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::normal_distribution<double> nd(0.0, 1.0);

    //computing parameters now to avoid slowing the loop
    double drift = (r - 0.5 * sigma * sigma) * T;
    double volatility = (sigma * std::sqrt(T));
    double discount_rate = std::exp(- r * T);

    //creating the payoff vector
    std::vector<double> all_payoffs = MonteCarloPayoffs(N, S0, K, type, drift, volatility, gen, nd);

    //computing the price of the option
    double sum_of_payoffs = std::accumulate(all_payoffs.begin(),all_payoffs.end(),0.0);
    double average_payoff = sum_of_payoffs / N;
    double option_price = discount_rate * average_payoff;

    //printing the result
    std::cout << "The price for the option is: " << option_price << std::endl;

}