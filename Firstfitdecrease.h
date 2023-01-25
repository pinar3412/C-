#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include<tuple>
#include "Solution.h"
#include "Double.h"

class Firstfitdecrease
{

public:
      
   static bool sortbysec(const pair<int, int>& a,
        const pair<int, int>& b)
    {
        return (a.second > b.second);
    }

    static bool sortbyth(const tuple<int, int, int, int, int, int, int, int >& a,
        const tuple<int, int, int, int, int, int, int, int >& b)
    {
        return (get<0>(a) > get<0>(b));
    }



    vector<Double>	make_double_vec(const vector<int>& items, const vector<int>& weights) {

        vector<Double>combine;
        for (int i = 0; i < items.size(); i++) {

            combine.push_back(Double(items[i], -1, weights[items[i] + 1]));
            for (int j = i + 1; j < items.size(); j++) {

                if (i != j) {
                    combine.push_back(Double(items[i], items[j], weights[items[j] + 1] + weights[items[i] + 1]));

                }
            }
        }
        return combine;
    }




    vector<int> converter(const unordered_set<int>& bins) {

        vector<int>converted_bins;
        converted_bins.insert(converted_bins.end(), bins.begin(), bins.end());

        return converted_bins;
    }


    void complete_Sol(vector<int>& mainvec, int capacity, bool sorted, Solution& solution, const vector<int>& freeItems) {

        int n = freeItems.size();

        auto weightPair = solution.getweightpair(freeItems);


        if (sorted == true) {
            sort(weightPair.begin(), weightPair.end(), sortbysec);
        }



        for (int i = 0;i < n; i++) {

            int p = -1;
            for (int j = 0; j < mainvec.size() - 1; j++) {

                if ((solution.getAssignment()[weightPair[i].first] > -1)) {
                    break;
                }

                if (solution.get_current_capacity(j) == capacity) {
                    if (p == -1)
                        p = j;
                    continue;
                }


                if (solution.get_current_capacity(j) >= weightPair[i].second) {
                    solution.assignItem(weightPair[i].first, j);
                    break;
                }

            }

            if (solution.getAssignment()[weightPair[i].first] == -1)
                solution.assignItem(weightPair[i].first, p);


        }
    }



    void local_search(Solution& originalsolution, int n, bool random, vector<int> mainVec) {

        Solution   solution(originalsolution);
        vector<int> freeItems;

        if (random == false) {

            auto sortedBins = solution.getBinsSorted();

            if (solution.getObj() < n)
                n = solution.getObj();

            for (int i = 0; i < n; i++) {

                for (int item : solution.getBins(sortedBins[i].second))
                    freeItems.push_back(item);
            }
        }

        else {

            vector<int> randombins(originalsolution.getObj() - 1);
            for (int i = 0; i < originalsolution.getObj() - 1; i++)
                randombins[i] = i;

            random_shuffle(randombins.begin(), randombins.end());

            if (solution.getObj() < n)
                n = solution.getObj();

            for (int i = 0;i < n; i++) {

                for (int item : solution.getBins(randombins[i]))
                    freeItems.push_back(item);
            }

        }

        for (int item : freeItems) {

            solution.removeItem(item);

        }
        vector<tuple<int, int, int, int, int, int, int, int > > v;
        int counter = 0;
        vector<int> removeItem_list;


        vector<Double> free_pairs = make_double_vec(freeItems, mainVec);
        vector<Double> bins_pairs;
        for (int bins = 0, k = 0; bins < solution.getAllof_Bins().size(); bins++) {
            if (solution.getBins(bins).size() != 0) {
                bins_pairs = make_double_vec(converter(solution.getBins(bins)), mainVec);

                for (int i = 0; i < free_pairs.size(); i++) {
                    for (int bin = 0; bin < bins_pairs.size(); bin++) {
                        if (mainVec[0] - free_pairs[i].getTotalWeight() >= 0) {
                            if (free_pairs[i].getTotalWeight() - bins_pairs[bin].getTotalWeight() > 0 && free_pairs[i].getTotalWeight() - bins_pairs[bin].getTotalWeight() <= solution.get_current_capacity(bins)) {  // (free_pairs[i].getTotalWeight() - bins_pairs[bin].getTotalWeight())> counter ***

                                counter = free_pairs[i].getTotalWeight() - bins_pairs[bin].getTotalWeight();

                                v.push_back(make_tuple(counter, free_pairs[i].getItem1(), free_pairs[i].getItem2(), bins_pairs[bin].getItem1(), bins_pairs[bin].getItem2(), bins, bins_pairs[bin].getTotalWeight(), i));// binsde gerekecek

                                sort(v.begin(), v.end(), sortbyth);



                            }
                        }

                    }
                }

            }
        }


        for (int i = 0; i < v.size(); i++) {

            if (get<0>(v[i]) > (solution.get_current_capacity(get<5>(v[i]))))
                continue;


            if (solution.getAssignment()[get<1>(v[i])] == -1 &&
                ((get<2>(v[i]) != -1 && solution.getAssignment()[get<2>(v[i])] == -1) || (get<2>(v[i]) == -1)) &&
                (solution.getAssignment()[get<3>(v[i])] != -1) &&
                ((get<4>(v[i]) != -1 && solution.getAssignment()[get<4>(v[i])] != -1) || (get<4>(v[i]) == -1))) {

                solution.removeItem(get<3>(v[i]));
                if ((get<4>(v[i]) != -1))
                    solution.removeItem(get<4>(v[i]));

                solution.assignItem(get<1>(v[i]), get<5>(v[i]));

                if (get<2>(v[i]) != -1)
                    solution.assignItem(get<2>(v[i]), get<5>(v[i]));

            }

        }

        freeItems.clear();

        for (int i = 0; i < solution.getAssignment().size(); i++)
            if (solution.getAssignment()[i] == -1)
                freeItems.push_back(i);


        /******************************************/
        complete_Sol(mainVec, mainVec[0], true, solution, freeItems);

        cout << "current " << originalsolution.getObj() << endl;
        cout << "testing " << solution.getObj() << endl;

        cout << "efficiency " << solution.getefficiency() << endl;



        if (solution.getefficiency() > originalsolution.getefficiency()) 
            originalsolution = solution;
        
    }




};

