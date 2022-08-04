#pragma once

class EgMesh;

/*!
*	\brief	정점의 국소 영역의 면적을 계산한다.
*	\note	참고 논문: Discrete Differential-Geometry Operators for Triangulated 2-Manifolds
*
*	\param	pVert[in]	정점에 대한 포인터
*
*	\return 국소 영역의 면적을 반환한다.
*/
double get_mixed_voronoi_cell_area(EgVertex *pVert);

/*!
*	\brief	정점의 국소 영역 경계점의 리스트를 생성한다.
*	\note	주로 디버깅을 위한 렌더링 용으로 사용
*
*	\param	pMesh[in]		대상 메쉬
*	\param	BndryPts[out]	i번째 정점의 국소 영역의 경계점은 BndryPt[i][]에 저장된다.
*/
void get_mixed_voronoi_cell_bndry(EgMesh *pMesh, std::vector<std::vector<EgPos>> &BndryPts);

/*!
*	\biref	폴리 라인(Polyline)의 각 정점의 곡률을 계산한다.
*	\note	마지막 수정일: 2022-04-16
*	\note	양 끝점의 곡률은 0으로 정한다.
*
*	\param	Pts[in]			폴리 라인의 정점 리스트
*	\param	Ks[out]			각 정점의 곡률이 저장된다.
*	\param	bSigned[in]		곡률 부호를 고려하면 true, 아니면 false
*	\param	Up[in]			폴리 라인이 놓인 평면의 법선 벡터
*/
void get_curvature_polyline(std::vector<EgPos> &Pts, std::vector<double> &Ks, bool bSigned, EgVec3 Up);

/*!
*	\biref	정점의 가우스 곡률을 계산한다.
*	\note	마지막 수정일: 2022-04-16
*
*	\param	pVert[in]		대상 정점
*	\param	bLocalAvg[in]	국소 면적으로 평균 계산 여부
*
*	\return 정점의 가우스 곡률을 반환한다.
*/
double get_gaussian_curvature(EgVertex *pVert, bool bLocalAvg);

/*!
*	\biref	메쉬의 가우스 곡률을 계산한다.
*	\note	마지막 수정일: 2022-04-16
*
*	\param	pMesh[in]	대상 메쉬
*	\param	Ks[out]		i번째 정점의 가우스 곡률이 Ks[i]에 저장된다.
*	\param	Kmin[out]	최소 가우스 곡률이 저장된다.
*	\param	Kmax[out]	최대 가우스 곡률이 저장된다.
*/
void get_gaussian_curvature(EgMesh *pMesh, std::vector<double> &Ks, double &Kmin, double &Kmax);

/*!
*	\biref	정점의 평균 곡률을 계산한다(박정호).
*	\note	경계 정점의 경우 주변 곡률의 평균값으로 대체
*
*	@param	pVert[in]		대상 정점
*	@param	bLocalAvg[in]	국소 면적으로 평균 계산 여부
*
*	@return 정점의 평균 곡률을 반환한다.
*/
double get_mean_curvature(EgVertex *pVert, bool bLocalAvg);

/*!
*	\biref	메쉬의 평균 곡률을 계산한다.
*
*	\param	pMesh[in]	대상 메쉬
*	\param	Hs[out]		i번째 정점의 평균 곡률이 Hs[i]에 저장된다.
*	\param	Hmin[out]	최소 평균 곡률이 저장된다.
*	\param	Hmax[out]	최대 평균 곡률이 저장된다.
*/
void get_mean_curvature(EgMesh *pMesh, std::vector<double> &Hs, double &Hmin, double &Hmax);

/*!
*	\biref	정점의 주곡률과 주방향을 계산한다.
*	\note	1. 참고 문헌: "A Novel Cubic-Order Algorithm for Approximating Principal Direction Vectors", GOLDFEATHER, J., AND INTERRANTE, V. 2004.
*			2. 주곡률은 음수, 양수 모두 가질 수 있음
*
*	\param	vtx[in]			메쉬 정점
*	\param	k1[out]			최대 곡률이 저장된다.
*	\param	k2[out]			최소 곡률이 저장된다.
*	\param	e1[out]			최대 곡률 방향이 저장된다.
*	\param	e2[out]			최소 곡률 방향이 저장된다.
*	\param	MethodType[in]	곡률 계산을 위한 기법(0: 이산 미분 기하, 1: 곡면 피팅)
*/
void get_principal_curvature(EgVertex *vtx, double &k1, double &k2, EgVec3 &e1, EgVec3 &e2, int MethodType);

