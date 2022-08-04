#pragma once

// Ŭ���� ����
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
*	\brief	���� ������ ��ü�� �⺻ Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date	2018-01-01
*/
class EgObject
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	��ü�� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� ��ü�� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return ���� ��ǥ�迡�� ǥ���� ��ü�� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	��ü�� �����Ѵ�.
	*
	*	\param	EC[in]		���� ��ǥ��(���� ��ǥ�� ����)
	*	\param	t[in]		������ ��ü�� �̵� ����(���� ��ǥ�� ����)
	*	\param	q[in]		������ ��ü�� ȸ�� ����(���� ��ǥ�� ����)
	*	\param	s[in]		������ ��ü�� ������ ����(���� ��ǥ�� ����)
	*	\param	bFirst[in]	���� ��ü���� ���ÿ� ������ ��� ù ��° ��ü�� ���� ����
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	���� ���� ��ü�� ������ �Ѵ�.
	*
	*	\param  r[in]	������ red ����
	*	\param  g[in]	������ green ����
	*	\param  b[in]	������ blue ����
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*!
	*	\brief	������
	*/
	EgObject() {};

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgObject() {};
};

/*!
*	\class	EgVertex
*	\brief	�޽� ������ ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	2018-01-25
*/
class EgVertex : public EgObject
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	������ ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*
	*	\return ������ ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� ������ ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return ���� ��ǥ�迡�� ǥ���� ������ ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	������ �����Ѵ�.
	*
	*	\param	EC[in]		���� ��ǥ��(���� ��ǥ�� ����)
	*	\param	t[in]		������ ��ü�� �̵� ����(���� ��ǥ�� ����)
	*	\param	q[in]		������ ��ü�� ȸ�� ����(���� ��ǥ�� ����)
	*	\param	s[in]		������ ��ü�� ������ ����(���� ��ǥ�� ����)
	*	\param	bFirst[in]	���� ��ü���� ���ÿ� ������ ��� ù ��° ��ü�� ���� ����
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	���� ���� ������ ������ �Ѵ�.
	*
	*	\param  r[in]	������ red ����
	*	\param  g[in]	������ green ����
	*	\param  b[in]	������ blue ����
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \brief ������ ���Ե� �޽��� ������ */
	EgMesh *m_pMesh;

	/*! \brief ������ �ε��� */
	int m_Idx;

	/*! \brief ������ 3���� ��ǥ */
	EgPos m_Pos;

	/*! \brief ������ ���� */
	EgVec3 m_Color;

	/*! \brief ������ ���� ����ġ */
	float m_EditWgt;

	/*! \brief �������� �����ϴ� �������� ������ �迭 */
	std::vector<EgEdge *> m_pEdges;

