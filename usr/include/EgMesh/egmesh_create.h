#pragma once

class EgVertex;
class EgTexel;
class EgNormal;
class EgTexture;
class EgMaterial;
class EgMesh;

/*!
*	\biref	�޽� ��ü�� �����Ѵ�.
*
*	\param	MeshName[in] ������ �޽� ��ü�� �̸�
*
*	\return ������ �޽��� �����͸� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh(std::string MeshName);

/*!
*	\biref	�޽� ������ �����Ѵ�.
*
*	\param	x[in] ������ x ��ǥ
*	\param	y[in] ������ y ��ǥ
*	\param	z[in] ������ z ��ǥ
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgVertex *create_vertex(double x, double y, double z);

/*!
*	\biref	�޽� ������ �����Ѵ�.
*
*	\param	pt[in]	������ ��ǥ
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgVertex *create_vertex(EgPos pt);

/*!
*	\biref	�ؽ�ó ��ǥ�� �����Ѵ�.
*
*	\param	s[in] �ؽ�ó s ��ǥ
*	\param	t[in] �ؽ�ó t ��ǥ
*
*	\return ������ �ؽ�ó ��ǥ�� �����͸� ��ȯ�Ѵ�.
*/
EgTexel *create_texel(double s, double t);

/*!
*	\biref	�޽� ������ �����Ѵ�.
*
*	\param	nx[in] ������ x ��ǥ
*	\param	ny[in] ������ y ��ǥ
*	\param	nz[in] ������ z ��ǥ
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgNormal *create_normal(double nx, double ny, double nz);

/*!
*	\brief	�޽� �ﰢ���� �����Ѵ�.
*
*	\param	v0[in]			�ﰢ���� ù ��° ����
*	\param	v1[in]			�ﰢ���� �� ��° ����
*	\param	v2[in]			�ﰢ���� �� ��° ����
*	\param	pMtl[in]		�ﰢ���� ����ϴ� ������ ���� ������
*	\param	GroupName[in]	�ﰢ���� ���� �׷��� �̸�
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgMaterial *pMtl = NULL, std::string GroupName = "");

/*!
*	\brief	�޽� �ﰢ���� �����Ѵ�.
*
*	\param	v0[in]			�ﰢ���� ù ��° ����
*	\param	v1[in]			�ﰢ���� �� ��° ����
*	\param	v2[in]			�ﰢ���� �� ��° ����
*	\param	t0[in]			�ﰢ���� ù ��° ������ �ؼ�
*	\param	t1[in]			�ﰢ���� �� ��° ������ �ؼ�
*	\param	t2[in]			�ﰢ���� �� ��° ������ �ؼ�
*	\param	pMtl[in]		�ﰢ���� ����ϴ� ������ ���� ������
*	\param	GroupName[in]	�ﰢ���� ���� �׷��� �̸�
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2, EgMaterial *pMtl, std::string GroupName = "");

/*!
*	\brief	�޽� �ﰢ���� �����Ѵ�.
*
*	\param	v0[in]			�ﰢ���� ù ��° ����
*	\param	v1[in]			�ﰢ���� �� ��° ����
*	\param	v2[in]			�ﰢ���� �� ��° ����
*	\param	t0[in]			�ﰢ���� ù ��° ������ �ؼ�
*	\param	t1[in]			�ﰢ���� �� ��° ������ �ؼ�
*	\param	t2[in]			�ﰢ���� �� ��° ������ �ؼ�
*	\param	n0[in]			�ﰢ���� ù ��° ������ ����
*	\param	n1[in]			�ﰢ���� �� ��° ������ ����
*	\param	n2[in]			�ﰢ���� �� ��° ������ ����
*	\param	pMtl[in]		�ﰢ���� ����ϴ� ������ ���� ������
*	\param	GroupName[in]	�ﰢ���� ���� �׷��� �̸�
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2, EgNormal *n0, EgNormal *n1, EgNormal *n2, EgMaterial *pMtl, std::string GroupName = "");

/*!
*	\biref	�޽� ������ �����Ѵ�.
*
*	\param	mtl_name[in] ������ ������ �̸�
*	\param	ar[in] �ֺ��� red �ݻ���
*	\param	ag[in] �ֺ��� green �ݻ���
*	\param	ab[in] �ֺ��� blue �ݻ���
*	\param	dr[in] ���ݻ� red �ݻ���
*	\param	dg[in] ���ݻ� green �ݻ���
*	\param	db[in] ���ݻ� blue �ݻ���
*	\param	sr[in] ���ݻ� red �ݻ���
*	\param	sg[in] ���ݻ� green �ݻ���
*	\param	sb[in] ���ݻ� blue �ݻ���
*	\param	ns[in] ���ݻ� ����
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgMaterial *create_material(std::string mtl_name, float ar, float ag, float ab, float dr, float dg, float db, float sr, float sg, float sb, float ns);

/*!
*	\biref	�޽� ������ �����Ѵ�.
*
*	\param	mtl_name[in]	������ ������ �̸�
*	\param	r[in]			���ݻ� red �ݻ���
*	\param	g[in]			���ݻ� green �ݻ���
*	\param	b[in]			���ݻ� blue �ݻ���
*	\param	ns[in]			���ݻ� ����
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgMaterial *create_material(std::string mtl_name, float r, float g, float b, float ns);

/*!
*	\brief	������ ������ �����Ѵ�.
*
*	\return ������ ������ �����͸� ��ȯ�Ѵ�.
*/
EgMaterial *create_material_random();

