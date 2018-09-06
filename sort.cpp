#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

//时间 最好：n 最坏：n^2 平均：n^2
//空间 1
//稳定
void bubble_sort(vector<int> &vec) {
    bool sorted = false;  // 外层优化,标记未排序是否已有序

    for (int i = 0; i <= vec.size() - 2 && !sorted; i++) {  // i标记未排序序列开头,初始0无已排序序列
        sorted = true;  // 若未出现交换,择未排序序列已有序
        for (int j = vec.size() - 1; j >= i + 1; j--) {  // j在未排序序列中从后向前遍历,直到遇到i
            if (vec[j] < vec[j - 1]) {
                swap(vec[j], vec[j - 1]);  // 如前一个比后一个大,则交换
                sorted = false;  // 出现交换说明未排序序列依然无序
            }
        }
    }
}

//时间 最好：n 最坏：n^2 平均：n^2
//空间 1
//稳定
void insertion_sort(vector<int> &vec) {
    for (int i = 1; i <= vec.size() - 1; i++) {  // i标记未排序序列开头,初始1默认第0个已排序
        int temp = vec[i];  //  保存当前基准值
        int j = i - 1;
        for (; j >= 0; j--) {  // 遍历已排序序列内容
            if (vec[j] > temp) vec[j + 1] = vec[j];  // 如果比基准值大,则往后移一位
            else break;
        }
        vec[j + 1] = temp;  // 填入基准值
    }
}

//时间 最好：n^2 最坏：n^2 平均：n^2
//空间 1
//稳定
void selection_sort(vector<int> &vec) {
    for (int i = 0; i <= vec.size() - 1; i++) {  // i标记未排序序列开头,初始0无已排序序列
        int min = i;  //  保存最小值下标

        for (int j = i; j <= vec.size() - 1; j++) {  // 遍历未排序序列
            if (vec[j] < vec[min]) {
                min = j;  // 保存最小值下标
            }
        }
        swap(vec[min], vec[i]);  // 将最小值与未排序序列第一个元素交换
    }
}

//时间 最好：n 最坏：n^2 平均：n^1.3
//空间 1
//不稳定
void shell_sort(vector<int> &vec) {
    for (int increment = vec.size() / 2; increment >= 1; increment /= 2) {  // increment逐渐变小,直到1变为插入排序
        for (int i = increment; i <= vec.size() - 1; i++) {  // i标记未排序序列开头,初始increment默认第0个已排序
            int temp = vec[i];  //  保存当前基准值
            int j = i - increment;
            for (; j >= 0; j -= increment) {  // 以increment的步距遍历已排序序列内容
                if (vec[j] > temp) vec[j + increment] = vec[j];  // 如果比基准值大,则往后移increment位
                else break;
            }
            vec[j + increment] = temp;  // 填入基准值
        }
    }
}


void merge(vector<int> &vec, int start, int mid, int end) {
//    int *temp = new int[end - start + 1];  //  临时储存合并结果
    int temp[end - start + 1];  //  临时储存合并结果
    int i = 0;
    int left = start;  // 左子树的起始下标
    int right = mid + 1;  // 右子树的起始下标
    while (left <= mid && right <= end) {  // 左右子树互相比较,把较小的先放进temp
        temp[i++] = vec[left] < vec[right] ? vec[left++] : vec[right++];
    }
    while (left <= mid) {  // 左子树剩余的放进temp
        temp[i++] = vec[left++];
    }
    while (right <= end) {  // 右子树剩余的放进temp
        temp[i++] = vec[right++];
    }
    for (int j = 0; j <= (end - start); j++) {  // 将temp赋值进对应的vec位置
        vec[start + j] = temp[j];
    }
}

//时间 最好：nlogn 最坏：nlogn 平均：nlogn
//空间 n
//稳定
void merge_sort(vector<int> &vec, int start, int end) {
    if (start == end) return;  // 分割至0个元素,则返回
    int mid = (start + end) / 2;  // 二分
    merge_sort(vec, start, mid);  // 递归左子树
    merge_sort(vec, mid + 1, end);  // 递归右子树
    merge(vec, start, mid, end);  // 将左右子树合并
}


void adjust_heap(vector<int> &vec, int start, int end) {
    int child = start * 2 + 1;  // 左孩子下标
    while (child < end) {
        if (child + 1 < end && vec[child] < vec[child + 1]) {  //比较左右孩子的值,取值大的下标
            child++;
        }
        if (vec[start] < vec[child]) {  // 孩子比对应的结点大
            int temp = vec[start];  // 交换孩子和结点的值,确保节点大于孩子
            vec[start] = vec[child];
            vec[child] = temp;
            start = child;  // 将结点下标移到新位置
            child = 2 * start + 1;  //  继续检查下一层是否满足大顶堆
        } else {
            break;
        }
    }
}

