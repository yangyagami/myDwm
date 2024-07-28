/* See LICENSE file for copyright and license details. */


/* appearance */
#include <X11/X.h>
static const unsigned int bargap     	= 10;        /* gap pixel between windows */
static const unsigned int gappx     	= 10;        /* gap pixel between windows */
static const unsigned int borderpx  	= 0;        /* border pixel of windows */
static const unsigned int snap      	= 32;       /* snap pixel */
static const int showbar            	= 1;        /* 0 means no bar */
static const int topbar             	= 1;        /* 0 means bottom bar */
static const int scalepreview           = 4;        /* preview scaling (display w and h / scalepreview) */
static const int previewbar             = 1;        /* show the bar in the preview window */
static const char *fonts[]          	= { "FontAwesome:pixelsize=18:antialias=true:autohint=true" };
static const char dmenufont[]       	= "Sauce Code Pro Nerd Font Mono:size=14";
static const char col_gray1[]       	= "#222222";
static const char col_gray2[]       	= "#444444";
static const char col_gray3[]       	= "#bbbbbb";
static const char col_gray4[]       	= "#eeeeee";
static const unsigned int baralpha      = OPAQUE;
static const unsigned int borderalpha   = OPAQUE;
static const char col_cyan[]            = "#37474f";
static const char col_blue[]            = "#686ab3";

/*nord theme*/
static const char col_nordfg[] = "#434C5E";
static const char col_nordbg[] = "#D8DEE9";
static const char col_nordborder[] = "#D8DEE9";

static const char col_nordfgSel[] = "#434C5E";
static const char col_nordbgSel[] = "#88C0D0";
static const char col_nordborderSel[] = "#88C0D0";

/*dark theme*/
static const char col_darkfg[] = "#EEEEEE";
static const char col_darkbg[] = "#1E222B";
static const char col_darkborder[] = "#1E222B";

static const char col_darkfgSel[] = "#83A4C7";
static const char col_darkbgSel[] = "#282C37";
static const char col_darkborderSel[] = "#83A4C7";

/* window frame theme */
static const char col_background[] = "#FFFFFF";

/*status theme*/
static const char *status_colors[][3] = {
	/*               fg         bg         border   */
	{"#8BACAA", col_darkbg, col_darkborder},
	{"#B04759", col_darkbg, col_darkborder},
	{"#E76161", col_darkbg, col_darkborder},
	{"#F99B7D", col_darkbg, col_darkborder},
};
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_darkfg, col_darkbg, col_darkborder },
	[SchemeSel]  = { col_darkfgSel, col_darkbgSel,  col_darkborderSel  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Chromium", NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "平铺",     tile          },    /* first entry is default */
	{ "浮动",     NULL          },    /* no layout function means floating behavior */
	{ "总览",     overview_grid },    /* no layout function means floating behavior */
	{ "ver",      vertical      },    /* no layout function means floating behavior */
	{ "[M]",      monocle       },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      previewtag,     {.ui = TAG } },     \

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_nordbg, "-nf", col_nordfg, "-sb", col_nordbgSel, "-sf", col_nordfgSel, NULL };
static const char *termcmd[]  = { "st", "-e", "fish", NULL };
static const char *flameshotcmd[] = { "flameshot", "gui", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask, 			XK_p,      spawn,          {.v = flameshotcmd } },
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,             			XK_c,      killallclients,     {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

