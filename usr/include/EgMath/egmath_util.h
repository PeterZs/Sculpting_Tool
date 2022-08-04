#pragma once

// 클래스 선언
class EgPos;
class EgVec;
class EgVec2;
class EgVec3;
class EgVec4;
class EgMat;
class EgQuat;
class EgTrans;
class EgLine;
class EgPlane;

/*!
*	\brief	벡터 v를 벡터 w에 사영시킨 벡터를 구한다.
*
*	\param	v[in]	사영 벡터
*	\param	w[in]	기준 벡터
*
*	\return 벡터 v를 벡터 w에 사영시킨 벡터를 반환한다.
*/
EgVec2 proj(const EgVec2 &v, const EgVec2 &w);

/*!
*	\brief	벡터 v를 90도 회전한 수직 벡터를 구한다.
*	\note	마지막 수정일: 2020-07-05
*
*	\param	v[in]	회전할 벡터
*	\param	CCW[in]	회전 방향(반시계 방향: true, 시계 방향: false)
*
*	\return 벡터 v를 90도 회전한 수직 벡터를 반환한다.
*/
EgVec2 ortho(const EgVec2 &v, bool CCW);

/*!
*	\brief	두 벡터의 차이 벡터의 길이를 구한다.
*
*	\param	v[in]	첫 번째 벡터
*	\param	w[in]	두 번재 벡터
*
*	\return 차이 벡터 (v - w)의 길이를 반환한다.
*/
double dist(const EgVec2 &v, const EgVec2 &w);

/*!
*	\brief	벡터의 크기를 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 벡터 v의 크기를 반환한다.
*/
double norm(const EgVec2 &v);

/*!
*	\brief	벡터의 크기 제곱을 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 벡터 v의 크기 제곱을 반환한다.
*/
double norm_sq(const EgVec2 &v);

/*!
*	\brief	두 벡터의 사이각(0 ~ 180)을 구한다.
*
*	\param	v[in]		시작 벡터
*	\param	w[in]		끝 벡터
*	\param	radian[in]	각도의 형태(true: radian, false: degree)
*
*	\return 벡터 \a v에서 벡터 \a w까지의 사이각을 반환한다.
*/
double angle(const EgVec2 &v, const EgVec2 &w, bool radian = false);

/*!
*	\brief	벡터 v를 벡터 w에 사영시킨 벡터를 구한다.
*
*	\param	v[in]	사영 벡터
*	\param	w[in]	참조 벡터
*
*	\return 벡터 v를 벡터 w에 사영시킨 벡터를 반환한다.
*/
EgVec3 proj(const EgVec3 &v, const EgVec3 &w);

/*!
*	\brief	벡터 v에 수직한 단위 벡터를 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 벡터 v에 수직한 단위 벡터를 구하여 반환한다.
*/
EgVec3 ortho(const EgVec3 &v);

/*!
*	\brief	벡터 v와 w의 차이벡터의 길이를 구한다.
*
*	\param	v[in]	벡터
*	\param	w[in]	벡터
*
*	\return	벡터 \a v, \a w의 차이벡터의 길이를 반환한다.
*/
double dist(const EgVec3 &v, const EgVec3 &w);

/*!
*	\brief	벡터 u, v, w의 행렬식을 계산한다.
*
*	\param	u[in]	벡터
*	\param	v[in]	벡터
*	\param	w[in]	벡터
*
*	\return 벡터 u, v, w의 행렬식의 값을 반환한다.
*/
double det(const EgVec3 &u, const EgVec3 &v, const EgVec3 &w);

/*!
*	\brief	벡터 v의 크기를 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 벡터 \a v의 크기를 반환한다.
*/
double norm(const EgVec3 &v);

/*!
*	\brief	벡터 v의 크기의 제곱을 계산한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 벡터 \a v의 크기의 제곱을 반환한다.
*/
double norm_sq(const EgVec3 &v);

/*!
*	\brief	두 벡터 사이의 사이각(0 ~ 180)을 구한다.
*
*	\param	v[in]		시작 벡터
*	\param	w[in]		끝 벡터
*	\param	radian[in]	각도의 형태(true: radian, false: degree)
*
*	\return 벡터 \a v에서 벡터 \a w까지의 사이각(예각, 방향 상관없음)
*/
double angle(const EgVec3 &v, const EgVec3 &w, bool radian = false);

