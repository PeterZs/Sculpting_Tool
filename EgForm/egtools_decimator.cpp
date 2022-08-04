#include "egtools_decimator.h"

extern void normalize_uv(double &u, double &v);
//{
//	u = (u > 1.0) ? (u - (int)(u)) : u;
//	u = (u < 0.0) ? (u - (int)(u - 1.0)) : u;
//
//	v = (v > 1.0) ? (v - (int)(v)) : v;
//	v = (v < 0.0) ? (v - (int)(v - 1.0)) : v;
//}

/***************************
EdgeCollapseInfo 클래스 구현
/***************************/
/*!
*	\brief 생성자
*
*	\param pEdge 제거할 에지에 대한 포인터
*	\param Pos 에지 제거 후, 양 끝점의 위치
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos)
{
	m_pEdge = pEdge;
	m_Pos = Pos;
	m_Cost = pEdge->m_Cost;
}

/*!
*	\brief 생성자
*
*	\param pEdge 제거할 에지에 대한 포인터
*	\param Pos 에지 제거 후, 양 끝점의 위치
*	\param UV 에지 제거 후, 양 끝점의 텍스처 좌표
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(EgEdge *pEdge, EgPos Pos, EgVec2 UV)
{
	m_pEdge = pEdge;
	m_Pos = Pos;
	m_UV = UV;
	m_Cost = pEdge->m_Cost;
}

/*!
*	\brief 복사 생성자
*
*	\param cpy 복사될 객체
*/
EgDecimator::EdgeCollapseInfo::EdgeCollapseInfo(const EdgeCollapseInfo &cpy)
{
	m_pEdge = cpy.m_pEdge;
	m_Pos = cpy.m_Pos;
	m_UV = cpy.m_UV;
	m_Cost = cpy.m_Cost;
}

/*!
*	\brief 소멸자
*/
EgDecimator::EdgeCollapseInfo::~EdgeCollapseInfo()
{
}

/*!
*	\brief 대입 연산자
*
*	\param rhs 대입될 객체
*/
EgDecimator::EdgeCollapseInfo &EgDecimator::EdgeCollapseInfo::operator =(const EdgeCollapseInfo &rhs)
{
	m_pEdge = rhs.m_pEdge;
	m_Pos = rhs.m_Pos;
	m_UV = rhs.m_UV;
	m_Cost = rhs.m_Cost;
	return *this;
}

/*!
*	\brief 비교(>) 연산자
*
*	\param lhs 왼쪽 객체
*	\param rhs 오른쪽 객체
*/
bool operator >(const EgDecimator::EdgeCollapseInfo &lhs, const EgDecimator::EdgeCollapseInfo &rhs)
{
	return (lhs.m_Cost > rhs.m_Cost);
}

/**********************
EgDecimator 클래스 구현
/**********************/
/*!
*	\brief 생성자
*
*	\param pMesh 단순화할 대상 메쉬에 대한 포인터
*	\param bTexture 텍스처 단순화 여부
*/
EgDecimator::EgDecimator(EgMesh *pMesh, bool bDecimateTexture)
{
	// 대상 메쉬와 텍스처 적용 여부를 설정한다.
	m_pMesh = pMesh;
	if (!m_pMesh->m_pTexels.empty() && bDecimateTexture)
		m_bTextureDecimate = true;
	else
		m_bTextureDecimate = false;
}

/*!
*	\brief 소멸자
*/
EgDecimator::~EgDecimator()
{
}

/*!
*	\brief 초기화 작업을 수행한다.
*
*	\param CollapseType 에지 제거 옵션
*/
void EgDecimator::Init(TypeCollapse CollapseType)
{
	// 에지 제거 옵션을 설정한다.
	m_CollapseType = CollapseType;

	// 메쉬 정점의 인덱스를 갱신한다.
	int NumVert = m_pMesh->UpdateVertIdx();

	// 텍스처 단순화를 포함 한다면 
	if (m_bTextureDecimate)
	{
		// 텍스처 좌표를 정규화 한다.
		for (EgTexel *t : m_pMesh->m_pTexels)
			::normalize_uv(t->m_UV[0], t->m_UV[1]);

		// 경계 정점의 정보를 초기화 한다.
		InitBndryVertInfo_T(NumVert);

		// 메쉬 정점의 QEM 행렬을 초기화 한다.
		InitVertQEM_T(NumVert);

		// 에지의 제거 비용을 초기화 한다.
		InitCollapseInfo_T();
	}
	else // 기하정보만 단순화 한다면
	{
		// 메쉬 정점의 QEM 행렬을 초기화 한다.
		InitVertQEM(NumVert);

		// 에지의 제거 비용을 초기화 한다.
		InitCollapseInfo();
	}
}

/*!
*	\brief 메쉬의 경계(형상 + 텍스처) 정점 정보를 구한다.
*
*	\param NumVert 메쉬 정점의 개수
*/
void EgDecimator::InitBndryVertInfo_T(int NumVert)
{
	// 경계 정점 정보를 초기화 한다.
	m_BndryVertInfo.clear();
	m_BndryVertInfo.assign(NumVert, false);

	// 메쉬 각각의 정점에 대하여
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// 정점에서 시작하는 첫 번째 에지의 텍셀을 구하여
		EgTexel *pTexel = v->m_pEdges[0]->m_pTexel;

		// 정점에서 시작하는 각각의 에지에 대하여		
		for (EgEdge *e : v->m_pEdges)
		{
			// 경계 에지가 있다면 경계 정점임을 기록한다.
			if (e->m_pMate == NULL)
			{
				m_BndryVertInfo[v->m_Idx] = true;
				break;
			}
			// 텍스처 경계 에지가 있다면 경계 정점임을 기록한다.
			if (e->m_pTexel->m_UV != pTexel->m_UV)
			{
				m_BndryVertInfo[v->m_Idx] = true;
				break;
			}
		}
	}
}

