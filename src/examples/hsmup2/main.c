#include "cross_lib.h"

/* ============================================================
 *  HORIZONTAL SHOOTER - Cross-Lib / ANSI C89
 * ============================================================ */

#define MAX_BULLETS     16
#define MAX_ENEMIES     16
#define MAX_EBULLETS    12
#define MAX_POWERUPS     4
#define FIRE_COOLDOWN    4
#define INVINCIBLE_TICKS 300
#define ENEMY_FIRE_CD   12

/* Tile / colour assignments – player is 2x2, enemy is 2x1 */
#define T_PLAYER_TL  _TILE_1    /* player top-left       */
#define T_PLAYER_TR  _TILE_6    /* player top-right      */
#define T_PLAYER_BL  _TILE_0    /* player bottom-left    */
#define T_PLAYER_BR  _TILE_26   /* player bottom-right   */
#define C_PLAYER     _XL_CYAN
#define T_ENEMY_L    _TILE_2    /* enemy front (faces player) */
#define T_ENEMY_R    _TILE_7    /* enemy rear/engine         */
#define C_ENEMY      _XL_RED
#define T_BULLET     _TILE_3
#define C_BULLET     _XL_YELLOW
#define T_POWERUP    _TILE_4
#define C_POWERUP    _XL_GREEN
#define T_EBULLET    _TILE_5
#define C_EBULLET    _XL_MAGENTA

/* Power-up types */
#define PU_DOUBLE     0
#define PU_SPREAD     1
#define PU_INVINCIBLE 2
#define PU_POINTS     3

/* Screen buffer – tracks what is currently displayed at each cell */
static uint8_t scr[XSize][YSize];

/* ---------- entity arrays (no heap) ---------- */

typedef struct {
    uint8_t x, y;
    int8_t  dx, dy;
    uint8_t active;
} Bullet;

typedef struct {
    uint8_t x, y;   /* left-edge position; occupies (x,y) and (x+1,y) */
    int8_t  dx, dy;
    uint8_t fire_cd;
    uint8_t active;
} Enemy;

typedef struct {
    uint8_t x, y;
    uint8_t type;
    uint8_t active;
} PowerUp;

static Bullet   bullets[MAX_BULLETS];
static Enemy    enemies[MAX_ENEMIES];
static Bullet   ebullets[MAX_EBULLETS];
static PowerUp  powerups[MAX_POWERUPS];

/* ---------- player state ---------- */
static uint8_t px, py; /* top-left of 2x2; occupies (px,py),(px+1,py),(px,py+1),(px+1,py+1) */
static uint8_t lives;
static uint8_t power_level;
static uint8_t fire_timer;
static uint16_t invincible;
static uint16_t score;
static uint8_t tick;

/* ---------- helpers ---------- */

static void clear_scr(void)
{
    uint8_t x, y;
    for (x = 0; x < XSize; x++) {
        for (y = 0; y < YSize; y++) {
            if (scr[x][y] != 0) {
                _XL_DELETE(x, y);
                scr[x][y] = 0;
            }
        }
    }
}

static void set_cell(uint8_t x, uint8_t y, uint8_t tile, uint8_t color)
{
    if (x >= XSize || y >= YSize) return;
    if (scr[x][y] != tile) {
        _XL_DRAW(x, y, tile, color);
        scr[x][y] = tile;
    }
}

static void clear_cell(uint8_t x, uint8_t y)
{
    if (x >= XSize || y >= YSize) return;
    if (scr[x][y] != 0) {
        _XL_DELETE(x, y);
        scr[x][y] = 0;
    }
}

/* Draw 2x2 player at top-left (x,y) */
static void draw_player(uint8_t x, uint8_t y, uint8_t color)
{
    set_cell(x,     y,     T_PLAYER_TL, color);
    set_cell(x + 1, y,     T_PLAYER_TR, color);
    set_cell(x,     y + 1, T_PLAYER_BL, color);
    set_cell(x + 1, y + 1, T_PLAYER_BR, color);
}

