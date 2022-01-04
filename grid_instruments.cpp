#include <cmath>
#include "grid_instruments.h"

grid_instruments::grid_instruments() {
    update_variables();
}

grid_instruments::~grid_instruments() {

}

void grid_instruments::findCenterHWND() {
    RECT rect;
    GetWindowRect(hwnd, &rect);
    centerhwnd.x = (rect.right - rect.left) / 2 + rect.left;
    centerhwnd.y = (rect.bottom - rect.top) / 2 + rect.top;
}

POINT grid_instruments::get_inventory() {
    return inventory;
}

void grid_instruments::update_variables() {
    step = scale;
    step_item = step_item_def * scale;
}

int grid_instruments::find_Point_top_left_item() {
    POINT cursor;
    GetCursorPos(&cursor);
    int x = cursor.x;
    HDC dc = GetDC(0);
    COLORREF color;
    int count = 0;
    while (true) {
        color = GetPixel(dc, x, cursor.y);
        x++;
        count++;
        //std::cout << x << ':' << cursor.y <<'|' << std::hex << color << std::dec << std::endl;
        if ((color & 0x00FF0000) >= 0x00300000 && (color & 0x0000FF00) >= 0x00003000 &&
            (color & 0x000000FF) >= 0x00000030)
            if ((color & 0x00FF0000) <= 0x003d0000 && (color & 0x0000FF00) <= 0x00003d00 &&
                (color & 0x000000FF) <= 0x0000003d)
                break;
        if (count > 400)return 1;
        continue;
    }
    //c0 - cf инвентарь

    int y = cursor.y;
    count = 0;
    while (true) {
        color = GetPixel(dc, x, y);
        y--;
        //Цвет
        count++;
        //std::cout << x << ':' << y << '|' << std::hex << color << std::dec << std::endl;
        if ((color & 0x00FF0000) >= 0x00c00000 && (color & 0x0000c000) >= 0x00003000 &&
            (color & 0x000000c0) >= 0x00000030)
            if ((color & 0x00FF0000) <= 0x00cf0000 && (color & 0x0000ff00) <= 0x0000cf00 &&
                (color & 0x000000FF) <= 0x000000cf)
                break;
        if (count > 400)return 1;
    }
    x--;
    x += step;
    y += step + 2;
    int retcode = 1;
    color = GetPixel(dc, x, y);
    if ((color & 0x00FF0000) >= 0x00850000 && (color & 0x0000FF00) >= 0x00008500 && (color & 0x000000FF) >= 0x00000085)
        if ((color & 0x00FF0000) <= 0x008f0000 && (color & 0x0000FF00) <= 0x00008f00 &&
            (color & 0x000000FF) <= 0x0000008f)
            retcode = 0;
    item.x = x;
    item.y = y;
    return 0;
}

int grid_instruments::set_podzol_text(COLORREF &color) {
    podzol = color;
    return 0;
}

int grid_instruments::set_iron_text(COLORREF &color) {
    iron = color;
    return 0;
}

int grid_instruments::set_coal_text(COLORREF &color) {
    coal = color;
    return 0;
}

int grid_instruments::set_red_text(COLORREF &color) {
    red = color;
    return 0;
}

int grid_instruments::set_gold_text(COLORREF &color) {
    gold = color;
    return 0;
}

int grid_instruments::set_diamond_text(COLORREF &color) {
    diamond = color;
    return 0;
}

int grid_instruments::set_emerald_text(COLORREF &color) {
    emerald = color;
    return 0;
}

int grid_instruments::set_dirt_text(COLORREF &color) {
    dirt = color;
    return 0;
}

int grid_instruments::set_hard_dirt_text(COLORREF &color) {
    hard_dirt = color;
    return 0;
}

int grid_instruments::set_invetrory(POINT &p) {
    inventory = p;
    return 0;
}

int grid_instruments::set_invent_with_verstak(POINT &p) {
    invent_with_verstak = p;
    return 0;
}

int grid_instruments::set_verstak_craft(POINT &p) {
    verstak_craft = p;
    return 0;
}

int grid_instruments::set_verstak_result(POINT &p) {
    verstak_result = p;
    return 0;
}