/*!
*	\brief 일반화된 Quatric error 행렬을 구한다.
*
*	\param K 결과가 저장될 6 x 6 행렬
*	\param p 삼각형의 일반화된 정점 벡터
*	\param q 삼각형의 일반화된 정점 벡터
*	\param r 삼각형의 일반화된 정점 벡터
*/
void EgDecimator::GetErrorMatrix_T(EgMat &K, EgVec &p, EgVec &q, EgVec &r)
{
	// 수직한 5차원 벡터 e1, e2 정의한다.
	EgVec e1 = (q - p).Normalize();
	EgVec e2 = ((r - p) - ((r - p) * e1) * e1).Normalize();

	// 행렬 K는 5 x 5 행렬 A와 5차원 벡터 b와 상수 c로 구성된다.
	// K = | A    b |
	//     | b^t  c |

	// 행렬 K의 A부분을 구하고,		
	K[0][0] = 1.0 - e1[0] * e1[0] - e2[0] * e2[0];
	K[0][1] = -e1[0] * e1[1] - e2[0] * e2[1];
	K[0][2] = -e1[0] * e1[2] - e2[0] * e2[2];
	K[0][3] = -e1[0] * e1[3] - e2[0] * e2[3];
	K[0][4] = -e1[0] * e1[4] - e2[0] * e2[4];

	K[1][0] = K[0][1];
	K[1][1] = 1.0 - e1[1] * e1[1] - e2[1] * e2[1];
	K[1][2] = -e1[1] * e1[2] - e2[1] * e2[2];
	K[1][3] = -e1[1] * e1[3] - e2[1] * e2[3];
	K[1][4] = -e1[1] * e1[4] - e2[1] * e2[4];

	K[2][0] = K[0][2];
	K[2][1] = K[1][2];
	K[2][2] = 1.0 - e1[2] * e1[2] - e2[2] * e2[2];
	K[2][3] = -e1[2] * e1[3] - e2[2] * e2[3];
	K[2][4] = -e1[2] * e1[4] - e2[2] * e2[4];

	K[3][0] = K[0][3];
	K[3][1] = K[1][3];
	K[3][2] = K[2][3];
	K[3][3] = 1.0 - e1[3] * e1[3] - e2[3] * e2[3];
	K[3][4] = -e1[3] * e1[4] - e2[3] * e2[4];

	K[4][0] = K[0][4];
	K[4][1] = K[1][4];
	K[4][2] = K[2][4];
	K[4][3] = K[3][4];
	K[4][4] = 1.0 - e1[4] * e1[4] - e2[4] * e2[4];

	// 벡터 b를 구하고,
	EgVec b = (p * e1) * e1 + (p * e2) * e2 - p;
	K[5][0] = K[0][5] = b[0];
	K[5][1] = K[1][5] = b[1];
	K[5][2] = K[2][5] = b[2];
	K[5][3] = K[3][5] = b[3];
	K[5][4] = K[4][5] = b[4];

	// 상수 c를 계산한다.
	K[5][5] = p * p - SQR(p * e1) - SQR(p * e2);
}

/*!
*	\brief 메쉬 정점에서 정의되는 QEM 행렬을 초기화 한다.
*
*	\param NumVert 메쉬 정점의 개수
*/
void EgDecimator::InitVertQEM_T(int NumVert)
{
	// QEM 리스트를 초기화 한다.
	m_QEM.clear();
	m_QEM.assign(NumVert, EgMat(6, 6));

	// 각각의 삼각형에 대하여
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		// 5차원의 세 점 p, q, r 정의한다.
		EgVertex *v0 = f->GetVertex(0);
		EgVertex *v1 = f->GetVertex(1);
		EgVertex *v2 = f->GetVertex(2);
		EgTexel *t0 = f->GetTexel(0);
		EgTexel *t1 = f->GetTexel(1);
		EgTexel *t2 = f->GetTexel(2);
		EgVec p(5, v0->m_Pos[0], v0->m_Pos[1], v0->m_Pos[2], t0->m_UV[0], t0->m_UV[1]);
		EgVec q(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
		EgVec r(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

		// 텍스처 좌표를 포함한 Quadric error 행렬을 구한다.
		EgMat K(6, 6);
		GetErrorMatrix_T(K, p, q, r);

		// 삼각형의 세 정점의 QEM에 누적한다.
		m_QEM[f->GetVertex(0)->m_Idx] += K;
		m_QEM[f->GetVertex(1)->m_Idx] += K;
		m_QEM[f->GetVertex(2)->m_Idx] += K;
	}
}

/*!
*	\brief 메쉬의 각각의 에지를 제거하는 비용을 초기화 한다.
*	\note 에지 (vi, vk)와 (vk, vi)는 동일한 에지로 판단하여 대표 에지에 대해서만 비용을 구한다.
*/
void EgDecimator::InitCollapseInfo_T()
{
	// 각각의 정점에 대하여
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// 정점에서 시작하는 각각의 에지에 대하여
		for (EgEdge *e : v->m_pEdges)
		{
			// 대표 에지(경계 에지 또는 먼저 방문된 에지)라면
			if (e->m_pMate == NULL || e->m_pMate->m_Cost == 0.0)
			{
				// 에지의 양끝 정점과 텍스처 정점을 구한다.
				EgVertex *v1 = v;
				EgVertex *v2 = EV(e);
				EgTexel *t1 = e->m_pTexel;
				EgTexel *t2 = e->m_pNext->m_pTexel;

				// 에지의 양끝점(position + texture coord)을 구하여,
				EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
				EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

				// 새로운 정점의 6x6 QEM을 구한다.
				EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

				// 새로운 정점의 5차원 벡터 (position + texture coord)를 구한다.
				EgVec x(5), b(5), y(6);
				b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

				// 6x6 K 행렬의 부분행렬 A를 구하여 새로운 정점을 계산한다.
				EgMat A = sub(Q, 0, 0, 4, 4);

				// 에지 제거 옵션에 따라 위치와 비용을 계산한다.
				if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
				{
					y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
					double cost1 = y * (Q * y);
					y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? vt1 : vt2;
					e->m_Cost = MIN(cost1, cost2);
					//x = (vt1 + vt2) * 0.5;
					//normalize_uv(x[3], x[4]);
					//y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
					//e->m_Cost = y * (Q * y);
					//printf("Texture boundary cost = %3.10lf\n", e->m_Cost);
				}
				else if (m_CollapseType == COLLAPSE_OPT_POS)
				{
					if (EQ_ZERO(det(A), 1.0e-7))
					{
						x = (vt1 + vt2) * 0.5;
						normalize_uv(x[3], x[4]);
						y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
						e->m_Cost = y * (Q * y);
						//printf("Singular cost = %3.10lf\n", e->m_Cost);
					}
					else
					{
						x = inv(A) * (-b);
						normalize_uv(x[3], x[4]);
						e->m_Cost = x * b + Q[5][5];
					}
				}
				else if (m_CollapseType == COLLAPSE_MID_POS)
				{
					x = (vt1 + vt2) * 0.5;
					normalize_uv(x[3], x[4]);
					y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
					e->m_Cost = y * (Q * y);
				}
				else // COLLAPSE_END_POS
				{
					y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
					double cost1 = y * (Q * y);
					y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? vt1 : vt2;
					e->m_Cost = MIN(cost1, cost2);
				}

				// 대표 에지 제거 정보를 힙에 추가한다.
				EdgeCollapseInfo info(e, EgPos(x[0], x[1], x[2]), EgVec2(x[3], x[4]));
				m_Heap.push(info);
			}
		}
	}
}

