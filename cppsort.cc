/**
 * filename: cppsort.cc 
 * author:   GHzbq
 * date:     2019.5.24
 * function: 尝试用C++封装各种排序算法
 * */
#include <iostream>
#include <vector>

template<typename T>
void print(std::vector<T>& array)
{
    for(auto& e : array)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void _mergeData(std::vector<T>& array, int left, int mid, int right, std::vector<T>& temp)
{
    int beginL = left;
    int beginR = mid;
    int pos = left;
    while(beginL < mid && beginR < right)
    {
        if(array[beginL] <= array[beginR])
        {
            temp[pos] = array[beginL];
            ++pos;
            ++beginL;
        }
        else
        {
            temp[pos] = array[beginR];
            ++pos;
            ++beginR;
        }
    }

    while(beginL < mid)
    {
        temp[pos] = array[beginL];
        ++pos;
        ++beginL;
    }

    while(beginR < right)
    {
        temp[pos] = array[beginR];
        ++pos;
        ++beginR;
    }

    pos = left;
    while(pos < right)
    {
        array[pos] = temp[pos];
        ++pos;
    }
}

template<typename T>
void _mergeSort(std::vector<T>& array, int left, int right, std::vector<T> & temp)
{
    /**
     * 这种情况，区间
     * 只有一个元素  或者
     * 一个元素都没有
     * 直接返回  作为递归的出口
     * */
    if(left+1 == right || right <= left)
    {
        return;
    }

    /**
     * 如果区间内只有两个元素，那么也没必要继续进行归并了
     * 也可以作为递归的一个出口
     * */
    if(left + 2 == right)
    {
        /**
         * 我们考虑排一个升序
         * */
        if(array[left] > array[left+1])
        {
            std::swap(array[left], array[left+1]);
        }
    }

    int mid = left + (right-left)/2;
    _mergeSort(array, left, mid, temp);
    _mergeSort(array, mid, right, temp);
    _mergeData(array, left, mid, right, temp);
}

/**
 * 这是递归版本的mergeSort
 * */
template<typename T>
void mergeSortRecursion(std::vector<T>& array)
{
    if(array.empty())
    {
        return ;
    }

    std::vector<T> temp;
    temp.resize(array.size());
    /**
     * 排序元素是一个左闭右闭的区间
     * */
    _mergeSort(array, 0, static_cast<int>(array.size()), temp);
}

/**
 * 这是非递归版本(循环迭代)的mergeSort
 * */
template<typename T>
void mergeSortCyclic(std::vector<T> & array)
{
    if(array.empty())
    {
        return;
    }

    std::vector<T> temp;
    temp.resize(array.size());
    int size = static_cast<int>(array.size());
    int left = 0;
    int right = 0;
    int mid = 0;
    int i = 0;
    int gap = 1;
    while(gap < size)
    {
        for(i = 0; i < size; i += 2*gap)
        {
            left = i;
            mid = left + gap;
            right = mid + gap;
            /**
             * 需要考虑 mid 和 right 越界的情况
             * */
            if(mid >= size)
            {
                mid = size;
            }

            if(right >= size)
            {
                right = size;
            }

            _mergeData(array, left, mid, right, temp);
        }

        gap *= 2;
    }
}

int main(void)
{
    std::vector<int> array{8, 6, 5, 3, 2, 9, 1, 0, 4, 5, 7};
    print(array);
    //mergeSortRecursion(array);
    mergeSortCyclic(array);
    print(array);


    return 0;
}
