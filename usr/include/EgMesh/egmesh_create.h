#pragma once

class EgVertex;
class EgTexel;
class EgNormal;
class EgTexture;
class EgMaterial;
class EgMesh;

/*!
*	\biref	메쉬 객체를 생성한다.
*
*	\param	MeshName[in] 생성할 메쉬 객체의 이름
*
*	\return 생성된 메쉬의 포인터를 반환한다.
*/
EgMesh *create_mesh(std::string MeshName);

/*!
*	\biref	메쉬 정점을 생성한다.
*
*	\param	x[in] 정점의 x 좌표
*	\param	y[in] 정점의 y 좌표
*	\param	z[in] 정점의 z 좌표
*
*	\return 생성된 정점의 포인터를 반환한다.
*/
EgVertex *create_vertex(double x, double y, double z);

/*!
*	\biref	메쉬 정점을 생성한다.
*
*	\param	pt[in]	정점의 좌표
*
*	\return 생성된 정점의 포인터를 반환한다.
*/
EgVertex *create_vertex(EgPos pt);

/*!
*	\biref	텍스처 좌표를 생성한다.
*
*	\param	s[in] 텍스처 s 좌표
*	\param	t[in] 텍스처 t 좌표
*
*	\return 생성된 텍스처 좌표의 포인터를 반환한다.
*/
EgTexel *create_texel(double s, double t);

/*!
*	\biref	메쉬 법선을 생성한다.
*
*	\param	nx[in] 법선의 x 좌표
*	\param	ny[in] 법선의 y 좌표
*	\param	nz[in] 법선의 z 좌표
*
*	\return 생성된 법선의 포인터를 반환한다.
*/
EgNormal *create_normal(double nx, double ny, double nz);

/*!
*	\brief	메쉬 삼각형을 생성한다.
*
*	\param	v0[in]			삼각형의 첫 번째 정점
*	\param	v1[in]			삼각형의 두 번째 정점
*	\param	v2[in]			삼각형의 세 번째 정점
*	\param	pMtl[in]		삼각형이 사용하는 재질에 대한 포인터
*	\param	GroupName[in]	삼각형이 속한 그룹의 이름
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgMaterial *pMtl = NULL, std::string GroupName = "");

/*!
*	\brief	메쉬 삼각형을 생성한다.
*
*	\param	v0[in]			삼각형의 첫 번째 정점
*	\param	v1[in]			삼각형의 두 번째 정점
*	\param	v2[in]			삼각형의 세 번째 정점
*	\param	t0[in]			삼각형의 첫 번째 정점의 텍셀
*	\param	t1[in]			삼각형의 두 번째 정점의 텍셀
*	\param	t2[in]			삼각형의 세 번째 정점의 텍셀
*	\param	pMtl[in]		삼각형이 사용하는 재질에 대한 포인터
*	\param	GroupName[in]	삼각형이 속한 그룹의 이름
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2, EgMaterial *pMtl, std::string GroupName = "");

/*!
*	\brief	메쉬 삼각형을 생성한다.
*
*	\param	v0[in]			삼각형의 첫 번째 정점
*	\param	v1[in]			삼각형의 두 번째 정점
*	\param	v2[in]			삼각형의 세 번째 정점
*	\param	t0[in]			삼각형의 첫 번째 정점의 텍셀
*	\param	t1[in]			삼각형의 두 번째 정점의 텍셀
*	\param	t2[in]			삼각형의 세 번째 정점의 텍셀
*	\param	n0[in]			삼각형의 첫 번째 정점의 법선
*	\param	n1[in]			삼각형의 두 번째 정점의 법선
*	\param	n2[in]			삼각형의 세 번째 정점의 법선
*	\param	pMtl[in]		삼각형이 사용하는 재질에 대한 포인터
*	\param	GroupName[in]	삼각형이 속한 그룹의 이름
*/
EgFace *create_face(EgVertex *v0, EgVertex *v1, EgVertex *v2, EgTexel *t0, EgTexel *t1, EgTexel *t2, EgNormal *n0, EgNormal *n1, EgNormal *n2, EgMaterial *pMtl, std::string GroupName = "");