/*!
*	\brief	두 벡터 사이의 사이각(0 ~ 360)을 구한다.
*
*	\param	v[in]		시작 벡터
*	\param	w[in]		끝 벡터
*	\param	up[in]		회전축 벡터
*	\param	radian[in]	각도의 형태(true: radian, false: degree)
*
*	\return 벡터 \a v에서 벡터 \a w까지의 사이각(기준 벡터를 기준 반시계 방향)
*/
double angle(const EgVec3 &v, const EgVec3 &w, const EgVec3 &up, bool radian = false);

/*!
*	\brief	두 벡터가 평행인지 조사한다.
*	\note	마지막 수정일: 2021-05-08
*
*	\param	v[in]		첫 번째 벡터
*	\param	w[in]		두 번째 벡터
*	\param	eps[in]		오차의 허용 범위
*
*	\return 두 벡터가 평행(같은 방향 또는 반대 방향)이면 true, 아니면 false를 반환한다.
*/
bool is_parallel(EgVec3 v, EgVec3 w, double eps = 1.0e-14);

/*!
*	\brief	두 벡터가 수직인지 조사한다.
*	\note	마지막 수정일: 2021-05-08(가장 정확)
*
*	\param	v[in]		첫 번째 벡터
*	\param	w[in]		두 번째 벡터
*	\param	eps[in]		오차의 허용 범위
*
*	\return 두 벡터가 수직이면 true, 아니면 false를 반환한다.
*/
bool is_ortho(EgVec3 v, EgVec3 w, double eps = 1.0e-14);

/*!
*	\brief	세 벡터가 한 평면 위에 놓여 있는지 조사한다.
*
*	\param	u[in]		첫 번째 벡터
*	\param	v[in]		두 번째 벡터
*	\param	w[in]		세 번째 벡터
*	\param	eps[in]		오차의 허용 범위
*
*	\return 세 벡터가 한 평면 위에 놓여 있다면 true, 아니면 false를 반환한다.
*/
bool is_coplanar(EgVec3 u, EgVec3 v, EgVec3 w, double eps = 1.0e-9);

/*!
*	\brief	벡터 v의 크기를 구한다.
*
*	\param	v[in]	벡터
*
*	\return 벡터 \a v의 크기를 반환한다.
*/
double norm(const EgVec4 &v);

/*!
*	\brief	벡터 v의 크기 제곱을 구한다.
*
*	\param	v[in]	벡터
*
*	\return 벡터 \a v의 크기 제곱을 반환한다.
*/
double norm_sq(const EgVec4 &v);

/*!
*	\brief	두 벡터의 차이벡터의 크기를 구한다.
*
*	\param	v[in]	벡터
*	\param	w[in]	벡터
*
*	\return 두 벡터의 차이벡터의 크기를 반환한다.
*/
double dist(const EgVec4 &v, const EgVec4 &w);

/*!
*	\brief	가중치를 적용하여 동차 좌표로 변환한다: v=(x, y, z, w) -> v'=(wx, wy, wz, w)
*
*	\param	v[in]	대상 벡터
*
*	\return 동차 좌표 v'=(wx, wy, wz, w)를 반환한다.
*/
EgVec4 homogenize(const EgVec4 &v);

/*!
*	\brief	v=(wx, wy, wz, w) -> v'=(x, y, z, 1)
*
*	\param	v[in]	4차원 공간의 벡터
*
*	\return v'=(x, y, z, 1)를 반환한다.
*/
EgVec4 cartesianize(const EgVec4 &v);

/*!
*	\brief	동차 좌표 v=(wx, wy, wz, w) -> v'=(x, y, z, w)로 변환한다.
*
*	\param	v[in]	4차원 공간의 벡터
*
*	\return 변환된 벡터 v'=(x, y, z, w)를 반환한다.
*/
EgVec4 rationalize(const EgVec4 &v);

/*!
*	\brief	벡터의 크기를 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 계산된 크기를 반환한다.
*/
double norm(const EgVec &v);

/*!
*	\brief	벡터의 크기의 제곱을 구한다.
*
*	\param	v[in]	대상 벡터
*
*	\return 계산된 크기의 제곱을 반환한다.
*/
double norm_sq(const EgVec &v);

