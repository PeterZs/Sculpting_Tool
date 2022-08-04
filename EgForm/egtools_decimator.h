#pragma once

#include <vector>
#include <map>
#include <queue>
#include <functional>
#include "EgMath\egmath.h"
#include "EgMesh\egmesh.h"

/*!
*	\class EgDecimator
*	\brief 메쉬의 단순화를 위한 클래스(위치 + 텍스처 좌표를 포함)
*
*	\author 박정호, 윤승현
*	\date 01 Oct. 2018
*/
class EgDecimator
{
public:
	/*!
	*	\class EdgeCollapseInfo
	*	\brief 에지 제거 정보를 표현하는 클래스
	*
	*	\author 박정호, 윤승현
	*	\date 01 Oct. 2018
	*/
	class EdgeCollapseInfo
	{
		// 프렌드 함수
		friend bool operator >(const EdgeCollapseInfo &lhs, const EdgeCollapseInfo &rhs);

	public:
		/*! \brief 제거할 에지에 대한 포인터 */
		EgEdge *m_pEdge;

		/*! \brief 정보가 생성될 당시 에지 제거 비용 */
		double m_Cost;

		/*! \brief 에지 제거 후, 두 끝점의 위치 */
		EgPos m_Pos;

		/*! \brief 에지 제거 후, 두 끝점의 텍스쳐 좌표 */
		EgVec2 m_UV;

	public:
		// 생성자 및 소멸자
		EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos);
		EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos, EgVec2 UV);
		EdgeCollapseInfo(const EdgeCollapseInfo &cpy);
		~EdgeCollapseInfo();

		// 대입 연산자
		EdgeCollapseInfo &operator =(const EdgeCollapseInfo &rhs);
	};

	/*! \brief 에지 붕괴 타입 열거형 */
	enum TypeCollapse
	{
		COLLAPSE_OPT_POS = 0,
		COLLAPSE_MID_POS,
		COLLAPSE_END_POS,
	};

public:
	/*! \brief 단순화할 대상 메쉬에 대한 포인터 */
	EgMesh *m_pMesh;

	/*! \brief 메쉬의 각 정점의 경계 정점 여부를 저장하는 변수 */
	std::vector<bool> m_BndryVertInfo;

	/*! \brief 대상 메쉬의 각 정점에서 정의된 QEM 행렬 */
	std::vector<EgMat> m_QEM;

	/*! \brief 에지 제거 비용에 따라 에지 제거 정보를 저장하는 최소힙 */
	std::priority_queue<EdgeCollapseInfo, std::vector<EdgeCollapseInfo>, std::greater<EdgeCollapseInfo>> m_Heap;

	/*! \brief 에지 제거 옵션 */
	TypeCollapse m_CollapseType;

	/*! \breif 텍스처 단순화 여부 */
	bool m_bTextureDecimate;

protected:
	// 텍스처를 고려한 함수들
	void GetErrorMatrix_T(EgMat &K, EgVec &p, EgVec &q, EgVec &r);
	void InitBndryVertInfo_T(int NumVert);
	void InitVertQEM_T(int NumVert);
	void InitCollapseInfo_T();
	bool IsCollapsible_T(EgEdge *pEdge);
	int CollapseEdge_T(EdgeCollapseInfo &info, int &sIdx, int &eIdx);
	void UpdateCollapseInfo_T(EgVertex *v);

	// 텍스처를 고려하지 않는 함수들
	void GetErrorMatrix(EgMat &K, double a, double b, double c, double d);
	EgMat Inv3(EgMat &A, double det);
	void InitVertQEM(int NumVert);
	void InitCollapseInfo();
	bool IsCollapsible(EgEdge *pEdge);
	int CollapseEdge(EdgeCollapseInfo &info, int &sIdx, int &eIdx);
	void UpdateCollapseInfo(EgVertex *v);

	// 공통 함수
	void DeleteIncidentFaces(EgEdge *e);
	void DeleteUnusedGeometry(int &num_vert, int &num_tex, int &num_normal);
	void UpdateFaceList();

public:
	// 생성자 및 소멸자
	EgDecimator(EgMesh *pMesh, bool bDecimateTexture);
	~EgDecimator();

	// 멤버 함수
	void Init(TypeCollapse CollapseType);
	void Decimate(int TarNumVert, const char *FileName = NULL);
	void Decimate(const char *fname);
};
