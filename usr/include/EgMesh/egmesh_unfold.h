#pragma once

/*!
*	\brief	2차원 정의역 매개화된 메쉬를 생성한다.
*	\note	경계 시작점의 인덱스를 인수로 추가, pMesh를 rearrange_verts하도록 수정 (박정호)
*
*	\param	pMesh[in]			대상 메쉬
*	\param	BndryType[in]		2차원 정의역 형태(0: 단위 정사각형, 1: 단위 원)
*	\param	StartVertIdx[in]	경계 시작점의 인덱스 (0 <= StartVertIdx < 메쉬의 경계 정점 수)
*
*	\return 매개화된 2차원 메쉬를 반환한다.
*/
EgMesh *get_unfold_mesh(EgMesh *pMesh, int BndryType, int StartVertIdx = 0);

/*!
*	\brief	2차원으로 등각 매개화된 메쉬를 생성한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	pConstFace[in]	제약 삼각형
*
*	\return 매개화된 2차원 메쉬를 반환한다.
*/
EgMesh *get_unfold_mesh_conformal(EgMesh *pMesh, EgFace *pConstFace);