/*!
*	\brief	두 벡터의 차이벡터의 크기를 구한다.
*
*	\param	v[in]	첫 번째 벡터
*	\param	w[in]	두 번째 벡터
*
*	\return 두 벡터의 차이벡터의 크기를 반환한다.
*/
double dist(const EgVec &v, const EgVec &w);

/*!
*	\brief	포인트의 \a p의 길이를 구한다.
*
*	\param	p[in]	포인트
*
*	\return 포인트 \a p의 길이를 반환한다.
*/
double norm(const EgPos &p);

/*!
*	\brief	포인트의 \a p의 길이 제곱을 구한다.
*
*	\param	p[in]	포인트
*
*	\return 포인트 \a p의 길이 제곱을 반환한다.
*/
double norm_sq(const EgPos &p);

/*!
*	\brief	폴리 라인의 길이를 구한다.
*
*	\param	Pts[in]	폴리 라인을 구성하는 점들의 집합
*
*	\return 폴리 라인의 길이를 반환한다.
*/
double dist(std::vector<EgPos> &Pts);

/*!
*	\brief	점 \a p에서 점 \a q까지의 거리를 구한다.
*
*	\param	p[in]	첫 번째 점
*	\param	q[in]	두 번째 점
*
*	\return 점 \a p에서 점 \a q까지의 거리를 반환한다.
*/
double dist(const EgPos &p, const EgPos &q);

/*!
*	\brief	점 \a p에서 점 \a q까지의 거리 제곱을 구한다.
*
*	\param	p[in]	첫 번째 점
*	\param	q[in]	두 번째 점
*
*	\return 점 \a p에서 점 \a q까지의 거리 제곱을 반환한다.
*/
double dist_sq(const EgPos &p, const EgPos &q);

/*!
*	\brief	점 p와 q를 t : (1 - t)로 내분한다.
*
*	\param	p[in]	3차원 공간의 점
*	\param	q[in]	3차원 공간의 점
*
*	\return 점 p와 q의 내분점을 반환한다.
*/
EgPos lerp(const EgPos &p, const EgPos &q, double t);

/*!
*	\brief	점들의 affine combination을 구한다
*
*	\param	Pts[in]		점의 배열에 대한 포인터
*	\param	Wgts[in]	combination의 상수값
*
*	\return 점들의 affine combination의 결과를 반환한다.
*/
EgPos affine_sum(std::vector<EgPos> &Pts, std::vector<double> &Wgts);

/*!
*	\brief	삼각형이 둔각삼각형인지 검사한다.
*	\note	구현: 박정호(2019-02-03), 확인: 윤승현(2019-03-03)
*
*	\param	p[in]	삼각형의 첫 번째 정점(반시계 방향)
*	\param	q[in]	삼각형의 두 번째 정점(반시계 방향)
*	\param	r[in]	삼각형의 세 번째 정점(반시계 방향)
*
*	\return 각(rpq)각 둔각인 경우 1, 각(pqr)이 둔각인 경우 2, 각(qrp)가 둔각인경우 3, 둔각이 아닌경우 0를 반환한다.
*/
int is_obtuse_tri(const EgPos &p, const EgPos &q, const EgPos &r); // 박정호 2019 02 03 추가

/*!
*	\brief	삼각형의 외심(circumcenter)를 구한다.
*	\note	구현: 박정호(2019-02-03), 확인: 윤승현(2019-03-03)
*
*	\param	p[in]	삼각형의 첫 번째 정점(반시계 방향)
*	\param	q[in]	삼각형의 두 번째 정점(반시계 방향)
*	\param	r[in]	삼각형의 세 번째 정점(반시계 방향)
*
*	\return 삼각형의 외심의 위치를 반환한다.
*/
EgPos circumcenter(const EgPos &p, const EgPos &q, const EgPos &r); // 박정호 2019 02 03 추가

/*!
*	\brief	삼각형의 넓이를 구한다
*
*	\param	p[in]	삼각형의 첫 번째 정점(반시계 방향)
*	\param	q[in]	삼각형의 두 번째 정점(반시계 방향)
*	\param	r[in]	삼각형의 세 번째 정점(반시계 방향)
*
*	\return 삼각형의 넓이를 구하여 반환한다.
*/
double area_tri(const EgPos &p, const EgPos &q, const EgPos &r); // 박정호 2019 02 03 추가

