#ifndef __Terminal_VIEW_H
#define __Terminal_VIEW_H

#include <string>

#include "../Page.h"

namespace Page
{

	class TerminalView
	{
	public:
		void SetTermText(std::string termText);
		void Create(lv_obj_t* root);
		void Delete();

	public:
		struct
		{
			// lv_obj_t* labelTitle;
			// lv_obj_t* labelTick;
			lv_obj_t* termTextLabel;
			lv_group_t* group;
			
		} ui;

	};

}

#endif // !__VIEW_H
