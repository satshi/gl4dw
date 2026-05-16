//
//  中断処理
//

#include"cells.h"
/*
#include <owl\owlpch.h>
#include <owl\applicat.h>
#include <owl\statusba.h>
#include <stdio.h>
#include <owl\gauge.h>
extern TApplication* app;
extern TStatusBar* sb;
extern TGauge* SolidGauge;

#define SYSTEM__MES app->PumpWaitingMessages();
char percent[10];
#define SET_PERCENT(a) SolidGauge->SetValue(a);
#define DISP_PERCENT
#define PERCENT100 SolidGauge->SetValue(100);

*/

BOOL cells::interupt(int i)
{
/*
	app->PumpWaitingMessages();
	SolidGauge->SetValue(i);
*/
	return FALSE;
}