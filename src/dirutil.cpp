/* -------------------------------------------------------------------------
 *	ファイル名の操作
 * ---------------------------------------------------------------------- */
#include "dirutil.h"
#include <string.h>

//ファイルネーム（フルパス）からディレクトリーを求める。
char* Directory(char* FileName)
{
	int n;
	static char dir[256];

	for(n=strlen(FileName);FileName[n]!='\\';n--){}
	n--;

	for(;n>=0;n--)
	{
		dir[n]=FileName[n];
	}
	return dir;
}

//ファイルネーム（フルパス）から
//ディレクトリ、拡張子ものぞいた名前を求める。
char* filename(char* FileName)
{
	int i=0,n;
	static char fn[256];

	for(n=strlen(FileName);FileName[n]!='\\';n--){}

	n++;
	while(FileName[n+i]!='.')
	{
		fn[i++]=FileName[n+i];
	}
	fn[i]=0;
	return fn;
}