/*!
*	\biref	메쉬 각 정점의 주곡률과 주방향을 계산한다.
*	\note	1. 참고 문헌: "A Novel Cubic-Order Algorithm for Approximating Principal Direction Vectors", GOLDFEATHER, J., AND INTERRANTE, V. 2004.
*			2. 주곡률은 음수, 양수 모두 가질 수 있음
*
*	\param	pMesh[in]		대상 메쉬
*	\param	K1[out]			i번째 정점의 최대 곡률이 K1[i]에 저장된다.
*	\param	K2[out]			i번째 정점의 최소 곡률이 K2[i]에 저장된다.
*	\param	E1[out]			i번째 정점의 최대 곡률 방향이 E1[i]에 저장된다.
*	\param	E2[out]			i번째 정점의 최소 곡률 방향이 E2[i]에 저장된다.
*	\param	MethodType[in]	곡률 계산을 위한 기법(0: 이산 미분 기하, 1: 곡면 피팅)
*/
void get_principal_curvature(EgMesh *pMesh, std::vector<double> &K1, std::vector<double> &K2, std::vector<EgVec3> &E1, std::vector<EgVec3> &E2, int MethodType);

/*!
*	\brief	메쉬의 라플라시안 행렬을 계산한다.
*
*	\param	pMesh[in]	대상 메쉬
*	\param	D[out]		국소 면적의 역수(1/A_i)가 대각선 원소에 저장된다.
*	\param	M[out]		라플라시안 행렬이 저장된다.
*	\param	Type[in]	가중치 타입(0: uniform, 1: cotangent, 2: concavity-aware, 3: convexity-aware)
*/
void get_laplacian_matrix(EgMesh *pMesh, Eigen::SparseMatrix<double> &D, Eigen::SparseMatrix<double> &M, int WgtType);

/*!
*	\brief	특징 추출을 위한 라플라스 행렬을 계산한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Verts[in]		부분 영역에 대한 정점의 리스트(비제약 정점 + 제약 정점 순으로 저장됨)
*	\param	M[out]			라플라시안 행렬이 저장된다.
*	\param	bConcavity[in]	오목한 특징을 추출할 경우 true, 볼록한 특징을 추출할 경우 false
*/
void get_laplacian_matrix_roi(EgMesh *pMesh, std::vector<EgVertex *> &Verts, Eigen::SparseMatrix<double> &M, bool bConcavity = true);

/*!
*	\brief	메쉬의 각 삼각형에서 그래디언트를 계산한다.
*	\note	마지막 수정일: 2020-11-02
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Values[in]		각 정점에 할당된 스칼라 값
*	\param	Gradients[out]	Gradients[i]에 i번째 삼각형의 그래디언트가 저장된다.
*	\param	bNormalize[in]	그래디언트의 정규화 여부
*/
void get_gradient_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<EgVec3> &Gradients, bool bNormalize);

/*!
*	\brief	메쉬의 각 삼각형에서 그래디언트 장의 크기를 계산한다.
*	\note	마지막 수정일: 2022-04-20
*
*	\param	pMesh[in]		대상 메쉬
*	\param	Values[in]		각 정점에 할당된 스칼라 값
*	\param	Magnitudes[out]	Magnitudes[i]에 i번째 삼각형의 그래디언트 크기가 저장된다.
*/
void get_gradient_magnitude_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<double> &Magnitudes);

/*!
*   \brief   메쉬의 각 정점의 발산을 계산한다.
*
*   \param   pMesh[in]			대상 메쉬
*   \param   Values[in]         각 삼각형에 할당된 벡터 값
*   \param   Divergences[out]   i번째 정점의 발산이 Divergence[i]에 저장된다.
*/
void get_divergence_field(EgMesh *pMesh, std::vector<EgVec3> &Values, std::vector<double> &Divergences);

/*!
*	\brief	메쉬의 각 정점의 라플라시안을 계산한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	Values[in]			각 정점에 할당된 스칼라 값
*	\param	Laplacians[out]		Laplacians[i]에 i번째 정점의 라플라시안이 저장된다.
*	\param	WgtType[in]			에지 가중치 타입 (0: unifork, 1: cotangent, 2: concavity, 3: convex)
*/
void get_laplacian_field(EgMesh *pMesh, std::vector<double> &Values, std::vector<double> &Laplacians, int WgtType);
