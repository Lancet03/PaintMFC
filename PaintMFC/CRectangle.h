#pragma once
#include "CFigure.h"

class CRectangle : public CFigure {
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};