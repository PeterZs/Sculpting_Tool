#pragma once

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include "EgMath\egmath.h"
#include "EgMesh\egmesh.h"

/*!
*	\class EgDecimator
*	\brief �޽��� �ܼ�ȭ�� ���� Ŭ����(��ġ + �ؽ�ó ��ǥ�� ����)
*
*	\author ����ȣ, ������
*	\date 01 Oct. 2018
*/
class EgDecimator
{
public:
	/*!
	*	\class EdgeCollapseInfo
	*	\brief ���� ���� ������ ǥ���ϴ� Ŭ����
	*
	*	\author ����ȣ, ������
	*	\date 01 Oct. 2018
	*/
	class EdgeCollapseInfo
	{
		// ������ �Լ�
		friend bool operator >(const EdgeCollapseInfo &lhs, const EdgeCollapseInfo &rhs);

	public:
		/*! \brief ������ ������ ���� ������ */
		EgEdge *m_pEdge;

		/*! \brief ������ ������ ��� ���� ���� ��� */
		double m_Cost;

		/*! \brief ���� ���� ��, �� ������ ��ġ */
		EgPos m_Pos;

		/*! \brief ���� ���� ��, �� ������ �ؽ��� ��ǥ */
		EgVec2 m_UV;

	public:
		// ������ �� �Ҹ���
		EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos);
		EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos, EgVec2 UV);
		EdgeCollapseInfo(const EdgeCollapseInfo &cpy);
		~EdgeCollapseInfo();

		// ���� ������
		EdgeCollapseInfo &operator =(const EdgeCollapseInfo &rhs);
	};

	/*! \brief ���� �ر� Ÿ�� ������ */
	enum TypeCollapse
	{
		COLLAPSE_OPT_POS = 0,
		COLLAPSE_MID_POS,
		COLLAPSE_END_POS,
	};

public:
	/*! \brief �ܼ�ȭ�� ��� �޽��� ���� ������ */
	EgMesh *m_pMesh;

	/*! \brief �޽��� �� ������ ��� ���� ���θ� �����ϴ� ���� */
	std::vector<bool> m_BndryVertInfo;

	/*! \brief ��� �޽��� �� �������� ���ǵ� QEM ��� */
	std::vector<EgMat> m_QEM;

	/*! \brief ���� ���� ��뿡 ���� ���� ���� ������ �����ϴ� �ּ��� */
	std::priority_queue<EdgeCollapseInfo, std::vector<EdgeCollapseInfo>, std::greater<EdgeCollapseInfo>> m_Heap;

	/*! \brief ���� ���� �ɼ� */
	TypeCollapse m_CollapseType;

	/*! \breif �ؽ�ó �ܼ�ȭ ���� */
	bool m_bTextureDecimate;

protected:
	// �ؽ�ó�� ����� �Լ���
	void GetErrorMatrix_T(EgMat &K, EgVec &p, EgVec &q, EgVec &r);
	void InitBndryVertInfo_T(int NumVert);
	void InitVertQEM_T(int NumVert);
	void InitCollapseInfo_T();
	bool IsCollapsible_T(EgEdge *pEdge);
	int CollapseEdge_T(EdgeCollapseInfo &info, int &sIdx, int &eIdx);
	void UpdateCollapseInfo_T(EgVertex *v);

	// �ؽ�ó�� ������� �ʴ� �Լ���
	void GetErrorMatrix(EgMat &K, double a, double b, double c, double d);
	EgMat Inv3(EgMat &A, double det);
	void InitVertQEM(int NumVert);
	void InitCollapseInfo();
	bool IsCollapsible(EgEdge *pEdge);
	int CollapseEdge(EdgeCollapseInfo &info, int &sIdx, int &eIdx);
	void UpdateCollapseInfo(EgVertex *v);

	// ���� �Լ�
	void DeleteIncidentFaces(EgEdge *e);
	void DeleteUnusedGeometry(int &num_vert, int &num_tex, int &num_normal);
	void UpdateFaceList();

public:
	// ������ �� �Ҹ���
	EgDecimator(EgMesh *pMesh, bool bDecimateTexture);
	~EgDecimator();

	// ��� �Լ�
	void Init(TypeCollapse CollapseType);
	void Decimate(int TarNumVert, const char *FileName = NULL);
	void Decimate(const char *fname);
};
