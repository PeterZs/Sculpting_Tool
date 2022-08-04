#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cassert>
#include <stdarg.h>
#include "egmath_type.h"
#include "egmath_opt.h"
#include "egmath_util.h"
#include "egmath_cast.h"
#include "egmath_intersect.h"

// 클래스 선언
class EgVec2;
class EgVec3;
class EgVec4;
class EgVec;
class EgPos;
class EgMat;
class EgQuat;
class EgTrans;
class EgLine;
class EgPlane;

/*!
*	\class	EgVec2
*	\brief	2차원 벡터를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgVec2
{
public:
	/*! \brief 2차원 벡터의 좌표 배열 */
	double m_Coords[2];

public:
	/*!
	*	\brief	생성자
	*
	*	\param	x[in]	벡터의 x 좌표
	*	\param	y[in]	벡터의 y 좌표
	*/
	EgVec2(double x = 0.0, double y = 0.0);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgVec2(const EgVec2 &cpy);

	/*!
	*	\brief	소멸자
	*/
	~EgVec2();	

	/*!
	*	\brief	벡터의 좌표를 설정한다.
	*
	*	\param	x[in]	벡터의 x 좌표
	*	\param	y[in]	벡터의 y 좌표
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec2 &Set(double x, double y);

	/*!
	*	\brief	벡터를 단위길이로 정규화한다.
	*
	*	\return 정규화된 자신을 반환한다.
	*/
	EgVec2 &Normalize();

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]	대입될 벡터
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgVec2 &operator =(const EgVec2 &rhs);

	/*!
	*	\brief	벡터를 더한다.
	*
	*	\param	rhs[in]	더할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec2 &operator +=(const EgVec2 &rhs);

	/*!
	*	\brief	벡터를 뺀다.
	*
	*	\param	rhs[in]		뺄 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec2 &operator -=(const EgVec2 &rhs);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec2 &operator *=(const double &s);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec2 &operator /=(const double &s);

	/*!
	*	\brief	단항 연산자(+)
	*
	*	\return 동일 부호를 갖는 객체를 반환한다.
	*/
	EgVec2 operator +() const;

	/*!
	*	\brief	단항 연산자(-)
	*
	*	\return 반대 부호를 갖는 객체를 반환한다.
	*/
	EgVec2 operator -() const;

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in]	좌표의 인덱스
	*
	*	\return 벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	double &operator [](const int &idx);

	/*!
	*	\brief	상수 객체에 대한 인덱스 연산자([])
	*
	*	\param	idx[in]	원소의 인덱스
	*
	*	\return 벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	const double &operator [](const int &idx) const;

	/*!
	*	\brief	두 벡터의 합을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 합 벡터를 반환한다.
	*/
	friend EgVec2 operator +(const EgVec2 &v, const EgVec2 &w);

	/*!
	*	\brief	두 벡터의 차를 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 차 벡터를 반환한다.
	*/
	friend EgVec2 operator -(const EgVec2 &v, const EgVec2 &w);

	/*!
	*	\brief	두 벡터의 내적을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 내적을 반환한다.
	*/
	friend double operator *(const EgVec2 &v, const EgVec2 &w);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec2 operator *(const EgVec2 &v, double s);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec2 operator *(double s, const EgVec2 &v);

	/*!
	*	\brief	벡터를 상수로 나눈다
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 상수로 나누어진 벡터를 반환한다.
	*/
	friend EgVec2 operator /(const EgVec2 &v, double s);

	/*!
	*	\brief	두 벡터가 같은지 검사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 같으면 true, 다르면 false를 반한한다.
	*/
	friend bool operator ==(const EgVec2 &v, const EgVec2 &w);

	/*!
	*	\brief	두 벡터가 다른지 검사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgVec2 &v, const EgVec2 &w);

	/*!
	*	\brief	벡터를 콘솔 창에 출력한다.
	*
	*	\param	os[in]	출력 스트림
	*	\param	v[in]	출력 벡터
	*
	*	\return 벡터가 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgVec2 &v);

	/*!
	*	\brief	벡터의 좌표를 입력 받는다.
	*
	*	\param	is[in]	입력 스트림
	*	\param	v[out]	대상 벡터
	*
	*	\return 입력 스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgVec2 &v);
};

/*!
*	\class	EgVec3
*	\brief	3차원 벡터를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgVec3
{
public:
	/*! \brief 3차원 벡터의 좌표 배열 */
	double m_Coords[3];

