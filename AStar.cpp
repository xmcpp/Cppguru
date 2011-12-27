#include "pch.h"
#include "AStar.h"

AStar::AStar(void)
: m_iMapSize(0) , m_bFail(false)
{
}

AStar::~AStar(void)
{
}

unsigned int AStar::calculateH(unsigned int x , unsigned int z)
{
	return (abs(x-m_iEndX) + abs( z - m_iEndZ ))*10;
	//return ((x-m_iEndX)*(x-m_iEndX)+(z-m_iEndZ)*(z-m_iEndZ))*10;
}
//加载地图碰撞数据
bool AStar::loadMap(unsigned int width , unsigned int height , const std::vector<bool>& mapData)
{
	clear();

	m_iWidth = width;
	m_iHeight = height;
	m_iMapSize = width * height;


	//检测数据有效性
	if (mapData.size() != m_iMapSize) return false;


	//初始化总结点列表
	mMapData.resize(m_iMapSize);
	for (size_t j = 0 ; j < m_iHeight ; j++)
	{
		for (size_t i = 0 ; i < m_iWidth ; i++)
		{
			unsigned int index = j*m_iWidth+i;
			Node* pNode = &mMapData[index];
			pNode->nodeIndex = index;
			pNode->x = i;
			pNode->z = j;
			pNode->bPass = mapData[index];

			pNode->f = 0;
			pNode->g = 0;
			pNode->h = 0;
			pNode->mParentNode = NULL;
		}
	}
	return true;
}

std::list<int> AStar::getPath()
{
	return mResultList;
}

//搜索路径
bool AStar::findPath(unsigned int startX , unsigned int startZ , unsigned int endX , unsigned int endZ)
{
	m_bFail = false;
	mResultList.clear();
	mOpenList.clear();
	mCloseList.clear();

	if (!hasNode(startX , startZ)) return false;
	if (!hasNode(endX , endZ)) return false;

	m_iStartX = startX;
	m_iStartZ = startZ;
	m_iEndX = endX;
	m_iEndZ = endZ;


	//计算开始结束索引
	m_iDestIndex = getNodeIndex(endX , endZ);
	m_iStartIndex = getNodeIndex(startX , startZ);
	
	//估价开始点结点
	Node* pStartNode = &mMapData[m_iStartZ * m_iWidth + m_iStartX];
	pStartNode->g = 0;
	pStartNode->h = calculateH(m_iStartX , m_iStartZ);
	pStartNode->f = pStartNode->g + pStartNode->h;
	

	//将开始点的指针加入开启列表
	mOpenList.push_back(pStartNode);


	while (!m_bFail)
	{
		Node* pBestNode = getOpenListBestNode();

		if (pBestNode==NULL)
		{
			m_bFail = true;
			return false;
		}
		if (pBestNode->nodeIndex == m_iDestIndex)
		{
			Node* pNode = pBestNode;
			while (pNode)
			{
				if (pNode->nodeIndex==m_iStartIndex)
				{
					mResultList.push_front(pNode->nodeIndex);
					return true;
				}
				else
				{
					mResultList.push_front(pNode->nodeIndex);
					pNode = pNode->mParentNode;
				}
			}
			
			return false;
		}
		findAllSubNode(pBestNode);
	}

	return false;
}



//清空所有数据,可重新加载地图
void AStar::clear()
{
	mOpenList.clear();
	mCloseList.clear();
	mMapData.clear();
	m_bFail = false;
}


//获得一个结点的索引
unsigned int AStar::getNodeIndex(unsigned int x , unsigned int z)
{
	return z*m_iWidth + x;
}


//获得开启列表中估价最好的结点(排序之后,第一个结点即最佳结点)
AStar::Node* AStar::getOpenListBestNode()
{
	if (mOpenList.empty()) return NULL;
	

	//从开启列表中取出首结点，并增加入关闭列表
	Node* pNode = mOpenList.front();
	mOpenList.pop_front();

	mCloseList.push_back(pNode);

	return pNode;
}

