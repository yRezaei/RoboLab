#ifndef MATH3D_H
#define MATH3D_H

#include "../../src/engine.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <numeric>


const float EPSILON = std::numeric_limits<float>::epsilon();

inline float Distance2D(float x0, float x1, float y0, float y1)
{
	return sqrt((x0 - x1)*(x0 - x1) + (y0 - y1)*(y0 - y1));
}

inline int IsPointInBoundingBox(float x1, float y1, float x2, float y2, float px, float py) {
	float left, top, right, bottom; // Bounding Box For Line Segment
									// For Bounding Box
	if (x1 < x2)
	{
		left = x1;
		right = x2;
	}
	else
	{
		left = x2;
		right = x1;
	}
	if (y1 < y2)
	{
		top = y1;
		bottom = y2;
	}
	else
	{
		top = y1;
		bottom = y2;
	}
	if ((px + 0.01) >= left && (px - 0.01) <= right &&
		(py + 0.01) >= top && (py - 0.01) <= bottom)
	{
		return 1;
	}
	else return 0;
}

inline int LineIntersection(float l1x1, float l1y1, float l1x2, float l1y2, float l2x1, float l2y1, float l2x2, float l2y2,
	float *m1, float *c1, float *m2, float *c2, float* intersection_X, float* intersection_Y)
{
	float dx, dy;
	dx = l1x2 - l1x1;
	dy = l1y2 - l1y1;
	*m1 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	*c1 = l1y1 - *m1 * l1x1; // which is same as y2 - slope * x2

	dx = l2x2 - l2x1;
	dy = l2y2 - l2y1;
	*m2 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	*c2 = l2y1 - *m2 * l2x1; // which is same as y2 - slope * x2

	if ((*m1 - *m2) == 0) return 0;
	else
	{
		*intersection_X = (*c2 - *c1) / (*m1 - *m2);
		*intersection_Y = *m1 * *intersection_X + *c1;
		return 1;
	}
}

inline int LineSegmentIntersection(float l1x1, float l1y1, float l1x2, float l1y2, float l2x1, float l2y1, float l2x2, float l2y2,
	float *m1, float *c1, float *m2, float *c2, float* intersection_X, float* intersection_Y)
{
	float dx, dy;
	dx = l1x2 - l1x1;
	dy = l1y2 - l1y1;
	*m1 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	*c1 = l1y1 - *m1 * l1x1; // which is same as y2 - slope * x2

	dx = l2x2 - l2x1;
	dy = l2y2 - l2y1;
	*m2 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	*c2 = l2y1 - *m2 * l2x1; // which is same as y2 - slope * x2

	if ((*m1 - *m2) == 0) return 0;
	else
	{
		*intersection_X = (*c2 - *c1) / (*m1 - *m2);
		*intersection_Y = *m1 * *intersection_X + *c1;
	}
	if (IsPointInBoundingBox(l1x1, l1y1, l1x2, l1y2, *intersection_X, *intersection_Y) == 1 &&
		IsPointInBoundingBox(l2x1, l2y1, l2x2, l2y2, *intersection_X, *intersection_Y) == 1)
	{
		return 1;
	}
	else return 0;
}


inline float AreaRectangle(Vec2f A, Vec2f B, Vec2f C, Vec2f D)
{
	// Formula: 0.5*abs((Ay-Cy)*(Dx-Bx)+(By-Dy)*(Ax-Cx)
	return 0.5f * std::fabsf((A.y - C.y)*(D.x - B.x) + (B.y - D.y)*(A.x - C.x));
}


inline float AreaTriangle(Vec2f A, Vec2f B, Vec2f C)
{
	// Formula: 0.5*abs(Ax*(By-Cy)+ Bx*(Cy-Ay)+Cx*(Ay-By))
	return 0.5f * std::fabsf(A.x*(B.y - C.y) + B.x*(C.y - A.y) + C.x*(A.y - B.y));
}


inline bool ApproxEqual(float a, float b)
{
	bool returnFlag = false;
	if (abs(a - b) < EPSILON)
	{
		returnFlag = true;
	}
	return returnFlag;
}


inline double ScalarProduct(std::vector<double> const& a, std::vector<double> const& b)
{
	double product = 0;
	if (a.size() != b.size()) { throw std::runtime_error("different sizes"); }

	for (int i = 0; i < a.size(); i++)
	{
		product = product + a[i] * b[i];
	}

	//finally you return the product
	return product;

	//return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);

	//	double product = 0;
	//	product = (a*b.axis1) + (a.axis2*b.axis2);
	//	return product;

}


inline bool rectangle_collision(float L1, float T1, float W1, float H1, float L2, float T2, float W2, float H2)
{
	bool intersection;
	if ((L1 + W1 < L2) || (L2 + W2 < L1) || (T1 + H1 < T2) || (T2 + H2 < T1))
		intersection = false;
	else
		intersection = true;
	return intersection;
}



#endif // !MATH3D_H

