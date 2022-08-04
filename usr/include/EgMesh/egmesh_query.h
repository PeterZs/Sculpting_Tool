#pragma once

class EgVertex;
class EgFace;
class EgMesh;

/*!
*	\brief	�޽��� ������ N-�� �̿� ������ ���ϴ� �Լ�
*
*	\param	pMesh[in]		��� �޽�
*	\param	pVert[in]		������ ����
*	\param	N[in]			������ �̿� ������ �ִ� ����
*	\param	RingVerts[out]	����� �����(i-�� �̿� ������ RingVerts[i][0], ..., RingVerts[i][m]�� �����)
*
*	\return ���� ������ �ִ� ������ ��ȯ�Ѵ�(N ���� ���� ���� ����)
*/
int get_neighbor_verts(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<std::vector<EgVertex *>> &RingVerts);

/*!
*   \brief	�޽� ����� N-�� �̿� ������ ���ϴ� �Լ�
*   \note	���� ��, ��� ������ m_EditWgt�� 0���� �ʱ�ȭ�ȴ�.
*
*   \param  pMesh[in]		��� �޽�
*   \param  BndryVerts[in]	������ ��� ���� ����Ʈ
*   \param  N[in]			������ �̿� ������ �ִ� ���� (������ ��� ��ü �޽��� �����Ѵ�.)
*   \param  RingVerts[out]	����� �����(i-�� �̿� ������ RingVerts[i][0], ..., RingVerts[i][m]�� �����)
*
*   \return ���� ������ �ִ� ������ ��ȯ�Ѵ�(N ���� ���� ���� ����)
*/
int get_neighbor_verts(EgMesh *pMesh, std::vector<EgVertex *> &BndryVerts, int N, std::vector<std::vector<EgVertex *>> &RingVerts);

/*!
*	\brief	�޽� ������ N-�� �ﰢ���� ���ϴ� �Լ�
*
*	\param	pMesh[in]	��� �޽�
*	\param	pVert[in]	������ ����
*	\param	N[in]		������ �̿� ������ �ִ� ����
*	\param	Faces[out]	�ﰢ���� �����
*
*	\return ���õ� �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int get_neighbor_faces(EgMesh *pMesh, EgVertex *pVert, int N, std::vector<EgFace *> &Faces);

/*!
*	\brief	�޽� ��� �Ǵ� Ȧ ������ ����Ʈ�� ���Ѵ�.
*	\note	������ ������: 2021-02-10
*
*	\param	pMesh[in]			��� �޽�
*	\param	BndryVerts[out]		��� �Ǵ� Ȧ ������ �����
*	\param	bClockWise[in]		true�� ��� ���� �ð�, Ȧ�� �ݽð� ��������, false�� ��� ���� �ݽð� Ȧ�� �ð� �������� ����ȴ�.
*	\param	bSortByLen[in]		true�� ��� ���(Ȧ)�� ���̿� ���� ������������ ���ĵȴ�.
*
*	\return ���(Ȧ)�� ���� ��ȯ�Ѵ�(non-manifold ������ �ִٸ� -1�� ��ȯ�Ѵ�).
*/
int get_bndry_verts(EgMesh *pMesh, std::vector<std::vector<EgVertex *>> &BndryVerts, bool bClockWise, bool bSortByLen);

/*!
*	\brief	�޽� ���(Ȧ) ������ ����Ʈ�� ���Ѵ�.
*	\note	Manifold �Ǵ� non-manifold ���� ���� ��� ������ ã�´�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	BndryVerts[out]		���(Ȧ) ������ ����ȴ�.
*
*	\return ��� ������ ���� ��ȯ�Ѵ�.
*/
int get_bndry_verts(EgMesh *pMesh, std::vector<EgVertex *> &BndryVerts);

