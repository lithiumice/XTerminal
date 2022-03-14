#ifndef __Pictures_VIEW_H
#define __Pictures_VIEW_H

#include <string>

#include "../Page.h"

namespace Page
{

	class PicturesView
	{
	public:
		void GuiInit();
		void GuiInit(lv_obj_t* root);
		// void ListAddItem(lv_obj_t* list, const char* icon, const char* name);
		void ListAddText(lv_obj_t* list, const char* name);
		void Create(lv_obj_t* root);
		void Delete();

	public:
		struct
		{
#define SET_DEF(icon,className)\
		lv_obj_t* className;

#define SET_DEF2(className) 

#include "_Setting_DEF.inc"
#undef SET_DEF2
#undef SET_DEF

			lv_obj_t* list1;
			lv_obj_t* btn;
			lv_obj_t* spinbox;
			lv_group_t* group;
		} ui;

	};

}

#endif // !__VIEW_H
