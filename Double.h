#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>



class Double 
{
private:
	int  item1, item2, totalweight; // iki e�yan�n numaralr� ve toplam a��rl�klar�
	
	

										/*hem vector alan hemde unordered set tipinde ikili kombinasyonlar�na kadarleri als�n;;; bo�ta kalan biri i�in item2 = -1 yap�cak tek varsa;
										* bir free bins  i�in bir de her dolu olan bin i�in
										* bo� olma iht de koyman laz�m removed items da onlar� atla
										* toplam a��rl�klar�n� ve hangi e�yalar�n olmas� gerekti�ini yaz�cak >>> double
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