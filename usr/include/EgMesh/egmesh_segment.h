#pragma once

class EgVertex;
class EgFace;
class EgMesh;

/*!
*	\brief	메쉬에서 concave한 정점을 찾는다.
*
*	\param	pMesh[in] 대상 메쉬
*	\param	Verts[out] concave한 정점이 저장된다.
*
*	\return concave한 정점의 개수를 반환한다.
*/
int get_concave_verts(EgMesh *pMesh, std::vector<EgVertex *> &Verts);

/*!
*	\brief	메쉬에서 concave한 삼각형을 찾는다.
*
*	\param	pMesh[in] 대상 메쉬
*	\param	Faces[out] concave한 삼각형이 저장된다.
*
*	\return concave한 삼각형의 수를 반환한다.
*/
int get_concave_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces);

/*!
*	\brief	메쉬의 제약 정점으로 하모닉 필드를 구성한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	OneVerts[in]	제약값 1을 갖는 정점의 리스트
*	\param	HalfVerts[in]	제약값 0.5을 갖는 정점의 리스트
*	\param	ZeroVerts[in]	제약값 0을 갖는 정점의 리스트
*	\param	Field[out]		i번째 정점의 하모닉 필드값이 Field[i]에 저장된다.
*	\param	bBndryCstr[in]	경계 정점의 자동 제약 조건(0.5) 사용 여부
*	\param	FieldType[in]	하모닉 필드의 타입(0: 부드러운 필드, 1: 오목성 기반 필드, 2: 볼록성 기반 필드)
*/
void get_harmonic_field(
	EgMesh *pMesh, 
	std::vector<EgVertex *> &OneVerts, 
	std::vector<EgVertex *> &HalfVerts, 
	std::vector<EgVertex *> &ZeroVerts, 
	std::vector<double> &Field, 
	bool bBndryCstr, 
	int FieldType);

/*!
*	\brief	Dot scissor용 feature-aware 하모닉 필드를 구성한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	OneVert[in]		조건 1값을 갖는 제약 정점
*	\param	ZeroVert[in]	조건 0값을 갖는 제약 정점
*	\param	Field[out]		i번째 정점의 하모닉 필드값이 Field[i]에 저장된다.
*	\param	bConcavity[in]	오목성 기반 필드인 경우 true, 볼록성 기반 필드인 경우 false
*/
void get_seg_field_by_dot_scissor(
	EgMesh *pMesh, 
	EgVertex *OneVert, 
	EgVertex *ZeroVert, 
	std::vector<double> &Field, 
	bool bConcavity = true);

/*!
*	\brief	Dot scissor 툴을 이용하여 메쉬의 특징 영역의 분할 경계선을 생성한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	PtsOnCircle[in]		DotCircle위의 8개의 점
*	\param	SltFaces[out]		분할 경계선의 내부 또는 교차하는 삼각형이 저장된다.
*	\param	SegBndryPts[out]	분할 경계선과 에지의 교차점들이 저장된다.
*	\param	KeyPts[out]			분할 경계선의 대표점들이 저장된다(측지선 생성용)
*	\param	bConcavity[in]		오목성 기반일 경우 true, 볼록성 기반일 경우 false
*/
void get_seg_bndry_by_dot_scissor(
	EgMesh *pMesh, 
	std::vector<EgMeshPt> PtsOnCircle, 
	std::vector<EgFace *> &SltFaces, 
	std::vector<std::vector<EgPos>> &SegBndryPts, 
	std::vector<std::vector<EgMeshPt>> &KeyPts,
	bool bConcavity);

/*!
*	\brief	Magic wand용 feature-aware 하모닉 필드를 구성한다.
*
*	\param	pMesh[in]		대상 메쉬
*	\param	SeedVerts[in]	시드 정점의 리스트
*	\param	RoiRadius[in]	관심 영역의 반경
*	\param	Field[out]		i번째 정점의 하모닉 필드값이 Field[i]에 저장된다.
*	\param	bConcavity[in]	오목성 감지 필드이면 true, 볼록성 감지 필드이면 false
*/
void get_seg_field_by_magic_wand(
	EgMesh *pMesh, 
	std::vector<EgObject *> SeedVerts, 
	double RoiRadius, 
	std::vector<double> &Field,
	bool bConcavity);

/*!
*	\brief	메쉬의 특징 영역의 분할 경계선을 생성한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	SeedVerts[in]		선택을 위한 seed 정점의 리스트
*	\param	RoiRadius[in]		후보 영역을 정의하는 반경
*	\param	SltFaces[out]		분할 경계선의 내부 또는 교차하는 삼각형이 저장된다.
*	\param	SegBndryPts[out]	분할 경계선과 에지의 교차점들이 저장된다.
*	\param	bConcavity[in]		오목성 기반 경계선이면 true, 볼록성 기반 경계선이면 false
*/
void get_seg_bndry_by_magic_wand_basic(
	EgMesh *pMesh,
	std::vector<EgObject *> SeedPts,
	double RoiRadius,
	std::vector<EgFace *> &SltFaces,
	std::vector<std::vector<EgPos>> &SegBndryPts,
	bool bConcavity);

/*!
*	\brief	메쉬의 특징 영역의 분할 경계선을 생성한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	SeedVerts[in]		선택을 위한 seed 정점의 리스트
*	\param	RoiRadius[in]		후보 영역을 정의하는 반경
*	\param	SltFaces[out]		분할 경계선의 내부 또는 교차하는 삼각형이 저장된다.
*	\param	SegBndryPts[out]	분할 경계선과 에지의 교차점들이 저장된다.
*	\param	KeyPts[out]			분할 경계선의 보간점들이 저장된다(측지선 생성용)
*	\param	KeyPtsOpt[in]		보간점 결정 옵션(0: 최대 평균 곡률, 1: 최대 그래디언트 크기)
*	\param	bConcavity[in]		오목성 기반 경계선이면 true, 볼록성 기반 경계선이면 false
*/
void get_seg_bndry_by_magic_wand(
	EgMesh *pMesh, 
	std::vector<EgObject *> SeedPts, 
	double RoiRadius,
	std::vector<EgFace *> &SltFaces, 
	std::vector<std::vector<EgPos>> &SegBndryPts, 
	std::vector<std::vector<EgMeshPt>> &KeyPts,
	int KeyPtOpt,
	bool bConcavity);

/*!
*	\brief	메쉬의 특징 영역의 분할 경계선을 생성한다.
*
*	\param	pMesh[in]			대상 메쉬
*	\param	KeyPts[in]			분할 경계선의 대표점 집합
*	\param	SegBndryPts[out]	대표점을 통과하는 분할 경계선(비등방 측지선)이 저장된다.
*/
void get_seg_bndry_by_aniso_geodesic(
	EgMesh *pMesh, 
	std::vector<std::vector<EgMeshPt>> &KeyPts, 
	std::vector<std::vector<EgPos>> &SegBndryPts);

