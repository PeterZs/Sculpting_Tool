#pragma once

#define MAX_BVH_DEPTH 10

/*!
*	\class	EgBvh
*	\brief	AABB (Axis-Aligned Bounding Box) Ÿ���� BVH (Bounding Volume Hierarchy)�� ǥ���ϴ� Ŭ����
*	\note	������ ������: 2021-02-23
*
*	\author �ѻ���, ������
*/
class EgBvh
{
public:
	/*!
	*	\class	AaBb (Axis-Alined Bounding Box)
	*	\brief	AABB Ÿ�� ��� ���ڸ� ǥ���ϴ� Ŭ����
	*	\note	������ ������: 2021-04-07
	*
	*	\author �ѻ���, ������
	*/
	class AaBb
	{
	public:
		/* \brief ��� �޽��� ���� ������ */
		EgMesh *m_pMesh;

		/* \brief ��� ���ڿ� ���Ե� �ﰢ�� ����Ʈ */
		std::vector<EgFace *> m_Faces;

		/* \brief ��� ������ �ּ� ��ġ */
		EgPos m_Min;

		/* \brief ��� ������ �ִ� ��ġ */
		EgPos m_Max;

		/* \brief ��� ������ BVH ���� */
		int m_Depth;

		/* \brief ���� ��� ���� ���� */
		bool m_bLeaf;

		/* \brief ���� ��� ���ڿ� ���� ������ */
		std::vector<AaBb *> m_ChildNodes;

	public:
		/*!
		 *	\brief	����Ʈ ������
		 */
		AaBb();

		/*!
		 *	\brief	�ﰢ�� ����Ʈ�� �ٿ���ϴ� ��� ���ڿ� ���� ��� ����(�ʿ��� ���)�� �����Ѵ�.
		 *
		 *	\param	pMesh[in]	�޽� ������
		 *	\param	Faces[in]	��� ���ڿ� ���Ե� �ﰢ�� ����Ʈ
		 *	\param	Depth[in]	��� ������ BVH ����
		 */
		AaBb(EgMesh *pMesh, std::vector<EgFace *> &Faces, const int depth);

		/*!
		*	\brief	�Ҹ���
		*/
		~AaBb();

		/*!
		*	\brief	��� ���ڸ� �� ��(�ִ��� ����)���� �����Ͽ� 4���� ��� ���ڸ� �����Ѵ�.
		*/
		void Divide();

		/*!
		 *	\brief	���� ��� ���� ������ �ִ� �Ÿ� ������ ����Ѵ�.
		 *	\note	���� ��� ���� ���ο� ���ԵǾ��ٸ� 0�� ��ȯ�Ѵ�.
		 *
		 *	\param	p[in]	���� ��ġ
		 *
		 *	\return ���� ��� ���� ������ �ִ� �Ÿ� ������ ��ȯ�Ѵ�.
		 */
		double GetSqrDist(const EgPos &p);

		/*!
		 *	\brief	������ ��� ������ �������� ����Ѵ�.
		 *	\note	����: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-box-intersection
		 *
		 *	\param	Ray[in]		������ ����(����)
		 *	\param	t[out]		�����ϴ� ��� �������� �Ķ���Ͱ� ����ȴ�.
		 *
		 *	\return ������ ��� ���ڰ� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
		 */
		bool IntersectWithRay(const EgLine &Ray, double &t);

		/*!
		 *	\brief	�ﰢ���� ��� ������ ���� ���θ� �˻��Ѵ�.
		 *
		 *	\param	p0[in]		������ �ﰢ���� ù ��° ����
		 *	\param	p1[in]		������ �ﰢ���� �� ��° ����
		 *	\param	p2[in]		������ �ﰢ���� �� ��° ����
		 *
		 *	\return �ﰢ���� ��� ���ڰ� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
		 */
		bool IntersectWithTri(const EgPos &p0, const EgPos &p1, const EgPos &p2);
	};

public:
	/* \brief ��� �޽��� ���� ������ */
	EgMesh *m_pMesh;

	/* \brief �ֻ��� ��� ���ڿ� ���� ������ */
	AaBb *m_pRoot;

	/* \brief ��� �޽��� ���� ���� */
	bool m_bCopy;
	
public:
	/*!
	 *	\brief	������
	 */
	EgBvh();

	/*!
	 *	\brief	��� �޽��� ���� BVH�� �����Ѵ�.
	 *
	 *	\param	pMesh[in]		��� �޽�
	 */
	EgBvh(EgMesh *pMesh);

	/*!
	 *	\brief	�Է� ������ BVH�� �����Ѵ�.
	 *
	 *	\param	Verts[in]	������ ����Ʈ
	 *	\param	Faces[in]	�ﰢ���� �����ϴ� ������ �ε��� ����Ʈ
	 */
	EgBvh(std::vector<EgPos> &Verts, std::vector<int> &Faces);	

	/*!
	 *	\brief	�Ҹ���
	 */
	~EgBvh();

	/*!
	 *	\brief	���� �޽� ������ �Ÿ��� �־��� �Ÿ����� ������� �����Ѵ�.
	 *
	 *	\param	Dist[in]		�Է� �Ÿ�
	 *	\param	p[in]			������ ���� ��ġ
	 *	\param	bVertOnly[in]	���� �޽� ���� ������ �Ÿ����� �����ϸ� true, ���� �޽� �ﰢ�� ������ �Ÿ��� �����ϸ� false
	 *
	 *	\return ������ �޽� ������ �Ÿ��� �־��� �Ÿ����� ������ true, �ƴϸ� false�� ��ȯ�Ѵ�.
	 */
	bool IsCloserThan(double Dist, const EgPos &p, bool bVertOnly);

