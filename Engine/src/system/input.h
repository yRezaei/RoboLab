#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <vector>
#include <array>
#include <utility>
#include <glm/glm.hpp>
#include "../mathematic/math3D.h"


namespace robolab {
	using namespace math3D;
	namespace gui {
		class Window;
	}
}
namespace robolab {
	namespace system {

		struct InputEvent {
			std::array<bool, 283> keyState;
			std::array<bool, 3> mouseState;
			bool isMouseMoving;
			bool isWheelRotating;
			Vec2i mousePos;
			Vec2i mouseWheel;
			InputEvent() {
				keyState = std::array<bool, 283>{0};
				mouseState = std::array<bool, 3>{0};
				isMouseMoving = false;
				isWheelRotating = false;
			}
			void reset() {
				keyState = std::array<bool, 283>{0};
				//mouseState = std::array<bool, 3>{0};
				 mouseWheel = Vec2i();
			}
		};

		enum KeyEventType {
			KEY_UNKNOWN = 0,
			KEY_A = 4,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z,
			KEY_1,
			KEY_2,
			KEY_3,
			KEY_4,
			KEY_5,
			KEY_6,
			KEY_7,
			KEY_8,
			KEY_9,
			KEY_0,
			KEY_RETURN,
			KEY_ESCAPE,
			KEY_BACKSPACE,
			KEY_TAB,
			KEY_SPACE,
			KEY_MINUS,
			KEY_EQUALS,
			KEY_LEFTBRACKET,
			KEY_RIGHTBRACKET,
			KEY_BACKSLASH,
			KEY_NONUSHASH,
			KEY_SEMICOLON,
			KEY_APOSTROPHE,
			KEY_GRAVE,
			KEY_COMMA,
			KEY_PERIOD,
			KEY_SLASH,
			KEY_CAPSLOCK,
			KEY_F1,
			KEY_F2,
			KEY_F3,
			KEY_F4,
			KEY_F5,
			KEY_F6,
			KEY_F7,
			KEY_F8,
			KEY_F9,
			KEY_F10,
			KEY_F11,
			KEY_F12,
			KEY_PRINTSCREEN,
			KEY_SCROLLLOCK,
			KEY_PAUSE,
			KEY_INSERT,
			KEY_HOME,
			KEY_PAGEUP,
			KEY_DELETE,
			KEY_END,
			KEY_PAGEDOWN,
			KEY_RIGHT,
			KEY_LEFT,
			KEY_DOWN,
			KEY_UP,
			KEY_NUMLOCKCLEAR,
			KEY_KP_DIVIDE,
			KEY_KP_MULTIPLY,
			KEY_KP_MINUS,
			KEY_KP_PLUS,
			KEY_KP_ENTER,
			KEY_KP_1,
			KEY_KP_2,
			KEY_KP_3,
			KEY_KP_4,
			KEY_KP_5,
			KEY_KP_6,
			KEY_KP_7,
			KEY_KP_8,
			KEY_KP_9,
			KEY_KP_0,
			KEY_KP_PERIOD,
			KEY_NONUSBACKSLASH,
			KEY_APPLICATION,
			KEY_POWER,
			KEY_KP_EQUALS,
			KEY_F13,
			KEY_F14,
			KEY_F15,
			KEY_F16,
			KEY_F17,
			KEY_F18,
			KEY_F19,
			KEY_F20,
			KEY_F21,
			KEY_F22,
			KEY_F23,
			KEY_F24,
			KEY_Execute,
			KEY_HELP,
			KEY_MENU,
			KEY_SELECT,
			KEY_STOP,
			KEY_AGAIN,
			KEY_UNDO,
			KEY_CUT,
			KEY_COPY,
			KEY_PASTE,
			KEY_FIND,
			KEY_MUTE,
			KEY_VOLUMEUP,
			KEY_VOLUMEDOWN,
			KEY_LOCKINGCAPSLOCK,
			KEY_LOCKINGNUMLOCK,
			KEY_LOCKINGSCROLLLOCK,
			KEY_KP_COMMA,
			KEY_KP_EQUALSAS400,
			KEY_INTERNATIONAL1,
			KEY_INTERNATIONAL2,
			KEY_INTERNATIONAL3,
			KEY_INTERNATIONAL4,
			KEY_INTERNATIONAL5,
			KEY_INTERNATIONAL6,
			KEY_INTERNATIONAL7,
			KEY_INTERNATIONAL8,
			KEY_INTERNATIONAL9,
			KEY_LANG1,
			KEY_LANG2,
			KEY_LANG3,
			KEY_LANG4,
			KEY_LANG5,
			KEY_LANG6,
			KEY_LANG7,
			KEY_LANG8,
			KEY_LANG9,
			KEY_ALTERASE,
			KEY_SYSREQ,
			KEY_CANCEL,
			KEY_CLEAR,
			KEY_PRIOR,
			KEY_RETURN2,
			KEY_SEPARATOR,
			KEY_OUT,
			KEY_OPER,
			KEY_CLEARAGAIN,
			KEY_CRSEL,
			KEY_EXSEL,
			KEY_KP_00,
			KEY_KP_000,
			KEY_THOUSANDSSEPARATOR,
			KEY_DECIMALSEPARATOR,
			KEY_CURRENCYUNIT,
			KEY_CURRENCYSUBUNIT,
			KEY_KP_LEFTPAREN,
			KEY_KP_RIGHTPAREN,
			KEY_KP_LEFTBRACE,
			KEY_KP_RIGHTBRACE,
			KEY_KP_TAB,
			KEY_KP_BACKSPACE,
			KEY_KP_A,
			KEY_KP_B,
			KEY_KP_C,
			KEY_KP_D,
			KEY_KP_E,
			KEY_KP_F,
			KEY_KP_XOR,
			KEY_KP_POWER,
			KEY_KP_PERCENT,
			KEY_KP_LESS,
			KEY_KP_GREATER,
			KEY_KP_AMPERSAND,
			KEY_KP_DBLAMPERSAND,
			KEY_KP_VERTICALBAR,
			KEY_KP_DBLVERTICALBAR,
			KEY_KP_COLON,
			KEY_KP_HASH,
			KEY_KP_SPACE,
			KEY_KP_AT,
			KEY_KP_EXCLAM,
			KEY_KP_MEMSTORE,
			KEY_KP_MEMRECALL,
			KEY_KP_MEMCLEAR,
			KEY_KP_MEMADD,
			KEY_KP_MEMSUBTRACT,
			KEY_KP_MEMMULTIPLY,
			KEY_KP_MEMDIVIDE,
			KEY_KP_PLUSMINUS,
			KEY_KP_CLEAR,
			KEY_KP_CLEARENTRY,
			KEY_KP_BINARY,
			KEY_KP_OCTAL,
			KEY_KP_DECIMAL,
			KEY_KP_HEXADECIMAL,
			KEY_LCTRL,
			KEY_LSHIFT,
			KEY_LALT,
			KEY_LGUI,
			KEY_RCTRL,
			KEY_RSHIFT,
			KEY_RALT,
			KEY_RGUI,
			KEY_MODE = 257,
			KEY_AUDIONEXT = 258,
			KEY_AUDIOPREV = 259,
			KEY_AUDIOSTOP = 260,
			KEY_AUDIOPLAY = 261,
			KEY_AUDIOMUTE = 262,
			KEY_MEDIASELECT = 263,
			KEY_WWW = 264,
			KEY_MAIL = 265,
			KEY_CALCULATOR = 266,
			KEY_COMPUTER = 267,
			KEY_AC_SEARCH = 268,
			KEY_AC_HOME = 269,
			KEY_AC_BACK = 270,
			KEY_AC_FORWARD = 271,
			KEY_AC_STOP = 272,
			KEY_AC_REFRESH = 273,
			KEY_AC_BOOKMARKS = 274,
			KEY_BRIGHTNESSDOWN = 275,
			KEY_BRIGHTNESSUP = 276,
			KEY_DISPLAYSWITCH = 277,
			KEY_KBDILLUMTOGGLE = 278,
			KEY_KBDILLUMDOWN = 279,
			KEY_KBDILLUMUP = 280,
			KEY_EJECT = 281,
			KEY_SLEEP = 282
		};

		enum MouseEventType {
			MOUSE_BUTTON_LEFT = 0,
			MOUSE_BUTTON_MIDDLE = 1,
			MOUSE_BUTTON_RIGHT = 2
		};

		class Input
		{
			friend class Window;
		private:
			static std::array<bool, 283> previousKeyState;
			static std::array<bool, 283> currentKeyState;

			static std::array<bool, 3> previousMouseState;
			static std::array<bool, 3> currentMouseState;

			static bool mouseMovement;
			static bool wheelRotation;
			static Vec2i mousePosition;
			static Vec2i wheelDirection;

		public:
			static void updateInputState(InputEvent& inputEvent);
			static bool KeyPressed(KeyEventType keyEvent);
			static bool KeyReleased(KeyEventType keyEvent);
			static bool keyRepeat(KeyEventType keyEvent);
			static bool MousePressed(MouseEventType mouseEvent);
			static bool MouseReleased(MouseEventType mouseEvent);
			static bool MouseRepeat(MouseEventType mouseEvent);
			static bool IsMouseMoving();
			static bool IsMouseWheelRotating();
			static const Vec2i& MousePos();
			static const Vec2i& MouseWheel();
		};

	}
}

#endif // !INPUT_SYSTEM_H