int grid_instruments::set_invent_with_chest(POINT &p) {
    invent_with_chest = p;
    return 0;
}

int grid_instruments::set_chest(POINT &p) {
    chest = p;
    return 0;
}

int grid_instruments::find_invetrory() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_invetrory(p);
    return 0;
}

int grid_instruments::find_invent_with_verstak() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_invent_with_verstak(p);
    return 0;
}

int grid_instruments::find_verstak_craft() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_verstak_craft(p);
    return 0;
}

int grid_instruments::find_verstak_result() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_verstak_result(p);
    return 0;
}

int grid_instruments::find_invent_with_chest() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_invent_with_chest(p);
    return 0;
}

int grid_instruments::find_chest() {
    POINT p = calc_first_item();
    if (p.x == 0)return 1;
    set_chest(p);
    return 0;
}

int grid_instruments::find_textures() {
    HDC dc = GetDC(0);
    POINT item;
    item.y = chest.y;
    item.x = chest.x;
    COLORREF color = GetPixel(dc, item.x, item.y);
    set_emerald_text(color);
    item.x = chest.x + 1 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_diamond_text(color);
    item.x = chest.x + 2 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_gold_text(color);
    item.x = chest.x + 3 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_iron_text(color);
    item.x = chest.x + 4 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_coal_text(color);
    item.x = chest.x + 5 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_red_text(color);
    item.x = chest.x + 6 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_dirt_text(color);
    item.x = chest.x + 7 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_hard_dirt_text(color);
    item.x = chest.x + 8 * (step_item + 2 * scale);
    color = GetPixel(dc, item.x, item.y);
    set_podzol_text(color);
    return 0;
}

int grid_instruments::craft_blocks() {
    int slp = 20;
    POINT item_verstak, item_invent;
    for (int j = 0; j < 3; j++) {
        item_invent.y = invent_with_verstak.y + (step_item + 2 * scale) * j;
        for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                item_invent.x = invent_with_verstak.x + (step_item + 2 * scale) * (i * 3 + k);
                item_verstak.x = verstak_craft.x + (step_item + 2 * scale) * i;
                item_verstak.y = verstak_craft.y + (step_item + 2 * scale) * k;
                Sleep(slp);
                SetCursorPos(item_invent.x, item_invent.y);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(slp);
                SetCursorPos(item_verstak.x, item_verstak.y);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(slp);
                Sleep(slp);
            }
        }
        Sleep(slp);
        SetCursorPos(verstak_result.x, verstak_result.y);
        Sleep(slp);
        keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
        Sleep(slp);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(slp);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(slp);
        keybd_event(VK_SHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
        Sleep(slp);
        Sleep(slp);
        Sleep(slp);
    }
    return 0;
}

