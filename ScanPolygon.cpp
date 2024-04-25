#define NOMINMAX

#include "ScanPolygon.h"
#include <iostream>
#include <d3d9.h>

int W = 640;
int H = 480;

bool ScanPolygon::pnpoly(GVertex p[], size_t pLength, GVertex& t)
{
	// https://wrf.ecse.rpi.edu/Research/Short_Notes/pnpoly.html
	size_t i, j = 0;
	bool c = false;
	for (i = 0, j = pLength - 1; i < pLength; j = i++) {
		if (((p[i].y > t.y) != (p[j].y > t.y))
			&& (t.x < (p[j].x - p[i].x) * (t.y - p[i].y) / (p[j].y - p[i].y) + p[i].x))
			c = !c;
	}
	return c;
}


GVertex* ScanPolygon::getFrame(GVertex polygon[], size_t polygonLength, GVertex* frame)
{
	float minx = std::numeric_limits<float>::max();
	float miny = std::numeric_limits<float>::max();
	float maxx = std::numeric_limits<float>::min();
	float maxy = std::numeric_limits<float>::min();

	for (unsigned int i = 0; i < polygonLength; i++) {
		if (polygon[i].x < minx)
			minx = polygon[i].x;
		if (polygon[i].x > maxx)
			maxx = polygon[i].x;
		if (polygon[i].y < miny)
			miny = polygon[i].y;
		if (polygon[i].y > maxy)
			maxy = polygon[i].y;
	}
	frame[0] = { minx, miny, 0, 0,  {0, 0, 0}, {0, 0, 0, 0} };
	frame[1] = { maxx, miny, 0, 0,  {0, 0, 0}, {0, 0, 0, 0} };;
	frame[2] = { maxx, maxy, 0, 0,  {0, 0, 0}, {0, 0, 0, 0} };
	frame[3] = { minx, maxy, 0, 0,  {0, 0, 0}, {0, 0, 0, 0} };;

	return frame;
}

void ScanPolygon::trace(char* pixels, GVertex p[], size_t pLength)
{
	DWORD* row = (DWORD*)pixels;
	GVertex* frame = new GVertex[4];
	frame = getFrame(p, pLength, frame);

	float y1 = frame[0].y;
	float y2 = y1;
	float x1 = frame[0].x;
	float x2 = x1;
	for (int i = 1; i < 4; i++) {
		if (frame[i].y != y1) {
			y2 = frame[i].y;
			break;
		}
	}
	for (int i = 1; i < 4; i++) {
		if (frame[i].x != x1) {
			x2 = frame[i].x;
			break;
		}
	}
	float t = y1;
	y1 = std::min(y1, y2);
	y2 = std::max(t, y2);
	t = x1;
	x1 = std::min(x1, x2);
	x2 = std::max(t, x2);

	int iy1 = (int)std::round(y1);
	int iy2 = (int)std::round(y2);
	int ix1 = (int)std::round(x1);
	int ix2 = (int)std::round(x2);
	for (int y = iy1; y <= iy2; y++) {
		for (int x = ix1; x <= ix2; x++) {
			GVertex gv = { (float)x, (float)y };
			if (pnpoly(p, pLength, gv) && y >= 0 && y < H && x >= 0 && x < W) {
				//pixels[W * y + x].r = 255;
				//pixels[W * y + x].g = 255;
				//pixels[W * y + x].b = 255;
				*(row + W * y * 4 + x * 4) = D3DCOLOR_XRGB(95, 74, 124);
			}
		}
	}


	delete[] frame;
}

//bool black = true;
////tictac = false;
//for (int y = 0; y < h; ++y) {
//    DWORD* row = (DWORD*)data;
//    for (int x = 0; x < w; ++x) {
//        if (!black) {
//            *row++ = tictac ? D3DCOLOR_XRGB(95, 74, 124) : D3DCOLOR_XRGB(0, 255, 0);
//        }
//        else {
//            *row++ = tictac ? D3DCOLOR_XRGB(0, 255, 0) : D3DCOLOR_XRGB(95, 74, 124);
//        }
//        black = !black;
//
//    }
//    black = !black;
//    data += pitch;
//}