public:
	/*!
	*	\brief	������
	*
	*	\param	x[in]	������ x ��ǥ
	*	\param	y[in]	������ y ��ǥ
	*	\param	z[in]	������ z ��ǥ
	*/
	EgVertex(double x = 0.0, double y = 0.0, double z = 0.0);

	/*!
	*	\brief	������
	*
	*	\param	Pos[in]	������ ��ǥ
	*/
	EgVertex(EgPos Pos);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgVertex();

	/*!
	*	\brief	������ ����(������ ����� ������ ��)�� ��ȯ�Ѵ�.
	*	\note	���� ������ ��� ������ ������ �ﰢ�� ���� ����.
	*
	*	\return ���� ������ ��ȯ�Ѵ�.
	*/
	int GetDegree();

	/*!
	*	\brief	������ 1�� �̿� ������ ���Ѵ�.
	*
	*	\param	Verts[out]	1�� �̿� �������� �����Ͱ� ����ȴ�.
	*	\param	bCCW[in]	1�� �̿� ������ �ݽð� �������� �����Ϸ��� true
	*
	*	\return 1�� ������ ��(degree)�� ��ȯ�Ѵ�.
	*/
	int GetOneRingVert(std::vector<EgVertex *> &Verts, bool bCCW = false);

	/*!
	*	\brief	������ �����ϴ� 1�� �ﰢ���� ���Ѵ�.
	*
	*	\param	Faces[out]	������ �����ϴ� �ﰢ������ �����Ͱ� ����ȴ�.
	*
	*	\return ������ �����ϴ� 1�� �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int GetOneRingFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	������ 1�� ��� ������ ���Ѵ�.
	*
	*	\param	Edges[out]	��� �������� �����Ͱ� ����ȴ�.
	*
	*	\return ������ 1�� ��� ������ ���� ��ȯ�Ѵ�.
	*/
	int GetOneRingEdge(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	�������� ����ϴ� ������ ���Ѵ�.
	*
	*	\param	Edges[out]	�������� ����ϴ� �������� �����Ͱ� �ݽð� �������� ����ȴ�.
	*
	*	\return �������� ����ϴ� ������ ���� ��ȯ�Ѵ�.
	*/
	int GetOutGoingEdge(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	������ 1�� �̿� ������ ���Ѵ�.
	*
	*	\return 1���� �̿� ������ ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgVertex *> GetOneRingVert();

	/*!
	*	\brief	������ �����ϴ� 1�� �ﰢ���� ���Ѵ�.
	*
	*	\return ������ �����ϴ� 1�� �ﰢ�� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgFace *> GetOneRingFace();

	/*!
	*	\brief	������ 1�� ��� ������ ���Ѵ�.
	*
	*	\return ������ 1�� ��� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgEdge *> GetOneRingEdge();

	/*!
	*	\brief	�������� ����ϴ� ������ ���Ѵ�.
	*
	*	\return �������� ����ϴ� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgEdge *> GetOutGoingEdge();

	/* !
	*	\brief	��� ���� ���θ� �����Ѵ�.
	*
	*	\return ��� �����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsBndry();

	/* !
	*	\brief	�ڳ� ���� ���θ� �����Ѵ�.
	*
	*	\return �ڳ� �����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsCorner();

	/*!
	*	\brief	������ ������ ������ �ִ��� �Ǵ��Ѵ�.
	*
	*	\return	������ ������ ������ ������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsConvex();

	/*!
	*	\brief	������ ������ ������ �ִ��� �Ǵ��Ѵ�.
	*
	*	\return	������ ������ ������ ������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsConcave();

	/*!
	*	\brief	���� ���������� �˻��Ѵ�.
	*
	*	\return	���� �����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsIsolated();

	/*!
	*	\brief	�������� �����ϴ� ���� �߿� complex(non-manifold) ������ �ִ��� �����Ѵ�.
	*
	*	\return	Complex ������ �����ϰ� �ִٸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool HasComplexEdge();

	/*!
	*	\brief	������ �Է� ������ ����Ǿ� �ִ��� �����Ѵ�.
	*
	*	\param	v[in]	�Է� ����
	*
	*	\return	������ v�� ����Ǿ� ������ ������ ��ȯ�ϰ�, �ƴϸ� NULL�� ��ȯ�Ѵ�.
	*/
	EgEdge *IsAdjacent(EgVertex *v);

	/*!
	*	\brief	������ ��� ���� ������ ���Ѵ�.
	*
	*	\param	bWgt[in]	���� ����ġ ���� ����
	*
	*	\return ������ ��� ���� ������ ��ȯ�Ѵ�.
	*/
	EgVec3 GetAvgNormal(bool bWgt = false);

	/*!
	*	\breif	������ 1-�� �������� �����߽��� ��ȯ�Ѵ�.
	*
	*	\return ������ 1-�� �������� �����߽��� ��ȯ�Ѵ�.
	*/
	EgPos GetOneRingCenter();

	/*!
	*	\brief	������ ��ġ�� perturbation �Ѵ�
	*
	*	\param	rate[in]	���� �߽� �������� ������ ����
	*
	*	\return	����� ������ ��ġ�� ��ȯ�Ѵ�.
	*/
	EgPos Perturbate(double rate);

	/*!
	*	\brief	�������� �����ϴ� ���� ����Ʈ���� ������ �����Ѵ�.
	*	\note	������ ������: 2021-01-08
	*
	*	\param	e[in]	������ ���� ������
	*
	*	\return	���� ��, �������� �����ϴ� ������ ���� ��ȯ�Ѵ�(������ ������ ���� ��� -1�� ��ȯ)
	*/
	int DeleteEdge(EgEdge *e);
};

/*!
*	\class	EgTexel
*	\brief	�޽��� �ؽ�ó ������ ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	2018-01-27
*/
class EgTexel
{
public:
	/*! \brief �ؽ�ó ������ �ε��� */
	int m_Idx;

	/*! \brief �ؽ�ó ��ǥ */
	EgVec2 m_UV;

public:
	/*!
	*	\brief	������
	*
	*	\param	u[in]	���� ���� �ؽ�ó ��ǥ
	*	\param	v[in]	���� ���� �ؽ�ó ��ǥ
	*/
	EgTexel(double u = 0.0, double v = 0.0);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgTexel();
};

/*!
*	\class	EgNormal
*	\brief	�޽��� ���� ������ ǥ���ϴ� Ŭ����
*
*	\author	����ȣ, ������
*	\date	27 Jun 2018
*/
class EgNormal
{
public:
	/*! \brief ������ �ε��� */
	int m_Idx;

	/*! \brief ������ ���� */
	EgVec3 m_Dir;

public:
	/*!	\brief	������
	*
	*	\param	nx[in]	������ x ��ǥ
	*	\param	ny[in]	������ y ��ǥ
	*	\param	nz[in]	������ z ��ǥ
	*/
	EgNormal(double nx = 0.0, double ny = 0.0, double nz = 0.0);

	/*!	\brief	������
	*
	*	\param	Dir[in]	������ ����
	*/
	EgNormal(EgVec3 Dir);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgNormal();
};

/*!
*	\class	EgEdge
*	\brief	�ﰢ���� ��������(Halfedge)�� ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	25 Jan 2018
*/
class EgEdge
{
public:
	/*! \brief ���� �������� ����� ���� */
	EgVertex *m_pVert;

	/*! \brief ���� �������� ����� �ؼ� */
	EgTexel *m_pTexel;

	/*! \brief ���� �������� ����� ���� */
	EgNormal *m_pNormal;

	/*! \brief ������ ���Ե� �ﰢ���� ���� ������ */
	EgFace *m_pFace;

	/*! \brief �ﰢ���� �����ϴ� ���� ������ ���� ������ */
	EgEdge *m_pNext;

	/*! \brief ������ �ﰢ���� �ݴ��� ������ ���� ������ */
	EgEdge *m_pMate;

	/*! \brief ������ �ο��� ���(����ġ, ����, ��� ����) ���� ����, �̻�� ���� = -1.0 */
	double m_Cost;

public:
	/*!
	*	\brief	������
	*
	*	\param	pVert[in]	������ �������� �Ҵ�� ������ ���� ������
	*	\param	pTexel[in]	������ �������� �Ҵ�� �ؼ��� ���� ������
	*	\param	pNormal[in] ������ �������� �Ҵ�� ������ ���� ������
	*/
	EgEdge(EgVertex *pVert, EgTexel *pTexel, EgNormal *pNormal);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgEdge();

	/*!
	*	\brief	������ ������ �ﰢ���� ���Ѵ�.
	*
	*	\param	Faces[out]	�ﰢ�� �����Ͱ� ����ȴ�.
	*
	*	\return ����Ʈ ������ �ִ� ��� 2, ����Ʈ ������ ���� ��� 1�� ��ȯ�ȴ�.
	*/
	int	GetIncidentFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	������ ������ �ﰢ���� ���Ѵ�.
	*
	*	\return ������ ������ �ﰢ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgFace *> GetIncidentFace();

	/*!
	*	\brief	��� ���� ���θ� �����Ѵ�.
	*
	*	\return ��� �����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsBndry();

	/*!
	*	\brief	������ �ؽ�ó ��� �������� �����Ѵ�.
	*
	*	\return �ؽ�ó ��� �����̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsTexBndry();

	/*!
	*	\brief	������ ���� �������� �˻��Ѵ�.
	*
	*	\return ������ ���Ű����� ��� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsCollapsible();

	/*!
	*	\brief	�ﰢ������ ������ ���ֺ��� �ִ� ����(0 ~ 180)�� ����Ѵ�.
	*
	*	\param	bRadian[in]		���� �̸� true, �ƴϸ� false
	*
	*	\return �ﰢ������ ������ ���ֺ��� �ִ� ������ ��ȯ�Ѵ�.
	*/
	double GetAngle(bool bRadian);

	/*!
	*	\brief	������ ���ֺ��� �ִ� ������ ��ź��Ʈ ���� ����Ѵ�.
	*
	*	\param	bPositive[in]	��� ��ź��Ʈ ���� ���� ��� true, �ƴϸ� false
	*
	*	\return ���� ��ź��Ʈ ���� ��ȯ�Ѵ�.
	*/
	double GetCotangent(bool bPositive);

	/*!
	*	\brief	������ ���̸� ���Ѵ�.
	*
	*	\return ������ ���̸� ��ȯ�Ѵ�.
	*/
	double GetLength();

	/*!
	*	\brief	���� �������� ������� ���Ѵ�.
	*	\note	�̰���
	*
	*	\return ���� ������� ��ȯ�Ѵ�.
	*/
	double GetNormalCurvature();

	/*!
	*	\brief	������ ���� ���͸� ��ȯ�Ѵ�.
	*
	*	\param	bNormalize[in]	���� ���͸� ����ȭ �Ϸ��� true, �ƴϸ� false
	*
	*	\return ������ ���� ����(������-����)�� ��ȯ�Ѵ�.
	*/
	EgVec3 GetDir(bool bNormalize);
};

/*!
*	\class	EgFace
*	\brief	�޽��� �ﰢ���� ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	2018-01-25
*/
class EgFace : public EgObject
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	�ﰢ���� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� �ﰢ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*	\note	���� ��ǥ��� �ﰢ���� ���� �߽ɿ��� ���ǵ�
	*
	*	\return ���� ��ǥ�迡�� ǥ���� �ﰢ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	�ﰢ���� ���� �޽��� �����Ѵ�.
	*
	*	\param	EC[in]		���� ��ǥ��(���� ��ǥ�� ����)
	*	\param	t[in]		������ ��ü�� �̵� ����(���� ��ǥ�� ����)
	*	\param	q[in]		������ ��ü�� ȸ�� ����(���� ��ǥ�� ����)
	*	\param	s[in]		������ ��ü�� ������ ����(���� ��ǥ�� ����)
	*	\param	bFirst[in]	���� ��ü���� ���ÿ� ������ ��� ù ��° ��ü�� ���� ����
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	���� ���� �ﰢ���� ������ �Ѵ�.
	*
	*	\param  r[in]	������ red ����
	*	\param  g[in]	������ green ����
	*	\param  b[in]	������ blue ����
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \brief �ﰢ���� �ε��� */
	int m_Idx;

	/*! \brief �ﰢ���� ���� ������ ���� ������ */
	EgEdge *m_pEdge;

	/*! \brief �ﰢ���� ����ϴ� ������ ���� ������ */
	EgMaterial *m_pMaterial;

	/*! \brief �ﰢ���� ���� �׷��� �̸� */
	std::string m_GroupName;

public:
	/*!
	*	\brief	������
	*
	*	\param	e0[in]			�ﰢ���� ù ��° ����
	*	\param	e1[in]			�ﰢ���� �� ��° ����
	*	\param	e2[in]			�ﰢ���� �� ��° ����
	*	\param	pMtl[in]		�ﰢ���� ����ϴ� ������ ���� ������
	*	\param	GroupName[in]	�ﰢ���� ���� �׷��� �̸�
	*/
	EgFace(EgEdge *e0, EgEdge *e1, EgEdge *e2, EgMaterial *pMtl, std::string GroupName);

	/*!
	*	\brief ������
	*
	*	\param v0[in]			�ﰢ���� ù ��° ����
	*	\param v1[in]			�ﰢ���� �� ��° ����
	*	\param v2[in]			�ﰢ���� �� ��° ����
	*	\param t0[in]			�ﰢ���� ù ��° ������ �ؽ�ó ��ǥ
	*	\param t1[in]			�ﰢ���� �� ��° ������ �ؽ�ó ��ǥ
	*	\param t2[in]			�ﰢ���� �� ��° ������ �ؽ�ó ��ǥ
	*	\param n0[in]			�ﰢ���� ù ��° ������ ����
	*	\param n1[in]			�ﰢ���� �� ��° ������ ����
	*	\param n2[in]			�ﰢ���� �� ��° ������ ����
	*	\param pMtl[in]			�ﰢ���� ����ϴ� ������ ���� ������
	*	\param GroupName[in]	�ﰢ���� ���� �׷��� �̸�
	*/
	EgFace(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2,	EgNormal *n0, EgNormal *n1, EgNormal *n2, EgMaterial *pMtl, std::string GroupName);

	/*!
	*	\brief �Ҹ���
	*/
	virtual ~EgFace();
	
	/*!
	*	\brief	�ﰢ���� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgEdge *> &Edges();

	/*!
	*	\brief	�ﰢ���� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgVertex *> &Verts();

	/*!
	*	\brief	�ﰢ�� ������ �����͸� ��ȯ�Ѵ�.
	*
	*	\param	vIdx[in]	�ﰢ���� �����ϴ� ������ �ε���(0, 1, 2)
	*
	*	\return �ε����� �����Ǵ� ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgVertex *GetVertex(int vidx);

	/*!
	*	\brief	�ﰢ������ �ؽ�ó ������ �����͸� ��ȯ�Ѵ�.
	*
	*	\param	tidx[in]	�ﰢ���� �����ϴ� �ؽ�ó ������ �ε���(0, 1, 2)
	*
	*	\return �ε����� �����Ǵ� �ؽ�ó ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgTexel *GetTexel(int tidx);

	/*!
	*	\brief	�ﰢ������ ������ �����͸� ��ȯ�Ѵ�.
	*
	*	\param	nIdx[in]	�ﰢ���� �����ϴ� ������ �ε���(0, 1, 2)
	*
	*	\return �ε����� �����ϴ� ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgNormal *GetNormal(int nidx);
	
	/*!
	*	\brief	�ﰢ���� ���� �����͸� ��ȯ�Ѵ�.
	*
	*	\param	eIdx[in]	�ﰢ���� �����ϴ� ������ �ε���(0, 1, 2)
	*
	*	\return �ε����� �����Ǵ� ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgEdge *GetEdge(int eidx);

	/*!
	*	\brief	�ﰢ������ ������ ��ǥ�� ��ȯ�Ѵ�.
	*
	*	\param	vidx[in]	�ﰢ���� �����ϴ� ���� �ε���(0, 1, 2)
	*
	*	\return �ε����� �����ϴ� ������ ��ǥ�� ��ȯ�Ѵ�.
	*/
	EgPos GetVertexPos(int vidx);

	/*!
	*	\brief	�ﰢ������ ������ �Ҵ�� �ؽ�ó ��ǥ�� ��ȯ�Ѵ�.
	*
	*	\param	tidx[in]	�ﰢ���� �����ϴ� �������� �ε���(0, 1, 2)
	*
	*	\return �ε����� �����ϴ� �ؽ�ó ��ǥ�� ��ȯ�Ѵ�.
	*/
	EgVec2 GetTexelCoord(int tidx);

	/*!
	*	\brief	�ﰢ������ ���������� �Ҵ�� ������ ������ ��ȯ�Ѵ�.
	*
	*	\param	nidx[in]	�ﰢ���� �����ϴ� �������� �ε���(0, 1, 2)
	*	\param	bLocal[in]	��ü�� �𵨸� ��ǥ�迡�� ǥ���� ������ ��� true, ���� ��ǥ�迡�� ǥ���� ��� false
	*
	*	\return �ε����� �����ϴ� ������ ������ ��ȯ�Ѵ�.
	*/
	EgVec3 GetNormalDir(int nidx, bool bLocal);

	/*!
	*	\brief	�ﰢ���� ���� �������͸� ����Ѵ�.
	*
	*	\param	bLocal[in]	��ü�� �𵨸� ��ǥ�迡�� ǥ���� ������ ��� true, ���� ��ǥ�迡�� ǥ���� ��� false
	*
	*	\return �ﰢ���� ���� �������͸� ��ȯ�Ѵ�.
	*/
	EgVec3 GetFaceNormal(bool bLocal);

	/*!
	*	\brief	�ﰢ���� �����ϴ� ������ �ε��� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� �����ϴ� ������ �ε��� �迭�� ���� �����͸� ��ȯ�Ѵ�.
	*/
	int *GetVertexIdxs();

	/*!
	*	\brief	�ﰢ���� �����ϴ� �ؽ�ó ������ �ε��� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� �����ϴ� �ؽ�ó ������ �ε��� �迭�� ���� �����͸� ��ȯ�Ѵ�.
	*/
	int *GetTexelIdxs();

	/*!
	*	\brief	�ﰢ���� �����ϴ� ������ �ε��� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �ﰢ���� �����ϴ� ������ �ε��� �迭�� ���� �����͸� ��ȯ�Ѵ�.
	*/
	int *GetNormalIdxs();

	/*!
	*	\brief	�ﰢ������ ������ �ε����� ��ȯ�Ѵ�.
	*
	*	\param	e[in]	ã�� ������ ���� ������
	*
	*	\return �ﰢ������ ������ �ε����� ��ȯ�Ѵ�.
	*/
	int GetEdgeIdx(EgEdge *pEdge);

	/*!
	*	\brief	�ﰢ���� ������ ����Ѵ�.
	*
	*	\return ���� ������ ��ȯ�Ѵ�.
	*/
	double GetArea();

	/*!
	*	\brief	�ﰢ���� �ѷ��� ���̸� ����Ѵ�.
	*
	*	\return	���� �ѷ��� ���̸� ��ȯ�Ѵ�.
	*/
	double GetPerimeter();

	/*!
	*	\brief	�ﰢ���� ���� �߽��� ����Ѵ�.
	*
	*	\param	bLocal[in]	��ü�� �𵨸� ��ǥ�迡�� ǥ���� ��� true, ���� ��ǥ�迡�� ǥ���� ��� false
	*
	*	\return �ﰢ���� ���� �߽��� ��ġ�� ��ȯ�Ѵ�.
	*/
	EgPos GetCOG(bool bLocal);

	/*!
	*	\brief	�ﰢ�� ������ ������ �ﰢ���� ���Ѵ�.
	*
	*	\param	Faces[out]	������ ������ �ﰢ���� �����Ͱ� ����ȴ�.
	*
	*	\return ������ ������ �ﰢ���� ����(0, 1, 2, 3)�� ��ȯ�Ѵ�.
	*/
	int GetAdjacentFace(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	���� �ﰢ�� ���θ� �����Ѵ�.
	*
	*	\param	pFace[in]	������ �ﰢ��
	*
	*	\return	���� �ﰢ���̸� ���� ������ �����͸� ��ȯ�ϰ�, �ƴϸ� NULL�� ��ȯ�Ѵ�.
	*/
	EgEdge *IsAdjacentFace(EgFace *pFace);

	/*!
	*	\brief	�ﰢ���� ��� �ﰢ������ �����Ѵ�.
	*
	*	\return	��� �ﰢ���̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsBndryFace();

	/*!
	*	\brief	���� �ﰢ������ �����Ѵ�.
	*
	*	\return	���� �ﰢ���̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsIsolated();
};

/*!
*	\class	EgTexture
*	\brief	�޽��� ����ϴ� �ؽ�ó�� ǥ���ϴ� Ŭ����
*
*	\author ������
*	\date	2018-11-29
*/
class EgTexture
{
	/*!
	*	\brief	1���� �ؽ�ó�� �����Ѵ�.
	*	\note	������ ������: 2022-04-21
	*
	*	\param	id[in]	������ �ؽ�ó�� ����(0: Rainbow, 1: Heat, 2: BYGCR)
	*/
	friend EgTexture *create_texture_1d(int id);

public:
	/*! brief �ؽ�ó�� ������ �̸�(Ȯ��� ����) */
	std::string m_FileName;

	/*! brief OpenGL �ؽ�ó�� ������ ��� ���̵�(1���� ����) */
	GLuint m_TexId;

public:
	/*!
	*	\brief ������
	*/
	EgTexture();

	/*!
	*	\brief �Ҹ���
	*/
	~EgTexture();

	/*!
	*	\brief	�ؽ�ó ���Ϸκ��� OpenGL �ؽ�ó�� �����Ѵ�.
	*
	*	\param	fname[in]	�ؽ�ó ���ϸ�
	*
	*	\return �����̸� true, ���и� false�� ��ȯ�Ѵ�.
	*/
	bool LoadTexture(const char *fname);
};

/*!
*	\class	EgMaterial
*	\brief	�޽��� ����ϴ� ������ ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	2018-07-02
*/
class EgMaterial
{
public:
	/*! \brief ������ �ε��� */
	int m_Idx;

	/*! \brief ������ �̸� */
	std::string m_Name;

	/*! \brief ������ �ֺ��� �ݻ� ��� */
	GLfloat m_Ambient[4];

	/*! \brief ������ ���ݻ� ��� */
	GLfloat m_Diffuse[4];

	/*! \brief ������ ���ݻ� ��� */
	GLfloat m_Specular[4];

	/*! \brief ������ ���ݻ� ���� */
	GLfloat m_Shiness;

	/*! \brief ������ ����ϴ� �ؽ�ó�� ���� ������(�ؽ�ó�� ���� ������ ���� �� �� ����) */
	EgTexture *m_pTexture;

public:
	/*!
	*	\brief ������
	*
	*	\param Name ������ ������ �̸�
	*/
	EgMaterial(std::string Name);

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		������ ����
	*/
	EgMaterial(const EgMaterial &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgMaterial();

	/*!
	*	\brief	���� ������ ��ü�� �̸��� ��ȯ�Ѵ�.
	*
	*	\return	���� ������ ��ü�� �̸��� ��ȯ�Ѵ�.
	*/
	std::string GetNewObjName();

	/*!
	*	\brief	������ �ֺ��� �ݻ� ����� �����Ѵ�.
	*
	*	\param	r[in] Red ���п� ���� �ݻ���
	*	\param	g[in] Green ���п� ���� �ݻ���
	*	\param	b[in] Blue ���п� ���� �ݻ���
	*	\param	a[in] Alpha ������ ���� ���� ��
	*/
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	������ ���ݻ� ����� �����Ѵ�.
	*
	*	\param	r[in] Red ���п� ���� �ݻ���
	*	\param	g[in] Green ���п� ���� �ݻ���
	*	\param	b[in] Blue ���п� ���� �ݻ���
	*	\param	a[in] Alpha ������ ���� ���� ��
	*/
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	������ ���ݻ� ����� �����Ѵ�.
	*
	*	\param	r[in] Red ���п� ���� �ݻ���
	*	\param	g[in] Green ���п� ���� �ݻ���
	*	\param	b[in] Blue ���п� ���� �ݻ���
	*	\param	a[in] Alpha ������ ���� ���� ��
	*/
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a = 1.0f);

	/*!
	*	\brief	������ ���ݻ� ������ �����Ѵ�.
	*
	*	\param	s[in] ������ ���ݻ� ����
	*/
	void SetShiness(GLfloat s);

	/*!
	*	\brief	������ �ؽ�ó�� �����Ѵ�.
	*
	*	\param	pTexture[in]	������ �ؽ�ó�� ���� ������
	*/
	void SetTexture(EgTexture *pTexture);

	/*!
	*	\brief	������ Ȱ��ȭ �Ѵ�.
	*
	*	\param	bTexture[in]	�ؽ�ó ���� ����
	*/
	void Enable();

	/*!
	*	\brief	������ ��Ȱ��ȭ �Ѵ�.
	*/
	void Disable();
};

/*!
*	\class	EgBox
*	\brief	3���� ��鿡�� ���� ��ǥ���� �࿡ ������ �ٿ�� �ڽ��� ǥ���ϴ� Ŭ����
*
*	\author ������(shyun@dongguk.edu)
*	\date	2015-01-29
*/
class EgBox
{
public:
	/*! \brief ��� ������ ��� �޽� */
	EgMesh *m_pMesh;

	/*! \brief ��� ������ �ּ���(�޽��� �𵨸� ��ǥ�迡�� ǥ��) */
	EgPos m_MinPt;

	/*! \brief ��� ������ �ִ���(�޽��� �𵨸� ��ǥ�迡�� ǥ��) */
	EgPos m_MaxPt;

public:
	/*!
	*	\brief	������
	*
	*	\param	minx[in]	��� ������ �ּ����� x ��ǥ
	*	\param	miny[in]	��� ������ �ּ����� y ��ǥ
	*	\param	minz[in]	��� ������ �ּ����� z ��ǥ
	*	\param	maxx[in]	��� ������ �ִ����� x ��ǥ
	*	\param	maxy[in]	��� ������ �ִ����� y ��ǥ
	*	\param	maxz[in]	��� ������ �ִ����� z ��ǥ
	*/
	EgBox(double minx = 0, double miny = 0, double minz = 0, double maxx = 0, double maxy = 0, double maxz = 0);

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		����� ��ü
	*/
	EgBox(const EgBox &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	~EgBox() {}
	
	/*!
	*	\brief	���� ������
	*
	*	\param	rhs[in]		���Ե� ��ü
	*
	*	\return ���Ե� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgBox &operator =(const EgBox &rhs);
	
	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� ��� ������ �𵨸� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return ���� ��ǥ�迡�� ǥ���� ��� ������ �𵨸� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	EgTrans GetMC();

	/*!
	*	\brief	�������� x�� ������ �ʺ� ��ȯ�Ѵ�.
	*
	*	\return	�������� x�� ������ �ʺ� ��ȯ�Ѵ�.
	*/
	double GetWidth();

	/*!
	*	\brief	�������� y�� ������ ���̸� ��ȯ�Ѵ�.
	*
	*	\return	�������� y�� ������ ���̸� ��ȯ�Ѵ�.
	*/
	double GetHeight();

	/*!
	*	\brief	�������� z�� ������ ���̸� ��ȯ�Ѵ�.
	*
	*	\return	�������� z�� ������ ���̸� ��ȯ�Ѵ�.
	*/
	double GetDepth();

	/*!
	*	\brief	�������� �밢���� ���̸� ��ȯ�Ѵ�.
	*
	*	\return �������� �밢���� ���̸� ��ȯ�Ѵ�.
	*/
	double GetDiagonal();

	/*!
	*	\brief �������� 8���� �𼭸� ������ ��ȯ�Ѵ�.
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
	*	\param Pt �������� 8���� �𼭸� ��ġ�� ����ȴ�.
	*	\param bLocal �𼭸� ������ ��ǥ��(true: �𵨸� ��ǥ��, false: ���� ��ǥ��)
	*/
	void GetCornerPts(EgPos *Pt, bool bLocal = true);

	/*!
	*	\brief	��� ���ڸ� ������ �Ѵ�.
	*
	*	\param	r[in]		��� ���� �׵θ��� ������ ����
	*	\param	g[in]		��� ���� �׵θ��� �ʷϻ� ����
	*	\param	b[in]		��� ���� �׵θ��� �Ķ��� ����
	*	\param	width[in]	��� ���� �׵θ��� �β�
	*/
	void Render(double r, double g, double b, double width);
};

/*! \brief �޽� ������ �ɼ� */
#define RENDER_POLYGON			0x0001
#define RENDER_WIRE				0x0002
#define RENDER_POINT			0x0004
#define RENDER_NORMAL			0x0008
#define RENDER_BACK_FACE		0x0010
#define RENDER_TEXTURE			0X0020

/*! \brief �޽� ���� �Ӽ� �ɼ� */
enum TypeNormal
{
	NORMAL_ASIS = 0,
	NORMAL_FACE = 1,
	NORMAL_VERTEX = 2,
};

/*!
*	\class	EgMesh
*	\brief	�ﰢ �޽��� ǥ���ϴ� Ŭ����
*
*	\author ����ȣ, ������
*	\date	2018-01-25
*/
class EgMesh : public EgObject
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	�ڽ��� �����Ѵ�.
	*
	*	\return �ڽ��� ������ ��ü�� �����͸� ��ȯ�Ѵ�.
	*/
	virtual EgMesh *CopyObject();

	/*!
	*	\brief	��ü�� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� �޽��� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return ���� ��ǥ�迡�� ǥ���� �޽��� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	�޽��� �����Ѵ�.
	*
	*	\param	EC[in]		���� ��ǥ��(���� ��ǥ�� ����)
	*	\param	t[in]		���� �̵� ����(���� ��ǥ�� ����)
	*	\param	q[in]		���� ȸ�� ����(���� ��ǥ�� ����)
	*	\param	s[in]		���� ������ ����(���� ��ǥ�� ����)
	*	\param	bFirst[in]	���� ��ü���� ���ÿ� ������ ��� ù ��° ��ü�� ���� ����
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	�޽��� �𵨸� ��ǥ�踦 �����Ѵ�.
	*
	*	\param	Type[in]	����� �𵨸� ��ǥ���� Ÿ��(0: ���� ��ǥ��, 1: AABB, 2: OBB)
	*/
	virtual void UpdateMC(int Type);

	/*!
	*	\brief	���� ���� �޽��� ������ �Ѵ�.
	*
	*	\param  r[in]	������ red ����
	*	\param  g[in]	������ green ����
	*	\param  b[in]	������ blue ����
	*/
	virtual void RenderForEdit(float r, float g, float b);

	/*!
	*	\brief �޽��� ������ �Ѵ�.
	*/
	virtual void Render();

public:
	/*! \brief �޽��� �̸� */
	std::string m_Name;

	/*! \brief �޽��� ���ǵ� �𵨸� ��ǥ�� */
	EgTrans m_MC;

	/*! \brief ������ ������ �迭 */
	std::vector<EgVertex *> m_pVerts;

	/*! \brief �ؽ�ó ������ ������ �迭 */
	std::vector<EgTexel *> m_pTexels;

	/*! \brief ������ ������ �迭 */
	std::vector<EgNormal *> m_pNormals;

	/*! \brief �ﰢ���� ������ �迭 */
	std::vector<EgFace *> m_pFaces;

	/*! \brief ������ ������ �迭 */
	std::vector<EgMaterial *> m_pMaterials;

	/*! \brief �ؽ�ó�� ������ �迭(���� ������ ���� ����) */
	std::vector<EgTexture *> m_pTextures;

	/*! \brief �𵨸� ��ǥ�迡�� ǥ���� �޽��� ��� ���� */
	EgBox m_BndBox;

	/*! \brief ������ �ɼ�: RENDER_POLYGON, RENDER_WIRE, ... */
	unsigned int m_RenderOption;

	/*! \brief �޽��� ���� Ÿ��: NORMAL_FACE �Ǵ� NORMAL_VERTEX */
	TypeNormal m_NormalType;

	/*! \brief ��� �������� ���� ���� ����: (������, ������ ��ǥ �迭)�� ������ */
	std::map<std::string, std::vector<float>> m_VertexBuf;

	/*! \brief ��� �������� ���� �ؽ�ó ��ǥ ����: (������, �ؽ�ó ��ǥ �迭)�� ������ */
	std::map<std::string, std::vector<float>> m_TexelBuf;

	/*! \brief ��� �������� ���� ���� ����: (������, ������ ��ǥ �迭)�� ������ */
	std::map<std::string, std::vector<float>> m_NormalBuf;

	/*! \brief �ﰢ�� ���̵�� �������� ���÷��� ����Ʈ */
	GLuint m_DisplayListOfFaceId;

	/*! \brief �޽��� �м� ����� �������� ���÷��� ����Ʈ((����)�Ÿ���, Isophotic �Ÿ���, ���� �Ÿ���, ���� �Ÿ���, �����Ÿ��׷����Ʈ��) */
	GLuint m_DisplayListOfAnalysis;

protected:
	/*!
	*	\brief	�ε����� -1�� �޽��� �ﰢ���� �����Ѵ�.
	*	\note	(1) �ﰢ�� ���� �������� ���� ������ �ʴ� ����/�ؼ�/������ ���ŵ��� �ʴ´�.
	*			(2) ���� ����/�ؼ�/������ �����ϱ� ���ؼ��� delete_unused_*() �Լ��� �߰��� ȣ���ؾ� �Ѵ�.
	*			(3) ������ ������: 2021-02-17
	*	\return ���� �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int DeleteFaces();

	/*!
	*	\brief	�޽��� ��� ���� ������ �����Ѵ�.
	*	\note	������ ������: 2021-02-17
	*/
	void DeleteMesh();

	/*!
	*	\brief	���� ���۸� �����Ѵ�.
	*/
	void UpdateVertexBuf();

	/*!
	*	\brief	�ؽ�ó ���۸� �����Ѵ�.
	*/
	void UpdateTexelBuf();

	/*!
	*	\brief	���� ���۸� �����Ѵ�.
	*/
	void UpdateNormalBuf();
	

public:
	/*!
	*	\brief	������
	*
	*	\param	Name[in]	������ �޽��� �̸�
	*/
	EgMesh(std::string Name = "");

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		����� �޽� ��ü
	*/
	EgMesh(const EgMesh &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgMesh();

	/*!
	*	\brief	�޽��� ������ �߰��Ѵ�.
	*
	*	\param	pVert[in]	�߰��� ������ ���� ������
	*/
	void AddVertex(EgVertex *pVert);

	/*!
	*	\brief	�޽��� �ؼ��� �߰��Ѵ�.
	*
	*	\param	pTexel[in]	�߰��� �ؼ��� ���� ������
	*/
	void AddTexel(EgTexel *pTexel);

	/*!
	*	\brief	�޽��� ������ �߰��Ѵ�.
	*
	*	\param	pNormal[in]		�߰��� ������ ���� ������
	*/
	void AddNormal(EgNormal *pNormal);

	/*!
	*	\brief	�޽��� �ﰢ���� �߰��Ѵ�.
	*
	*	\param	pFace[in]	�߰��� �ﰢ���� ���� ������
	*/
	void AddFace(EgFace *pFace);

	/*!
	*	\brief	�޽��� ������ �߰��Ѵ�.
	*
	*	\param	pMaterial[in]	�߰��� ������ ���� ������
	*/
	void AddMaterial(EgMaterial *pMaterial);

	/*!
	*	\brief	�޽��� �ﰢ���� �����Ѵ�.
	*	\note	(1) �ﰢ�� ���� �������� ���� ������ �ʴ� ����/�ؼ�/������ ���ŵ��� �ʴ´�.
	*			(2) ���� ����/�ؼ�/������ �����ϱ� ���ؼ��� delete_unused_*() �Լ��� �߰��� ȣ���ؾ� �Ѵ�.
	*			(3) ������ ������: 2021-02-17
	*
	*	\param	Faces[in]	������ �ﰢ�� ����Ʈ
	*
	*	\return ���� �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int DeleteFaces(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	�޽� �������� �����Ѵ�.
	*	\note	(1) ������ ���Ե� �ﰢ���鵵 �Բ� ���ŵȴ�.
	*			(2) ���� ���� �������� ���� ������ �ʴ� �ؼ�/������ ���ŵ��� �ʴ´�.
	*			(3) ���� �ؼ�/������ �����ϱ� ���ؼ��� delete_unused_*() �Լ��� �߰��� ȣ���ؾ� �Ѵ�.
	*			(4) ������ ������: 2021-02-17
	*
	*	\param	Verts[in]	������ ������ ����Ʈ
	*
	*	\return ���� ������ ������ ��ȯ�Ѵ�.
	*/
	int DeleteVerts(std::vector<EgVertex *> &Verts);

	/*!
	*	\brief	�޽��� ������ �����Ѵ�.
	*	\note	(1) ������ ���Ե� �ﰢ���鵵 �Բ� ���ŵȴ�.
	*			(2) ���� ���� �������� ���� ������ �ʴ� ����/�ؼ�/������ ���ŵ��� �ʴ´�.
	*			(3) ���� ����/�ؼ�/������ �����ϱ� ���ؼ��� delete_unused_*() �Լ��� �߰��� ȣ���ؾ� �Ѵ�.
	*			(4) ������ ������: 2021-01-08
	*
	*	\param	pEdges[in]		������ ���� ����Ʈ
	*
	*	\return ���� �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int DeleteEdges(std::vector<EgEdge *> &Edges);

	/*!
	*	\brief	�޽��� ���� ���̸� ����Ͽ� m_Cost ������ ����Ѵ�.
	*
	*	\param	MetricType[in]	�Ÿ� �Լ� Ÿ��(0: ���, 1: ����(�ּ� �ְ�� ������ ª��), 2: ����(�ּ� �ְ�� ������ ���))
	*/
	void UpdateEdgeLength(int MetricType = 0);

	/*!
	*	\brief	������ �ݴ��� ���� ������ �����Ѵ�.

	*	\param	pVert[in]	������ ������
	*/
	void UpdateEdgeMate(EgVertex *pVert = NULL);

	/*!
	*	\brief	������ ���� ����Ʈ�� ������ �����ϰ�, ���ο� m_pNormals�� �����Ѵ�.
	*	\note	������ ������: 2021-04-16
	*
	*	\param	NormalType[in]	������ ����(NORMAL_ASIS: ����, NORMAL_FACE: �ﰢ�� ����, NORMAL_VERTEX: ���� ����)
	*/
	void UpdateNormal(TypeNormal NormalType = NORMAL_ASIS);

	/*!
	*	\brief	�޽� ���� ������ ������ �����Ѵ�.
	*
	*	\param	Faces[in]	���� ������ �ﰢ���� ����Ʈ
	*/
	void UpdateNormal(const std::vector<EgFace *> &Faces);

	/*!
	*	\brief	�޽� ���� ������ ������ �����Ѵ�.
	*
	*	\param	Verts[in]	���� ������ ������ ����Ʈ
	*/
	void UpdateNormal(const std::vector<EgVertex *> &Verts);

	/*!
	*	\brief	�޽��� ������ �Ųٷ� �ٲ۴�.
	*/
	void ReverseNormal();

	/*!
	*	\brief	�޽��� �ѷ��δ� ��� ���ڸ� �����Ѵ�.
	*/
	void UpdateBndBox();

	/*!
	*	\brief �޽��� ũ�⸦ �밢�� �������� ����ȭ �Ѵ�.
	*/
	void Normalize();

	/*!
	*	\brief	�޽� ������ �ε���(0, 1, 2, ...)�� �����Ѵ�.
	*
	*	\return ������ ������ ��ȯ�Ѵ�.
	*/
	int UpdateVertIdx();

	/*!
	*	\brief	�޽����� �ؼ��� �ε����� �����Ѵ�
	*
	*	\return �ؼ��� ������ ��ȯ�Ѵ�.
	*/
	int UpdateTexIdx();

	/*!
	*	\brief	�޽����� ������ �ε����� �����Ѵ�
	*
	*	\return ������ ������ ��ȯ�Ѵ�.
	*/
	int UpdateNormalIdx();

	/*!
	*	\brief	�޽����� �ﰢ���� �ε����� �����Ѵ�.
	*
	*	\return �ﰢ���� ������ ��ȯ�Ѵ�.
	*/
	int UpdateFaceIdx();

	/*!
	*	\brief	�޽����� ������ �ε����� �����Ѵ�.
	*
	*	\return ������ ������ ��ȯ�Ѵ�.
	*/
	int UpdateMaterialIdx();

	/*!
	*	\brief	�޽��� ������ ������ ��ȯ�Ѵ�.
	*
	*	\return �޽��� ������ ������ ��ȯ�Ѵ�.
	*/
	int GetNumVert();

	/*!
	*	\brief	�޽��� �ؼ��� ������ ��ȯ�Ѵ�.
	*
	*	\return �޽��� �ؼ��� ������ ��ȯ�Ѵ�.
	*/
	int GetNumTexel();

	/*!
	*	\brief	�޽��� ������ ������ ��ȯ�Ѵ�.
	*
	*	\return �޽��� ������ ������ ��ȯ�Ѵ�.
	*/
	int GetNumNormal();

	/*!
	*	\brief	�޽��� �ﰢ���� ������ ��ȯ�Ѵ�.
	*
	*	\return �޽��� �ﰢ���� ������ ��ȯ�Ѵ�.
	*/
	int GetNumFace();

	/*!
	*	\brief	�޽��� ������ ������ ��ȯ�Ѵ�.
	*
	*	\return �޽��� ������ ������ ��ȯ�Ѵ�.
	*/
	int GetNumMtrl();

	/*!
	*	\brief	�޽��� �ؽ�ó ��� ���θ� �����Ѵ�.
	*
	*	\return �޽��� �ؽ�ó�� ����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool HasTexture();

	/*!
	*	\brief	�޽��� �����ϴ� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �޽��� �����ϴ� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgVertex *> &Verts() { return m_pVerts; }

	/*!
	*	\brief	�޽��� �����ϴ� �ؼ� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �޽��� �����ϴ� �ؼ� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgTexel *> &Texels() { return m_pTexels; };

	/*!
	*	\brief	�޽��� �����ϴ� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �޽��� �����ϴ� ���� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgNormal *> &Normals() { return m_pNormals; }

	/*!
	*	\brief	�޽��� �����ϴ� �ﰢ�� ����Ʈ�� ��ȯ�Ѵ�.
	*
	*	\return �޽��� �����ϴ� �ﰢ�� ����Ʈ�� ��ȯ�Ѵ�.
	*/
	std::vector<EgFace *> &Faces() { return m_pFaces; }	

	/*!
	*	\brief	�޽��� �����ϴ� ������ �ּ� ���̸� ���Ѵ�.
	*
	*	\return ������ �ּ� ���̸� ��ȯ�Ѵ�.
	*/
	double GetMinEdgeLen();

	/*!
	*	\brief	�޽��� �����ϴ� ������ �ִ� ���̸� ���Ѵ�.
	*
	*	\return ������ �ִ� ���̸� ��ȯ�Ѵ�.
	*/
	double GetMaxEdgeLen();	

	/*!
	*	\brief	�޽��� �����ϴ� ������ ��� ���̸� ���Ѵ�.
	*
	*	\return ������ ��� ���̸� ��ȯ�Ѵ�.
	*/
	double GetAvgEdgeLen();

	/*!
	*	\brief	�޽� ���� ������ ����Ʈ�� ���Ѵ�.
	*
	*	\param	Normals[out]	���� ���͵��� ����ȴ�.
	*	\param	Type[in]		���� ������ Ÿ��(0: ����, 1: �ﰢ��)
	*/
	void GetNormalArray(std::vector<EgVec3> &Normals, int Type);

	/*!
	*	\brief	�޽��� Idx��° ������ �����͸� ã�´�.
	*
	*	\param	Idx[in]		������ �ε���(0���� ����)
	*
	*	\return �޽��� Idx��° ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgVertex *GetVert(int Idx);

	/*!
	*	\brief	�޽��� Idx��° �ؼ��� �����͸� ã�´�.
	*
	*	\param	Idx[in]		�ؼ��� �ε���(0���� ����)
	*
	*	\return �޽��� Idx��° �ؼ��� �����͸� ��ȯ�Ѵ�.
	*/
	EgTexel *GetTexel(int Idx);

	/*!
	*	\brief	�޽��� Idx��° ������ �����͸� ã�´�.
	*
	*	\param	Idx[in]		������ �ε���(0���� ����)
	*
	*	\return �޽��� Idx��° ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgNormal *GetNormal(int Idx);

	/*!
	*	\brief	�޽��� Idx��° �ﰢ���� �����͸� ã�´�.
	*
	*	\param	Idx[in]		�ﰢ���� �ε���(0���� ����)
	*
	*	\return �޽��� Idx��° �ﰢ���� �����͸� ��ȯ�Ѵ�.
	*/
	EgFace *GetFace(int Idx);

	/*!
	*	\brief	�޽��� Idx ��° ������ ã�´�.
	*
	*	\param	Idx[in]		������ �ε���
	*
	*	\return Idx ��° ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgMaterial *GetMaterial(int Idx);

	/*!
	*	\brief	�־��� �̸��� ���� ������ ã�´�.
	*
	*	\param	Name[in]	������ �̸�
	*
	*	\return �־��� �̸��� ���� ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgMaterial *GetMaterial(std::string Name);

	/*!
	*	\brief	�־��� �̸��� ���� �ؽ�ó�� ã�´�.
	*
	*	\param	Name[in]	�ؽ�ó ���ϸ�
	*
	*	\return �־��� �̸��� ���� �ؽ�ó�� �����͸� ��ȯ�Ѵ�.
	*/
	EgTexture *GetTexture(std::string Name);

	/*!
	*	\brief	�޽��� �ﰢ������ ������ �Ѵ�.
	*	\note	����, �븻 ���۸� ����Ѵ�.
	*/
	void RenderPolygon();

	/*!
	*	\brief	�޽��� �ؽ�ó�� ������ �Ѵ�
	*	\note	����, �븻, �ؽ�ó ���۸� ����Ѵ�.
	*/
	void RenderTexture();

	/*!
	*	\brief	������ �������� ���� �������Ѵ�.
	*/
	void RenderVertColor();

	/*!
	*	\brief	�޽��� ������ ������ �Ѵ�.
	*/
	void RenderPoint();

	/*!
	*	\brief	�޽��� ���̾����������� ������ �Ѵ�.
	*	\note	���� ���۸� ����Ѵ�.
	*/
	void RenderWire();

	/*!
	*	\brief	�޽��� �ﰢ���� ���ο� ������ �����Ѵ�.
	*
	*	\param	pMtl[in]	������ ���� ������
	*/
	void SetMaterial(EgMaterial *pMtl);

	/*!
	*	\brief	�޽� ������ ������ �����Ѵ�.
	*
	*	\param	Alpha[in]	������ ����
	*/
	void SetTransparent(GLfloat Alpha);
	
	/*!
	*	\brief ������ ���� ������ �������ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*/
	void CreateDisplayListOfLocalRegion();

	/*!
	*	\brief	�޽� ���� ��Į�� ���� ����ȭ�ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*
	*	\param	Values[in]			Values[i]�� i��° ������ �Ҵ�� ��Į�� ���� �����
	*	\param	Min[in]				������ �ּҰ�(0���� ����)
	*	\param	Max[in]				������ �ִ밪(1�� ����)
	*	\param	ColorMapId[in]		����� Į��� ���̵�(0: rainbow, 1: heat, 2: B-Y-G-C-B)
	*	\param	NumIsoLines[in]		Iso-line�� ��
	*	\param	IsoColor[in]		Iso-line�� ����
	*/
	void CreateDisplayListOfScalarField(std::vector<double> Values, double Min, double Max, int ColorMapId, int NumIsoLines, EgVec3 IsoColor);

	/*!
	*	\brief	�޽� ���� �������� ����ȭ�ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*
	*	\param	Values[in]		Values[i]�� i��° ���� �Ǵ� �ﰢ���� �Ҵ�� ���Ͱ� �����
	*	\param	bFace[in]		�������� �ﰢ������ ���ǵǾ����� true, �������� ���ǵǾ����� false
	*	\param	StColor[in]		���� �������� ����
	*	\param	EdColor[in]		���� ������ ����
	*/
	void CreateDisplayListOfVectorField(std::vector<EgVec3> Values, bool bFace, EgVec3 StColor, EgVec3 EdColor);

	/*!
	*	\brief	�޽� ���� �������� ����ȭ�ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*	\note	������ ������: 2021-06-13
	*
	*	\param	VF1[in]			VF1[i]�� i��° ���� �Ǵ� �ﰢ���� �Ҵ�� ù ��° ���Ͱ� �����
	*	\param	VF2[in]			VF2[i]�� i��° ���� �Ǵ� �ﰢ���� �Ҵ�� �� ��° ���Ͱ� �����
	*	\param	bFace[in]		�������� �ﰢ������ ���ǵǾ����� true, �������� ���ǵǾ����� false
	*	\param	StColor1[in]	ù ��° �������� ���� �������� ����
	*	\param	EdColor1[in]	ù ��° �������� ���� ������ ����
	*	\param	StColor2[in]	ù ��° �������� ���� �������� ����
	*	\param	EdColor2[in]	ù ��° �������� ���� ������ ����
	*/
	void CreateDisplayListOfVectorField(std::vector<EgVec3> &v1, std::vector<EgVec3> &v2, bool bFace, EgVec3 StColor1, EgVec3 EdColor1, EgVec3 StColor2, EgVec3 EdColor2);

	/*!
	*	\brief	������ �Ҵ�� ��Į�� ���� Iso-line�� �������ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*	\note	������ ������: 2020-11-03
	*
	*	\param	Values[in]			Values[i]�� i��° ������ �Ҵ�� ��Į�� ���� �����
	*	\param	MinVal[in]			������ Isovalue�� �ּҰ�
	*	\param	MaxVal[in]			������ Isovalue�� �ִ밪
	*	\param	NumIsoValues[in]	������ ������ Iso-value�� ��
	*/
	void CreateDisplayListOfIsoLines(std::vector<double> &Values, double MinVal, double MaxVal, int NumIsoVal);

	/*!
	*	\brief	�޽� �м��� ����� �������ϴ� ���÷��� ����Ʈ�� �����Ѵ�.
	*/
	void DeleteDisplayListOfAnalysis();
};

/*! \brief �޽� ���� ���� ��ġ Ÿ�� ������ */
enum TypeMeshPt
{
	PT_ON_V0 = 0,	// ���� V0 ���� ���� ��
	PT_ON_V1 = 1,	// ���� V1 ���� ���� ��
	PT_ON_V2 = 2,	// ���� V2 ���� ���� ��
	PT_ON_E0 = 3,	// �������� V0�� ���� ���� ���� ��
	PT_ON_E1 = 4,	// �������� V1�� ���� ���� ���� ��
	PT_ON_E2 = 5,	// �������� V2�� ���� ���� ���� ��
	PT_IN_TRI = 6,	// �ﰢ�� ������
	PT_OUT_TRI = 7,	// �ﰢ�� �ܺ���
	PT_UNKNOWN,
};

/*!
*	\class  EgMeshPt
*	\brief  �޽� ���� ���� ǥ���ϴ� Ŭ����
*
*	\author ������, ������
*	\date	2020-12-30
*/
class EgMeshPt : public EgObject
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	���� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*
	*	\return ���� ���Ե� �޽��� �����͸� ��ȯ�Ѵ�.
	*/
	virtual	EgMesh *GetMesh();

	/*!
	*	\brief	���� ��ǥ�迡�� ǥ���� ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*
	*	\return	���� ��ǥ�迡�� ǥ���� ���� ���� ��ǥ�踦 ��ȯ�Ѵ�.
	*/
	virtual EgTrans GetTrans();

	/*!
	*	\brief	���� ������ �ﰢ���� �����Ѵ�.
	*
	*	\param	EC[in]		���� ��ǥ��(���� ��ǥ�� ����)
	*	\param	t[in]		���� �̵� ����(���� ��ǥ�� ����)
	*	\param	q[in]		���� ȸ�� ����(���� ��ǥ�� ����)
	*	\param	s[in]		���� ������ ����(���� ��ǥ�� ����)
	*	\param	bFirst[in]	���� ��ü���� ���ÿ� ������ ��� ù ��° ��ü�� ���� ����
	*/
	virtual void Edit(EgTrans EC, EgVec3 t, EgQuat q, EgVec3 s, bool bFirst);

	/*!
	*	\brief	���� ���� ���� ������ �Ѵ�.
	*
	*	\param	r[in]	������ red ����
	*	\param	g[in]	������ green ����
	*	\param	b[in]	������ blue ����
	*/
	virtual void RenderForEdit(float r, float g, float b);

public:
	/*! \biref ���� ���� �ﰢ���� ���� ������ */
	EgFace *m_pFace;

	/*! \biref ���� ���� �ﰢ������ ǥ���� barycentric ��ǥ */
	EgVec3 m_Coords;

	/*! \biref ���� ��ġ Ÿ�� */
	TypeMeshPt m_PtType;

public:
	/*!
	*	\brief	����Ʈ ������
	*/
	EgMeshPt();

	/*!
	*	\brief	������
	*
	*	\param	pVert[in]	�޽� ����
	*/
	EgMeshPt(EgVertex *pVert);

	/*!
	*	\brief	������
	*
	*	\param	pFace[in]	���� ������ �ﰢ���� ���� ������
	*	\param	Pos[in]		���� 3���� ��ǥ
	*/
	EgMeshPt(EgFace *pFace, EgPos Pos);

	/*!
	*	\brief	������
	*
	*	\param	pFace[in]	���� ������ �ﰢ���� ���� ������
	*	\param	Coords[in]	�ﰢ�� ���� ���� barycentric ��ǥ
	*/
	EgMeshPt(EgFace *pFace, EgVec3 Coords);

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		����� ��ü
	*/
	EgMeshPt(const EgMeshPt &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgMeshPt();

	/*!
	*	\brief	���� ������
	*
	*	\param	rhs[in]		���Ե� ��ü
	*
	*	\return ���Ե� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshPt &operator =(const EgMeshPt &rhs);

	/*!
	*	\brief	�� ��ǥ�迡�� ǥ���� ���� ��ǥ�� ��ȯ�Ѵ�.
	*
	*	\return �� ��ǥ�迡�� ǥ���� ���� ��ǥ�� ��ȯ�Ѵ�.
	*/
	EgPos Pos();

	/*!
	*	\brief	���� �ʱ�ȭ �Ѵ�.
	*/
	void Reset();

	/*!
	*	\brief	��� �޽��� �ﰢ���� �����Ͽ� ���� ��ġ�� �����Ѵ�.
	*
	*	\param	pMesh[in]	��� �޽�
	*	\param	Pos[in]		�Է� ���� ��ǥ
	*
	*	\return	�Է� ���� �޽� ���� ���̸� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool Set(EgMesh *pMesh, EgPos Pos);

	/*!
	*	\brief	���� ��ġ�� �����Ѵ�.
	*
	*	\param	pFace[in]	���� ���Ե� �ﰢ��
	*	\param	Pos[in]		���� 3���� ��ǥ
	*/
	void Set(EgFace *pFace, EgPos Pos);

	/*!
	*	\brief	���� ��ġ�� �����Ѵ�.
	*
	*	\param	pFace[in]	���� ���Ե� �ﰢ��
	*	\param	Coords[in]	�ﰢ�� �������� ǥ���� ���� Barycentric ��ǥ
	*/
	void Set(EgFace *pFace, EgVec3 Coords);

	/*!
	*	\brief	���� ��ġ�� �����Ͽ� m_PtType�� �����Ѵ�.
	*/
	void LocatePt();

	/*!
	*	\brief	�޽� ���� ���� �������� �����Ѵ�.
	*
	*	\return �����̶�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsOnVertex();

	/*!
	*	\brief	�޽� ���� ���� ���� ���� ������ �����Ѵ�.
	*
	*	\return ���� ���� ���̶�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsOnEdge();

	/*!
	*	\brief	�޽� ���� ���� �ﰢ�� ���������� �����Ѵ�.
	*
	*	\return �ﰢ�� �������̶�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsInFace();

	/*!
	*	\brief	�޽� ���� ���� �ﰢ�� �ܺ������� �����Ѵ�.
	*
	*	\return �ﰢ�� �ܺ����̶�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsOutFace();

	/*!
	*	\brief	�ﰢ�� ���������� �Ÿ��� ����Ѵ�.
	*
	*	\param	vidx[in]	�ﰢ�� ������ �ε���
	*
	*	\return ���� �Ÿ��� ��ȯ�Ѵ�.
	*/
	double GetDist2Vert(int vidx);

	/*!
	*	\brief	���� ����ϴ� ������ ���Ѵ�.
	*
	*	\return ���� ����ϴ� ������ ��ȯ�ϰ�, ���� ���� ���� ������ NULL�� ��ȯ�Ѵ�.
	*/
	EgEdge *GetEdgeOverPt();

	/*!
	*	\brief	�ﰢ���� ���� ����� ������ ã�´�.
	*
	*	\return �ﰢ���� ���� ����� ������ �����͸� ��ȯ�Ѵ�.
	*/
	EgVertex *GetClosestVert();

	/*!
	*	\brief	�޽� ���� ���� ������ �ﰢ���� ���Ѵ�.
	*
	*	\param	Faces[out]		������ �ﰢ���� ����ȴ�.
	*
	*	\return ������ �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int	GetAdjacentFaces(std::vector<EgFace *> &Faces);

	/*!
	*	\brief	�޽� ���� �� ���� ������ �����Ѵ�.
	*
	*	\param	p[in]	ù ��° ��
	*	\param	q[in]	�� ��° ��
	*
	*	\return �� ���� ������ true, �ٸ��� false�� ��ȯ�Ѵ�.
	*/
	friend bool operator ==(const EgMeshPt &p, const EgMeshPt &q);

	/*!
	*	\brief	�޽� ���� �� ���� �ٸ��� �����Ѵ�.
	*
	*	\param	p[in]	ù ��° ��
	*	\param	q[in]	�� ��° ��
	*
	*	\return �� ���� �ٸ��� true, ������ false�� ��ȯ�Ѵ�.
	*/
	friend bool operator !=(const EgMeshPt &p, const EgMeshPt &q);

	/*!
	*	\brief	��� ������(<<)
	*
	*	\param	os[out]		��� ��Ʈ��
	*	\param	p[in]		����� �޽� ���� ��
	*
	*	\return ��µ� ��Ʈ���� ��ȯ�Ѵ�.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgMeshPt &p);
};

/*!
*	\class	EgMeshVec
*	\brief	�޽� ���� ���� ����(Straightest Geodesic)�� ǥ���ϴ� Ŭ����
*
*	\author ������, ������
*	\date	2020-12-03
*/
class EgMeshVec
{
public:
	/*! \biref ������ ������ */
	EgMeshPt m_Pt;

	/*! \biref ������ ����� ���� */
	EgVec3 m_Dir;

public:
	/*!
	*	\brief	����Ʈ ������
	*/
	EgMeshVec();

	/*!
	*	\brief	������
	*
	*	\param	Pt[in]		������ ������
	*	\param	Dir[in]		������ ����� ����
	*/
	EgMeshVec(EgMeshPt Pt, EgVec3 Dir);

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		����� ��ü
	*/
	EgMeshVec(const EgMeshVec &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgMeshVec();

	/*!
	*	\brief	�޽� ���� ������ ���̸� ��ȯ�Ѵ�.
	*
	*	\return	�޽� ���� ������ ���̸� ��ȯ�Ѵ�.
	*/
	double GetLength();

	/*!
	*	\brief	������ �������� ��ȯ�Ѵ�.
	*
	*	\return	������ �������� ��ȯ�Ѵ�.
	*/
	EgMeshPt GetStartPt();

	/*!
	*	\brief	������ ������ ���Ѵ�.
	*
	*	\return	������ ������ ��ȯ�Ѵ�.
	*/
	EgMeshPt GetEndPt();

	/*!
	*	\brief	�޽� ���� ������ ��ο� ������ ���Ѵ�.
	*
	*	\param	Path[out]	������ ���������� ���������� ��ΰ� ����ȴ�.
	*
	*	\return	�޽� ���� ������ ������ ��ȯ�Ѵ�.
	*/
	EgMeshPt GetPath(std::vector<EgPos> &Path);

	/*!
	*	\brief	+ ���� ������
	*
	*	\return ���Ϻ�ȣ�� ���� ��ü�� ��ȯ�Ѵ�.
	*/
	EgMeshVec operator +();

	/*!
	*	\brief	- ���� ������
	*
	*	\return �ݴ��ȣ�� ���� ��ü�� ��ȯ�Ѵ�.
	*/
	EgMeshVec operator -();

	/*!
	*	\brief	���͸� ����� �Ѵ�.
	*
	*	\param	s[in]	���
	*
	*	\return ������ �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshVec &operator *=(const double &s);

	/*!
	*	\brief	���͸� ����� ������
	*
	*	\param	s[in]	���
	*
	*	\return ����� ���־��� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshVec &operator /=(const double &s);

	/*!
	*	\brief	���� ������
	*
	*	\param	rhs[in]		���Ե� ��ü
	*
	*	\return	���Ե� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshVec &operator =(const EgMeshVec &rhs);

	/*!
	*	\brief	�ڽſ��� �ٸ� ���͸� ���Ѵ�.
	*	\note	������ ������: 2021-01-21
	*
	*	\param	rhs[in]		�ǿ����� ��ü
	*
	*	\return	����� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshVec &operator +=(const EgMeshVec &rhs);

	/*!
	*	\brief	�ڽſ��� �ٸ� ���͸� ����.
	*
	*	\param	rhs[in]		�ǿ����� ��ü
	*
	*	\return	����� �ڽ��� ��ȯ�Ѵ�.
	*/
	EgMeshVec &operator -=(const EgMeshVec &rhs);

	/*!
	*	\brief	�޽� ���� �� ���Ͱ� ������ üũ�Ѵ�.
	*
	*	\param	v[in]	ù ��° ����
	*	\param	w[in]	�� ��° ����
	*
	*	\return	�� ������ �������� ������ ������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	friend bool operator ==(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	�޽� ���� �� ���Ͱ� �ٸ��� üũ�Ѵ�.
	*
	*	\param	v[in]	ù ��° ����
	*	\param	w[in]	�� ��° ����
	*
	*	\return	�� ���Ͱ� �ٸ��� true, ������ false�� ��ȯ�Ѵ�.
	*/
	friend bool operator !=(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	�޽� ���� �� ���� ����.
	*	\note	������ ������: 2021-07-04
	*	\note	��� ���� v = p - q ������, q + v = p�� �ƴ� ���� ����
	*
	*	\param	p[in]	ù ��° ��
	*	\param	q[in]	�� ��° ��
	*
	*	\return	�� q���� �� p�� ���ϴ� �޽� ���� ���� v�� ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator -(EgMeshPt &p, EgMeshPt &q);

	/*!
	*	\brief	�޽� ���� ���� ���͸� ���Ѵ�.
	*	\note	������ ������: 2021-01-14
	*
	*	\param	p[in]	�޽� ���� ��
	*	\param	v[in]	���� ����
	*
	*	\return	�� p���� ���� v�� ���� �޽� ���� ���� ��ȯ�Ѵ�.
	*/
	friend EgMeshPt operator +(EgMeshPt &p, EgMeshVec &v);

	/*!
	*	\brief	�޽� ���� ���� ���͸� ���Ѵ�.
	*
	*	\param	v[in]	���� ����
	*	\param	p[in]	�޽� ���� ��
	*
	*	\return	�� p���� ���� v�� ���� �޽� ���� ���� ��ȯ�Ѵ�.
	*/
	friend EgMeshPt operator +(EgMeshVec &v, EgMeshPt &p);

	/*!
	*	\brief	�޽� ���� ���� ���͸� ����.
	*
	*	\param	p[in]	�޽� ���� ��
	*	\param	v[in]	�� ����
	*
	*	\return	�� p���� ���� v�� ���� �޽� ���� ���� ��ȯ�Ѵ�.
	*/
	friend EgMeshPt operator -(EgMeshPt &p, EgMeshVec &v);

	/*!
	*	\brief	�޽� ���� �� ���͸� ���Ѵ�.
	*	\note	�� ������ ���� ��ġ�� �ٸ��� �� ��° ���͸� ù ��° ������ ���� ��ġ�� ���� �̵���Ų��.
	*
	*	\param	v[in]	ù ��° ����
	*	\param	w[in]	�� ��° ����
	*
	*	\return	�� ������ ���� ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator +(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	�޽� ���� �� ���͸� ����.
	*	\note	�� ������ ���� ��ġ�� �ٸ��� �� ��° ���͸� ù ��° ������ ���� ��ġ�� ���� �̵���Ų��.
	*
	*	\param	v[in]	ù ��° ����
	*	\param	w[in]	�� ��° ����
	*
	*	\return	�� ������ ���� ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator -(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	���͸� ����� �Ѵ�.
	*
	*	\param	v[in]	����
	*	\param	s[in]	���
	*
	*	\return ������ ����踦 ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator *(EgMeshVec &v, const double &s);

	/*!
	*	\brief	���͸� ����� �Ѵ�.
	*
	*	\param	s[in]	���
	*	\param	v[in]	����
	*
	*	\return ������ ����踦 ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator *(const double &s, EgMeshVec &v);

	/*!
	*	\brief	���͸� ����� ������.
	*
	*	\param	v[in]	����
	*	\param	s[in]	���
	*
	*	\return ����� ���� ���͸� ��ȯ�Ѵ�.
	*/
	friend EgMeshVec operator /(EgMeshVec &v, double s);

	/*!
	*	\brief	�� ������ ������ ���Ѵ�.
	*
	*	\param	v[in]	ù ��° ����
	*	\param	w[in]	�� ��° ����
	*
	*	\return �� ������ ������ ��ȯ�Ѵ�.
	*/
	friend double operator *(const EgMeshVec &v, const EgMeshVec &w);

	/*!
	*	\brief	��� ������(<<)
	*
	*	\param	os[out]		��� ��Ʈ��
	*	\param	v[in]		����� �޽� ���� ����
	*
	*	\return ��µ� ��Ʈ���� ��ȯ�Ѵ�.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgMeshVec &v);
};

/*!
*	\class	EgPolyline
*	\brief	3���� ������ ���������� ǥ���ϴ� Ŭ����
*
*	\author	������
*/
class EgPolyline : public EgMesh
{
public:
	/*!
	*	\brief	��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ��ü�� Ŭ���� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetClassName();

	/*!
	*	\brief	���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*
	*	\return ���� �����Ǵ� ��ü�� �̸��� ��ȯ�Ѵ�.
	*/
	virtual std::string GetNewObjName();

	/*!
	*	\brief	���������� ������ �Ѵ�.
	*/
	virtual void Render();

public:
	/*! \brief	���� �������� ���� */
	bool m_bClosed;

	/*! \brief	���������� ���� */
	EgVec3 m_Color;

	/*! \brief	���������� �β� */
	double m_Width;

public:
	/*!
	*	\brief	������
	*/
	EgPolyline();

	/*!
	*	\brief	������
	*
	*	\param	PtList[in]		���������� �����ϴ� ������ ����Ʈ
	*	\param	bClosed[in]		���� ������� ����
	*	\param	Color[in]		���������� ����
	*	\param	Width[in]		���������� �β�
	*/
	EgPolyline(std::vector<EgPos> &PtList, bool bClosed, EgVec3 Color, double Width);

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]	����� ��ü
	*/
	EgPolyline(const EgPolyline &cpy);

	/*!
	*	\brief	�Ҹ���
	*/
	virtual ~EgPolyline();
};

/*!
*	\class	QNode<T1, T2>
*	\brief	ť�� ��带 ǥ���ϴ� Ŭ����
*	\note	������ ������: 2020-02-23
*
*	\author ������
*/
template<class T1, class T2>
class QNode
{
public:
	/* \brief ��� ������ */
	T1 m_pData;

	/* \brief ������ ���� ����� ��(�Ÿ� ��) */
	T2 m_Value;

public:
	/*!
	*	\brief	������
	*	
	*	\param	pData[in]	��� 
	*	\param	Value[in]	����� ��
	*/
	QNode(T1 pData, T2 Value)
	{
		m_pData = pData;
		m_Value = Value;
	}

	/*!
	*	\brief	���� ������
	*
	*	\param	cpy[in]		����� ��ü
	*/
	QNode(const QNode &cpy)
	{
		m_pData = cpy.m_pData;
		m_Value = cpy.m_Value;
	}

	/*!
	*	\brief	�Ҹ���
	*/
	~QNode() {}

	/*!
	*	\brief	���� ������
	*
	*	\param	rhs[in]		���Ե� ��ü
	*
	*	\return	���Ե� �ڽ��� ��ȯ�Ѵ�.
	*/
	QNode &operator =(const QNode &rhs)
	{
		m_pData = rhs.m_pData;
		m_Value = rhs.m_Value;
		return *this;
	}

	/*!
	*	\brief	�� ����� ũ�⸦ ���Ѵ�.
	*
	*	\param	lhs[in]		���� ���
	*	\param	rhs[in]		������ ���
	*
	*	\return ���� ��尡 ������ ��庸�� ũ�� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	friend bool operator >(const QNode &lhs, const QNode &rhs)
	{
		return (lhs.m_Value > rhs.m_Value);
	}

	/*!
	*	\brief	�� ����� ũ�⸦ ���Ѵ�.
	*
	*	\param	lhs[in]		���� ���
	*	\param	rhs[in]		������ ���
	*
	*	\return ���� ��尡 ������ ��庸�� ������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	friend bool operator <(const QNode &lhs, const QNode &rhs)
	{
		return (lhs.m_Value < rhs.m_Value);
	}
};

/*!
*	\class	EgGraph
*	\brief	���� ������ �̿��Ͽ� �ﰢ �޽��� ������ ǥ���ϴ� Ŭ����
*
*	\author ������
*	\date	2021-09-28
*/
class EgGraph
{
public:
	/*! \brief ������ �� */
	int m_vnum;

	/*! \brief ������ �� */
	int m_enum;

	/*! \brief �ﰢ���� �� */
	int m_fnum;	

	/*! \brief ���� ������ ����Ű�� ������ �ε��� */
	std::vector<int> m_halfedge_to_vertex;

	/*! \brief ���� ������ ���Ե� �ﰢ���� �ε��� */
	std::vector<int> m_halfedge_to_face;

	/*! \brief ���� ���� ������ �ε��� */
	std::vector<int> m_halfedge_to_next;

	/*! \brief ���� ���� ������ �ε��� */
	std::vector<int> m_halfedge_to_prev;

	/*! \brief �������� �����ϴ� ù ��° ���� ���� */
	std::vector<int> m_vertex_to_halfedge;

	/*! \brief ����ȭ�� ������ ���� �迭 */
	std::vector<double> m_edge_lengths;

	/*! \brief ����ȭ�� ���� ������ ��� ���� */
	double m_avg_edge_len;

public:
	/*!
	*	\brief	������
	*
	*	\param	pMesh[in]	��� �޽�
	*/
	EgGraph(EgMesh *pMesh);

	/*!
	*	\brief	�Ҹ���
	*/
	~EgGraph();
};
