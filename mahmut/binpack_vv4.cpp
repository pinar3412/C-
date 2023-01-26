

#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Solution.h"
#include "Double.h"
#include<tuple>
#include "Genetic.h"
#include <random>
#include "Firstfitdecrease.h"
#include <string>
#include <iostream>
#include <cstdlib> 
using namespace std;
#include <iostream>
#include <Windows.h>
#include "dirent.h"
//
//void readFromFile(const string& f, vector<int>& vec)
//{
//    string line;
//  
//    ifstream myfile(f.c_str());
//  
//
//    if (!myfile)
//    {
//        std::cout << "Cannot open the File " << endl;
//        exit(1);
//    }
//    if (myfile.is_open())
//    {
//        while (std::getline(myfile, line))
//        {
//            int a;
//            std::istringstream ss(line);
//
//            while (ss >> a)
//            {
//                vec.push_back(a);       //add the word to the temporary vector 
//            }
//        }
//        myfile.close();
//    }
//
//}

void readFromFile(const string& f, vector<int>& vec)
{
    string line;
      string filename = "testing/" + f ;
    
      cout << "fil " << filename;
    ifstream myfile(filename);
    /*ifstream myfile(f.c_str());*/

    if (!myfile)
    {
        std::cout << "Cannot open the File " << endl;
        exit(1);
    }
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            int a;
            std::istringstream ss(line);
            cout << line << endl;

            while (ss >> a)
            {
                vec.push_back(a);       //add the word to the temporary vector 
            }
        }
        myfile.close();
    }

}

//void readFromFile(const std::vector<std::string>& fileNames, vector<int>& vec) {
//    for (const auto& fileName : fileNames) {
//        std::ifstream file(fileName);
//        if (file.is_open()) {
//            std::string line;
//            while (std::getline(file, line)) {
//                std::cout << line << '\n';
//            }
//            file.close();
//        }
//        else {
//            std::cout << "Unable to open file: " << fileName << '\n';
//        }
//    }
//}

void writeFromFile(const string& filename, int objfunc, float efficiency) {
    ofstream fout;
    fout.open("solution.txt");
   
    fout << filename <<"  "<<"bin:"<<objfunc<<"E:"<<efficiency << endl;
    fout.close();
 
}
double getRandomDouble() {
    // Create a uniform random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0, 1);
        
    return dis(gen);
}


int main(int, char** argv)
{
    vector<int> unassignedvec;
    int capacity = 0;
    bool sorted = false;
    int n = 0;
    bool rand = true;

    vector<int>mainvec;
       

  /*  string filename;
    cin >> filename;*/


    //std::vector<std::string> file_list;

    //DIR* dir = opendir(".");
    //struct dirent* entry;
    //while ((entry = readdir(dir)) != NULL)
    //{
    //    // Check if the entry is a regular file
    //    if (entry->d_type == DT_REG)
    //    {
    //        file_list.push_back(entry->d_name);
    //    }
    //}
    //closedir(dir);
    //


    /*******/
    int c = -1;
    vector<string> dummy;
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir("C:/Users/PINAR/source/repos/mahmut/testing")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL) {
            printf("%s\n", ent->d_name);

            dummy.push_back(ent->d_name);
            if(c>1)
                 /*readFromFile(ent->d_name, mainvec);
         */
           c++;
        }
        closedir(dir);
    }
    else {
        /* could not open directory */
        perror("");
        return EXIT_FAILURE;
    }

    /*for (int i = 2; i < dummy.size();i++) {
        cout << "pay attention " << dummy[i] << endl;
        readFromFile(dummy, mainvec);
        break;
    }
        */
    
  ///  readFromFile("C:/Users/PINAR/source/repos/mahmut/testing", mainvec);
    cout << dummy[13] << endl;
    readFromFile( dummy[13], mainvec);
    vector<int>::iterator it;
    it = mainvec.begin();
    mainvec.erase(it);

    capacity = mainvec[0]; // add the first element as a capacity parameter of bins
          

    Solution s(capacity, mainvec);
    Firstfitdecrease ffd;


    vector<int> freeItems = vector<int>(mainvec.size() - 1);
    for (int i = 0; i < mainvec.size() - 1; i++)
        freeItems[i] = i;

        
    /*   for (int i = 0; i < mainvec.size() - 1; i++) {
        s.assignItem(freeItems[i], i);
    }
    */
        
    ffd.complete_Sol(mainvec, capacity, sorted, s, freeItems);
     

    for (int i = 0; i < 5; i++) {
        ffd.local_search(s, 4, rand, mainvec);
      //  local_search(s, 4, false, mainvec);
    }
        
   cout << "Final state of capacty" << s.getObj() << endl;
   cout<< s.getefficiency();
  
  /**********************/
    

   Genetic g(mainvec);

 
   for (int i = 0;i < g.getpopulation();i++) {
       Solution s2(capacity, mainvec);
 
        if (i == 0)
           sorted = true;
        else
           sorted = false;

        ffd.complete_Sol(mainvec, capacity, sorted, s2, freeItems);
        ffd.local_search(s2, 4, rand, mainvec);
        g.getsol(s2);
     
        s2 = Solution();
         
   }

    Solution s3(capacity, mainvec);

    for (int i = 0; i < 20; i++) {
        g.crossover(s3, ffd, false);
    }
     
      cout << s3.getObj() << "efficiency " << s3.getefficiency() << endl;
      cout << s3.getbest()<< "   " << s.getbest()<<endl;
      cout << "*****"<< getRandomDouble();
  

  /*if (getRandomDouble() >= 0.9)
      g.mutation(ffd);*/
      g.mutation(ffd);

      for (int i = 0; i < 30; i++) {
          g.crossover(s3, ffd, false);
      }

      writeFromFile("//", s3.getObj(), s3.getefficiency());

}
