#pragma once

class CFigure {
public:
	CString figureName;
	int x, y;
	int width, height;

	CFigure(CString figureName);
	virtual ~CFigure();
	virtual bool PtInFig(int x, int y) = 0;
	virtual void DrawSelf(CDC* pDC) = 0;
};