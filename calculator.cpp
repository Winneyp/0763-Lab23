#include <windows.h>
#include <stdio.h>
HWND textfield,textbox[2];
char textsave1[20],textsave2[20];
double ftxt1=0,ftxt2=0;
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		case WM_CREATE:{
			textfield = CreateWindow("STATIC",
									"Please input two numbers",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									20,20,200,25, // x,y position,word width,word height
									hwnd,NULL,NULL,NULL);
			textbox[0]	= CreateWindowW(L"EDIT",L"",WS_VISIBLE|WS_BORDER|WS_CHILD,
									20,55,200,25,
									hwnd,NULL,NULL,NULL);
			textbox[1]	= CreateWindowW(L"EDIT",L"",WS_VISIBLE|WS_BORDER|WS_CHILD,
									20,85,200,25,
									hwnd,NULL,NULL,NULL);
			CreateWindow("BUTTON","+",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									25,120,35,35,
									hwnd,(HMENU) 1,NULL,NULL);
			CreateWindow("BUTTON","-",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									75,120,35,35,
									hwnd,(HMENU) 2,NULL,NULL);
			CreateWindow("BUTTON","*",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									125,120,35,35,
									hwnd,(HMENU) 3,NULL,NULL);
			CreateWindow("BUTTON","/",
									WS_VISIBLE|WS_CHILD|WS_BORDER,
									175,120,35,35,
									hwnd,(HMENU) 4,NULL,NULL);	
			
			break;
		}

		case WM_COMMAND:{
			GetWindowText(textbox[0],&textsave1[0],20);
			GetWindowText(textbox[1],&textsave2[0],20);
			ftxt1 = atof(textsave1);
			ftxt2 = atof(textsave2);
			switch (LOWORD(wParam)){
				case 1:
					sprintf(textsave1,"%f",ftxt1+ftxt2);
					::MessageBox(hwnd,textsave1,"Button was clicked",MB_OK);
					break;
				case 2:
					sprintf(textsave1,"%f",ftxt1-ftxt2);
					::MessageBox(hwnd,textsave1,"Button was clicked",MB_OK);
					break;
				case 3:
					sprintf(textsave1,"%f",ftxt1*ftxt2);
					::MessageBox(hwnd,textsave1,"Button was clicked",MB_OK);
					break;
				case 4:
					sprintf(textsave1,"%f",ftxt1/ftxt2);
					::MessageBox(hwnd,textsave1,"Button was clicked",MB_OK);
					break;
				default :

					break;
			}
			break;
		}
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(27);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_MINIMIZEBOX|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}