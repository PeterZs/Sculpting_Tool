#pragma once

/*!
*	\brief	2���� ���ǿ� �Ű�ȭ�� �޽��� �����Ѵ�.
*	\note	��� �������� �ε����� �μ��� �߰�, pMesh�� rearrange_verts�ϵ��� ���� (����ȣ)
*
*	\param	pMesh[in]			��� �޽�
*	\param	BndryType[in]		2���� ���ǿ� ����(0: ���� ���簢��, 1: ���� ��)
*	\param	StartVertIdx[in]	��� �������� �ε��� (0 <= StartVertIdx < �޽��� ��� ���� ��)
*
*	\return �Ű�ȭ�� 2���� �޽��� ��ȯ�Ѵ�.
*/
EgMesh *get_unfold_mesh(EgMesh *pMesh, int BndryType, int StartVertIdx = 0);

/*!
*	\brief	2�������� � �Ű�ȭ�� �޽��� �����Ѵ�.
*
*	\param	pMesh[in]		��� �޽�
*	\param	pConstFace[in]	���� �ﰢ��
*
*	\return �Ű�ȭ�� 2���� �޽��� ��ȯ�Ѵ�.
*/
EgMesh *get_unfold_mesh_conformal(EgMesh *pMesh, EgFace *pConstFace);