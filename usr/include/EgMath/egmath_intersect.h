#pragma once

/*!
*	\brief	직선과 직선의 교차점을 계산한다.
*	\note	마지막 수정일: 2021-05-08
*
*	\param	l0[in]		첫 번째 직선의 방정식
*	\param	l1[in]		두 번째 직선의 방정식
*	\param	t0[out]		첫 번째 직선위 교차점의 파라미터 값이 저장됨
*	\param	t1[out]		두 번째 직선위 교차점의 파라미터 값이 저장됨
*	\param	p[out]		교차점이 저장될 변수
*
*	\return 두 직선이 교차하면 true, 교차하지 않으면(평행, 꼬인 위치) false를 반환한다.
*/
bool intersect_line_line(
	EgLine l0,	EgLine l1, 
	double &t0, double &t1, EgPos &p);

/*!
*	\brief	두 에지 (p0, p1), (q0, q1)의 교차 여부와 교차점을 계산한다.
*	\noet	마지막 수정일: 2021-05-04
*
*	\param	p0[in]	첫 번째 에지의 시작점
*	\param	p1[in]	첫 번째 에지의 끝점
*	\param	q0[in]	두 번째 에지의 시작점
*	\param	q1[in]	두 번째 에지의 끝점
*	\param	pt[out]	교차할 경우 교차점이 저장된다.
*
*	\return 두 에지가 교차하면 true, 아니면 false를 반환한다.
*/
bool intersect_edge_edge(
	EgPos p0, EgPos p1, 
	EgPos q0, EgPos q1, 
	EgPos &pt);


/*!
*	\brief	직선과 삼각형 (p1p2p3)의 교차점을 계산한다.
*	\note	참고문헌: Real-time rendering (pp. 581)
*
*	\param	p1[in]				삼각형의 첫 번째 정점(반시계 방향)
*	\param	p2[in]				삼각형의 두 번째 정점(반시계 방향)
*	\param	p3[in]				삼각형의 세 번째 정점(반시계 방향)
*	\param	l[in]				직선의 방정식
*	\param	t[out]				교차점의 직선 파라미터가 저장됨
*	\param	q[out]				교차점이 저장됨
*	\param	alpha[out]			barycentric 좌표가 저장됨
*	\param	beta[out]			barycentric 좌표가 저장됨
*	\param	gamma[out]			barycentric 좌표가 저장됨
*	\param	bCullBackFace[in]	직선이 삼각형의 뒷면과 만나는 경우를 제외하려면. (디폴트: true).
*	\note	q = alpha * p1 + beta * p2 + gamma * p3, (alpha + beta + gamma = 1)
*
*	\return true: 성공, false: 직선이 삼각형이 평행하거나 교차점이 삼각형의 외부에 존재하는 경우.
*/
bool intersect_line_tri(
	const EgPos &p1, const EgPos &p2, const EgPos &p3, 
	const EgLine &l, 
	double &t, 
	EgPos &q, 
	double &alpha, 
	double &beta, 
	double &gamma, 
	bool bCullBackFace = true);

/*!
*	\brief	직선과 삼각형 (p1p2p3)의 교차점을 계산한다.
*	\note	참고문헌: Real-time rendering (pp. 581)
*
*	\param	p1[in]				삼각형의 첫 번째 정점(반시계 방향)
*	\param	p2[in]				삼각형의 두 번째 정점(반시계 방향)
*	\param	p3[in]				삼각형의 세 번째 정점(반시계 방향)
*	\param	l[in]				직선의 방정식
*	\param	q[out]				교차점이 저장됨
*	\param	bCullBackFace[in]	직선이 삼각형의 뒷면과 만나는 경우를 제외하려면. (디폴트: true).
*
*	\return true: 성공, false: 직선이 삼각형이 평행하거나 교차점이 삼각형의 외부에 존재하는 경우.
*/
bool intersect_line_tri(
	const EgPos &p1, const EgPos &p2, const EgPos &p3, 
	const EgLine &l,
	EgPos &q, 
	bool bCullBackFace = true);

