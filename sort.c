#include "sort.h"

void _swap(DataType * left, DataType * right)
{
    DataType temp = *left;
    *left = *right;
    *right = temp;
}
void insertSort(DataType *array, int size)
{

    if(array == NULL)
    {
        return;
    }
    int i = 1; // 
    DataType key = 0;
    for(i = 1; i < size; ++i)
    {
        key = array[i];
        if(array[i] < array[i - 1])
        {
           // // 直接查找插入位置 由于数据元素比较少 
           // int j = 0;
           // for(j = i; j > 0; --j)
           // {
           //     if(key < array[j - 1])
           //     {
           //         array[j] = array[j - 1];
           //     }
           //     else 
           //     {
           //         break;
           //     }
           // }
           // array[j] = key;
            // 由于前面部分数据已经有序 可以考虑二分查找
            int begin = 0;
            int end = i - 1;
            int left = begin;
            int right = end;
            while(left <= right)
            {
                int mid = left + (right - left) / 2;
                if(key < array[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            // left 就是插入元素的位置
            // 将 left 及其之后的元素向后搬移
            while(end >= left)
            {
                array[end + 1] = array[end];
                --end;
            }
            // 然后将 key 放到下标为 left 处
            array[left] = key;
        }
    
    }
}
void shellSort(DataType * array, int size)
{// 也是插入排序的思想 不过进行分组
    if(array == NULL)
    {
        return;
    }

    int i = 0;
    int gap = size;
    while(gap > 1)
    {
        gap = gap / 3 + 1;
        for(i = gap; i < size; ++i)
        {
            DataType key = array[i];
            int end = i - gap;
            while(end >= 0 && key < array[end])
            {
                array[end+gap] = array[end];
                end -= gap;
            }
            array[end+gap] = key;
        }
    }
}

void BubbleSort(DataType *array, int size)
{
    if(array == NULL)
    {
        return;
    }
    int i = 0;
    int j = 0;
    int flag = 0;
    for(i = 0; i < size; ++i)
    {
        for(j = 0; j < size - i - 1; ++j)
        {
            if(array[j] > array[j+1])
            {
                _swap(&array[j], &array[j+1]);
                flag = 1;
            }
        }
        if(flag == 0)
        {
            break;
        }
    }
}

void selectSort(DataType * array, int size)
{
    if(array == NULL)
    {
        return;
    }
    

    int begin = 0;
    int end = size-1;
    while(begin < end)
    {
        int maxpos = begin;
        int minpos = begin;
        int j = begin + 1;
        while(j <= end)
        {
            if(array[j] > array[maxpos])
            {
                maxpos = j;
            }
            if(array[j] < array[minpos])
            {
                minpos = j;
            }
            ++j;
        }
        if(maxpos != end)
        {
            _swap(&array[end], &array[maxpos]);
        }
        if(minpos == end)
        {
            minpos = maxpos;
        }
        if(minpos != begin)
        {
            _swap(&array[begin], &array[minpos]);
        }

        ++begin;
        --end;
    }
    
}


int GetMidIndex(DataType * array, int left, int right)
{
    int mid = left + (right - left) / 2;
    if(array[left] < array[mid])
    {
        if(array[right - 1] > array[mid])
        {
            return mid;
        }
        else if(array[right - 1] < array[left])
        {
            return left;
        }
        else
        {
            return right - 1;
        }
    }
    else
    {// array[left] > array[mid]
        if(array[right - 1] > array[left])
        {
            return left; 
        }
        else if(array[mid] > array[right - 1] )
        {
            return mid;
        }
        else
        {
            return right - 1;
        }
    }
}

// 前后指针
int division(DataType * array, int left, int right)
{
    DataType key = array[right - 1];
    int begin = left;
    int end = right - 1;
    while(begin < end)
    {
        while(begin < end && array[begin] <=  key)
        {
            ++begin;
        }
        while(begin < end && array[end] >= key)
        {
            --end;
        }
        if(begin < end)
        {
            _swap(&array[begin], &array[end]);
        }
    }

    // 此时 begin 和 end 相遇 
    _swap(&array[begin], &array[right - 1]);
    return begin;
}

// 挖坑法
int division1(DataType * array, int left, int right)
{
    DataType key = array[right - 1]; // 注意到此时 right - 1 是一个坑
    int begin = left;
    int end = right - 1;
    while(begin < end)
    {
        while(begin < end && key >= array[begin])
        {
            ++begin;
        }
        // 此时就找到了第一个 大于基准值的元素
        // 填坑
        if(begin < end)
        {
            array[end] = array[begin];
        }
        while(begin < end && array[end] >= key)
        {
            --end;
        }
        if(begin < end)
        {
            array[begin] = array[end];
        }
    }
    array[begin] = key;
    return begin;
}

// 前后指针 朝同一个方向走
int division2(DataType *array, int left, int right)
{
    int pre = left - 1;
    int cur = left;
    DataType key = array[right - 1];
    while(cur < right - 1)
    {
        if(array[cur] < key && cur - pre > 0)
        {
            ++pre;
            _swap(&array[cur], &array[pre]);
        }
        else 
        {

        }
        ++cur;
    }

    _swap(&array[++pre], &array[right - 1]);
    return pre;
}

void quickSort(DataType * array, int left, int right)
{
    if(NULL == array)
    {
        return;
    }

    if(left >= right - 1)
    {
        return;
    }

    int mid = GetMidIndex(array, left, right);
    if(mid != right - 1)
    {
        _swap(&array[mid], &array[right - 1]);
    }
    int ret = division2(array, left, right);
    quickSort(array, left, ret);
    quickSort(array, ret+1, right);
}


void AdjustDown(DataType * array, int size, int parent)
{
    int child = parent * 2 + 1;
    while(child < size)
    {
        if((child + 1) < size && (array[child + 1] - array[child]) > 0)
        {
            child += 1;
        }
        if(array[parent] < array[child])
        {
            _swap(&array[parent], &array[child]);
            parent = child;
            child = parent * 2 + 1;
        }
        else 
            return;
    }
}

void createHeap(DataType * array, int size)
{
    int end = size - 1;
    int root = ((size - 1) - 1) / 2;
    for(; root >= 0; --root)
    {
        AdjustDown(array, size, root);
    }
    // 排序
    while(end)
    {
        _swap(&array[0], &array[end]);
        AdjustDown(array, end, 0);
        --end;
    }
}

// 升序，建个大堆
void heapSort(DataType * array, int size)
{
    if(array == NULL)
    {
        return;
    }
    createHeap(array, size);
}

void mergeSort(DataType * array, int size)
{
    if(array == NULL)
    {
        return ;
    }

}

void radixSort(DataType * array, int size);

void print(DataType *array, int size)
{
    if(array == NULL)
    {
        return;
    }
    int i = 0;
    for(i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

