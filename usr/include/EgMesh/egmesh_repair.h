#pragma once

/*!
*	\brief	�޽��� �и��� ��(�ﰢ�� ����)�� ã�´�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	ShellList[out]	�и��� ���� ����ȴ�.
*
*	\return �и��� �ﰢ�� ������ ���� ��ȯ�Ѵ�.
*/
int find_isolated_shells(EgMesh *pMesh, std::vector<std::list<EgFace *>> &Shells);

/*!
*	\brief	�޽��� �и��� ��(�ﰢ�� ����)�� �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ���ŵ� ���� ���� ��ȯ�Ѵ�.
*/
int delete_isolated_shells(EgMesh *pMesh);

/*!
*	\brief	�޽��� �ߺ� ������ ã�´�.
*	\note	������ ������: 2021-08-24
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Verts[out]	Non-manifold ������ ����ȴ�.
*	\param	eps[in]		��ġ ��� ����
*
*	\return �ߺ� ���� ���� ��ȯ�Ѵ�.
*/
int find_duplicate_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts, double eps = 1.0e-14);

/*!
*	\brief	�޽��� �ߺ� ������ �����Ѵ�.
*	\note	������ ������: 2021-08-24
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	eps[in]		��ġ ��� ����
*
*	\return ���ŵ� ���� ���� ��ȯ�Ѵ�.
*/
int delete_duplicate_verts(EgMesh *pMesh, double eps = 1.0e-14);

/*!
*	\brief	�޽��� non-manifold ������ ã�´�.
*	\note	������ ������: 2021-08-24
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Verts[out]	Non-manifold ������ ����ȴ�.
*
*	\return Non-manifold ���� ���� ��ȯ�Ѵ�.
*/
int find_non_manifold_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	�޽��� non-manifold ������ �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ���ŵ� ���� ���� ��ȯ�Ѵ�.
*/
int delete_non_manifold_verts(EgMesh *pMesh);

/*!
*	\brief	Non-manifold ������ ã�´�.
*	\note	������ ������: 2021-08-25
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Edges[out]	Non-manifold ������ ����ȴ�.
*
*	\return Non-manifold ������ ���� ��ȯ�Ѵ�.
*/
int find_non_manifold_edges(EgMesh *pMesh, std::vector<EgEdge *> &Edges);

/*!
*	\brief	Non-manifold ������ �����Ѵ�.
*	\note	Non-manifold ������ ����� �ﰢ���� �����ϴ°� �ּ��ΰ�???
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ������ non-manifold ������ ������ �ﰢ���� ������ ��ȯ�Ѵ�.
*/
int delete_non_manifold_edges(EgMesh *pMesh);

/*!
*	\brief	��ȭ�� �ﰢ��(������ 0�� �����)�� ã�´�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Faces[out]	��ȭ�� �ﰢ������ ����ȴ�.
*	\param	eps[in]		��ȭ�� �ﰢ���� �Ǵ��ϱ� ���� ��� ����
*
*	\return ��ȭ�� �ﰢ�� ���� ��ȯ�Ѵ�.
*/
int find_degenerate_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces, double eps = 1.0e-6);

/*!
*	\brief	��ȭ(degenerate) �ﰢ���� �����Ѵ�.
*	\note	������ ������: 2021-08-23
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	eps[in]		��ȭ�� �ﰢ���� �Ǵ��ϱ� ���� ��� ����
*
*	\return ������ �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int delete_degenerate_faces(EgMesh *pMesh, double eps = 1.0e-6);

/*!
*	\brief	�޽��� �̻�� ������ ã�´�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Verts[out]	�̻�� ������ ����ȴ�.
*
*	\return �̻�� ���� ���� ��ȯ�Ѵ�.
*/
int find_unused_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	�޽��� �̻�� ������ �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ���ŵ� ������ ���� ��ȯ�Ѵ�.
*/
int delete_unused_verts(EgMesh *pMesh);

