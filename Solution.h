#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;


class Solution {

private:

    vector<int> weightvec;
    vector<unordered_set<int>> bins;
    int obj_function;//kullan�lan kutu say�s�
    long exe_time;
    vector<int> assignment; //i. eleman�nn atand��� kutuyu verecek
    std::vector<int> Current_capacityofBins;
    int capacity_bins;
    float efficiency;
    float bestefficiency;
 

public:

    
    ~Solution() = default;
    Solution(const Solution& solution)  = default;
    Solution(Solution&&) = default;
    Solution& operator= (Solution&&) = default;
	Solution& operator= (Solution&) = default;

  

    Solution(int capacity, vector<int>& w_vec) : 
        capacity_bins(capacity), 
        weightvec(w_vec),
        Current_capacityofBins(w_vec.size()-1 ,capacity),
        bins(),
        obj_function(0),
        exe_time(0),
        efficiency(0),
        bestefficiency(0)
      
    { 
       
        bins.resize(weightvec.size() - 1);
        assignment = vector<int>((weightvec.size() - 1), -1);
        for (int i = 0;i < weightvec.size() - 1;i++) {
            bins[i] = unordered_set<int>();
        }
    
    }
    Solution() = default;


    void assignItem(int productnumber, int bin) {

      
        if (Current_capacityofBins[bin] == capacity_bins) {
            obj_function += 1;
        }
             
      
        assignment[productnumber] = bin;
        bins[bin].insert(productnumber);
        Current_capacityofBins[bin] -= weightvec[productnumber + 1];

      //  cout << productnumber << "   " << "bin " << bin << endl;


    }


    
    void removeItem(int productnumber) { 
    
        int bin = assignment[productnumber];
       

        assignment[productnumber] = -1;
        bins[bin].erase(productnumber);
        Current_capacityofBins[bin] += weightvec[productnumber+1];

 
        if (Current_capacityofBins[bin] ==capacity_bins) {
            obj_function -= 1;
        }
         
    }

  
    int get_current_capacity(int bin) {
        return Current_capacityofBins[bin];
    }
 
    int getObj() { return obj_function; }
    

    int getcapacity() { return capacity_bins; }

    vector<int> getAssignment() { return assignment; }

    unordered_set<int> getBins(int bin) {   return bins[bin]; }


    vector<unordered_set<int>> getAllof_Bins() { return bins; }

    long getExeTime() { return exe_time; }

   float getefficiency() {
        unordered_set<int>::iterator i;
        efficiency = 0;
        for(int binn=0; binn<bins.size();binn++){
     
            if (Current_capacityofBins[binn]==capacity_bins)
                continue;
            float sq = 0;
            for (i = bins[binn].begin(); i != bins[binn].end();i++) {
             

                 sq += weightvec[*i + 1];
               
            }
            efficiency += (sq * sq) / capacity_bins;

            if (efficiency > bestefficiency)
                bestefficiency = efficiency;
       }
        return efficiency/obj_function;
    }

   float getbest() {
      
       return bestefficiency / obj_function;
   }

    vector<pair<int, int>> getBinsSorted() {
        vector<pair<int, int>> vec = vector<pair<int, int>>();

        for (int i = 0; i < obj_function; i++)
            vec.push_back(make_pair(capacity_bins - get_current_capacity(i), i));
        
        sort(vec.begin(), vec.end());        

        return vec;
    }

    vector<pair<int, int>> getweightpair(const vector<int>&Items) {
        vector<pair<int, int>> vec = vector<pair<int, int>>();
        
        for (int i = 0; i < Items.size(); i++)
            vec.push_back(make_pair(Items[i], weightvec[Items[i]+1]));

       return vec;
    }

};

