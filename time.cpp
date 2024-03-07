#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "copyClass/TreeCopy"

using namespace std;

size_t lcg()
{
    static size_t x = 0;
    x = (1021*x + 24631) % 116640;
    return x;
}

using namespace Tree;

double calculateAverageFillTimeVec(int numValues, int numAttempts) 
{
    vector<int> vec;

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalTime = 0;

    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();

        for (int j = 0; j < numValues; j++) {
            vec.push_back(lcg());
        }

        end = chrono::high_resolution_clock::now();

        totalTime += chrono::duration_cast<chrono::microseconds>(end - start).count();

        vec.clear();
    }

    return totalTime / numAttempts;
}

double calculateAverageSearchTimeVec(int numValues, int numAttempts) 
{

    vector<int> vec;

    for (int i = 0; i < numValues; i++) {
        vec.push_back(lcg());
    }

    int* searchValues = new int[numAttempts];
    for (int i = 0; i < numAttempts; i++) {
        searchValues[i] = lcg();
    }

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalTime = 0;

    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();

        std::find(vec.begin(), vec.end(), searchValues[i]);
        

        end = chrono::high_resolution_clock::now();

        totalTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    delete[] searchValues;

    return totalTime / numAttempts;
}

double calculateAverageAddTimeVec(int numValues, int numAttempts) {
    
    vector<int> vec(numValues);
    for (int i = 0; i < numValues; i++) {
        vec[i] = lcg();
    }

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalAddTime = 0;
    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();
        vec.push_back(lcg());
        end = chrono::high_resolution_clock::now();
        totalAddTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return totalAddTime / numAttempts;
}

double calculateAverageRemoveTimeVec(int numValues, int numAttempts) {
    

    chrono::time_point<chrono::high_resolution_clock> start, end;
    
    vector<int> vec(numValues);
    for (int i = 0; i < numValues; i++) {
        vec[i] = lcg();
    }

    double totalRemoveTime = 0;
    int si = 0;
    int numAtt = 0;
    for (int i = 0; i < numAttempts; i++) 
    {
        si = vec.size();
        if(si == 0)
        {
            break;
        }
        
        start = chrono::high_resolution_clock::now();
        vec.erase(vec.begin() +  lcg() % si);
        end = chrono::high_resolution_clock::now();
        ++numAtt;
        totalRemoveTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return totalRemoveTime / numAtt;
}

double calculateAverageFillTimeTree(int numValues, int numAttempts) 
{
    Binary<int> vec;

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalTime = 0;

    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();

        for (int j = 0; j < numValues; j++) {
            vec.add(lcg());
        }

        end = chrono::high_resolution_clock::now();

        totalTime += chrono::duration_cast<chrono::microseconds>(end - start).count();

        vec.~Binary();
    }

    return totalTime / numAttempts;
}

double calculateAverageSearchTimeTree(int numValues, int numAttempts) 
{

    Binary<int> vec;

    for (int i = 0; i < numValues; i++) {
        vec.add(lcg());
    }

    int* searchValues = new int[numAttempts];
    for (int i = 0; i < numAttempts; i++) {
        searchValues[i] = lcg();
    }

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalTime = 0;

    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();

        vec.in(searchValues[i]);
        

        end = chrono::high_resolution_clock::now();

        totalTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    delete[] searchValues;

    return totalTime / numAttempts;
}

double calculateAverageAddTimeTree(int numValues, int numAttempts) {
    
    
    Binary<int> vec;
    
    for (int i = 0; i < numValues; i++) {
        vec.add( lcg());
    }

    chrono::time_point<chrono::high_resolution_clock> start, end;
    double totalAddTime = 0;
    for (int i = 0; i < numAttempts; i++) {
        start = chrono::high_resolution_clock::now();
        vec.add(lcg());
        end = chrono::high_resolution_clock::now();
        totalAddTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return totalAddTime / numAttempts;
}

double calculateAverageRemoveTimeTree(int numValues, int numAttempts) {
    

    chrono::time_point<chrono::high_resolution_clock> start, end;
    
    Binary<int> vec;
    for (int i = 0; i < numValues; i++) {
        vec.add(lcg());
    }

    double totalRemoveTime = 0;
    int si = 0;
    int numAtt = 0;
    for (int i = 0; i < numAttempts; i++) 
    {
        
        start = chrono::high_resolution_clock::now();
        vec.discard(lcg());
        end = chrono::high_resolution_clock::now();
        ++numAtt;
        totalRemoveTime += chrono::duration_cast<chrono::microseconds>(end - start).count();
    }

    return totalRemoveTime / numAtt;
}



int main() {
    int numValues = 100000, numAttempts = 100;


    cout << "Средние времена для numValues = " << numValues << " и numAttempts = " << numAttempts;
    double averageTime = calculateAverageFillTimeVec(numValues, numAttempts);
    cout << "\n\nСреднее время заполнения Vec: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageSearchTimeVec(numValues, numAttempts);
    cout << "\n\nСреднее время поиска Vec: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageAddTimeVec(numValues, numAttempts);
    cout << "\n\nСреднее время добавления Vec: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageRemoveTimeVec(numValues, numAttempts);
    cout << "\n\nСреднее время удаления Vec: " << averageTime << " microseconds" << endl;

    averageTime = calculateAverageFillTimeTree(numValues, numAttempts);
    cout << "\n\n\n\n\nСреднее время заполнения Tree: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageSearchTimeTree(numValues, numAttempts);
    cout << "\n\nСреднее время поиска Tree: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageAddTimeTree(numValues, numAttempts);
    cout << "\n\nСреднее время добавления Tree: " << averageTime << " microseconds" << endl;
    averageTime = calculateAverageRemoveTimeTree(numValues, numAttempts);
    cout << "\n\nСреднее время удаления Tree: " << averageTime << " microseconds" << endl;

    return 0;
}
