#pragma once

// 클래스 선언
class EgObject;
class EgVertex;
class EgTexel;
class EgNormal;
class EgEdge;
class EgFace;
class EgMeshPt;
class EgTexture;
class EgMaterial;
class EgBox;
class EgMesh;
class EgMeshPt;
class EgMeshVec;
class EgBvh;

/*!
*	\class	EgObject
*	\brief	편집 가능한 객체의 기본 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	2018-01-01
*/
class EgObject
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	새로 생성되는 객체의 이름을 반환한다.
	*
	*	\return 새로 생성되는 객체의 이름을 반환한다.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	객체가 포함된 메쉬의 포인터를 반환한다.
	*
	*	\return 객체가 포함된 메쉬의 포인터를 반환한다.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	월드 좌표계에서 표현된 객체의 로컬 좌표계를 반환한다.
	*
	*	\return 월드 좌표계에서 표현된 객체의 로컬 좌표계를 반환한다.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	객체를 편집한다.
	*
	*	\param	EC[in]		편집 좌표계(월드 좌표계 기준)
	*	\param	t[in]		편집될 객체의 이동 변위(편집 좌표계 기준)
	*	\param	q[in]		편집될 객체의 회전 변위(편집 좌표계 기준)
	*	\param	s[in]		편집될 객체의 스케일 변위(편집 좌표계 기준)
	*	\param	bFirst[in]	여러 객체들을 동시에 편집할 경우 첫 번째 객체에 대한 여부
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	편집 중인 객체를 렌더링 한다.
	*
	*	\param  r[in]	색상의 red 성분
	*	\param  g[in]	색상의 green 성분
	*	\param  b[in]	색상의 blue 성분
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*!
	*	\brief	생성자
	*/
	EgObject() {};

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgObject() {};
};

