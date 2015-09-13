#define PICTUS_VER_MAJOR		1
#define PICTUS_VER_MINOR		3
#define PICTUS_VER_REVISION		2
#define PICTUS_VER_BUILD		0

#define LOC_TX_(a,b,c,d) L#a#b#c#d
#define LOC_TX(a,b,c,d) LOC_TX_(a,b,c,d)

#define STRINGIFY2(m) #m
#define STRINGIFY(m) STRINGIFY2(m)

#define _WIDEN(x)  L ## x
#define WIDEN(x)   _WIDEN(x)

#define RC_FILE_VERSION			PICTUS_VER_MAJOR,PICTUS_VER_MINOR,PICTUS_VER_REVISION,PICTUS_VER_BUILD
#define STR_RC_FILE_VERSION		WIDEN(STRINGIFY(PICTUS_VER_MAJOR)) L"." WIDEN(STRINGIFY(PICTUS_VER_MINOR)) L"." WIDEN(STRINGIFY(PICTUS_VER_REVISION)) L"." WIDEN(STRINGIFY(PICTUS_VER_BUILD))
