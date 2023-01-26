#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>



class Double 
{
private:
	int  item1, item2, totalweight; // iki eþyanýn numaralrý ve toplam aðýrlýklarý
	
	

										/*hem vector alan hemde unordered set tipinde ikili kombinasyonlarýna kadarleri alsýn;;; boþta kalan biri için item2 = -1 yapýcak tek varsa;
										* bir free bins  için bir de her dolu olan bin için
										* boþ olma iht de koyman lazým removed items da onlarý atla
										* toplam aðýrlýklarýný ve hangi eþyalarýn olmasý gerektiðini yazýcak >>> double
										*


*/
public:
	Double(int  item1, int  item2, int  totlweight) :
		
		item1(item1),
		item2(item2),
		totalweight(totlweight)
	{
		
	}
	Double() = default;

	int getItem1() {return item1;  }

	int getItem2() { return item2; }

	int getTotalWeight() { return totalweight; }

};