//时间 最好：nlogn 最坏：nlogn 平均：nlogn
//空间 1
//不稳定
void heap_sort(vector<int> &vec) {
    int n = vec.size();
    for (int i = n / 2 - 1; i >= 0; i--) {  // 循环结点位置
        adjust_heap(vec, i, n - 1);  // 调整每个结点组成大顶堆
    }
    for (int i = n - 1; i > 0; i--) {  // i标记未排序序列的末端,将根结点(最大值)与末端的值进行交换后调整大顶堆
        int temp = vec[i];  // 交换
        vec[i] = vec[0];
        vec[0] = temp;
        adjust_heap(vec, 0, i);  // 调整
    }
}


int partition(vector<int> &vec, int start, int end, bool mot) {
    if (mot) {  // median-of-three  抽取首尾中三个数值,将大小居中的值放在首位
        int mid = start + (end - start) / 2;
        if (vec[start] > vec[end]) swap(vec[start], vec[end]);
        if (vec[mid] > vec[end]) swap(vec[end], vec[mid]);
        if (vec[mid] > vec[start]) swap(vec[mid], vec[start]);
    }

    int base = vec[start];  // 临时保存基准值
    while (start < end) {
        while (start < end && vec[end] >= base)  // 从末端开始,如果大于等于基准值,则下标往中间近一位
            end--;
        vec[start] = vec[end];  // 如小于基准值,则赋值至前半段
        while (start < end && vec[start] <= base)  // 从首端开始,如果小于等于基准值,则下标往中间近一位
            start++;
        vec[end] = vec[start];  // 如大于基准值,则赋值至后半段
    }
    vec[start] = base;  // 将基准值放回序列分割位置
    return start;
}

const int MAX_LENGTH_INSERT_SORT = 10;  // 序列长度小于阈值则直接使用插入排序

//时间 最好：nlogn 最坏：n^2 平均：nlogn
//空间 logn
//不稳定
void quick_sort_v1(vector<int> &vec, int start, int end) {
    if (start < end) {
        int pivot = partition(vec, start, end, false);  // 分割并返回分割下标
        quick_sort_v1(vec, start, pivot - 1);  // 对左半边递归
        quick_sort_v1(vec, pivot + 1, end);  // 对右半边递归
    }
}

// 增加median-of-three
void quick_sort_v2(vector<int> &vec, int start, int end) {
    if (start < end) {
        int pivot = partition(vec, start, end, true);  // 分割并返回分割下标
        quick_sort_v2(vec, start, pivot - 1);  // 对左半边递归
        quick_sort_v2(vec, pivot + 1, end);  // 对右半边递归
    }
}

// 增加小序列直接使用插入排序
void quick_sort_v3(vector<int> &vec, int start, int end) {
    if ((end - start) > MAX_LENGTH_INSERT_SORT) {  // 序列长度达标则使用快速排序
        int pivot = partition(vec, start, end, true);  // 分割并返回分割下标
        quick_sort_v3(vec, start, pivot - 1);  // 对左半边递归
        quick_sort_v3(vec, pivot + 1, end);  // 对右半边递归
    } else
        insertion_sort(vec);  // 序列长度过小直接使用插入排序
}

// 增加尾递归
void quick_sort_v4(vector<int> &vec, int start, int end) {
    while (start < end) {
        int pivot = partition(vec, start, end, true);  // 分割并返回分割下标
        quick_sort_v4(vec, start, pivot - 1);  // 对半边递归
        start = pivot + 1;
    }
}

//时间 最好：n+k 最坏：n+k 平均：n+k
//空间 k
//不稳定
// 要求输入必须全是正整数
void counting_sort_unstable(vector<int> &vec, int max = -1) {
    if (max < 0) {  // 获取max,必须非负整数
        max = vec[0];
        for (int i = 1; i < vec.size(); i++) {
            max = vec[i] > max ? vec[i] : max;
        }
    }

    int index = 0;
    auto *temp = new int[max + 1]();  // 保存每个值出现的次数
    for (int x:vec) {  // 记录每个值出现的次数
        temp[x]++;
    }
    for (int i = 0; i < max + 1; i++) {  // 从头遍历temp,下标即为值
        while (temp[i] > 0) {
            vec[index++] = i;  // 排序过程,依次赋值
            temp[i]--;  //次数减一直到0
        }
    }
    delete[] temp;
}

//时间 最好：n+k 最坏：n+k 平均：n+k
//空间 n+k
//稳定
void counting_sort_stable(vector<int> &vec, int max = -1) {
    if (max < 0) {  // 获取max,必须非负整数
        max = vec[0];
        for (int i = 1; i < vec.size(); i++) {
            max = vec[i] > max ? vec[i] : max;
        }
    }

    auto *C = new int[max + 1]();  // 保存每个值出现的次数
    auto *B = new int[vec.size()]();  // 保存重新排序后的序列

    for (int x:vec) {
        C[x]++;  // 记录每个值出现的次数
    }
    for (int i = 1; i <= max; i++) {
        C[i] += C[i - 1];  // 累加
    }
    for (int i = vec.size() - 1; i >= 0; i--) {  // 倒叙遍历vec,
        B[C[vec[i]] - 1] = vec[i];  // 在B上排序
        C[vec[i]]--;  // 避免同值冲突
    }
    vec.assign(B, B + vec.size());
    delete[] C;
    delete[] B;
}

