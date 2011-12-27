/*-----------------------------------------------------------------------------------------------------------------

A*Ѱ·�㷨��

Author: ����

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
	//�����
	class Node
	{
	public:
		//�ý�����ڵ�ͼ���������
		unsigned int x , z;
		//�ý��Ĺ���ֵ���� f (�ܹ���) h(��Ŀ���Ĺ���) g(����ʼ��Ĺ���)
		unsigned int f , h , g;
		//�ý��ĸ����
		Node* mParentNode;
		//�ý�������
		int nodeIndex;
		//�Ƿ����
		bool bPass;
	};

public:
	AStar(void);
	~AStar(void);
	//���ص�ͼ��ײ����
	bool loadMap(unsigned int width , unsigned int height , const std::vector<bool>& mapData);
	//����·��
	bool findPath(unsigned int startX , unsigned int startZ , unsigned int endX , unsigned int endZ);
	//�����������,�����¼��ص�ͼ
	void clear();
	//���һ����������
	unsigned int getNodeIndex(unsigned int x , unsigned int z);
	std::list<int> getPath();

private:
	//����Hֵ
	unsigned int calculateH(unsigned int x , unsigned int z);
	//��ÿ����б��й�����õĽ��(����֮��,��һ����㼴��ѽ��)
	Node* getOpenListBestNode();
	//���������ӽ��
	void findAllSubNode(Node* pBestNode);
	//����Ƿ����(ע����Դ�����)
	bool hasNode(int x , int z);
	//�����ӽ�� ��һ������㣬��Ҫ�������x��z����
	void handleSubNode(Node* pParentNode , unsigned int x , unsigned int z, unsigned int distance);
	//�ڿ����б������һ�����
	Node* findNodeFromOpenList(unsigned int index);
	//�ڹر��б������һ�����
	Node* findNodeFromCloseList(unsigned int index);
	//���´����ӽ�㣨�ڹر��б��з���Gֵ��ԭ�����͵Ľ��ʱ���ã�
	void rehandleNode(Node* pNode);
	//�ӹر��б���ȡ��һ����㵽�����б���
	void findCloseNodeMoveToOpen(unsigned int index);
	//��һ�������뵽�����б��в���������fֵ��͵�������ǰ
	void insertNodeToOpenAndOrder(Node* pNode);
private:
	
	std::list<Node*>			mOpenList;					//�����б�
	std::list<Node*>			mCloseList;					//�ر��б�
	std::vector<Node>			mMapData;					//��ͼ������б�
	std::list<int>              mResultList;			    //Ѱ·���
	unsigned int				m_iWidth;
	unsigned int				m_iHeight;
	unsigned int				m_iMapSize;
	unsigned int				m_iStartX , m_iStartZ , m_iEndX , m_iEndZ;	//��ʼ��ͽ�����
	bool						m_bFail;					//����ʧ�ܣ�û�п���·��

	unsigned int				m_iDestIndex;				//Ŀ���������
	unsigned int				m_iStartIndex;				//��ʼ��������
};

#endif //__ASTAR_T__
