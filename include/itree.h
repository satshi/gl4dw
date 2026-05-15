/*
 稜を作るために使う木
*/

#ifndef ITREE_H_
#define ITREE_H_

typedef unsigned long ULONG;


#ifndef TRUE
typedef int BOOL;
#define TRUE 1
#define FALSE 0
#endif   //#ifndef TRUE


class itree
{
  public:
	//-----------------------------ノードのクラス
	class node
	{
	  public:
		ULONG key;
		node* left;
		node* right;
		
		node() //デフォールトコンストラクタ
		{
			key=0;
			left=NULL;
			right=NULL;
		}
		
		node(ULONG k)
		{
			key=k;
			left=NULL;
			right=NULL;
		}
	}
	
	//-----------------------ここから木のメンバー
	node* root;
	int n;
	
	itree()
	{
		root=NULL;
		n=0;
	}
	
	~itree();
	
	
	BOOL drop(ULONG nkey);//polytope.cppで定義する。
	ULONG* toAry(); //配列にする。
}

#endif  //#ifndef ITREE_H_
