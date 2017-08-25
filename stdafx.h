
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#define ZOOM_IN            11    /* 焦距以速度SS变大(倍率变大) */
#define ZOOM_OUT        12    /* 焦距以速度SS变小(倍率变小) */
#define FOCUS_NEAR      13  /* 焦点以速度SS前调 */
#define FOCUS_FAR       14  /* 焦点以速度SS后调 */
#define IRIS_OPEN       15  /* 光圈以速度SS扩大 */
#define IRIS_CLOSE      16  /* 光圈以速度SS缩小 */

#define TILT_UP            21    /* 云台以SS的速度上仰 */
#define TILT_DOWN        22    /* 云台以SS的速度下俯 */
#define PAN_LEFT        23    /* 云台以SS的速度左转 */
#define PAN_RIGHT        24    /* 云台以SS的速度右转 */
#define UP_LEFT            25    /* 云台以SS的速度上仰和左转 */
#define UP_RIGHT        26    /* 云台以SS的速度上仰和右转 */
#define DOWN_LEFT        27    /* 云台以SS的速度下俯和左转 */
#define DOWN_RIGHT        28    /* 云台以SS的速度下俯和右转 */
#define PAN_AUTO        29    /* 云台以SS的速度左右自动扫描 */

#define TILT_DOWN_ZOOM_IN    58    /* 云台以SS的速度下俯&&焦距以速度SS变大(倍率变大) */
#define TILT_DOWN_ZOOM_OUT  59  /* 云台以SS的速度下俯&&焦距以速度SS变小(倍率变小) */
#define PAN_LEFT_ZOOM_IN    60  /* 云台以SS的速度左转&&焦距以速度SS变大(倍率变大)*/
#define PAN_LEFT_ZOOM_OUT   61  /* 云台以SS的速度左转&&焦距以速度SS变小(倍率变小)*/
#define PAN_RIGHT_ZOOM_IN    62  /* 云台以SS的速度右转&&焦距以速度SS变大(倍率变大) */
#define PAN_RIGHT_ZOOM_OUT  63  /* 云台以SS的速度右转&&焦距以速度SS变小(倍率变小) */
#define UP_LEFT_ZOOM_IN     64  /* 云台以SS的速度上仰和左转&&焦距以速度SS变大(倍率变大)*/
#define UP_LEFT_ZOOM_OUT    65  /* 云台以SS的速度上仰和左转&&焦距以速度SS变小(倍率变小)*/
#define UP_RIGHT_ZOOM_IN    66  /* 云台以SS的速度上仰和右转&&焦距以速度SS变大(倍率变大)*/
#define UP_RIGHT_ZOOM_OUT   67  /* 云台以SS的速度上仰和右转&&焦距以速度SS变小(倍率变小)*/
#define DOWN_LEFT_ZOOM_IN   68  /* 云台以SS的速度下俯和左转&&焦距以速度SS变大(倍率变大) */
#define DOWN_LEFT_ZOOM_OUT  69  /* 云台以SS的速度下俯和左转&&焦距以速度SS变小(倍率变小) */
#define DOWN_RIGHT_ZOOM_IN    70  /* 云台以SS的速度下俯和右转&&焦距以速度SS变大(倍率变大) */
#define DOWN_RIGHT_ZOOM_OUT    71  /* 云台以SS的速度下俯和右转&&焦距以速度SS变小(倍率变小) */
#define TILT_UP_ZOOM_IN        72    /* 云台以SS的速度上仰&&焦距以速度SS变大(倍率变大) */
#define TILT_UP_ZOOM_OUT    73    /* 云台以SS的速度上仰&&焦距以速度SS变小(倍率变小) */