//时间 最好：n*k 最坏：n*k 平均：n*k
//空间 n
//稳定
// 要求输入必须全是正整数 内部可结合任意稳定排序方法
void radix_sort(vector<int> &vec, int max = -1) {
    if (max < 0) {  // 获取max,必须非负整数
        max = vec[0];
        for (int i = 1; i < vec.size(); i++) {
            max = vec[i] > max ? vec[i] : max;
        }
    }
    //内部使用计数排序
    auto *C = new int[10]();  // 保存每个值出现的次数
    auto *B = new int[vec.size()]();  // 保存重新排序后的序列

    for (int exp = 1; max / exp > 0; exp *= 10) {  //exp 1为个位，10为十位
        for (int x:vec) {
            C[(x / exp) % 10]++;  // 记录每个值出现的次数
        }
        for (int i = 1; i <= 9; i++) {
            C[i] += C[i - 1];  // 累加
        }
        for (int i = vec.size() - 1; i >= 0; i--) {  // 倒叙遍历vec,
            B[C[(vec[i] / exp) % 10] - 1] = vec[i];  // 在B上排序
            C[(vec[i] / exp) % 10]--;  // 避免同值冲突
        }
        memset(C, 0, sizeof(*C) * 10);
        vec.assign(B, B + vec.size());
    }

}

//选择桶
int choose_bucket(int num, int bucket_num, int min, int max) {
    int count = bucket_num * (num - min) / (max - min + 1);
    return count;
}

//时间 最好：n+k 最坏：n^2 平均：n+k
//空间 n+k
//稳定
//要求值均匀分布，内部可结合其他排序
void bucket_sort(vector<int> &vec, int bucket_num) {
    int min = vec[0];
    int max = vec[0];

    for (int i = 1; i < vec.size(); i++) {
        min = vec[i] < min ? vec[i] : min;
        max = vec[i] > max ? vec[i] : max;
    }

    if (min == max) return;
    //创建桶
    vector<vector<int>> bucket(bucket_num);

    int bucket_id = 0;
    for (int x:vec) {
        bucket_id = choose_bucket(x, bucket_num, min, max);  //选出数据应该放在哪个桶
        bucket[bucket_id].push_back(x);  //放入对应的桶
    }
    for (int i = 0; i < bucket_num; i++) {  //对每个桶分别使用快速排序
        quick_sort_v1(bucket[i], 0, bucket[i].size() - 1);
    }
    //将所有桶的数据按顺序组合起来
    int index = 0;
    for (int i = 0; i < bucket_num; i++) {
        for (int x:bucket[i]) {
            vec[index++] = x;
        }
    }
}


int main() {
    clock_t start, end;

    random_device rd;
    auto gen = default_random_engine(rd());
    uniform_int_distribution<int> dis(1, 10000);

    const int datasize = 1 << 10;
    vector<int> vec(datasize);

    for (int &x : vec) {
        *&x = dis(gen);
    }

    vector<int> temp = vec;

    start = clock();
    bubble_sort(temp);
    end = clock();
    cout << "BubbleSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    selection_sort(temp);
    end = clock();
    cout << "SelectionSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    insertion_sort(temp);
    end = clock();
    cout << "InsertionSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    shell_sort(temp);
    end = clock();
    cout << "ShellSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    merge_sort(temp, 0, datasize - 1);
    end = clock();
    cout << "MergeSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    heap_sort(temp);
    end = clock();
    cout << "HeapSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    quick_sort_v1(temp, 0, datasize - 1);
    end = clock();
    cout << "QuickSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    quick_sort_v2(temp, 0, datasize - 1);
    end = clock();
    cout << "QuickSort + median-of-three using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    quick_sort_v3(temp, 0, datasize - 1);
    end = clock();
    cout << "QuickSort + median-of-three + insert using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    quick_sort_v4(temp, 0, datasize - 1);
    end = clock();
    cout << "QuickSort + median-of-three + tail-recursion using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    counting_sort_stable(temp);
    end = clock();
    cout << "CountingSort stable using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    counting_sort_unstable(temp);
    end = clock();
    cout << "CountingSort unstable using: " << end - start << " us" << endl;


    temp = vec;
    start = clock();
    radix_sort(temp);
    end = clock();
    cout << "RadixSort using: " << end - start << " us" << endl;

    temp = vec;
    start = clock();
    bucket_sort(temp, 10);
    end = clock();
    cout << "BucketSort using: " << end - start << " us" << endl;

    start = clock();
    sort(vec.begin(), vec.end());
    end = clock();
    cout << "standard sort using: " << end - start << " us" << endl;
}