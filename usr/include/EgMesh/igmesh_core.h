#pragma once

class IgVertex;
class IgEdge;
class IgFace;
class IgMesh;

/*!
*	\class	IgVertex
*	\brief	삼각 메쉬의 Vertex를 표현하는 클래스
*
*	\author 한상준
*	\date	2022-02-01
*/
class IgVertex 
{
private:
	/*! \brief 정점의 인덱스 */
	unsigned int m_Idx;

	/*! \brief 정점의 위치 */
	EgPos m_Pos;

	/*! \brief 정점에서 시작하는 하프에지 리스트 */
	std::vector<IgEdge *> m_pHEdges;
	
	/*! \brief 객체의 유효성 */
	bool m_Valid;

	/*! \brief 경계 정점 여부 */
	bool m_Boundary;

	/*!
	*	\brief	vertex 주위의 모든 halfedge에 문제가 없는지를 판단 (미완성)
	*
	*	\return	문제가 없을 경우 true를 반환한다
	*/
	bool integrity_test() const;

	/*!
	*	\brief	halfedge를 vertex가 포함하는지를 판단한다
	*
	*	\param	halfedge[in]	판단할 halfedge
	*
	*	\return	IgVertex로부터 빠져나가는 halfedge 중 halfedge[in]이 포함된 경우 true를 반환한다
	*/
	bool contain(IgEdge *halfedge) const;

public:
	/*!
	*	\brief	생성자
	*/
	IgVertex();

	/*!
	*	\brief	생성자
	*
	*	\param	idx[in]	추가하는 vertex의 index
	*/
	IgVertex(unsigned int idx);

	/*!
	*	\brief	소멸자
	*/
	virtual ~IgVertex();

	/*!
	*	\brief	IgVertex의 좌표를 설정
	*
	*	\param	pos[in]	설정할 좌표
	*/
	void set_position(EgPos& pos);

	/*!
	*	\brief	IgVertex에서 출발하는 halfedge를 추가
	*
	*	\param	p_HEdge[in]	추가하는 halfedge의 포인터
	*/
	void add_halfedge(IgEdge* p_HEdge);

	/*!
	*	\brief	IgVertex의 index를 설정
	*
	*	\param	idx[in]	설정할 index
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	IgVertex의 validity를 설정
	*
	*	\param	valid[in]	설정할 validity
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	IgVertex의 boundary 여부를 설정
	*
	*	\param	boundary[in]	경계 vertex인 경우 true
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	IgVertex의 index를 반환
	*
	*	\return	IgVertex의 index를 반환한다
	*/
	unsigned int idx() const;

	/*!
	*	\brief	IgVertex의 validity를 반환
	*
	*	\return	IgVertex의 validity를 반환한다
	*/
	bool is_valid() const;

	/*!
	*	\brief	IgVertex의 boundary 여부를 반환
	*
	*	\return	IgVertex의 boundary 여부를 반환한다
	*/
	bool is_boundary() const;

	/*!
	*	\brief	non manifold vertex인지를 판단 (미완성)
	*	\note	piecewise flat surface 상의 vertex위에 삼각형 하나만 동 떠있는 경우를 다루지 못함!
	*
	*	\return	non manifold vertex인 경우 true를 반환한다
	*/
	bool is_non_manifold() const;

	/*!
	*	\brief	vertex의 주변 halfedge list에서 p_HEdge를 제거
	*
	*	\param	제거할 halfedge의 포인터
	*
	*	\return	성공적으로 제거될 경우 true를 반환한다
	*/
	bool remove_halfedge_from_list(IgEdge* p_HEdge);

	/*!
	*	\brief	IgVertex 주위 halfedge를 반시계 방향으로 정렬 (미완성)
	*
	*	\return	정렬에 성공하는 경우 true를 반환한다
	*/
	bool set_halfedge_ccw();

	/*!
	*	\brief	voronoi cell area를 구한다
	*
	*	\return	voronoi cell area를 반환한다
	*/
	double mixed_voronoi_cell_area() const;

	/*!
	*	\brief	IgVertex의 좌표를 반환
	*
	*	\return	IgVertex의 좌표를 반환한다
	*/
	EgPos point();

	/*!
	*	\brief	vertex에서 빠져나가는 halfedge
	*
	*	\return	vertex에서 빠져나가는 halfedge의 포인터를 vector 자료구조로 반환한다
	*/
	std::vector<IgEdge*> halfedges_around_vertex() const;

	/*!
	*	\brief	vertex 주위의 face
	*
	*	\return	vertex 주위 face의 포인터를 vector 자료구조로 반환한다
	*/
	std::vector<IgFace*> faces_around_vertex() const;