/*!
*	\brief	세점 p, q, r로 정의되는 삼각형을 기준으로 pt의 barycentric 좌표를 계산한다.
*	\note	조건: pt는 (p, q, r)로 정의되는 평면 위에 존재한다고 가정
*	\note	마지막 수정일: 2021-04-29
*
*	\param	pt[in]	조사할 점의 좌표
*	\param	p[in]	삼각형의 첫 번째 정점(반시계 방향)
*	\param	q[in]	삼각형의 두 번째 정점(반시계 방향)
*	\param	r[in]	삼각형의 세 번째 정점(반시계 방향)
*
*	\return pt의 barycentric 좌표 (alpha, beta, gamma)를 반환한다 (pt = alpha * p + beta * q + gamma * r = r + alpha(p - r) + beta(q - r)).
*/
EgVec3 get_barycentric_coords(EgPos pt, EgPos p, EgPos q, EgPos r);

/*!
*	\brief	점 p의 좌표를 주어진 자리수까지(반올림하여) 나타냄
*
*	\param	p[in]		3차원 공간의 점
*	\param	place[in]	반올림할 자리수
*
*	\return 반올림된 점의 표현을 반환한다.
*/
EgPos round_off(const EgPos &p, int place);

/*!
*	\brief	전치행렬을 반환한다.
*
*	\param	m[in]	행렬
*
*	\return 행렬 \a m의 전치행렬을 반환한다.
*/
EgMat tr(const EgMat &m);

/*!
*	\brief	행렬의 row-echelon 폼을 반환한다.
*
*	\param	m[in]	행렬
*
*	\return row-echelon 폼을 반환한다.
*/
EgMat ref(const EgMat &m);

/*!
*	\brief	행렬의 reduced row-echelon 폼을 반환한다.
*
*	\param	m[in]	행렬
*
*	\return reduced row-echelon 폼을 반환한다.
*/
EgMat rref(const EgMat &m);

/*!
*	\brief	행렬 \a m의 Null 공간의 기저를 열 벡터로 갖는 행렬을 반환한다.
*
*	\param	m[in]	행렬
*
*	\return 행렬 \a m의 Null 공간의 기저를 열 벡터로 갖는 행렬을 반환한다.
*/
EgMat basis_null(const EgMat &m);

/*!
*	\brief	행렬의 rank (독립한 열벡터 혹은 행벡터의 수)를 계산
*
*	\param	m[in]	행렬
*
*	\return 구해진 행렬의 rank를 반환한다.
*/
int rank(const EgMat &m);

/*!
*	\brief	행렬의 nullity 를 계산
*
*	\param	m[in]	행렬
*
*	\return 구해진 nullity를 반환한다.
*/
int nullity(const EgMat &m);

/*!
*	\brief	LU 분해를 통해, 행렬 A의 행렬식을 구한다.
*
*	\param	A[in]	n x n 대상 행렬
*
*	\return 행렬식의 값을 반환한다.
*/
double det(const EgMat &A);

/*!
*	\brief	LU 분해를 통해, 행렬 A의 역행렬을 구한다.
*
*	\param	A[in]	n x n 대상행렬.
*
*	\return 행렬 A의 역행렬을 반환한다.
*/
EgMat inv(const EgMat &A);

/*!
*	\brief	행렬 A의 부분행렬을 반환한다.
*
*	\param	A[in]	행렬
*	\param	r0[in]	시작 행의 인덱스
*	\param	c0[in]	시작 열의 인덱스
*	\param	r1[in]	끝 행의 인덱스
*	\param	c1[in]	끝 열의 인덱스
*
*	\return 행렬 A의 부분행렬을 반환한다.
*/
EgMat sub(const EgMat &A, int r0, int c0, int r1, int c1);

/*!
*	\brief	행렬 A를 L(하삼각행렬)과 U(상삼각행렬)의 곱으로 분해
*
*	\param	A[in]	대상 정방행렬
*	\param	L[out]	하삼각행렬이 저장됨
*	\param	U[out]	상삼각행렬이 저장됨
*
*	\return 성공: true, 실패: false
*/
int dcmp_lu(const EgMat &A, EgMat &L, EgMat &U);

