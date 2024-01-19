/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 20;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 20;       /* vert inner gap between windows */
static const unsigned int gappoh    = 20;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 20;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=9", "Material Design Icons:Regular:pixelsize=19:antialias=true" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#1e2326";
static const char col_gray2[]       = "#272e33";
static const char col_gray3[]       = "#d3c6aa";
static const char col_gray4[]       = "#fffbef";
static const char col_gray5[]       = "#9da9a0";
static const char col_gray6[]       = "#859289";
static const char col_cyan[]        = "#7fbbb3";
static const char col_border[]      = "#7fbbb3";
static const char col_orange[]      = "#e69875";
static const char col_blue[]        = "#7fbbb3";
static const char col_darkblue[]    = "#384b55";
static const char col_mauve[]       = "#d699b6";
static const char col_yellow[]      = "#dbbc7f";
static const char col_green[]       = "#a7c080";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
	[SchemeStatus]  = { col_cyan, col_gray1,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_cyan, col_darkblue,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { col_gray5, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	[SchemeInfoSel]  = { col_gray4, col_gray1,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
	[SchemeInfoNorm]  = { col_gray3, col_gray1,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "󰺻", ""};
static const int taglayouts[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const unsigned int ulinepad	= 5;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke	= 2;	/* thickness / height of the underline */
static const unsigned int ulinevoffset	= 1;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		= 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     switchtotag    isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       1 << 4,       1,             0,             -1 },
	{ "firefox",  NULL,       NULL,       1 << 1,       1,             0,             -1 },
        { "Thunar",   NULL,	  NULL,       1 << 2,       1,             0,             -1 },
        { "Mousepad", NULL,       NULL,       1 << 3,       1,             0,             -1 },
	{ "steam",    NULL,       NULL,       1 << 5,       0,             0,             -1 },
        { "Cider",    NULL,       NULL,       1 << 6,       0,             0,             -1 },
        { "kitty",    "kitty",    "ncmpcpp",  1 << 6,       1,             1,             -1 },
        { "ncmpcpp",  "st",       "ncmpcpp",  1 << 6,       1,             1,             -1 },
        { "Nsxiv",    NULL,       NULL,       1 << 6,       1,             1,             -1 },
        { "discord",  NULL,       NULL,       1 << 7,       1,             0,             -1 },
	{ "dev.geopjr.Tuba",	NULL,	NULL,	1 << 7,		1,		0,		-1 },
        { "thunderbird", NULL,     NULL,      1 << 8,       0,             0,             -1 },
	{ "kdeconnect.sms",	NULL,	NULL,	1 << 9,		1,		1,		-1 },
	{ "valent",	NULL,	NULL,	      1 << 9,       0,             0,             -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

/*#include "fibonacci.c"*/
#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
        { "󰕴",     dwindle }, /* first entry is default */
	{ "󰃚",      monocle },
	{ "󰕰",      tile },
	{ "󰡃",      spiral },
	{ "󱒉",      deck },
	{ "󰾍",      bstack },
	{ "󱇚",      bstackhoriz },
	{ "󰡃",      grid },
	{ "󱒇",      nrowgrid },
	{ "󰕭",      horizgrid },
	{ "󱒈",      gaplessgrid },
	{ "󰕫",      centeredmaster },
	{ "󰕬",      centeredfloatingmaster },
	{ "󰕯",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
/*static const char *dmenucmd[] = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };*/
/*static const char *dmenucmd[] = { "dmenu_run", "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };*/
static const char *dmenucmd[] = { "dmenu_run", "-c", NULL };
static const char *termcmd[]  = { "st", NULL };
/*static const char *termcmd[]  = { "kitty", NULL };*/
static const char *dmenuexit[] = { "dmenu-power", NULL };
static const char *roficmd[] = { "rofi_run_dwm", "-d", NULL };
static const char *exitcmd[] = { "rofi_run_dwm", "-l", NULL };
static const char *rofitab[] = { "rofi_run_dwm", "-w", NULL };
static const char *layoutmenu_cmd = "layoutmenu.sh";

#include "selfrestart.c"
#include "exitdwm.c"

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
        { Mod1Mask,                     XK_F1,     spawn,          {.v = roficmd } },
        { MODKEY,                       XK_x,      spawn,          {.v = exitcmd } },
	{ Mod1Mask,			XK_x,      spawn,          {.v = dmenuexit } },
        { Mod1Mask,			XK_Tab,	   spawn,	   {.v = rofitab } },
        { Mod1Mask|ShiftMask,           XK_k,      spawn,          SHCMD("kunst") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY|Mod1Mask,              XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ Mod1Mask|ShiftMask,           XK_space,  togglefloating, {0} },
	{ Mod1Mask|ControlMask,         XK_space,  togglealwaysontop, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_c,                      spawn,         SHCMD("pkill picom") },
	{ Mod1Mask,                     XK_c,                      spawn,         SHCMD("picom --config ~/.config/picom/picom.conf --daemon") },
	{ MODKEY,                       XK_k,                      spawn,         SHCMD("conky_toggle") },
	{ MODKEY|ControlMask,           XK_c,                      spawn,         SHCMD("rofi_run_dwm -c") },
	{ Mod1Mask,                     XK_q,                      spawn,         SHCMD("rofi_run_dwm -q") },
        { 0,				XF86XK_Tools,		   spawn,         SHCMD("st -g 120x30+30+55 -c ncmpcpp -e ncmpcpp") },
	{ 0,				XF86XK_AudioPlay,	   spawn,	  SHCMD("mpc toggle") },
	{ 0,				XF86XK_AudioPrev,	   spawn,	  SHCMD("mpc prev") },
	{ 0,				XF86XK_AudioNext,	   spawn,	  SHCMD("mpc next") },
	{ 0,				XF86XK_AudioStop,	   spawn,	  SHCMD("mpc stop") },
        { 0,                            XF86XK_AudioMute,          spawn,         SHCMD("pactl set-sink-mute 0 toggle; kill -44 $(pidof dwmblocks)") },
        { 0,                            XF86XK_AudioLowerVolume,   spawn,         SHCMD("pactl set-sink-mute 0 false ; i3-volume -nPpC down 5; kill -44 $(pidof dwmblocks)") },
        { 0,                            XF86XK_AudioRaiseVolume,   spawn,         SHCMD("pactl set-sink-mute 0 false ; i3-volume -nPpC up 5; kill -44 $(pidof dwmblocks)") },
        { 0,                            XK_Print,                  spawn,         SHCMD("ob-screenshot --in5") },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
        { Mod1Mask|ControlMask,             XK_r,      self_restart,   {0} },
	/*{ MODKEY|ShiftMask,             XK_e,      quit,           {0} },*/
	{ MODKEY|ShiftMask,             XK_e,      exitdwm,       {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkLtSymbol,          0,              Button1,        cyclelayout,    {.i = +1 } },
	{ ClkLtSymbol,          0,              Button3,        cyclelayout,    {.i = -1 } },
	{ ClkLtSymbol,          0,              Button2,        layoutmenu,     {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5 } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "incnmaster",     incnmaster },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
};
