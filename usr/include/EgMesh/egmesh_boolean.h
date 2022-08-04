#pragma once

/*!
/*	\biref	두 메쉬 간의 교차를 계사하는 함수
*
*	\param	pBvh[in]		첫 번째 메쉬의 BVH
*	\param	pMesh[in]		두 번째 메쉬의 포인터
*	\param	CutFaces[out]	교차가 발생하는 두 번째 메쉬의 삼각형이 저장된다.
*	\param	CutLines[out]	교차선분이 저장된다.
*/
void intersect_mesh_mesh(
	EgBvh *pBvh, 
	EgMesh *pMesh, 
	std::vector<EgFace *> &CutFaces, 
	std::vector<std::pair<EgPos, EgPos>> &CutLines);