public:
	/*!
	*	\brief	생성자
	*
	*	\param	x[in]	벡터의 x 좌표
	*	\param	y[in]	벡터의 y 좌표
	*	\param	z[in]	벡터의 z 좌표
	*/
	EgVec3(double x = 0.0, double y = 0.0, double z = 0.0);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgVec3(const EgVec3 &cpy);

	/*!
	*	\brief	소멸자
	*/
	~EgVec3();	

	/*!
	*	\brief	벡터의 좌표를 설정한다.
	*
	*	\param	x[in]	설정할 x 좌표
	*	\param	y[in]	설정할 y 좌표
	*	\param	z[in]	설정할 z 좌표
	*/
	EgVec3 &Set(double x, double y, double z);

	/*!
	*	\brief	단위벡터로 정규화한다.
	*
	*	\return 정규화된 자신을 반환한다.
	*/
	EgVec3 &Normalize();
		
	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]	대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgVec3 &operator =(const EgVec3 &rhs);

	/*!
	*	\brief	벡터를 더한다.
	*
	*	\param	rhs[in]	더할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec3 &operator +=(const EgVec3 &rhs);

	/*!
	*	\brief	벡터를 뺀다.
	*
	*	\param	rhs[in]	뺄 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec3 &operator -=(const EgVec3 &rhs);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec3 &operator *=(const double &s);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	s[in]	나눌 상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec3 &operator /=(const double &s);

	/*!
	*	\brief	벡터를 외적한다.
	*
	*	\param	rhs[in]	외적할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec3 &operator ^=(const EgVec3 &rhs);

	/*!
	*	\brief	단항 연산자(+)
	*
	*	\return 동일부호를 갖는 객체를 반환한다.
	*/
	EgVec3 operator +() const;

	/*!
	*	\brief	단항 연산자(-)
	*
	*	\return 반대부호를 갖는 객체를 반환한다.
	*/
	EgVec3 operator -() const;

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in]		참조 인덱스
	*
	*	\return 벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	double &operator [](const int &idx);

	/*!
	*	\brief	상수객체에 대한 인덱스 연산자([])
	*
	*	\param	idx[in]	인덱스
	*
	*	\return 벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	const double &operator [](const int &idx) const;

	/*!
	*	\brief	두 벡터를 더한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 합을 반환한다.
	*/
	friend EgVec3 operator +(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	두 벡터를 뺀다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 차를 반환한다.
	*/
	friend EgVec3 operator -(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec3 operator *(const EgVec3 &v, const double &s);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec3 operator *(const double &s, const EgVec3 &v);

	/*!
	*	\brief	두 벡터의 내적을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 내적 결과를 반환한다.
	*/
	friend double operator *(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	역수 벡터를 구한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 역수 벡터를 반환한다.
	*/
	friend EgVec3 operator /(const double &s, const EgVec3 &v);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 상수로 나누어진 벡터를 반환한다.
	*/
	friend EgVec3 operator /(const EgVec3 &v, const double &s);

	/*!
	*	\brief	두 벡터의 외적 벡터를 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 외적 벡터 (v X w)를 반환한다.
	*/
	friend EgVec3 operator ^(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	두 벡터가 같은지 조사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	두 벡터가 다른지 조사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 다르면 ture, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgVec3 &v, const EgVec3 &w);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	v[in]		출력할 벡터
	*
	*	\return 벡터가 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgVec3 &v);

	/*!
	*	\brief	입력 연산자(>>)
	*
	*	\param	is[in]	입력스트림
	*	\param	v[out]	입력값이 저장될 벡터
	*
	*	\return 입력값이 제거된 입력스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgVec3 &v);
};

/*!
*	\class	EgVec4
*	\brief	4차원 벡터를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgVec4
{
public:
	/*! \brief 4차원 벡터의 좌표 배열 */
	double m_Coords[4];

public:
	/*!
	*	\brief	생성자
	*
	*	\param	x[in]	벡터의 x 좌표
	*	\param	y[in]	벡터의 y 좌표
	*	\param	z[in]	벡터의 z 좌표
	*	\param	w[in]	벡터의 w 좌표
	*/
	EgVec4(double x = 0.0, double y = 0.0, double z = 0.0, double w = 0.0);
	
	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgVec4(const EgVec4 &cpy);

	/*!
	*	\brief	소멸자
	*/
	~EgVec4();	

	/*!
	*	\brief	벡터의 좌표를 설정한다.
	*
	*	\param	x[in]	설정할 x 좌표
	*	\param	y[in]	설정할 y 좌표
	*	\param	z[in]	설정할 z 좌표
	*	\param	w[in]	설정할 w 좌표
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec4 &Set(double x, double y, double z, double w);

	/*!
	*	\brief	벡터를 단위벡터로 정규화한다.
	*
	*	\return 정규화된 자신을 반환한다.
	*/
	EgVec4 &Normalize();

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]	대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgVec4 &operator =(const EgVec4 &rhs);

	/*!
	*	\brief	벡터를 더한다.
	*
	*	\param	rhs[in]	더할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec4 &operator +=(const EgVec4 &rhs);

	/*!
	*	\brief	벡터를 뺀다.
	*
	*	\param	rhs[in]	뺄 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec4 &operator -=(const EgVec4 &rhs);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec4 &operator *=(const double &s);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec4 &operator /=(const double &s);

	/*!
	*	\brief	+ 단항 연산자
	*
	*	\return 동일부호를 갖는 객체를 반환한다.
	*/
	EgVec4 operator +() const;

	/*!
	*	\brief	- 단항 연산자
	*
	*	\return 반대부호를 갖는 객체를 반환한다.
	*/
	EgVec4 operator -() const;

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in]	인덱스
	*
	*	\return	벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	double &operator [](const int &idx);

	/*!
	*	\brief	상수 객체에 대한 인덱스 연산자([])
	*
	*	\param	idx[in]	인덱스
	*
	*	\return	벡터의 idx번째 원소의 레퍼런스를 반환한다.
	*/
	const double &operator [](const int &idx) const;

	/*!
	*	\brief	두 벡터를 더한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 합을 반환한다.
	*/
	friend EgVec4 operator +(const EgVec4 &v, const EgVec4 &w);

	/*!
	*	\brief	두 벡터를 뺀다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 차를 반환한다.
	*/
	friend EgVec4 operator -(const EgVec4 &v, const EgVec4 &w);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 연산의 결과를 반환한다.
	*/
	friend EgVec4 operator *(const EgVec4 &v, const double &s);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 연산의 결과를 반환한다.
	*/
	friend EgVec4 operator *(const double &s, const EgVec4 &v);

	/*!
	*	\brief	두 벡터의 내적을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 내적의 결과를 반환한다.
	*/
	friend double operator *(const EgVec4 &v, const EgVec4 &w);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 연산의 결과를 반환한다.
	*/
	friend EgVec4 operator /(const EgVec4 &v, const double &s);

	/*!
	*	\brief	두 벡터가 같은지 검사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 같다면 true, 다른면 false를 반환한다.
	*/
	friend bool operator ==(const EgVec4 &v, const EgVec4 &w);

	/*!
	*	\brief	두 벡터가 다른지 검사한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터가 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgVec4 &v, const EgVec4 &w);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	v[in]		출력 벡터
	*
	*	\return 벡터가 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgVec4 &v);

	/*!
	*	\brief	입력 연산자(>>)
	*
	*	\param	is[in]	입력 스트림
	*	\param	v[out]	입력값이 저장될 벡터
	*
	*	\return 입력값이 제거된 입력스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgVec4 &v);
};

/*!
*	\class	EgVec
*	\brief	n차원 벡터를 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgVec
{
public:
	/*! \brief 벡터의 좌표 배열 */
	std::vector<double> m_Coords;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	dim[in]	벡터의 차원
	*/
	EgVec(int dim = 3);

	/*!
	*	\brief	생성자
	*	\note	원소는 모두 실수형으로 전달해야 함
	*	\note	마지막 수정일: 2021-05-30 (va_arg(ap, dim)->va_arg(ap, x))
	*
	*	\param	dim[in]	벡터의 차원
	*	\param	x[in]	벡터의 첫 번째 좌표
	*/
	EgVec(int dim, double x, ...);

	/*!
	*	\brief	생성자
	*	\note	원소는 모두 정수형으로 전달해야 함
	*	\note	마지막 수정일: 2021-05-30 (va_arg(ap, dim)->va_arg(ap, x))
	*
	*	\param	dim[in]		벡터의 차원
	*	\param	x[in]		벡터의 첫 번째 좌표
	*/
	EgVec(int dim, int x, ...);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	copy[in]	복사될 객체
	*/
	EgVec(const EgVec &cpy);

	/*!
	*	\brief	소멸자
	*/
	~EgVec();

	/*!
	*	\brief	벡터의 원소를 설정한다.
	*	\note	매개변수는 실수형으로 주어야 한다. 예) 1: 불가능, 1.0: 가능.
	*
	*	\param	x[in]	첫 번째 좌표
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec &Set(double x, ...);

	/*!
	*	\brief	벡터의 원소를 설정한다.
	*	\note	매개변수는 정수형으로 주어야 한다. 예) 1: 가능, 1.0: 불가능.
	*
	*	\param	x[in]	첫 번째 좌표
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec &Set(int x, ...);

	/*!
	*	\brief	벡터의 원소를 설정한다.
	*
	*	\param	Coords[in]	설정될 좌표 배열
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec &Set(double *Coords);

	/*!
	*	\brief	벡터를 정규화한다.
	*
	*	\return 정규화된 자신을 반환한다.
	*/
	EgVec &Normalize();

	/*!
	*	\brief	벡터를 영벡터로 설정한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgVec &SetZeros();

	/*!
	*	\brief	벡터의 차원을 반환한다.
	*
	*	\return 벡터의 차원을 반환한다.
	*/
	int GetDim() const;

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]	오른쪽 피연산자
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgVec &operator =(const EgVec &rhs);

	/*!
	*	\brief	벡터를 더한다.
	*
	*	\param	rhs[in]	더할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec &operator +=(const EgVec &rhs);

	/*!
	*	\brief	벡터를 뺀다.
	*
	*	\param	rhs[in]	뺄 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec &operator -=(const EgVec &rhs);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec &operator *=(const double &s);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgVec &operator /=(const double &s);

	/*!
	*	\brief	+ 단항 연산자
	*
	*	\return 동일부호 객체를 반환한다.
	*/
	EgVec operator +() const;

	/*!
	*	\brief	- 단항 연산자
	*
	*	\return 반대부호 객체를 반환한다.
	*/
	EgVec operator -() const;

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in]	인덱스
	*
	*	\return 벡터의 idx 번째 원소의 레퍼런스를 반환한다.
	*/
	double &operator [](const int &idx);

	/*!
	*	\brief	상수 객체의 인덱스 연산자([])
	*
	*	\param	idx[in]	인덱스
	*
	*	\return 벡터의 idx 번째 원소의 레퍼런스를 반환한다.
	*/
	const double &operator [](const int &idx) const;

	/*!
	*	\brief	두 벡터를 더한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 합을 반환한다.
	*/
	friend EgVec operator +(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터를 뺀다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 차를 반환한다.
	*/
	friend EgVec operator -(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터의 내적을 구한다.
	*
	*	\param	v[in]	첫 번째 벡터
	*	\param	w[in]	두 번째 벡터
	*
	*	\return 두 벡터의 내적값을 반환한다.
	*/
	friend double operator *(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec operator *(const EgVec &v, const double &s);

	/*!
	*	\brief	벡터를 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	v[in]	벡터
	*
	*	\return 벡터의 상수배를 반환한다.
	*/
	friend EgVec operator *(const double &s, const EgVec &v);

	/*!
	*	\brief	벡터를 상수로 나눈다.
	*
	*	\param	v[in]	벡터
	*	\param	s[in]	상수
	*
	*	\return 연산의 결과를 반환한다.
	*/
	friend EgVec operator /(const EgVec &v, const double &s);

	/*!
	*	\brief	두 벡터의 크기를 비교한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 왼쪽 벡터의 크기가 오른쪽 벡터보다 크면 true, 아니면 false를 반환한다.
	*/
	friend bool operator >(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터의 크기를 비교한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 왼쪽 벡터의 크기가 오른쪽 벡터보다 크거나 같으면 true, 아니면 false를 반환한다.
	*/
	friend bool operator >=(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터의 크기를 비교한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 왼쪽 벡터의 크기가 오른쪽 벡터보다 작으면 true, 아니면 false를 반환한다.
	*/
	friend bool operator <(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터의 크기를 비교한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 왼쪽 벡터의 크기가 오른쪽 벡터보다 작거나 같으면 true, 아니면 false를 반환한다.
	*/
	friend bool operator <=(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터가 같은지 조사한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 두 벡터가 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	두 벡터가 다른지 조사한다.
	*
	*	\param	v[in]	왼쪽 벡터
	*	\param	w[in]	오른쪽 벡터
	*
	*	\return 두 벡터가 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgVec &v, const EgVec &w);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	v[in]		출력할 벡터
	*
	*	\return 벡터가 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgVec &v);

	/*!
	*	\brief	입력 연산자(>>)
	*
	*	\param	is[in]	입력 스트림
	*	\param	v[out]	입력값이 저장될 벡터
	*
	*	\return 입력값이 제거된 입력스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgVec &v);
};

/*!
*	\class	EgPos
*	\brief	3차원 위치(position)를 나타내는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgPos
{
public:
	/*! \brief 3차원 좌표 배열 */
	double m_Coords[3];

public:
	/*!
	*	\brief	생성자
	*
	*	\param	x[in]	x 좌표
	*	\param	y[in]	y 좌표
	*	\param	z[in]	z 좌표
	*/
	EgPos(double x = 0.0, double y = 0.0, double z = 0.0);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in] 복사될 객체
	*
	*	\return 복사된 자신을 반환한다.
	*/
	EgPos(const EgPos &cpy);

	/*!
	*	\brief  소멸자
	*/
	~EgPos();

	/*!
	*	\brief	포인트의 좌표를 설정한다.
	*
	*	\param	x[in] x 좌표
	*	\param	y[in] y 좌표
	*	\param	z[in] z 좌표
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgPos &Set(double x, double y, double z);

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		오른쪽 피연산자
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgPos &operator =(const EgPos &rhs);

	/*!
	*	\brief	벡터를 더한다.
	*
	*	\param	v[in]	더할 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgPos &operator +=(const EgVec3 &v);

	/*!
	*	\brief	벡터를 뺀다.
	*
	*	\param	v[in]	뺄 벡터
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgPos &operator -=(const EgVec3 &v);

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in] 인덱스
	*
	*	\return 포인트의 idx 번째 원소의 레퍼런스를 반환한다.
	*/
	double &operator [](const int &idx);

	/*!
	*	\brief	상수 객체의 인덱스 연산자([])
	*
	*	\param	idx[in] 인덱스
	*
	*	\return 포인트의 idx 번째 원소의 레퍼런스를 반환한다.
	*/
	const double &operator [](const int &idx) const;

	/*!
	*	\brief	두 위치의 차이 벡터를 구한다.
	*
	*	\param	p[in]	첫 번째 위치
	*	\param	q[in]	두 번째 위치
	*
	*	\return q에서 p로 향하는 벡터를 반환한다.
	*/
	friend EgVec3 operator -(const EgPos &p, const EgPos &q);

	/*!
	*	\brief	위치에서 벡터를 뺀다.
	*
	*	\param	p[in]	위치
	*	\param	v[in]	벡터
	*
	*	\return 새로운 위치를 반환한다.
	*/
	friend EgPos operator -(const EgPos &p, const EgVec3 &v);

	/*!
	*	\brief	위치에서 벡터를 더한다.
	*
	*	\param	p[in]	위치
	*	\param	v[in]	벡터
	*
	*	\return 새로운 위치를 반환한다.
	*/
	friend EgPos operator +(const EgPos &p, const EgVec3 &v);

	/*!
	*	\brief	위치에서 벡터를 더한다.
	*
	*	\param	v[in]	벡터
	*	\param	p[in]	위치
	*
	*	\return 새로운 위치를 반환한다.
	*/
	friend EgPos operator +(const EgVec3 &v, const EgPos &p);

	/*!
	*	\brief	두 위치가 같은지 조사한다.
	*
	*	\param	p[in]	첫 번째 위치
	*	\param	q[in]	두 번재 위치
	*
	*	\return 두 위치가 같으면 true, 다르면 false를 반한한다.
	*/
	friend bool operator ==(const EgPos &p, const EgPos &q);

	/*!
	*	\brief	두 위치가 다른지 조사한다.
	*
	*	\param	p[in]	첫 번째 위치
	*	\param	q[in]	두 번재 위치
	*
	*	\return 두 위치가 다르면 true, 같으면 false를 반한한다.
	*/
	friend bool operator !=(const EgPos &p, const EgPos &q);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]		출력 스트림
	*	\param	p[in]		출력할 객체
	*
	*	\return 출력된 스트림 객체를 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgPos &p);

	/*!
	*	\brief	입력 연산자(>>)
	*
	*	\param	is[in]	입력 스트림
	*	\param	v[out]	입력값이 저장될 벡터
	*
	*	\return 입력값이 제거된 입력 스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgPos &p);
};

/*!
*	\class	EgMat
*	\brief	행렬을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgMat
{
public:
	/*! \brief 행렬의 행의 개수 */
	int m_nRow;

	/*! \brief 행렬의 열의 개수 */
	int m_nCol;

	/*! \brief 행렬의 원소를 저장하는 배열 */
	std::vector<double> m_Data;	
	
public:
	/*!
	*	\brief	생성자
	*
	*	\param	r[in]		행의 수
	*	\param	c[in]		열의 수
	*	\param	elem[in]	행렬의 원소 배열
	*/
	EgMat(int r = 4, int c = 4, double *elem = NULL);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgMat(const EgMat &cpy);

	/*!
	*	\brief 소멸자
	*/
	~EgMat();	

	/*!
	*	\brief	행렬을 전치행렬로 변환한다.
	*
	*	\return 변환된 자신을 반환한다.
	*/
	EgMat &SetTranspose();

	/*!
	*	\brief	단위행렬로 변환한다.
	*	\note	정방행렬이 아니면 최대한 단위행렬로 만든다.
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &SetIdentity();

	/*!
	*	\brief	영행렬로 변환한다.
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &SetZeros();

	/*!
	*	\brief	행벡터를 설정한다.
	*
	*	\param	idx[in]		설정할 행의 인덱스
	*	\param	v[in]		설정할 벡터
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &SetRowVec(const int idx, const EgVec &v);

	/*!
	*	\brief	열벡터를 설정한다.
	*
	*	\param	idx[in]		설정할 열의 인덱스
	*	\param	v[in]		설정할 벡터
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &SetColVec(const int idx, const EgVec &v);

	/*!
	*	\brief	두 행을 교환한다.
	*
	*	\param	idx0[in]	교환할 행의 인덱스
	*	\param	idx1[in]	교환할 행의 인덱스
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &ExchangeRows(const int idx0, const int idx1);

	/*!
	*	\brief	두 열을 교환한다.
	*
	*	\param	idx0[in]	교환할 열의 인덱스
	*	\param	idx1[in]	교환할 열의 인덱스
	*
	*	\return 변환된 자신을 리턴한다.
	*/
	EgMat &ExchangeCols(const int idx0, const int idx1);

	/*!
	*	\brief	행벡터를 반환한다.
	*
	*	\param	idx[in]		행의 인덱스
	*
	*	\return idx 번째 행벡터를 반환한다.
	*/
	EgVec GetRowVec(const int idx) const;

	/*!
	*	\brief	열벡터를 반환한다.
	*
	*	\param	idx[in]		열의 인덱스
	*
	*	\return idx 번째 열벡터를 반환한다.
	*/
	EgVec GetColVec(const int idx) const;

	/*!
	*	\brief	행의 수를 반환한다.
	*
	*	\return 행의 수를 반환한다.
	*/
	int	GetRowNum() const;

	/*!
	*	\brief	열의 수를 반환한다.
	*
	*	\return 열의 수를 반환한다.
	*/
	int GetColNum() const;

	/*!
	*	\brief	정방행렬 여부를 조사한다.
	*
	*	\return 정방행렬의 경우 true, 직사각행렬의 경우 false를 반환한다.
	*/
	bool IsSquare() const;

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in] 대입될 행렬 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgMat &operator =(const EgMat &rhs);

	/*!
	*	\brief	행렬을 더한다.
	*
	*	\param	rhs[in]	더할 행렬
	*
	*	\return 더해진 자신을 반환한다.
	*/
	EgMat &operator +=(const EgMat &rhs);

	/*!
	*	\brief	행렬을 뺀다.
	*
	*	\param	rhs[in]	뺄 행렬
	*
	*	\return 연산후 대입된 자신을 반환한다.
	*/
	EgMat &operator -=(const EgMat &rhs);

	/*!
	*	\brief	행렬을 곱한다.
	*
	*	\param	rhs[in]	곱할 행렬
	*
	*	\return 곱해진 자신을 반환한다.
	*/
	EgMat &operator *=(const EgMat &rhs);

	/*!
	*	\brief	행렬을 상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgMat &operator *=(const double &s);

	/*!
	*	\brief	행렬을 상수로 나눈다.
	*
	*	\param	s[in]	상수
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgMat &operator /=(const double &s);

	/*!
	*	\brief	+ 단항 연산자
	*
	*	\return 동일부호를 갖는 객체를 반환한다.
	*/
	EgMat operator +() const;

	/*!
	*	\brief	- 단항 연산자
	*
	*	\return 반대부호의 갖는 객체를 반환한다.
	*/
	EgMat operator -() const;

	/*!
	*	\brief	인덱스 연산자([])
	*
	*	\param	idx[in]		행의 인덱스
	*
	*	\return idx 행의 배열의 시작 주소를 반환한다.
	*/
	double *operator [](const int idx);

	/*!
	*	\brief	상수객체의 인덱스 연산자([])
	*
	*	\param	idx[in]		행의 인덱스
	*
	*	\return idx 행의 배열의 시작 주소를 반환한다.
	*/
	const double *operator [](const int idx) const;

	/*!
	*	\brief	두 행렬을 더한다.
	*
	*	\param	A[in]	첫 번째 행렬
	*	\param	B[in]	두 번째 행렬
	*
	*	\return 두 행렬의 합을 반환한다.
	*/
	friend EgMat operator +(const EgMat &A, const EgMat &B);

	/*!
	*	\brief	두 행렬을 뺀다.
	*
	*	\param	A[in]	첫 번째 행렬
	*	\param	B[in]	두 번째 행렬
	*
	*	\return 두 행렬의 차를 반환한다.
	*/
	friend EgMat operator -(const EgMat &A, const EgMat &B);

	/*!
	*	\brief	두 행렬을 곱한다.
	*
	*	\param	A[in]	첫 번째 행렬
	*	\param	B[in]	두 번째 행렬
	*
	*	\return 두 행렬의 곱을 반환한다.
	*/
	friend EgMat operator *(const EgMat &A, const EgMat &B);

	/*!
	*	\brief	행렬을 상수배 한다.
	*
	*	\param	M[in]	행렬
	*	\param	s[in]	상수
	*
	*	\return 행렬의 상수배를 반환한다.
	*/
	friend EgMat operator *(const EgMat &M, const double &s);

	/*!
	*	\brief	행렬을 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	M[in]	행렬
	*
	*	\return 행렬의 상수배를 반환한다.
	*/
	friend EgMat operator *(const double &s, const EgMat &M);

	/*!
	*	\brief	행렬과 벡터의 곱을 구한다.
	*
	*	\param	M[in]	행렬
	*	\param	v[in]	벡터
	*
	*	\return 행렬과 벡터의 곱(벡터)를 반환한다.
	*/
	friend EgVec operator *(const EgMat &M, const EgVec &v);

	/*!
	*	\brief	벡터와 행렬을 곱한다.
	*
	*	\param	v[in]	n by 1 벡터
	*	\param	M[in]	1 by m 행렬
	*
	*	\return 벡터와 행렬의 곱(행렬)을 반환한다.
	*/
	friend EgMat operator *(const EgVec &v, const EgMat &M);

	/*!
	*	\brief	행렬을 상수로 나눈다.
	*
	*	\param	M[in]	행렬
	*	\param	s[in]	상수
	*
	*	\return 계산의 결과를 반환한다.
	*/
	friend EgMat operator /(const EgMat &A, const double &s);

	/*!
	*	\brief	두 행렬을 같은지 검사한다.
	*
	*	\param	A[in]	왼쪽 행렬
	*	\param	B[in]	오른쪽 행렬
	*
	*	\return 두 행렬이 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgMat &A, const EgMat &B);

	/*!
	*	\brief	두 행렬이 다른지 검사한다.
	*
	*	\param	A[in]	왼쪽 피연산자
	*	\param	B[in]	오른쪽 피연산자
	*
	*	\return 두 행렬이 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgMat &A, const EgMat &B);

	/*!
	*	\brief	출력 연산자(<<)
	*
	*	\param	os[out]	출력 스트림
	*	\param	M[in]	출력할 행렬
	*
	*	\return 출력된 스트림 객체를 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgMat &m);
};

/*!
*	\class	EgQuat
*	\brief	쿼터니온 (q = W + iX + jY + kZ)을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
enum TypeEuler
{
	EULER_XYZ = 0,
	EULER_ZYX = 1,
};
enum TypeArcBall
{
	ARCBALL_FREE = 0,
	ARCBALL_X,
	ARCBALL_Y,
	ARCBALL_Z
};
class EgQuat
{
public:
	/*! \brief 쿼터니온의 실수부 */
	double m_W;

	/*! \brief 쿼터니온의 i 허수부 */
	double m_X;

	/*! \brief 쿼터니온의 j 허수부 */
	double m_Y;

	/*! \brief 쿼터니온의 k 허수부 */
	double m_Z;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	w[in]	실수부
	*	\param	x[in]	i 허수부
	*	\param	y[in]	j 허수부
	*	\param	z[in]	k 허수부
	*/
	EgQuat(double w = 1.0, double x = 0.0, double y = 0.0, double z = 0.0);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]	복사될 객체
	*/
	EgQuat(const EgQuat &cpy);

	/*!
	*	\brief	생성자
	*
	*	\param	q[in]	생성될 쿼터니온의 원소를 저장한 배열
	*/
	EgQuat(const double *q);

	/*!
	*	\brief	회전축를 중심으로 회전하는 단위쿼터니온을 생성한다.
	*
	*	\param	axis[in]	회전축
	*	\param	theta[in]	회전각도
	*	\param	radian[in]	회적각도가 라디안이면 true, 아니면 false
	*/
	EgQuat(EgVec3 axis, double theta, bool radian = false);

	/*!
	*	\brief	오일러 각(degree) 이용하여 쿼터니온을 생성한다.
	*
	*	\param	theta1[in]		첫 번째축에 대한 회전각도(degree)
	*	\param	theta2[in]		두 번째축에 대한 회전각도(degree)
	*	\param	theta3[in]		세 번째축에 대한 회전각도(degree)
	*	\param	eulerType[in]	오일러 축 타입(XYZ = RxRyRz, ZYX = RzRyRx, ...)
	*/
	EgQuat(double theta1, double theta2, double theta3, TypeEuler eulerType = EULER_XYZ);

	/*!
	*	\brief	생성자
	*
	*	\param	axis0[in]		첫 번째 축 벡터
	*	\param	axis1[in]		두 번째 축 벡터
	*	\param	axis_type[in]	입력 축 벡터의 순서(0: xy축, 1: yz축, 2: zx축)
	*/
	EgQuat(EgVec3 axis0, EgVec3 axis1, int axis_type);

	/*!
	*	\brief	소멸자
	*/
	~EgQuat();

	/*!
	*	\brief	실수부와 허수부의 값을 설정한다.
	*
	*	\param	w[in]	쿼터니온의 실수부
	*	\param	x[in]	쿼터니온의 i 허수부
	*	\param	y[in]	쿼터니온의 j 허수부
	*	\param	z[in]	쿼터니온의 k 허수부
	*
	*	\return	설정된 자신을 반환한다.
	*/
	EgQuat &Set(double w, double x, double y, double z);

	/*!
	*	\brief	실수부와 허수부의 값을 설정한다.
	*
	*	\param	q[in]			설정될 값의 배열
	*	\param	invOrder[in]	true: (w, x, y, z) = (q[3], q[0], q[1], q[2]), false: (w, x, y, z) = (q[0], q[1], q[2], q[3])
	*
	*	\return	설정된 자신을 반환한다.
	*/
	EgQuat &Set(double *q, bool invOrder = false);

	/*!
	*	\brief	회전축을 중심으로 입력각도 만큼 회전하는 쿼터니온을 설정한다.
	*
	*	\param	theta[in]	입력각도
	*	\param	axis[in]	회전축
	*	\param	radian[in]	입력각도가 라디안이면 true, 아니면 false
	*
	*	\return 설정된 자신을 리턴한다.
	*/
	EgQuat &SetFromAngleAxis(const double theta, EgVec3 axis, bool radian = false);

	/*!
	*	\brief	아크볼 위의 점 p를 점 q로 회전하는 쿼터니온을 설정한다.
	*
	*	\param	p[in]		아크볼 위의 점
	*	\param	q[in]		아크볼 위의 점
	*	\param	arcType[in]	아크볼의 타입
	*
	*	\return 설정된 자신을 리턴한다.
	*/
	EgQuat &SetFromArcBall(EgVec3 p, EgVec3 q, TypeArcBall arcType = ARCBALL_FREE);

	/*!
	*	\brief	오일러 각(degree) 이용하여 쿼터니온을 설정한다.
	*
	*	\param	theta1[in]		첫 번째축에 대한 회전각도(degree)
	*	\param	theta2[in]		두 번째축에 대한 회전각도(degree)
	*	\param	theta3[in]		세 번째축에 대한 회전각도(degree)
	*	\param	eulerType[in]	오일러축(XYZ = RxRyRz, ZYX = RzRyRx)
	*
	*	\return	설정된 자신을 반환한다.
	*/
	EgQuat &SetFromEulerAngle(double theta1, double theta2, double theta3, TypeEuler eulerType = EULER_XYZ);

	/*!
	*	\brief	좌표계의 두 축으로 쿼터니온을 설정한다.
	*
	*	\param	x_axis[in]	좌표계의 x 축
	*	\param	y_axis[in]	좌표계의 y 축
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetFromFrameXY(const EgVec3 &x_axis, const EgVec3 &y_axis);

	/*!
	*	\brief	좌표계의 두 축으로 쿼터니온을 설정한다.
	*
	*	\param	y_axis[in]	좌표계의 y 축
	*	\param	z_axis[in]	좌표계의 z 축
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetFromFrameYZ(const EgVec3 &y_axis, const EgVec3 &z_axis);

	/*!
	*	\brief	좌표계의 두 축으로 쿼터니온을 설정한다.
	*
	*	\param	z_axis[in]	좌표계의 z 축
	*	\param	x_axis[in]	좌표계의 x 축
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetFromFrameZX(const EgVec3 &z_axis, const EgVec3 &x_axis);

	/*!
	*	\brief	회전 행렬로 쿼터니온을 설정한다.
	*
	*	\param	mat[in]		4 by 4 변환행렬을 표현하는 배열
	*	\parma	isGL[in]	OpenGL의 변환행렬이면 true, 아니면 false
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetFromMatrix(double *mat, bool isGL);

	/*!
	*	\brief	쿼터니온을 항등원으로 설정한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetIdentity();

	/*!
	*	\brief	쿼터니온을 역원으로 설정한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetInverse();

	/*!
	*	\brief	쿼터니온을 conjugate 한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetConjugate();

	/*!
	*	\brief	쿼터니온을 negate 한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &SetNegate();

	/*!
	*	\brief	쿼터니온을 단위 쿼터니온으로 설정한다.
	*
	*	\return 설정된 자신을 반환한다.
	*/
	EgQuat &Normalize();

	/*!
	*	\brief	단위 회전축과 회전각을 구한다.
	*
	*	\param	axis[out]	단위 회전축이 저장됨
	*	\param	angle[out]	회전각이 저장됨
	*	\param	radian[in]	회전각을 라디안으로 구하려면 true, 아니면 false
	*/
	void	GetAngleAxis(EgVec3 &axis, double &angle, bool radian = false) const;

	/*!
	*	\brief	회전의 오일러 표현을 구한다.
	*
	*	\param	theta1[out]		첫 번째 회전축의 각도가 저장됨
	*	\param	theta2[out]		두 번째 회전축의 각도가 저장됨
	*	\param	theta3[out]		세 번째 회전축의 각도가 저장됨
	*	\param	radian[in]		저장되는 회전각이 라디안이면 true, 아니면 false
	*	\param	eulerType[in]	회전축의 순서(EULER_XYZ 또는 EULER_ZYX)
	*/
	void	GetEulerAngle(double &theta1, double &theta2, double &theta3, bool radian = false, TypeEuler eulerType = EULER_XYZ);

	/*!
	*	\brief	단위 쿼터니온 여부를 판정한다.
	*
	*	\return 단위 쿼터니온이면 true 아니면 false를 반환한다.
	*/
	bool	IsUnitQuater() const;

	/*!
	*	\brief	현재 쿼터니온이 항등원인지 여부를 판정한다.
	*
	*	\return 항등원이면 true, 아니면 false를 반환한다.
	*/
	bool	IsIdentity() const;

	/*!
	*	\brief	쿼터니온의 W 성분을 반환한다.
	*
	*	\return 쿼터니온의 W 성분을 반환한다.
	*/
	double	W() const;

	/*!
	*	\brief	쿼터니온의 X 성분을 반환한다.
	*
	*	\return 쿼터니온의 X 성분을 반환한다.
	*/
	double	X() const;

	/*!
	*	\brief	쿼터니온의 Y 성분을 반환한다.
	*
	*	\return 쿼터니온의 Y 성분을 반환한다.
	*/
	double	Y() const;

	/*!
	*	\brief	쿼터니온의 Z 성분을 반환한다.
	*
	*	\return 쿼터니온의 Z 성분을 반환한다.
	*/
	double	Z() const;	

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgQuat &operator =(const EgQuat &rhs);

	/*!
	*	\brief	쿼터니온을 더한다.
	*
	*	\param	rhs[in]		더할 객체
	*
	*	\return 연산후 대입된 자신을 반환한다.
	*/
	EgQuat &operator +=(const EgQuat &rhs);

	/*!
	*	\brief	쿼터니온을 뺀다.
	*
	*	\param	rhs[in]		뺄 객체
	*
	*	\return 연산후 대입된 자신을 반환한다.
	*/
	EgQuat &operator -=(const EgQuat &rhs);

	/*!
	*	\brief	쿼터니온을 곱한다.
	*
	*	\param	rhs[in]		곱할 객체
	*
	*	\return	곱해진 자신을 반환한다.
	*/
	EgQuat &operator *=(const EgQuat &rhs);

	/*!
	*	\brief	상수배 한다.
	*
	*	\param	s[in]	상수
	*
	*	\return 상수배 된 자신을 반환한다.
	*/
	EgQuat &operator *=(const double s);

	/*!
	*	\brief	상수로 나눈다.
	*
	*	\param	s[in]	상수
	*
	*	\return 상수로 나뉘어진 자신을 반환한다.
	*/
	EgQuat &operator /=(const double s);

	/*!
	*	\brief	+ 단항 연산자
	*
	*	\return 동일 부호의 객체를 반환한다.
	*/
	EgQuat operator +() const;

	/*!
	*	\brief	- 단항 연산자
	*
	*	\return 반대 부호의 객체를 반환한다.
	*/
	EgQuat operator -() const;

	/*!
	*	\brief	두 쿼터니온을 더한다.
	*
	*	\param	q1[in]	첫 번째 쿼터니온
	*	\param	q2[in]	두 번째 쿼터니온
	*
	*	\return 두 쿼터니온의 합을 반환한다.
	*/
	friend EgQuat operator +(const EgQuat &q1, const EgQuat &q2);

	/*!
	*	\brief	두 쿼터니온의 차를 구한다.
	*
	*	\param	q1[in]	첫 번째 쿼터니온
	*	\param	q2[in]	두 번째 쿼터니온
	*
	*	\return 두 쿼터니온의 차를 반환한다.
	*/
	friend EgQuat operator -(const EgQuat &q1, const EgQuat &q2);

	/*!
	*	\brief	두 쿼터니온을 곱한다.
	*
	*	\param	q1[in]	첫 번째 쿼터니온
	*	\param	q2[in]	두 번째 쿼터니온
	*
	*	\return 두 쿼터니온의 곱을 반환한다.
	*/
	friend EgQuat operator *(const EgQuat &q1, const EgQuat &q2);

	/*!
	*	\brief	회전된 벡터를 계산한다
	*	\note	현재 쿼터니온은 단위쿼터니온이어야 함
	*
	*	\param	q[in]	쿼터니온
	*	\param	v[in]	회전시킬 벡터
	*
	*	\return 회전된 벡터를 반환한다.
	*/
	friend EgPos operator *(const EgQuat &q, const EgPos &p);

	/*!
	*	\brief	회전된 점의 위치를 계산한다
	*	\note	현재 쿼터니온은 단위쿼터니온이어야 함
	*
	*	\param	q[in]	쿼터니온
	*	\param	p[in]	회전시킬 점의 위치
	*
	*	\return 회전된 벡터를 반환한다.
	*/
	friend EgVec3 operator *(const EgQuat &q, const EgVec3 &v);

	/*!
	*	\brief	쿼터니온을 상수배 한다.
	*
	*	\param	q[in]	쿼터니온
	*	\param	s[in]	상수
	*
	*	\return 쿼터니온의 상수배를 반환한다.
	*/
	friend EgQuat operator *(const EgQuat &q, const double &s);

	/*!
	*	\brief	쿼터니온을 상수배 한다.
	*
	*	\param	s[in]	상수
	*	\param	q[in]	쿼터니온
	*
	*	\return 쿼터니온의 상수배를 반환한다.
	*/
	friend EgQuat operator *(const double &s, const EgQuat &q);

	/*!
	*	\brief	쿼터니온을 상수로 나눈다.
	*
	*	\param	q[in]	쿼터니온
	*	\param	s[in]	상수
	*
	*	\return 나눈 결과를 반환한다.
	*/
	friend EgQuat operator /(const EgQuat &q1, const double s);

	/*!
	*	\brief	등호연산자(==)
	*
	*	\param	q1[in]	왼쪽 피연산자
	*	\param	q2[in]	오른편 피연산자
	*
	*	\return 두 쿼터니온이 같으면 true, 다르면 false 반환한다.
	*/
	friend bool operator ==(const EgQuat &q1, const EgQuat &q2);

	/*!
	*	\brief	부등호연산자(!=)
	*
	*	\param	q1[in]	왼쪽 피연산자
	*	\param	q2[in]	오른편 피연산자
	*
	*	\return 두 쿼터니온이 다르면 true, 같으면 false 반환한다.
	*/
	friend bool operator !=(const EgQuat &q1, const EgQuat &q2);

	/*!
	*	\brief	출력 연산자
	*
	*	\param	os[out]		출력 스트림
	*	\param	q[in]		출력할 쿼터니온
	*
	*	\return 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgQuat &q);

	/*!
	*	\brief	입력 연산자
	*
	*	\param	is[in]	입력 스트림
	*	\param	q[out]	입력받을 쿼터니온
	*
	*	\return 입력된 스트림을 반환한다.
	*/
	friend std::istream &operator >>(std::istream &is, EgQuat &q);
};

