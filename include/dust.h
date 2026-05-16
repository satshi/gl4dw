#ifndef _DUST_H
#define _DUST_H

#include<math.h>

//BOOLの定義
typedef int BOOL;
#define TRUE 1
#define FALSE 0
//１つのセルあたりの要素の数の最大値
#define MAX_NUMBER_PER_CELL 1024

//稜の数の最大値
#define MAX_NUMBER_OF_EDGES 30000

//面の数の最大値
#define MAX_NUMBER_OF_FACES 20000

inline BOOL eql(double a, double b)
{
	return fabs(a-b)<10e-6;
}

#endif