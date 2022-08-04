#pragma once

/*! \brief ���� ���� ������ ǥ���ϴ� �ڷ��� */
typedef QNode<EgEdge *, double> EdgeSplit;

/*!
*	\brief	���� ���� ���� ���θ� �Ǵ��Ѵ�.
*
*	\param	e[in]			������ ������ ���� ������
*	\param	Low[in]			������ ������ ���̰� Low���� ª�ƾ� �Ѵ�.
*	\param	High[in]		������, High���� �� ������ �����Ǹ� �������� ���Ѵ�.
*
*	\return ���� �����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool is_collapsable(EgEdge *e, double Low, double High);

/*!
*	\brief	���� �ø� ������ �˻��Ѵ�.
*
*	\param	e[in]	�˻��� ������ ������
*
*	\return �ø� ������ ����ϸ� true, �ƴϸ� false�� ��ȯ�Ѵ�.
*/
bool is_flippable(EgEdge *e);

/*!
*	\brief	������ ���޽��� �����Ѵ�.
*	\note	���� �ؽ�ó ������
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	TarLenOrRate[in]	��ǥ ������ ���� �Ǵ� ��� ���� ���� ��� ����
*	\param	bRate[in]			�����̸� true, ���̸� false
*	\param	bFixedBndry[in]		��踦 ������Ű���� true, �ƴϸ� false�� ����
*	\param	FixedVerts[in]		Relaxation ����� ������ų ������ ����Ʈ
*/
void remesh(EgMesh *pMesh, double TarLenOrRate, bool bRate, bool bFixedBndry, std::vector<EgVertex *> &FixedVerts = std::vector<EgVertex *>());

/*!
*	\brief	�޽��� ������ �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	High[in]			���� ���� ����(High ���� �� ������ ����)
*	\param	bUpdateNormal[in]	���� ���� ��, ���� ���� ����
*/
void remesh_edge_split(EgMesh *pMesh, double High, bool bUpdateNormal = true);

/*!
*	\brief	�޽��� ���� e = (v1, v2)�� �����Ѵ�.
*	\note	v1�� v2������ ��������, v1�� ������� �ʴ� ������ �ȴ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	Low[in]				���� ���� ����(Low ���� ª�� ������ ����)
*	\param	High[in]			���� ���� ��, High ���� �� ������ �����Ǹ� �������� �ʴ´�.
*	\param	bFixedBndry[in]		��� ������ ������ �����Ϸ��� true, �ƴϸ� false
*	\param	bUpdateNormal[in]	���� ���� ��, ���� ���� ����
*/
void remesh_edge_collapse(EgMesh *pMesh, double Low, double High, bool bFixedBndry, bool bUpdateNormal = true);

/*!
*	\brief	���� �ø��� ���� ������ ������ ����ȭ �Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	bUpdateNormal[in]	���� �ø� ��, ���� ���� ����
*/
void remesh_edge_flip(EgMesh *pMesh, bool bUpdateNormal = true);

/*!
*	\brief	������ ��ġ�� ��������� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	FixedVerts[in]		������ų ������ ����Ʈ
*/
void remesh_relaxation(EgMesh *pMesh, std::vector<EgVertex *> &FixedVerts = std::vector<EgVertex *>());

/*!
*	\brief	���� ������ ���� ������ ���޽��� �����Ѵ�.
*
*	\param	pMesh[in]			��� �޽�
*	\param	TarLenOrRate[in]	Ÿ�� ���� ���� �Ǵ� ����
*	\param	bRate[in]			true �̸� Ÿ�� ���� ����, false�̸� ����
*	\param	Faces[in]			���� ������ �ﰢ�� ����Ʈ
*/
void remesh_region(EgMesh *pMesh, double TarLenOrRate, bool bRate, std::vector<EgFace *> &Faces);

/*!
*	\brief	���� ������ ������ �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	High[in]		High���� �� ������ �����Ѵ�.
*	\param	FixedFaces[in]	���� ������ �ﰢ�� ����Ʈ
*/
void remesh_edge_split_region(EgMesh *pMesh, double High, std::vector<EgFace *> &FixedFaces);

/*!
*	\brief	���� ������ ���� e = (v1, v2)�� �����Ѵ�.
*	\note	v1�� v2������ ��������, v1�� ������� �ʴ� ������ �ȴ�.
*
*	\param	pMesh[in]			��� �޽��� ���� ������
*	\param	Low[in]				Low ���� ª�� ������ �����Ѵ�.
*	\param	High[in]			���� ���� ��, High ���� �� ������ �����Ǹ� �������� �ʴ´�.
*	\param	bFixedBndry[in]		��� ������ ������ �����Ϸ��� true, �ƴϸ� false
*	\param	FixedFaces[in]		���� ������ �ﰢ�� ����Ʈ
*/
void remesh_edge_collapse_region(EgMesh *pMesh, double Low, double High, bool bFixedBndry, std::vector<EgFace *> &FixedFaces);

/*!
*	\brief	�޽� ��踦 ���޽� �Ѵ�.
*
*	\param	pMesh[in]		��� �޽��� ���� ������
*	\param	LenOrRate[in]	��ǥ ������ ���� �Ǵ� ��� ���� ���� ��� ����
*	\param	bRate[in]		�����̸� true, ���̸� false
*/
void remesh_bndry(EgMesh *pMesh, double TarLenOrRate, bool bRate);
