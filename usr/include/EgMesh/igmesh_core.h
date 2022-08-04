#pragma once

class IgVertex;
class IgEdge;
class IgFace;
class IgMesh;

/*!
*	\class	IgVertex
*	\brief	�ﰢ �޽��� Vertex�� ǥ���ϴ� Ŭ����
*
*	\author �ѻ���
*	\date	2022-02-01
*/
class IgVertex 
{
private:
	/*! \brief ������ �ε��� */
	unsigned int m_Idx;

	/*! \brief ������ ��ġ */
	EgPos m_Pos;

	/*! \brief �������� �����ϴ� �������� ����Ʈ */
	std::vector<IgEdge *> m_pHEdges;
	
	/*! \brief ��ü�� ��ȿ�� */
	bool m_Valid;

	/*! \brief ��� ���� ���� */
	bool m_Boundary;

	/*!
	*	\brief	vertex ������ ��� halfedge�� ������ �������� �Ǵ� (�̿ϼ�)
	*
	*	\return	������ ���� ��� true�� ��ȯ�Ѵ�
	*/
	bool integrity_test() const;

	/*!
	*	\brief	halfedge�� vertex�� �����ϴ����� �Ǵ��Ѵ�
	*
	*	\param	halfedge[in]	�Ǵ��� halfedge
	*
	*	\return	IgVertex�κ��� ���������� halfedge �� halfedge[in]�� ���Ե� ��� true�� ��ȯ�Ѵ�
	*/
	bool contain(IgEdge *halfedge) const;

public:
	/*!
	*	\brief	������
	*/
	IgVertex();

	/*!
	*	\brief	������
	*
	*	\param	idx[in]	�߰��ϴ� vertex�� index
	*/
	IgVertex(unsigned int idx);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~IgVertex();

	/*!
	*	\brief	IgVertex�� ��ǥ�� ����
	*
	*	\param	pos[in]	������ ��ǥ
	*/
	void set_position(EgPos& pos);

	/*!
	*	\brief	IgVertex���� ����ϴ� halfedge�� �߰�
	*
	*	\param	p_HEdge[in]	�߰��ϴ� halfedge�� ������
	*/
	void add_halfedge(IgEdge* p_HEdge);

	/*!
	*	\brief	IgVertex�� index�� ����
	*
	*	\param	idx[in]	������ index
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	IgVertex�� validity�� ����
	*
	*	\param	valid[in]	������ validity
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	IgVertex�� boundary ���θ� ����
	*
	*	\param	boundary[in]	��� vertex�� ��� true
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	IgVertex�� index�� ��ȯ
	*
	*	\return	IgVertex�� index�� ��ȯ�Ѵ�
	*/
	unsigned int idx() const;

	/*!
	*	\brief	IgVertex�� validity�� ��ȯ
	*
	*	\return	IgVertex�� validity�� ��ȯ�Ѵ�
	*/
	bool is_valid() const;

	/*!
	*	\brief	IgVertex�� boundary ���θ� ��ȯ
	*
	*	\return	IgVertex�� boundary ���θ� ��ȯ�Ѵ�
	*/
	bool is_boundary() const;

	/*!
	*	\brief	non manifold vertex������ �Ǵ� (�̿ϼ�)
	*	\note	piecewise flat surface ���� vertex���� �ﰢ�� �ϳ��� �� ���ִ� ��츦 �ٷ��� ����!
	*
	*	\return	non manifold vertex�� ��� true�� ��ȯ�Ѵ�
	*/
	bool is_non_manifold() const;

	/*!
	*	\brief	vertex�� �ֺ� halfedge list���� p_HEdge�� ����
	*
	*	\param	������ halfedge�� ������
	*
	*	\return	���������� ���ŵ� ��� true�� ��ȯ�Ѵ�
	*/
	bool remove_halfedge_from_list(IgEdge* p_HEdge);

	/*!
	*	\brief	IgVertex ���� halfedge�� �ݽð� �������� ���� (�̿ϼ�)
	*
	*	\return	���Ŀ� �����ϴ� ��� true�� ��ȯ�Ѵ�
	*/
	bool set_halfedge_ccw();

