#pragma once
#include "CFigure.h"

class CCircle : public CFigure {
public:
	CCircle() : CFigure(L"Circle") {};
	virtual ~CCircle() {};
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};