/*!
*	\brief	�޽����� ������ �ʴ� �ؼ��� ã�´�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	Texels[out]		�̻�� �ؼ��� ����ȴ�.
*
*	\return �̻�� �ؼ� ���� ��ȯ�Ѵ�.
*/
int find_unused_texels(EgMesh *pMesh, std::vector<EgTexel *> &Texels);

/*!
*	\brief	�޽��� �̻�� �ؼ��� �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ���ŵ� �ؼ��� ���� ��ȯ�Ѵ�.
*/
int delete_unused_texels(EgMesh *pMesh);

/*!
*	\brief	�޽����� �̻�� ������ ã�´�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	Normals[out]	�̻�� ������ ����ȴ�.
*
*	\return �̻�� ������ ���� ��ȯ�Ѵ�.
*/
int find_unused_normals(EgMesh *pMesh, std::vector<EgNormal *> &Normals);

/*!
*	\brief	�޽����� �̻�� ������ �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*
*	\return ���ŵ� ���� ���� ��ȯ�Ѵ�.
*/
int delete_unused_normals(EgMesh *pMesh);

/*!
*	\brief	�� ���� ��� ��� ������ ������ (�ڳ�)�ﰢ���� ã�´�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Faces[out]	�ڳ� �ﰢ���� ����ȴ�.
*
*	\return �ڳ� �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int find_corner_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces);

/*!
*	\brief	�� ���� ��� ��� ������ ������ (�ڳ�)�ﰢ���� �����Ѵ�.
*	\note	Non-manifold ������ ���� ����� �� �� ����.
*
*	\param	pMesh[in] ��� �޽��� ���� ������
*
*	\return ���ŵ� �ڳ� �ﰢ�� ���� ��ȯ�Ѵ�.
*/
int delete_corner_faces(EgMesh *pMesh);

/*!
*	\brief	�޽��� �ڱ� ���� �ﰢ���� ã�´�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*	\param	Faces[out]	�ڱ� ���� �ﰢ������ ����ȴ�.
*	\param	Lines[out]	���� ���ε��� ����ȴ�
*
*	\return �ڱ� ������ �߻��� �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int find_self_intersection(EgMesh *pMesh, std::vector<EgFace *> &Faces,	std::vector<std::pair<EgPos, EgPos>> &Lines);

/*!
*	\brief	�޽��� �ڱ� ���� �ﰢ���� �����Ѵ�.
*
*	\param	pMesh[in] ��� �޽�
*
*	\return ���ŵ� �ڱ� ���� �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int delete_self_intersection(EgMesh *pMesh);

/*!
*	\brief	�޽� ���� ������ ����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*/
void report_artifact(EgMesh *pMesh);

/*!
*	\brief	�޽� ���� ������ �����Ѵ�.
*
*	\param	pMesh[in]	��� �޽��� ���� ������
*/
void repair_artifact(EgMesh *pMesh);

/*!
*	\brief	�޽� ���� ������ �ݺ������� �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	MaxIters[in]	�ִ� �ݺ� ȸ��(����Ʈ 50)
*/
void repair_artifact_repeat(EgMesh *pMesh, int MexIters = 30);

/*!
*	\brief	�޽��� Ȧ�� ä���.
*	\note	Ȧ�� ���� ���� ���, ���� �� Ȧ�� ä���� �ʴ´�.
*			Ȧ ��迡�� ������ ������ �����ϱ� ���ؼ��� delete_duplicate_verts() �Լ��� ȣ���ؾ� �Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	FillType[in]		Ȧ ��ġ Ÿ��(0: �ּ� ����, 1: �ּ� �����, 2: �ּ� ��� ��ȭ��)
*	\param	bStitch[in]			Ȧ ��ġ�� �޽��� ���� ����(true: ����, false: �̿���)
*/
void fill_holes(EgMesh *pMesh, int FillType, bool bStitch);