	/*!
	*	\brief	voronoi cell area�� ���Ѵ�
	*
	*	\return	voronoi cell area�� ��ȯ�Ѵ�
	*/
	double mixed_voronoi_cell_area() const;

	/*!
	*	\brief	IgVertex�� ��ǥ�� ��ȯ
	*
	*	\return	IgVertex�� ��ǥ�� ��ȯ�Ѵ�
	*/
	EgPos point();

	/*!
	*	\brief	vertex���� ���������� halfedge
	*
	*	\return	vertex���� ���������� halfedge�� �����͸� vector �ڷᱸ���� ��ȯ�Ѵ�
	*/
	std::vector<IgEdge*> halfedges_around_vertex() const;

	/*!
	*	\brief	vertex ������ face
	*
	*	\return	vertex ���� face�� �����͸� vector �ڷᱸ���� ��ȯ�Ѵ�
	*/
	std::vector<IgFace*> faces_around_vertex() const;

	/*!
	*	\brief	vertex �ֺ��� vertices
	*
	*	\return	vertex �ֺ��� vertices�� �����͸� vector �ڷᱸ���� ��ȯ�Ѵ�
	*/
	std::vector<IgVertex*> vertices_around_vertex() const;
};

/*!
*	\class	IgEdge
*	\brief	�ﰢ �޽��� ���������� ǥ���ϴ� Ŭ����
*
*	\author �ѻ���
*	\date	2022-02-01
*/
class IgEdge 
{
private:
	/*! \brief �������� ���̵� */
	unsigned int m_Idx;

	/*! \brief ���������� ���� ���� */
	IgVertex *m_pVert;

	/*! \brief ���������� ������ �ﰢ�� */
	IgFace *m_pFace;

	/*! \brief ���� �������� */
	IgEdge *m_pNext;

	/*! \brief ���� �������� */
	IgEdge *m_pPrev;

	/*! \brief �ݴ��� �������� */
	IgEdge *m_pOpposite;

	/*! \brief �������� ���� */
	double m_Length;

	/*! \brief ��ü�� ��ȿ�� */
	bool m_Valid;

	/*! \brief ��� ���� ���� */
	bool m_Boundary;

public:
	/*!
	*	\brief	������
	*/
	IgEdge();

	/*!
	*	\brief	������
	*
	*	\param	idx[in]		���� ����� halfedge�� �ε���
	*/
	IgEdge(unsigned int idx);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~IgEdge();

	/*!
	*	\brief	Halfedge�� ���� vertex�� �����Ѵ�
	*
	*	\param	pVert[in]	Vertex�� ������
	*/
	void set_vertex(IgVertex *pVert);

	/*!
	*	\brief	Halfedge�� �����ϴ� face�� �����Ѵ�
	*
	*	\param	pFace[in]	Face�� ������
	*/
	void set_face(IgFace *pFace);

	/*!
	*	\brief	���� Halfedge�� �����͸� �����Ѵ�
	*
	*	\param	pNext[in]	���� halfedge�� ������
	*/
	void set_next(IgEdge *pNext);

	/*!
	*	\brief	���� Halfedge�� �����͸� �����Ѵ�
	*
	*	\param	pPrev[in]	���� halfedge�� ������
	*/
	void set_prev(IgEdge *pPrev);

	/*!
	*	\brief	���ֺ��� Halfedge�� �����͸� �����Ѵ�
	*
	*	\param	pOpposite[in]	���ֺ��� halfedge�� ������
	*/
	void set_opposite(IgEdge *pOpposite);

	/*!
	*	\brief	Halfedge�� �ε����� �����Ѵ�
	*
	*	\param	idx[in]		halfedge�� �ε���
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	Halfedge�� ���̸� �����Ѵ�
	*
	*	\param	length[in]	halfedge�� ����
	*/
	void set_length(double length);

