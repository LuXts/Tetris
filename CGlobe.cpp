#include "pch.h"
#include "CGlobe.h"

CGlobe Globe;

BOOL CGlobe::KEY_UP = FALSE;
BOOL CGlobe::KEY_DOWN = FALSE;
BOOL CGlobe::KEY_LEFT = FALSE;
BOOL CGlobe::KEY_RIGHT = FALSE;
BOOL CGlobe::KEY_PAUSE = FALSE;

CTetrisDlg* CGlobe::dlg = NULL;