/*!
*	\brief 반복적으로 에지를 제거하여 메쉬 단순화를 수행한다.
*
*	\prarm TarNumVert[in] 목표 정점의 개수
*	\param FileName[out] 제거되는 에지 정보를 기록할 파일명
*/
void EgDecimator::Decimate(int TarNumVert, const char *FileName)
{
	// 목표 정점의 개수가 현재 정점의 개수 보다 크다면 리턴한다.
	int NumVert = m_pMesh->GetNumVert();
	if (TarNumVert >= NumVert)
		return;

	if (m_bTextureDecimate)
		printf("Start decimation with textures...\n");
	else
		printf("Start decimation w/o textures...\n");

	printf("\tMesh name = %s\n", m_pMesh->m_Name.c_str());
	printf("\tTarget number of vertices = %d\n", TarNumVert);
	clock_t st = clock();

	// 제거되는 에지의 순서를 기록할 파일을 생성하고 메쉬의 이름을 출력한다.
	FILE *fp;
	if (FileName != NULL)
	{
		fopen_s(&fp, FileName, "a");
		fprintf_s(fp, "%s\n", m_pMesh->m_Name.c_str());
	}

	// 반복적으로 에지를 제거하여 삼각형의 개수를 줄인다.
	while (!m_Heap.empty())
	{
		// 최소 비용을 갖는 제거 정보를 뽑아서,
		EdgeCollapseInfo Info = m_Heap.top();
		m_Heap.pop();

		// 이미 제거된 에지이거나, 에지 제거 비용이 변경되었다면 스킵한다.
		if (Info.m_pEdge->m_pFace->m_Idx == -1 || Info.m_pEdge->m_Cost != Info.m_Cost)
			continue;

		// 선택된 에지를 제거하고, 삼각형 수를 줄인다.
		int sIdx, eIdx, result;
		if (m_bTextureDecimate)
			result = CollapseEdge_T(Info, sIdx, eIdx);
		else
			result = CollapseEdge(Info, sIdx, eIdx);
		if (result > 0)
		{
			// 정점의 수를 줄이고
			NumVert -= result;

			// 제거되는 에지의 정점 인덱스를 기록한다.
			if (FileName != NULL)
				fprintf_s(fp, "%d\t%d\n", sIdx, eIdx);
		}

		// 삼각형의 개수가 원하는 수에 도달했다면 종료한다.
		if (NumVert <= TarNumVert)
			break;
	}

	// 파일의 기록을 종료한다.
	if (FileName != NULL)
	{
		fprintf_s(fp, "%d\t%d\n", -1, -1);
		fclose(fp);
	}

	// 메쉬의 삼각형 리스트를 갱신한다.
	UpdateFaceList();
	m_pMesh->UpdateNormal();

	// 단순화 정보를 출력한다.
	int NumRmvVert, NumRmvTex, NumRmvNormal;
	DeleteUnusedGeometry(NumRmvVert, NumRmvTex, NumRmvNormal);
	printf("\tElapsed time = %u ms\n", clock() - st);
	printf("\tNumber of vertices = %d\n", m_pMesh->GetNumVert());
	printf("\tNumber of texels = %d\n", m_pMesh->GetNumTexel());
	printf("\tNumber of normals = %d\n", m_pMesh->GetNumNormal());
	printf("\tNumber of faces = %d\n", m_pMesh->GetNumFace());
	printf("\tNumber of removed vertices = %d\n", NumRmvVert);
	printf("\tNumber of removed texels = %d\n", NumRmvTex);
	printf("\tNumber of removed normals = %d\n", NumRmvNormal);
	printf("Decimation completed...\n\n");

	// 경계 상자와 렌더링 버퍼를 초기화 한다.
	m_pMesh->UpdateBndBox();
	m_pMesh->m_VertexBuf.clear();
	m_pMesh->m_NormalBuf.clear();
	m_pMesh->m_TexelBuf.clear();
}

