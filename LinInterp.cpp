//
// Created by stef on 16.04.20.
//

#ifndef PROJECT_LININTERP_CPP
#define PROJECT_LININTERP_CPP

#include <vector>

template <class T>
class LinInterp {
public:
    void sort();
    T val(float timestamp);
private:
    std::vector<int> timestamps;
    std::vector<T> values;
};

template<class T>
void LinInterp<T>::sort() {
    for(int i = 1; i < timestamps.size(); ++i) {
        bool swapHappened = false;
        for(int j = 0; j < timestamps.size()-i; ++j) {
            if(timestamps[j] > timestamps[j+1]) {
                int tempTimestamp = timestamps[j];
                timestamps[j] = timestamps[j+1];
                timestamps[j+1]= tempTimestamp;
                T tempValue = values[j];
                values[j] = values[j+1];
                values[j+1] = tempValue;
                swapHappened = true;
            }
        }
        if(!swapHappened)
            break;
    }
}

template<class T>
T LinInterp<T>::val(float timestamp) {
    sort();
    int I = 0;
    for(int i = 0; i < timestamps.size(); ++i) {
        if(timestamps[i] == timestamp) {
            return values[i];
        }
        if(timestamps[i] > timestamp)
            break;
        ++I;
    }
    if(I == timestamps.size()) {
        return values[I-1];
    }
    int A = timestamps[I-1];
    int B = timestamps[I];
    int X = values[I-1];
    int Y = values[I];
    float factor = (timestamp-X) / (float)(Y-X);
    return X + (factor * (Y-X));
}


#endif //PROJECT_LININTERP_CPP