/*!
*	\class	EgVertex
*	\brief	메쉬 정점을 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	2018-01-25
*/
class EgVertex : public EgObject
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	정점이 포함된 메쉬의 포인터를 반환한다.
	*
	*	\return 정점이 포함된 메쉬의 포인터를 반환한다.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	월드 좌표계에서 표현된 정점의 로컬 좌표계를 반환한다.
	*
	*	\return 월드 좌표계에서 표현된 정점의 로컬 좌표계를 반환한다.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	정점을 편집한다.
	*
	*	\param	EC[in]		편집 좌표계(월드 좌표계 기준)
	*	\param	t[in]		편집될 객체의 이동 변위(편집 좌표계 기준)
	*	\param	q[in]		편집될 객체의 회전 변위(편집 좌표계 기준)
	*	\param	s[in]		편집될 객체의 스케일 변위(편집 좌표계 기준)
	*	\param	bFirst[in]	여러 객체들을 동시에 편집할 경우 첫 번째 객체에 대한 여부
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	편집 중인 정점을 렌더링 한다.
	*
	*	\param  r[in]	색상의 red 성분
	*	\param  g[in]	색상의 green 성분
	*	\param  b[in]	색상의 blue 성분
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \brief 정점이 포함된 메쉬의 포인터 */
	EgMesh *m_pMesh;

	/*! \brief 정점의 인덱스 */
	int m_Idx;

	/*! \brief 정점의 3차원 좌표 */
	EgPos m_Pos;

	/*! \brief 정점의 색상 */
	EgVec3 m_Color;

	/*! \brief 정점의 편집 가중치 */
	float m_EditWgt;

	/*! \brief 정점에서 시작하는 하프에지 포인터 배열 */
	std::vector<EgEdge *> m_pEdges;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	x[in]	정점의 x 좌표
	*	\param	y[in]	정점의 y 좌표
	*	\param	z[in]	정점의 z 좌표
	*/
	EgVertex(double x = 0.0, double y = 0.0, double z = 0.0);

	/*!
	*	\brief	생성자
	*
	*	\param	Pos[in]	정점의 좌표
	*/
	EgVertex(EgPos Pos);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgVertex();

	/*!
	*	\brief	정점의 차수(정점과 연결된 에지의 수)를 반환한다.
	*	\note	내부 정점의 경우 정점을 공유한 삼각형 수와 같다.
	*
	*	\return 정점 차수를 반환한다.
	*/
	int GetDegree();

	/*!
	*	\brief	정점의 1링 이웃 정점을 구한다.
	*
	*	\param	Verts[out]	1링 이웃 정점들의 포인터가 저장된다.
	*	\param	bCCW[in]	1링 이웃 정점을 반시계 방향으로 정렬하려면 true
	*
	*	\return 1링 정점의 수(degree)를 반환한다.
	*/
	int GetOneRingVert(std::vector<EgVertex *> &Verts, bool bCCW = false);

	/*!
	*	\brief	정점을 공유하는 1링 삼각형을 구한다.
	*
	*	\param	Faces[out]	정점을 공유하는 삼각형들의 포인터가 저장된다.
	*
	*	\return 정점을 공유하는 1링 삼각형의 수를 반환한다.
	*/
	int GetOneRingFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	정점의 1링 경계 에지를 구한다.
	*
	*	\param	Edges[out]	경계 에지들의 포인터가 저장된다.
	*
	*	\return 정점의 1링 경계 에지의 수를 반환한다.
	*/
	int GetOneRingEdge(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	정점에서 출발하는 에지를 구한다.
	*
	*	\param	Edges[out]	정점에서 출발하는 에지들의 포인터가 반시계 방향으로 저장된다.
	*
	*	\return 정점에서 출발하는 에지의 수를 반환한다.
	*/
	int GetOutGoingEdge(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	정점의 1링 이웃 정점을 구한다.
	*
	*	\return 1링을 이웃 정점의 리스트를 반환한다.
	*/
	std::vector<EgVertex *> GetOneRingVert();

	/*!
	*	\brief	정점을 공유하는 1링 삼각형을 구한다.
	*
	*	\return 정점을 공유하는 1링 삼각형 리스트를 반환한다.
	*/
	std::vector<EgFace *> GetOneRingFace();

	/*!
	*	\brief	정점의 1링 경계 에지를 구한다.
	*
	*	\return 정점의 1링 경계 에지 리스트를 반환한다.
	*/
	std::vector<EgEdge *> GetOneRingEdge();

	/*!
	*	\brief	정점에서 출발하는 에지를 구한다.
	*
	*	\return 정점에서 출발하는 에지 리스트를 반환한다.
	*/
	std::vector<EgEdge *> GetOutGoingEdge();

	/* !
	*	\brief	경계 정점 여부를 조사한다.
	*
	*	\return 경계 정점이면 true, 아니면 false를 반환한다.
	*/
	bool IsBndry();

	/* !
	*	\brief	코너 정점 여부를 조사한다.
	*
	*	\return 코너 정점이면 true, 아니면 false를 반환한다.
	*/
	bool IsCorner();

	/*!
	*	\brief	정점이 볼록한 영역에 있는지 판단한다.
	*
	*	\return	정점이 볼록한 영역에 있으면 true, 아니면 false를 반환한다.
	*/
	bool IsConvex();

	/*!
	*	\brief	정점이 오목한 영역에 있는지 판단한다.
	*
	*	\return	정점이 오목한 영역에 있으면 true, 아니면 false를 반환한다.
	*/
	bool IsConcave();

	/*!
	*	\brief	고립된 정점인지를 검사한다.
	*
	*	\return	고립된 정점이면 true, 아니면 false를 반환한다.
	*/
	bool IsIsolated();

	/*!
	*	\brief	정점에서 시작하는 에지 중에 complex(non-manifold) 에지가 있는지 조사한다.
	*
	*	\return	Complex 에지를 포함하고 있다면 true, 아니면 false를 반환한다.
	*/
	bool HasComplexEdge();

	/*!
	*	\brief	정점이 입력 정점과 연결되어 있는지 조사한다.
	*
	*	\param	v[in]	입력 정점
	*
	*	\return	정점이 v와 연결되어 있으면 에지를 반환하고, 아니면 NULL을 반환한다.
	*/
	EgEdge *IsAdjacent(EgVertex *v);

	/*!
	*	\brief	정점의 평균 단위 법선을 구한다.
	*
	*	\param	bWgt[in]	각도 가중치 적용 여부
	*
	*	\return 정점의 평균 단위 법선을 반환한다.
	*/
	EgVec3 GetAvgNormal(bool bWgt = false);

	/*!
	*	\breif	정점의 1-링 정점들의 무게중심을 반환한다.
	*
	*	\return 정점의 1-링 정점들의 무게중심을 반환한다.
	*/
	EgPos GetOneRingCenter();

	/*!
	*	\brief	정점의 위치를 perturbation 한다
	*
	*	\param	rate[in]	무게 중심 방향으로 움직일 비율
	*
	*	\return	변경된 정점의 위치를 반환한다.
	*/
	EgPos Perturbate(double rate);

	/*!
	*	\brief	정점에서 시작하는 에지 리스트에서 에지를 제거한다.
	*	\note	마지막 수정일: 2021-01-08
	*
	*	\param	e[in]	제거할 에지 포인터
	*
	*	\return	제거 후, 정점에서 시작하는 에지의 수를 반환한다(제거할 에지가 없는 경우 -1을 반환)
	*/
	int DeleteEdge(EgEdge *e);
};

/*!
*	\class	EgTexel
*	\brief	메쉬의 텍스처 정점을 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	2018-01-27
*/
class EgTexel
{
public:
	/*! \brief 텍스처 정점의 인덱스 */
	int m_Idx;

	/*! \brief 텍스처 좌표 */
	EgVec2 m_UV;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	u[in]	수평 방향 텍스처 좌표
	*	\param	v[in]	수직 방향 텍스처 좌표
	*/
	EgTexel(double u = 0.0, double v = 0.0);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgTexel();
};

/*!
*	\class	EgNormal
*	\brief	메쉬의 법선 정보를 표현하는 클래스
*
*	\author	박정호, 윤승현
*	\date	27 Jun 2018
*/
class EgNormal
{
public:
	/*! \brief 법선의 인덱스 */
	int m_Idx;

	/*! \brief 법선의 방향 */
	EgVec3 m_Dir;

public:
	/*!	\brief	생성자
	*
	*	\param	nx[in]	법선의 x 좌표
	*	\param	ny[in]	법선의 y 좌표
	*	\param	nz[in]	법선의 z 좌표
	*/
	EgNormal(double nx = 0.0, double ny = 0.0, double nz = 0.0);

	/*!	\brief	생성자
	*
	*	\param	Dir[in]	법선의 방향
	*/
	EgNormal(EgVec3 Dir);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgNormal();
};

/*!
*	\class	EgEdge
*	\brief	삼각형의 하프에지(Halfedge)를 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	25 Jan 2018
*/
class EgEdge
{
public:
	/*! \brief 에지 시작점에 연결된 정점 */
	EgVertex *m_pVert;

	/*! \brief 에지 시작점에 연결된 텍셀 */
	EgTexel *m_pTexel;

	/*! \brief 에지 시작점에 연결된 법선 */
	EgNormal *m_pNormal;

	/*! \brief 에지가 포함된 삼각형에 대한 포인터 */
	EgFace *m_pFace;

	/*! \brief 삼각형을 구성하는 다음 에지에 대한 포인터 */
	EgEdge *m_pNext;

	/*! \brief 인접한 삼각형의 반대편 에지에 대한 포인터 */
	EgEdge *m_pMate;

	/*! \brief 에지에 부여된 비용(가중치, 길이, 사용 여부) 등의 정보, 미사용 에지 = -1.0 */
	double m_Cost;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	pVert[in]	에지의 시작점에 할당된 정점에 대한 포인터
	*	\param	pTexel[in]	에지의 시작점에 할당된 텍셀에 대한 포인터
	*	\param	pNormal[in] 에지의 시작점에 할당된 법선에 대한 포인터
	*/
	EgEdge(EgVertex *pVert, EgTexel *pTexel, EgNormal *pNormal);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgEdge();

	/*!
	*	\brief	에지를 공유한 삼각형을 구한다.
	*
	*	\param	Faces[out]	삼각형 포인터가 저장된다.
	*
	*	\return 메이트 에지가 있는 경우 2, 메이트 에지가 없는 경우 1이 반환된다.
	*/
	int	GetIncidentFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	에지를 공유한 삼각형을 구한다.
	*
	*	\return 에지를 공유한 삼각형의 리스트를 반환한다.
	*/
	std::vector<EgFace *> GetIncidentFace();

	/*!
	*	\brief	경계 에지 여부를 조사한다.
	*
	*	\return 경계 에지이면 true, 아니면 false를 반환한다.
	*/
	bool IsBndry();

	/*!
	*	\brief	에지가 텍스처 경계 에지인지 조사한다.
	*
	*	\return 텍스처 경계 에지이면 true, 아니면 false를 반환한다.
	*/
	bool IsTexBndry();

	/*!
	*	\brief	에지가 제거 가능한지 검사한다.
	*
	*	\return 에지가 제거가능할 경우 true, 아니면 false를 반환한다.
	*/
	bool IsCollapsible();

	/*!
	*	\brief	삼각형에서 에지가 마주보고 있는 각도(0 ~ 180)를 계산한다.
	*
	*	\param	bRadian[in]		라디안 이면 true, 아니면 false
	*
	*	\return 삼각형에서 에지가 마주보고 있는 각도를 반환한다.
	*/
	double GetAngle(bool bRadian);

	/*!
	*	\brief	에지가 마주보고 있는 각도의 코탄젠트 값을 계산한다.
	*
	*	\param	bPositive[in]	양수 코탄젠트 값을 원할 경우 true, 아니면 false
	*
	*	\return 계산된 코탄젠트 값을 반환한다.
	*/
	double GetCotangent(bool bPositive);

	/*!
	*	\brief	에지의 길이를 구한다.
	*
	*	\return 에지의 길이를 반환한다.
	*/
	double GetLength();

	/*!
	*	\brief	에지 방향으로 법곡률을 구한다.
	*	\note	미검증
	*
	*	\return 계산된 법곡률을 반환한다.
	*/
	double GetNormalCurvature();

	/*!
	*	\brief	에지의 방향 벡터를 반환한다.
	*
	*	\param	bNormalize[in]	방향 벡터를 정규화 하려면 true, 아니면 false
	*
	*	\return 에지의 방향 벡터(시작점-끝점)를 반환한다.
	*/
	EgVec3 GetDir(bool bNormalize);
};

/*!
*	\class	EgFace
*	\brief	메쉬의 삼각형을 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	2018-01-25
*/
class EgFace : public EgObject
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	삼각형이 포함된 메쉬의 포인터를 반환한다.
	*
	*	\return 삼각형이 포함된 메쉬의 포인터를 반환한다.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	월드 좌표계에서 표현된 삼각형의 로컬 좌표계를 반환한다.
	*	\note	로컬 좌표계는 삼각형의 무게 중심에서 정의됨
	*
	*	\return 월드 좌표계에서 표현된 삼각형의 로컬 좌표계를 반환한다.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	삼각형이 속한 메쉬를 편집한다.
	*
	*	\param	EC[in]		편집 좌표계(월드 좌표계 기준)
	*	\param	t[in]		편집될 객체의 이동 변위(편집 좌표계 기준)
	*	\param	q[in]		편집될 객체의 회전 변위(편집 좌표계 기준)
	*	\param	s[in]		편집될 객체의 스케일 변위(편집 좌표계 기준)
	*	\param	bFirst[in]	여러 객체들을 동시에 편집할 경우 첫 번째 객체에 대한 여부
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	편집 중인 삼각형을 렌더링 한다.
	*
	*	\param  r[in]	색상의 red 성분
	*	\param  g[in]	색상의 green 성분
	*	\param  b[in]	색상의 blue 성분
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \brief 삼각형의 인덱스 */
	int m_Idx;

	/*! \brief 삼각형의 시작 에지에 대한 포인터 */
	EgEdge *m_pEdge;

	/*! \brief 삼각형이 사용하는 재질에 대한 포인터 */
	EgMaterial *m_pMaterial;

	/*! \brief 삼각형이 속한 그룹의 이름 */
	std::string m_GroupName;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	e0[in]			삼각형의 첫 번째 에지
	*	\param	e1[in]			삼각형의 두 번째 에지
	*	\param	e2[in]			삼각형의 세 번째 에지
	*	\param	pMtl[in]		삼각형이 사용하는 재질에 대한 포인터
	*	\param	GroupName[in]	삼각형이 속한 그룹의 이름
	*/
	EgFace(EgEdge *e0, EgEdge *e1, EgEdge *e2, EgMaterial *pMtl, std::string GroupName);

	/*!
	*	\brief 생성자
	*
	*	\param v0[in]			삼각형의 첫 번째 정점
	*	\param v1[in]			삼각형의 두 번째 정점
	*	\param v2[in]			삼각형의 세 번째 정점
	*	\param t0[in]			삼각형의 첫 번째 정점의 텍스처 좌표
	*	\param t1[in]			삼각형의 두 번째 정점의 텍스처 좌표
	*	\param t2[in]			삼각형의 세 번째 정점의 텍스처 좌표
	*	\param n0[in]			삼각형의 첫 번째 정점의 법선
	*	\param n1[in]			삼각형의 두 번째 정점의 법선
	*	\param n2[in]			삼각형의 세 번째 정점의 법선
	*	\param pMtl[in]			삼각형이 사용하는 재질에 대한 포인터
	*	\param GroupName[in]	삼각형이 속한 그룹의 이름
	*/
	EgFace(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2,	EgNormal *n0, EgNormal *n1, EgNormal *n2, EgMaterial *pMtl, std::string GroupName);

	/*!
	*	\brief 소멸자
	*/
	virtual ~EgFace();
	
	/*!
	*	\brief	삼각형의 에지 리스트를 반환한다.
	*
	*	\return 삼각형의 에지 리스트를 반환한다.
	*/
	std::vector<EgEdge *> &Edges();

	/*!
	*	\brief	삼각형의 정점 리스트를 반환한다.
	*
	*	\return 삼각형의 정점 리스트를 반환한다.
	*/
	std::vector<EgVertex *> &Verts();

	/*!
	*	\brief	삼각형 정점의 포인터를 반환한다.
	*
	*	\param	vIdx[in]	삼각형을 구성하는 정점의 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응되는 정점의 포인터를 반환한다.
	*/
	EgVertex *GetVertex(int vidx);

	/*!
	*	\brief	삼각형에서 텍스처 정점의 포인터를 반환한다.
	*
	*	\param	tidx[in]	삼각형을 구성하는 텍스처 정점의 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응되는 텍스처 정점의 포인터를 반환한다.
	*/
	EgTexel *GetTexel(int tidx);

	/*!
	*	\brief	삼각형에서 법선의 포인터를 반환한다.
	*
	*	\param	nIdx[in]	삼각형을 구성하는 법선의 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응하는 법선의 포인터를 반환한다.
	*/
	EgNormal *GetNormal(int nidx);
	
	/*!
	*	\brief	삼각형의 에지 포인터를 반환한다.
	*
	*	\param	eIdx[in]	삼각형을 구성하는 에지의 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응되는 에지의 포인터를 반환한다.
	*/
	EgEdge *GetEdge(int eidx);

	/*!
	*	\brief	삼각형에서 정점의 좌표를 반환한다.
	*
	*	\param	vidx[in]	삼각형을 구성하는 정점 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응하는 정점의 좌표를 반환한다.
	*/
	EgPos GetVertexPos(int vidx);

	/*!
	*	\brief	삼각형에서 에지에 할당된 텍스처 좌표를 반환한다.
	*
	*	\param	tidx[in]	삼각형을 구성하는 하프에지 인덱스(0, 1, 2)
	*
	*	\return 인덱스에 대응하는 텍스처 좌표를 반환한다.
	*/
	EgVec2 GetTexelCoord(int tidx);

	/*!
	*	\brief	삼각형에서 하프에지에 할당된 법선의 방향을 반환한다.
	*
	*	\param	nidx[in]	삼각형을 구성하는 하프에지 인덱스(0, 1, 2)
	*	\param	bLocal[in]	객체의 모델링 좌표계에서 표현된 법선일 경우 true, 월드 좌표계에서 표현될 경우 false
	*
	*	\return 인덱스에 대응하는 법선의 방향을 반환한다.
	*/
	EgVec3 GetNormalDir(int nidx, bool bLocal);

	/*!
	*	\brief	삼각형의 단위 법선벡터를 계산한다.
	*
	*	\param	bLocal[in]	객체의 모델링 좌표계에서 표현된 법선일 경우 true, 월드 좌표계에서 표현될 경우 false
	*
	*	\return 삼각형의 단위 법선벡터를 반환한다.
	*/
	EgVec3 GetFaceNormal(bool bLocal);

	/*!
	*	\brief	삼각형을 구성하는 정점의 인덱스 리스트를 반환한다.
	*
	*	\return 삼각형을 구성하는 정점의 인덱스 배열에 대한 포인터를 반환한다.
	*/
	int *GetVertexIdxs();

	/*!
	*	\brief	삼각형을 구성하는 텍스처 정점의 인덱스 리스트를 반환한다.
	*
	*	\return 삼각형을 구성하는 텍스처 정점의 인덱스 배열에 대한 포인터를 반환한다.
	*/
	int *GetTexelIdxs();

	/*!
	*	\brief	삼각형을 구성하는 법선의 인덱스 리스트를 반환한다.
	*
	*	\return 삼각형을 구성하는 법선의 인덱스 배열에 대한 포인터를 반환한다.
	*/
	int *GetNormalIdxs();

	/*!
	*	\brief	삼각형에서 에지의 인덱스를 반환한다.
	*
	*	\param	e[in]	찾을 에지에 대한 포인터
	*
	*	\return 삼각형에서 에지의 인덱스를 반환한다.
	*/
	int GetEdgeIdx(EgEdge *pEdge);

	/*!
	*	\brief	삼각형의 면적을 계산한다.
	*
	*	\return 계산된 면적을 반환한다.
	*/
	double GetArea();

	/*!
	*	\brief	삼각형의 둘레의 길이를 계산한다.
	*
	*	\return	계산된 둘레의 길이를 반환한다.
	*/
	double GetPerimeter();

	/*!
	*	\brief	삼각형의 무게 중심을 계산한다.
	*
	*	\param	bLocal[in]	객체의 모델링 좌표계에서 표현된 경우 true, 월드 좌표계에서 표현될 경우 false
	*
	*	\return 삼각형의 무게 중심의 위치를 반환한다.
	*/
	EgPos GetCOG(bool bLocal);

	/*!
	*	\brief	삼각형 에지를 공유한 삼각형을 구한다.
	*
	*	\param	Faces[out]	에지를 공유한 삼각형의 포인터가 저장된다.
	*
	*	\return 에지를 공유한 삼각형의 개수(0, 1, 2, 3)를 반환한다.
	*/
	int GetAdjacentFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	인접 삼각형 여부를 조사한다.
	*
	*	\param	pFace[in]	조사할 삼각형
	*
	*	\return	인접 삼각형이면 공유 에지의 포인터를 반환하고, 아니면 NULL을 반환한다.
	*/
	EgEdge *IsAdjacentFace(EgFace *pFace);

	/*!
	*	\brief	삼각형이 경계 삼각형인지 조사한다.
	*
	*	\return	경계 삼각형이면 true, 아니면 false를 반환한다.
	*/
	bool IsBndryFace();

	/*!
	*	\brief	고립된 삼각형인지 조사한다.
	*
	*	\return	고립된 삼각형이면 true, 아니면 false를 반환한다.
	*/
	bool IsIsolated();
};

