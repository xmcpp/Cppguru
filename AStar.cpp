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
//���ص�ͼ��ײ����
bool AStar::loadMap(unsigned int width , unsigned int height , const std::vector<bool>& mapData)
{
	clear();

	m_iWidth = width;
	m_iHeight = height;
	m_iMapSize = width * height;


	//���������Ч��
	if (mapData.size() != m_iMapSize) return false;


	//��ʼ���ܽ���б�
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

//����·��
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


	//���㿪ʼ��������
	m_iDestIndex = getNodeIndex(endX , endZ);
	m_iStartIndex = getNodeIndex(startX , startZ);
	
	//���ۿ�ʼ����
	Node* pStartNode = &mMapData[m_iStartZ * m_iWidth + m_iStartX];
	pStartNode->g = 0;
	pStartNode->h = calculateH(m_iStartX , m_iStartZ);
	pStartNode->f = pStartNode->g + pStartNode->h;
	

	//����ʼ���ָ����뿪���б�
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



//�����������,�����¼��ص�ͼ
void AStar::clear()
{
	mOpenList.clear();
	mCloseList.clear();
	mMapData.clear();
	m_bFail = false;
}


//���һ����������
unsigned int AStar::getNodeIndex(unsigned int x , unsigned int z)
{
	return z*m_iWidth + x;
}


//��ÿ����б��й�����õĽ��(����֮��,��һ����㼴��ѽ��)
AStar::Node* AStar::getOpenListBestNode()
{
	if (mOpenList.empty()) return NULL;
	

	//�ӿ����б���ȡ���׽�㣬��������ر��б�
	Node* pNode = mOpenList.front();
	mOpenList.pop_front();

	mCloseList.push_back(pNode);

	return pNode;
}

//����Ƿ����(ע����Դ�����)
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

//�����б������һ�����
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

//�ڹر��б������һ�����
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


//���´����ӽ�㣨�ڹر��б��з���Gֵ��ԭ�����͵Ľ��ʱ���ã�
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


//�ӹر��б���ȡ��һ����㵽�����б���
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

//��һ�������뵽�����б��в���������fֵ��͵�������ǰ
void AStar::insertNodeToOpenAndOrder(Node* pNode)
{
	int f = pNode->f;

	//��������б��ǿյģ���ֱ������½���ȥ
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
	//fֵ�ڴ��б�����󣬲��뵽���
	mOpenList.push_back(pNode);
}

//���������ӽ��
void AStar::findAllSubNode(Node* pBestNode)
{
	int x,z;



	//��
	if (hasNode(x = (int)pBestNode->x,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//����
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//����
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z-1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//��
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//��
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//��
	if (hasNode(x = (int)pBestNode->x,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,10);
	}
	//����
	if (hasNode(x = (int)pBestNode->x-1,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,14);
	}
	//����
	if (hasNode(x = (int)pBestNode->x+1,z = (int)pBestNode->z+1))
	{
		handleSubNode(pBestNode,x,z,14);
	}

}

//�����ӽ��
void AStar::handleSubNode(Node* pParentNode , unsigned int x , unsigned int z , unsigned int distance)
{
	int nodeIndex= getNodeIndex(x , z);		//��ǰ��������ֵ

	//�ж��Ƿ����
	if (mMapData[nodeIndex].bPass == false)
	{
		return;
	}

	int g;				//��ǰ����Gֵ
	//int c=0;
	Node *pOldNode,*pSubNode;

	//�����ӽڵ�� g ֵ
	g = pParentNode->g + distance;


	//�ӽڵ���Open������
	if (pOldNode = findNodeFromOpenList(nodeIndex))
	{
		//for(c=0;c<8;c++)
		//	if(pParentNode->Child[c] == NULL) /* Add Old to the list of BestNode's Children (or Successors). */
		//		break;
		//pParentNode->Child[c]=pOldNode;


		//����µ�Gֵ��ԭ���ĸ��̣���ı�ԭ���ĸ����Ϊ�½��ĸ���㣬���ı�·��(ֻҪ�Ƚ�gֵ�Ϳ�����)
		if (g < pOldNode->g)  
		{
			pOldNode->mParentNode = pParentNode;
			pOldNode->g = g;
			pOldNode->f = g + pOldNode->h;
		}
	}
	else if (pOldNode = findNodeFromCloseList(nodeIndex))		//��Closed������
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

			//��һ�ַ�ʽ
			//����Gֵ�����ı䣬������Ҫ���¼�����ӽ����Χ���ӽ��Ĺ���ֵ �������һЩ
			//rehandleNode(pOldNode);       
			
			//�ڶ��ַ�ʽ���ӹر��б���ȡ���������ӽ������б���
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





 