/*!
*	@brief	���� �ﰢ���� ���(Ȧ) ������ ����Ʈ�� ���Ѵ�.
*	@author ����ȣ
*
*	@param  Faces[in]		���õ� �ﰢ���� ����Ʈ
*	@param	BndryList[out]	���(Ȧ) ������ ����� ����Ʈ
*	@param	bClockWise[in]	true�� ��� ���(Ȧ) ������ �ð�(�ݽð�) ��������, false�� ��� ���(Ȧ) ������ �ݽð�(�ð�) �������� ����ȴ�.
*	@param	bSortByLen[in]	true�� ��� ���(Ȧ)�� ���̿� ���� ������������ ���ĵȴ�.
*
*	@return ���(Ȧ)�� ���� ��ȯ�Ѵ�(non-manifold ������ �ִٸ� -1�� ��ȯ�Ѵ�).
*/
int get_bndry_verts_from_faces(std::vector<EgFace *> &Faces, std::vector<std::vector<EgVertex *>> &BndryList, bool bClockWise, bool bSortByLen);

/*!
*	\brief	������ ����� ��� �ﰢ�� ����Ʈ�� ���Ѵ�.
*
*	\param	BndryVerts[in]		���(Ȧ) ������ ����Ʈ
*	\param	BndryFaces[out]		���(Ȧ) ������ ����� �ﰢ�� ����Ʈ�� ����ȴ�.
*
*	\return �ﰢ���� ���� ��ȯ�Ѵ�.
*/
int get_bndry_faces(std::vector<EgVertex *> &BndryVerts, std::vector<EgFace *> &BndryFaces);

/*!
*	\brief	�޽��� ��� ��� ������ ����� �ﰢ�� ����Ʈ�� ���Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	BndryFaces[out]		��� ������ ����� �ﰢ���� ����Ʈ�� �����
*
*	\return	�ﰢ���� ���� ��ȯ�Ѵ�.
*/
int get_bndry_faces(EgMesh *pMesh, std::vector<EgFace *> &BndryFaces);

/*!
*	\brief	���� �������� ����� ��� ������ ����Ʈ�� ���ϴ� �Լ�
*
*	\param	pStEdge[in]			���� ������ ���� ������
*	\param	BndryEdges[out]		��� ������ ����Ʈ�� �����
*
*	\return	������ ���� ��ȯ�Ѵ�.
*/
int get_bndry_edges(EgEdge *pStEdge, std::vector<EgEdge *> &BndryEdges);

/*!
*	\brief �޽� ���� ������ ����Ʈ�� ���Ѵ�.
*
*	\param pMesh[in]		��� �޽�
*	\param IntrVerts[out]	���� ������ ����ȴ�.
*
*	\return ���� ������ ���� ��ȯ�Ѵ�.
*/
int get_intr_verts(EgMesh *pMesh, std::vector<EgVertex *> &IntrVerts);

/*!
*	\brief ���� �ﰢ���� ���� ����Ʈ�� ���Ѵ�.
*
*	\param Faces[in]	���õ� �ﰢ���� ����Ʈ
*	\param Verts[out]	���õ� �ﰢ���� ������ ����ȴ�.
*
*	\return ������ ���� ��ȯ�Ѵ�.
*/
int get_verts_from_faces(const std::vector<EgFace *> &Faces, std::vector<EgVertex *> &Verts);

/*!
*	\brief ���� �ﰢ���� ���� ������ �ܺ� ������ ����Ʈ�� ���Ѵ�.
*
*	\param Faces[in]		���õ� �ﰢ���� ����Ʈ
*	\param IntrVerts[out]	���õ� �ﰢ���� ���� ������ ����ȴ�.
*	\param BndryVerts[out]	���õ� �ﰢ���� �ܺ� ������ ����ȴ�.
*
*	\return ������ ���� ��ȯ�Ѵ�.
*/
int get_verts_from_faces(const std::vector<EgFace *> &Faces, std::vector<EgVertex *> &IntrVerts, std::vector<EgVertex *> &BndryVerts);

/*!
*	\brief ���� ������ �ﰢ�� ����Ʈ�� ���Ѵ�.
*
*	\param Verts[in]	���õ� ������ ����Ʈ
*	\param Faces[out]	���õ� ������ �ﰢ���� ����ȴ�.
*
*	\return �ﰢ�� ���� ��ȯ�Ѵ�.
*/
int get_faces_from_verts(const std::vector<EgVertex *> &Verts, std::vector<EgFace *> &Faces);

/*!
*	\brief	�޽��� ������ ����-��� ������ ��迭 �Ѵ�.
*
*	\param	pMesh[IN/OUT] ��� �޽�
*
*	\return ����� ���� ��ȯ�Ѵ�.
*/
int rearrange_verts(EgMesh *pMesh);

