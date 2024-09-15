#include <stdio.h>
#include <Windows.h>

int main()
{
  WNDCLASSW wc = {}; //Create a WNDCLASSW (window class) structure so we can give window info (most variables can be null)
  wc.lpszClassName = L"dummyclassnamebecauseicouldntthinkofanythingmorecreative"; //The class name cannot be null
  wc.lpfnWndProc = DefWindowProcW; //This points to a function which will handle window messages (function pointer).

  RegisterClassExW(&wc); //Register the window class structure with Windows so that the OS knows a new window is about to drop in

  //Actually create the window
  CreateWindowW(
    L"dummyclassnamebecauseicouldntthinkofanythinmorecreative", //Class name paramter should be straight forward enough... use same one that's in WNDCLASSW struct
    L"cool window text that the user will see", //The text on the window title that the user will see
    WS_OVERLAPPEDWINDOW, WS_VISIBLE, //Window styles that we want: WS_OVERLAPPEDWINDOW has the generic styles (title bar, close button, minimize button, etc.); WS_VISIBLE is there because we want the user to see the window
    CW_USEDEFAULT, //Horizontal position of the window (CW_USEDEFAULT means we let the system decide)
    CW_USEDEFAULT, //Vertical position of the window (let system decide)
    700, //Window width: we want it to be 700px WIDE
    500, //Window height: we want it to be 500px TALL
    NULL, //There isn't anybody to be the window's parent (I guess you could try to make the console window the parent, but we prb don't want to see the console window IRL)
    NULL, //Simple example without WinMain() won't have an hInstance we can rip out from main() args
    NULL, //lpParam is not needed in most simple instances
    );

  //Now we want the window to stay open and have the DefWindowProcW() function be able to handle events (messages); we will create a message pump/loop to do that

  MSG msg; //Create a MSG struct to contain message details
  while(GetMessage(&msg, NULL, 0, 0)) //there are better ways to write this loop, but it will work for now
  //GetMessage() function needs to fill out the MSG struct, so put that in for 1st arg; NULL in 2nd arg tells function to get messages from all windows that we created (so just 1 rn); 0 for 3rd and 4th args mean get 'em all (no msg filtering)
    {
      TranslateMessage(&msg); //translate any keyboard messages into actual characters (textboxes and stuff won't work without this)
      DispatchMessage(&msg); //dispatch the message to the window procedure (DefWindowProcW())
    }

  //Now we should have a nice window
}
