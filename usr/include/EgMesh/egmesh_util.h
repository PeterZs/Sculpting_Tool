#pragma once

class EgObject;
class EgVertex;
class EgTexel;
class EgNormal;
class EgEdge;
class EgFace;
class EgMeshPt;
class EgMesh;
class EgMaterial;
class EgBox;

/*!
*	\brief 정수를 문자열로 변환하여 반환한다.
*
*	\param i 문자열로 변환될 정수
*
*	\return 문자열로 변환된 정수
*/
std::string cast_str(int i);

/*!
*	\brief 실수를 문자열로 변환하여 반환한다.
*
*	\param v 문자열로 변환될 실수
*
*	\return 문자열로 변환된 실수
*/
std::string cast_str(double v);

/*!
*	\brief 실수를 문자열로 변환하여 반환한다.
*
*	\param v 문자열로 변환될 실수
*
*	\return 문자열로 변환된 실수
*/
std::string cast_str(float v);

/*!
*	\brief 구간에서 맵핑된 색상 값을 계산한다.
*
*	\param val 맵핑할 값
*	\param min 구간의 시작값
*	\param max 구간의 끝값
*	\param Cmin 시작값의 색상
*	\param Cman 끝값의 색상
*
*	\return 맵핑된 색상을 반환한다.
*/
EgVec3 get_color_map(double val, double min, double max, EgVec3 Cmin, EgVec3 Cmax);

/*!
*	\brief 구간에서 맵핑된 색상 값을 계산한다.
*
*	\param val 맵핑할 값
*	\param min 구간의 시작값
*	\param max 구간의 끝값
*	\param Cmin 시작값의 색상
*	\param Cmin 중간값의 색상
*	\param Cman 끝값의 색상
*
*	\return 맵핑된 색상을 반환한다.
*/
EgVec3 get_color_map(double val, double min, double max, EgVec3 Cmin, EgVec3 Cmid, EgVec3 Cmax);

/*!
*	\brief 무지개 색상에서 보간된 색을 얻는다.
*
*	\param t 색상 파라미터: 0(빨강) <= t <= 1.0(보라)
*
*	\return 보간된 중간 색상을 반환한다.
*/
EgVec3 get_color_map_from_rainbow(double t);

/*!
*	\brief BCGYR 색상에서 보간된 색을 얻는다.
*
*	\param t 색상 파라미터: 0(Blue) <= t <= 1.0(Red)
*
*	\return 보간된 중간 색상을 반환한다.
*/
EgVec3 get_color_map_from_bcgyr(double t);

/*!
*	\brief 임의의 색상을 조합한다.
*
*	\return 임의의 색상을 반환한다.
*/
EgVec3 get_color_random();

/*!
*	\brief 인덱스에 따라 정해진 색상을 반환한다.
*
*	\idx 색상의 인덱스
*
*	\return 인덱스에 따라 정해진 색상을 반환한다.
*/
EgVec3 get_color_sequence(int idx);

/*!
*	\brief	경계(홀)의 길이를 계산한다.
*
*	\param	BndryVerts[in]	경계(홀)을 구성하는 정점의 리스트
*	\param	bClosed[in]		경계 정점의 폐곡선 구성 여부
*
*	\return 계산된 정점의 길이를 반환한다.
*/
double get_hole_perimeter(std::vector<EgVertex *> &BndryVerts, bool bClosed);

/*!
*	\brief	삼각형 기준 입력점의 barycentric 좌표를 계산하는 함수
*
*	\param	P[in]		입력 정점
*	\param	pFace[in]	기준 삼각형
*
	\return	입력 정점의 barycentric 좌표를 반환한다.
*/
EgVec3 get_barycentric_coords(EgPos P, EgFace *pFace);

/*!
*	\brief	메쉬 위에 정의된 스칼라장(scalar field)의 등위선(iso-line) 집합을 구하는 함수
*	\note	마지막 수정일: 2020-11-22
*	\note	등위선 위의 선분은 연결되지 않음
*
*	\param	pMesh[in]			스칼라장이 정의된 메쉬
*	\param	Field[in]			메쉬 위의 스칼라장(i번째 정점의 값 SF[i]에 저장됨)
*	\param	Min[in]				조사할 스칼라장의 최소값
*	\param	Max[in]				조사할 스칼라장의 최대값
*	\param	NumLines[in]		추출할 등위선의 수
*	\param	Isolines[out]		i번째 등위선의 j번째 선분의 양 끝점이 Isolines[i][j], Isolines[i][j+1]에 저장됨 (연결되지 않은 단순 선분 형태, (p, q)-(r, s)...)
*	\param	IsolineCuts[out]	i번째 등위선의 j번째 선분의 양 끝점의 교차 정보가 IsolineCuts[i][j], IsolineCuts[i][j+1]에 저장됨
*/
void get_iso_line_set(
	EgMesh *pMesh, 
	std::vector<double> &Field,
	double Min, 
	double Max, 
	int NumLines, 
	std::vector<std::vector<EgPos>> &Isolines, 
	std::vector<std::vector<EdgeCut>> &IsolineCuts);

