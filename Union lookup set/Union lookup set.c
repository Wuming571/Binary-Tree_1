#include<stdio.h>
#include<stdlib.h>
/*1 2 3 4 5 6 

关系：  （4.3） （3 2） （ 2 1） 

查询： （4.1） （4.6）； 

 */  

int f[10];

void init(int n)
{
	
	for(int i=1;i<=n;i++)
	{
		f[i]=i;//建立起了n个单元数集合 
	}
   return;	
}
//查找祖先  
int find(int x)
{
  //非递归
  while(f[x]!=x)
  {
  	x=f[x];
  	
   } 
   return x;

}
//查找祖先 O(n) 
int find1(int x)
{
  //递归
  if(f[x]!=x)
  {
  	return find1(f[x]);
  }
  return x;
}
//优化 路径压缩 --O(1)
int find2(int x)
{
  //递归
  if(f[x]!=x)
  {
  	return f[x]=find2(f[x]);      
  }
  return x;
}
//建立x y的关系--通过合并两者所在的集合 
void unionn(int x,int y)
{
    int ax=find2(x);
	int ay=find2(y);
	
	f[ay]=ax;//合并	
	
	//f[find2(x)]=find2(y); 
		
	
}
int  main()
{
	init(6);
	int m,x,y;
	scanf_s("%d",&m);//有m对关系
	for(int i=1;i<=m;i++)
	{
		scanf_s("%d %d",&x,&y);
		unionn(x,y);//建立起关系； 
		
	 } 
	scanf_s("%d",&m);//有m个查询
	for(int i=1;i<=m;i++)
	{
		scanf_s("%d %d",&x,&y);
		 int ax=find2(x);
	      int ay=find2(y);
	      if(ax==ay)
		  {
		  	printf("YES\n");//x和y有关系 
		   } 
		   else{
		   	printf("No\n");//x和没有关系 
		   } 
		
	 } 	
 } 
