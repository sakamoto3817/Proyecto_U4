#include <windows.h>
#include <string>
using namespace std;
HWND pantalla;

double n1=0;
char operador=' ';
string texto="";

void actualizar() {
    SetWindowTextA(pantalla,texto.c_str());
}

void boton(string valor) {
    if(valor=="C") {
        texto="";
        n1=0;
        operador=' ';
    }
    else if (valor=="=") {
        double n2=stod(texto);
        double res=0;

        switch (operador){
            case '+':
                res=n1+n2;
                break;
            case '-':
                res=n1-n2;
                break;
            case '*':
                res=n1*n2;
                break;
            case '/':
                if (n2==0) {
                    texto="ERROR";
                    actualizar();
                    return;
                }
                res=n1/n2;
                break;
        }

        texto=to_string(res);
        n1=res;
        operador=' ';
    }
    else if (valor=="+" || valor=="-"||valor=="*" || valor=="/") {
        n1=stod(texto);
        operador=valor[0];
        texto="";
    }
    else {
        texto+=valor;
    }
    actualizar();
}

LRESULT CALLBACK Ventana( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lparam) {
    if (msg==WM_CREATE) {
        pantalla=CreateWindowA(
            "EDIT","",
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 20, 20,290,40,
            hwnd, NULL, NULL, NULL);

        string botones[18]={
            "7","8","9","/",
            "4","5","6","*",
            "3","2","1","-",
            "0",".","+","C",
            "="
        };

        for (int i=0;i<17;i++) {
            int fila=i/4;
            int columna=i%4;

            CreateWindowA(
                "BUTTON",botones[i].c_str(),
                WS_CHILD | WS_VISIBLE,
                20+ columna*75,
                80+ fila*60,
                65,50,
                hwnd, (HMENU)(i+1),
                NULL,NULL
                );
        }
    }

    if (msg==WM_COMMAND) {
        int id=LOWORD(wParam);

        string botones[17]={
            "7","8","9","/",
            "4","5","6","*",
            "3","2","1","-",
            "0",".","+","C","="
    };
        if (id>=1 && id<=17) {
            boton(botones[id-1]);
        }
    }
    if (msg==WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wParam, lparam);
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int nCmdShow) {
    WNDCLASSA wc={};
    wc.lpfnWndProc=Ventana;
    wc.hInstance=hInst;
    wc.lpszClassName="Calculadora";

    RegisterClassA(&wc);

    HWND hwnd=CreateWindowA(
        "Calculadora","Mi Calculadora",
        WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
        100,100,350,410,
        NULL, NULL, hInst, NULL
        );

    ShowWindow(hwnd,nCmdShow);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