	/*!
	*	\brief	Halfedge�� ��ȿ���� �����Ѵ�
	*
	*	\param	valid[in]	halfedge�� ��ȿ��
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	boundary ���θ� �����Ѵ�
	*
	*	\param	boundary[in]	Boundary�� ��� True
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	halfedge�� ���� vertex�� ������
	*
	*	\return	halfedge�� ���� vertex�� �����͸� ��ȯ�Ѵ�
	*/
	IgVertex *vertex() const;

	/*!
	*	\brief	halfedge�� �����ϴ� face�� ������
	*
	*	\return	halfedge�� �����ϴ� face�� �����͸� ��ȯ�Ѵ�
	*/
	IgFace *face() const;

	/*!
	*	\brief	���� halfedge�� ������
	*
	*	\return	���� halfedge�� �����͸� ��ȯ�Ѵ�
	*/
	IgEdge *next() const;

	/*!
	*	\brief	���� halfedge�� ������
	*
	*	\return	���� halfedge�� �����͸� ��ȯ�Ѵ�
	*/
	IgEdge *prev() const;

	/*!
	*	\brief	���ֺ��� halfedge�� ������
	*
	*	\return	���ֺ��� halfedge�� �����͸� ��ȯ�Ѵ�
	*/
	IgEdge *opposite() const;

	/*!
	*	\brief	halfedge�� index
	*
	*	\return	halfedge�� index�� ��ȯ�Ѵ�
	*/
	unsigned int idx() const;

	/*!
	*	\brief	halfedge�� ����
	*
	*	\return	halfedge�� ���̸� ��ȯ�Ѵ�
	*/
	double length() const;

	/*!
	*	\brief	halfedge�� validity
	*
	*	\return	halfedge�� validity�� ��ȯ�Ѵ�
	*/
	bool is_valid() const;

	/*!
	*	\brief	halfedge�� ��� ����
	*
	*	\return	halfedge�� ����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�
	*/
	bool is_boundary() const;

	/*!
	*	\brief	halfedge�� ���ֺ��� ���� ũ�� (radian, �ﰢ�޽ÿ����� ����)
	*
	*	\return	halfedge�� ���ֺ��� ���� ũ�⸦ ��ȯ�Ѵ�
	*/
	double angle() const;

	/*!
	*	\brief	halfedge�� flip�� �� �ִ����� �Ǵ��Ѵ�
	*
	*	\return	halfedge�� flip�� �� ������ true�� ��ȯ�Ѵ�
	*/
	bool is_flippable() const;

	/*!
	*	\brief	halfedge�� legality
	*
	*	\return	halfedge�� legality�� �Ǵ��Ͽ� legal�ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�
	*/
	bool is_legal() const;
};

/*!
*	\class	IgFace
*	\brief	�ﰢ �޽��� face�� ǥ���ϴ� Ŭ����
*
*	\author �ѻ���
*	\date	2022-02-01
*/
class IgFace 
{
private:
	/*! \brief Face�� �ε��� */
	unsigned int m_Idx;

	/*! \brief Face�� �̷�� Halfdege */
	IgEdge *m_pHEdge;

	/*! \brief ��ü�� ��ȿ�� */
	bool m_Valid;

	/*! \brief ��� �ﰢ�� ���� */
	bool m_Boundary;

public:
	/*!
	*	\brief	������
	*/
	IgFace();

	/*!
	*	\brief	������
	*
	*	\param	idx[in]	������ index
	*/
	IgFace(unsigned int idx);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~IgFace();

	/*!
	*	\brief	halfedge ������
	*
	*	\param	p_HEdge[in] �������� halfedge�� ������
	*/
	void set_halfedge(IgEdge *p_HEdge);

	/*!
	*	\brief	index ������
	*
	*	\param	idx[in] �������� index
	*/
	void set_idx(unsigned int idx);

	/*!
	*	\brief	validity ������
	*
	*	\param	valid[in] �������� validity
	*/
	void set_valid(bool valid);

	/*!
	*	\brief	boundary ������
	*
	*	\param	boundary[in] boundary�� ��� true, �ƴ� ��� false
	*/
	void set_boundary(bool boundary);

	/*!
	*	\brief	halfedge ������
	*
	*	\return	face�ȿ� ���Ե� halfedge�� �����͸� ��ȯ�Ѵ�
	*/
	IgEdge *halfedge() const;

