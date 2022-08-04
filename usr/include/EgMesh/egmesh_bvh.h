#pragma once

#define MAX_BVH_DEPTH 10

/*!
*	\class	EgBvh
*	\brief	AABB (Axis-Aligned Bounding Box) 타입의 BVH (Bounding Volume Hierarchy)를 표현하는 클래스
*	\note	마지막 수정일: 2021-02-23
*
*	\author 한상준, 윤승현
*/
class EgBvh
{
public:
	/*!
	*	\class	AaBb (Axis-Alined Bounding Box)
	*	\brief	AABB 타입 경계 상자를 표현하는 클래스
	*	\note	마지막 수정일: 2021-04-07
	*
	*	\author 한상준, 윤승현
	*/
	class AaBb
	{
	public:
		/* \brief 대상 메쉬에 대한 포인터 */
		EgMesh *m_pMesh;

		/* \brief 경계 상자에 포함된 삼각형 리스트 */
		std::vector<EgFace *> m_Faces;

		/* \brief 경계 상자의 최소 위치 */
		EgPos m_Min;

		/* \brief 경계 상자의 최대 위치 */
		EgPos m_Max;

		/* \brief 경계 상자의 BVH 레벨 */
		int m_Depth;

		/* \brief 리프 경계 상자 여부 */
		bool m_bLeaf;

		/* \brief 하위 경계 상자에 대한 포인터 */
		std::vector<AaBb *> m_ChildNodes;

	public:
		/*!
		 *	\brief	디폴트 생성자
		 */
		AaBb();

		/*!
		 *	\brief	삼각형 리스트를 바운딩하는 경계 상자와 하위 경계 상자(필요한 경우)를 생성한다.
		 *
		 *	\param	pMesh[in]	메쉬 포인터
		 *	\param	Faces[in]	경계 상자에 포함될 삼각형 리스트
		 *	\param	Depth[in]	경계 상자의 BVH 레벨
		 */
		AaBb(EgMesh *pMesh, std::vector<EgFace *> &Faces, const int depth);

		/*!
		*	\brief	소멸자
		*/
		~AaBb();

		/*!
		*	\brief	경계 상자를 두 축(최단축 제외)으로 분할하여 4개의 경계 상자를 생성한다.
		*/
		void Divide();

		/*!
		 *	\brief	점과 경계 상자 사이의 최단 거리 제곱을 계산한다.
		 *	\note	점이 경계 상자 내부에 포함되었다면 0을 반환한다.
		 *
		 *	\param	p[in]	점의 위치
		 *
		 *	\return 점과 경계 상자 사이의 최단 거리 제곱을 반환한다.
		 */
		double GetSqrDist(const EgPos &p);

		/*!
		 *	\brief	광선과 경계 상자의 교차점을 계산한다.
		 *	\note	참조: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
		 *
		 *	\param	Ray[in]		조사할 광선(직선)
		 *	\param	t[out]		교차하는 경우 교차점의 파라미터가 저장된다.
		 *
		 *	\return 광선과 경계 상자가 교차하면 true, 아니면 false를 반환한다.
		 */
		bool IntersectWithRay(const EgLine &Ray, double &t);

		/*!
		 *	\brief	삼각형과 경계 상자의 교차 여부를 검사한다.
		 *
		 *	\param	p0[in]		조사할 삼각형의 첫 번째 정점
		 *	\param	p1[in]		조사할 삼각형의 두 번째 정점
		 *	\param	p2[in]		조사할 삼각형의 세 번째 정점
		 *
		 *	\return 삼각형과 경계 상자가 교차하면 true, 아니면 false를 반환한다.
		 */
		bool IntersectWithTri(const EgPos &p0, const EgPos &p1, const EgPos &p2);
	};

public:
	/* \brief 대상 메쉬에 대한 포인터 */
	EgMesh *m_pMesh;

	/* \brief 최상위 경계 상자에 대한 포인터 */
	AaBb *m_pRoot;

	/* \brief 대상 메쉬를 복제 여부 */
	bool m_bCopy;
	
public:
	/*!
	 *	\brief	생성자
	 */
	EgBvh();

	/*!
	 *	\brief	대상 메쉬에 대한 BVH를 생성한다.
	 *
	 *	\param	pMesh[in]		대상 메쉬
	 */
	EgBvh(EgMesh *pMesh);

	/*!
	 *	\brief	입력 정보로 BVH를 생성한다.
	 *
	 *	\param	Verts[in]	정점의 리스트
	 *	\param	Faces[in]	삼각형을 구성하는 정점의 인덱스 리스트
	 */
	EgBvh(std::vector<EgPos> &Verts, std::vector<int> &Faces);	

	/*!
	 *	\brief	소멸자
	 */
	~EgBvh();

