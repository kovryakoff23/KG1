#ifndef SCENE_2D_H
#define SCENE_2D_H

#include "Camera2D.h"

class Scene2D : public Camera2D
{
private:
	typedef double (*Func)(double);
public:
	Scene2D(double L, double R, double B, double T) : Camera2D(L, R, B, T)
	{
	}
	void Plot(HDC dc, Func fi,Func r, bool axes=true)
	{
		if (axes)
			Axes(dc);
		double t =-10;
		MoveTo(fi(t), r(t));
		while (t < 5) {
			LineTo(dc, fi(t), r(t));
			t += 0.1;
		}
		// Построение графика функции f
		// Здесь передаваемая в качестве параметра функция f вызывается как обычная функция:
		// f(x);
	}
};

#endif SCENE_2D_H
