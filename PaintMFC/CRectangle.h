#pragma once
#include "CFigure.h"

class CRectangle : public CFigure {
public:
	CRectangle() : CFigure(1) {};
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};