/*!
*	\class	EgLine
*	\brief	3차원 공간의 직선을 나타내는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgLine
{
public:
	/*! \brief 직선 위의 한 점 */
	EgPos m_Pos;

	/*! \brief 직선의 방향 벡터 l(t) = m_Pos + m_Dir * t */
	EgVec3 m_Dir;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	Pos[in]		직선 위의 한 점
	*	\param	Dir[in]		직선의 방향 벡터(단위 벡터일 필요 없음)
	*/
	EgLine(EgPos p = EgPos(0, 0, 0), EgVec3 v = EgVec3(0, 0, 0));

	/*!
	*	\brief	두 점을 지나는 직선을 생성하는 생성자
	*
	*	\param	p[in]	직선 위의 점, l(0) = p
	*	\param	q[in]	직선 위의 점, l(1) = q
	*/
	EgLine(EgPos p, EgPos q);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgLine(EgLine &cpy);

	/*!
	*	\brief 소멸자
	*/
	~EgLine();	

	/*!
	*	\brief	직선 위의 점을 계산한다.
	*
	*	\param	t[in]	매개변수
	*
	*	\return 직선 위의 점 l(t)를 반환한다.
	*/
	EgPos Eval(double t);

	/*!
	*	\brief	점 q가 직선 위의 점인지 조사한다.
	*
	*	\param	q[in]	조사할 점
	*
	*	\return 점 q가 직선 위의 점이면 true, 아니면 false를 반환한다.
	*/
	bool IsOnLine(EgPos &q);	

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입할 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgLine &operator =(const EgLine &rhs);

	/*!
	*	\brief	두 직선이 같은지 조사한다.
	*
	*	\param	lhs[in]		왼쪽 직선
	*	\param	rhs[in]		오른쪽 직선
	*
	*	\return 동일한 직선이면 true, 아니면 false를 반환한다.
	*/
	friend bool operator ==(EgLine &lhs, EgLine &rhs);

	/*!
	*	\brief	두 직선이 다른지 조사한다.
	*
	*	\param	lhs[in]		왼쪽 직선
	*	\param	rhs[in]		오른쪽 직선
	*
	*	\return 다른 직선이면 true, 아니면 false를 반환한다.
	*/
	friend bool operator !=(EgLine &lhs, EgLine &rhs);

	/*!
	*	\brief	출력 연산자
	*
	*	\param	os[out]		출력 스트림
	*	\param	l[in]		출력할 객체
	*
	*	\return 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgLine &l);
};

/*!
*	\class	EgPlane
*	\brief	평면을 표현하는 클래스
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	01 Jan 2001
*/
class EgPlane
{
public:
	/*! \brief 평면의 방정식(ax + by + cz + d = 0)을 4차원 동차좌표로 표현 (a, b, c, d) */
	EgVec4 m_Coords;

public:
	/*!
	*	\brief	생성자
	*/
	EgPlane();