	/*!
	*	\brief	index ������
	*
	*	\return	face�� index�� ��ȯ�Ѵ�
	*/
	unsigned int idx() const;

	/*!
	*	\brief	validity ������
	*
	*	\return	IgFace�� validity�� ��ȯ�Ѵ�
	*/
	bool is_valid() const;

	/*!
	*	\brief	boundary ������
	*
	*	\return	IgFace�� ����� ��� true, �ƴ� ��� false�� ��ȯ�Ѵ�
	*/
	bool Is_boundary() const;

	/*!
	*	\brief	�ﰢ���� ���� (�ﰢ�޽��� ���)
	*
	*	\return	�ﰢ���� ���̸� ��ȯ�Ѵ�
	*/
	double area() const;

	/*!
	*	\brief	�ﰢ�������� �Ǵ�
	*
	*	\return	�ﰢ���̸� true�� ��ȯ�Ѵ�
	*/
	bool is_triangle() const;
};

/*!
*	\class	IgMesh
*	\brief	Intrinsic Delaunay �ﰢȭ�� �޽��� ǥ���ϴ� Ŭ����
*
*	\author �ѻ���
*	\date	2022-02-01
*/
class IgMesh : public EgObject 
{
private:
	/*! \brief ������ Mesh */
	EgMesh *m_Mesh;

	/*! \brief �޽��� �̸� */
	std::string m_Name;

	/*! \brief halfedge �迭 */
	std::vector<IgEdge *> m_pHEdges;

	/*! \brief vertex �迭 */
	std::vector<IgVertex *> m_pVertices;

	/*! \brief face �迭 */
	std::vector<IgFace *> m_pFaces;

	/*! \brief halfedge�� ���� */
	unsigned int m_NumHalfedges;

	/*! \brief vertex�� ���� */
	unsigned int m_NumVertices;

	/*! \brief vertex�� ���� */
	unsigned int m_NumFaces;

	/*! \brief halfedge�� ���� */
	unsigned int m_ValidNumHalfedges;

	/*! \brief vertex�� ���� */
	unsigned int m_ValidNumVertices;

	/*! \brief vertex�� ���� */
	unsigned int m_ValidNumFaces;

	/*!
	*	\brief	IgMesh�� vertex�� �����ϴ��� �Ǵ�
	*
	*	\param	vertex[in]	���� ���θ� �Ǵ��ϴ� vertex
	*
	*	\return	�����ϴ� ��� true�� ��ȯ�Ѵ�
	*/
	bool contain(const IgVertex* vertex);

	/*!
	*	\brief	IgMesh�� halfedge�� �����ϴ��� �Ǵ�
	*
	*	\param	halfedge[in]	���� ���θ� �Ǵ��ϴ� halfedge
	*
	*	\return	�����ϴ� ��� true�� ��ȯ�Ѵ�
	*/
	bool contain(const IgEdge* halfedge);

	/*!
	*	\brief	IgMesh�� face�� �����ϴ��� �Ǵ�
	*
	*	\param	face[in]	���� ���θ� �Ǵ��ϴ� face
	*
	*	\return	�����ϴ� ��� true�� ��ȯ�Ѵ�
	*/
	bool contain(const IgFace* face);

public:
	/*! \brief ���� ���� */
	static IgVertex *null_vertex;
	static IgEdge *null_halfedge;
	static IgFace *null_face;

public:
	/*!
	*	\brief	Class�� �̸��� ��ȯ�Ѵ�.
	*
	*	\return	Class�� �̸��� ��ȯ�Ѵ�
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	���ο� Object�� �̸�
	*
	*	\return	���ο� Object�� �̸��� ��ȯ�Ѵ�
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	Object�� ����
	*
	*	\return	������ Object�� �����͸� ��ȯ�Ѵ�
	*/
	virtual IgMesh *CopyObject();