/*!
*	\class	EgTexture
*	\brief	메쉬가 사용하는 텍스처를 표현하는 클래스
*
*	\author 윤승현
*	\date	2018-11-29
*/
class EgTexture
{
	/*!
	*	\brief	1차원 텍스처를 생성한다.
	*	\note	마지막 수정일: 2022-04-21
	*
	*	\param	id[in]	생성할 텍스처의 종류(0: Rainbow, 1: Heat, 2: BYGCR)
	*/
	friend EgTexture *create_texture_1d(int id);

public:
	/*! brief 텍스처의 파일의 이름(확장명 포함) */
	std::string m_FileName;

	/*! brief OpenGL 텍스처가 생성된 경우 아이디(1부터 시작) */
	GLuint m_TexId;

public:
	/*!
	*	\brief 생성자
	*/
	EgTexture();

	/*!
	*	\brief 소멸자
	*/
	~EgTexture();

	/*!
	*	\brief	텍스처 파일로부터 OpenGL 텍스처를 생성한다.
	*
	*	\param	fname[in]	텍스처 파일명
	*
	*	\return 성공이면 true, 실패면 false를 반환한다.
	*/
	bool LoadTexture(const char *fname);
};

/*!
*	\class	EgMaterial
*	\brief	메쉬가 사용하는 재질을 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	2018-07-02
*/
class EgMaterial
{
public:
	/*! \brief 재질의 인덱스 */
	int m_Idx;

	/*! \brief 재질의 이름 */
	std::string m_Name;

	/*! \brief 재질의 주변광 반사 계수 */
	GLfloat m_Ambient[4];

	/*! \brief 재질의 난반사 계수 */
	GLfloat m_Diffuse[4];

	/*! \brief 재질의 전반사 계수 */
	GLfloat m_Specular[4];

	/*! \brief 재질의 전반사 지수 */
	GLfloat m_Shiness;

	/*! \brief 재질이 사용하는 텍스처에 대한 포인터(텍스처는 여러 재질이 공유 할 수 있음) */
	EgTexture *m_pTexture;

public:
	/*!
	*	\brief 생성자
	*
	*	\param Name 생성할 재질의 이름
	*/
	EgMaterial(std::string Name);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사할 재질
	*/
	EgMaterial(const EgMaterial &cpy);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgMaterial();

	/*!
	*	\brief	새로 생성할 객체의 이름을 반환한다.
	*
	*	\return	새로 생성할 객체의 이름을 반환한다.
	*/
	std::string GetNewObjName();

	/*!
	*	\brief	재질의 주변광 반사 계수를 설정한다.
	*
	*	\param	r[in] Red 성분에 대한 반사계수
	*	\param	g[in] Green 성분에 대한 반사계수
	*	\param	b[in] Blue 성분에 대한 반사계수
	*	\param	a[in] Alpha 블렌딩을 위한 알파 값
	*/
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	재질의 난반사 계수를 설정한다.
	*
	*	\param	r[in] Red 성분에 대한 반사계수
	*	\param	g[in] Green 성분에 대한 반사계수
	*	\param	b[in] Blue 성분에 대한 반사계수
	*	\param	a[in] Alpha 블렌딩을 위한 알파 값
	*/
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	재질의 전반사 계수를 설정한다.
	*
	*	\param	r[in] Red 성분에 대한 반사계수
	*	\param	g[in] Green 성분에 대한 반사계수
	*	\param	b[in] Blue 성분에 대한 반사계수
	*	\param	a[in] Alpha 블렌딩을 위한 알파 값
	*/
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	재질의 전반사 지수를 설정한다.
	*
	*	\param	s[in] 재질의 전반사 지수
	*/
	void SetShiness(GLfloat s);

