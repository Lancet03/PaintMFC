#include "pch.h"

#include "framework.h"
#include "CRectangle.h"

#include <algorithm>


bool CRectangle::PtInFig(int x, int y) {
	RECT r;
	r.left = this->x;
	r.right = this->x + this->width;
	r.top = this->y;
	r.bottom = this->y + this->height;

	if (r.left > r.right) {
		std::swap(r.left, r.right);
	}
	if (r.top > r.bottom) {
		std::swap(r.top, r.bottom);
	}

	CPoint point;
	point.x = x;
	point.y = y;
	return PtInRect(&r, point);
}

void CRectangle::DrawSelf(CDC* pDC) {
	pDC->Rectangle(this->x, this->y, this->x + this->width, this->y + this->height);
}