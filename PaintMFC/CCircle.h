#pragma once
#include "CFigure.h"

class CCircle : public CFigure {
	char figureType = 'C';
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};