	/*!
	*	\brief	재질의 텍스처를 설정한다.
	*
	*	\param	pTexture[in]	설정할 텍스처에 대한 포인터
	*/
	void SetTexture(EgTexture *pTexture);

	/*!
	*	\brief	재질을 활성화 한다.
	*
	*	\param	bTexture[in]	텍스처 적용 여부
	*/
	void Enable();

	/*!
	*	\brief	재질의 비활성화 한다.
	*/
	void Disable();
};

/*!
*	\class	EgBox
*	\brief	3차원 장면에서 월드 좌표계의 축에 평행한 바운딩 박스를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	2015-01-29
*/
class EgBox
{
public:
	/*! \brief 경계 상자의 대상 메쉬 */
	EgMesh *m_pMesh;

	/*! \brief 경계 상자의 최소점(메쉬의 모델링 좌표계에서 표현) */
	EgPos m_MinPt;

	/*! \brief 경계 상자의 최대점(메쉬의 모델링 좌표계에서 표현) */
	EgPos m_MaxPt;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	minx[in]	경계 상자의 최소점의 x 좌표
	*	\param	miny[in]	경계 상자의 최소점의 y 좌표
	*	\param	minz[in]	경계 상자의 최소점의 z 좌표
	*	\param	maxx[in]	경계 상자의 최대점의 x 좌표
	*	\param	maxy[in]	경계 상자의 최대점의 y 좌표
	*	\param	maxz[in]	경계 상자의 최대점의 z 좌표
	*/
	EgBox(double minx = 0, double miny = 0, double minz = 0, double maxx = 0, double maxy = 0, double maxz = 0);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgBox(const EgBox &cpy);

	/*!
	*	\brief	소멸자
	*/
	~EgBox() {}
	
	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgBox &operator =(const EgBox &rhs);
	
	/*!
	*	\brief	월드 좌표계에서 표현된 경계 상자의 모델링 좌표계를 반환한다.
	*
	*	\return 월드 좌표계에서 표현된 경계 상자의 모델링 좌표계를 반환한다.
	*/
	EgTrans GetMC();

	/*!
	*	\brief	경계상자의 x축 방향의 너비를 반환한다.
	*
	*	\return	경계상자의 x축 방향의 너비를 반환한다.
	*/
	double GetWidth();

	/*!
	*	\brief	경계상자의 y축 방향의 높이를 반환한다.
	*
	*	\return	경계상자의 y축 방향의 높이를 반환한다.
	*/
	double GetHeight();

	/*!
	*	\brief	경계상자의 z축 방향의 깊이를 반환한다.
	*
	*	\return	경계상자의 z축 방향의 깊이를 반환한다.
	*/
	double GetDepth();

	/*!
	*	\brief	경계상자의 대각선의 길이를 반환한다.
	*
	*	\return 경계상자의 대각선의 길이를 반환한다.
	*/
	double GetDiagonal();

	/*!
	*	\brief 경계상자의 8개의 모서리 정점을 반환한다.
	*	\note
	*
	*           (2) *------------* (3)
	*             + |          + |
	*           +   |        +   |
	*     (6) *------------* (7) |
	*         |     |      |     |
	*         | (0) *------|-----* (1)
	*         |   +        |   +
	*         | +          | +
	*     (4) *------------* (5)
	*
	*	\param Pt 경계상자의 8개의 모서리 위치가 저장된다.
	*	\param bLocal 모서리 정점의 좌표계(true: 모델링 좌표계, false: 월드 좌표계)
	*/
	void GetCornerPts(EgPos *Pt, bool bLocal = true);

	/*!
	*	\brief	경계 상자를 렌더링 한다.
	*
	*	\param	r[in]		경계 상자 테두리의 빨간색 성분
	*	\param	g[in]		경계 상자 테두리의 초록색 성분
	*	\param	b[in]		경계 상자 테두리의 파란색 성분
	*	\param	width[in]	경계 상자 테두리의 두께
	*/
	void Render(double r, double g, double b, double width);
};

/*! \brief 메쉬 렌더링 옵션 */
#define RENDER_POLYGON			0x0001
#define RENDER_WIRE				0x0002
#define RENDER_POINT			0x0004
#define RENDER_NORMAL			0x0008
#define RENDER_BACK_FACE		0x0010
#define RENDER_TEXTURE			0X0020

/*! \brief 메쉬 법선 속성 옵션 */
enum TypeNormal
{
	NORMAL_ASIS = 0,
	NORMAL_FACE = 1,
	NORMAL_VERTEX = 2,
};

/*!
*	\class	EgMesh
*	\brief	삼각 메쉬를 표현하는 클래스
*
*	\author 박정호, 윤승현
*	\date	2018-01-25
*/
class EgMesh : public EgObject
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	새로 생성되는 객체의 이름을 반환한다.
	*
	*	\return 새로 생성되는 객체의 이름을 반환한다.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	자신을 복사한다.
	*
	*	\return 자신을 복사한 객체의 포인터를 반환한다.
	*/
	virtual EgMesh *CopyObject();

	/*!
	*	\brief	객체가 포함된 메쉬의 포인터를 반환한다.
	*
	*	\return 객체가 포함된 메쉬의 포인터를 반환한다.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	월드 좌표계에서 표현된 메쉬의 로컬 좌표계를 반환한다.
	*
	*	\return 월드 좌표계에서 표현된 메쉬의 로컬 좌표계를 반환한다.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	메쉬를 편집한다.
	*
	*	\param	EC[in]		편집 좌표계(월드 좌표계 기준)
	*	\param	t[in]		편집 이동 변위(편집 좌표계 기준)
	*	\param	q[in]		편집 회전 변위(편집 좌표계 기준)
	*	\param	s[in]		편집 스케일 변위(편집 좌표계 기준)
	*	\param	bFirst[in]	여러 객체들을 동시에 편집할 경우 첫 번째 객체에 대한 여부
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	메쉬의 모델링 좌표계를 변경한다.
	*
	*	\param	Type[in]	변경될 모델링 좌표계의 타입(0: 월드 좌표계, 1: AABB, 2: OBB)
	*/
	virtual void UpdateMC(int Type);

	/*!
	*	\brief	편집 중인 메쉬를 렌더링 한다.
	*
	*	\param  r[in]	색상의 red 성분
	*	\param  g[in]	색상의 green 성분
	*	\param  b[in]	색상의 blue 성분
	*/
	virtual void RenderForEdit(float r, float g, float b);

	/*!
	*	\brief 메쉬를 렌더링 한다.
	*/
	virtual void Render();

public:
	/*! \brief 메쉬의 이름 */
	std::string m_Name;

	/*! \brief 메쉬가 정의된 모델링 좌표계 */
	EgTrans m_MC;

	/*! \brief 정점의 포인터 배열 */
	std::vector<EgVertex *> m_pVerts;

	/*! \brief 텍스처 정점의 포인터 배열 */
	std::vector<EgTexel *> m_pTexels;

	/*! \brief 법선의 포인터 배열 */
	std::vector<EgNormal *> m_pNormals;

	/*! \brief 삼각형의 포인터 배열 */
	std::vector<EgFace *> m_pFaces;

	/*! \brief 재질의 포인터 배열 */
	std::vector<EgMaterial *> m_pMaterials;

	/*! \brief 텍스처의 포인터 배열(여러 재질이 공유 가능) */
	std::vector<EgTexture *> m_pTextures;

	/*! \brief 모델링 좌표계에서 표현된 메쉬의 경계 상자 */
	EgBox m_BndBox;

	/*! \brief 렌더링 옵션: RENDER_POLYGON, RENDER_WIRE, ... */
	unsigned int m_RenderOption;

	/*! \brief 메쉬의 법선 타입: NORMAL_FACE 또는 NORMAL_VERTEX */
	TypeNormal m_NormalType;

	/*! \brief 고속 렌더링을 위한 정점 버퍼: (재질명, 정점의 좌표 배열)로 구성됨 */
	std::map<std::string, std::vector<float>> m_VertexBuf;

	/*! \brief 고속 렌더링을 위한 텍스처 좌표 버퍼: (재질명, 텍스처 좌표 배열)로 구성됨 */
	std::map<std::string, std::vector<float>> m_TexelBuf;

	/*! \brief 고속 렌더링을 위한 법선 버퍼: (재질명, 법선의 좌표 배열)로 구성됨 */
	std::map<std::string, std::vector<float>> m_NormalBuf;

	/*! \brief 삼각형 아이디로 렌더링된 디스플레이 리스트 */
	GLuint m_DisplayListOfFaceId;

	/*! \brief 메쉬의 분석 결과로 렌더링된 디스플레이 리스트((측지)거리장, Isophotic 거리장, 에지 거리장, 위상 거리장, 측지거리그래디언트장) */
	GLuint m_DisplayListOfAnalysis;

