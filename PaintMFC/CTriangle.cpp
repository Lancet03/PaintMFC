#include "pch.h"

#include "CTriangle.h"

bool CTriangle::PtInFig(int x, int y) {
	CPoint p1 = CPoint(this->x, this->y);
	CPoint p2 = CPoint(this->x + this->width / 2, this->y + this->height);
	CPoint p3 = CPoint(this->x + this->width, this->y);

	double v1 = (p1.x - x) * (p2.y - p1.y) - (p2.x - p1.x) * (p1.y - y);
	double v2 = (p2.x - x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - y);
	double v3 = (p3.x - x) * (p1.y - p3.y) - (p1.x - p3.x) * (p3.y - y);

	if ((v1 > 0 && v2 > 0 && v3 > 0) || (v1 < 0 && v2 < 0 && v3 < 0)) {
		return true;
	}
	else if (v1 == 0 || v2 == 0 || v3 == 0) {
		return true;
	}
	else {
		return false;
	}
}

void CTriangle::DrawSelf(CDC* pDC) {
	CPoint points[3];
	points[0] = CPoint(this->x, this->y);
	points[1] = CPoint(this->x + this->width / 2, this->y + this->height);
	points[2] = CPoint(this->x + this->width, this->y);

	pDC->Polygon(points, 3);
}