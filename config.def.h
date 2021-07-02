// #include <X11/XF86keysym.h>

/****************************************************************************************
 * Appearance
 * Basic settings
 ****************************************************************************************/
static const unsigned int borderpx  = 1;	// border pixel of windows
static const unsigned int gappx     = 0;	// gaps between windows
static const unsigned int snap      = 32;	// snap pixel
static const int showbar            = 1;	// 0 means no bar
static const int vertpad            = 10;	// vertical padding of bar
static const int sidepad            = 10;	// horizontal padding of bar
static const int topbar             = 1;	// 0 means bottom bar
static const unsigned int gappih    = 10;	// horiz inner gap between windows
static const unsigned int gappiv    = 10;	// vert inner gap between windows
static const unsigned int gappoh    = 10;	// horiz outer gap between windows and screen edge
static const unsigned int gappov    = 10;	// vert outer gap between windows and screen edge
static const int smartgaps          = 0;	// 1 means no outer gap when there is only one window


/****************************************************************************************
 * Fonts
 ****************************************************************************************/
// static const char *fonts[]          = { "monospace:size=14" };
// static const char dmenufont[]       = "monospace:size=14";
static const char *fonts[]		= { "FontAwesome:pixelsize=16:antialias=true:autohint=true" };
static const char dmenufont[]		= "FontAwesome:pixelsize=16:antialias=true:autohint=true";


/****************************************************************************************
 * Colors
 * Basic settings
 ****************************************************************************************/
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_black[]       = "#000000";
static const char col_gray[] 	    = "#8191a8";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray,  col_cyan  },
};


/****************************************************************************************
 * others
 ****************************************************************************************/
static Bool isFakeFullScreen = False;

/****************************************************************************************
 * Tags and rules
 * class      instance    title       tags mask	isfloating   monitor
 ****************************************************************************************/
static const char *tags[] = { "1", "2", "3", "4", "5" };
static const Rule rules[] = {
		{"Firfox"},
	 //	{ .class = "Firefox",  .instance = NULL,      .title = NULL,        1<<4,	.isfloating = 0,           -1 },
};



/****************************************************************************************
 * Layouts
 * symbol	arrange		function 
 ****************************************************************************************/
static const float mfact     = 0.5;	// factor of master area size [0.05..0.95]
static const int nmaster     = 1;	// number of clients in master area
static const int resizehints = 1;	// 1 means respect size hints in tiled resizals
static const Layout layouts[] = {
	{ "T",      tile },		// first entry is default */
	{ "F",      NULL },		// no layout function means floating behavior */
	{ "M",      monocle },
};



/*****************************************************************************************
 * key definitions 
 ****************************************************************************************/
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },


/****************************************************************************************
 * Helper for spawning shell commands in the pre dwm-5.0 fashion
 ****************************************************************************************/
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
// static const char *fonts[]          = { "monospace:size=14" };
// static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static char dmenumon[2] = "0"; 										/* component of dmenucmd, manipulated in spawn() */

static const char *dmenucmd[]		= { "/home/pramodkadam/.local/bin/mdmenu_run", NULL };		// dmemu
static const char *search_home[]	= { "/home/pramodkadam/.local/bin/search_home", NULL };		// search
static const char *powerctl[] 		= { "/home/pramodkadam/.local/bin/dwm_power", NULL };		// powerctl
static const char *bluetooth[] 		= { "/home/pramodkadam/.local/bin/dwm_bluetooth", NULL }; 	// bluetooth
static const char *connect_wifi[]	= { "/home/pramodkadam/.local/bin/connect_wifi" , NULL };	// wifi

static const char *termcmd[] 		= { "tilix", NULL };						// terminal

static const char *brightness_up[]	= { "/home/pramodkadam/.local/bin/brightness.sh" , "up", NULL };	// Brightness up 
static const char *brightness_down[] 	= { "/home/pramodkadam/.local/bin/brightness.sh" , "down", NULL };	// Brightness down
static const char *volume_up[]		= { "/home/pramodkadam/.local/bin/volume.sh",		"up",	NULL};	// Volume up
static const char *volume_down[]	= { "/home/pramodkadam/.local/bin/volume.sh",		"down", NULL};	// Volume down


/****************************************************************************************
 * Commands
 ****************************************************************************************/
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } 	},
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } 	},
	{ MODKEY,                       XK_b,      togglebar,      {0} 			},
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } 		},
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } 		},
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } 		},
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } 		},
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} 	},
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} 	},
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },

	{ MODKEY,                       XK_u,		incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,		incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_i,		incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      	incrigaps,      {.i = -1 } },
	{ MODKEY|Mod5Mask,              XK_o,      	incrogaps,      {.i = +1 } },
	{ MODKEY|Mod5Mask|ShiftMask,    XK_o,      	incrogaps,      {.i = -1 } },
	{ MODKEY|Mod5Mask,              XK_6,      	incrihgaps,     {.i = +1 } },
	{ MODKEY|Mod5Mask|ShiftMask,    XK_6,      	incrihgaps,     {.i = -1 } },
	{ MODKEY|Mod5Mask,              XK_7,      	incrivgaps,     {.i = +1 } },
	{ MODKEY|Mod5Mask|ShiftMask,    XK_7,      	incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod5Mask,              XK_8,      	incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod5Mask|ShiftMask,    XK_8,      	incrohgaps,     {.i = -1 } },
	{ MODKEY,                       XK_9,   	incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_9,	      	incrovgaps,     {.i = -1 } },
	{ MODKEY|Mod5Mask,              XK_0,      	togglegaps,     {0} },
	{ MODKEY|Mod5Mask|ShiftMask,    XK_0,      	defaultgaps,    {0} },
	
	{ MODKEY|ControlMask,           XK_f,		toggle_fake_full_screen,		},
	{ 0,                            0x1008ff11,	spawn,		{.v = volume_down} 	},  // Volume up
	{ 0,                            0x1008ff13,	spawn,		{.v = volume_up}	},  // Volume down
	{ MODKEY|ShiftMask,             0xff52,		spawn,		{.v = brightness_up}	},  // Up Key
	{ MODKEY|ShiftMask,             0xff54,		spawn,		{.v = brightness_down}	},  // Down Key
	{ MODKEY,                       XK_s,		spawn,		{.v = search_home}      },  // Dmenu search
	{ MODKEY|ControlMask,           XK_d,		spawn,		{.v = powerctl}		},  // Dmenu power
	{ MODKEY|ShiftMask,             XK_b,		spawn,		{.v = bluetooth}	},  // Dmenu bluetooth
	{ MODKEY|ShiftMask,             XK_n,		spawn,		{.v = connect_wifi}	},  // Dmenu wifi
	{ MODKEY,                       XK_c,		cycle_tags,	{.i = +1}		},  // Cycle Through tags
	{ MODKEY|ControlMask,		XK_c,		cycle_tags,	{.i = -1}		},  // Cycle Through tags
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,		quit,           {0} },
};

/****************************************************************************************
* Button definitions
*  click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin   
****************************************************************************************/
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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



 /****************************************************************************************
* Sock for dwm-msg
****************************************************************************************/
static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};