protected:
	/*!
	*	\brief	인덱스가 -1인 메쉬의 삼각형을 제거한다.
	*	\note	(1) 삼각형 제거 과정에서 생긴 사용되지 않는 정점/텍셀/법선은 제거되지 않는다.
	*			(2) 남은 정점/텍셀/법선을 제거하기 위해서는 delete_unused_*() 함수를 추가로 호출해야 한다.
	*			(3) 마지막 수정일: 2021-02-17
	*	\return 남은 삼각형의 수를 반환한다.
	*/
	int DeleteFaces();

	/*!
	*	\brief	메쉬의 모든 내부 정보를 제거한다.
	*	\note	마지막 수정일: 2021-02-17
	*/
	void DeleteMesh();

	/*!
	*	\brief	정점 버퍼를 갱신한다.
	*/
	void UpdateVertexBuf();

	/*!
	*	\brief	텍스처 버퍼를 갱신한다.
	*/
	void UpdateTexelBuf();

	/*!
	*	\brief	법선 버퍼를 갱신한다.
	*/
	void UpdateNormalBuf();
	

public:
	/*!
	*	\brief	생성자
	*
	*	\param	Name[in]	생성할 메쉬의 이름
	*/
	EgMesh(std::string Name = "");

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 메쉬 객체
	*/
	EgMesh(const EgMesh &cpy);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgMesh();

	/*!
	*	\brief	메쉬에 정점을 추가한다.
	*
	*	\param	pVert[in]	추가할 정점에 대한 포인터
	*/
	void AddVertex(EgVertex *pVert);

	/*!
	*	\brief	메쉬에 텍셀을 추가한다.
	*
	*	\param	pTexel[in]	추가할 텍셀에 대한 포인터
	*/
	void AddTexel(EgTexel *pTexel);

	/*!
	*	\brief	메쉬에 법선을 추가한다.
	*
	*	\param	pNormal[in]		추가할 법선에 대한 포인터
	*/
	void AddNormal(EgNormal *pNormal);

	/*!
	*	\brief	메쉬에 삼각형을 추가한다.
	*
	*	\param	pFace[in]	추가할 삼각형에 대한 포인터
	*/
	void AddFace(EgFace *pFace);

	/*!
	*	\brief	메쉬에 재질을 추가한다.
	*
	*	\param	pMaterial[in]	추가할 재질에 대한 포인터
	*/
	void AddMaterial(EgMaterial *pMaterial);

	/*!
	*	\brief	메쉬의 삼각형을 제거한다.
	*	\note	(1) 삼각형 제거 과정에서 생긴 사용되지 않는 정점/텍셀/법선은 제거되지 않는다.
	*			(2) 남은 정점/텍셀/법선을 제거하기 위해서는 delete_unused_*() 함수를 추가로 호출해야 한다.
	*			(3) 마지막 수정일: 2021-02-17
	*
	*	\param	Faces[in]	제거할 삼각형 리스트
	*
	*	\return 남은 삼각형의 수를 반환한다.
	*/
	int DeleteFaces(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	메쉬 정점들을 제거한다.
	*	\note	(1) 정점이 포함된 삼각형들도 함께 제거된다.
	*			(2) 정점 제거 과정에서 생긴 사용되지 않는 텍셀/법선은 제거되지 않는다.
	*			(3) 남은 텍셀/법선을 제거하기 위해서는 delete_unused_*() 함수를 추가로 호출해야 한다.
	*			(4) 마지막 수정일: 2021-02-17
	*
	*	\param	Verts[in]	제거할 정점의 리스트
	*
	*	\return 남은 정점의 개수를 반환한다.
	*/
	int DeleteVerts(std::vector<EgVertex *> &Verts);

	/*!
	*	\brief	메쉬의 에지를 제거한다.
	*	\note	(1) 에지가 포함된 삼각형들도 함께 제거된다.
	*			(2) 에지 제거 과정에서 생긴 사용되지 않는 정점/텍셀/법선은 제거되지 않는다.
	*			(3) 남은 정점/텍셀/법선을 제거하기 위해서는 delete_unused_*() 함수를 추가로 호출해야 한다.
	*			(4) 마지막 수정일: 2021-01-08
	*
	*	\param	pEdges[in]		제거할 에지 리스트
	*
	*	\return 남은 삼각형의 수를 반환한다.
	*/
	int DeleteEdges(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	메쉬의 에지 길이를 계산하여 m_Cost 변수에 기록한다.
	*
	*	\param	MetricType[in]	거리 함수 타입(0: 등방, 1: 비등방(최소 주곡률 방향을 짧게), 2: 비등방(최소 주곡률 방향을 길게))
	*/
	void UpdateEdgeLength(int MetricType = 0);

	/*!
	*	\brief	에지의 반대편 에지 정보를 갱신한다.

	*	\param	pVert[in]	정점의 포인터
	*/
	void UpdateEdgeMate(EgVertex *pVert = NULL);

	/*!
	*	\brief	기존의 법선 리스트를 무조건 제거하고, 새로운 m_pNormals을 구성한다.
	*	\note	마지막 수정일: 2021-04-16
	*
	*	\param	NormalType[in]	법선의 형태(NORMAL_ASIS: 기존, NORMAL_FACE: 삼각형 법선, NORMAL_VERTEX: 정점 법선)
	*/
	void UpdateNormal(TypeNormal NormalType = NORMAL_ASIS);

	/*!
	*	\brief	메쉬 선택 영역의 법선을 갱신한다.
	*
	*	\param	Faces[in]	선택 영역의 삼각형의 리스트
	*/
	void UpdateNormal(const std::vector<EgFace *> &Faces);

	/*!
	*	\brief	메쉬 선택 영역의 법선을 갱신한다.
	*
	*	\param	Verts[in]	선택 영역의 정점의 리스트
	*/
	void UpdateNormal(const std::vector<EgVertex *> &Verts);

	/*!
	*	\brief	메쉬의 법선을 거꾸로 바꾼다.
	*/
	void ReverseNormal();

	/*!
	*	\brief	메쉬를 둘러싸는 경계 상자를 갱신한다.
	*/
	void UpdateBndBox();

	/*!
	*	\brief 메쉬의 크기를 대각선 기준으로 정규화 한다.
	*/
	void Normalize();

	/*!
	*	\brief	메쉬 정점의 인덱스(0, 1, 2, ...)를 갱신한다.
	*
	*	\return 정점의 개수를 반환한다.
	*/
	int UpdateVertIdx();

	/*!
	*	\brief	메쉬에서 텍셀의 인덱스를 갱신한다
	*
	*	\return 텍셀의 개수를 반환한다.
	*/
	int UpdateTexIdx();

	/*!
	*	\brief	메쉬에서 법선의 인덱스를 갱신한다
	*
	*	\return 법선의 개수를 반환한다.
	*/
	int UpdateNormalIdx();

	/*!
	*	\brief	메쉬에서 삼각형의 인덱스를 갱신한다.
	*
	*	\return 삼각형의 개수를 반환한다.
	*/
	int UpdateFaceIdx();

	/*!
	*	\brief	메쉬에서 재질의 인덱스를 갱신한다.
	*
	*	\return 재질의 개수를 반환한다.
	*/
	int UpdateMaterialIdx();

	/*!
	*	\brief	메쉬의 정점의 개수를 반환한다.
	*
	*	\return 메쉬의 정점의 개수를 반환한다.
	*/
	int GetNumVert();

	/*!
	*	\brief	메쉬의 텍셀의 개수를 반환한다.
	*
	*	\return 메쉬의 텍셀의 개수를 반환한다.
	*/
	int GetNumTexel();

	/*!
	*	\brief	메쉬의 법선의 개수를 반환한다.
	*
	*	\return 메쉬의 법선의 개수를 반환한다.
	*/
	int GetNumNormal();

	/*!
	*	\brief	메쉬의 삼각형의 개수를 반환한다.
	*
	*	\return 메쉬의 삼각형의 개수를 반환한다.
	*/
	int GetNumFace();

	/*!
	*	\brief	메쉬의 재질의 개수를 반환한다.
	*
	*	\return 메쉬의 재질의 개수를 반환한다.
	*/
	int GetNumMtrl();

	/*!
	*	\brief	메쉬의 텍스처 사용 여부를 조사한다.
	*
	*	\return 메쉬가 텍스처를 사용하면 true, 아니면 false를 반환한다.
	*/
	bool HasTexture();

	/*!
	*	\brief	메쉬를 구성하는 정점 리스트를 반환한다.
	*
	*	\return 메쉬를 구성하는 정점 리스트를 반환한다.
	*/
	std::vector<EgVertex *> &Verts() { return m_pVerts; }

	/*!
	*	\brief	메쉬를 구성하는 텍셀 리스트를 반환한다.
	*
	*	\return 메쉬를 구성하는 텍셀 리스트를 반환한다.
	*/
	std::vector<EgTexel *> &Texels() { return m_pTexels; };

	/*!
	*	\brief	메쉬를 구성하는 법선 리스트를 반환한다.
	*
	*	\return 메쉬를 구성하는 법선 리스트를 반환한다.
	*/
	std::vector<EgNormal *> &Normals() { return m_pNormals; }

	/*!
	*	\brief	메쉬를 구성하는 삼각형 리스트를 반환한다.
	*
	*	\return 메쉬를 구성하는 삼각형 리스트를 반환한다.
	*/
	std::vector<EgFace *> &Faces() { return m_pFaces; }	

	/*!
	*	\brief	메쉬를 구성하는 에지의 최소 길이를 구한다.
	*
	*	\return 에지의 최소 길이를 반환한다.
	*/
	double GetMinEdgeLen();

	/*!
	*	\brief	메쉬를 구성하는 에지의 최대 길이를 구한다.
	*
	*	\return 에지의 최대 길이를 반환한다.
	*/
	double GetMaxEdgeLen();	

	/*!
	*	\brief	메쉬를 구성하는 에지의 평균 길이를 구한다.
	*
	*	\return 에지의 평균 길이를 반환한다.
	*/
	double GetAvgEdgeLen();

	/*!
	*	\brief	메쉬 법선 벡터의 리스트를 구한다.
	*
	*	\param	Normals[out]	법선 벡터들이 저장된다.
	*	\param	Type[in]		법선 벡터의 타입(0: 정점, 1: 삼각형)
	*/
	void GetNormalArray(std::vector<EgVec3> &Normals, int Type);

	/*!
	*	\brief	메쉬의 Idx번째 정점의 포인터를 찾는다.
	*
	*	\param	Idx[in]		정점의 인덱스(0부터 시작)
	*
	*	\return 메쉬의 Idx번째 정점의 포인터를 반환한다.
	*/
	EgVertex *GetVert(int Idx);

	/*!
	*	\brief	메쉬의 Idx번째 텍셀의 포인터를 찾는다.
	*
	*	\param	Idx[in]		텍셀의 인덱스(0부터 시작)
	*
	*	\return 메쉬의 Idx번째 텍셀의 포인터를 반환한다.
	*/
	EgTexel *GetTexel(int Idx);

	/*!
	*	\brief	메쉬의 Idx번째 법선의 포인터를 찾는다.
	*
	*	\param	Idx[in]		법선의 인덱스(0부터 시작)
	*
	*	\return 메쉬의 Idx번째 법선의 포인터를 반환한다.
	*/
	EgNormal *GetNormal(int Idx);

	/*!
	*	\brief	메쉬의 Idx번째 삼각형의 포인터를 찾는다.
	*
	*	\param	Idx[in]		삼각형의 인덱스(0부터 시작)
	*
	*	\return 메쉬의 Idx번째 삼각형의 포인터를 반환한다.
	*/
	EgFace *GetFace(int Idx);

	/*!
	*	\brief	메쉬의 Idx 번째 재질을 찾는다.
	*
	*	\param	Idx[in]		재질의 인덱스
	*
	*	\return Idx 번째 재질의 포인터를 반환한다.
	*/
	EgMaterial *GetMaterial(int Idx);

	/*!
	*	\brief	주어진 이름을 갖는 재질을 찾는다.
	*
	*	\param	Name[in]	재질의 이름
	*
	*	\return 주어진 이름을 갖는 재질의 포인터를 반환한다.
	*/
	EgMaterial *GetMaterial(std::string Name);

	/*!
	*	\brief	주어진 이름을 갖는 텍스처를 찾는다.
	*
	*	\param	Name[in]	텍스처 파일명
	*
	*	\return 주어진 이름을 갖는 텍스처의 포인터를 반환한다.
	*/
	EgTexture *GetTexture(std::string Name);

	/*!
	*	\brief	메쉬를 삼각형으로 렌더링 한다.
	*	\note	정점, 노말 버퍼를 사용한다.
	*/
	void RenderPolygon();

	/*!
	*	\brief	메쉬를 텍스처로 렌더링 한다
	*	\note	정점, 노말, 텍스처 버퍼를 사용한다.
	*/
	void RenderTexture();

	/*!
	*	\brief	정점의 색상으로 모델을 렌더링한다.
	*/
	void RenderVertColor();

	/*!
	*	\brief	메쉬의 정점을 렌더링 한다.
	*/
	void RenderPoint();

	/*!
	*	\brief	메쉬를 와이어프레임으로 렌더링 한다.
	*	\note	정점 버퍼를 사용한다.
	*/
	void RenderWire();

	/*!
	*	\brief	메쉬의 삼각형에 새로운 재질을 설정한다.
	*
	*	\param	pMtl[in]	재질에 대한 포인터
	*/
	void SetMaterial(EgMaterial *pMtl);

	/*!
	*	\brief	메쉬 재질의 투명도를 설정한다.
	*
	*	\param	Alpha[in]	설정할 투명도
	*/
	void SetTransparent(GLfloat Alpha);
	
	/*!
	*	\brief 정점의 국소 영역을 렌더링하는 디스플레이 리스트를 생성한다.
	*/
	void CreateDisplayListOfLocalRegion();

	/*!
	*	\brief	메쉬 위의 스칼라 장을 가시화하는 디스플레이 리스트를 생성한다.
	*
	*	\param	Values[in]			Values[i]에 i번째 정점에 할당된 스칼라 값이 저장됨
	*	\param	Min[in]				조사할 최소값(0으로 매핑)
	*	\param	Max[in]				조사할 최대값(1로 매핑)
	*	\param	ColorMapId[in]		사용할 칼라맵 아이디(0: rainbow, 1: heat, 2: B-Y-G-C-B)
	*	\param	NumIsoLines[in]		Iso-line의 수
	*	\param	IsoColor[in]		Iso-line의 색상
	*/
	void CreateDisplayListOfScalarField(std::vector<double> Values, double Min, double Max, int ColorMapId, int NumIsoLines, EgVec3 IsoColor);

	/*!
	*	\brief	메쉬 위의 벡터장을 가시화하는 디스플레이 리스트를 생성한다.
	*
	*	\param	Values[in]		Values[i]에 i번째 정점 또는 삼각형에 할당된 벡터가 저장됨
	*	\param	bFace[in]		벡터장이 삼각형별로 정의되었으면 true, 정점별로 정의되었으면 false
	*	\param	StColor[in]		벡터 시작점의 색상
	*	\param	EdColor[in]		벡터 끝점의 색상
	*/
	void CreateDisplayListOfVectorField(std::vector<EgVec3> Values, bool bFace, EgVec3 StColor, EgVec3 EdColor);

	/*!
	*	\brief	메쉬 위의 벡터장을 가시화하는 디스플레이 리스트를 생성한다.
	*	\note	마지막 수정일: 2021-06-13
	*
	*	\param	VF1[in]			VF1[i]에 i번째 정점 또는 삼각형에 할당된 첫 번째 벡터가 저장됨
	*	\param	VF2[in]			VF2[i]에 i번째 정점 또는 삼각형에 할당된 두 번째 벡터가 저장됨
	*	\param	bFace[in]		벡터장이 삼각형별로 정의되었으면 true, 정점별로 정의되었으면 false
	*	\param	StColor1[in]	첫 번째 벡터장의 벡터 시작점의 색상
	*	\param	EdColor1[in]	첫 번째 벡터장의 벡터 끝점의 색상
	*	\param	StColor2[in]	첫 번째 벡터장의 벡터 시작점의 색상
	*	\param	EdColor2[in]	첫 번째 벡터장의 벡터 끝점의 색상
	*/
	void CreateDisplayListOfVectorField(std::vector<EgVec3> &v1, std::vector<EgVec3> &v2, bool bFace, EgVec3 StColor1, EgVec3 EdColor1, EgVec3 StColor2, EgVec3 EdColor2);

	/*!
	*	\brief	정점에 할당된 스칼라 값의 Iso-line을 렌더링하는 디스플레이 리스트를 제거한다.
	*	\note	마지막 수정일: 2020-11-03
	*
	*	\param	Values[in]			Values[i]에 i번째 정점에 할당된 스칼라 값이 저장됨
	*	\param	MinVal[in]			조사할 Isovalue의 최소값
	*	\param	MaxVal[in]			조사할 Isovalue의 최대값
	*	\param	NumIsoValues[in]	라인을 생성할 Iso-value의 수
	*/
	void CreateDisplayListOfIsoLines(std::vector<double> &Values, double MinVal, double MaxVal, int NumIsoVal);

	/*!
	*	\brief	메쉬 분석의 결과를 렌더링하는 디스플레이 리스트를 제거한다.
	*/
	void DeleteDisplayListOfAnalysis();
};

/*! \brief 메쉬 위의 점의 위치 타입 열거형 */
enum TypeMeshPt
{
	PT_ON_V0 = 0,	// 정점 V0 위에 놓인 점
	PT_ON_V1 = 1,	// 정점 V1 위에 놓인 점
	PT_ON_V2 = 2,	// 정점 V2 위에 놓인 점
	PT_ON_E0 = 3,	// 시작점이 V0인 에지 위에 놓인 점
	PT_ON_E1 = 4,	// 시작점이 V1인 에지 위에 놓인 점
	PT_ON_E2 = 5,	// 시작점이 V2인 에지 위에 놓인 점
	PT_IN_TRI = 6,	// 삼각형 내부점
	PT_OUT_TRI = 7,	// 삼각형 외부점
	PT_UNKNOWN,
};

/*!
*	\class  EgMeshPt
*	\brief  메쉬 위의 점을 표현하는 클래스
*
*	\author 하유진, 윤승현
*	\date	2020-12-30
*/
class EgMeshPt : public EgObject
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	점이 포함된 메쉬의 포인터를 반환한다.
	*
	*	\return 점이 포함된 메쉬의 포인터를 반환한다.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	월드 좌표계에서 표현된 점의 로컬 좌표계를 반환한다.
	*
	*	\return	월드 좌표계에서 표현된 점의 로컬 좌표계를 반환한다.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	점을 포함한 삼각형을 편집한다.
	*
	*	\param	EC[in]		편집 좌표계(월드 좌표계 기준)
	*	\param	t[in]		편집 이동 변위(편집 좌표계 기준)
	*	\param	q[in]		편집 회전 변위(편집 좌표계 기준)
	*	\param	s[in]		편집 스케일 변위(편집 좌표계 기준)
	*	\param	bFirst[in]	여러 객체들을 동시에 편집할 경우 첫 번째 객체에 대한 여부
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	편집 중인 점을 렌더링 한다.
	*
	*	\param	r[in]	색상의 red 성분
	*	\param	g[in]	색상의 green 성분
	*	\param	b[in]	색상의 blue 성분
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \biref 점이 놓인 삼각형에 대한 포인터 */
	EgFace *m_pFace;

	/*! \biref 점이 놓인 삼각형에서 표현된 barycentric 좌표 */
	EgVec3 m_Coords;

	/*! \biref 점의 위치 타입 */
	TypeMeshPt m_PtType;

public:
	/*!
	*	\brief	디폴트 생성자
	*/
	EgMeshPt();

	/*!
	*	\brief	생성자
	*
	*	\param	pVert[in]	메쉬 정점
	*/
	EgMeshPt(EgVertex *pVert);

	/*!
	*	\brief	생성자
	*
	*	\param	pFace[in]	점을 포함한 삼각형에 대한 포인터
	*	\param	Pos[in]		점의 3차원 좌표
	*/
	EgMeshPt(EgFace *pFace, EgPos Pos);

	/*!
	*	\brief	생성자
	*
	*	\param	pFace[in]	점을 포함한 삼각형에 대한 포인터
	*	\param	Coords[in]	삼각형 기준 점의 barycentric 좌표
	*/
	EgMeshPt(EgFace *pFace, EgVec3 Coords);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgMeshPt(const EgMeshPt &cpy);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgMeshPt();

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgMeshPt &operator =(const EgMeshPt &rhs);

	/*!
	*	\brief	모델 좌표계에서 표현된 점의 좌표를 반환한다.
	*
	*	\return 모델 좌표계에서 표현된 점의 좌표를 반환한다.
	*/
	EgPos Pos();

	/*!
	*	\brief	점을 초기화 한다.
	*/
	void Reset();

	/*!
	*	\brief	대상 메쉬의 삼각형을 조사하여 점의 위치를 설정한다.
	*
	*	\param	pMesh[in]	대상 메쉬
	*	\param	Pos[in]		입력 점의 좌표
	*
	*	\return	입력 점이 메쉬 위의 점이면 true, 아니면 false를 반환한다.
	*/
	bool Set(EgMesh *pMesh, EgPos Pos);

	/*!
	*	\brief	점의 위치를 설정한다.
	*
	*	\param	pFace[in]	점이 포함된 삼각형
	*	\param	Pos[in]		점의 3차원 좌표
	*/
	void Set(EgFace *pFace, EgPos Pos);

	/*!
	*	\brief	점의 위치를 설정한다.
	*
	*	\param	pFace[in]	점이 포함된 삼각형
	*	\param	Coords[in]	삼각형 기준으로 표현된 점의 Barycentric 좌표
	*/
	void Set(EgFace *pFace, EgVec3 Coords);

	/*!
	*	\brief	점의 위치를 조사하여 m_PtType에 설정한다.
	*/
	void LocatePt();

	/*!
	*	\brief	메쉬 위의 점이 정점인지 조사한다.
	*
	*	\return 정점이라면 true, 아니면 false를 반환한다.
	*/
	bool IsOnVertex();

	/*!
	*	\brief	메쉬 위의 점이 에지 위의 점인지 조사한다.
	*
	*	\return 에지 위의 점이라면 true, 아니면 false를 반환한다.
	*/
	bool IsOnEdge();

	/*!
	*	\brief	메쉬 위의 점이 삼각형 내부점인지 조사한다.
	*
	*	\return 삼각형 내부점이라면 true, 아니면 false를 반환한다.
	*/
	bool IsInFace();

	/*!
	*	\brief	메쉬 위의 점이 삼각형 외부점인지 조사한다.
	*
	*	\return 삼각형 외부점이라면 true, 아니면 false를 반환한다.
	*/
	bool IsOutFace();

	/*!
	*	\brief	삼각형 정점까지의 거리를 계산한다.
	*
	*	\param	vidx[in]	삼각형 정점의 인덱스
	*
	*	\return 계산된 거리를 반환한다.
	*/
	double GetDist2Vert(int vidx);

	/*!
	*	\brief	점을 통과하는 에지를 구한다.
	*
	*	\return 점을 통과하는 에지를 반환하고, 점이 에지 위에 없으면 NULL을 반환한다.
	*/
	EgEdge *GetEdgeOverPt();

	/*!
	*	\brief	삼각형의 가장 가까운 정점을 찾는다.
	*
	*	\return 삼각형의 가장 가까운 정점의 포인터를 반환한다.
	*/
	EgVertex *GetClosestVert();

	/*!
	*	\brief	메쉬 위의 점과 인접한 삼각형을 구한다.
	*
	*	\param	Faces[out]		인접한 삼각형이 저장된다.
	*
	*	\return 인접한 삼각형의 수를 반환한다.
	*/
	int	GetAdjacentFaces(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	메쉬 위의 두 점이 같은지 조사한다.
	*
	*	\param	p[in]	첫 번째 점
	*	\param	q[in]	두 번째 점
	*
	*	\return 두 점이 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgMeshPt &p, const EgMeshPt &q);

	/*!
	*	\brief	메쉬 위의 두 점이 다른지 조사한다.
	*
	*	\param	p[in]	첫 번째 점
	*	\param	q[in]	두 번째 점
	*
	*	\return 두 점이 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgMeshPt &p, const EgMeshPt &q);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	p[in]		출력할 메쉬 위의 점
	*
	*	\return 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgMeshPt &p);
};

/*!
*	\class	EgMeshVec
*	\brief	메쉬 위의 놓이 벡터(Straightest Geodesic)를 표현하는 클래스
*
*	\author 하유진, 윤승현
*	\date	2020-12-03
*/
class EgMeshVec
{
public:
	/*! \biref 벡터의 시작점 */
	EgMeshPt m_Pt;

	/*! \biref 벡터의 방향과 길이 */
	EgVec3 m_Dir;

public:
	/*!
	*	\brief	디폴트 생성자
	*/
	EgMeshVec();

	/*!
	*	\brief	생성자
	*
	*	\param	Pt[in]		벡터의 시작점
	*	\param	Dir[in]		벡터의 방향과 길이
	*/
	EgMeshVec(EgMeshPt Pt, EgVec3 Dir);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgMeshVec(const EgMeshVec &cpy);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgMeshVec();

	/*!
	*	\brief	메쉬 위의 벡터의 길이를 반환한다.
	*
	*	\return	메쉬 위의 벡터의 길이를 반환한다.
	*/
	double GetLength();

	/*!
	*	\brief	벡터의 시작점을 반환한다.
	*
	*	\return	벡터의 시작점을 반환한다.
	*/
	EgMeshPt GetStartPt();

	/*!
	*	\brief	벡터의 끝점을 구한다.
	*
	*	\return	벡터의 끝점을 반환한다.
	*/
	EgMeshPt GetEndPt();

	/*!
	*	\brief	메쉬 위의 벡터의 경로와 끝점을 구한다.
	*
	*	\param	Path[out]	벡터의 시작점에서 끝점까지의 경로가 저장된다.
	*
	*	\return	메쉬 위의 벡터의 끝점을 반환한다.
	*/
	EgMeshPt GetPath(std::vector<EgPos> &Path);

	/*!
	*	\brief	+ 단항 연산자
	*
	*	\return 동일부호를 갖는 객체를 반환한다.
	*/
	EgMeshVec operator +();

	/*!
	*	\brief	- 단항 연산자
	*
	*	\return 반대부호를 갖는 객체를 반환한다.
	*/
	EgMeshVec operator -();

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 상수배된 자신을 반환한다.
	*/
	EgMeshVec &operator *=(const double &s);

	/*!
	*	\brief	벡터를 상수로 나눈다
	*
	*	\param	s[in]	상수
	*
	*	\return 상수로 나주어진 자신을 반환한다.
	*/
	EgMeshVec &operator /=(const double &s);

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return	대입된 자신을 반환한다.
	*/
	EgMeshVec &operator =(const EgMeshVec &rhs);

	/*!
	*	\brief	자신에서 다른 벡터를 더한다.
	*	\note	마지막 수정일: 2021-01-21
	*
	*	\param	rhs[in]		피연산자 객체
	*
	*	\return	변경된 자신을 반환한다.
	*/
	EgMeshVec &operator +=(const EgMeshVec &rhs);

	/*!
	*	\brief	자신에서 다른 벡터를 뺀다.
	*
	*	\param	rhs[in]		피연산자 객체
	*
	*	\return	변경된 자신을 반환한다.
	*/
	EgMeshVec &operator -=(const EgMeshVec &rhs);

	/*!
	*	\brief	메쉬 위의 두 벡터가 같은지 체크한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return	두 벡터의 시작점과 방향이 같으면 true, 아니면 false를 반환한다.
	*/
	friend bool operator ==(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	메쉬 위의 두 벡터가 다른지 체크한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return	두 벡터가 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	메쉬 위의 두 점을 뺀다.
	*	\note	마지막 수정일: 2021-07-04
	*	\note	결과 벡터 v = p - q 이지만, q + v = p가 아닐 수도 있음
	*
	*	\param	p[in]	첫 번째 점
	*	\param	q[in]	두 번째 점
	*
	*	\return	점 q에서 점 p로 향하는 메쉬 위의 벡터 v를 반환한다.
	*/
	friend EgMeshVec operator -(EgMeshPt &p, EgMeshPt &q);

	/*!
	*	\brief	메쉬 위의 점에 벡터를 더한다.
	*	\note	마지막 수정일: 2021-01-14
	*
	*	\param	p[in]	메쉬 위의 점
	*	\param	v[in]	더할 벡터
	*
	*	\return	점 p에서 벡터 v를 더한 메쉬 위의 점을 반환한다.
	*/
	friend EgMeshPt operator +(EgMeshPt &p, EgMeshVec &v);

	/*!
	*	\brief	메쉬 위의 점에 벡터를 더한다.
	*
	*	\param	v[in]	더할 벡터
	*	\param	p[in]	메쉬 위의 점
	*
	*	\return	점 p에서 벡터 v를 더한 메쉬 위의 점을 반환한다.
	*/
	friend EgMeshPt operator +(EgMeshVec &v, EgMeshPt &p);

	/*!
	*	\brief	메쉬 위의 점에 벡터를 뺀다.
	*
	*	\param	p[in]	메쉬 위의 점
	*	\param	v[in]	뺄 벡터
	*
	*	\return	점 p에서 벡터 v를 더한 메쉬 위의 점을 반환한다.
	*/
	friend EgMeshPt operator -(EgMeshPt &p, EgMeshVec &v);

	/*!
	*	\brief	메쉬 위의 두 벡터를 더한다.
	*	\note	두 벡터의 시작 위치가 다르면 두 번째 벡터를 첫 번째 벡터의 시작 위치로 평행 이동시킨다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return	두 벡터의 합을 반환한다.
	*/
	friend EgMeshVec operator +(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	메쉬 위의 두 벡터를 뺀다.
	*	\note	두 벡터의 시작 위치가 다르면 두 번째 벡터를 첫 번째 벡터의 시작 위치로 평행 이동시킨다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return	두 벡터의 차를 반환한다.
	*/
	friend EgMeshVec operator -(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgMeshVec operator *(EgMeshVec &v, const double &s);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgMeshVec operator *(const double &s, EgMeshVec &v);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 상수로 나눈 벡터를 반환한다.
	*/
	friend EgMeshVec operator /(EgMeshVec &v, double s);

	/*!
	*	\brief	두 벡터의 내적을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 내적을 반환한다.
	*/
	friend double operator *(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	v[in]		출력할 메쉬 위의 벡터
	*
	*	\return 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgMeshVec &v);
};

/*!
*	\class	EgPolyline
*	\brief	3차원 공간의 폴리라인을 표현하는 클래스
*
*	\author	하유진
*/
class EgPolyline : public EgMesh
{
public:
	/*!
	*	\brief	객체의 클래스 이름을 반환한다.
	*
	*	\return 객체의 클래스 이름을 반환한다.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	새로 생성되는 객체의 이름을 반환한다.
	*
	*	\return 새로 생성되는 객체의 이름을 반환한다.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	폴리라인을 렌더링 한다.
	*/
	virtual void Render();

public:
	/*! \brief	닫힌 폴리라인 여부 */
	bool m_bClosed;

	/*! \brief	폴리라인의 색상 */
	EgVec3 m_Color;

	/*! \brief	폴리라인의 두께 */
	double m_Width;

public:
	/*!
	*	\brief	생성자
	*/
	EgPolyline();

	/*!
	*	\brief	생성자
	*
	*	\param	PtList[in]		폴리라인을 구성하는 정점의 리스트
	*	\param	bClosed[in]		닫힌 폴라라인 여부
	*	\param	Color[in]		폴리라인의 색상
	*	\param	Width[in]		폴리라인의 두께
	*/
	EgPolyline(std::vector<EgPos> &PtList, bool bClosed, EgVec3 Color, double Width);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgPolyline(const EgPolyline &cpy);

	/*!
	*	\brief	소멸자
	*/
	virtual ~EgPolyline();
};

/*!
*	\class	QNode<T1, T2>
*	\brief	큐의 노드를 표현하는 클래스
*	\note	마지막 수정일: 2020-02-23
*
*	\author 윤승현
*/
template<class T1, class T2>
class QNode
{
public:
	/* \brief 노드 데이터 */
	T1 m_pData;

	/* \brief 정렬을 위한 노드의 값(거리 등) */
	T2 m_Value;

public:
	/*!
	*	\brief	생성자
	*	
	*	\param	pData[in]	노드 
	*	\param	Value[in]	노드의 값
	*/
	QNode(T1 pData, T2 Value)
	{
		m_pData = pData;
		m_Value = Value;
	}

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	QNode(const QNode &cpy)
	{
		m_pData = cpy.m_pData;
		m_Value = cpy.m_Value;
	}

	/*!
	*	\brief	소멸자
	*/
	~QNode() {}

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return	대입된 자신을 반환한다.
	*/
	QNode &operator =(const QNode &rhs)
	{
		m_pData = rhs.m_pData;
		m_Value = rhs.m_Value;
		return *this;
	}

	/*!
	*	\brief	두 노드의 크기를 비교한다.
	*
	*	\param	lhs[in]		왼쪽 노드
	*	\param	rhs[in]		오른쪽 노드
	*
	*	\return 왼쪽 노드가 오른쪽 노드보다 크면 true, 아니면 false를 반환한다.
	*/
	friend bool operator >(const QNode &lhs, const QNode &rhs)
	{
		return (lhs.m_Value > rhs.m_Value);
	}

	/*!
	*	\brief	두 노드의 크기를 비교한다.
	*
	*	\param	lhs[in]		왼쪽 노드
	*	\param	rhs[in]		오른쪽 노드
	*
	*	\return 왼쪽 노드가 오른쪽 노드보다 작으면 true, 아니면 false를 반환한다.
	*/
	friend bool operator <(const QNode &lhs, const QNode &rhs)
	{
		return (lhs.m_Value < rhs.m_Value);
	}
};

/*!
*	\class	EgGraph
*	\brief	하프 에지를 이용하여 삼각 메쉬의 위상을 표현하는 클래스
*
*	\author 윤승현
*	\date	2021-09-28
*/
class EgGraph
{
public:
	/*! \brief 정점의 수 */
	int m_vnum;

	/*! \brief 에지의 수 */
	int m_enum;

	/*! \brief 삼각형의 수 */
	int m_fnum;	

	/*! \brief 하프 에지가 가르키는 끝점의 인덱스 */
	std::vector<int> m_halfedge_to_vertex;

	/*! \brief 하프 에지가 포함된 삼각형의 인덱스 */
	std::vector<int> m_halfedge_to_face;

	/*! \brief 다음 하프 에지의 인덱스 */
	std::vector<int> m_halfedge_to_next;

	/*! \brief 이전 하프 에지의 인덱스 */
	std::vector<int> m_halfedge_to_prev;

	/*! \brief 정점에서 시작하는 첫 번째 하프 에지 */
	std::vector<int> m_vertex_to_halfedge;

	/*! \brief 정규화된 에지의 길이 배열 */
	std::vector<double> m_edge_lengths;

	/*! \brief 정규화를 위한 에지의 평균 길이 */
	double m_avg_edge_len;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	pMesh[in]	대상 메쉬
	*/
	EgGraph(EgMesh *pMesh);

	/*!
	*	\brief	소멸자
	*/
	~EgGraph();
};
