// QuicksortTester.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <algorithm>    
#include <array>        
#include <random>
#include <stdlib.h>
#include <chrono>
using namespace std::chrono;
using namespace std;


class QS {
public:
    //default constructor

    void QSBasic(int arr[], int low, int high, int& comp, int& swaps) {


        if (low < high) {
            int p = partition(arr, low, high,comp,swaps);
            QSBasic(arr, low, p - 1, comp, swaps);
            QSBasic(arr, p + 1, high, comp, swaps);
        }
    }
    int partition(int arr[], int low, int high, int& comp, int& swaps) {
        int pivot = arr[high];    // pivot
        int i = (low - 1);  // Index of smaller element

        for (int j = low; j <= high - 1; j++) {
            if (arr[j] <= pivot) {
                comp++;
                i++;
                swap(&arr[i], &arr[j]);
                swaps++;
            }
        }
        swap(&arr[i + 1], &arr[high]);
        swaps++;
        return (i + 1);
    }
    void swap(int* a, int* b) {
        int t = *a;
        *a = *b;
        *b = t;
    }


    void QS3way(int arr[], int low, int high, int& comp, int& swaps) {
     
        if (low < high) {
            int lt = low;
            int gt = high;
            int pivot = arr[low];
            int i = low + 1;
            while (i <= gt) {
                int c = arr[i] - pivot;
                if (c < 0) {
                    comp++;
                    swap(&arr[lt++], &arr[i++]);
                    swaps++;
                }
                else if (c > 0) {
                    comp++;
                    swap(&arr[i], &arr[gt--]);
                    swaps++;
                }
                else {
                    comp++;
                    i++;
                }
            }//end while

            QS3way(arr, low, lt - 1, comp, swaps);
            QS3way(arr, gt + 1, high, comp, swaps);
        }//end if
    }

    void QS2Key(int* arr, int low, int high, int &comp,int &swaps) {
   
        if (low < high) {

            if (arr[high]<arr[low]) {
                swap(&arr[low], &arr[high]);
                swaps++;
            }


            int lt = low + 1;
            int gt = high - 1;
            int i = low + 1;
            while (i <= gt) {
                //comp++;
                int ai = arr[i];
                if (ai < arr[low]) {
                    comp++;
                    swap(&arr[lt++], &arr[i++]);
                    swaps++;
                }
                else if (arr[high] < ai) {
                    comp++;
                    swap(&arr[i], &arr[gt--]);
                    swaps++;
                }
                else {
                    comp++;
                    i++;
                }
            }//end while

            swap(&arr[low], &arr[--lt]);
            swaps++;
            swap(&arr[high], &arr[++gt]);
            swaps++;

            QS2Key(arr, low, lt - 1, comp, swaps);
            if (arr[lt] < arr[gt]) {
                comp++;
                QS2Key(arr, lt + 1, gt - 1, comp, swaps);
            }
            QS2Key(arr, gt + 1, high, comp, swaps);

        }//end if

    }

    void randomize(int arr[], int n){
        unsigned seed = 0;
        shuffle(arr, arr + n, default_random_engine(seed));
    }
    void sorterRand(int arr[], int size) {
        int swapavg=0;
        int compavg=0;
        int timeavg=0;

        double a = 0;
        double b = 0;
        double x = 0;
        

        int comp=0;
        int swaps=0;
        randomize(arr, size);
        cout << "Basic QS" << endl;
        auto start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        timeavg = duration.count();
        compavg = comp;
        swapavg = swaps;

        comp = 0;
        swaps = 0;
        randomize(arr, size);
        //cout << "Basic QS" << endl;
        start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        randomize(arr, size);
        //cout << "Basic QS" << endl;
         start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
         stop = high_resolution_clock::now();
         duration = duration_cast<microseconds>(stop - start);

        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);


        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp/duration.count() << " :: " << swaps/duration.count() << endl;
        x = timeavg;
        timeavg = 0;
        compavg = 0;
        swapavg = 0;

       
        comp = 0;
        swaps = 0;
        randomize(arr, size);
        cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = duration.count();
        compavg = comp;
        swapavg = swaps;

        comp = 0;
        swaps = 0;
        randomize(arr, size);
        //cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        randomize(arr, size);
       // cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);


        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp / duration.count() << " :: " << swaps / duration.count() << endl;
        a = timeavg;
        timeavg = 0;
        compavg = 0;
        swapavg = 0;
       
        comp = 0;
        swaps = 0;
        randomize(arr, size);
        cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        randomize(arr, size);
        //cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        randomize(arr, size);
        //cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);
        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp / duration.count() << " :: " << swaps / duration.count() << endl;
        b = timeavg;
        