	/*!
	 *	\brief	���� �޽��� �ִ� �Ÿ��� ����Ѵ�.
	 *
	 *	\param	p[in]		���� ��ġ
	 *	\param	q[out]		�ִ� �Ÿ��� �߻��ϴ� �޽� ���� ���� ����ȴ�.
	 *	\param	pFace[out]	�ִ� �Ÿ��� �߻��ϴ� �ﰢ���� �����Ͱ� ����ȴ�.
	 *	\param	bSinged[in]	���� �Ÿ� ��ȯ ����
	 *
	 *	\return ���� �ִ� �Ÿ��� ��ȯ�Ѵ�.
	 */
	double ComputeDistance(EgPos p, EgPos &q, EgFace **pFace, bool bSigned);

	/*!
	 *	\brief	���� �޽��� �ִ� �Ÿ��� ����Ѵ�.
	 *
	 *	\param	p[in]		���� ��ġ
	 *	\param	q[out]		�ִ� �Ÿ��� �߻��ϴ� �޽� ���� ���� ����ȴ�.
	 *	\param	fidx[out]	�ִ� �Ÿ��� �߻��ϴ� �ﰢ���� �ε����� ����ȴ�.
	 *	\param	sign[in]	���� �Ÿ� ��ȯ ����
	 *
	 *	\return ���� �ִ� �Ÿ��� ��ȯ�Ѵ�.
	 */
	double ComputeDistance(EgPos p, EgPos &q, int &fidx, bool sign);

	/*!
	 *	\brief	������ �޽��� �������� ����Ѵ�.
	 *	\note	������ �������� �ֻ��� ��� ���� �ܺο� �ִ� ������ �����Ѵ�.
	 *
	 *	\param	Ray[in]				����(����) ��ü
	 *	\param	t[out]				�������� ���� �Ķ���Ͱ� ����ȴ�.
	 *	\param	pFace[out]			���� �ﰢ���� �����Ͱ� ����ȴ�.
	 *	\param	bCullBackFace[in]	�ﰢ�� �޸� ������ �������� ����
	 *	\param	bNear[in]			�������� ����(����� �������̸� true, �� �������̸� false)
	  *
	 *	\return ������ �޽��� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
	 */
	bool IntersectWithRay(EgLine Ray, double &t, EgFace **pFace, bool bCullBackFace, bool bNear = true);

	/*!
	 *	\brief	�Է� �ﰢ���� �����ϴ� ��� �ﰢ���� ã�´�.
	  *
	 *	\param	f[in]				�Է� �ﰢ��
	 *	\param	HitFaces[out]		�Է� �ﰢ���� �����ϴ� �ﰢ���� ����ȴ�.
	 *	\param	CutLines[out]		���� ������ ����ȴ�.
	 *
	 *	\return �Է� �ﰢ���� �����ϴ� �ﰢ���� ���� ��ȯ�Ѵ�.
	 */
	int IntersectWithTri(EgFace *f, std::vector<EgFace *> &HitFaces, std::vector<std::pair<EgPos, EgPos>> &CutLines);
	
	/*!
	*	\brief	�Է� �ﰢ���� �����ϴ� ��� �ﰢ���� ã�´�.
	 *
	*	\param	u0[in]				�Է� �ﰢ���� ù ��° ������ ��ǥ
	*	\param	u1[in]				�Է� �ﰢ���� �� ��° ������ ��ǥ
	*	\param	u2[in]				�Է� �ﰢ���� �� ��° ������ ��ǥ
	*	\param	HitFaces[out]		�Է� �ﰢ���� �����ϴ� �ﰢ���� ����ȴ�.
	*
	*	\return �Է� �ﰢ���� �����ϴ� �ﰢ���� ���� ��ȯ�Ѵ�.
	*/
	int IntersectWithTri(EgPos u0, EgPos u1, EgPos u2, std::vector<EgFace *> &HitFaces);
};

/*!
  *	\brief	���� �ﰢ�� ���� ������ �ִ� �Ÿ� ������ ����Ѵ�.
  *
  *	\param	q[in]	���� ��ġ
  *	\param	f[in]	��� �ﰢ���� ������
	*
  *	\return ���� �ִ� �Ÿ� ������ ��ȯ�Ѵ�.
  */
double dist_sq_vert(const EgPos &p, EgFace *f);

/*!
  *	\brief	���� �ﰢ�� ������ �ִ� �Ÿ� ������ ����Ѵ�.
  *
  *	\param	q[in]	���� ��ġ
  *	\param	f[in]	��� �ﰢ���� ������
	*
  *	\return ���� �ִ� �Ÿ� ������ ��ȯ�Ѵ�.
  */
double dist_sq(const EgPos &q, EgFace *f);

/*!
 *	\brief	���� �ﰢ�� ������ �ִ� �Ÿ� ������ ����Ѵ�.
 *
 *	\param	q[in]	���� ��ġ
 *	\param	f[in]	��� �ﰢ���� ������
 *	\param	r[out]	�ִ� �Ÿ��� �߻��Ǵ� ���� ����ȴ�.
 *
 *	\return ���� �ִ� �Ÿ� ������ ��ȯ�Ѵ�.
 */
double dist_sq(const EgPos &p, EgFace *f, EgPos &q);
