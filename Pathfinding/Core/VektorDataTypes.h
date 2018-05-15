#ifndef _VEKTORDATATYPES_H
#define _VEKTORDATATYPES_H



#define EPSILON = 1e-15;

namespace vektor3d
{
	typedef float f32;
	
	typedef unsigned short us16;
	
	typedef unsigned int ui32;
	
	typedef int i32;
	
	typedef short s16;
	
	typedef bool boolean;
	
	typedef char c8;
	
	typedef unsigned char uc8;
	
	enum E_PRIMITIVE_TYPE
	{
		EPT_POINT = 0,
		EPT_LINE,
		EPT_LINE_STRIP,
		EPT_LINE_LOOP,
		EPT_TRIANGLE,
		EPT_TRIANGLE_FAN,
		EPT_TRIANGLE_STRIP,
		EPT_QUAD
	};
	
	enum RENDERER_TYPE { ERT_OGL = 0 , ERT_D3D = 1 };
	
	enum E_TRANSFORMATION_STATE { ETS_WORLD = 0 , ETS_VIEW , ETS_PROJECTION , ETS_TEXTURE };
	
	enum E_NODE_TYPE	{ ENT_TRANSFORM_NODE, ENT_CAMERA_NODE , ENT_LIGHT_NODE, ENT_OPAQUE_NODE, ENT_TRANSPARENT_NODE };
	
	enum E_BOUNDS_TYPE	{ EBT_BOUNDING_SPHERE, EBT_BOUNDING_BOX  };
	
	enum E_AXIS_TYPE { EAT_X_AXIS, EAT_Y_AXIS, EAT_Z_AXIS };
	
	enum E_TEXTURE_TYPE { ETT_TEXTURE_1D, ETT_TEXTURE_2D, ETT_TEXTURE_3D, ETT_TEXTURE_CUBEMAP };
	
	enum E_IMAGEFORMAT_TYPE { EFT_RGB, EFT_BGR, EFT_RGBA, EFT_ARGB	};
	
	enum E_TEXTUREFILTER_MODE { ETM_FASTEST, ETM_NICEST, ETM_POINT_SAMPLING, ETM_LINEAR_SAMPLING, ETM_TRILINEAR_SAMPLING };
	
	enum E_MIPMAP_MODE { EMM_BASE_LEVEL_MIPMAP, EMM_MULTI_LEVEL_MIPMAP };
	
	enum E_TEXTURE_BOUNDARY_MODE { ETB_CLAMP, ETB_REPEAT, ETB_CLAMP_TO_EDGE, ETB_CLAMP_TO_BOUNDARY };
	
	//struct RayStruct
//	{
//		core::Point3f RayBegin;
//		core::Point3f RayEnd;
//	} Ray;
	
	
	/*struct EventMouseInput
	{
		ui32 X;
		
		ui32 Y;
		
		f32 Wheel;
		
		// A bitmap of button states. You can use isButtonPressed() to determine
		// if a button is pressed or not.
		// Currently only valid if the event was EMIE_MOUSE_MOVED
		ui32 ButtonStates;
		
		// Is the left button pressed down?
		bool isLeftPressed() const { return 0 != ( ButtonStates & EMBSM_LEFT ); }
		
		// Is the right button pressed down?
		bool isRightPressed() const { return 0 != ( ButtonStates & EMBSM_RIGHT ); }
		
		// Is the middle button pressed down?
		bool isMiddlePressed() const { return 0 != ( ButtonStates & EMBSM_MIDDLE ); }
	
	};
	
	// Any kind of keyboard event.
	struct EventKeyInput
	{
		// Character corresponding to the key (0, if not a character)
		wchar_t Char;
		
		//! Key which has been pressed or released
		EKEY_CODE Key;
		
		//! If not true, then the key was left up
		bool PressedDown:1;
		
		//! True if shift was also pressed
		bool Shift:1;
		
		//! True if ctrl was also pressed
		bool Control:1;
	};*/
}

#endif