/* Clear all 4 cells of 2x2 player at (x,y) */
static void clear_player(uint8_t x, uint8_t y)
{
    clear_cell(x,     y);
    clear_cell(x + 1, y);
    clear_cell(x,     y + 1);
    clear_cell(x + 1, y + 1);
}

/* Clear old 2x2 cells that are NOT inside the new 2x2 at (nx,ny) */
static void clear_player_diff(uint8_t ox, uint8_t oy, uint8_t nx, uint8_t ny)
{
    uint8_t cx, cy;
    for (cy = 0; cy < 2; cy++) {
        for (cx = 0; cx < 2; cx++) {
            uint8_t cellx = ox + cx;
            uint8_t celly = oy + cy;
            if (cellx < nx || cellx > (uint8_t)(nx + 1) ||
                celly < ny || celly > (uint8_t)(ny + 1)) {
                clear_cell(cellx, celly);
            }
        }
    }
}

/* Draw 2-cell horizontal enemy at (x,y) */
static void draw_enemy(uint8_t x, uint8_t y)
{
    set_cell(x,     y, T_ENEMY_L, C_ENEMY);
    set_cell(x + 1, y, T_ENEMY_R, C_ENEMY);
}

/* Clear both cells of 2-cell enemy at (x,y) */
static void clear_enemy(uint8_t x, uint8_t y)
{
    clear_cell(x,     y);
    clear_cell(x + 1, y);
}

/* Clear old enemy cells NOT inside the new 2-cell at (nx,ny) */
static void clear_enemy_diff(uint8_t ox, uint8_t oy, uint8_t nx, uint8_t ny)
{
    if (!((ox == nx || ox == (uint8_t)(nx + 1)) && oy == ny)) {
        clear_cell(ox, oy);
    }
    if (!((ox + 1 == nx || ox + 1 == (uint8_t)(nx + 1)) && oy == ny)) {
        clear_cell(ox + 1, oy);
    }
}

/* ---------- game reset ---------- */

static void reset_game(void)
{
    uint8_t i;
    px = 2;
    py = YSize / 2;
    lives = 3;
    power_level = 1;
    fire_timer = 0;
    invincible = 0;
    score = 0;
    tick = 0;

    for (i = 0; i < MAX_BULLETS; i++)   bullets[i].active = 0;
    for (i = 0; i < MAX_ENEMIES; i++)   enemies[i].active = 0;
    for (i = 0; i < MAX_EBULLETS; i++)  ebullets[i].active = 0;
    for (i = 0; i < MAX_POWERUPS; i++)  powerups[i].active = 0;

    clear_scr();
}

/* ---------- spawn helpers ---------- */

static uint8_t find_bullet_slot(void)
{
    uint8_t i;
    for (i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) return i;
    }
    return 255;
}

static uint8_t find_enemy_slot(void)
{
    uint8_t i;
    for (i = 0; i < MAX_ENEMIES; i++) {
        if (!enemies[i].active) return i;
    }
    return 255;
}

static uint8_t find_ebullet_slot(void)
{
    uint8_t i;
    for (i = 0; i < MAX_EBULLETS; i++) {
        if (!ebullets[i].active) return i;
    }
    return 255;
}

static uint8_t find_powerup_slot(void)
{
    uint8_t i;
    for (i = 0; i < MAX_POWERUPS; i++) {
        if (!powerups[i].active) return i;
    }
    return 255;
}

/* ---------- fire player bullets ---------- */

