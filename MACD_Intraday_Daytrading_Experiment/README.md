# Intraday Daytrading Experiment

In this third-year university project for Trading, Market Design & Application, I simulate the role of an intraday trader by back and forward testing a trading strategy that utilizes a (6,24,3) MACD technical indicator. During the backtesting of this trading strategy, I download past market data from Yahoo Finance and perform data manipulation to stitch and reformat the data into a format inputtable to a Python function built to mimic the trading strategy set out in this project. The process of mimicking the trading strategy is performed for TSLA, NVDA, and GOOG stocks, and then the outcomes are measured using certain performance tests. In this experiment, shorting TSLA using the trading strategy in question yields the best results, and it is brought forward to the forward testing on Interactive Brokers, where it is traded on live market data. The performance of the forward test is then analyzed to provide a comparison of results from both the forward test and backtest to identify the effectiveness of the trading strategy. The accompanying Technical Report describes the experiment's process in more detail and discusses my findings. Please see the code file for all related Python code and the PDF file for the detailed Technical Report.

## Table of contents
1. [Objectives](#objectives)
2. [Key Takeaways](#key_takeaways)

<a name="objectives"></a>
## Objectives
Following are the objectives for this project:
- Backtest trading strategy for different stocks
- Measure the perfomrance of each backtest 
- Forward test the trading strategy on the most promising stock using live market data
- Measure the performance of the forward test

 <a name="key_takeaways"></a>
## Key Takeaways
Following is the knowledge I acquired from completing this project:
- Withdrawing market data from Yahoo finance in python
- Data anyalsis using Pandas
- Moving Averages & Exoponetial Moving Averages
- MACD Technical Indicator
- Performance Measures: Avg.Ret Tot.Ret Std.Ret Sharpe.Ratio Tot.PnL Win.Ratio
- Performance Measure (forward test exclusive): t-test
- Volatility smiles
