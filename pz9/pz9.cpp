#include <iostream>

using namespace std;

// Варіант 5 
// Y = (8 * х2 + 12 * х – 7) / (3 * x + 25), X = 4

int main()
{
    setlocale(LC_ALL, "ukr");
    long RES[7], X = 4;

    _asm {                          
        lea EBX, RES                ; завантаження адреси результатів в регістр EBX
        mov ECX, 7                  ; рахівник кількості повторень циклу
    m1: mov EAX, 3                  ; EAX = 3 , Розташування початку циклу
        imul X                      ; EAX = 3 * x
        add EAX, 25                 ; EAX = 3 * x + 25
        mov EDI, EAX                ; пересилання знаменника в регістр EDI
        mov EAX, 8                  ; EAX = x
        imul X                      ; EAX = x ^ 2
        imul X                      ; EAX = x ^ 2 * 8
        mov EDX, X                  ; EDX = 4
        imul EDX, 12                ; EDX = 4 * 12
        sub EDX, 7                  ; EDX = 4 * 12 - 7
        add EAX, EDX                ; EAX = x ^ 2 * 8 + 12 * 4 - 7
        cdq                         ; розширення операнда - ділимого в EAX - EDX
        div EDI                     ; часне – EAX, залишок – EDX
        shr EDI, 1                  ; ділення знаменника на 2
        cmp EDI, EDX                ; порівняння половини дільника з залишком
        adc EAX, 0                  ; додавання до часного заєму від порівняння
        mov dword ptr[EBX], EAX     ; пересилання результату в пам’ять
        add EBX, 4                  ; збільшення адреси результатів
        add X, 3                    ; збільшення аргументу
        loop m1                     ; зациклення по рахівнику в ECX
    }
    cout << "Результат Асемблеру: " << endl;
    for (int i = 0; i < 7; i++) {
        cout << RES[i] << " ";
    }
    cout << endl;

    int num = 4;

    cout << "Результат С++: " << endl;

    for (int i = 0; i < 7; i++) {
        
        double x = pow(num, 2) * 8 + 12 * num - 7;
        double y = 3 * num + 25;

        cout << x / y << " ";

        num += 3;
    }

}