	/*!
	*	\brief	생성자
	*
	*	\param	n[in]	평면의 법선벡터
	*	\param	p[in]	평면 위의 한 점
	*/
	EgPlane(EgVec3 n, EgPos p);

	/*!
	*	\brief	세 점 p1, p2, p3 를 지나는 평면의 생성자
	*
	*	\param	p1[in]	평면 위의 첫 번째 점
	*	\param	p2[in]	평면 위의 두 번째 점
	*	\param	p3[in]	평면 위의 세 번째 점
	*/
	EgPlane(const EgPos &p1, const EgPos &p2, const EgPos &p3);

	/*!
	*	\brief	생성자
	*
	*	\param	a[in]	평면의 방정식의 계수
	*	\param	b[in]	평면의 방정식의 계수
	*	\param	c[in]	평면의 방정식의 계수
	*	\param	d[in]	평면의 방정식의 계수
	*/
	EgPlane(double a, double b, double c, double d);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgPlane(const EgPlane &cpy);

	/*!
	*	\brief 소멸자
	*/
	~EgPlane();

	/*!
	*	\brief	평면의 함수값을 계산한다.
	*
	*	\param	p[in]	조사할 좌표(x, y, z)
	*
	*	\return 함수값 f(x, y, z) = ax + by + cz + d를 반환한다.
	*/
	double Eval(EgPos p);