	/*!
	*	\brief	IgMesh�� ���� EgMesh
	*
	*	\return	IgMesh�� ���� EgMesh�� �����͸� ��ȯ�Ѵ�
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	EgMesh�� �̿��ϴ� ������
	*
	*	\return	EgMesh�� �̿��Ͽ� IgMesh�� �����Ѵ�
	*/
	IgMesh(EgMesh *pMesh);

	/*!
	*	\brief	IgMesh�� ���� ������
	*
	*	\param	cpy[in]	������ ��ü
	*
	*	\return	cpy�� �����Ͽ� IgMesh�� �����Ѵ�
	*/
	IgMesh(const IgMesh &cpy);

	/*!
	*	\brief	IgMesh�� �Ҹ���
	*/
	virtual ~IgMesh();

	/*!
	*	\brief	IgMesh�� EgMesh�� ��ȯ
	*
	*	\return	IgMesh�� EgMesh�� ��ȯ�Ͽ� ��ȯ�Ѵ�
	*/
	EgMesh *to_egmesh();

	/*!
	*	\brief	vertex �ֺ��� vertex
	*
	*	\param	vertex[in]	������ ������ vertex
	*
	*	\return	vertex[in]�� �ֺ� vertex�� vector form���� ��ȯ�Ѵ�
	*/
	std::vector<IgVertex *> vertices_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	face �ֺ��� vertex
	*
	*	\param	face[in]	������ ������ face
	*
	*	\return	vertex[in]�� �ֺ� vertex�� vector form���� ��ȯ�Ѵ�
	*/
	std::vector<IgVertex *> vertices_around_face(const IgFace *face);

	/*!
	*	\brief	halfedge�� �������� ����
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	halfedge[in]�� ���� vertex�� �����͸� first, �� vertex�� �����͸� second�� �����Ͽ� ��ȯ�Ѵ�
	*/
	std::pair<IgVertex *, IgVertex *> vertex(const IgEdge *halfedge);

	/*!
	*	\brief	�޽��� ��� vertex�� halfedge�� �ݽð�������� �迭�Ѵ� (�̿ϼ�)
	*
	*	\return	������ ��� true�� ��ȯ�Ѵ�
	*/
	bool set_vertices_halfedge_ccw() const;

	/*!
	*	\brief	vertex �ֺ��� halfedge
	*
	*	\param	vertex[in]	������ ������ vertex
	*
	*	\return	vertex[in]���� ���������� halfedge�� vector�� ��ȯ�Ѵ�
	*/
	std::vector<IgEdge *> halfedge_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	face �ֺ��� halfedge
	*
	*	\param	face[in]	������ ������ face
	*
	*	\return	face[in]�� �ֺ� halfedge�� �ּҸ� ��ȯ�Ѵ�
	*/
	std::vector<IgEdge *> halfedge_around_face(const IgFace *face);
	
	/*!
	*	\brief	vertex �ֺ��� face
	*
	*	\param	vertex[in]	������ ������ vertex
	*
	*	\return	vertex[in]�� �ֺ� face�� �����͸� ��ȯ�Ѵ�
	*/
	std::vector<IgFace *> faces_around_vertex(const IgVertex *vertex);

	/*!
	*	\brief	���ֺ��� halfedge
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	halfedge[in]�� ���ֺ��� halfedge�� ������
	*/
	IgEdge *opposite(const IgEdge *halfedge);

	/*!
	*	\brief	���� halfedge
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	halfedge[in] ������ halfedge�� ������
	*/
	IgEdge *next(const IgEdge *halfedge);

	/*!
	*	\brief	���� halfedge
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	halfedge[in] ������ halfedge�� ������
	*/
	IgEdge *prev(const IgEdge *halfedge);

	/*!
	*	\brief	halfedge�� �����ϴ� face
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	halfedge[in] �� �����ϴ� face�� ��ȯ�Ѵ�
	*/
	IgFace *face(const IgEdge *halfedge);

	/*!
	*	\brief	halfedge�� ����
	*
	*	\return	IgMesh�� halfedge�� ������ ��ȯ�Ѵ�
	*/
	unsigned int number_of_halfedges() const;

	/*!
	*	\brief	vertex�� ����
	*
	*	\return	IgMesh�� vertex�� ������ ��ȯ�Ѵ�
	*/
	unsigned int number_of_vertices() const;

