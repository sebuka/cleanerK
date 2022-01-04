#include "Windows.h"
#include "Windowsx.h"
#include "iostream"
#include "sstream"
#include "Ctype.h"
#include "grid_instruments.h"
#include "conio.h"

HHOOK _hook = 0;

HHOOK _mouse, _kbhook, inst_hook;
bool mouse_hook_set = 0;
bool lctrl_is_down = 0;

LRESULT CALLBACK Hookproc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_LBUTTONUP) {
            tagMSLLHOOKSTRUCT *st = (tagMSLLHOOKSTRUCT *) lParam;
            int x = st->pt.x, y = st->pt.y;
            std::stringstream ss;
            ss << x;
            ss << ':';
            ss << y;
            ss << std::endl;
            std::cout << ss.str();
            HDC dc = GetDC(NULL);
            COLORREF color = GetPixel(dc, x, y);
            COLORREF red = color & 0x000000FF;
            COLORREF green = color & 0x0000FF00;
            green = green >> 8;
            COLORREF blue = color & 0x00FF0000;
            blue = blue >> 16;
            ReleaseDC(NULL, dc);
            std::cout << "color: " << red << "," << green << "," << blue << std::endl;
            std::cout << "colorint: " << color << std::endl;
            //std::cout << "colorint: " << std::hex<<color << std::endl;

        }
    }
    // call the next hook in the hook chain. This is nessecary or your hqsook chain will break and the hook stops
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void MouseHook() {
    if (!(_mouse = SetWindowsHookExA(WH_MOUSE_LL, Hookproc, NULL, 0))) {
        MessageBox(NULL, "Failed to install _hook!", "Error", MB_ICONERROR);
    }
}

LRESULT CALLBACK shift_keybord(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0) return CallNextHookEx(_hook, nCode, wParam, lParam);
    tagKBDLLHOOKSTRUCT *key;
    if (wParam == WM_KEYDOWN) {
        //std::cout << "key_down"<<std::endl;
        key = (tagKBDLLHOOKSTRUCT *) lParam;
        //std::cout << key->vkCode << std::endl;
        if (key->vkCode == VK_LSHIFT) {
            if (mouse_hook_set == 0) {
                std::cout << "shift_down" << std::endl;
                MouseHook();
                mouse_hook_set = 1;
            }
        }
    }
    if (wParam == WM_KEYUP) {
        key = (tagKBDLLHOOKSTRUCT *) lParam;
        if (key->vkCode == VK_LSHIFT) {
            std::cout << "shift_up" << std::endl;
            UnhookWindowsHookEx(_mouse);
            mouse_hook_set = 0;
        }
    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void KBHook() {
    if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, shift_keybord, NULL, 0))) {
        MessageBox(NULL, "Failed to install _hook!", "Error", MB_ICONERROR);
    }
}

POINT grid_instruments::item = POINT();
POINT grid_instruments::verstak = POINT();
POINT grid_instruments::centerhwnd = POINT();
POINT grid_instruments::inventory = POINT();
POINT grid_instruments::invent_with_verstak = POINT();
POINT grid_instruments::verstak_craft = POINT();
POINT grid_instruments::verstak_result = POINT();
POINT grid_instruments::invent_with_chest = POINT();
POINT grid_instruments::chest = POINT();

COLORREF grid_instruments::dirt = 3822969;
COLORREF grid_instruments::coal = 2829099;
COLORREF grid_instruments::iron = 14211288;
COLORREF grid_instruments::gold = 9175039;
COLORREF grid_instruments::diamond = 15201954;
COLORREF grid_instruments::emerald = 9365336;
COLORREF grid_instruments::red = 114;
COLORREF grid_instruments::podzol = 1782347;
COLORREF grid_instruments::hard_dirt = 3822969;

