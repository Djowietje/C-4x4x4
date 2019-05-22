#ifndef WINDOWS_HPP
#define WINDOWS_HPP
#include <Windows.h>
#endif

#ifndef KEYHANDLER_HPP
#define KEYHANDLER_HPP
#include "KeyHandler.hpp"
static KeyHandler* keyHandlerPtr = new KeyHandler();
#endif

#ifndef MOUSEHANDLER_HPP
#define MOUSEHANDLER_HPP
#include "MouseHandler.hpp"
static MouseHandler* mouseHandlerPtr = new MouseHandler();
#endif

#ifndef MESSAGEHANDLER_HPP
#define MESSAGEHANDLER_HPP
#include "MessageHandler.hpp"
static MessageHandler* messageHandlerPtr = new MessageHandler();
#endif // !MESSAGEHANDLER_HPP

#ifndef IOSTREAM
#define IOSTREAM
#include <iostream>
#endif

#ifndef PROGRAM_NAME
#define PROGRAM_NAME
static const char* pName = "CPP 4x4x4";
#endif

#ifndef WINDOW_HPP
#define WINDOW_HPP
#include "Window.hpp"
#endif // !WINDOW_HPP

