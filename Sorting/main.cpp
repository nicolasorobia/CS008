#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& arr, int target)
{
    int low = 0, high = int(arr.size()) - 1;

    while (low <= high)
    {
        // handles int overflow
        int mid = low + (high - low) / 2;  
        if (arr[mid] < target)      low  = mid + 1;
        else if (arr[mid] > target) high = mid - 1;
        else                        return mid; // found target
    }

    return -1; // target not found
}

std::size_t lowerBound(const std::vector<int>& arr, int target, long& count)
{
    std::size_t low = 0, high = arr.size();
    while (low < high) {
        std::size_t mid = low + (high - low) / 2;
        count++;
        if (arr[mid] < target) low  = mid + 1;
        else                   high = mid;
    }

    return low;
}

int main()
{
    // Part 1 implementation
    std::vector<int> data = {3, 8, 15, 22, 37, 41, 56, 70};
    std::cout << "Print index of where target is in array. If not in there, return -1\n";
    int target = 15, target2 = 67;

    std::cout << "Target " << target << " is in index: " << binarySearch(data, target) << '\n';
    std::cout << "Target " << target2 << " is in index: " << binarySearch(data, target2) << '\n';

    // Part 2 implementation
    // long counter = 0; // added for part 3
    // std::size_t i = lowerBound(data, target2, counter);
    // if (i < data.size() && data[i] == target2) {
    //     std::cout << "Target found!\n";
    // } else {
    //     std::cout << target2 << " is not in data, insert it at index " << i << '\n';
    // }

    // Part 3: linear scan vs binary search
    const std::size_t N = 1000000;
    std::vector<int> bigData;
    bigData.reserve(N); // allocate once

    // fill with even numbers
    for (std::size_t i = 0; i < N; i++) bigData.push_back(int(i * 2));

    long bs_count = 0; // binary search counter
    long ls_count = 0; // linear scan counter
    int bigTarget = 676767;

     // linear search: only count inside the loop, print once after it
    bool foundLinear = false;
    for (std::size_t j = 0; j < N; j++) {
        ls_count++;
        if (bigData[j] == bigTarget) {
            foundLinear = true;
            break;
        }
    }
 
    if (foundLinear)
        std::cout << "Linear scan found the target in " << ls_count << " comparisons\n";
    else
        std::cout << "Linear scan: not in data after " << ls_count << " comparisons\n";


    // binary search
    std::size_t index = lowerBound(bigData, bigTarget, bs_count);

    if (index < bigData.size() && bigData[index] == bigTarget)
        std::cout << "Binary search found the target in " << bs_count << " comparisons\n";
    else
        std::cout << "Binary search: not in data after " << bs_count << " comparisons\n";
    
    return 0;
}