/*!
*	\biref	메쉬 재질을 생성한다.
*
*	\param	mtl_name[in] 생성할 재질의 이름
*	\param	ar[in] 주변광 red 반사계수
*	\param	ag[in] 주변광 green 반사계수
*	\param	ab[in] 주변광 blue 반사계수
*	\param	dr[in] 난반사 red 반사계수
*	\param	dg[in] 난반사 green 반사계수
*	\param	db[in] 난반사 blue 반사계수
*	\param	sr[in] 전반사 red 반사계수
*	\param	sg[in] 전반사 green 반사계수
*	\param	sb[in] 전반사 blue 반사계수
*	\param	ns[in] 전반사 지수
*
*	\return 생성된 재질의 포인터를 반환한다.
*/
EgMaterial *create_material(std::string mtl_name, float ar, float ag, float ab, float dr, float dg, float db, float sr, float sg, float sb, float ns);

/*!
*	\biref	메쉬 재질을 생성한다.
*
*	\param	mtl_name[in]	생성할 재질의 이름
*	\param	r[in]			난반사 red 반사계수
*	\param	g[in]			난반사 green 반사계수
*	\param	b[in]			난반사 blue 반사계수
*	\param	ns[in]			전반사 지수
*
*	\return 생성된 재질의 포인터를 반환한다.
*/
EgMaterial *create_material(std::string mtl_name, float r, float g, float b, float ns);

/*!
*	\brief	임의의 재질을 생성한다.
*
*	\return 생성된 재질의 포인터를 반환한다.
*/
EgMaterial *create_material_random();

/*!
*	\biref	2D 텍스처를 생성한다.
*
*	\param	file_name[in] 텍스처 파일의 이름
*
*	\return 생성된 테스처의 포인터를 반환한다.
*/
EgTexture *create_texture(std::string file_name);

/*!
*	\biref	경계 정점을 채우는 초기 메쉬를 생성한다.
*	\note	concave 경계에 수정 필요(2021-02-12)
*
*	\param	Verts[in] 경계 정점의 리스트
*
*	\return 생성된 메쉬를 반환한다.
*/
EgMesh *create_mesh_from_bndry_verts(std::vector<EgVertex *> &Verts);

/*!
*	\biref	다수의 메쉬를 병합하여 새로운 메쉬를 생성한다.
*	\note	기하정보만 병합되고 재질과 텍스처 정보를 병합되지 않는다.
*
*	\param	MeshList[in] 병합할 메쉬리스트
*
*	\return 생성된 메쉬를 반환한다.
*/
EgMesh *create_mesh_by_merging(std::vector<EgMesh *> &MeshList);

/*!
*	\brief	선택된 삼각형으로 부분 메쉬를 생성한다.
*
*	\param	pMesh[in]	선택된 삼각형이 포함된 메쉬
*	\param	Faces[in]	선택된 삼각형 리스트
*	\param	bCalcNormal 메쉬 생성후 법선 계산 여부
*
*	\return 생성된 메쉬를 반환한다.
*/
EgMesh *create_mesh_from_slt_faces(EgMesh *pMesh, const std::vector<EgFace *> &Faces, bool bCalcNormal = true);

/*!
*	\brief	선택된 삼각형으로 부분 메쉬를 생성한다.
*	\note   속도 최적화 및 대응관계 생성을 위한 재구현
*
*	@param	pMesh[in]			선택된 삼각형이 포함된 메쉬
*	@param	Faces[in]			선택된 삼각형 리스트
*	@param	bCalcNormal[in]		메쉬 생성후 법선 계산 여부
*	@param	VertVertPairs[out]	정점간 대응관계(부분 메쉬의 정점, 원래 메쉬의 정점)가 저장된다.
*
*	@author 박정호
*
*	@return 생성된 메쉬를 반환한다.
*/
EgMesh *create_mesh_from_slt_faces(EgMesh *pMesh, std::vector<EgFace *> &Faces, bool bCalcNormal, std::unordered_map<EgVertex *, EgVertex *> &VertVertPairs);

/*!
*	\brief	폴리라인으로 정의되는 실린더 메쉬를 생성한다.
*
*	\param	TraPts[in]		폴리라인 정점의 리스트
*	\param	Radius[in]		실린더 반경
*	\param	Samples[in]		실린더 단면의 샘플링 수
*	\param	bTrim[in]		자기 교차의 트리밍 여부
*
*	\return	생성된 실린더 메쉬를 반환한다.
*/
EgMesh *create_mesh_cylinder(std::vector<EgPos> TraPts, double Radius, int Samples, bool bTrim);