	/*!
	*	\brief	face�� ����
	*
	*	\return	IgMesh�� face�� ������ ��ȯ�Ѵ�
	*/
	unsigned int number_of_faces() const;

	/*!
	*	\brief	halfedge�� ���� (data�� ������ �������� �ʰ� validity�� �ٲ�)
	*
	*	\param	halfedge[in]	������ halfedge
	*
	*	\return	IgMesh�� halfedge�� �����Ѵ�
	*/
	bool remove(IgEdge *halfedge);

	/*!
	*	\brief	face�� ���� (data�� ������ �������� �ʰ� validity�� �ٲ�)
	*
	*	\param	face[in]	������ face
	*
	*	\return	IgMesh�� face�� �����Ѵ�
	*/
	bool remove(IgFace *face);

	/*!
	*	\brief	vertex�� ���� (data�� ������ �������� �ʰ� validity�� �ٲ�)
	*
	*	\param	vertex[in]	������ vertex
	*
	*	\return	IgMesh�� vertex�� �����Ѵ�
	*/
	bool remove(IgVertex *vertex);

	/*!
	*	\brief	halfedge�� �߰��ϰ� Valid�� ��ü�� ������ ������Ʈ�Ѵ�.
	*
	*	\param	halfedge[in]	�߰��� halfedge
	*
	*	\return	IgMesh�� halfedge�� �߰��Ѵ�
	*/
	void add(IgEdge *halfedge);

	/*!
	*	\brief	face�� �߰��ϰ� Valid�� ��ü�� ������ ������Ʈ�Ѵ�.
	*
	*	\param	face[in]	�߰��� face
	*
	*	\return	IgMesh�� face�� �߰��Ѵ�
	*/
	void add(IgFace *face);

	/*!
	*	\brief	vertex�� �߰��ϰ� Valid�� ��ü�� ������ ������Ʈ�Ѵ�.
	*
	*	\param	vertex[in]	�߰��� vertex
	*
	*	\return	IgMesh�� vertex�� �߰��Ѵ�
	*/
	void add(IgVertex *vertex);

	/*!
	*	\brief	Validity�� false�� face, halfedge, vertex�� ��� ����
	*	\note	Validity�� False�� ��ü�� delete�ϰ� ���Ӱ� index�� �ο��Ѵ�.
	*
	*	\return	validity�� false�� face, halfedge, vertex�� ��� �����Ѵ�
	*/
	void garbage_collection();

	/*!
	*	\brief	IgMesh���� halfedge�� flip
	*
	*	\param	halfedge[in]	flip�� halfedge
	*
	*	\return	flip�� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�
	*/
	bool flip(IgEdge *halfedge);

	/*!
	*	\brief	IgMesh���� halfedge�� flip (intrinsic)
	*
	*	\param	halfedge[in]	flip�� halfedge
	*
	*	\return	flip�� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�
	*/
	bool flip_intrinsic(IgEdge *halfedge);

	/*!
	*	\brief	IgMesh�� delaunay triangulation �˰����� ����
	*
	*	\param	intrinsic[in]	true�� ��� intrinsic delaunay triangulation�� �Ѵ�
	*/
	void delaunay_triangulation(bool intrinsic);

	/*!
	*	\brief	Laplacian matrix (cotangent weight)�� ���Ѵ�.
	*
	*	\param	D[in]	���� ������ ������ ����ȴ�.
	*	\param	M[in]	���� ����ġ�� ����ȴ�.
	*/
	void get_laplacian_matrix(Eigen::SparseMatrix<double> &D, Eigen::SparseMatrix<double> &M);

	/*!
	*	\brief	IgMesh�� obj ���Ϸ� export (�̿ϼ�)
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_obj(const char *filename);

	/*!
	*	\brief	IgMesh�� stl ���Ϸ� export (�̿ϼ�)
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_stl(const char *filename);

	/*!
	*	\brief	IgMesh�� off ���Ϸ� export
	*
	*	\param	filename[in]	filename
	*/
	void write_smesh_off(const char *filename);
};