/*!
*	\brief	행렬 A를 L(하삼각행렬)과 U(상삼각행렬)로 변환(부분피봇팅(행교환)을 수행)
*			분해 후, lin_sys_lu(A, x, b, Idx)를 호출하여 선형 시스템 Ax = b 를 만족하는 벡터 x를 구함
*
*	\param	A[in\out]	n by n 행렬으로 LU 형태로 변환된다.
*	\param	Idx[out]	행 교환 정보가 저장된다.
*	\param	d[out]		행 교환수가 짝수이면 1, 홀수이면 -1 이 저장된다.
*
*	\return 성공하면 true, 실패하면 false를 반환한다.
*/
int dcmp_lu(EgMat &A, EgVec &Idx, double &d);

/*!
*	\brief	행렬 A를 Householder 행렬을 사용하여 Q * R로 분해
*
*	\param	A[in]	m x n 대상행렬
*	\param	Q[out]	m x m 직교행렬
*	\param	R[out]	m x n 상삼각행렬
*
*	\return 실패하면 -1, 성공하면 householder 행렬을 적용한 회수를 반환한다.
*/
int dcmp_qr(const EgMat &A, EgMat &Q, EgMat &R);

/*!
*	\brief	SVD를 이용하여 행렬 A를 A = U * W * tr(V)로 분해
*
*	\param	A[in]	m x n 행렬 (m >= n)
*	\param	U[out]	m x n 행렬로서 열벡터는 A의 열공간의 단위기저가 저장된다.
*	\param	S[out]	특이값이 저장될 n 차원벡터. W는 S의 원소로 생성되는 대각선 행렬
*	\param	V[out]	n x n 행렬로서 열벡터는 A의 행공간 및 널공간의 단위기저가 저장된다.
*/
void dcmp_sv(const EgMat &A, EgMat &U, EgVec &S, EgMat &V);

/*!
*	\brief	선형 방정식 Ax = b의 해를 구한다.
*
*	\param	A[in]		LU로 분해된 행렬(dcmp_lu(A, Idx, d)의 결과)
*	\param	x[out]		해가 저장될 벡터
*	\param	b[in]		상수 벡터
*	\param	Idx[in]		행의 교환정보를 저장한 벡터(dcmp_lu(A, Idx, d)의 결과)
*/
void lin_sys_lu(const EgMat &A, EgVec &x, const EgVec &b, const EgVec &Idx);

/*!
*	\brief	선형방정식 Ax = b 를 만족하는 minimum length least square 해를 구함
*
*	\param	A[in]	m x n 행렬 (m >= n)
*	\param	x[out]	해가 저장된다.
*	\param	b[in]	상수벡터
*
*	\return 조건수(condition number)를 반환한다.
*/
double lin_sys_sv(const EgMat &A, EgVec &x, const EgVec &b);

/*!
*	\brief	선형방정식 Ax = b 를 만족하는 minimum length least square 해 x를 구한다.\n
*			- 이 함수를 호출하기 전에, dcmp_sv(A, U, S, V)를 호출하여 행렬 A의 분해된 결과를 사용한다.
*			- 한번 분해된 행렬 A는 상수벡터 b만 바꾸면서 해를 구하게 된다.
*
*	\param	U[in]	m x n 행렬로 dcmp_sv(A, U, S, V)의 결과
*	\param	S[in]	n 차원 벡터로 dcmp_sv(A, U, S, V)의 결과
*	\param	V[in]	n x n 행렬로 dcmp_sv(A, U, S, V)의 결과
*	\param	x[out]	해가 저장될 n 차원 벡터
*	\param	b[in]	m 차원 상수벡터
*
*	\return 조건수(condition number)를 반환한다.
*/
double lin_sys_sv(const EgMat &U, const EgVec &S, const EgMat &V, EgVec &x, const EgVec &b);

/*!
*	\brief	Conjugate gradient 방법을 사용하여 선형방정식 Ax = b 를 푼다.\n
*			- 행렬 A는 대칭행렬이어야 한다.
*			- sparse 선형시스템을 풀기위한 효과적인 방법이다.
*
*	\param	A[in]		n x n 대칭행렬.
*	\param	x[in/out]	n 차원 초기 해 벡터.
*	\param	b[in]		n 차원 상수 벡터.
*	\param	iter[in]	반복회수, 만약 반복회수가 n이면 정확한 해를 구한다.
*
*	\return 실제 반복회수를 반환한다.
*/
int lin_sys_cg(const EgMat &A, EgVec &x, const EgVec &b, int iter);