	/*!
	 *	\brief	점과 메쉬 사이의 거리가 주어진 거리보다 가까운지 조사한다.
	 *
	 *	\param	Dist[in]		입력 거리
	 *	\param	p[in]			조사할 점의 위치
	 *	\param	bVertOnly[in]	점과 메쉬 정점 사이의 거리만을 조사하면 true, 점과 메쉬 삼각형 사이의 거리를 조사하면 false
	 *
	 *	\return 정점과 메쉬 사이의 거리가 주어진 거리보다 가까우면 true, 아니면 false를 반환한다.
	 */
	bool IsCloserThan(double Dist, const EgPos &p, bool bVertOnly);

	/*!
	 *	\brief	점과 메쉬의 최단 거리를 계산한다.
	 *
	 *	\param	p[in]		점의 위치
	 *	\param	q[out]		최단 거리가 발생하는 메쉬 위의 점이 저장된다.
	 *	\param	pFace[out]	최단 거리가 발생하는 삼각형의 포인터가 저장된다.
	 *	\param	bSinged[in]	음수 거리 변환 여부
	 *
	 *	\return 계산된 최단 거리를 반환한다.
	 */
	double ComputeDistance(EgPos p, EgPos &q, EgFace **pFace, bool bSigned);

	/*!
	 *	\brief	점과 메쉬의 최단 거리를 계산한다.
	 *
	 *	\param	p[in]		점의 위치
	 *	\param	q[out]		최단 거리가 발생하는 메쉬 위의 점이 저장된다.
	 *	\param	fidx[out]	최단 거리가 발생하는 삼각형의 인덱스가 저장된다.
	 *	\param	sign[in]	음수 거리 변환 여부
	 *
	 *	\return 계산된 최단 거리를 반환한다.
	 */
	double ComputeDistance(EgPos p, EgPos &q, int &fidx, bool sign);

	/*!
	 *	\brief	광선과 메쉬의 교차점을 계산한다.
	 *	\note	광선의 시작점은 최상위 경계 상자 외부에 있는 것으로 가정한다.
	 *
	 *	\param	Ray[in]				광선(직선) 객체
	 *	\param	t[out]				교차점의 직선 파라미터가 저장된다.
	 *	\param	pFace[out]			교차 삼각형의 포인터가 저장된다.
	 *	\param	bCullBackFace[in]	삼각형 뒷면 교차를 포함할지 여부
	 *	\param	bNear[in]			교차점을 형태(가까운 교차점이면 true, 먼 교차점이면 false)
	  *
	 *	\return 광선과 메쉬가 교차하면 true, 아니면 false를 반환한다.
	 */
	bool IntersectWithRay(EgLine Ray, double &t, EgFace **pFace, bool bCullBackFace, bool bNear = true);

	/*!
	 *	\brief	입력 삼각형과 교차하는 모든 삼각형을 찾는다.
	  *
	 *	\param	f[in]				입력 삼각형
	 *	\param	HitFaces[out]		입력 삼각형과 교차하는 삼각형이 저장된다.
	 *	\param	CutLines[out]		교차 라인이 저장된다.
	 *
	 *	\return 입력 삼각형과 교차하는 삼각형의 수를 반환한다.
	 */
	int IntersectWithTri(EgFace *f, std::vector<EgFace *> &HitFaces, std::vector<std::pair<EgPos, EgPos>> &CutLines);
	
	/*!
	*	\brief	입력 삼각형과 교차하는 모든 삼각형을 찾는다.
	 *
	*	\param	u0[in]				입력 삼각형의 첫 번째 정점의 좌표
	*	\param	u1[in]				입력 삼각형의 두 번째 정점의 좌표
	*	\param	u2[in]				입력 삼각형의 세 번째 정점의 좌표
	*	\param	HitFaces[out]		입력 삼각형과 교차하는 삼각형이 저장된다.
	*
	*	\return 입력 삼각형과 교차하는 삼각형의 수를 반환한다.
	*/
	int IntersectWithTri(EgPos u0, EgPos u1, EgPos u2, std::vector<EgFace *> &HitFaces);
};

/*!
  *	\brief	점과 삼각형 정점 사이의 최단 거리 제곱을 계산한다.
  *
  *	\param	q[in]	점의 위치
  *	\param	f[in]	대상 삼각형의 포인터
	*
  *	\return 계산된 최단 거리 제곱을 반환한다.
  */
double dist_sq_vert(const EgPos &p, EgFace *f);

/*!
  *	\brief	점과 삼각형 사이의 최단 거리 제곱을 계산한다.
  *
  *	\param	q[in]	점의 위치
  *	\param	f[in]	대상 삼각형의 포인터
	*
  *	\return 계산된 최단 거리 제곱을 반환한다.
  */
double dist_sq(const EgPos &q, EgFace *f);

/*!
 *	\brief	점과 삼각형 사이의 최단 거리 제곱을 계산한다.
 *
 *	\param	q[in]	점의 위치
 *	\param	f[in]	대상 삼각형의 포인터
 *	\param	r[out]	최단 거리가 발생되는 점이 저장된다.
 *
 *	\return 계산된 최단 거리 제곱을 반환한다.
 */
double dist_sq(const EgPos &p, EgFace *f, EgPos &q);