/*!
*	\brief 정해진 순서에 따라 에지 제거를 수행한다.
*
*	\param fname 에지 제거의 순서 정보가 저장된 파일
*/
void EgDecimator::Decimate(const char *fname)
{
	printf("Start decimation from sequence file...\n");
	printf("\tMesh name = %s\n", m_pMesh->m_Name.c_str());
	clock_t st = clock();

	// 파일을 읽기 모드로 오픈한다.
	FILE *fp;
	fopen_s(&fp, fname, "r");
	if (fp == NULL)
	{
		printf("File open failed...\n");
		return;
	}

	// 파일의 포인터를 해당 메쉬의 이름이 나올때까지 이동한다.
	while (true)
	{
		char buffer[256];
		if (fscanf_s(fp, "%s", buffer, 256) == EOF)
		{
			fclose(fp);
			printf("\t%s decimation sequence does not exist...\n", m_pMesh->m_Name.c_str());
			return;
		}
		if (m_pMesh->m_Name == std::string(buffer))
			break;
	}

	// 메쉬 단순화를 수행한다.
	int vidx1, vidx2;
	while (true)
	{
		// 파일에서 제거할 에지의 시작점과 끝점의 인덱스를 읽는다.
		fscanf_s(fp, "%d%d", &vidx1, &vidx2);
		if (vidx1 == -1 && vidx2 == -1)
			break;

		// 에지의 시작점과 끝점을 구하여,
		EgVertex *v1 = m_pMesh->m_pVerts[vidx1];
		EgVertex *v2 = m_pMesh->m_pVerts[vidx2];

		// 해당 에지를 찾는다.
		EgEdge *pEdge = NULL;
		for (EgEdge *e : v1->m_pEdges)
		{
			if (EV(e) == v2)
			{
				pEdge = e;
				break;
			}
		}

		// 텍스처를 단순화 한다면
		if (m_bTextureDecimate)
		{
			// 에지의 양끝 정점과 텍스처 정점을 구한다.
			EgTexel *t1 = pEdge->m_pTexel;
			EgTexel *t2 = pEdge->m_pNext->m_pTexel;

			// 에지의 양끝점(position + texture coord)을 구하여,
			EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
			EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

			// 새로운 정점의 QEM을 구한다.
			EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

			// 새로운 정점의 5차원 벡터 (position + texture coord)를 구한다.
			EgVec x(5), b(5);
			b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

			// 6x6 K 행렬의 부분행렬 A를 구하여 새로운 정점을 계산한다.
			EgMat A = sub(Q, 0, 0, 4, 4);

			// 에지 제거 옵션에 따라 위치를 계산한다.
			switch (m_CollapseType)
			{
			case COLLAPSE_OPT_POS:
				if (EQ_ZERO(det(A), 1.0e-6))
				{
					x = (vt1 + vt2) * 0.5;
					x[3] = vt1[3];
					x[4] = vt1[4];
				}
				else
				{
					x = inv(A) * (-b);
				}
				break;

			case COLLAPSE_MID_POS:
				x = (vt1 + vt2) * 0.5;
				x[3] = vt1[3];
				x[4] = vt1[4];
				break;

			case COLLAPSE_END_POS:
				x = vt1;
				break;
			}

			// 에지를 공유한 삼각형을 제거한다(정점은 남는다).
			std::vector<EgFace *> DelFaces;
			DelFaces.push_back(pEdge->m_pFace);
			if (pEdge->m_pMate != NULL)
				DelFaces.push_back(pEdge->m_pMate->m_pFace);

			// 각각의 삼각형에 대하여
			for (EgFace *f : DelFaces)
			{
				// 삼각형 내의 각각의 에지에 대하여
				for (int i = 0; i < 3; ++i)
				{
					EgEdge *e = f->GetEdge(i);
					e->m_Cost = -1.0;
					// 반대편 에지의 정보를 갱신하고,
					if (e->m_pMate != NULL)
					{
						e->m_pMate->m_pMate = NULL;
						e->m_pMate = NULL;
					}

					// 정점에서 시작하는 에지 리스트에서 현재 에지를 제거한다.
					e->m_pVert->DeleteEdge(e);
				}
			}

			// 에지의 시작점(v1)의 위치를 갱신한다.
			v1->m_Pos.Set(x[0], x[1], x[2]);

			// 에지의 시작점에서 시작하는 모든 에지의 텍스처 좌표를 변경한다.
			normalize_uv(x[3], x[4]);
			for (EgEdge *e : v1->m_pEdges)
				e->m_pTexel->m_UV = EgVec2(x[3], x[4]);

			// v2에서 시작하는 모든 에지들의 시작점을 v1으로 변경한다.
			for (EgEdge *e : v2->m_pEdges)
			{
				e->m_pVert = v1;
				e->m_pTexel = pEdge->m_pTexel;
				v1->m_pEdges.push_back(e);
			}

			// v2에서 시작하는 에지 정보를 제거하고,
			v2->m_pEdges.clear();

			// v1에서 시작하는 에지의 mate 에지의 정보를 갱신한다.
			m_pMesh->UpdateEdgeMate(v1);

			// v1의 QEM 행렬을 갱신한다.
			m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];
		}
		else // 기하정보만 단순화 한다면
		{
			// 새로운 정점의 QEM을 구한다.
			EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

			// 새로운 정점의 위치를 구한다.
			EgVec x(3), b(3);
			b.Set(Q[0][3], Q[1][3], Q[2][3]);
			double det =
				(Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2]) -
				(Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

			// 에지 제거 타입에 따라 위치와 비용을 계산한다.
			switch (m_CollapseType)
			{
			case COLLAPSE_OPT_POS:
				if (EQ_ZERO(det, 1.0e-6))
					x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				else
					x = Inv3(Q, det) * (-b);
				break;

			case COLLAPSE_MID_POS:
				x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				break;

			case COLLAPSE_END_POS:
				x = cast_vec(v1->m_Pos);
				break;
			}

			// 에지를 공유한 삼각형을 제거한다(정점은 남는다).
			std::vector<EgFace *> DelFaces;
			DelFaces.push_back(pEdge->m_pFace);
			if (pEdge->m_pMate != NULL)
				DelFaces.push_back(pEdge->m_pMate->m_pFace);

			// 각각의 삼각형에 대하여
			for (EgFace *f : DelFaces)
			{
				// 삼각형 내의 각각의 에지에 대하여
				for (int i = 0; i < 3; ++i)
				{
					EgEdge *e = f->GetEdge(i);
					e->m_Cost = -1.0;
					// 반대편 에지의 정보를 갱신하고,
					if (e->m_pMate != NULL)
					{
						e->m_pMate->m_pMate = NULL;
						e->m_pMate = NULL;
					}

					// 정점에서 시작하는 에지 리스트에서 현재 에지를 제거한다.
					e->m_pVert->DeleteEdge(e);
				}
			}

			// v1의 정보 변경
			v1->m_Pos = cast_pos(x);

			// v2의 정보 변경
			for (EgEdge *e : v2->m_pEdges)
			{
				e->m_pVert = v1;
				v1->m_pEdges.push_back(e);
			}

			// v2에서 시작하는 에지 정보를 제거하고,
			v2->m_pEdges.clear();

			// v1에서 시작하는 에지의 mate 에지의 정보를 갱신한다.
			m_pMesh->UpdateEdgeMate(v1);

			// v1의 QEM 행렬을 갱신한다.
			m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];
		}
	}

	// 파일 포인터를 닫는다.
	fclose(fp);

	// 메쉬의 삼각형 리스트를 갱신한다.
	UpdateFaceList();
	m_pMesh->UpdateNormal();

	// 단순화 정보를 출력한다.
	int NumRmvVert, NumRmvTex, NumRmvNormal;
	DeleteUnusedGeometry(NumRmvVert, NumRmvTex, NumRmvNormal);
	printf("\tElapsed time = %u ms\n", clock() - st);
	printf("\tNumber of vertices = %d\n", m_pMesh->GetNumVert());
	printf("\tNumber of texels = %d\n", m_pMesh->GetNumTexel());
	printf("\tNumber of normals = %d\n", m_pMesh->GetNumNormal());
	printf("\tNumber of faces = %d\n", m_pMesh->GetNumFace());
	printf("\tNumber of removed vertices = %d\n", NumRmvVert);
	printf("\tNumber of removed texels = %d\n", NumRmvTex);
	printf("\tNumber of removed normals = %d\n", NumRmvNormal);
	printf("Decimation completed...\n\n");

	// 경계 상자와 렌더링 버퍼를 초기화 한다.
	m_pMesh->UpdateBndBox();
	m_pMesh->m_VertexBuf.clear();
	m_pMesh->m_NormalBuf.clear();
	m_pMesh->m_TexelBuf.clear();
}