/*!
*	\biref	2D �ؽ�ó�� �����Ѵ�.
*
*	\param	file_name[in] �ؽ�ó ������ �̸�
*
*	\return ������ �׽�ó�� �����͸� ��ȯ�Ѵ�.
*/
EgTexture *create_texture(std::string file_name);

/*!
*	\biref	��� ������ ä��� �ʱ� �޽��� �����Ѵ�.
*	\note	concave ��迡 ���� �ʿ�(2021-02-12)
*
*	\param	Verts[in] ��� ������ ����Ʈ
*
*	\return ������ �޽��� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh_from_bndry_verts(std::vector<EgVertex *> &Verts);

/*!
*	\biref	�ټ��� �޽��� �����Ͽ� ���ο� �޽��� �����Ѵ�.
*	\note	���������� ���յǰ� ������ �ؽ�ó ������ ���յ��� �ʴ´�.
*
*	\param	MeshList[in] ������ �޽�����Ʈ
*
*	\return ������ �޽��� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh_by_merging(std::vector<EgMesh *> &MeshList);

/*!
*	\brief	���õ� �ﰢ������ �κ� �޽��� �����Ѵ�.
*
*	\param	pMesh[in]	���õ� �ﰢ���� ���Ե� �޽�
*	\param	Faces[in]	���õ� �ﰢ�� ����Ʈ
*	\param	bCalcNormal �޽� ������ ���� ��� ����
*
*	\return ������ �޽��� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh_from_slt_faces(EgMesh *pMesh, const std::vector<EgFace *> &Faces, bool bCalcNormal = true);

/*!
*	\brief	���õ� �ﰢ������ �κ� �޽��� �����Ѵ�.
*	\note   �ӵ� ����ȭ �� �������� ������ ���� �籸��
*
*	@param	pMesh[in]			���õ� �ﰢ���� ���Ե� �޽�
*	@param	Faces[in]			���õ� �ﰢ�� ����Ʈ
*	@param	bCalcNormal[in]		�޽� ������ ���� ��� ����
*	@param	VertVertPairs[out]	������ ��������(�κ� �޽��� ����, ���� �޽��� ����)�� ����ȴ�.
*
*	@author ����ȣ
*
*	@return ������ �޽��� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh_from_slt_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces, bool bCalcNormal, std::unordered_map<EgVertex *, EgVertex *> &VertVertPairs);

/*!
*	\brief	������������ ���ǵǴ� �Ǹ��� �޽��� �����Ѵ�.
*
*	\param	TraPts[in]		�������� ������ ����Ʈ
*	\param	Radius[in]		�Ǹ��� �ݰ�
*	\param	Samples[in]		�Ǹ��� �ܸ��� ���ø� ��
*	\param	bTrim[in]		�ڱ� ������ Ʈ���� ����
*
*	\return	������ �Ǹ��� �޽��� ��ȯ�Ѵ�.
*/
EgMesh *create_mesh_cylinder(std::vector<EgPos> TraPts, double Radius, int Samples, bool bTrim);