	/*!
	*	\brief	vertex 주변의 vertices
	*
	*	\return	vertex 주변의 vertices의 포인터를 vector 자료구조로 반환한다
	*/
	std::vector<IgVertex*> vertices_around_vertex() const;
};

/*!
*	\class	IgEdge
*	\brief	삼각 메쉬의 하프에지를 표현하는 클래스
*
*	\author 한상준
*	\date	2022-02-01
*/
class IgEdge 
{
private:
	/*! \brief 하프에지 아이디 */
	unsigned int m_Idx;

	/*! \brief 하프에지의 시작 정점 */
	IgVertex *m_pVert;

	/*! \brief 하프에지를 포함한 삼각형 */
	IgFace *m_pFace;

	/*! \brief 다음 하프에지 */
	IgEdge *m_pNext;

	/*! \brief 이전 하프에지 */
	IgEdge *m_pPrev;

	/*! \brief 반대편 하프에지 */
	IgEdge *m_pOpposite;

	/*! \brief 하프에지 길이 */
	double m_Length;

	/*! \brief 객체의 유효성 */
	bool m_Valid;

	/*! \brief 경계 에지 여부 */
	bool m_Boundary;

public:
	/*!
	*	\brief	생성자
	*/
	IgEdge();

	/*!
	*	\brief	생성자
	*
	*	\param	idx[in]		새로 만드는 halfedge의 인덱스
	*/
	IgEdge(unsigned int idx);

	/*!
	*	\brief	소멸자
	*/
	virtual ~IgEdge();

	/*!
	*	\brief	Halfedge의 시작 vertex를 설정한다
	*
	*	\param	pVert[in]	Vertex의 포인터
	*/
	void set_vertex(IgVertex *pVert);

	/*!
	*	\brief	Halfedge가 포함하는 face를 설정한다
	*
	*	\param	pFace[in]	Face의 포인터
	*/
	void set_face(IgFace *pFace);

	/*!
	*	\brief	다음 Halfedge의 포인터를 설정한다
	*
	*	\param	pNext[in]	다음 halfedge의 포인터
	*/
	void set_next(IgEdge *pNext);

	/*!
	*	\brief	이전 Halfedge의 포인터를 설정한다
	*
	*	\param	pPrev[in]	이전 halfedge의 포인터
	*/
	void set_prev(IgEdge *pPrev);

	/*!
	*	\brief	마주보는 Halfedge의 포인터를 설정한다
	*
	*	\param	pOpposite[in]	마주보는 halfedge의 포인터
	*/
	void set_opposite(IgEdge *pOpposite);

	/*!
	*	\brief	Halfedge의 인덱스를 설정한다
	*
	*	\param	idx[in]		halfedge의 인덱스
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	Halfedge의 길이를 설정한다
	*
	*	\param	length[in]	halfedge의 길이
	*/
	void set_length(double length);

	/*!
	*	\brief	Halfedge의 유효성을 설정한다
	*
	*	\param	valid[in]	halfedge의 유효성
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	boundary 여부를 설정한다
	*
	*	\param	boundary[in]	Boundary인 경우 True
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	halfedge의 시작 vertex의 포인터
	*
	*	\return	halfedge의 시작 vertex의 포인터를 반환한다
	*/
	IgVertex *vertex() const;

	/*!
	*	\brief	halfedge를 포함하는 face의 포인터
	*
	*	\return	halfedge를 포함하는 face의 포인터를 반환한다
	*/
	IgFace *face() const;

	/*!
	*	\brief	다음 halfedge의 포인터
	*
	*	\return	다음 halfedge의 포인터를 반환한다
	*/
	IgEdge *next() const;

	/*!
	*	\brief	이전 halfedge의 포인터
	*
	*	\return	이전 halfedge의 포인터를 반환한다
	*/
	IgEdge *prev() const;

	/*!
	*	\brief	마주보는 halfedge의 포인터
	*
	*	\return	마주보는 halfedge의 포인터를 반환한다
	*/
	IgEdge *opposite() const;

	/*!
	*	\brief	halfedge의 index
	*
	*	\return	halfedge의 index를 반환한다
	*/
	unsigned int idx() const;

	/*!
	*	\brief	halfedge의 길이
	*
	*	\return	halfedge의 길이를 반환한다
	*/
	double length() const;

	/*!
	*	\brief	halfedge의 validity
	*
	*	\return	halfedge의 validity를 반환한다
	*/
	bool is_valid() const;

