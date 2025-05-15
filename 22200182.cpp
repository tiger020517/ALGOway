//Blog: https://blockdmask.tistory.com/308 (난수 생성)
//

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

#include <iostream>
#include <vector>
#include <chrono>
#include <numeric> // std::accumulate

using namespace std;
using namespace std::chrono;

pair<long long, int> knapsack_bruteforce(int capacity, const vector<int>& weights, const vector<int>& benefits) {
    int n = benefits.size();
    long long max_benefit = 0;
    auto start_time = high_resolution_clock::now();

    function<void(int, int, int)> solve =
        [&](int index, int current_weight, int current_benefit) {
        if (index == n) {
            if (current_weight <= capacity && current_benefit > max_benefit) {
                max_benefit = current_benefit;
            }
            return;
        }

        // Include the current item
        if (current_weight + weights[index] <= capacity) {
            solve(index + 1, current_weight + weights[index], current_benefit + benefits[index]);
        }

        // Exclude the current item
        solve(index + 1, current_weight, current_benefit);
    };

    solve(0, 0, 0);

    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    return {duration.count(), (int)max_benefit};
}

int main(void)
{
	vector<int> bbitems = {11, 21, 31};

	for (int num_items : bbitems)
	{
		cout << "Number of items: " << num_items << endl;

		vector<int> benefits(num_items);
		vector<int> weights(num_items);
		int capacity = num_items * 25;

		for (int i = 0; i < num_items; ++i)
		{
			benefits[i] = rand() % 500 + 1;
			weights[i] = rand() % 500 + 1;
		}

		cout << "Knapsack Capacity: " << capacity << endl;

		pair<long long, int> result_bf = knapsack_bruteforce(capacity, weights, benefits);
		cout << "Brute-force: Processing Time = " << result_bf.first << "ms, Maximum Benefit = " << result_bf.second << endl;
	}
}