/*!
*	\brief	QR 분해법을 이용하여 선형방정식 Ax = b의 least square 해를 찾는다.
*
*	\param	A[in]	m x n 행렬.
*	\param	x[out]	n 차원 해 벡터.
*	\param	b[in]	n 차원 상수 벡터.
*
*	\return 1: 성공, 0: 실패.
*/
int lin_sys_qr(const EgMat &A, EgVec &x, const EgVec &b);

/*!
*	\brief	상사변환(similarity transformation)을 사용하여 실수대칭행렬의 모든 eigenvector와 eigenvalue를 구한다.
*
*	\param	A[in]	n x n 대칭행렬.
*	\param	D[out]	n개의 eigenvalue를 저장된다.
*	\param	V[out]	n개의 eigenvector (열벡터)를 저장된다.
*
*	\return 상사변환의 회수를 반환한다.
*/
int eigen_sys(const EgMat &A, EgVec &D, EgMat &V);

/*!
*	\brief	dcmp_sv 를 사용하여 주성분 (principle component)를 찾는다.
*	\note	함수호출 후, Data 값들은 평균이 원점에 위치하도록 이동된다.
*
*	\param	Data[in]		m x n 데이터 행렬 (m: 데이터의 개수, n: 데이터의 차원)
*	\param	PC[out]			열벡터로 표현된 주성분.
*	\param	SigVal[out]		주성분벡터의 특이값을 저장한 n 차원 벡터.
*	\param	Mean[out]		평균벡터
*/
void pca(EgMat &Data, EgMat &PC, EgVec &SigVal, EgVec &Mean);

/*!
*	\brief	쿼터니온의 크기를 구한다.
*
*	\param	q[in] 대상 쿼터니온
*
*	\return 쿼터니온의 크기를 반환한다.
*/
double norm(const EgQuat &q);

/*!
*	\brief	쿼터니온의 역원을 구하는 함수.
*
*	\param	q[in] 대상 쿼터니온
*
*	\return 쿼터니온의 역원을 반환한다.
*/
EgQuat inv(const EgQuat &q);

/*!
*	\brief	벡터(pure imaginary 쿼터니온)의 exponential mapping을 구한다.
*
*	\param	v[in]	쿼터니온 q = (0, v)
*
*	\return 단위회전축 v/||v|| 를 중심으로 2 * ||v|| 의 회전각을 갖는 쿼터니온을 반환한다.
*/
EgQuat exp(const EgVec3 &v);

/*!
*	\brief	쿼터니온 q의 로그값을 구한다.
*
*	\param	q[in]	대상 쿼터니온
*
*	\return 순허수 쿼터니온의 허수부분 Log(q) = (0, x, y, z)을 반환한다.
*/
EgVec3 log(const EgQuat &q);

/*!
*	\brief  두 쿼터니온을 내적한다.
*
*	\param	q1[in]	쿼터니온
*	\param	q2[in]	쿼터니온
*
*	\return 내적값을 반환한다.
*/
double quat_dot(const EgQuat &q1, const EgQuat &q2);

/*!
*	\brief	쿼터니온 q1, q2를 Spherical linear interpolation 한다.
*
*	\param	q1[in]	쿼터니온
*	\param	q2[in]	쿼터니온
*	\param	t[in]	보간될 시간
*
*	\return 보간된 쿼터니온을 반환한다.
*/
EgQuat slerp(EgQuat q1, EgQuat q2, double t);

/*!
*	\brief	한 점에서 직선까지의 거리를 구한다.
*
*	\param	l[in]	직선
*	\param	q[in]	한 점
*
*	\return 점 \a q에서 직선 \a l까지의 수직거리
*/
double dist(const EgLine &l, const EgPos &q);

/*!
*	\brief	두 직선 l1(t)와 l2(t)사이의 최단 거리를 구한다.
*
*	\param	l1[in]	첫 번째 직선
*	\param	l2[in]	두 번째 직선
*	\param	t1[in]	최단 거리가 생기는 l1의 파리미터 값이 저장됨
*	\param	t2[in]	최단 거리가 생기는 l2의 파리미터 값이 저장됨
*
*	\return 두 직선 사이의 최단거리를 계산하여 반환한다 (두 직선이 만나는 경우 -1.0을 반환한다).
*/
double dist(EgLine &l0, EgLine &l1, double &t1, double &t2);

