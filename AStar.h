/*-----------------------------------------------------------------------------------------------------------------

A*寻路算法类

Author: 苗琳

Date: 2009-5-30

Update:

----------------------------------------------------------------------------------------------------------------**/	
#ifndef __ASTAR_T__
#define __ASTAR_T__

#include <vector>
#include <list>
class AStar
{
public:
	//结点类
	class Node
	{
	public:
		//该结点所在地图数组的索引
		unsigned int x , z;
		//该结点的估价值变量 f (总估价) h(到目标点的估价) g(到开始点的估价)
		unsigned int f , h , g;
		//该结点的父结点
		Node* mParentNode;
		//该结点的索引
		int nodeIndex;
		//是否可走
		bool bPass;
	};

public:
	AStar(void);
	~AStar(void);
	//加载地图碰撞数据
	bool loadMap(unsigned int width , unsigned int height , const std::vector<bool>& mapData);
	//搜索路径
	bool findPath(unsigned int startX , unsigned int startZ , unsigned int endX , unsigned int endZ);
	//清空所有数据,可重新加载地图
	void clear();
	//获得一个结点的索引
	unsigned int getNodeIndex(unsigned int x , unsigned int z);
	std::list<int> getPath();

private:
	//计算H值
	unsigned int calculateH(unsigned int x , unsigned int z);
	//获得开启列表中估价最好的结点(排序之后,第一个结点即最佳结点)
	Node* getOpenListBestNode();
	//搜索所有子结点
	void findAllSubNode(Node* pBestNode);
	//结点是否存在(注意可以传负数)
	bool hasNode(int x , int z);
	//处理子结点 传一个父结点，和要处理结点的x，z索引
	void handleSubNode(Node* pParentNode , unsigned int x , unsigned int z, unsigned int distance);
	//在开启列表里查找一个结点
	Node* findNodeFromOpenList(unsigned int index);
	//在关闭列表里查找一个结点
	Node* findNodeFromCloseList(unsigned int index);
	//重新处理子结点（在关闭列表中发现G值比原来更低的结点时调用）
	void rehandleNode(Node* pNode);
	//从关闭列表中取出一个结点到开启列表中
	void findCloseNodeMoveToOpen(unsigned int index);
	//将一个结点插入到开启列表中并重新排序，f值最低的排在最前
	void insertNodeToOpenAndOrder(Node* pNode);
private:
	
	std::list<Node*>			mOpenList;					//开启列表
	std::list<Node*>			mCloseList;					//关闭列表
	std::vector<Node>			mMapData;					//地图结点总列表
	std::list<int>              mResultList;			    //寻路结果
	unsigned int				m_iWidth;
	unsigned int				m_iHeight;
	unsigned int				m_iMapSize;
	unsigned int				m_iStartX , m_iStartZ , m_iEndX , m_iEndZ;	//开始点和结束点
	bool						m_bFail;					//查找失败，没有可用路径

	unsigned int				m_iDestIndex;				//目标结点的索引
	unsigned int				m_iStartIndex;				//开始结点的索引
};

#endif //__ASTAR_T__
