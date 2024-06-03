#pragma once

class CFigure {
public:
	char figureType;
	int x, y;
	int width, height;

	CFigure();
	virtual ~CFigure();
	virtual bool PtInFig(int x, int y) = 0;
	virtual void DrawSelf(CDC* pDC) = 0;
};