/*!
*	\brief	두 직선이 꼬인 위치에 있는지 조사한다.
*
*	\param	l0[in]	첫 번째 직선
*	\param	l1[in]	두 번째 직선
*
*	\return 두 직선이 꼬인 위치에 있다면 true, 아니면 false를 반환한다.
*/
bool is_skew(EgLine &l0, EgLine &l1);

/*!
*	\brief	평면 pi에서 점 p까지의 부호있는 거리를 계산한다.
*
*	\param	pi[in]	평면의 객체
*	\param	p[in]	평면 밖의 한점.
*
*	\return 평면 \a pi에서 점 \a p까지의 부호있는 거리
*/
double dist(EgPlane &pi, EgPos &p);

/*!
*	\brief	점 p를 평면 pi에 사영시킨 점을 구한다.
*
*	\param	p[in]	평면 밖의 점
*	\param	pi[in]	평면
*
*	\return	점 p를 평면 pi에 사영시킨 점을 반환한다.
*/
EgPos proj(EgPos &p, EgPlane &pi);

/*!
*	\brief	강체변환의 역변환을 구한다.
*
*	\param	X[in]	대상 객체
*
*	\return X의 역변환을 반환한다.
*/
EgTrans inv(const EgTrans &X);

/*!
*	\brief	강체변환의 이동성분을 구한다.
*
*	\param	X[in]	강체변환 객체
*
*	\return X의 이동정보를 반환한다.
*/
EgVec3 part_trans(const EgTrans &X);

/*!
*	\brief	강체변환의 회전성분을 구한다.
*
*	\param	X[in]	강체변환 객체
*
*	\return X의 회전정보를 반환한다.
*/
EgQuat part_rot(const EgTrans &X);

/*!
*	\brief	변환 X의 크기를 구한다.
*
*	\param	X[in]	강체변환
*
*	\return 변환 X의 크기를 반환한다.
*/
double norm(const EgTrans &X);

/*!
*	\brief	두 변환 사이의 거리를 구한다
*
*	\param	X1[in]		첫 번째 변환
*	\param	X2[in]		두 번째 변환
*
*	\return X1에서 X2변환까지의 거리를 반환한다.
*/
double dist(const EgTrans &X1, const EgTrans &X2);

/*!
*	\brief	X 좌표계에서 표현된 변환 dX를 Y 좌표계에서 표현된 변환으로 계산한다.
*
*	\param	X[in]		기준좌표계
*	\param	dX[in]		기준좌표계 X에서 표현된 변환
*	\param	Y[in]		대상좌표계
*
*	\return X에서 표현된 변환 dX를 Y에서 표현으로 변환하여 반환한다.
*/
EgTrans ad(const EgTrans &X1, const EgTrans &dX, const EgTrans &X2);

/*!
*	\brief	두 변환을 보간한다.
*
*	\param	X1[in]		첫 번째 변환
*	\param	X2[in]		두 번째 변환
*	\param	t[in]		보간 파라미터(0 ~ 1)
*
*	\return 보간된 변환이 반환된다.
*/
EgTrans lerp(EgTrans X1, EgTrans X2, const double t);

/*!
*	\brief Gift Wrap알고리즘을 이용하여 2차원 convex hull을 구한다.
*
*	\param InPts[in]	입력 정점
*	\param OutPts[out]	convex hull의 정점들이 반시계 방향으로 저장됨
*/
void find_convexhull_2d(const std::vector<EgPos> &InPts, std::vector<EgPos> &OutPts);

/*!
*	\brief	주어진 정점이 다각형 내부에 포함되는지 여부를 판단
*	\note	테스트 필요
*
*	\param	Pts[in]		다각형을 이루는 정점의 리스트(반시계 방향)
*	\param	p[in]		포함 여부를 조사할 정점
*
*	\return 다각형 내부에 포함될 경우 true, 그렇지 않으면 false를 반환
*/
bool pt_in_polygon(const std::vector<EgPos> &Pts, EgPos const &p);
