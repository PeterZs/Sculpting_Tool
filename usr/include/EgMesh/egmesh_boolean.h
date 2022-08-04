#pragma once

/*!
/*	\biref	�� �޽� ���� ������ ����ϴ� �Լ�
*
*	\param	pBvh[in]		ù ��° �޽��� BVH
*	\param	pMesh[in]		�� ��° �޽��� ������
*	\param	CutFaces[out]	������ �߻��ϴ� �� ��° �޽��� �ﰢ���� ����ȴ�.
*	\param	CutLines[out]	���������� ����ȴ�.
*/
void intersect_mesh_mesh(
	EgBvh *pBvh, 
	EgMesh *pMesh, 
	std::vector<EgFace *> &CutFaces, 
	std::vector<std::pair<EgPos, EgPos>> &CutLines);

