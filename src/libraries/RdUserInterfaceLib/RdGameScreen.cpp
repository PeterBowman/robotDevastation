
#include "RdGameScreen.hpp"

const SDL_Color rd::RdGameScreen::greencolor = {0, 255, 0, 0};
const SDL_Color rd::RdGameScreen::redcolor =   {255, 0, 0, 0};

rd::RdGameScreen::RdGameScreen()
{
    /// \todo Fix this

    //-- Setup SDL
    //----------------------------------------------------------------------------------------
    // Load SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        RD_ERROR("Unable to initialize SDL: %s\n", SDL_GetError());
        return;
    }
    atexit(SDL_Quit); // Clean it up nicely :)

    //-- Init ttf
    if (TTF_Init() == -1)
    {
      RD_ERROR("Unable to initialize SDL_ttf: %s \n", TTF_GetError());
      return;
    }

    //-- Load the font(s)
    char * font_name = "/usr/share/fonts/truetype/freefont/FreeMono.ttf";
    player_font = TTF_OpenFont(font_name, 12);
    if (player_font == NULL)
    {
        RD_ERROR("Unable to load font: %s %s \n", font_name, TTF_GetError());
        return;
    }

    enemy_font = TTF_OpenFont(font_name, 12);
    if (enemy_font == NULL)
    {
        RD_ERROR("Unable to load font: %s %s \n", font_name, TTF_GetError());
        return;
    }

    mentalMap = 0;
}

void rd::RdGameScreen::show(SDL_Surface *screen)
{
    //-- Get a copy of the enemies stored & draw them:
    std::vector<RdEnemy> enemies_stored  = mentalMap->getEnemies();
    for (int i = 0; i < (int) enemies_stored.size(); i++)
    {
        RdPlayer player_data = mentalMap->getPlayer(enemies_stored[i].getPlayerId());
        drawTargetUI(screen, enemies_stored[i], player_data);
    }

    //-- Get a copy of the players stored & draw them:
    std::vector<RdPlayer> players_stored = mentalMap->getPlayers();
    for ( int i = 0; i < (int) players_stored.size(); i++)
    {
        drawPlayerUI(screen, players_stored[i], 5, 10+i*(PLAYER_NAME_H+3));
    }

    //-- Draw scope:
    drawScope(screen);
}

void rd::RdGameScreen::setMentalMap(RdMentalMap *mentalMap)
{
    this->mentalMap = mentalMap;
}

bool rd::RdGameScreen::drawPlayerUI(SDL_Surface *screen, RdPlayer player, int x, int y)
{
    //-- Player interface:
    SDL_Surface * text_surface = TTF_RenderText_Solid(player_font, player.getName().c_str(), greencolor );
    SDL_Rect text_rect = {x, y, PLAYER_NAME_W, PLAYER_NAME_H};
    SDL_BlitSurface(text_surface, NULL, screen, &text_rect);

    //-- Health bar:
    SDL_Rect health_bar = {x+PLAYER_NAME_W, y, HEALTH_BAR_W, HEALTH_BAR_H };
    SDL_Rect current_health = {x+PLAYER_NAME_W,
                               y,
                               (int)(HEALTH_BAR_W*player.getHealth() / (float) player.getMaxHealth()),
                               HEALTH_BAR_H };

    SDL_FillRect(screen, &health_bar, SDL_MapRGB(screen->format, 0, 127, 0));
    SDL_FillRect(screen, &current_health, SDL_MapRGB(screen->format, 0, 255, 0));

    SDL_FreeSurface(text_surface);
    return true;
}