/*!
*	\brief	메쉬 위에 정의된 스칼라장(scalar field)에서 하나의 등위선(iso-line)을 구하는 함수
*	\note	마지막 수정일: 2021-02-09
*
*	\param	pMesh[in]		스칼라장이 정의된 메쉬
*	\param	Field[in]		메쉬 위의 스칼라장(i번째 정점의 값 SF[i]에 저장됨)
*	\param	Isovalue[in]	추출할 등위선의 isovalue
*	\param	Isoline[out]	등위선의 i번째 선분의 양 끝점이 IsoLines[i], IsoLines[i+1]에 저장됨
*	\param	CutInfo[out]	등위선의 i번째 선분의 양 끝점의 교차 정보가 CutInfo, CutInfo[i+1]에 저장됨
*/
void get_iso_line_segment(
	EgMesh *pMesh, 
	std::vector<double> &Field,
	double Isovalue, 
	std::vector<EgPos> &Isoline, 
	std::vector<EdgeCut> &IsolineCut);

/*!
*	\brief	메쉬 위에 정의된 스칼라장(scalar field)에서 연결된 등위선(여러개 가능)을 구하는 함수
*	\note	마지막 수정일: 2021-12-31
*
*	\param	pMesh[in]					스칼라장이 정의된 메쉬
*	\param	Field[in]					메쉬 위의 스칼라장(Field[i]에 i번째 정점의 값이 저장됨)
*	\param	Isovalue[in]				추출할 등위선의 isovalue
*	\param	ConnectedIsolines[out]		등위선을 구성하는 점들의 집합: i번째 등위선 위의 점들은 IsoPts[i]에 저장됨(연결된 형태)
*	\param	ConnectedIsolineCuts[out]	등위선을 구성하는 점들의 교차정보 집합: i번째 등위선의 교차 정보는 CutEdges[i]에 저장됨
*/
void get_iso_line_connected(
	EgMesh *pMesh,
	std::vector<double> &Field,
	double Isovalue,
	std::vector<std::vector<EgPos>> &ConnectedIsolines,
	std::vector<std::vector<EdgeCut>> &ConnectedIsolineCuts);

/*!
*	\brief	폴리라인 위의 회전 최소화 틀장을 구한다.
*
*	\param	Pts[in]		폴리라인의 정점의 리스트
*	\param	T0[in]		시작 점에서의 첫 번째 축벡터(접선)
*	\param	R0[in]		시작 점에서의 두 번째 축벡터
*	\param	Ts[out]		각 정점에서의 접선 벡터
*	\param	Rs[out]		각 정점에서의 두 번째 축벡터가 저장된다.
*	\param	Ss[out]		각 정점에서의 세 번째 축벡터가 저장된다.
*/
void get_rotation_minimizing_frame(
	std::vector<EgPos> Pts,
	EgVec3 T0,
	EgVec3 R0,
	std::vector<EgVec3> &Ts,
	std::vector<EgVec3> &Rs,
	std::vector<EgVec3> &Ss);

/*!
*	\brief	K-Mean 클러스터링을 수행한다.
*
*	\param	Points[in]			입력 데이터 리스트
*	\param	K[in]				클러스터의 수
 *	\param	Epochs[in]			반복 회수
*	\param	InitCenter[in]		각 크러스터의 초기 중심
*	\param	ClusterIds[out]		입력 데이터의 클러스터 아이디가 저장된다.
*	\param	Centers[out]		각 클러스터의 중심이 저장된다.
*/
void get_cluster_by_k_mean(
	std::vector<EgVec3> &Points,
	int K,
	int Epochs,
	std::vector<EgVec3> InitCenter,
	std::vector<int> &ClusterIds,
	std::vector<EgVec3> &Centers);

/*!
*	\brief	K-Mean 클러스터링을 수행한다.
*
*	\param	Points[in]			입력 데이터 리스트
*	\param	K[in]				클러스터의 수
 *	\param	Epochs[in]			반복 회수
*	\param	InitCenter[in]		각 크러스터의 초기 중심
*	\param	ClusterIds[out]		입력 데이터의 클러스터 아이디가 저장된다.
*	\param	Centers[out]		각 클러스터의 중심이 저장된다.
*/
void get_cluster_by_k_mean(
	std::vector<double> &Points,
	int K,
	int Epochs,
	std::vector<double> InitCenter,
	std::vector<int> &ClusterIds,
	std::vector<double> &Centers);