//结点是否存在(注意可以传负数)
bool AStar::hasNode(int x , int z)
{
	if (x >= 0 && x < m_iWidth && z >=0 && z < m_iHeight)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//开启列表里查找一个结点
AStar::Node* AStar::findNodeFromOpenList(unsigned int index)
{
	Node* pNode = NULL;

	std::list<Node*>::iterator itr = mOpenList.begin();
	while (itr != mOpenList.end())
	{
		if ((*itr)->nodeIndex == index)
		{
			pNode = *itr;
			return pNode;
		}

		++itr;
	}

	return pNode;
}

//在关闭列表里查找一个结点
AStar::Node* AStar::findNodeFromCloseList(unsigned int index)
{
	Node* pNode = NULL;

	std::list<Node*>::iterator itr = mCloseList.begin();
	while (itr != mCloseList.end())
	{
		if ((*itr)->nodeIndex == index)
		{
			pNode = *itr;
			return pNode;
		}

		++itr;
	}

	return pNode;
}


//重新处理子结点（在关闭列表中发现G值比原来更低的结点时调用）
void AStar::rehandleNode(Node* pNode)
{
	//int c,g;
	//struct NODE *Child, *Father;

	//g=pNode->g;            // alias.
	//for(c=0;c<8;c++)
	//{
	//	if ((Child=pNode->Child[c])==NULL)   // create alias for faster access.
	//		break;
	//	if (g+1 < Child->g)
	//	{
	//		Child->g=g+1;
	//		Child->f=Child->g+Child->h;
	//		Child->Parent=pNode;           // reset parent to new path.
	//		Push(Child);                 // Now the Child's branch need to be
	//	}     // checked out. Remember the new cost must be propagated down.
	//}

	//while (Stack->NextStackPtr != NULL)
	//{
	//	Father=Pop();
	//	for(c=0;c<8;c++)
	//	{
	//		if ((Child=Father->Child[c])==NULL)       /* we may stop the propagation 2 ways: either */
	//			break;
	//		if (Father->g+1 < Child->g) /* there are no children, or that the g value of */
	//		{                           /* the child is equal or better than the cost we're propagating */
	//			Child->g=Father->g+1;
	//			Child->f=Child->g+Child->h;
	//			Child->Parent=Father;
	//			Push(Child);
	//		}
	//	}
	//}
}


//从关闭列表中取出一个结点到开启列表中
void AStar::findCloseNodeMoveToOpen(unsigned int index)
{
	Node* pNode = NULL;

	std::list<Node*>::iterator itr = mCloseList.begin();
	while (itr != mCloseList.end())
	{
		if ((*itr)->nodeIndex == index)
		{
			pNode = *itr;
			mCloseList.erase(itr);
			mOpenList.push_back(pNode);
			break;
		}

		++itr;
	}
}

//将一个结点插入到开启列表中并重新排序，f值最低的排在最前
void AStar::insertNodeToOpenAndOrder(Node* pNode)
{
	int f = pNode->f;

	//如果开启列表是空的，则直接添加新结点进去
	if (mOpenList.empty())
	{
		mOpenList.push_back(pNode);
		return;
	}



	std::list<Node*>::iterator itr = mOpenList.begin();
	while (itr != mOpenList.end())
	{
		if (f <= (*itr)->f)
		{
			mOpenList.insert(itr , pNode);
			return;
		}

		++itr;
	}
	//f值在打开列表中最大，插入到最后
	mOpenList.push_back(pNode);
}

//搜索所有子结点
void AStar::findAllSubNode(Node* pBestNode)
{
	int x,z;



	//上
	if (hasNode(x = (int)pBestNode->x,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//上左
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//上右
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//左
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//右
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//下
	if (hasNode(x = (int)pBestNode->x,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//下左
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//下右
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,14);
	}

}

//处理子结点
void AStar::handleSubNode(Node* pParentNode , unsigned int x , unsigned int z , unsigned int distance)
{
	int nodeIndex= getNodeIndex(x , z);		//当前结点的索引值

	//判断是否可走
	if (mMapData[nodeIndex].bPass == false)
	{
		return;
	}

	int g;				//当前结点的G值
	//int c=0;
	Node *pOldNode,*pSubNode;

	//计算子节点的 g 值
	g = pParentNode->g + distance;


	//子节点再Open表中吗？
	if (pOldNode = findNodeFromOpenList(nodeIndex))
	{
		//for(c=0;c<8;c++)
		//	if(pParentNode->Child[c] == NULL) /* Add Old to the list of BestNode's Children (or Successors). */
		//		break;
		//pParentNode->Child[c]=pOldNode;


		//如果新的G值比原来的更短，则改变原结点的父结点为新结点的父结点，即改变路径(只要比较g值就可以了)
		if (g < pOldNode->g)  
		{
			pOldNode->mParentNode = pParentNode;
			pOldNode->g = g;
			pOldNode->f = g + pOldNode->h;
		}
	}
	else if (pOldNode = findNodeFromCloseList(nodeIndex))		//在Closed表中吗？
	{
		//for(c=0;c<8;c++)
		//	if (BestNode->Child[c] == NULL) /* Add Old to the list of BestNode's Children (or Successors). */
		//		break;
		//BestNode->Child[c]=Old;


		if (g < pOldNode->g)  /* if our new g value is < Old's then reset Old's parent to point to BestNode */
		{
			pOldNode->mParentNode = pParentNode;
			pOldNode->g = g;
			pOldNode->f = g + pOldNode->h;

			//第一种方式
			//由于G值发生改变，所以需要重新计算该子结点周围的子结点的估价值 这样会快一些
			//rehandleNode(pOldNode);       
			
			//第二种方式，从关闭列表中取出，并增加进开启列表中
			findCloseNodeMoveToOpen(nodeIndex);
		}
	}
	else
	{
		pSubNode = &mMapData[nodeIndex];
		pSubNode->mParentNode = pParentNode;
		pSubNode->g = g;
		pSubNode->h = calculateH(x , z);
		pSubNode->f = g + pSubNode->h;
		insertNodeToOpenAndOrder(pSubNode);

		//for(c=0;c<8;c++)
		//	if (BestNode->Child[c] == NULL) /* Add Old to the list of BestNode's Children (or Successors). */
		//		break;
		//BestNode->Child[c]=Successor;
	}
}





 