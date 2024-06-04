#pragma once

class CFigure {
public:
	int figureType = 0;
	int x, y;
	int width, height;

	CFigure(int figureType);
	virtual ~CFigure();
	virtual bool PtInFig(int x, int y) = 0;
	virtual void DrawSelf(CDC* pDC) = 0;
};