static void fire_player(void)
{
    uint8_t slot;

    /* Level 1: single straight from top-right */
    slot = find_bullet_slot();
    if (slot < MAX_BULLETS && px + 2 < XSize) {
        bullets[slot].x = px + 2;
        bullets[slot].y = py;
        bullets[slot].dx = 1;
        bullets[slot].dy = 0;
        bullets[slot].active = 1;
    }

    if (power_level >= 2) {
        slot = find_bullet_slot();
        if (slot < MAX_BULLETS && py + 1 < YSize && px + 2 < XSize) {
            bullets[slot].x = px + 2;
            bullets[slot].y = py + 1;
            bullets[slot].dx = 1;
            bullets[slot].dy = 0;
            bullets[slot].active = 1;
        }
    }

    if (power_level >= 3) {
        slot = find_bullet_slot();
        if (slot < MAX_BULLETS && py > 0 && px + 2 < XSize) {
            bullets[slot].x = px + 2;
            bullets[slot].y = py;
            bullets[slot].dx = 1;
            bullets[slot].dy = -1;
            bullets[slot].active = 1;
        }
    }

    if (power_level >= 4) {
        slot = find_bullet_slot();
        if (slot < MAX_BULLETS && py + 2 < YSize && px + 2 < XSize) {
            bullets[slot].x = px + 2;
            bullets[slot].y = py + 1;
            bullets[slot].dx = 1;
            bullets[slot].dy = 1;
            bullets[slot].active = 1;
        }
    }

    _XL_SHOOT_SOUND();
}

/* ---------- spawn enemy ---------- */

static void spawn_enemy(void)
{
    uint8_t slot, r;
    int8_t dy;

    slot = find_enemy_slot();
    if (slot >= MAX_ENEMIES) return;

    enemies[slot].x = XSize - 2;
    r = (uint8_t)(_XL_RAND() % YSize);
    enemies[slot].y = r;

    if (_XL_RAND() % 10 < 3) {
        dy = (_XL_RAND() & 1) ? -1 : 1;
        enemies[slot].dy = dy;
    } else {
        enemies[slot].dy = 0;
    }
    enemies[slot].dx = -1;
    enemies[slot].fire_cd = ENEMY_FIRE_CD + (uint8_t)(_XL_RAND() % 10);
    enemies[slot].active = 1;
}

/* ---------- spawn power-up ---------- */

static void spawn_powerup(void)
{
    uint8_t slot, r;

    slot = find_powerup_slot();
    if (slot >= MAX_POWERUPS) return;

    powerups[slot].x = XSize - 1;
    r = (uint8_t)(_XL_RAND() % YSize);
    powerups[slot].y = r;
    powerups[slot].type = (uint8_t)(_XL_RAND() % 4);
    powerups[slot].active = 1;
}

/* ---------- main game tick ---------- */

