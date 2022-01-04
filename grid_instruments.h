#pragma once

#include "Windows.h"
#include "iostream"
#include "fstream"

class grid_instruments {
public:
    POINT testp;

    grid_instruments();

    ~grid_instruments();

    void findCenterHWND();

    POINT get_inventory();

    //void set_scale(int scale);s
    void update_variables();

    int find_Point_top_left_item();

    int craft_blocks();

    int out_dirt();

    int get_coal();

    int get_iron();

    int get_red();

    int proverka_blocks_chest();

    int set_podzol_text(COLORREF &);

    int set_dirt_text(COLORREF &);

    int set_hard_dirt_text(COLORREF &);

    int set_iron_text(COLORREF &);

    int set_red_text(COLORREF &);

    int set_diamond_text(COLORREF &);

    int set_gold_text(COLORREF &);

    int set_emerald_text(COLORREF &);

    int set_coal_text(COLORREF &);

    int set_invetrory(POINT &);

    int set_invent_with_verstak(POINT &);

    int set_verstak_craft(POINT &);

    int set_verstak_result(POINT &);

    int set_invent_with_chest(POINT &);

    int set_chest(POINT &);

    int find_invetrory();

    int find_invent_with_verstak();

    int find_verstak_craft();

    int find_verstak_result();

    int find_invent_with_chest();

    int find_chest();

    int find_textures();

    COLORREF get_podzol_text();

    COLORREF get_dirt_text();

    COLORREF get_hard_dirt_text();

    COLORREF get_iron_text();

    COLORREF get_red_text();

    COLORREF get_diamond_text();

    COLORREF get_gold_text();

    COLORREF get_emerald_text();

    COLORREF get_coal_text();

    POINT get_iventory();

    POINT get_invent_with_verstak();

    POINT get_verstak_craft();

    POINT get_verstak_result();

    POINT get_invent_with_chest();

    POINT get_chest();

    POINT calc_first_item();

    void SetHwnd(HWND hwnd);

    POINT GetCenterHWND();

    int setfile();

    int getfile();

    int cout_points();

private:
    bool chest_open;
    int scale = 3;
    int step_item_def = 16;
    int step, step_item;
    HWND hwnd;

    static POINT item;
    static POINT verstak;
    static POINT centerhwnd;
    //Инвентарь
    static POINT inventory;
    //Верстак
    static POINT invent_with_verstak;
    static POINT verstak_craft;
    static POINT verstak_result;
    //Чест
    static POINT invent_with_chest;
    static POINT chest;
    static COLORREF dirt;
    static COLORREF coal;
    static COLORREF iron;
    static COLORREF gold;
    static COLORREF diamond;
    static COLORREF emerald;
    static COLORREF red;
    static COLORREF podzol;
    static COLORREF hard_dirt;
    double item_stepx = 7.3333;
    double item_stepy = 5.3333;
};