	/*!
	*	\brief	halfedge의 경계 여부
	*
	*	\return	halfedge가 경계이면 true, 아니면 false를 반환한다
	*/
	bool is_boundary() const;

	/*!
	*	\brief	halfedge와 마주보는 각의 크기 (radian, 삼각메시에서만 적용)
	*
	*	\return	halfedge와 마주보는 각의 크기를 반환한다
	*/
	double angle() const;

	/*!
	*	\brief	halfedge가 flip할 수 있는지를 판단한다
	*
	*	\return	halfedge를 flip할 수 있으면 true를 반환한다
	*/
	bool is_flippable() const;

	/*!
	*	\brief	halfedge의 legality
	*
	*	\return	halfedge의 legality를 판단하여 legal하면 true, 아니면 false를 반환한다
	*/
	bool is_legal() const;
};

/*!
*	\class	IgFace
*	\brief	삼각 메쉬의 face를 표현하는 클래스
*
*	\author 한상준
*	\date	2022-02-01
*/
class IgFace 
{
private:
	/*! \brief Face의 인덱스 */
	unsigned int m_Idx;

	/*! \brief Face를 이루는 Halfdege */
	IgEdge *m_pHEdge;

	/*! \brief 객체의 유효성 */
	bool m_Valid;

	/*! \brief 경계 삼각형 여부 */
	bool m_Boundary;

public:
	/*!
	*	\brief	생성자
	*/
	IgFace();

	/*!
	*	\brief	생성자
	*
	*	\param	idx[in]	설정할 index
	*/
	IgFace(unsigned int idx);

	/*!
	*	\brief	소멸자
	*/
	virtual ~IgFace();

	/*!
	*	\brief	halfedge 설정자
	*
	*	\param	p_HEdge[in] 설정해줄 halfedge의 포인터
	*/
	void set_halfedge(IgEdge *p_HEdge);

	/*!
	*	\brief	index 설정자
	*
	*	\param	idx[in] 설정해줄 index
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	validity 설정자
	*
	*	\param	valid[in] 설정해줄 validity
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	boundary 설정자
	*
	*	\param	boundary[in] boundary인 경우 true, 아닌 경우 false
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	halfedge 접근자
	*
	*	\return	face안에 포함된 halfedge의 포인터를 반환한다
	*/
	IgEdge *halfedge() const;

	/*!
	*	\brief	index 접근자
	*
	*	\return	face의 index를 반환한다
	*/
	unsigned int idx() const;

	/*!
	*	\brief	validity 접근자
	*
	*	\return	IgFace의 validity를 반환한다
	*/
	bool is_valid() const;

	/*!
	*	\brief	boundary 접근자
	*
	*	\return	IgFace가 경계인 경우 true, 아닌 경우 false를 반환한다
	*/
	bool Is_boundary() const;

	/*!
	*	\brief	삼각형의 넓이 (삼각메시인 경우)
	*
	*	\return	삼각형의 넓이를 반환한다
	*/
	double area() const;

	/*!
	*	\brief	삼각형인지를 판단
	*
	*	\return	삼각형이면 true를 반환한다
	*/
	bool is_triangle() const;
};

/*!
*	\class	IgMesh
*	\brief	Intrinsic Delaunay 삼각화된 메쉬를 표현하는 클래스
*
*	\author 한상준
*	\date	2022-02-01
*/
class IgMesh : public EgObject 
{
private:
	/*! \brief 원래의 Mesh */
	EgMesh *m_Mesh;

	/*! \brief 메쉬의 이름 */
	std::string m_Name;

	/*! \brief halfedge 배열 */
	std::vector<IgEdge *> m_pHEdges;

	/*! \brief vertex 배열 */
	std::vector<IgVertex *> m_pVertices;

	/*! \brief face 배열 */
	std::vector<IgFace *> m_pFaces;

	/*! \brief halfedge의 개수 */
	unsigned int m_NumHalfedges;

	/*! \brief vertex의 개수 */
	unsigned int m_NumVertices;

	/*! \brief vertex의 개수 */
	unsigned int m_NumFaces;

	/*! \brief halfedge의 개수 */
	unsigned int m_ValidNumHalfedges;

	/*! \brief vertex의 개수 */
	unsigned int m_ValidNumVertices;

	/*! \brief vertex의 개수 */
	unsigned int m_ValidNumFaces;

	/*!
	*	\brief	IgMesh가 vertex를 포함하는지 판단
	*
	*	\param	vertex[in]	포함 여부를 판단하는 vertex
	*
	*	\return	포함하는 경우 true를 반환한다
	*/
	bool contain(const IgVertex* vertex);

