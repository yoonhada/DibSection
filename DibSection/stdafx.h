#pragma once

enum _AXIS{ AXISX, AXISY, AXISZ };
enum _MAX{ ENOUGHBIGINT = 0x0001 << 30};

#include <Windows.h>
#include <WindowsX.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <CommCtrl.h>
#include <cmath>
#include <list>
#include <assert.h>

#include "resource.h"
#include "Define.h"

//
#include "Singleton.h"
#include "Frequency.h"
#include "DebugConsole.h"

#include "Point2.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Vertex.h"

//
#include "DibSection.h"
#include "Draw.h"
#include "DrawPixel.h"
#include "DrawBitmap.h"
#include "DrawModify.h"

//
#include "Trans.h"
#include "Node.h"
#include "ModelList.h"
#include "Draw3D.h"

#include "Memory.h"
#include "WndEx.h"