	/*!
	*	\brief	평면의 법벡터를 반환한다.
	*
	*	\param	bNormalize[in]	정규화 여부
	*
	*	\return 평면의 법벡터를 반환한다.
	*/
	EgVec3 N(bool bNormalize = false);

	/*!
	*	\brief	평면의 방정식(ax + by + cz + d = 0)의 상수 d를 반환한다.
	*
	*	\return 평면의 방정식(ax + by + cz + d = 0)의 상수 d를 반환한다.
	*/
	double d();

	/*!
	*	\brief	법선 방향을 y 축으로 하는 임의의 회전을 반환한다.
	*
	*	\return 법선 방향을 y 축으로 하는 임의의 회전을 반환한다.
	*/
	EgQuat Rot();

	/*!
	*	\brief	점 p가 평면에 놓인 점 인지를 조사한다.
	*
	*	\param	p[in]		조사할 점
	*	\param	eps[in]		오차의 허용 범위
	*
	*	\return 점 p가 평면에 놓인 점이면 true, 아니면 false를 반환한다.
	*/
	bool IsOnPlane(const EgPos &p, double eps = 1.0e-14);

	/*!
	*	\brief	점 p가 평면의 위쪽 점인지를 조사한다.
	*
	*	\param	p[in]		조사할 점
	*	\param	eps[in]		오차의 허용 범위
	*
	*	\return 점 p가 평면의 위쪽 점 일경우 true, 아니면 false를 반환한다.
	*/
	bool IsAbovePlane(const EgPos &p, double eps = 1.0e-14);

