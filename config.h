/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 1; /* border pixel of windows */
static const unsigned int snap = 32;    /* snap pixel */
static const unsigned int gappih = 20;  /* horiz inner gap between windows */
static const unsigned int gappiv = 10;  /* vert inner gap between windows */
static const unsigned int gappoh = 10; /* horiz outer gap between windows and screen edge */
static const unsigned int gappov = 30; /* vert outer gap between windows and screen edge */
static int smartgaps = 1; /* 1 means no outer gap when there is only one window */
static const int showbar = 1; /* 0 means no bar */
static const int topbar = 1;  /* 0 means bottom bar */
static const char *fonts[] = {
    "Jetbrains Mono Nerd Font:size=12:antialias=true:autohint=true",
    "JoyPixels:pixelsize=12:antialias=true:autohint=true"};
static const char col_gray1[] = "#1D202F";
static const char col_gray2[] = "#C0CAF5";
static const char col_gray3[] = "#C0CAF5";
static const char col_gray4[] = "#1D202F";
static const char col_cyan[] = "#7AA2F7";
static const char *colors[][3] = {
    /*               fg         bg         border   */
    [SchemeNorm] = {col_gray3, col_gray1, col_gray2},
    [SchemeSel] = {col_gray4, col_cyan, col_cyan},
};

/* tagging */
static const char *tags[] = {"", "", "", "", ""};

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp",      NULL,       NULL,       0,            1,           -1},
    {"PCManFM",   NULL,       NULL,       1 << 8,       1,           -1},
    {"Picture-in-picture", NULL, NULL,    1 << 8,       1,           -1},

};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;    /* number of clients in master area */
static const int resizehints = 1; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
#define FORCE_VSPLIT                                                           \
  1 /* nrowgrid layout: force two clients to always split vertically */

/* Include mod files */

#include "shiftview.c"
#include "vanitygaps.c"
#include "movestack.c"
#include "tatami.c"

static const Layout layouts[] = {
    /* symbol     arrange function */
    {"﬿", tile}, /* first entry is default */
    {" ", monocle},
    {"", spiral},
    {"ﰂ", tatami },
    {"", dwindle},
    {"ﳟ ", deck},
    {"", bstack},
    {"力", bstackhoriz},
    {"", grid},
    {"", nrowgrid},
    {"", horizgrid},
    {"", gaplessgrid},
    {"濾", centeredmaster},
    {"礪", centeredfloatingmaster},
    {"", NULL}, /* no layout function means floating behavior */
    {NULL, NULL},
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                                      \
  {MODKEY, KEY, view, {.ui = 1 << TAG}},                                       \
      {MODKEY | ControlMask, KEY, toggleview, {.ui = 1 << TAG}},               \
      {MODKEY | ShiftMask, KEY, tag, {.ui = 1 << TAG}},                        \
      {MODKEY | ControlMask | ShiftMask, KEY, toggletag, {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                                             \
  {                                                                            \
    .v = (const char *[]) { "/bin/sh", "-c", cmd, NULL }                       \
  }

static Key keys[] = {
    /* modifier                     key        function        argument */
    {MODKEY | Mod1Mask, 	    XK_u,      incrgaps,       {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_u,      incrgaps,       {.i = -1}},
    {MODKEY | Mod1Mask,             XK_i,      incrigaps,      {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_i,      incrigaps,      {.i = -1}},
    {MODKEY | Mod1Mask, XK_o, incrogaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_o, incrogaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_6, incrihgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_6, incrihgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_7, incrivgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_7, incrivgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_8, incrohgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_8, incrohgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_9, incrovgaps, {.i = +1}},
    {MODKEY | Mod1Mask | ShiftMask, XK_9, incrovgaps, {.i = -1}},
    {MODKEY | Mod1Mask, XK_0, togglegaps, {0}},
    {MODKEY | Mod1Mask | ShiftMask, XK_0, defaultgaps, {0}},
    {MODKEY | Mod1Mask , XK_j, shiftview, {.i = +1}},
    {MODKEY, XK_s, shiftview, {.i = +1}},
    {MODKEY | Mod1Mask , XK_k, shiftview, {.i = -1}},
    {MODKEY, XK_w, shiftview, {.i = -1}},
    {MODKEY, XK_j, focusstack, {.i = +1}},
    {MODKEY, XK_k, focusstack, {.i = -1}},
    {MODKEY, XK_i, incnmaster, {.i = +1}},
    {MODKEY, XK_d, incnmaster, {.i = -1}},
    {MODKEY, XK_h, setmfact, {.f = -0.05}},
    {MODKEY, XK_l, setmfact, {.f = +0.05}},
    {MODKEY | ShiftMask,            XK_j,      movestack,      {.i = +1}},
    {MODKEY | ShiftMask,            XK_k,      movestack,      {.i = -1}},
    {MODKEY | ShiftMask, XK_h, setcfact, {.f = +0.25}},
    {MODKEY | ShiftMask, XK_l, setcfact, {.f = -0.25}},
    {MODKEY | ShiftMask, XK_o, setcfact, {.f = 0.00}},
    {MODKEY, XK_m, setlayout, {.v = &layouts[1]}},
    {MODKEY | ShiftMask, XK_Return, zoom, {0}},
    {MODKEY, XK_Tab, view, {0}},
    {MODKEY, XK_q, killclient, {0}},
    {MODKEY, XK_space, cyclelayout, {.i = +1}},
    {MODKEY | ShiftMask, XK_space, cyclelayout, {.i = -1}},
    {MODKEY, XK_0, view, {.ui = ~0}},
    {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
    TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
        TAGKEYS(XK_5, 4) {MODKEY | ShiftMask, XK_q, quit, {0}},
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle,
 * ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function argument
     */
    {ClkLtSymbol, 0, Button1, setlayout, {0}},
    {ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[2]}},
    {ClkLtSymbol, 0, Button4, cyclelayout, {.i = +1}},
    {ClkLtSymbol, 0, Button5, cyclelayout, {.i = -1}},
    {ClkClientWin, MODKEY, Button1, movemouse, {0}},
    {ClkClientWin, MODKEY, Button2, togglefloating, {0}},
    {ClkClientWin, MODKEY, Button3, resizemouse, {0}},
    {ClkTagBar, 0, Button1, view, {0}},
    {ClkTagBar, 0, Button3, toggleview, {0}},
    {ClkTagBar, MODKEY, Button1, tag, {0}},
    {ClkTagBar, MODKEY, Button3, toggletag, {0}},
};
