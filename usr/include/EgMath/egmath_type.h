#pragma once

#define MTYPE_EPS	1.0e-6
//#define MTYPE_EPS	1.0e-15

// 매크로 상수
#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.78539816339744830961

// 매크로 정의
#define SQRT(X)		sqrt((X))

#define SQR(X)		((X) * (X))

#define DEG2RAD(X)	((X) * (M_PI) / (180.0))

#define RAD2DEG(X)	((X) * (180.0) / (M_PI))

#define SWAP(type, x, y) { type temp = (x); (x) = (y); (y) = temp; }

#define MIN(x, y)	((x) > (y) ? (y) : (x))

#define MAX(x, y)	((x) > (y) ? (x) : (y))

#define ABS(X)		(((X) > 0.0) ? (X) : (-(X)))

#define SIGN(a)		((a) > 0.0 ? (1.0) : (-1.0))

#define SIGN1(a, b) ((b) > 0.0 ? ABS(a) : -ABS(a))

#define SIGN2(a, b)	((b) >= 0.0 ? fabs(a) : -fabs(a))

#define PYTHAG(a, b) SQRT((SQR(a) + SQR(b)))

#define EQ(X, Y, EPS)	(ABS((X) - (Y)) < EPS)

#define EQ_ZERO(X, EPS) (ABS(X) < EPS)

#define ARR_ZERO(A, N) memset((A), 0, sizeof(A[0]) * (N))

#define ARR_COPY(D, S, N) memmove((D), (S), sizeof(S[0]) * (N))

#define ARR_COPY_2D(D, S, M, N) \
	for (int i = 0; i < (M); ARR_COPY(D[i], S[i], N), ++i);

#define ARR_ALLOC(D, TYPE, N) D = new TYPE [(N)]

#define ARR_ALLOC_2D(D, TYPE, M, N) \
	D = new TYPE *[(M)]; \
	for (int i = 0; i < (M); D[i] = new TYPE [(N)], ++i);

#define ARR_FREE(D) \
	delete [] D; \
	D = NULL

#define ARR_FREE_2D(D, M) \
	for (int i = 0; i < (M); delete [] D[i], ++i); \
	delete [] D; \
	D = NULL

#define UNIQUE(S) \
	sort(S.begin(), S.end()); \
	S.erase(unique(S.begin(), S.end()), S.end())