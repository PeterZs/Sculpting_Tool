#pragma once

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
*	\brief	2차원 벡터를 3차원 벡터로 변환한다.
*
*	\param	v[in]	2차원 벡터
*
*	\return 3차원 벡터를 반환한다.
*/
EgVec3 cast_vec3(const EgVec2 &v);

/*!
*	\brief	4차원 벡터를 3차원 벡터 형태로 반환한다.
*
*	\param	v[in] 4차원 벡터
*
*	\return 3차원 벡터를 반환한다.
*/
EgVec3 cast_vec3(const EgVec4 &v);

/*!
*	\brief	N 차원 벡터를 3차원 벡터로 변환한다.
*
*	\param	v[in]	N 차원 벡터
*
*	\return 3차원 벡터를 반환한다.
*/
EgVec3 cast_vec3(const EgVec &v);

/*!
*	\brief	점을 벡터로 변환한다.
*
*	\param	pt[in]	3차원 공간의 점
*
*	\return 변환된 벡터를 반환한다.
*/
EgVec3 cast_vec3(const EgPos &p);

/*!
*	\brief	3차원 벡터를 4차원 벡터형태로 반환한다.
*
*	\param	v[in]	3차원 벡터
*	\param	w[in]	4번째 좌표값
*
*	\return v의 확장된 4차원 벡터 표현을 반환한다.
*/
EgVec4 cast_vec4(const EgVec3 &v, double w = 0.0);

/*!
*	\brief	점 pt의 좌표를 4차원 벡터로 반환한다.
*
*	\param	pt[in]	3차원 공간의 점
*	\param	w[in]	4번째 좌표값
*
*	\return pt의 4차원 벡터 표현을 반환한다.
*/
EgVec4 cast_vec4(const EgPos &p, double w = 0.0);

/*!
*	\brief	쿼터니온을 4차원 벡터로 변환한다.
*
*	\param	q[in]	대상 쿼터니온
*
*	\return 4차원 벡터를 반환한다.
*/
EgVec4 cast_vec4(const EgQuat &q);

/*!
*	\brief	2차원 벡터 v의 좌표를 일반적인 벡터 형태로 반환한다.
*
*	\param	v[in]	2차원 벡터
*
*	\return 3차원 벡터 v의 좌표를 일반적인 벡터 형태로 반환한다.
*/
EgVec cast_vec(const EgVec2 &v);

/*!
*	\brief	3차원 벡터 v의 좌표를 일반적인 벡터 형태로 반환한다.
*
*	\param	v[in]	3차원 공간의 벡터
*
*	\return 3차원 벡터 v의 좌표를 일반적인 벡터 형태로 반환한다.
*/
EgVec cast_vec(const EgVec3 &v);

/*!
*	\brief	4차원 벡터 v의 좌표를 일반적인 벡터 형태로 반환
*
*	\param	v[in]	4차원 공간의 벡터
*
*	\return 4차원 벡터 v의 좌표의 일반 벡터 표현을 반환한다.
*/
EgVec cast_vec(const EgVec4 &v);

/*!
*	\brief	점 pt의 좌표를 벡터형태로 반환한다.
*
*	\param	pt[in] 3차원 공간의 점
*
*	\return pt의 벡터 표현을 반환한다.
*/
EgVec cast_vec(const EgPos &p);

/*!
*	\brief	쿼터니온을 4차원 벡터로 변환한다.
*
*	\param	q[in]	대상 쿼터니온
*
*	\return 벡터를 반환한다.
*/
EgVec cast_vec(const EgQuat &q);

/*!
*	\brief	벡터 v의 좌표를 포인트 형태로 반환한다.
*
*	\param	v[in] 3차원 공간의 벡터
*
*	\return v의 좌표를 포인트 형태로 반환한다.
*/
EgPos cast_pos(const EgVec3 &v);

/*!
*	\brief	4차원 벡터 v의 좌표를 3차원 포인트 형태로 반환한다.
*
*	\param	v[in]	4차원 공간의 벡터
*
*	\return 4차원 벡터 v의 좌표를 3차원 포인트 형태로 반환한다.
*/
EgPos cast_pos(const EgVec4 &v);

/*!
*	\brief	n 차원 벡터를 3차원 포인트의 형태로 변환한다.
*
*	\param	v[in]	벡터
*
*	\return v의 3차원 포인트 표현을 반환한다.
*/
EgPos cast_pos(const EgVec &v);

/*!
*	\brief	행렬의 원소를 담은 실수배열을 반환한다.
*
*	\param	m[in]	행렬
*
*	\return 행렬의 원소를 저장한 실수 배열을 반환한다.
*/
double *cast_arr(EgMat &m);

/*!
*	\brief	쿼터니온으로 표현되는 회전을 4 by 4 행렬로 변환한다.
*
*	\param	q[in]		대상쿼터니온
*	\param	isGL[in]	만약 true 이면 행렬에 OpenGL 형태로 계산된다.
*
*	\return 회전을 표현하는 행렬을 반환한다.
*/
EgMat cast_mat(const EgQuat &q, bool isGL = true);

/*!
*	\brief 강체변환 X에 해당하는 4행 4열의 동차좌표변환행렬로 변환한다.
*	\param X 강체변환
*	\param isGL 만약 true 이면 행렬에 OpenGL 형태로 저장한다.
*
*	\return 강체변환을 표현하는 행렬
*/
EgMat cast_mat(const EgTrans &X, bool isGL = true);

/*!
*	\brief	벡터를 쿼터니온의 형태로 변환한다.
*
*	\param	v[in]	벡터
*
*	\return 변환된 쿼터니온 (w, x, y, z) = (v[0], v[1], v[2], v[3])을 반환한다.
*/
EgQuat cast_quat(const EgVec &v);

/*!
*	\brief	4차원 벡터를 쿼터니온으로 변환한다.
*
*	\param	v[in]	4차원 벡터
*
*	\return 변환된 쿼터니온 (w, x, y, z) = (v[0], v[1], v[2], v[3])을 반환한다.
*/
EgQuat cast_quat(const EgVec4 &v);
