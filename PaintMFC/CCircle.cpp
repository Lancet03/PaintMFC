#include "pch.h"

#include "CCircle.h"
#include <cmath>

bool CCircle::PtInFig(int x, int y) {
	double a = std::abs(this->width / 2);
	double b = std::abs(this->height / 2);
	double centerX = this->x + this->width / 2;
	double centerY = this->y + this->height / 2;
	double dx = x - centerX;
	double dy = y - centerY;
	return (std::pow((x - centerX), 2) / pow(a, 2) + pow((y - centerY), 2) / pow(b, 2) <= 1);
}

void CCircle::DrawSelf(CDC* pDC) {
	pDC->Ellipse(this->x, this->y, this->x + this->width, this->y + this->height);
}