bool rd::RdGameScreen::drawTargetUI(SDL_Surface *screen, RdEnemy enemy, RdPlayer player_data)
{
    //-- Put enclosing box:
    SDL_Rect enemy_rect_top = { enemy.getPos().x, enemy.getPos().y,
                                enemy.getDimensions().x, ENEMY_THICKNESS };
    SDL_FillRect(screen, &enemy_rect_top, SDL_MapRGB(screen->format, 255, 0, 0));

    SDL_Rect enemy_rect_bottom = { enemy.getPos().x, enemy.getPos().y + enemy.getDimensions().y - ENEMY_THICKNESS,
                                   enemy.getDimensions().x, ENEMY_THICKNESS};
    SDL_FillRect(screen, &enemy_rect_bottom, SDL_MapRGB(screen->format, 255, 0, 0));

    SDL_Rect enemy_rect_left = { enemy.getPos().x, enemy.getPos().y,
                                 ENEMY_THICKNESS, enemy.getDimensions().y};
    SDL_FillRect(screen, &enemy_rect_left, SDL_MapRGB(screen->format, 255, 0, 0));

    SDL_Rect enemy_rect_right = { enemy.getPos().x + enemy.getDimensions().x - ENEMY_THICKNESS, enemy.getPos().y,
                                  ENEMY_THICKNESS, enemy.getDimensions().y};
    SDL_FillRect(screen, &enemy_rect_right, SDL_MapRGB(screen->format, 255, 0, 0));

    //-- Put enemy name:
    SDL_Surface * text_surface = TTF_RenderText_Solid(enemy_font, player_data.getName().c_str(), redcolor);
    SDL_Rect text_rect = { enemy.getPos().x, enemy.getPos().y - 15,
                           enemy.getDimensions().x, 15};
    SDL_Rect source_rect = {0, 0, enemy.getDimensions().x, 15};
    SDL_BlitSurface(text_surface, &source_rect, screen, &text_rect);

    //-- Put enemy health bar:
    SDL_Rect health_bar = { enemy.getPos().x,
                            enemy.getPos().y + enemy.getDimensions().y + 5,
                            enemy.getDimensions().x,
                            5 };
    SDL_FillRect(screen, &health_bar, SDL_MapRGB(screen->format, 127, 0, 0));

    SDL_Rect current_health = { enemy.getPos().x,
                                enemy.getPos().y + enemy.getDimensions().y + 5,
                                (int)(enemy.getDimensions().x *player_data.getHealth() / (float) player_data.getMaxHealth()),
                                5 };
    SDL_FillRect(screen, &current_health, SDL_MapRGB(screen->format, 255, 0, 0));

    SDL_FreeSurface(text_surface);
    return true;
}

bool rd::RdGameScreen::drawScope(SDL_Surface *screen)
{
    SDL_Rect scope_v_rect_top = { (int)(SCREEN_WIDTH  / 2 - SCOPE_VERT_W  / 2),
                                  (int)(SCREEN_HEIGHT / 2 - SCOPE_VERT_H  / 2),
                                  SCOPE_VERT_W,
                                  (int)(SCOPE_VERT_H / 2 - SCOPE_VERT_H_SPACE / 2) };
    SDL_FillRect(screen, &scope_v_rect_top, SDL_MapRGB(screen->format, 0, 0, 255));

    SDL_Rect scope_v_rect_bottom = { (int)(SCREEN_WIDTH  / 2 - SCOPE_VERT_W  / 2),
                                     (int)(SCREEN_HEIGHT / 2 + SCOPE_VERT_H_SPACE / 2),
                                     SCOPE_VERT_W,
                                     (int)(SCOPE_VERT_H / 2 - SCOPE_VERT_H_SPACE / 2) };
    SDL_FillRect(screen, &scope_v_rect_bottom, SDL_MapRGB(screen->format, 0, 0, 255));

    SDL_Rect scope_h_rect_left = { (int) (SCREEN_WIDTH  / 2 - SCOPE_HORIZ_W  / 2),
                                   (int) (SCREEN_HEIGHT / 2 - SCOPE_HORIZ_H  / 2),
                                   (int) (SCOPE_HORIZ_W / 2 - SCOPE_HORIZ_W_SPACE / 2),
                                   SCOPE_HORIZ_H };
    SDL_FillRect(screen, &scope_h_rect_left, SDL_MapRGB(screen->format, 0, 0, 255));

    SDL_Rect scope_h_rect_right = { (int) (SCREEN_WIDTH  / 2 + SCOPE_HORIZ_W_SPACE / 2),
                                    (int) (SCREEN_HEIGHT / 2 - SCOPE_HORIZ_H  / 2),
                                    (int) (SCOPE_HORIZ_W / 2 - SCOPE_HORIZ_W_SPACE / 2),
                                    SCOPE_HORIZ_H };
    SDL_FillRect(screen, &scope_h_rect_right, SDL_MapRGB(screen->format, 0, 0, 255));

    return true;
}