static void update(void)
{
    uint8_t input, i, j;
    uint8_t old_px, old_py;
    uint16_t r;
    int8_t ady;

    tick++;

    /* --- player movement (save old pos for diff-clear) --- */
    old_px = px;
    old_py = py;

    input = _XL_INPUT();
    if (_XL_UP(input) && py > 0)                       py--;
    else if (_XL_DOWN(input) && py + 1 < YSize - 1)    py++;
    if (_XL_LEFT(input) && px > 0)                      px--;
    else if (_XL_RIGHT(input) && px + 1 < XSize - 1)   px++;

    /* clear only the old cells not covered by the new 2x2 */
    if (old_px != px || old_py != py) {
        clear_player_diff(old_px, old_py, px, py);
    }

    /* --- player fire --- */
    if (fire_timer > 0) fire_timer--;
    if (_XL_FIRE(input) && fire_timer == 0) {
        fire_player();
        fire_timer = FIRE_COOLDOWN;
    }

    /* --- invincibility countdown --- */
    if (invincible > 0) invincible--;

    /* --- move player bullets --- */
    for (i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;
        {
            short nx = (short)bullets[i].x + (short)bullets[i].dx;
            short ny = (short)bullets[i].y + (short)bullets[i].dy;
            if (nx < 0 || nx >= (short)XSize || ny < 0 || ny >= (short)YSize) {
                clear_cell(bullets[i].x, bullets[i].y);
                bullets[i].active = 0;
            } else {
                clear_cell(bullets[i].x, bullets[i].y);
                bullets[i].x = (uint8_t)nx;
                bullets[i].y = (uint8_t)ny;
            }
        }
    }

    /* --- move enemy bullets --- */
    for (i = 0; i < MAX_EBULLETS; i++) {
        if (!ebullets[i].active) continue;
        {
            short nx = (short)ebullets[i].x + (short)ebullets[i].dx;
            short ny = (short)ebullets[i].y + (short)ebullets[i].dy;
            if (nx < 0 || nx >= (short)XSize || ny < 0 || ny >= (short)YSize) {
                clear_cell(ebullets[i].x, ebullets[i].y);
                ebullets[i].active = 0;
            } else {
                clear_cell(ebullets[i].x, ebullets[i].y);
                ebullets[i].x = (uint8_t)nx;
                ebullets[i].y = (uint8_t)ny;
            }
        }
    }

    /* --- move enemies: every 2 ticks --- */
    if ((tick & 1) == 0) {
        for (i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) continue;
            {
                short nx, ny;
                ady = enemies[i].dy;
                if (ady != 0 && (enemies[i].y < 4 || enemies[i].y > YSize - 5)) {
                    ady = 0;
                }
                nx = (short)enemies[i].x + (short)enemies[i].dx;
                ny = (short)enemies[i].y + (short)ady;

                if (nx < 0 || nx >= (short)(XSize - 1) || ny < 0 || ny >= (short)YSize) {
                    /* off-screen: clear tiles fully and deactivate */
                    clear_enemy(enemies[i].x, enemies[i].y);
                    enemies[i].active = 0;
                } else {
                    /* diff-clear: only remove old cells not in new position */
                    clear_enemy_diff(enemies[i].x, enemies[i].y,
                                    (uint8_t)nx, (uint8_t)ny);
                    enemies[i].x = (uint8_t)nx;
                    enemies[i].y = (uint8_t)ny;
                    draw_enemy(enemies[i].x, enemies[i].y);
                }
            }

            /* enemy fire from its front */
            if (enemies[i].active) {
                if (enemies[i].fire_cd > 0) {
                    enemies[i].fire_cd--;
                } else {
                    j = find_ebullet_slot();
                    if (j < MAX_EBULLETS && enemies[i].x > 0) {
                        ebullets[j].x = enemies[i].x - 1;
                        ebullets[j].y = enemies[i].y;
                        ebullets[j].dx = -1;
                        if (_XL_RAND() % 5 == 0) {
                            ebullets[j].dy = (_XL_RAND() & 1) ? -1 : 1;
                        } else {
                            ebullets[j].dy = 0;
                        }
                        ebullets[j].active = 1;
                    }
                    enemies[i].fire_cd = ENEMY_FIRE_CD + (uint8_t)(_XL_RAND() % 8);
                }
            }
        }
    }

    /* --- move power-ups: every 3 ticks --- */
    if ((tick % 3) == 0) {
        for (i = 0; i < MAX_POWERUPS; i++) {
            if (!powerups[i].active) continue;
            clear_cell(powerups[i].x, powerups[i].y);
            if (powerups[i].x > 0) {
                powerups[i].x--;
            } else {
                powerups[i].active = 0;
            }
        }
    }

    /* --- collisions: player bullets vs enemies --- */
    for (i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;
        for (j = 0; j < MAX_ENEMIES; j++) {
            if (!enemies[j].active) continue;
            if ((bullets[i].x == enemies[j].x || bullets[i].x == (uint8_t)(enemies[j].x + 1))
                && bullets[i].y == enemies[j].y) {
                clear_cell(bullets[i].x, bullets[i].y);
                bullets[i].active = 0;
                clear_enemy(enemies[j].x, enemies[j].y);
                enemies[j].active = 0;
                score += 10;
                _XL_PING_SOUND();
                break;
            }
        }
    }

    /* --- collisions: enemy bullets vs player (2x2) --- */
    if (invincible == 0) {
        for (i = 0; i < MAX_EBULLETS; i++) {
            if (!ebullets[i].active) continue;
            if ((ebullets[i].x == px || ebullets[i].x == (uint8_t)(px + 1))
                && (ebullets[i].y == py || ebullets[i].y == (uint8_t)(py + 1))) {
                clear_cell(ebullets[i].x, ebullets[i].y);
                ebullets[i].active = 0;
                lives--;
                power_level = 1;
                invincible = INVINCIBLE_TICKS;
                _XL_EXPLOSION_SOUND();
                break;
            }
        }
    }

    /* --- collisions: enemies vs player (2x1 vs 2x2) --- */
    if (invincible == 0) {
        for (i = 0; i < MAX_ENEMIES; i++) {
            if (!enemies[i].active) continue;
            if ((enemies[i].y == py || enemies[i].y == (uint8_t)(py + 1))
                && enemies[i].x <= (uint8_t)(px + 1)
                && (uint8_t)(enemies[i].x + 1) >= px) {
                clear_enemy(enemies[i].x, enemies[i].y);
                enemies[i].active = 0;
                lives--;
                power_level = 1;
                invincible = INVINCIBLE_TICKS;
                _XL_EXPLOSION_SOUND();
                break;
            }
        }
    }

    /* --- collisions: player vs power-ups (2x2) --- */
    for (i = 0; i < MAX_POWERUPS; i++) {
        if (!powerups[i].active) continue;
        if ((powerups[i].x == px || powerups[i].x == (uint8_t)(px + 1))
            && (powerups[i].y == py || powerups[i].y == (uint8_t)(py + 1))) {
            clear_cell(powerups[i].x, powerups[i].y);
            powerups[i].active = 0;
            switch (powerups[i].type) {
                case PU_DOUBLE:
                    if (power_level < 2) power_level++;
                    else score += 5;
                    break;
                case PU_SPREAD:
                    if (power_level < 4) power_level = (power_level >= 3) ? 4 : 3;
                    else score += 10;
                    break;
                case PU_INVINCIBLE:
                    invincible = INVINCIBLE_TICKS;
                    break;
                case PU_POINTS:
                    score += 50;
                    break;
            }
            _XL_TOCK_SOUND();
        }
    }

    /* --- spawn logic --- */
    r = _XL_RAND();
    if (r % 20 == 0) {
        spawn_enemy();
    }
    if (r % 150 == 0) {
        spawn_powerup();
    }

    /* --- render all active entities --- */
    for (i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active && bullets[i].x < XSize && bullets[i].y < YSize) {
            set_cell(bullets[i].x, bullets[i].y, T_BULLET, C_BULLET);
        }
    }
    for (i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active && (uint8_t)(enemies[i].x + 1) < XSize && enemies[i].y < YSize) {
            draw_enemy(enemies[i].x, enemies[i].y);
        }
    }
    for (i = 0; i < MAX_EBULLETS; i++) {
        if (ebullets[i].active && ebullets[i].x < XSize && ebullets[i].y < YSize) {
            set_cell(ebullets[i].x, ebullets[i].y, T_EBULLET, C_EBULLET);
        }
    }
    for (i = 0; i < MAX_POWERUPS; i++) {
        if (powerups[i].active && powerups[i].x < XSize && powerups[i].y < YSize) {
            set_cell(powerups[i].x, powerups[i].y, T_POWERUP, C_POWERUP);
        }
    }

    /* player – blink when invincible */
    if (invincible > 0) {
        if ((invincible / 4) % 2 == 0) {
            draw_player(px, py, _XL_WHITE);
        } else {
            clear_player(px, py);
        }
    } else {
        draw_player(px, py, C_PLAYER);
    }

    /* --- HUD --- */
    _XL_SET_TEXT_COLOR(_XL_WHITE);
    {
        char buf[16];
        uint8_t k;
        uint16_t s = score;

        if (s >= 10000) {
            buf[0] = '0' + (char)(s / 10000);
            buf[1] = '0' + (char)((s / 1000) % 10);
            buf[2] = '0' + (char)((s / 100) % 10);
            buf[3] = '0' + (char)((s / 10) % 10);
            buf[4] = '0' + (char)(s % 10);
            buf[5] = '\0';
        } else if (s >= 1000) {
            buf[0] = '0' + (char)((s / 1000) % 10);
            buf[1] = '0' + (char)((s / 100) % 10);
            buf[2] = '0' + (char)((s / 10) % 10);
            buf[3] = '0' + (char)(s % 10);
            buf[4] = '\0';
        } else if (s >= 100) {
            buf[0] = '0' + (char)((s / 100) % 10);
            buf[1] = '0' + (char)((s / 10) % 10);
            buf[2] = '0' + (char)(s % 10);
            buf[3] = '\0';
        } else if (s >= 10) {
            buf[0] = '0' + (char)((s / 10) % 10);
            buf[1] = '0' + (char)(s % 10);
            buf[2] = '\0';
        } else {
            buf[0] = '0' + (char)s;
            buf[1] = '\0';
        }
        _XL_PRINT(0, 0, buf);

        for (k = 0; k < lives && k < 5; k++) {
            set_cell(2 + k * 2,     0, T_PLAYER_TL, C_PLAYER);
            set_cell(2 + k * 2 + 1, 0, T_PLAYER_TR, C_PLAYER);
        }
        for (k = lives; k < 5; k++) {
            clear_cell(2 + k * 2,     0);
            clear_cell(2 + k * 2 + 1, 0);
        }

        _XL_SET_TEXT_COLOR(_XL_GREEN);
        {
            char pbuf[8];
            pbuf[0] = 'P';
            pbuf[1] = '0' + (char)power_level;
            pbuf[2] = '\0';
            _XL_PRINT(XSize - 4, 0, pbuf);
        }
    }
}

