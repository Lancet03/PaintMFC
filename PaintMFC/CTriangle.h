#pragma once
#include "CFigure.h"

class CTriangle : public CFigure {
public:
	CTriangle() : CFigure(3) {};
	virtual ~CTriangle() { };
	bool PtInFig(int x, int y) override;
	void DrawSelf(CDC* pDC) override;
};