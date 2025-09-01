//Blog: https://blockdmask.tistory.com/308 (난수 생성)
//Blog: https://velog.io/@seo78200/Algorithm-branch-and-bound-knapsack-problem (branch and bound)
//HyperScale AI: Gemini (Brute Force, BB, 람다 표현식 등등)
//Blog: https://zoomkoding.github.io/algorithm/2019/04/11/knapsack-1.html (greedy 등)
//Lecture slide chapter 6. page16-29 (BB )
/*
문제 해석
Brute Force, Greedy(fractional), DP, BB로 knapsack 문제ㅔ 해결하기
DP와 BB는 수업시간에 다루었으며, Greedy는 0-1을 해결하지 못하므로 Fractional로 해결
Brute Force는 다른곳에도 떠와도 됌

난수 생성
100으로 고정된 시드로 난수를 생성해(srand 사용해야함)
각 방법으로 해결 할 때 계속 100으로 초기화 하여서 각각의 알고리즘이 같은 data를 받는다
Benefit은 int 1 to 500
Weight는 int 1 to 100
Knapsack capacity = number of items * 25

출력 양식
Number of Items | Processing time in ms / Maximum benefit value
*/
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <functional>

using namespace std;
using namespace std::chrono;

void solve_recursive(int index, int current_weight, int current_benefit, int capacity, const vector<int>& weights, const vector<int>& benefits, int n, long long& max_benefit) {
    if (index == n) {
        if (current_weight <= capacity && current_benefit > max_benefit) {
            max_benefit = current_benefit;
        }
        return;
    }

    if (current_weight + weights[index] <= capacity) {
        solve_recursive(index + 1, current_weight + weights[index], current_benefit + benefits[index], capacity, weights, benefits, n, max_benefit);
    }

    solve_recursive(index + 1, current_weight, current_benefit, capacity, weights, benefits, n, max_benefit);
}

pair<long long, int> knapsack_bruteforce(int capacity, const vector<int>& weights, const vector<int>& benefits) {
    int n = benefits.size();
    long long max_benefit = 0;

    auto start_time = high_resolution_clock::now();
    solve_recursive(0, 0, 0, capacity, weights, benefits, n, max_benefit);
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);

    return {duration.count(), (int)max_benefit};
}

double calculate_bound(int level, int current_weight, int current_benefit, int capacity, const vector<int>& weights, const vector<int>& benefits) {
    int remain_capacity = capacity - current_weight;
    double bound = current_benefit;

    for (int i = level; i < weights.size() && remain_capacity > 0; ++i) {
        if (weights[i] <= remain_capacity) {
            remain_capacity -= weights[i];
            bound += benefits[i];
        } else {
            bound += (double)benefits[i] / weights[i] * remain_capacity;
            break ;
        }
    }
    return (bound);
}

pair<long long, int> knapsack_branch_and_bound(int capacity, const vector<int>& weights, const vector<int>& benefits) {
    int n = benefits.size();
    priority_queue<tuple<double, int, int, int>> pq;
    pq.push({calculate_bound(0, 0, 0, capacity, weights, benefits), 0, 0, 0});
    int max_benefit = 0;
    
    auto start_time = high_resolution_clock::now();

    while (!pq.empty()) {
        auto [bound, level, current_weight, current_benefit] = pq.top();
        pq.pop();


        if (bound <= max_benefit) {
            continue;
        }

        if (level == n) {
            if (current_benefit > max_benefit) {
                max_benefit = current_benefit;
            }
            continue;
        }

        int next_level = level + 1;

        int next_weight_include = current_weight + weights[level];
        int next_benefit_include = current_benefit + benefits[level];
        if (next_weight_include <= capacity) {
            double bound_include = calculate_bound(next_level, next_weight_include, next_benefit_include, capacity, weights, benefits);
            if (bound_include > max_benefit) {
                pq.push({bound_include, next_level, next_weight_include, next_benefit_include});
            }
        }

        double bound_exclude = calculate_bound(next_level, current_weight, current_benefit, capacity, weights, benefits);
        if (bound_exclude > max_benefit) {
            pq.push({bound_exclude, next_level, current_weight, current_benefit});
        }
    }
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    return {duration.count(), max_benefit};
}

bool compare(const tuple<double, int, int>&a, const tuple<double, int, int>& b) {
    return get<0>(a) > get<0>(b);
}

pair<long long, double> knapsack_greedy(int capacity, const vector<int> weights, const vector<int> benefits) {
    int n = benefits.size();
    vector<tuple<double, int, int>> items(n);

    for (int i = 0; i < n; ++i) {
        items[i] = {(double)(benefits[i]) / weights[i], weights[i], benefits[i]};
    }

    sort(items.begin(), items.end(), compare);

    double max_benefit = 0;
    int current_weight = 0;

    auto start_time = high_resolution_clock::now();

    for (const auto& item : items) {
        double ratio = get<0>(item);
        int weight = get<1>(item);
        int benefit = get<2>(item);

        if (current_weight + weight <= capacity) {
            current_weight += weight;
            max_benefit += benefit;
        } else {
            int remain_capacity = capacity - current_weight;
            max_benefit += ratio * remain_capacity;
            break ;
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    return {duration.count(), max_benefit};
}

pair <long long, int> knapsack_dp(int capacity, const vector<int>& weights, const vector<int>& benefits) {
    int n = benefits.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    auto start_time = high_resolution_clock::now();

    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            if (weights[i - 1] <= w) {
                dp[i][w] = max(benefits[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    return {duration.count(), dp[n][capacity]};
}


int main(void)
{
	vector<int> bbitems = {11, 21, 31};
    vector<int> otheritems = {10, 100, 1000, 10000};
    cout << "1.Brute force" << endl;
    cout << "Number of items\t\t\t Processing time in ms / Maximum benefit value" << endl;
	for (int num_items : bbitems)
	{
		cout << num_items;

		vector<int> benefits(num_items);
		vector<int> weights(num_items);
		int capacity = num_items * 25;

		for (int i = 0; i < num_items; ++i)
		{
			benefits[i] = rand() % 500 + 1;
			weights[i] = rand() % 500 + 1;
		}

		pair<long long, int> result_bf = knapsack_bruteforce(capacity, weights, benefits);
		cout << "\t\t\t\t " << result_bf.first << "ms / " << result_bf.second << endl;
    }
    cout << endl;
    cout << "2.Greedy / D.P. / B.&B." << endl;
    cout << "Number of items\t\t\t Processing time in ms / Maximum benefit value" << endl;
    cout <<"\t\t\t\t Greedy\t\t\t D.P.\t\t\t B.&B." << endl;
    for (int num_items : otheritems)
    {
        cout << num_items;

        vector<int> benefits(num_items);
        vector<int> weights(num_items);
        int capacity = num_items * 25;

        for (int i = 0; i < num_items; ++i)
        {
            benefits[i] = rand() % 500 + 1;
            weights[i] = rand() % 500 + 1;
        }

        
        
        pair<long long, int> result_dp = knapsack_dp(capacity, weights, benefits);
        cout << "\t\t\t\t " << result_dp.first << "ms / " << result_dp.second;
        pair<long long, int> result_bb = knapsack_branch_and_bound(capacity, weights, benefits);
        cout << "\t\t " << result_bb.first << "ms / " << result_bb.second;
        pair<long long, double> result_greedy = knapsack_greedy(capacity, weights, benefits);
        cout << "\t\t " << result_greedy.first << "ms / " << result_greedy.second;
        cout << endl;
    }
}