int grid_instruments::out_dirt() {
    int slp = 20;
    POINT item;
    HDC dc = GetDC(0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(slp);
    for (int j = 0; j < 6; ++j) {
        item.y = chest.y + j * (step_item + 2 * scale);
        for (int i = 0; i < 9; ++i) {
            item.x = chest.x + i * (step_item + 2 * scale);
            //std::cout << i << ':' << j << std::endl;
            COLORREF pix = GetPixel(dc, item.x, item.y);
            //std::cout << ((pix & 0x00FF0000)>>16)<<';'<< ((pix & 0x0000FF00)>>8)<< ';'<<(pix & 0x000000FF)<<std::endl;
            //std::cout << pix << std::endl;
            if(pix==coal||pix==dirt||pix==hard_dirt||pix==podzol) {
                SetCursorPos(item.x, item.y);
                Sleep(slp);
                keybd_event(0x51, 0, KEYEVENTF_EXTENDEDKEY, 0);
                Sleep(slp);
                keybd_event(0x51, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                Sleep(slp);

            }else if(pix==gold||pix==emerald||pix==diamond){
                    SetCursorPos(item.x, item.y);
                    Sleep(slp);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    Sleep(slp);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    Sleep(slp);

            }
        }
    }
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    return 0;
}

int grid_instruments::get_coal() {
    int slp = 20;
    POINT item;
    COLORREF coal = get_coal_text();
    HDC dc = GetDC(0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(slp);
    for (int j = 0; j < 6; ++j) {
        item.y = chest.y + j * (step_item + 2 * scale);
        for (int i = 0; i < 9; ++i) {
            item.x = chest.x + i * (step_item + 2 * scale);
            //std::cout << i << ':' << j << std::endl;
            COLORREF pix = GetPixel(dc, item.x, item.y);
            //std::cout << ((pix & 0x00FF0000)>>16)<<';'<< ((pix & 0x0000FF00)>>8)<< ';'<<(pix & 0x000000FF)<<std::endl;
            //std::cout << pix << std::endl;

            if (pix == coal) {
                SetCursorPos(item.x, item.y);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(slp);
                break;
            }
        }
    }
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    return 0;
}

int grid_instruments::get_iron() {
    int slp = 20;
    COLORREF iron = get_iron_text();
    POINT item;
    HDC dc = GetDC(0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(slp);
    for (int j = 0; j < 6; ++j) {
        item.y = chest.y + j * (step_item + 2 * scale);
        for (int i = 0; i < 9; ++i) {
            item.x = chest.x + i * (step_item + 2 * scale);
            //std::cout << i << ':' << j << std::endl;
            COLORREF pix = GetPixel(dc, item.x, item.y);
            //std::cout << ((pix & 0x00FF0000)>>16)<<';'<< ((pix & 0x0000FF00)>>8)<< ';'<<(pix & 0x000000FF)<<std::endl;
            //std::cout << pix << std::endl;

            if (pix == iron) {
                SetCursorPos(item.x, item.y);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(slp);
                break;
            }
        }
    }
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    return 0;
}

int grid_instruments::get_red() {
    COLORREF red = get_red_text();
    int slp = 20;
    POINT item;
    HDC dc = GetDC(0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(slp);
    for (int j = 0; j < 6; ++j) {
        item.y = chest.y + j * (step_item + 2 * scale);
        for (int i = 0; i < 9; ++i) {
            item.x = chest.x + i * (step_item + 2 * scale);
            //std::cout << i << ':' << j << std::endl;
            COLORREF pix = GetPixel(dc, item.x, item.y);
            //std::cout << ((pix & 0x00FF0000)>>16)<<';'<< ((pix & 0x0000FF00)>>8)<< ';'<<(pix & 0x000000FF)<<std::endl;
            //std::cout << pix << std::endl;
            if (pix == red) {
                SetCursorPos(item.x, item.y);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                Sleep(slp);
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                Sleep(slp);

            }
        }
    }
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    return 0;
}

int grid_instruments::proverka_blocks_chest() {
    int slp = 20;
    POINT item;
    HDC dc = GetDC(0);
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
    Sleep(slp);
    for (int j = 0; j < 6; ++j) {
        item.y = chest.y + j * (step_item + 2 * scale);
        for (int i = 0; i < 9; ++i) {
            item.x = chest.x + i * (step_item + 2 * scale);
            //std::cout << i << ':' << j << std::endl;
            COLORREF pix = GetPixel(dc, item.x, item.y);
            //std::cout << ((pix & 0x00FF0000)>>16)<<';'<< ((pix & 0x0000FF00)>>8)<< ';'<<(pix & 0x000000FF)<<std::endl;
            //std::cout << pix << std::endl;
            switch (pix) {
                case 3822969:
                    //земля //грубая земля
                case 1782347:
                    //Подзол
                    SetCursorPos(item.x, item.y);
                    Sleep(slp);
                    keybd_event(0x51, 0, KEYEVENTF_EXTENDEDKEY, 0);
                    Sleep(slp);
                    keybd_event(0x51, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
                    Sleep(slp);
                    break;
                case 9175039:
                    //золото
                case 9365336:
                    //изумруды
                case 15201954:
                    //алмазы
                case 14211288:
                    //Железо
                case 114:
                    //Редстоун
                case 2829099:
                    //Уголь
                    SetCursorPos(item.x, item.y);
                    Sleep(slp);
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    Sleep(slp);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                    Sleep(slp);
                    break;
            }
        }
    }
    keybd_event(VK_CONTROL, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    Sleep(slp);
    return 0;
}

COLORREF grid_instruments::get_podzol_text() {
    return podzol;
}

COLORREF grid_instruments::get_iron_text() {
    return iron;
}

COLORREF grid_instruments::get_coal_text() {
    return coal;
}

COLORREF grid_instruments::get_red_text() {
    return red;
}

COLORREF grid_instruments::get_gold_text() {
    return gold;
}

COLORREF grid_instruments::get_diamond_text() {
    return diamond;
}

COLORREF grid_instruments::get_emerald_text() {
    return emerald;
}

COLORREF grid_instruments::get_dirt_text() {
    return dirt;
}

COLORREF grid_instruments::get_hard_dirt_text() {
    return hard_dirt;
}

POINT grid_instruments::get_iventory() {
    return inventory;
}

POINT grid_instruments::get_invent_with_verstak() {
    return invent_with_verstak;
}

POINT grid_instruments::get_verstak_craft() {
    return verstak_craft;
}

POINT grid_instruments::get_verstak_result() {
    return verstak_result;
}

POINT grid_instruments::get_invent_with_chest() {
    return invent_with_chest;
}

POINT grid_instruments::get_chest() {
    return chest;
}


POINT grid_instruments::calc_first_item() {
    int retcode = 0;
    retcode = find_Point_top_left_item();
    if (retcode)return POINT();
    double x = item.x;
    double y = item.y;
    x = round(x + scale * item_stepx);
    y = round(y + scale * item_stepy);
    POINT p;
    p.x = (int) x;
    p.y = (int) y;
    return p;
}

void grid_instruments::SetHwnd(HWND hwnd) {
    this->hwnd = hwnd;
}

inline POINT grid_instruments::GetCenterHWND() {
    return centerhwnd;
}

int grid_instruments::setfile() {
    std::fstream file;
    file.open("coords.txt", std::fstream::in | std::fstream::out | std::fstream::trunc);
    bool ret = file.is_open();
    if (ret == 0)return 1;
    file << inventory.x << std::endl << inventory.y << std::endl
         << invent_with_verstak.x << std::endl << invent_with_verstak.y << std::endl
         << verstak_craft.x << std::endl << verstak_craft.y << std::endl
         << verstak_result.x << std::endl << verstak_result.y << std::endl
         << invent_with_chest.x << std::endl << invent_with_chest.y << std::endl
         << chest.x << std::endl << chest.y << std::endl << emerald << std::endl << diamond <<std::endl
         << gold << std::endl << iron << std::endl << coal << std::endl << red << std::endl
         << dirt << std::endl << hard_dirt << std::endl << podzol;
    file.close();
    return 0;
}

int grid_instruments::getfile() {
    std::fstream file("coords.txt", std::ios_base::in);
    if (!file.is_open())return 1;
    file >> inventory.x >> inventory.y
         >> invent_with_verstak.x >> invent_with_verstak.y
         >> verstak_craft.x >> verstak_craft.y
         >> verstak_result.x >> verstak_result.y
         >> invent_with_chest.x >> invent_with_chest.y
         >> chest.x >> chest.y >> emerald >> diamond
         >> gold >> iron >> coal >> red >> dirt
         >> hard_dirt >> podzol;
    return 0;
}

int grid_instruments::cout_points() {
    std::cout << "Инветарь:" << inventory.x << ';' << inventory.y << std::endl;
    std::cout << "Инветарь c верстаком:" << invent_with_verstak.x << ';' << invent_with_verstak.y << std::endl;
    std::cout << "Крафт 3x3:" << verstak_craft.x << ';' << verstak_craft.y << std::endl;
    std::cout << "Крафт:" << verstak_result.x << ';' << verstak_result.y << std::endl;
    std::cout << "Инвентарь с двойным сундуком:" << invent_with_chest.x << ';' << invent_with_chest.y << std::endl;
    std::cout << "Двойной сундук" << chest.x << ';' << chest.y << std::endl;
    std::cout << "Цвета :"<<emerald<<";"<<diamond<<";"<<gold<<";"<<iron<<";"<<coal<<";"<<red<<";"<<dirt<<";"<<hard_dirt<<";"<<podzol<<std::endl;
    return 0;
}