/*!
*	\brief 에지가 제거 가능한지 검사한다.
*
*	\param pEdge 제거 가능 여부를 조사할 에지에 대한 포인터
*
*	\return 에지가 제거가능할 경우 true, 아니면 false를 반환한다.
*/
bool EgDecimator::IsCollapsible_T(EgEdge *pEdge)
{
	// 에지의 시작점(v1)과 끝점(v2)을 구한다.
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// 에지 끝점이 경계 정점에 포함된다면 false를 반환한다.
	if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
		return false;

	// v1과 v2의 1링 정점의 집합 A와 B를 구한다.
	std::vector<EgVertex *> A, B;
	v1->GetOneRingVert(A);
	v2->GetOneRingVert(B);

	// A와 B의 교집합을 구한다.
	std::vector<EgVertex *> C;
	for (EgVertex *a : A)
	{
		for (EgVertex *b : B)
		{
			if (a == b)
			{
				C.push_back(a);
				break;
			}
		}
	}

	// 에지 제거의 조건을 만족할 경우 true를 반환한다.
	if (pEdge->m_pMate == NULL && C.size() == 1)
		return true;
	if (pEdge->m_pMate != NULL && C.size() == 2)
		return true;

	// 에지 제거 조건을 만족하지 못하는 경우 false를 반환한다.
	return false;
}

/*!
*	\brief 메쉬의 제거 가능한 에지를 제거한다.
*
*	\param info 제거할 에지의 정보
*	\param sIdx 제거할 에지의 시작점의 인덱스가 저장됨
*	\param eIdx 제거할 에지에 끝점의 인텍스가 저장됨
*
*	\return 제거된 정점의 개수를 반환한다(0: 제거 불가능, 1: 제거 가능)
*/
int EgDecimator::CollapseEdge_T(EdgeCollapseInfo &info, int &sIdx, int &eIdx)
{
	// 제거가 불가능한 에지라면 0을 반환한다.
	if (IsCollapsible_T(info.m_pEdge) == false)
		return 0;

	// 제거할 에지, 삼각형, 정점의 포인터를 구하고,	
	EgEdge *pEdge = info.m_pEdge;
	EgEdge *pMateEdge = pEdge->m_pMate;
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// 에지(메이트 에지)를 포함한 삼각형의 제거 정보를 기록한다.
	DeleteIncidentFaces(pEdge);

	// v1의 위치 변경하고
	v1->m_Pos = info.m_Pos;

	// 제거 에지와 텍스처를 공유하는 에지들의 텍스처 좌표를 수정한다.
	pEdge->m_pTexel->m_UV = info.m_UV;

	// v2에서 시작하는 각각의 에지에 대하여
	for (EgEdge *e : v2->m_pEdges)
	{
		// 시작점을 v1으로 변경하고 
		e->m_pVert = v1;

		// 제거 에지와 동일한 텍스처 영역을 공유하는 에지들의 좌표를 수정한다.
		if (e->m_pTexel == pEdge->m_pNext->m_pTexel)
			e->m_pTexel = pEdge->m_pTexel;

		// v1의 시작 에지에 추가한다.
		v1->m_pEdges.push_back(e);
	}

	// v2에서 시작하는 에지 정보를 제거하고,
	v2->m_pEdges.clear();

	// v1에서 시작하는 에지의 mate 에지의 정보를 갱신한다.
	m_pMesh->UpdateEdgeMate(v1);

	// v1의 QEM 행렬을 갱신한다.
	m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];

	// 제거되는 에지의 시작점과 끝점의 인덱스를 저장한다.
	sIdx = v1->m_Idx;
	eIdx = v2->m_Idx;

	// v1을 공유한 삼각형의 모든 에지 비용을 갱신한다.
	UpdateCollapseInfo_T(v1);

	// 제거된 정점의 개수를 반환한다.
	return 1;
}

/*!
*	\brief 정점을 공유한 에지의 제거 비용을 갱신한다.
*
*	\param v 정점에 대한 포인터
*/
void EgDecimator::UpdateCollapseInfo_T(EgVertex *v)
{
	// 정점 v에서 시작하는 각각의 에지에 대하여
	for (EgEdge *e : v->m_pEdges)
	{
		// e의 mate 에지가 대표 에지였다면, e를 대표 에지로 정의한다.
		if (e->m_pMate != NULL && e->m_pMate->m_Cost != 0.0)
			e->m_pMate->m_Cost = 0.0;

		// 대표 에지의 양끝점을 구하고,
		EgVertex *v1 = SV(e);
		EgVertex *v2 = EV(e);
		EgTexel *t1 = e->m_pTexel;
		EgTexel *t2 = e->m_pNext->m_pTexel;

		// 에지의 양끝점(position + texture coord)을 구하여,
		EgVec vt1(5, v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], t1->m_UV[0], t1->m_UV[1]);
		EgVec vt2(5, v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], t2->m_UV[0], t2->m_UV[1]);

		// 새로운 정점의 6x6 QEM을 구한다.
		EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

		// 새로운 정점의 5차원 벡터 (position + texture coord)를 구한다.
		EgVec x(5), b(5), y(6);
		b.Set(Q[0][5], Q[1][5], Q[2][5], Q[3][5], Q[4][5]);

		// 6x6 K 행렬의 부분행렬 A를 구하여 새로운 정점을 계산한다.
		EgMat A = sub(Q, 0, 0, 4, 4);

		// 에지 제거 옵션에 따라 위치와 비용을 계산한다.
		if (m_BndryVertInfo[v1->m_Idx] || m_BndryVertInfo[v2->m_Idx])
		{
			y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
			double cost1 = y * (Q * y);
			y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? vt1 : vt2;
			e->m_Cost = MIN(cost1, cost2);
			//x = (vt1 + vt2) * 0.5;
			//normalize_uv(x[3], x[4]);
			//y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
			//e->m_Cost = y * (Q * y);
			//printf("Updated texture boundary cost = %3.10lf\n", e->m_Cost);
		}
		else if (m_CollapseType == COLLAPSE_OPT_POS)
		{
			if (EQ_ZERO(det(A), 1.0e-7))
			{
				x = (vt1 + vt2) * 0.5;
				normalize_uv(x[3], x[4]);
				y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
				e->m_Cost = y * (Q * y);
				//printf("Singular cost = %3.10lf\n", e->m_Cost);
			}
			else
			{
				x = inv(A) * (-b);
				normalize_uv(x[3], x[4]);
				e->m_Cost = x * b + Q[5][5];
			}
		}
		else if (m_CollapseType == COLLAPSE_MID_POS)
		{
			x = (vt1 + vt2) * 0.5;
			normalize_uv(x[3], x[4]);
			y.Set(x[0], x[1], x[2], x[3], x[4], 1.0);
			e->m_Cost = y * (Q * y);
		}
		else // COLLAPSE_END_POS
		{
			y.Set(vt1[0], vt1[1], vt1[2], vt1[3], vt1[4], 1.0);
			double cost1 = y * (Q * y);
			y.Set(vt2[0], vt2[1], vt2[2], vt2[3], vt2[4], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? vt1 : vt2;
			e->m_Cost = MIN(cost1, cost2);
		}

		// 대표 에지 제거 정보를 힙에 추가한다.
		EdgeCollapseInfo info(e, cast_pos(x), EgVec2(x[3], x[4]));
		m_Heap.push(info);
	}
}

