return {
    name = "zerov1",
    caption = "ZeroV1",

    cbf_formspec = function(tabview, name, tabdata)
        local fs = ""
        fs = fs .. "style[zv1_title;border=false;font=bold;font_size=+8;textcolor=#00CCFF]"
        fs = fs .. "button[0.5,0.5;8,0.9;zv1_title;ZeroV1 Client]"
        fs = fs .. "style[zv1_desc;border=false;textcolor=#FFFFFF]"
        fs = fs .. "button[0.5,1.6;14,0.7;zv1_desc;This client was created by ZeroPlus to improve the gameplay experience.]"
        fs = fs .. "style[zv1_cmds;border=false;textcolor=#AAAAAA]"
        fs = fs .. "button[0.5,2.5;14,0.7;zv1_cmds;Commands: .fov  .armor  .hitbox  .fovscroll  .help]"
        fs = fs .. "style[zv1_mods;border=false;textcolor=#88FF88]"
        fs = fs .. "button[0.5,3.3;14,0.7;zv1_mods;Client mods supported - place mods in: clientmods/ folder]"
        fs = fs .. "style[zv1_contact;border=false;textcolor=#FFCC44]"
        fs = fs .. "button[0.5,4.1;14,0.7;zv1_contact;Contact: hameerghazi11@gmail.com]"
        return fs
    end,

    cbf_button_handler = function(this, fields, name, tabdata)
    end,

    on_change = function(type)
        if type == "ENTER" then
            mm_game_theme.set_engine()
        end
    end,
}