	/*!
	*	\brief	점 p가 평면의 아래쪽 점인지를 조사한다.
	*
	*	\param	p[in]		조사할 점
	*	\param	eps[in]		오차의 허용 범위
	*
	*	\return 점 p가 평면의 아래쪽 점 일경우 true, 아니면 false를 반환한다.
	*/
	bool IsBelowPlane(const EgPos &p, double eps = 1.0e-14);

	/*!
	*	\brief	법선이 반대인 평면을 반환한다.
	*
	*	\return 법선이 반대인 평면을 반환한다.
	*/
	EgPlane GetReversePlane();

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return 대입된 자신을 반환한다.
	*/
	EgPlane &operator =(const EgPlane &rhs);

	/*!
	*	\brief	두 평면이 같은지 조사한다.
	*
	*	\param	lhs[in]		첫 번째 평면
	*	\param	rhs[in]		두 번째 평면
	*
	*	\return 두 평면이 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgPlane &lhs, const EgPlane &rhs);

	/*!
	*	\brief	두 평면이 다른지 조사한다.
	*
	*	\param	lhs[in]		첫 번째 평면
	*	\param	rhs[in]		두 번째 평면
	*
	*	\return 두 평면이 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgPlane &lhs, const EgPlane &rhs);

	/*!
	*	\brief	출력 연산자
	*
	*	\param	os[out]		출력 스트림
	*	\param	pi[in]		출력 평면
	*
	*	\return 출력 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgPlane &pi);
};

/*!
*	\class	EgTrans
*	\brief	강체변환(rigid-body transformation)을 나타내는 클래스.
*
*	\author 윤승현(shyun@dongguk.edu)
*	\date	2001년 1월 1일.
*/
class EgTrans
{
public:
	/*! \brief 3차원 이동변환 */
	EgVec3 m_T;