	/*!
	*	\brief	IgMesh가 halfedge를 포함하는지 판단
	*
	*	\param	halfedge[in]	포함 여부를 판단하는 halfedge
	*
	*	\return	포함하는 경우 true를 반환한다
	*/
	bool contain(const IgEdge* halfedge);

	/*!
	*	\brief	IgMesh가 face를 포함하는지 판단
	*
	*	\param	face[in]	포함 여부를 판단하는 face
	*
	*	\return	포함하는 경우 true를 반환한다
	*/
	bool contain(const IgFace* face);

public:
	/*! \brief 정적 변수 */
	static IgVertex *null_vertex;
	static IgEdge *null_halfedge;
	static IgFace *null_face;

public:
	/*!
	*	\brief	Class의 이름을 반환한다.
	*
	*	\return	Class의 이름을 반환한다
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	새로운 Object의 이름
	*
	*	\return	새로운 Object의 이름을 반환한다
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	Object를 복사
	*
	*	\return	복사한 Object의 포인터를 반환한다
	*/
	virtual IgMesh *CopyObject();

	/*!
	*	\brief	IgMesh를 만든 EgMesh
	*
	*	\return	IgMesh를 만든 EgMesh의 포인터를 반환한다
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	EgMesh를 이용하는 생성자
	*
	*	\return	EgMesh를 이용하여 IgMesh를 생성한다
	*/
	IgMesh(EgMesh *pMesh);

	/*!
	*	\brief	IgMesh의 복사 생성자
	*
	*	\param	cpy[in]	복사할 객체
	*
	*	\return	cpy를 복사하여 IgMesh를 생성한다
	*/
	IgMesh(const IgMesh &cpy);

	/*!
	*	\brief	IgMesh의 소멸자
	*/
	virtual ~IgMesh();

	/*!
	*	\brief	IgMesh를 EgMesh로 변환
	*
	*	\return	IgMesh를 EgMesh로 변환하여 반환한다
	*/
	EgMesh *to_egmesh();

	/*!
	*	\brief	vertex 주변의 vertex
	*
	*	\param	vertex[in]	주위를 조사할 vertex
	*
	*	\return	vertex[in]의 주변 vertex를 vector form으로 반환한다
	*/
	std::vector<IgVertex *> vertices_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	face 주변의 vertex
	*
	*	\param	face[in]	주위를 조사할 face
	*
	*	\return	vertex[in]의 주변 vertex를 vector form으로 반환한다
	*/
	std::vector<IgVertex *> vertices_around_face(const IgFace *face);

	/*!
	*	\brief	halfedge의 시작점과 끝점
	*
	*	\param	halfedge[in]	조사할 halfedge
	*
	*	\return	halfedge[in]의 시작 vertex의 포인터를 first, 끝 vertex의 포인터를 second에 저장하여 반환한다
	*/
	std::pair<IgVertex *, IgVertex *> vertex(const IgEdge *halfedge);

	/*!
	*	\brief	메쉬의 모든 vertex의 halfedge를 반시계방향으로 배열한다 (미완성)
	*
	*	\return	성공할 경우 true를 반환한다
	*/
	bool set_vertices_halfedge_ccw() const;

	/*!
	*	\brief	vertex 주변의 halfedge
	*
	*	\param	vertex[in]	주위를 조사할 vertex
	*
	*	\return	vertex[in]에서 빠져나가는 halfedge의 vector를 반환한다
	*/
	std::vector<IgEdge *> halfedge_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	face 주변의 halfedge
	*
	*	\param	face[in]	주위를 조사할 face
	*
	*	\return	face[in]의 주변 halfedge의 주소를 반환한다
	*/
	std::vector<IgEdge *> halfedge_around_face(const IgFace *face);
	
	/*!
	*	\brief	vertex 주변의 face
	*
	*	\param	vertex[in]	주위를 조사할 vertex
	*
	*	\return	vertex[in]의 주변 face의 포인터를 반환한다
	*/
	std::vector<IgFace *> faces_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	마주보는 halfedge
	*
	*	\param	halfedge[in]	조사할 halfedge
	*
	*	\return	halfedge[in]과 마주보는 halfedge의 포인터
	*/
	IgEdge *opposite(const IgEdge *halfedge);

	/*!
	*	\brief	다음 halfedge
	*
	*	\param	halfedge[in]	조사할 halfedge
	*
	*	\return	halfedge[in] 다음의 halfedge의 포인터
	*/
	IgEdge *next(const IgEdge *halfedge);