/*!
*	\brief 평면 ax + by + cz + d = 0에서 점 p까지 거리의 제곱을 계산하는 행렬을 구한다.
*
*	\param K 계산된 행렬이 저장된다.
*	\param a 평면의 방정식의 상수
*	\param b 평면의 방정식의 상수
*	\param c 평면의 방정식의 상수
*	\param d 평면의 방정식의 상수
*/
void EgDecimator::GetErrorMatrix(EgMat &K, double a, double b, double c, double d)
{
	K[0][0] = a * a;
	K[0][1] = a * b;
	K[0][2] = a * c;
	K[0][3] = a * d;

	K[1][0] = K[0][1];	// 대칭성
	K[1][1] = b * b;
	K[1][2] = b * c;
	K[1][3] = b * d;

	K[2][0] = K[0][2];	// 대칭성
	K[2][1] = K[1][2];	// 대칭성
	K[2][2] = c * c;
	K[2][3] = c * d;

	K[3][0] = K[0][3];	// 대칭성
	K[3][1] = K[1][3];	// 대칭성
	K[3][2] = K[2][3];	// 대칭성
	K[3][3] = d * d;
}

/*
*	\brief 3행 3열의 대칭 행렬 A의 역행렬을 반환한다.
*
*	\param A 대상 행렬
*	\param det 행렬 A의 행렬식
*
*	\return 행렬 A의 역행렬을 반환한다.
*/
EgMat EgDecimator::Inv3(EgMat &A, double det)
{
	EgMat ret(3, 3);
	ret[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / det;
	ret[0][1] = -(A[0][1] * A[2][2] - A[0][2] * A[2][1]) / det;
	ret[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / det;

	ret[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / det;
	ret[1][2] = -(A[0][0] * A[1][2] - A[0][2] * A[1][0]) / det;

	ret[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / det;

	ret[1][0] = ret[0][1];
	ret[2][0] = ret[0][2];
	ret[2][1] = ret[1][2];

	return ret;
}

/*!
*	\brief 메쉬 정점에서 정의되는 QEM 행렬을 초기화 한다.
*
*	\param NumVert 메쉬 정점의 개수
*/
void EgDecimator::InitVertQEM(int NumVert)
{
	// QEM 리스트를 초기화 한다.
	m_QEM.clear();
	m_QEM.assign(NumVert, EgMat(4, 4));

	// 각각의 삼각형에 대하여
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		// 삼각형을 포함한 평면의 방정식 (ax + by + cz + d = 0)을 구하여
		EgVec3 n = f->GetFaceNormal(false); // n = (a, b, c)
		double d = -n * cast_vec3(f->GetVertex(0)->m_Pos);

		// 삼각형 f에 대한 fundamental error quadric 행렬을 구하고
		EgMat K(4, 4);
		GetErrorMatrix(K, n[0], n[1], n[2], d);

		// 삼각형의 세 정점에 K를 누적한다.
		m_QEM[f->GetVertex(0)->m_Idx] += K;
		m_QEM[f->GetVertex(1)->m_Idx] += K;
		m_QEM[f->GetVertex(2)->m_Idx] += K;

		// 삼각형의 각각의 에지에 대하여
		for (int i = 0; i < 3; ++i)
		{
			// 경계 에지라면,
			if (f->GetEdge(i)->IsBndry())
			{
				// 에지를 지나고 삼각형에 수직한 평면을 구하고, 
				EgEdge *e = f->GetEdge(i);
				EgVec3 ei = (EV(e)->m_Pos - SV(e)->m_Pos).Normalize();
				EgVec3 ni = (n ^ ei).Normalize();
				double di = -ni * cast_vec3(e->m_pVert->m_Pos);

				// 평면으로 정의되는 quadric error 행렬을 구한다.
				EgMat Ki(4, 4);
				GetErrorMatrix(Ki, ni[0], ni[1], ni[2], di);

				// 에지의 양끝점에 더한다.
				Ki *= 100.0;
				m_QEM[e->m_pVert->m_Idx] += Ki;
			}
		}
	}
}

/*!
*	\brief 각각의 에지를 제거하는 초기 비용을 계산한다.
*	\note 에지 (vi, vk)와 (vk, vi)는 동일한 에지로 간주하여 대표 에지에 대해서만 비용을 구한다.
*/
void EgDecimator::InitCollapseInfo()
{
	// 각각의 정점에 대하여
	for (EgVertex *v : m_pMesh->m_pVerts)
	{
		// 정점에서 시작하는 각각의 에지에 대하여
		for (EgEdge *e : v->m_pEdges)
		{
			// 대표 에지(경계에지 또는 최초 방문 에지)라면
			if (e->IsBndry() || e->m_pMate->m_Cost == 0.0)
			{
				// 에지의 양끝점을 구하여,
				EgVertex *v1 = v;
				EgVertex *v2 = EV(e);

				// 새로운 정점의 QEM을 구한다.
				EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];

				// 새로운 정점의 위치를 구한다.
				EgVec x(3), b(3), y(4);
				b.Set(Q[0][3], Q[1][3], Q[2][3]);
				double det = (Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2])
					- (Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

				// 에지 제거 타입에 따라 위치와 비용을 계산한다.
				if (m_CollapseType == COLLAPSE_OPT_POS)
				{
					if (EQ_ZERO(det, 1.0e-6))
					{
						x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
						y.Set(x[0], x[1], x[2], 1.0);
						e->m_Cost = y * (Q * y);
						//printf("Singular cost = %5.10lf\n", e->m_Cost);
					}
					else
					{
						x = Inv3(Q, det) * (-b);
						e->m_Cost = x * b + Q[3][3];
					}
				}
				else if (m_CollapseType == COLLAPSE_MID_POS)
				{
					x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
					y.Set(x[0], x[1], x[2], 1.0);
					e->m_Cost = y * (Q * y);
				}
				else // COLLAPSE_END_POS
				{
					y.Set(v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], 1.0);
					double cost1 = y * (Q * y);
					y.Set(v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], 1.0);
					double cost2 = y * (Q * y);
					x = (cost1 < cost2) ? cast_vec(v1->m_Pos) : cast_vec(v2->m_Pos);
					e->m_Cost = MIN(cost1, cost2);
				}

				// 대표 에지의 제거 정보를 힙에 추가한다.				
				EdgeCollapseInfo info(e, cast_pos(x));
				m_Heap.push(info);
			}
		}
	}
}