	/*! \brief 3차원 회전변환 */
	EgQuat m_Q;

public:
	/*!
	*	\brief	생성자
	*
	*	\param	t[in]	이동 정보
	*	\param	q[in]	회전 정보
	*/
	EgTrans(const EgVec3 &t = EgVec3(0.0, 0.0, 0.0), const EgQuat &q = EgQuat(1.0, 0.0, 0.0, 0.0));

	/*!
	*	\brief	생성자
	*
	*	\param	mat[in]		변환 행렬(4 X 4)
	*	\param	isGL[in]	변환 행렬의 OpenGL 형태(row major) 여부
	*/
	EgTrans(double *mat, bool isGL);

	/*!
	*	\brief	복사 생성자
	*
	*	\param	cpy[in]		복사될 객체
	*/
	EgTrans(const EgTrans &cpy);

	/*!
	*	\brief 소멸자
	*/
	~EgTrans();

	/*!
	*	\brief	회전을 negate한다.
	*/
	void SetNegate();

	/*!
	*	\brief	이동 변환을 설정한다.
	*
	*	\param	t[in] 설정될 이동 변환
	*/
	void SetTrans(const EgVec3 &t);

	/*!
	*	\brief	회전 변환을 설정한다.
	*
	*	\param	q[in] 설정될 회전 변환
	*/
	void SetRot(const EgQuat &q);

