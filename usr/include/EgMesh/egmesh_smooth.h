#pragma once

/*!
*	\brief	삼각형을 분할하여 세분화된 메쉬를 만든다.
*	\note	분할 후에 UpdateEdgeMate(), UpdateNormal() 함수를 호출해 주어야 한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*/
void get_refined_mesh(EgMesh *pMesh);

/*!
*	\brief 메쉬 전체를 스무딩 한다.
*
*	\param pMesh[in] 대상 메쉬에 대한 포인터
*/
void get_smooth_mesh(EgMesh *pMesh);

/*!
*	\brief 메쉬 선택 영역을 스무딩 한다.
*
*	\param pMesh[in] 대상 메쉬에 대한 포인터
*	\param Faces[in] 선택된 영역의 삼각형 리스트
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgFace *> &Faces);

/*!
*	\brief 메쉬 선택 영역을 스무딩 한다.
*
*	\param pMesh[in] 대상 메쉬에 대한 포인터
*	\param Verts[in] 선택된 영역의 정점 리스트
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgVertex *> &Verts);

/*!
*	\biref	선택된 정점 주변을 스무딩 한다.
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	Verts[in]		선택된 정점의 리스트
*	\param	Radius[in]		스무딩을 적용할 거리(반경)
*	\param	bFixedBndry[in]	경계 영역 스무딩 여부
*/
void get_smooth_mesh_region(EgMesh *pMesh, const std::vector<EgVertex *> &Verts, double Radius, bool bFixedBndry);

/*!
*	\brief 메쉬 경계를 고정한 채 스무딩을 수행한다.
*
*	\param pMesh[in] 대상 메쉬에 대한 포인터
*/
void get_smooth_mesh_interior(EgMesh *pMesh);

/*!
*	\brief 메쉬 경계에 스무딩을 수행한다.
*
*	\param pMesh[in] 대상 메쉬에 대한 포인터
*/
void get_smooth_mesh_boundary(EgMesh *pMesh);

/*!
*	\brief 메쉬 법선을 스무딩 한다.
*
*	\param pMesh[in]	대상 메쉬에 대한 포인터
*/
void get_smooth_mesh_normal(EgMesh *pMesh);

/*!
*	\brief	메쉬의 하모닉 기저를 이용하여 스무딩 한다.
*	\note	마지막 수정일: 2020-09-25
*
*	\param	pMesh[in]		대상 메쉬에 대한 포인터
*	\param	PassRatio[in]	메쉬의 정점 수 대비 저주파 통과 수의 비율 (0.0 < PassRatio < 1.0)
*/
void get_smooth_mesh_low_pass_filter(EgMesh *pMesh, double PassRate);

/*!
*	\brief	메쉬 위의 스칼라 필드를 스무딩한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Field[in/out]	입력 필드, 스무딩된 필드로 대체된다.
*/
void get_smooth_field(EgMesh *pMesh, std::vector<double> &Field);

/*!
*	\brief	메쉬 경계를 고정한 상태로 면적을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	bUniformWgt[in]		라플라시안 행렬의 균등 가중치 사용 여부
*/
void get_fair_mesh_membrane(EgMesh *pMesh, bool bUniformWgt = false);

/*!
*	\brief	선택 영역의 면적을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	Faces[in]			선택 영역의 삼각형 리스트
*	\param	bUniformWgt[in]		라플라시안 행렬의 균등 가중치 사용 여부
*/
void get_fair_mesh_membrane(EgMesh *pMesh, const std::vector<EgFace *> &Faces, bool bUniformWgt = false);

/*!
*	\brief	제약 조건하에 메쉬 면적을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*	\param	pMesh[in]			대상 메쉬에 대한 포인터
*	\param	FreeVerts[in]		자유 정점의 리스트
*	\param	FixedVerts[in]		고정 정점의 리스트
*	\param	bUniformWgt[in]		라플라시안 행렬의 균등 가중치 사용 여부
*/
void get_fair_mesh_membrane(EgMesh *pMesh, const std::vector<EgVertex *> &FreeVerts, const std::vector<EgVertex *> &FixedVerts, bool bUniformWgt);

/*!
*	\brief	메쉬 경계를 고정한 상태로 메쉬의 곡률합을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*	\param	pMesh[in] 대상 메쉬에 대한 포인터
*/
void get_fair_mesh_thin_plate(EgMesh *pMesh);

/*!
*	\brief	선택 영역의 곡률합을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*	\param	pMesh[in]	대상 메쉬에 대한 포인터
*	\param	Faces[in]	선택 영역의 삼각형 리스트
*/
void get_fair_mesh_thin_plate(EgMesh *pMesh, const std::vector<EgFace *> &Faces);

/*!
*   \brief  메쉬 경계를 고정한 상태로 메쉬의 곡률의 변화율을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*   \param  pMesh[in]	대상 메쉬에 대한 포인터
*/
void get_fair_mesh_minimum_variation(EgMesh *pMesh);

/*!
*   \brief	선택 영역의 곡률 변화율을 최소화하는 fairing을 수행한다.
*	\note	호출 후, UpdateNormal() 함수를 이용하여 법선을 갱신한다.
*
*   \param	pMesh[in]	대상 메쉬에 대한 포인터
*   \param  Faces[in]	선택 영역의 삼각형 리스트
*/
void get_fair_mesh_minimum_variation(EgMesh *pMesh, const std::vector<EgFace *> &Faces);
