#pragma once
#include "CFigure.h"

class CTriangle : public CFigure {
public:
	CTriangle() : CFigure(L"Triangle") {};
	virtual ~CTriangle() { };
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};