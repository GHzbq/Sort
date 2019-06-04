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
/**
 * 1. 冒泡排序
 * 以下代码是冒泡排序的实现
 * */
template <typename T>
void bubbleSort(std::vector<T>& array)
{
    if(array.empty())
    {
        return;
    }

    int size = static_cast<int>(array.size());
    int i = 0;
    int j = 0;
    bool flag = true;
    for(i = 0; i < size; ++i)
    {
        for(j = i; j < size; ++j)
        {
            ;
        }
    }
}

/**
 * 5. 快速排序
 * 以下代码是快排的实现
 * */

/**
 * 对快排的优化
 * */
template<typename T>
void median_of_three(std::vector<T>& array, int left, int right)
{
    int mid = left + (right-left)/2;
    if(array[left] <= array[mid])
    {
        if(array[mid] <= array[right-1])
        {
            // 这样的话，array[mid]就是第二大数
            // array[rihgt]为最大数
            // 将其交换
            // FIXME 这里可能需要判断一下 mid 是否等于 right-1
            std::swap(array[mid], array[right-1]);
        }
        else if(array[left] <= array[right-1])
        {
            // 这种情况 array[mid]最大
            // array[right-1]第二大
            // 不需要处理
        }
        else // array[right-1] < array[left]
        {
            std::swap(array[left], array[right-1]);
        }
    }
    else // array[left] > array[mid]
    {
        if(array[mid] >= array[right-1])
        {
            // array[left] 最大
            // array[mid]  第二大
            std::swap(array[mid], array[right-1]);
        }
        else if(array[left] >= array[right-1])
        {
            // array[left] 最大
            // array[right-1] 第二大
            // 这种情况不需要理会
        }
        else // array[right-1] > array[left] > array[mid]
        {
            std::swap(array[left], array[right -1]);
        }
    }
}

/**
 * 快排实现方法很多，我们只写一个好了
 * */
template <typename T>
int pation(std::vector<T>& array, int left, int right)
{
    /**
     * 考虑极值的情况
     * 我们采取一种办法，避免取到极值
     * 三数取中法 取三个数，最左，最中间和最右边，然后将三个数的第二大放到 array[rigth-1]的位置作为基准值
     * */
    median_of_three(array, left, right);
    int key = array[right-1];
    int begin = left;
    int end = right -1;

    while(begin < end)
    {
        /**
         * 反正不知道为什么
         * 一定要先找数组前面第一个大于key的值
         * 和 数组后面以一个小于key的值
         * 不然没办法排序
         * */
        while(begin < end && array[begin] <= key)
        {
            ++begin;
        }

        while(begin < end && array[end] >= key)
        {
            --end;
        }

        if(begin < end)
        {
            std::swap(array[begin], array[end]);
        }
    }

    if(begin != right-1)
    {
        std::swap(array[begin], array[right-1]);
    }

    return begin;
}

template <typename T>
void _quickSort(std::vector<T>& array, int left, int right)
{
    if (right - left > 1)
    {
        int pos = pation(array, left, right);
        _quickSort(array, left, pos);
        _quickSort(array, pos, right);
    }
}

template<typename T>
void quickSort(std::vector<T>& array)
{
    if(array.empty())
    {
        return ;
    }

    _quickSort(array, 0, static_cast<int>(array.size()));
}


/**
 * 6. 归并排序
 * 以下部分代码为 归并排序 的实现
 * */
/**
 * 这个_mergeData函数的作用是 
 * 借助辅助空间 temp
 * 将[left, mid)和[mid, right)区间的元素和并
 * */
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

    /**
     * 对一次_mergeData操作
     * 以下两个while循环 只会进入一个
     * 原因很好想
     * */
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
    //mergeSortCyclic(array);
    // quickSort<typename T>( std::vector<int> &array  )
    quickSort(array);
    print(array);


    return 0;
}
