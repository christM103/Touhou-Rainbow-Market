#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

namespace TR {
	struct TextBoxInfo {
        
        int textbox_speed;
        int textbox_style;
        bool textbox_confirm;
        std::unordered_set<std::string> textbox_prompts;

        TextBoxInfo(int txtSp = 1, int txtSt = 0, bool txtCon = false, const char* p1 = "", 
            const char* p2 = "", const char* p3 = "", const char* p4 = "")
        : textbox_speed(txtSp), textbox_style(txtSt), textbox_confirm(txtCon) { 
            if (std::empty(p1))
        
        }

	};
}