	/*!
	*	\brief	이전 halfedge
	*
	*	\param	halfedge[in]	조사할 halfedge
	*
	*	\return	halfedge[in] 이전의 halfedge의 포인터
	*/
	IgEdge *prev(const IgEdge *halfedge);

	/*!
	*	\brief	halfedge를 포함하는 face
	*
	*	\param	halfedge[in]	조사할 halfedge
	*
	*	\return	halfedge[in] 를 포함하는 face를 반환한다
	*/
	IgFace *face(const IgEdge *halfedge);

	/*!
	*	\brief	halfedge의 개수
	*
	*	\return	IgMesh의 halfedge의 개수를 반환한다
	*/
	unsigned int number_of_halfedges() const;

	/*!
	*	\brief	vertex의 개수
	*
	*	\return	IgMesh의 vertex의 개수를 반환한다
	*/
	unsigned int number_of_vertices() const;

	/*!
	*	\brief	face의 개수
	*
	*	\return	IgMesh의 face의 개수를 반환한다
	*/
	unsigned int number_of_faces() const;

	/*!
	*	\brief	halfedge를 제거 (data는 실제로 삭제하지 않고 validity만 바꿈)
	*
	*	\param	halfedge[in]	제거할 halfedge
	*
	*	\return	IgMesh의 halfedge를 제거한다
	*/
	bool remove(IgEdge *halfedge);

	/*!
	*	\brief	face를 제거 (data는 실제로 삭제하지 않고 validity만 바꿈)
	*
	*	\param	face[in]	제거할 face
	*
	*	\return	IgMesh의 face를 제거한다
	*/
	bool remove(IgFace *face);

	/*!
	*	\brief	vertex를 제거 (data는 실제로 삭제하지 않고 validity만 바꿈)
	*
	*	\param	vertex[in]	제거할 vertex
	*
	*	\return	IgMesh의 vertex를 제거한다
	*/
	bool remove(IgVertex *vertex);

	/*!
	*	\brief	halfedge를 추가하고 Valid한 객체의 개수를 업데이트한다.
	*
	*	\param	halfedge[in]	추가할 halfedge
	*
	*	\return	IgMesh의 halfedge를 추가한다
	*/
	void add(IgEdge *halfedge);

	/*!
	*	\brief	face를 추가하고 Valid한 객체의 개수를 업데이트한다.
	*
	*	\param	face[in]	추가할 face
	*
	*	\return	IgMesh의 face를 추가한다
	*/
	void add(IgFace *face);

	/*!
	*	\brief	vertex를 추가하고 Valid한 객체의 개수를 업데이트한다.
	*
	*	\param	vertex[in]	추가할 vertex
	*
	*	\return	IgMesh의 vertex를 추가한다
	*/
	void add(IgVertex *vertex);

	/*!
	*	\brief	Validity가 false인 face, halfedge, vertex를 모두 정리
	*	\note	Validity가 False인 객체를 delete하고 새롭게 index를 부여한다.
	*
	*	\return	validity가 false인 face, halfedge, vertex를 모두 정리한다
	*/
	void garbage_collection();

	/*!
	*	\brief	IgMesh위의 halfedge를 flip
	*
	*	\param	halfedge[in]	flip할 halfedge
	*
	*	\return	flip을 성공하면 true, 아니면 false를 반환한다
	*/
	bool flip(IgEdge *halfedge);

	/*!
	*	\brief	IgMesh위의 halfedge를 flip (intrinsic)
	*
	*	\param	halfedge[in]	flip할 halfedge
	*
	*	\return	flip을 성공하면 true, 아니면 false를 반환한다
	*/
	bool flip_intrinsic(IgEdge *halfedge);

	/*!
	*	\brief	IgMesh에 delaunay triangulation 알고리즘을 적용
	*
	*	\param	intrinsic[in]	true인 경우 intrinsic delaunay triangulation을 한다
	*/
	void delaunay_triangulation(bool intrinsic);

	/*!
	*	\brief	Laplacian matrix (cotangent weight)를 구한다.
	*
	*	\param	D[in]	국소 면적의 역수가 저장된다.
	*	\param	M[in]	에지 가중치가 저장된다.
	*/
	void get_laplacian_matrix(Eigen::SparseMatrix<double> &D, Eigen::SparseMatrix<double> &M);

	/*!
	*	\brief	IgMesh를 obj 파일로 export (미완성)
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_obj(const char *filename);

	/*!
	*	\brief	IgMesh를 stl 파일로 export (미완성)
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_stl(const char *filename);

	/*!
	*	\brief	IgMesh를 off 파일로 export
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_off(const char *filename);
};