	/*!
	*	\brief	대입 연산자
	*
	*	\param	rhs[in]		대입될 객체
	*
	*	\return 변경된 자신을 반환한다.
	*/
	EgTrans &operator =(const EgTrans &rhs);

	/*!
	*	\brief	변환을 곱한다.
	*
	*	\param	rhs[in]		곱해질 변환
	*
	*	\return 곱해진 자신을 반환한다.
	*/
	EgTrans &operator *=(const EgTrans &rhs);

	/*!
	*	\brief	두 변환을 곱한다.
	*
	*	\param	X1[in]	첫 번째 변환
	*	\param	X2[in]	두 번째 변환
	*
	*	\return 곱한 결과를 반환한다.
	*/
	friend EgTrans operator *(const EgTrans &X1, const EgTrans &X2);

	/*!
	*	\brief	변환된 점을 구한다.
	*
	*	\param	X[in]	변환 객체
	*	\param	p[in]	대상 점
	*
	*	\return 이전 좌표계에서 표현된 점 p의 좌표를 반환한다.
	*/
	friend EgPos operator *(const EgTrans &X, const EgPos &p);

	/*!
	*	\brief	변환된 벡터를 구한다.
	*
	*	\param	X[in]	변환 객체
	*	\param	v[in]	대상 벡터
	*
	*	\return 이전 좌표계에서 표현된 벡터 v의 좌표를 반환한다.
	*/
	friend EgVec3 operator *(const EgTrans &X, const EgVec3 &v);

	/*!
	*	\brief	변환된 직선을 구한다.
	*
	*	\param	X[in]	변환 객체
	*	\param	l[in]	대상 직선
	*
	*	\return 이전 좌표계에서 표현된 직선 l의 표현을 반환한다.
	*/
	friend EgLine operator *(const EgTrans &X, const EgLine &l);

	/*!
	*	\brief	변환된 평면을 구한다.
	*
	*	\param	X[in]	변환 객체
	*	\param	pi[in]	대상 평면
	*
	*	\return 이전 좌표계에서 표현된 평면 pi을 반환한다.
	*/
	friend EgPlane operator *(EgTrans &X, EgPlane &pi);

	/*!
	*	\brief	두 변환이 같은지 조사한다.
	*
	*	\param	X1[in]	첫 번째 변환
	*	\param	X2[in]	두 번째 변환
	*
	*	\return 두 변환이 같으면 true, 다르면 false를 반환한다.
	*/
	friend bool operator ==(const EgTrans &X1, const EgTrans &X2);

	/*!
	*	\brief	두 변환이 다른지 조사한다.
	*
	*	\param	X1[in]	첫 번째 변환
	*	\param	X2[in]	두 번째 변환
	*
	*	\return 두 변환이 다르면 true, 같으면 false를 반환한다.
	*/
	friend bool operator !=(const EgTrans &X1, const EgTrans &X2);

	/*!
	*	\brief	출력 연산자
	*
	*	\param	os[out]		출력 스트림
	*	\param	X[in]		출력 변환
	*
	*	\return 출력된 스트림을 반환한다.
	*/
	friend std::ostream &operator <<(std::ostream &os, const EgTrans &X);
};