        cout << endl << "percentages: " << endl;
        cout << "3way/basic: " <<   a/x  << endl;
        cout << "2key/basic: " << b/x << endl;
        
    }
    void sorterNon(int arr[], int size) {
        int comp = 0;
        int swaps = 0;
        int swapavg=0;
        int compavg=0;
        int timeavg=0;
        double a = 0;
        double b = 0;
        double x = 0;
        
       
        cout << "Basic QS" << endl;
        auto start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
         start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
         stop = high_resolution_clock::now();
         duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
         start = high_resolution_clock::now();
        QSBasic(arr, 0, size - 1, comp, swaps);
         stop = high_resolution_clock::now();
         duration = duration_cast<microseconds>(stop - start);
         timeavg = (timeavg + duration.count());
         compavg = (compavg + comp);
         swapavg = (swapavg + swaps);
        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp / duration.count() << " :: " << swaps / duration.count() << endl;
        x = timeavg;

        timeavg = 0;
        compavg = 0;
        swapavg = 0;
       
        
        comp = 0;
        swaps = 0;
        cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        //cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        //cout << "3 way QS" << endl;
        start = high_resolution_clock::now();
        QS3way(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp / duration.count() << " :: " << swaps / duration.count() << endl;
        a = timeavg;
        timeavg = 0;
        compavg = 0;
        swapavg = 0;

        comp = 0;
        swaps = 0;
        cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        //cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);

        comp = 0;
        swaps = 0;
        //cout << "2 key QS" << endl;
        start = high_resolution_clock::now();
        QS2Key(arr, 0, size - 1, comp, swaps);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        timeavg = (timeavg + duration.count());
        compavg = (compavg + comp);
        swapavg = (swapavg + swaps);


        cout << duration.count() << endl;
        cout << comp << " :: " << swaps << endl;
        cout << "avgs: " << timeavg / 3 << " :: " << compavg / 3 << " :: " << swapavg / 3 << endl;
        cout << comp / duration.count() << " :: " << swaps / duration.count() << endl;
        b = timeavg;


        cout << endl << "percentages: " << endl;
        cout << "3way/basic: " << a / x << endl;
        cout << "2key/basic: " << b / x << endl;

    }
   
};


int main()
{

    QS qs;
    vector<int> vec;

    

    cout << "10^3" << endl;
    for (int i = 0; i < 1000; i++) {
        vec.push_back(i);
    }
    int* arrthree = new int[1000];
    copy(vec.begin(), vec.end(), arrthree);
    vec.clear();

    qs.sorterRand(arrthree, 1000);
    delete[] arrthree;
    cout << endl << endl;




    //10^5 and in order
    cout << "10^5" << endl;
    for (int i = 0; i < 100000; i++) {
        vec.push_back(i);
    }
    int*  arrFive = new int[100000];
    copy(vec.begin(), vec.end(), arrFive);
    vec.clear();

    qs.sorterRand(arrFive, 100000);
    delete[] arrFive;
    cout << endl << endl;
    //end 10^5 and in order
    
    //fill 10^6
    cout << "10^6" << endl;
    for (int i = 0; i < 1000000; i++) {
        vec.push_back(i);
    }
    int* arrSix = new int[1000000];
    copy(vec.begin(), vec.end(), arrSix);
    vec.clear();

    qs.sorterRand(arrSix, 1000000);
    delete[] arrSix;
    cout << endl << endl;
    //end fill 10^6

    //fill 10^7
    cout << "10^7" << endl;
    for (int i = 0; i < 10000000; i++) {
        vec.push_back(i);
    }
    int* arrSeven = new int[10000000];
    copy(vec.begin(), vec.end(), arrSeven);
    vec.clear();

    qs.sorterRand(arrSeven, 10000000);
    delete[] arrSeven;
    cout << endl << endl;
    //end fill 10^7

    //fill duplicate
    cout << "duplicate" << endl;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(rand()%4);
    }
    int* arrDup = new int[10000];
    copy(vec.begin(), vec.end(), arrDup);
    vec.clear();

    qs.sorterRand(arrDup, 10000);
    delete[] arrDup;
    cout << endl << endl;
    //end fill duplicate


    //fill binary
    cout << "binary" << endl;
    for (int i = 0; i < 1000; i++) {
        vec.push_back(rand() % 2);
    }
    int* arrBinary = new int[1000];
    copy(vec.begin(), vec.end(), arrBinary);
    vec.clear();

    qs.sorterRand(arrBinary, 1000);
    delete[] arrBinary;
    cout << endl << endl;
    //end fill binary
    /*
    //fill reverse
    cout << "reverse" << endl;
    for (int i = 0; i < 10000; i++) {
        vec.push_back(10000-i);
    }
    int* arrRev = new int[10000];
    copy(vec.begin(), vec.end(), arrRev);
    vec.clear();

    qs.sorterNon(arrRev, 10000);
    delete[] arrRev;
    cout << endl << endl;
    //end fill reverse
    */



    
    
    
}


