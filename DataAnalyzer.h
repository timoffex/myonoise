//
//  DataAnalyzer.h
//  hello-myo
//
//  Created by Tima Peshin on 4/4/15.
//  Copyright (c) 2015 Thalmic Labs. All rights reserved.
//

#ifndef hello_myo_DataAnalyzer_h
#define hello_myo_DataAnalyzer_h

#include <stdint.h>
#include <vector>
#include <iostream>


template <class T>
class DataAnalyzer {
public:
    // TESTED - WORKS
    DataAnalyzer(int history_size, uint64_t microsecond_delay);
    
    // TESTED - WORKS
    void append_data(T data, uint64_t timestamp);
    
    
    
    void DEBUG_PRINT() {
        if (history_lst_index > history_fst_index) {
            for (int i = history_fst_index; i <= history_lst_index; i++)
                std::cout << i << ", " << history[i] << std::endl;
        } else {
            for (int i = 0; i < history_size; i++)
                std::cout   << (i+history_fst_index)%history_size
                            << ", "
                            << history[(history_fst_index+i)%history_size]
                            << std::endl;
        }
    }
private:
    std::vector<T> history; // time difference between each element is microsecond_delay, guaranteed
    
    int history_lst_index; // last index
    int history_fst_index; // first index
    int history_size; // num elements in history
    
    uint64_t history_fst_timestamp; // oldest timestamp
    uint64_t history_nxt_timestamp; // minimum next timestamp
    
    uint64_t microsecond_delay; // time difference between each element
};

template <class T>
DataAnalyzer<T>::DataAnalyzer(int hsize, uint64_t mdelay) {
    history_size = hsize;
    microsecond_delay = mdelay;
    
    history = std::vector<T>(history_size);
    
    history_fst_index = 0;
    history_lst_index = -1;
}

template <class T>
void DataAnalyzer<T>::append_data(T data, uint64_t timestamp) {
    if (history_lst_index == -1) {
        history_lst_index = 0;
        history[0] = data;
        
        history_fst_timestamp = timestamp;
        history_nxt_timestamp = timestamp+microsecond_delay;
    } else if (timestamp >= history_nxt_timestamp) {
        int num_copy_indices = static_cast<int>((timestamp - history_nxt_timestamp)/microsecond_delay);
        
        // copy data for time gap
        int next_index = history_lst_index;
        for (int i = 1; i <= num_copy_indices; i++) {
            next_index = (history_lst_index+i)%(history_size);
            history[next_index] = history[history_lst_index];
            
            if (next_index == history_fst_index) {
                history_fst_index = (next_index+1)%(history_size);
                history_fst_timestamp += microsecond_delay;
            }
        }
        
        // set data
        next_index = (next_index+1)%(history_size);
        if (next_index == history_fst_index) {
            history_fst_index = (next_index+1)%(history_size);
            history_fst_timestamp += microsecond_delay;
        }
        history[next_index] = data;
        
        
        // set first and last index
        history_lst_index = next_index;
        if (history_lst_index == history_fst_index) {
            history_fst_index = (history_lst_index+1)%(history_size);
            history_fst_timestamp += microsecond_delay;
        }
        
        // set next timestamp
        history_nxt_timestamp += (num_copy_indices + 1) * microsecond_delay;
    }
}

#endif
