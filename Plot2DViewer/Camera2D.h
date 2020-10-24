#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include <windows.h>

class Camera2D
{
protected:
	double L, R, B, T;					// ������� ���������� ������ ������� ������� ����
	int W, H;							// ���������� ������� ������� ����
	int WorldToScreenX(double X)		// ������� �� ������� ��������� � �������� (��� ��������)
	{double Xs = ((X - L) / (R - L)) * W;
	if (Xs > 0)
		return  Xs;
	else
		return 0;
	}
	int WorldToScreenY(double Y)		// ������� �� ������� ��������� � �������� (��� ��������)
	{
		double Ys = ((T - Y) / (T - B)) * H;
		if (Ys > 0)
			return  Ys;
		else
			return 0;
	}
	double ScreenToWorldX(int X)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return L + (L - R) * X / W;
	}
	double ScreenToWorldY(int Y)		// ������� �� �������� ��������� � ������� (��� ��������)
	{
		return  T - (T - B) * Y / H;
	}
private:
	double posX, posY;					// ������� ������������ ������� � ������� ����������� (��� ������� MoveTo � LineTo)
public:
	Camera2D(double L, double R, double B, double T) : L(L), R(R), B(B), T(T)
	{
	}
	void Clear(HDC dc)
	{
		RECT r;
		GetClientRect(WindowFromDC(dc), &r);
		Rectangle(dc, r.left, r.top, r.right, r.bottom);
	}
	void SetResolution(HDC dc)
	{
		RECT r;
		GetWindowRect(WindowFromDC(dc), &r);
		W = r.right - r.left;
		H = r.bottom - r.top;
		double Bn = (B + T) / 2 - (R - L) / 2 * H / W;
		double Tn = (B + T) / 2 + (R - L) / 2 * H / W;
		B = Bn;
		T = Tn;
		// ������ ��������� ���������� ��� ��������� �������� ����
		// � ��� �������� �������� ������� W, H, � ����� ������������� �������� ���������� L, R, B, T ����� �������, ����� ���������� ���������� �������� �� ������������ ����
	}
	void  Moving(double deltaX, double deltaY) {
		L = L - (R - L) * deltaX / W;
		R = R - (R - L) * deltaX / W;
		B = B + (B - T) * deltaY / H;
		T = T + (B - T) * deltaY / H;
	}
	void ChangeSize(double k, double X, double Y) {
		double Xp = atan(Y / X), Yp = sqrt(X*X + Y * Y);
		double Xw = ScreenToWorldX(Xp), Yw = ScreenToWorldY(Yp);
		L = Xw - (Xw - L) / k;
		R = Xw + (R - Xw) / k;
		T = Yw + (T - Yw) / k;
		B = Yw - (Yw - B) / k;
	}
	void MoveTo(double X, double Y)
	{
		posX = WorldToScreenX(X);
		posY = WorldToScreenY(Y);
	}
	void LineTo(HDC dc, double X, double Y)
	{
		::MoveToEx(dc, posX, posY, nullptr);
		double Xs, Ys;
		Xs = WorldToScreenX(X);
		Ys = WorldToScreenY(Y);
		posX = Xs;
		posY = Ys;
		::LineTo(dc, Xs, Ys);
		// ��������� ����� �� ������� ������� ������������ ������� � ����� (X, Y) � ��� ����������� � ��� �����
		// �������� ��������, ��� �� ��������� � ������� �����������
		// ��� ��������� ����� ����� ���� ������������ WinApi �������
		// ::MoveToEx(dc, Xs, Ys, nullptr) � ::LineTo(dc, Xs, Ys)
	}
	void Axes(HDC dc)
	{
		::MoveToEx(dc, 0, (WorldToScreenY(B) - WorldToScreenY(T)) / 2, NULL);
		::LineTo(dc, WorldToScreenX(R), (WorldToScreenY(B)- WorldToScreenY(T))/2);
		::MoveToEx(dc, (WorldToScreenX(R) - WorldToScreenX(L)) / 2, 0, NULL);
		::LineTo(dc, (WorldToScreenX(R) - WorldToScreenX(L)) / 2, WorldToScreenY(B));
	}
};

#endif CAMERA_2D_H