/*!
*	\brief	삼각형 T1 = (u0, u1, u2)과 T2 = (v0, v1, v2)의 교차 여부와 교차점을 계산한다.
*	\note	참고문헌: Real-time rendering (ERIT 방법)
*
*	\param	u0[in]	삼각형 T1의 첫 번째 정점(반시계 방향)
*	\param	u1[in]	삼각형 T1의 두 번째 정점(반시계 방향)
*	\param	u2[in]	삼각형 T1의 세 번째 정점(반시계 방향)
*	\param	v0[in]	삼각형 T2의 첫 번째 정점(반시계 방향)
*	\param	v1[in]	삼각형 T2의 두 번째 정점(반시계 방향)
*	\param	v2[in]	삼각형 T2의 세 번째 정점(반시계 방향)
*	\param	p[out]	두 삼각형의 첫 번째 교차점이 저장된다.
*	\param	q[out]	두 삼각형의 두 번째 교차점이 저장된다.
*
*	\return 두 삼각형이 교차하면 true, 아니면 false를 반환한다.
*/
bool intersect_tri_tri(
	EgPos u0, EgPos u1, EgPos u2, 
	EgPos v0, EgPos v1, EgPos v2, 
	EgPos &p, EgPos &q);

/*!
*	\brief	에지와 평면의 교차점을 계산한다.
*
*	\param	p[in]		에지의 시작점
*	\param	q[in]		에지의 끝점
*	\param	pi[in]		평면 객체
*	\param	pt[out]		교차점이 저장된다.
*
*	\return 에지와 평면이 교차하면 true, 아니면 false를 반환한다.
*/
bool intersect_edge_plane(EgPos p, EgPos q, EgPlane pi, EgPos &pt);

/*!
*	\brief	삼각형과 경계 상자의 교차 여부를 검사한다.
*	\note	참고문헌: Real-time rendering
*
*	\param	u0[in]			삼각형의 첫 번째 정점
*	\param	u1[in]			삼각형의 두 번째 정점
*	\param	u2[in]			삼각형의 세 번째 정점
*	\param	box_min[in]		경계 상자의 최소점
*	\param	box_max[in]		경계 상자의 최대점
*
*	\return 삼각형과 경계 상자가 교차하면 true, 아니면 false를 반환한다.
*/
bool intersect_tri_box(EgPos u0, EgPos u1, EgPos u2, EgPos box_min, EgPos box_max);

/*!
*	\brief	직선과 평면의 교차점을 계산한다.
*
*	\param	l[in]	직선 객체
*	\param	pi[in]	평면 객체
*	\param	pt[out]	교차점이 저장될 변수
*
*	\return 평면과 직선이 교차하면 true, 아니면(평행, 직선이 평면에 포함) false를 반환한다.
*/
bool intersect_line_plane(EgLine l, EgPlane pi, EgPos &pt);

/*!
*	\brief	광선과 평면의 교차점을 계산한다.
*
*	\param	l[in]	광선 객체
*	\param	pi[in]	평면 객체
*	\param	pt[out]	교차점이 저장될 변수
*
*	\return 평면과 광선이 교차하면 true, 아니면(평행, 직선이 평면에 포함) false를 반환한다.
*/
bool intersect_ray_plane(EgLine l, EgPlane pi, EgPos &pt);

/*!
*	\brief	두 평면의 교차 직선을 계산한다.
*
*	\param	pi1[in]		첫 번째 평면
*	\param	pi2[in]		두 번째 평면
*	\param	l[out]		두 평면의 교차 직선이 저장된다.
*
*	\return 두 평면이 교차할 경우 true, 평행할 경우 false를 반환한다.
*/
bool intersect_plane_plane(EgPlane pi1, EgPlane pi2, EgLine &l);

/*!
*	\brief	세 평면의 교차점을 계산한다.
*
*	\param	pi1[in]		첫 번째 평면
*	\param	pi2[in]		두 번째 평면
*	\param	pi3[in]		세 번째 평면
*	\param	p[out]		교차점이 저장될 점 객체.
*
*	\return 세 평면이 한 점에서 교차하면 true, 아니면 false를 반환한다.
*/
bool intersect_three_planes(EgPlane &pi1, EgPlane &pi2, EgPlane &pi3, EgPos &pt);
