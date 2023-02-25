#ifndef BILIBILILIVEPROTOCOL_IMWINDOW_H
#define BILIBILILIVEPROTOCOL_IMWINDOW_H

#include "../DataStruct/DataStruct.h"

class ImWindow {
private:
    UserInputT userInput;

    /// imgui part
    WNDCLASSEXW wc; // ����
    HWND hwnd; // ���ھ��

    /// imgui part

public:
    ImWindow();

    bool showInputWindow();

    ~ImWindow();
};


#endif //BILIBILILIVEPROTOCOL_IMWINDOW_H
