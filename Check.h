#pragma once

#ifndef _CHECK_H_
#define _CHECK_H_

#include "BoardAndCell.h"
#include <cmath>

bool NextCheck(CELL*, CELL, CELL);
bool Icheck(CELL*, CELL , CELL);
bool LineCheck(CELL* , CELL , CELL);
bool Lcheck(CELL*, CELL , CELL );
bool Zcheck(CELL*, CELL, CELL );
bool Ucheck(CELL*, CELL, CELL);
bool AllCheck(CELL*, CELL , CELL );
bool Check_Exist_EqualPair(CELL* );

#endif
