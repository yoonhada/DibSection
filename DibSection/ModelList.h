#pragma once

class CModelList
{
private:
	enum { HEXAGON, PYRAMID, DIAMOND, GLOBE, GEOSPHERE };
	
	int m_nTempIndex;
	int m_nTempVertex;
	
	std::list<CNode *> m_listNode;
	std::list<CNode *>::iterator it, itRutin;

	// Member
	void Pyramid(CNode *, float);
	void Diamond(CNode *, float);
	void Hexagon(CNode *, float);
	void GlobeSphere(CNode *, float, int=18, int = 36);
	void GeoSphere(CNode *, float, int=5);

	void DivideTriangle(CNode *, int, int, int, int);
public:
	CModelList(void);
	virtual ~CModelList(void);

	CNode* GetHead();
	CNode* GetCurr();
	CNode* GetNext();

	CNode* MoveHead();
	CNode* MoveNext();

	// List
	void Clear();
	void Insert(CNode *);
	void Remove();
	
	void RandomModel();
	void LoadModel(int, float, int=0, int=0, int=0, bool = true);
};