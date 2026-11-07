#include <iostream>
#include <vector>
#include <algorithm>

void printBigInt(const std::vector<int>& num) {
    for (int i = num.size() - 1; i >= 0; --i) {
        std::cout << num[i];
    }
    std::cout << std::endl;
}

std::vector<int> multiplyBigInt(const std::vector<int>& a, int b) {
    std::vector<int> result = a;
    int carry = 0;
    for (std::size_t i = 0; i < result.size(); ++i) {
        long long cur = result[i] * b + carry;
        result[i] = cur % 10;
        carry = cur / 10;
    }
    while (carry) {
        result.push_back(carry % 10);
        carry /= 10;
    }
    return result;
}

std::vector<int> addBigInt(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result;
    int carry = 0;
    for (std::size_t i = 0; i < std::max(a.size(), b.size()) || carry; ++i) {
        int sum = carry;
        if (i < a.size()) sum += a[i];
        if (i < b.size()) sum += b[i];
        result.push_back(sum % 10);
        carry = sum / 10;
    }
    return result;
}

std::vector<int> subtractBigInt(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> result = a;
    int carry = 0;
    for (std::size_t i = 0; i < b.size() || carry; ++i) {
        result[i] -= carry + (i < b.size() ? b[i] : 0);
        carry = result[i] < 0;
        if (carry) result[i] += 10;
    }
    while (result.size() > 1 && result.back() == 0) {
        result.pop_back();
    }
    return result;
}

std::vector<int> powerOfTwo(int n) {
    std::vector<int> result = {1};
    for (int i = 0; i < n; ++i) {
        result = multiplyBigInt(result, 2);
    }
    return result;
}

void task1() {
    int input_1;
    std::cout << "Enter number > 100: ";
    std::cin >> input_1;
    if (input_1 <= 100) { std::cout << "ERROR: Number must be > 100\n"; return; }
    
    std::vector<int> fact = {1};
    for (int i = 2; i <= input_1; ++i) {
        fact = multiplyBigInt(fact, i);
    }
    std::cout << "Factorial: "; 
    printBigInt(fact);
}

void task2() {
    int input_1;
    std::cout << "Enter number > 64: ";
    std::cin >> input_1;
    if (input_1 <= 64) { std::cout << "ERROR: Number must be > 64\n"; return; }
    
    std::vector<int> res = powerOfTwo(input_1);
    std::cout << "2^" << input_1 << " = "; 
    printBigInt(res);
}

void task3() {
    int input_1, input_2;
    std::cout << "Enter 2 numbers > 64: ";
    std::cin >> input_1 >> input_2;
    
    // ДОБАВЛЕНА ПРОВЕРКА
    if (input_1 <= 64 || input_2 <= 64) { 
        std::cout << "ERROR: Both numbers must be > 64\n"; 
        return; 
    }
    
    std::vector<int> p1 = powerOfTwo(input_1);
    std::vector<int> p2 = powerOfTwo(input_2);
    std::vector<int> sum = addBigInt(p1, p2);
    
    std::cout << "2^" << input_1 << " + 2^" << input_2 << " = "; 
    printBigInt(sum);
}

void task4() {
    int input_1, input_2;
    std::cout << "Enter 2 numbers > 64 and 1st > 2nd: ";
    std::cin >> input_1 >> input_2;
    
    // ДОБАВЛЕНА ПРОВЕРКА
    if (input_1 <= 64 || input_2 <= 64 || input_1 <= input_2) { 
        std::cout << "ERROR: Both must be > 64, and 1st must be > 2nd\n"; 
        return; 
    }
    
    std::vector<int> p1 = powerOfTwo(input_1);
    std::vector<int> p2 = powerOfTwo(input_2);
    std::vector<int> diff = subtractBigInt(p1, p2);
    
    std::cout << "2^" << input_1 << " - 2^" << input_2 << " = "; 
    printBigInt(diff);
}

void task5() {
    int input_1;
    std::cout << "Enter number > 100: ";
    std::cin >> input_1;
    if (input_1 <= 100) { std::cout << "ERROR: Number must be > 100\n"; return; }
    
    std::vector<int> a = {1}; 
    std::vector<int> b = {1}; 
    if (input_1 == 1) { printBigInt(a); return; }
    if (input_1 == 2) { printBigInt(b); return; }
    
    std::vector<int> c;
    for (int i = 3; i <= input_1; ++i) {
        c = addBigInt(a, b);
        a = b;
        b = c;
    }
    std::cout << "Fibonacci element #" << input_1 << ": "; 
    printBigInt(b);
}

int main() {
    int choice;
    std::cout << "Enter the task number (1-5): ";
    std::cin >> choice;
    
    switch(choice) {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        default: std::cout << "Wrong number\n";
    }
    return 0;
}