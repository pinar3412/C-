#pragma once

#include "Solution.h"
#include<tuple>
#include <numeric>
#include "Firstfitdecrease.h"
#include <random>
#include <ctime>
#include <algorithm>

class Genetic
{
private:

	int populationsize;//n
	int parentsize;
	vector<int> weights;

	int capacity;/// priorirtyQuee<tupple-3>: doluluk oranlarý,parentýn k,m olduðu,kutu nosu ***;
	vector<Solution>sol;
	vector<Solution>parentsol;
	vector<Solution>kparentsol;
	vector<tuple<float, int, int > > maxPriorityQ;
public:
	
    Genetic(vector<int>& mainvec) :
        populationsize(50),
        parentsize(20),
		weights(mainvec),
		capacity(mainvec[0])
	
    {};

	Genetic() = default;

	

	vector<Solution> parentSelection( ) {
				
	
		std::vector<int> ivec(populationsize);
		std::iota(ivec.begin(), ivec.end(), 0); // ivec will become: [0..50]

		random_shuffle(ivec.begin(), ivec.end());

		for (int i = 0;i < (2 * parentsize);i++) {
		
			parentsol.push_back(sol[ivec[i]]);
		}

		for (int i = 0;i < (2 * parentsize);i+=2) {
			
			if (parentsol[i].getObj() <= parentsol[i+1].getObj()) 
				kparentsol.push_back(parentsol[i]);
			
			else
				kparentsol.push_back(parentsol[i + 1]);
									
		}				
		return kparentsol;
	}

	
	static bool sortbythh(const tuple<float, int, int >& a,
		const tuple<float, int, int>& b)
	{
		return (get<0>(a) > get<0>(b));
	}

	
	void createTriple(bool& sortedd) {
		float counter;
		for (int i = 0;i < parentsize;i++) {
			for (int bin = 0;bin < kparentsol[i].getObj(); bin++) {

				counter = kparentsol[i].getefficiency();
				maxPriorityQ.push_back(make_tuple(counter, i, bin));
				
			}
		}

		if(sortedd==false)
			sort(maxPriorityQ.begin(), maxPriorityQ.end(), sortbythh);
		else
			random_shuffle(maxPriorityQ.begin(), maxPriorityQ.end());
				
	}

	void crossover(Solution& s3,Firstfitdecrease& ffd,bool random) {
		int bin = 0;
		parentSelection();
		createTriple(random);

		vector<int>unassignedvec;

			
		for (int i = 0; i < maxPriorityQ.size();i++) {

							
		int counter = 0;
		for (int item: kparentsol[get<1>(maxPriorityQ[i])].getBins(get<2>(maxPriorityQ[i]))) {
					
			if (s3.getAssignment()[item] > -1) {
				counter++;
				break;
			}
						
		}
									
		if (counter == 0&& kparentsol[get<1>(maxPriorityQ[i])].getBins(get<2>(maxPriorityQ[i])).size()>0) {
										
			for (int item : kparentsol[get<1>(maxPriorityQ[i])].getBins(get<2>(maxPriorityQ[i]))) {
							 
												
				s3.assignItem(item, bin);
			}
			bin++;
		}
			
		}
																				

		for (int i = 0; i < weights.size() - 1;i++) {
			if (s3.getAssignment()[i] == -1)
				unassignedvec.push_back(i);

		}
		if (unassignedvec.size() > 0) 
			ffd.complete_Sol(weights, capacity, true, s3, unassignedvec);



		cout << "before local search  " << s3.getObj();
		cout << "  eff: " << s3.getefficiency()<<endl;

		ffd.local_search(s3,4 , true, weights);
		cout << "after local search  " << s3.getObj();
		cout << "  eff :" << s3.getefficiency();
		int k = theswitch();
		sol[k] =s3;
		cout << " after swtiching " << sol[k].getefficiency() << endl;
		
		
	}

	int theswitch() {
		double min = 99999999;
		int finall = 0;

		
		for (int i = 0;i < populationsize;i++) {

			if (sol[i].getefficiency() < min) {
				min = sol[i].getefficiency();
				finall = i;
			}
		}


	
		cout << "the worst eff bin no: " << finall;
		cout << " " << sol[finall].getefficiency() << endl;
		return finall;
	}
	void mutation(Firstfitdecrease& ffd) {
		mt19937 rng(time(0));

		// Generate a random number between 1 and 50
		uniform_int_distribution<int> dist(1, 49);
		int r = dist(rng);
		ffd.local_search(sol[r], 4, false, weights);
		ffd.local_search(sol[r], 4, true, weights);

	}


	int getparent() { return parentsize; }
	int getpopulation() { return populationsize; }
	void getsol(Solution& solution) {  sol.push_back(solution); }
	vector < tuple<float, int, int >> getQueue() { return maxPriorityQ; }
	vector<Solution> getkparent() {	return kparentsol;}
	
};