/* ---------- game over screen ---------- */

static void show_game_over(void)
{
    uint8_t input;
    clear_scr();
    _XL_SET_TEXT_COLOR(_XL_RED);
    _XL_PRINT(2, YSize / 2 - 1, "GAME OVER");
    _XL_SET_TEXT_COLOR(_XL_WHITE);
    {
        char buf[16];
        uint16_t s = score;
        if (s >= 1000) {
            buf[0] = '0' + (char)(s / 1000);
            buf[1] = '0' + (char)((s / 100) % 10);
            buf[2] = '0' + (char)((s / 10) % 10);
            buf[3] = '0' + (char)(s % 10);
        } else if (s >= 100) {
            buf[0] = '0' + (char)(s / 100);
            buf[1] = '0' + (char)((s / 10) % 10);
            buf[2] = '0' + (char)(s % 10);
            buf[3] = '\0';
        } else if (s >= 10) {
            buf[0] = '0' + (char)(s / 10);
            buf[1] = '0' + (char)(s % 10);
            buf[2] = '\0';
        } else {
            buf[0] = '0' + (char)s;
            buf[1] = '\0';
        }
        buf[4] = '\0';
        _XL_PRINT(2, YSize / 2, buf);
    }
    _XL_SET_TEXT_COLOR(_XL_CYAN);
    _XL_PRINT(1, YSize / 2 + 2, "FIRE TO RESTART");

    while (1) {
        input = _XL_INPUT();
        if (_XL_FIRE(input)) break;
        _XL_SLOW_DOWN(_XL_SLOW_DOWN_FACTOR);
    }
}

/* ---------- main ---------- */

int main(void)
{
    _XL_INIT_GRAPHICS();
    _XL_INIT_INPUT();
    _XL_INIT_SOUND();

    while (1) {
        reset_game();
        while (lives > 0) {
            update();
            _XL_SLOW_DOWN(_XL_SLOW_DOWN_FACTOR);
        }
        show_game_over();
    }

    return 0;
}