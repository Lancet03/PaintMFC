#pragma once
#include "CFigure.h"

class CCircle : public CFigure {
public:
	CCircle() : CFigure(2) {};
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};