LRESULT CALLBACK keyboard(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0)return CallNextHookEx(_kbhook, nCode, wParam, lParam);
    //std::cout << "keybord" << std::endl;
    switch (wParam) {
        case WM_KEYDOWN: {
            tagKBDLLHOOKSTRUCT *key = (tagKBDLLHOOKSTRUCT *) lParam;
            //std::cout << key->vkCode << std::endl;
            switch (key->vkCode) {
                case VK_LCONTROL: {
                    lctrl_is_down = 1;
                    //std::cout << "ctrl_down";
                    break;
                }
            }
            break;
        }
        case WM_KEYUP: {
            //std::cout << "keybord" << ((tagKBDLLHOOKSTRUCT*)lParam)->vkCode << std::endl;
            tagKBDLLHOOKSTRUCT *key = (tagKBDLLHOOKSTRUCT *) lParam;
            grid_instruments inst;
            if (key->vkCode == VK_LCONTROL) {
                lctrl_is_down = 0;
                break;
            }
            //switch (key->vkCode) {
            //case VK_NUMPAD5:
            //	grid_instruments inst;
            //	inst.craft_blocks();
            //	break;
            //}
            if (lctrl_is_down)
                switch (key->vkCode) {
                    case 0x5A: {//z key

                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_invetrory()) {
                            std::cout << "Ошибка" << std::endl;
                            break;
                        }
                        std::cout << "инвентарь установлен" << std::endl;
                        POINT buf = inst.get_inventory();
                        SetCursorPos(buf.x, buf.y);
                        break;

                    }
                    case 0x58://xkey
                    {
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_invent_with_verstak()) {
                            std::cout << "Ошибка" << std::endl;
                            break;
                        }
                        std::cout << "инвентарь c с верстаком установлен" << std::endl;
                        POINT buf = inst.get_invent_with_verstak();
                        SetCursorPos(buf.x, buf.y);
                        break;
                    }
                    case 0x43: {//c-key
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_verstak_craft()) {
                            std::cout << "Ошибка" << std::endl;
                            //break;
                        }
                        std::cout << "верстаком установлен" << std::endl;
                        POINT buf = inst.get_verstak_craft();
                        SetCursorPos(buf.x, buf.y);
                        break;
                    }
                    case 0x56://vkey
                    {
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_verstak_result()) {
                            std::cout << "Ошибка" << std::endl;
                            break;
                        }
                        std::cout << "верстаком крафт установлен" << std::endl;
                        POINT buf = inst.get_verstak_result();
                        SetCursorPos(buf.x, buf.y);
                        break;

                    }
                    case 0x42://bkey
                    {
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_invent_with_chest()) {
                            std::cout << "Ошибка" << std::endl;
                            break;
                        }
                        std::cout << "инвентарь с честом установлен" << std::endl;
                        POINT buf = inst.get_invent_with_chest();
                        SetCursorPos(buf.x, buf.y);
                        break;
                    }
                    case 0x4e://nkey
                    {
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_chest()) {
                            std::cout << "Ошибка" << std::endl;
                            break;
                        }
                        std::cout << "честк установлен" << std::endl;
                        POINT buf = inst.get_chest();
                        SetCursorPos(buf.x, buf.y);
                        break;
                    }
                    case 0x54://t-key
                    {
                        grid_instruments inst;
                        inst.SetHwnd(GetForegroundWindow());
                        if (inst.find_textures()) {
                            std::cout << "Ошибка" << std::endl;
                        }
                        std::cout << " Текстуры установлены";
                        break;
                    }
                    case 0x41://a-key
                    {
                        grid_instruments inst;
                        if (inst.setfile())std::cout << "Ошибка записи" << std::endl;
                        std::cout << "Данные записаны" << std::endl;

                        break;
                    }
                    case 0x53://skey
                    {
                        grid_instruments inst;
                        if (inst.getfile())std::cout << "Ошибка чтения" << std::endl;
                        std::cout << "Данные установлены" << std::endl;
                        inst.cout_points();
                        break;
                    }
                    case 0x45: {
                        UnhookWindowsHookEx(_hook);
                        std::cout << "Выход из настроек";
                        return CallNextHookEx(_kbhook, nCode, wParam, lParam);
                    }
                }

        }
            break;
    }
    return CallNextHookEx(_kbhook, nCode, wParam, lParam);
}

bool settings = 1;

LRESULT CALLBACK keyboard_instruments(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode < 0)return CallNextHookEx(_kbhook, nCode, wParam, lParam);
    tagKBDLLHOOKSTRUCT *key = (tagKBDLLHOOKSTRUCT *) lParam;
    grid_instruments inst;
    switch (wParam) {
        case WM_KEYUP: {
            if (key->vkCode == VK_NUMPAD5) {
                //grid_instruments inst;
                inst.craft_blocks();
                break;
            }
            if (key->vkCode == VK_NUMPAD0) {
                if (settings) {
                    _hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard, NULL, 0);
                    std::cout << "Настройки включены" << std::endl;
                    std::cout << "ctrl +z инвентарь" << std::endl;
                    std::cout << "ctrl +x инвентарь c верстаком" << std::endl;
                    std::cout << "ctrl +с вестак" << std::endl;
                    std::cout << "ctrl +v крафт верстака" << std::endl;
                    std::cout << "ctrl +b инвентарь c сундуком" << std::endl;
                    std::cout << "ctrl +n сундук" << std::endl;
                    std::cout << "ctrl +t установить текстуры(после сундука)" << std::endl;
                    std::cout << "ctrl +a записать " << std::endl;
                    std::cout << "ctrl +s загрузить" << std::endl;
                    settings = 0;
                } else {
                    UnhookWindowsHookEx(_hook);
                    settings = 1;
                    std::cout << "Настройки выключены" << std::endl;
                }
            }
            if (key->vkCode == VK_NUMPAD1) {
                inst.out_dirt();
            }
            if (key->vkCode == VK_NUMPAD2) {
                inst.get_red();
            }
            if (key->vkCode == VK_NUMPAD3) {
                inst.get_iron();
            }
            if (key->vkCode == VK_NUMPAD4) {
                inst.get_coal();
            }
        }
    }
    return CallNextHookEx(_kbhook, nCode, wParam, lParam);
}

int main(void) {
    SetConsoleOutputCP(1251);
    std::cout << "mouseecents_start" << std::endl;
    std::cout << "Интерфейс крупный" << std::endl;
    std::cout << "NumPad0 настройки" << std::endl;
    std::cout << "NumPad1 чистка" << std::endl;
    std::cout << "NumPad2 редстоун" << std::endl;
    std::cout << "NumPad3 жлезо" << std::endl;
    std::cout << "NumPad4 уголь" << std::endl;
    std::cout << "NumPad5 крафт" << std::endl;
    std::cout << u8"Сделано StasLin007x6. Контакт: https://vk.com/staslina";
    MSG msg;
    std::string str;

    inst_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyboard_instruments, NULL, 0);
    //bool proverka = 1;
    //while (proverka) {
    grid_instruments inst;
    inst.getfile();
    inst.cout_points();
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        //if(_kbhit())
        //{
        //	if (_getch() == 's') {
        //		if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, keybord, NULL, 0)))
        //		{
        //			MessageBox(NULL, "Failed to install _hook!", "Error", MB_ICONERROR);
        //			std::cout << "Установка настроек ошибка влкючения" << std::endl;
        //		}
        //		else {
        //			std::cout << "Установка настроек включена" << std::endl;
        //		}
        //	}
        //}
    }
    std::cout << "mouseevents_stop";
}
