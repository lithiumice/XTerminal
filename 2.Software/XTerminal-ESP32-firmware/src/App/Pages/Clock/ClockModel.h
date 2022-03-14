#pragma once
#include "App/Utils/AccountSystem/Account.h"
#include "App/Accounts/Account_Master.h"
#include "lvgl.h"
#include "type.h"
#include "mesh_cube.h"

#define CANVAS_W 50

namespace Page
{
	class ClockModel
	{
	private:
        Account* account;

        Matrix4 m_world;
		Vector3i mesh_rotation = { 0, 0, 0 };
		Vector3i mesh_position = { 0, 0, 0 };

		int proj_nodes[NODECOUNT][2];    // projected nodes (x,y)

	public:
		void draw_vertex( uint16_t color, lv_obj_t* canvas);
		void draw_wireframe( uint16_t color, lv_obj_t* canvas);
		void draw_flat_color(const int(*n)[2], uint16_t color, lv_obj_t* canvas);
		void clear_dirty(const int(*n)[2], lv_obj_t* canvas);

        void  Init();
		void Update(lv_obj_t* canvas);
	};
}