/*!
*	\brief 에지가 제거 가능한지 검사한다.
*
*	\param pEdge 제거 가능 여부를 조사할 에지에 대한 포인터
*
*	\return 에지가 제거가능할 경우 true, 아니면 false를 반환한다.
*/
bool EgDecimator::IsCollapsible(EgEdge *pEdge)
{
	// 에지의 시작점(v1)과 끝점(v2)을 구한다.
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// v1과 v2의 1링 정점의 집합 A와 B를 구한다.
	std::vector<EgVertex *> A, B;
	v1->GetOneRingVert(A);
	v2->GetOneRingVert(B);

	// A와 B의 교집합을 구한다.
	std::vector<EgVertex *> C;
	for (EgVertex *a : A)
	{
		for (EgVertex *b : B)
		{
			if (a == b)
			{
				C.push_back(a);
				break;
			}
		}
	}

	// 에지 제거의 조건을 만족할 경우 true를 반환한다.
	if (pEdge->m_pMate == NULL && C.size() == 1)
		return true;
	if (pEdge->m_pMate != NULL && C.size() == 2)
		return true;

	// 에지 제거 조건을 만족하지 못하는 경우 false를 반환한다.
	return false;
}

/*!
*	\brief 메쉬의 제거 가능한 에지를 제거한다.
*
*	\param info 제거할 에지의 정보
*	\param sIdx 제거할 에지의 시작점의 인덱스가 저장됨
*	\param eIdx 제거할 에지에 끝점의 인텍스가 저장됨
*
*	\return 제거된 정점의 개수를 반환한다(0: 제거 불가능, 1: 제거 가능)
*/
int EgDecimator::CollapseEdge(EdgeCollapseInfo &info, int &sIdx, int &eIdx)
{
	// 제거가 불가능한 에지라면 0을 반환한다.
	if (IsCollapsible(info.m_pEdge) == false)
		return 0;

	// 제거할 에지와 정점의 포인터를 구하고
	EgEdge *pEdge = info.m_pEdge;
	EgVertex *v1 = pEdge->m_pVert;
	EgVertex *v2 = pEdge->m_pNext->m_pVert;

	// 에지(메이트 에지)를 포함한 삼각형의 제거 정보를 기록한다.
	DeleteIncidentFaces(pEdge);
	
	// v1의 위치 정보를 변경하고
	v1->m_Pos = info.m_Pos;

	// v2에서 시작하는 각각의 에지에 대하여
	for (EgEdge *e : v2->m_pEdges)
	{
		// 시작점을 v1으로 변경하고 v1의 시작에지에 추가한다.
		e->m_pVert = v1;
		v1->m_pEdges.push_back(e);
	}

	// v2에서 시작하는 에지 정보를 제거하고,
	v2->m_pEdges.clear();

	// v1에서 시작하는 에지의 mate 에지의 정보를 갱신한다.
	m_pMesh->UpdateEdgeMate(v1);

	// v1의 QEM 행렬을 갱신한다.
	m_QEM[v1->m_Idx] += m_QEM[v2->m_Idx];

	// 제거되는 에지의 시작점과 끝점의 인덱스를 저장한다.
	sIdx = v1->m_Idx;
	eIdx = v2->m_Idx;

	// v1을 공유한 삼각형의 모든 에지 비용을 갱신한다.
	UpdateCollapseInfo(v1);

	// 제거된 정점의 개수를 반환한다.
	return 1;
}

/*!
*	\brief 정점을 공유한 에지의 제거 비용을 갱신한다.
*
*	\param v 정점에 대한 포인터
*/
void EgDecimator::UpdateCollapseInfo(EgVertex *v)
{
	// 정점 v에서 시작하는 각각의 에지에 대하여
	for (EgEdge *e : v->m_pEdges)
	{
		// e의 mate 에지가 대표 에지였다면, e를 대표 에지로 정의한다.
		if (e->m_pMate != NULL && e->m_pMate->m_Cost != 0.0)
			e->m_pMate->m_Cost = 0.0;

		// 대표 에지의 양끝점을 구하고,
		EgVertex *v1 = SV(e);
		EgVertex *v2 = EV(e);

		// 새로운점의 QEM 행렬을 구하여,
		EgMat Q = m_QEM[v1->m_Idx] + m_QEM[v2->m_Idx];
		EgVec x(3), b(3), y(4);
		b.Set(Q[0][3], Q[1][3], Q[2][3]);

		// 새로운 위치를 구하고,
		double det =
			(Q[0][0] * Q[1][1] * Q[2][2] + 2 * Q[0][1] * Q[1][2] * Q[0][2]) -
			(Q[1][2] * Q[1][2] * Q[0][0] + Q[0][2] * Q[0][2] * Q[1][1] + Q[0][1] * Q[0][1] * Q[2][2]);

		// 에지 제거 타입에 따라 위치와 비용을 계산한다.
		if (m_CollapseType == COLLAPSE_OPT_POS)
		{
			if (EQ_ZERO(det, 1.0e-6))
			{
				x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
				y.Set(x[0], x[1], x[2], 1.0);
				e->m_Cost = y * (Q * y);
			}
			else
			{
				x = Inv3(Q, det) * (-b);
				e->m_Cost = x * b + Q[3][3];
			}
		}
		else if (m_CollapseType == COLLAPSE_MID_POS)
		{
			x = cast_vec(lerp(v1->m_Pos, v2->m_Pos, 0.5));
			y.Set(x[0], x[1], x[2], 1.0);
			e->m_Cost = y * (Q * y);
		}
		else // COLLAPSE_END_POS
		{
			y.Set(v1->m_Pos[0], v1->m_Pos[1], v1->m_Pos[2], 1.0);
			double cost1 = y * (Q * y);
			y.Set(v2->m_Pos[0], v2->m_Pos[1], v2->m_Pos[2], 1.0);
			double cost2 = y * (Q * y);
			x = (cost1 < cost2) ? cast_vec(v1->m_Pos) : cast_vec(v2->m_Pos);
			e->m_Cost = MIN(cost1, cost2);
		}

		// 대표 에지 제거 정보를 힙에 추가한다.
		EdgeCollapseInfo info(e, cast_pos(x));
		m_Heap.push(info);
	}
}

