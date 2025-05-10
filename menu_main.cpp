#include "menu_main.h"

namespace Tmpl8
{
    // + MAIN MENU
    Sprite img_menu_main_bg(new Surface("assets/images/menus/main_menu/img_menu_main_bg.png"), 1);
    Sprite img_menu_main_start(new Surface("assets/images/menus/main_menu/img_menu_main_start.png"), 1);
    Sprite img_menu_main_lvl1(new Surface("assets/images/menus/main_menu/img_menu_main_lvl1.png"), 1);
    Sprite img_menu_main_lvl2(new Surface("assets/images/menus/main_menu/img_menu_main_lvl2.png"), 1);
    Sprite img_menu_main_lvl3(new Surface("assets/images/menus/main_menu/img_menu_main_lvl3.png"), 1);
    Sprite img_menu_main_lvl4(new Surface("assets/images/menus/main_menu/img_menu_main_lvl4.png"), 1);
    Sprite img_menu_main_lvl5(new Surface("assets/images/menus/main_menu/img_menu_main_lvl5.png"), 1);
    Sprite img_menu_main_difficulty_easy(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_easy.png"), 1);
    Sprite img_menu_main_difficulty_medium(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_medium.png"), 1);
    Sprite img_menu_main_difficulty_hard(new Surface("assets/images/menus/main_menu/img_menu_main_difficulty_hard.png"), 1);
    Sprite img_menu_main_pro_tip(new Surface("assets/images/menus/main_menu/img_menu_main_pro_tip.png"), 1);

    // - Info panel
    Sprite img_menu_main_info_bg(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_bg.png"), 1);
    Sprite img_menu_main_info_info(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_info.png"), 1);
    Sprite img_menu_main_info_info_alt(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_info_alt.png"), 1);
    Sprite img_menu_main_info_quit(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_quit.png"), 1);
    Sprite img_menu_main_info_quit_alt(new Surface("assets/images/menus/main_menu/info/img_menu_main_info_quit_alt.png"), 1);

    // - Hover
    Sprite img_menu_main_start_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_start_alt.png"), 1);
    Sprite img_menu_main_lvl1_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl1_alt.png"), 1);
    Sprite img_menu_main_lvl2_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl2_alt.png"), 1);
    Sprite img_menu_main_lvl3_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl3_alt.png"), 1);
    Sprite img_menu_main_lvl4_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl4_alt.png"), 1);
    Sprite img_menu_main_lvl5_alt(new Surface("assets/images/menus/main_menu/hover/img_menu_main_lvl5_alt.png"), 1);
    Sprite img_menu_main_difficulty_easy_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_easy_hover.png"), 1);
    Sprite img_menu_main_difficulty_medium_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_medium_hover.png"), 1);
    Sprite img_menu_main_difficulty_hard_hover(new Surface("assets/images/menus/main_menu/hover/img_menu_main_difficulty_hard_hover.png"), 1);

    // - Selected
    Sprite img_selected(new Surface("assets/images/UI/img_selected.png"), 1);

    void MenuMain::drawMainBGPan(Surface* screen, float deltaTime)
    {
        float panning_speed = 150.0f;
        float bg_width = img_menu_main_bg.GetWidth();

        main_bg_x += panning_speed * deltaTime;

        if (main_bg_x >= bg_width) main_bg_x -= bg_width;

        img_menu_main_bg.Draw(screen, -main_bg_x, 0);
        img_menu_main_bg.Draw(screen, -main_bg_x + bg_width, 0);
    }

    void MenuMain::openMainMenu(Surface* screen, float deltaTime)
    {
        if (!mainMenuOpen) return;

        drawMainBGPan(screen, deltaTime);
        img_menu_main_pro_tip.Draw(screen, 7, SCREEN_HEIGHT - img_menu_main_pro_tip.GetHeight() - 7);

        audioOpen = true;
        quitOpen = true;
        audioManagerOpen(screen);
        quitManagerOpen(screen);

        // Level buttons
        Sprite* lvl_hover_list[5] = { &img_menu_main_lvl1_alt, &img_menu_main_lvl2_alt, &img_menu_main_lvl3_alt, &img_menu_main_lvl4_alt, &img_menu_main_lvl5_alt };
        Sprite* lvl_list[5] = { &img_menu_main_lvl1, &img_menu_main_lvl2, &img_menu_main_lvl3, &img_menu_main_lvl4, &img_menu_main_lvl5 };
        int lvl_list_X[5] = { MAIN_LVL1_X, MAIN_LVL2_X, MAIN_LVL3_X, MAIN_LVL4_X, MAIN_LVL5_X };

        // Difficulty buttons
        Sprite* difficulty_hover_list[3] = { &img_menu_main_difficulty_easy_hover, &img_menu_main_difficulty_medium_hover, &img_menu_main_difficulty_hard_hover };
        Sprite* difficulty_list[3] = { &img_menu_main_difficulty_easy, &img_menu_main_difficulty_medium, &img_menu_main_difficulty_hard };
        int difficulty_X[3] = { MAIN_EASY_X, MAIN_MEDIUM_X, MAIN_HARD_X };

        // Variables to track button hover state
        //static bool wasHoveringLevel[5] = { false };
        //static bool wasHoveringDifficulty[3] = { false };
        //static bool wasHoveringStart = false;
        //static bool wasHoveringInfo = false;

        // Level buttons loop
        for (int i = 0; i < 5; i++)
        {
            handleButton(
                screen,
                lvl_list_X[i], MAIN_LVLS_Y,
                MAIN_LVL_WIDTH, MAIN_LVL_HEIGHT,
                lvl_list[i], lvl_hover_list[i],
                wasHoveringLevel[i],
                [&]() {
                    manageLevelSelect(i);
                    score = 0.0f;
                    timer_current = 0.0f;
                });
        }

        // Difficulty buttons loop
        for (int i = 0; i < 3; i++)
        {
            handleButton(
                screen,
                difficulty_X[i], MAIN_DIFFICULTIES_Y,
                MAIN_DIFFICULTY_WIDTH, MAIN_DIFFICULTY_HEIGHT,
                difficulty_list[i], difficulty_hover_list[i],
                wasHoveringDifficulty[i],
                [&]() {
                    manageDifficultySelect(i);
                });

            // Draw the selected difficulty marker
            if (difficulty == i + 1)
            {
                static float totalTime = 0.0f;
                float floating_time = 2.0f;
                float amplitude = 5.0f;
                vec2 draw_pos = vec2(
                    difficulty_X[i] + MAIN_DIFFICULTY_WIDTH / 2 - img_selected.GetWidth() / 2,
                    MAIN_DIFFICULTIES_Y + MAIN_DIFFICULTY_HEIGHT + 10.0f
                );
                totalTime += deltaTime;
                draw_pos.y += sin((totalTime / floating_time) * 2.0f * PI) * amplitude - 4.0f;
                img_selected.Draw(screen, draw_pos);
            }
        }

        // Start button hover logic
        handleButton(
            screen,
            MAIN_START_X, MAIN_START_Y,
            MAIN_START_WIDTH, MAIN_START_HEIGHT,
            &img_menu_main_start, &img_menu_main_start_alt,
            wasHoveringStart,
            [&]() {
                manageLevelSelect(0);
                score = 0;
                timer_current = 0.0f;
            });

        // Info button hover logic
        /*static bool wasMousePressedLastFrame = false;*/
        handleButton(
            screen,
            MAIN_INFO_X, MAIN_INFO_Y,
            MAIN_INFO_WIDTH, MAIN_INFO_HEIGHT,
            &img_menu_main_info_info, &img_menu_main_info_info_alt,
            wasHoveringInfo,
            [&]() {
                if (isMousePressed && !wasMousePressedLastFrame)
                {
                    gamesound.playSound(gamesound.snd_select);
                    infoMenuOpen = true;
                }
            });

        // Open the info menu
        openInfoMenu(screen, deltaTime);

        // Store mouse pressed state for next frame
        wasMousePressedLastFrame = isMousePressed;
    }

    void MenuMain::openInfoMenu(Surface* screen, float deltaTime)
    {
        if (!infoMenuOpen) return;

        img_menu_main_info_bg.Draw(screen, SCREEN_HALF_WIDTH - MAIN_INFO_BG_WIDTH / 2, SCREEN_HALF_HEIGHT - MAIN_INFO_BG_HEIGHT / 2);

        // Handle the Quit button
        //static bool wasMousePressedLastFrame = false;
        //static bool wasHoveringQuit = false;

        handleButton(
            screen,
            MAIN_INFO_QUIT_X, MAIN_INFO_QUIT_Y,
            MAIN_INFO_QUIT_WIDTH, MAIN_INFO_QUIT_HEIGHT,
            &img_menu_main_info_quit_alt,
            &img_menu_main_info_quit,
            wasHoveringQuit,
            [&]() {
                if (isMousePressed && !wasMousePressedLastFrame) {
                    gamesound.playSound(gamesound.snd_select);
                    infoMenuOpen = false;
                }
            }
        );

        wasMousePressedLastFrame = isMousePressed;
    }
}

