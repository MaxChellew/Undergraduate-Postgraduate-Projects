# Monte Carlo Option Pricer

This project was a self-set project that looked into the implementation of a Monte Carlo simulation to price exotic options. The theoretical basis behind this program was to use Brownian motion to simulate the change in the underlying stock's price over time. Then multiple simulations of the stocks price could be mapped and the payoffs of an option could be calculated for each simulation. The payoffs for each simulation could then discounted to give the value of the option at time zero and average to aproximate the finial value of the option. Please find the C++ file in the repository to explore the exotic option pricer program.

Note: This program has not been heavily tested and may contain bugs

## Table of contents
1. [Objective](##objective)
2. [Key Takeaways](#key_takeaways)
3. [Reflection](#reflection)

<a name="objectives"></a>
## Objectives
Following are the project objectives:
- Create a monte-carlo simulation of a stock price
- Calculate the Payoff for different types of options (Put or Call)
- Calculate the payoff for different styles of options (European or American)
- Calculate the payoff for different exoticness of options (non-exotic, Asian, Barrier)
- Discounting
- Implement a User interface (UI)

<a name="key_takeaways"></a>
## Key Takeaways
Following is the knowledge I acquired from completing this project:
- Coding in C++
- Peforming Monte Carlo simulation using browian motion
- Payoff functuons for different options
- Calculating discount factors

<a name="reflection"></a>
## Reflection
Following are the things i would do to improve this project:
- Implement Pointers
- Opitmize code structure to improve runtime of calculating option prices
- Perform over all testing of program
- Perform testing of convergence for different N and n values