/*!
*	\brief	에지(메이트 에지)를 포함한 삼각형의 제거 정보를 기록한다.
*	\note	실제로 제거되지는 않고, UpdateFaceList() 기록된 정보를 이용하여 일괄 제거한다.
*
*	\param e 에지에 대한 포인터
*/
void EgDecimator::DeleteIncidentFaces(EgEdge *e)
{
	// 제거할 삼각형을 구하여,
	std::vector<EgFace *> Faces;
	e->GetIncidentFace(Faces);

	// 각각의 삼각형에 대하여,
	for (EgFace *f : Faces)
	{
		for (int i = 0; i < 3; ++i)
		{
			// 각각의 에지에 대하여
			EgEdge *e = f->GetEdge(i);

			// 경계 에지가 아니라면 반대편 에지의 정보를 갱신하고,
			if (!e->IsBndry())
			{
				e->m_pMate->m_pMate = NULL;
				e->m_pMate = NULL;
			}

			// 시작 정점의 에지 집합에서 현재 에지를 제거한다.
			e->m_pVert->DeleteEdge(e);
		}
		// 제거할 삼각형임을 기록한다.
		f->m_Idx = -1;
	}
}

/*!
*	\brief 에지 붕괴 후에 사용되지 않는 정점, 텍셀, 법선을 제거한다
*
*	\param	num_vert 제거된 정점의 수가 저장됨
*	\param	num_tex 제거된 텍셀의 수가 저장됨
*	\param	num_normal 제거된 법선의 수가 저장됨
*/
void EgDecimator::DeleteUnusedGeometry(int &num_vert, int &num_tex, int &num_normal)
{
	num_vert = 0;
	num_tex = 0;
	num_normal = 0;

	// 사용하지 않는 정점을 제거한다.
	if (!m_pMesh->m_pVerts.empty())
	{
		// 모든 정점의 인덱스를 -1로 초기화 한다.
		for (EgVertex *v : m_pMesh->m_pVerts)
			v->m_Idx = -1;

		// 각각의 삼각형마다
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// 에지가 사용하는 정점의 인덱스를 1로 표기한다.
			for (int i = 0; i < 3; ++i)
				f->GetVertex(i)->m_Idx = 1;
		}

		// 사용되는 정점으로 구성될 새로운 리스트를 정의하고,
		std::vector<EgVertex *> NewVerts;

		// 각각의 정점에 대하여
		for (EgVertex *v : m_pMesh->m_pVerts)
		{
			if (v->m_Idx == 1) // 사용된 정점이라면 리스트에 추가하고,
			{
				v->m_Idx = (int)NewVerts.size();
				NewVerts.push_back(v);
			}
			else // 사용되지 않은 정점이라면 제거한다.
			{
				num_vert++;
				delete v;
			}
		}

		// 정점의 리스트를 업데이트 한다.
		m_pMesh->m_pVerts = NewVerts;
	}
		
	// 사용하지 않는 텍셀을 제거한다
	if (!m_pMesh->m_pTexels.empty())
	{
		// 모든 텍셀의 인덱스를 -1로 초기화한다.
		for (EgTexel *t : m_pMesh->m_pTexels)
			t->m_Idx = -1;

		// 각각의 삼각형마다
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// 에지가 사용하는 텍셀의 인덱스를 1로 표기한다.
			for (int i = 0; i < 3; ++i)
				f->GetTexel(i)->m_Idx = 1;
		}

		// 사용되는 텍셀로 구성될 새로운 리스트를 정의하고,
		std::vector<EgTexel *> NewTexels;

		// 각각의 텍셀에 대하여
		for (EgTexel *t : m_pMesh->m_pTexels)
		{
			if (t->m_Idx == 1) // 사용된 텍셀이라면 리스트에 추가하고,
			{
				t->m_Idx = (int)NewTexels.size();
				NewTexels.push_back(t);
			}
			else // 사용되지 않는 텍셀이라면 제거한다.
			{
				num_tex++;
				delete t;
			}
		}

		// 텍셀의 리스트를 업데이트 한다.
		m_pMesh->m_pTexels = NewTexels;
	}

	// 사용하지 않는 법선을 제거한다.
	if (!m_pMesh->m_pNormals.empty())
	{
		// 모든 법선의 인덱스를 -1로 초기화 한다.
		for (EgNormal *n : m_pMesh->m_pNormals)
			n->m_Idx = -1;

		// 각각의 삼각형마다
		for (EgFace *f : m_pMesh->m_pFaces)
		{
			// 에지가 사용하는 법선의 인덱스를 1로 표기한다.
			for (int i = 0; i < 3; ++i)
				f->GetNormal(i)->m_Idx = 1;
		}

		// 사용되는 법선으로 구성될 새로운 리스트를 정의하고,
		std::vector<EgNormal *> NewNormals;

		// 각각의 법선에 대하여
		for (EgNormal *n : m_pMesh->m_pNormals)
		{
			if (n->m_Idx == 1) // 사용된 법선이라면 리스트에 추가하고,
			{
				n->m_Idx = (int)NewNormals.size();
				NewNormals.push_back(n);
			}
			else // 사용되지 않은 법선이라면 제거한다.
			{
				num_normal++;
				delete n;
			}
		}

		// 법선의 리스트를 업데이트 한다.
		m_pMesh->m_pNormals = NewNormals;
	}
}

/*!
*	\brief 단순화 후, 메쉬의 삼각형 리스트를 갱신한다.
*/
void EgDecimator::UpdateFaceList()
{
	// 남은 삼각형으로 구성된 삼각형의 리스트를 재구성한다.
	std::vector<EgFace *> NewFaces;
	for (EgFace *f : m_pMesh->m_pFaces)
	{
		if (f->m_Idx != -1)
		{
			f->m_Idx = (int)NewFaces.size();
			NewFaces.push_back(f);
		}
		else
			delete f;
	}
	m_pMesh->m_pFaces = NewFaces;
}
