#include <iostream>
#include <cmath>
#include <functional>
#include <thread>
#include <vector>


double myFunction(double x) {
    return std::sin(x);
}


double trapezoidalSegment(
    std::function<double(double)> f, 
    double a, 
    double b, 
    int n
) {
    double h = (b - a) / n;
    double integral = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        integral += f(a + i * h);
    }
    integral *= h;
    return integral;
}


void threadFunction(
    std::function<double(double)> f, 
    double a, 
    double b, 
    int n, 
    double& result
) {
    result = trapezoidalSegment(f, a, b, n);
}


int main() {
    double a, b;
    int n, numThreads;
    std::cout << "Enter the lower limit of integration (a): ";
    std::cin >> a;
    std::cout << "Enter the upper limit of integration (b): ";
    std::cin >> b;
    std::cout << "Enter the number of subintervals (n): ";
    std::cin >> n;
    std::cout << "Enter the number of threads: ";
    std::cin >> numThreads;
    double totalIntegral = 0.0;
    std::vector<std::thread> threads;
    std::vector<double> results(numThreads);
    double segmentWidth = (b - a) / numThreads;
    for (int i = 0; i < numThreads; ++i) {
        double segmentStart = a + i * segmentWidth;
        double segmentEnd = (i == numThreads - 1) ? b : (a + (i + 1) * segmentWidth);
        int segmentN = n / numThreads;
        threads.emplace_back(
            threadFunction, 
            myFunction, 
            segmentStart, 
            segmentEnd, 
            segmentN, 
            std::ref(results[i])
        );
    }
    for (auto& th : threads) th.join();
    for (const auto& res : results) totalIntegral += res;
    std::cout << "The approximate integral of the function from " << a << " to " << b << " is: " << totalIntegral << std::endl;
    return 0;
}
