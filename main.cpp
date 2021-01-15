#include "iostream"
#include <type_traits>
#include <vector>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;

#define BIGINT 32767

/**************
 * UTIL funcs to let users create arrays using input and to print array info
 * ***********/

template<typename T>
string toString(const T& value)
{
    ostringstream oss;
    oss << value;
    return oss.str();
}

template<typename T>
std::vector<T> split(const std::string& s, char delimiter)                                                                                                                          
{                                                                                                                                                                                             
   std::vector<T> splits;                                                                                                                                                           
   std::string split;                                                                                                                                                                         
   std::istringstream ss(s);                                                                                                                                                                  
   while (std::getline(ss, split, delimiter))                                                                                                                                                 
   {
        if (std::is_same<T, int>::value || std::is_same<T, short>::value) {
            splits.push_back(atoi(split.c_str()));
        } else if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            splits.push_back(atof(split.c_str()));
        }                                                                                                                                           
   }                                                                                                                                                                                          
   return splits;                                                                                                                                                                             
}

//By not it just supports int, short, double and float!
template<typename T>
vector<T> userAllocatesData() { 
    cout << "Write data separated by comma (ex: 1, 2, 3, 4,... 9)" << endl;
    string input_data;
    getline (cin, input_data);
    vector<T> data = split<T>(input_data, ',');

    return data;
}

template<typename T>
string vectorToString(vector <T>vec) {
    int size = vec.size();
    string ret;
    ret.append("[");
    for (int i = 0; i < size; i++) {
        ret.append(toString<T>(vec[i]));
        if (i < size-1) {
            ret.append(", ");
        }
    }
    ret.append("]");
    return ret;
}

template <typename T>
string arrayToString(T* array, int size) {
    vector<T> vec;
    for (int i = 0; i < size; i++) {
        vec.push_back(array[i]);
    }
 
    return vectorToString(vec);
}

template <typename T, size_t n> 
int findSizeArray(T (&arr)[n]) 
{ 
    return int(n);
} 


/**************
 * END Util
 * ***********/

/***************
 *  Insertion sort
 * ************/

template<typename T>
vector<T> insertSort(vector<T>vec) {
    vector<T> copy_vec(vec); //copy array to copy_vec
    int size = copy_vec.size();
    int steps=0;
    for (int j=1; j < size; j++){
        T key = copy_vec[j];
        int i = j-1;
        while (i >= 0 && copy_vec[i] > key) {
            if (i < j-1) {
                steps++;
            }
            copy_vec[i+1] = copy_vec[i];
            i--;
        }
        steps++;
        copy_vec[i+1] = key;
    }
    cout << "steps: " << steps << endl;
    return copy_vec;
}


/*******************
 *  Selection sort
 * *****************/

template<typename T>
vector<T>selectionSort(vector<T>vec) {
    vector<T>copy_vec(vec);
    int n = copy_vec.size();
    for (int i=0; i < n-1; i++) {
        int smallest=i;
        for (int j=i+1; j < n; j++) {
            if (copy_vec[j] < copy_vec[smallest]) {
                smallest = j;
            }
        }
        //Following three lines of code equals to "exchange copy_vec[i] with copy_vec[smallest]"
        T key = copy_vec[i];
        copy_vec[i] = copy_vec[smallest];
        copy_vec[smallest] = key;
    }
    return copy_vec;
}

/*************************
 *  MERGE SORT
 * ***********************/

template<typename T>
void merge(vector<T>&vec, int p, int q, int r) {
    cout << "values: [" << p << ", " << q << ", " << r << "]" << endl;
    int i, j;
    vector<T>L(q-p+1);
    vector<T>R(r-q);
    for (i = 0; i < L.size(); i++) {
        L[i] = vec[p+i];
    }
    for (j=0; j < R.size(); j++) {
        R[j] = vec[q+1+j];
    }
    L.push_back(BIGINT);
    R.push_back(BIGINT);
    i = j = 0;
    for (int k = p; k < r+1; k++){
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
    }
}

template <typename T>
void merge_sort(vector<T>&vec, int p, int r) {
    if (p < r) {
        int q = (p+r)/2;
        merge_sort(vec, p, q);
        merge_sort(vec, q+1, r);
        merge(vec, p, q, r);
    }
}

template <typename T>
int findValueIndex(vector<T>vec, T val) {
    int size = vec.size();
    for (int i=1; i < size; i++) {
        if (vec[i] == val) {
            return i;
        }
    }
    return -1;
}

template <size_t n>
int *binarySum(int (&A)[n], int (&B)[n]) {
    int size = n;
    int *C = new int[size+1];
    C[0] = 0;
    for (int i =0; i < size; i++) {
        C[i+1] = int(floor(float(C[i]+A[i]+B[i])/2.0));
        C[i] = (C[i]+A[i]+B[i]) % 2;
    }
    return C;
}

int main()
{
    vector<int> numbers = userAllocatesData<int>();
    cout << vectorToString(numbers) << endl;
    //numbers = selectionSort<int>(numbers);
    merge_sort<int>(numbers, 0, numbers.size()-1);
    cout << "Data ordered in a non-decresent way using insertion-sort: " << endl;
    cout << vectorToString(numbers) << endl;
    cout << "Enter a value you wish to find" << endl;
    int value_to_find;
    cin >> value_to_find;
    cout << "Index of such value: " << findValueIndex(numbers, value_to_find) << endl;
    int A[] = {0, 1, 1, 0};
    int B[] = {1, 1, 1, 1};
    int *C = binarySum(A, B);
    cout << arrayToString(A, findSizeArray(A)) << " + " << arrayToString(B, findSizeArray(B)) << " = " << arrayToString(C, findSizeArray(A)+1) << endl;
    return 0;
}