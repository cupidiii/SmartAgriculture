#include "menuConfig.h"
#include "menu.h"
#include "dispDirver.h"
#include "image.h"
#include "application.h"


/* Page*/
xPage Home_Page, System_Page, Data_page;
/* item */
xItem HomeHead_Item, SystemHead_Item, DataHead_Item, System_Item, Image_Item, Github_Item, Bilibili_Item;
xItem Contrast_Item, Power_Item, Humidity_Item, Temperatyue_Item, Soil_Item, Air_Item, Light_Item;
xItem Data_Item, H_curve_Item, T_curve_Item, S_curve_Item, A_curve_Item, L_curve_Item;



extern int temperature, humidity, light, soil, air;

/**
 * 在此建立所需显示或更改的数据
 * 无参数
 * 无返回值
 */
void Create_Parameter(void)
{
    static int Contrast = 255;
    static data_t Contrast_data;
    Contrast_data.name = "Contrast";
    Contrast_data.ptr = &Contrast;
    Contrast_data.function = OLED_SetContrast;
    Contrast_data.Function_Type = STEP_EXECUTE;
    Contrast_data.Data_Type = DATA_INT;
    Contrast_data.Operate_Type = READ_WRITE;
    Contrast_data.max = 255;
    Contrast_data.min = 0;
    Contrast_data.step = 2;
    static element_t Contrast_element;
    Contrast_element.data = &Contrast_data;
    Create_element(&Contrast_Item, &Contrast_element);

    static uint8_t power = true;
    static data_t Power_switch_data;
    Power_switch_data.ptr = &power;
    Power_switch_data.function = OLED_SetPowerSave;
    Power_switch_data.Data_Type = DATA_SWITCH;
    Power_switch_data.Operate_Type = READ_WRITE;
    static element_t Power_element;
    Power_element.data = &Power_switch_data;
    Create_element(&Power_Item, &Power_element);

    static data_t  H_curve_data;
    H_curve_data.name="H_curve_data";
    H_curve_data.unit="%";
    H_curve_data.ptr=&humidity;
    H_curve_data.Data_Type=DATA_INT;
    H_curve_data.max=1023;
    H_curve_data.min=0;
    static element_t H_curve_element;
    H_curve_element.data=&H_curve_data;
    Create_element(&H_curve_Item, &H_curve_element);
    
    static data_t  T_curve_data;
    T_curve_data.name="T_curve_data";
    T_curve_data.unit="C";
    T_curve_data.ptr=&temperature;
    T_curve_data.Data_Type=DATA_INT;
    T_curve_data.max=99;
    T_curve_data.min=0;
    static element_t T_curve_element;
    T_curve_element.data=&T_curve_data;
    Create_element(&T_curve_Item, &T_curve_element);

    static data_t  S_curve_data;
    S_curve_data.name="S_curve_data";
    S_curve_data.unit="%";
    S_curve_data.ptr=&soil;
    S_curve_data.Data_Type=DATA_INT;
    S_curve_data.max=1023;
    S_curve_data.min=0;
    static element_t S_curve_element;
    S_curve_element.data=&S_curve_data;
    Create_element(&S_curve_Item, &S_curve_element);

    static data_t A_curve_data;
    A_curve_data.name = "A_curve_data";
    A_curve_data.ptr = &air;
    A_curve_data.Data_Type = DATA_INT;
    A_curve_data.max=1023;
    A_curve_data.min=0;
    static element_t A_curve_element;
    A_curve_element.data = &A_curve_data;
    Create_element(&A_curve_Item, &A_curve_element);

    static data_t L_curve_data;
    L_curve_data.name = "L_curve_data";
    L_curve_data.unit="Lx";
    L_curve_data.ptr = &light;
    L_curve_data.Data_Type = DATA_INT;
    L_curve_data.max=1023;
    L_curve_data.min=0;
    static element_t L_curve_element;
    L_curve_element.data = &L_curve_data;
    Create_element(&L_curve_Item, &L_curve_element);
}

/**
 * 在此建立所需显示或更改的文本
 * 无参数
 * 无返回值
 */
void Create_Text(void)
{
    
}

/*
 * 菜单构建函数
 * 该函数不接受参数，也不返回任何值。
 * 功能：静态地构建一个菜单系统。
 */
void Create_MenuTree(xpMenu Menu)
{
    AddPage("[HomePage]", &Home_Page, IMAGE);
        AddItem("[HomePage]", LOOP_FUNCTION, NULL, &HomeHead_Item, &Home_Page, NULL, Application::Draw_Home);
        AddItem(" +System", PARENTS, logo_allArray[2], &System_Item, &Home_Page, &System_Page, NULL);
            AddPage("[System]", &System_Page, TEXT);
                AddItem("[System]", RETURN, NULL, &SystemHead_Item, &System_Page, &Home_Page, NULL);
                AddItem(" -Contrast", DATA, NULL, &Contrast_Item, &System_Page, NULL, NULL);
                AddItem(" -Power", DATA, NULL, &Power_Item, &System_Page, NULL, NULL);               
        AddItem(" -Image", LOOP_FUNCTION, logo_allArray[3], &Image_Item, &Home_Page, NULL, Application::Show_Logo);
        AddItem(" -H_curve", WAVE, logo_allArray[6], &H_curve_Item, &Home_Page, NULL, NULL);
        AddItem(" -T_curve", WAVE, logo_allArray[7], &T_curve_Item, &Home_Page, NULL, NULL);
        AddItem(" -S_curve", WAVE, logo_allArray[4], &S_curve_Item, &Home_Page, NULL, NULL);
        AddItem(" -A_curve", WAVE, logo_allArray[1], &A_curve_Item, &Home_Page, NULL, NULL);
        AddItem(" -L_curve", WAVE, logo_allArray[5], &L_curve_Item, &Home_Page, NULL, NULL);          
}

void Menu_Init(xpMenu Menu)
{
    Disp_Init();
    Create_Menu(Menu, &HomeHead_Item);
    Application::Draw_Home(NULL);
}
