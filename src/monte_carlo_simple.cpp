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

int main(){
    double S0 = 100.0; //initial underlying price
    double K = 100.0; //strike price
    double r = 0.03; //risk free rate
    double sigma = 0.2; //volatility
    double T = 2.0; //time to maturity in years
    std::size_t N = 10000; //Number of monte carlo paths

    OptionType type = OptionType::Call;

}