#define BUFFER_SIZE 16384

typedef struct renderer {
	unsigned texbo;
	unsigned vertbo;
	unsigned colbo;
	unsigned indbo;
	unsigned trans;
	unsigned sca;
} renderer;

typedef struct storage {
	unsigned      w;
	unsigned      h;
	unsigned      bi;
	unsigned      ind[BUFFER_SIZE * 6];
	float	      uv[BUFFER_SIZE * 8];
	float	      xy[BUFFER_SIZE * 8];
	unsigned char rgba[BUFFER_SIZE * 16];
} storage;

void r_init(renderer *);
void r_begin(renderer *, storage *, unsigned, unsigned);
void r_draw_rect(renderer *, storage *, mu_Rect, mu_Color);
void r_draw_text(renderer *, storage *, const char *, mu_Vec2, mu_Color);
void r_draw_icon(renderer *, storage *, int, mu_Rect, mu_Color);
void r_set_clip_rect(renderer *, storage *, mu_Rect);
void r_clear(renderer *, storage *, mu_Color);
void r_present(renderer *, storage *);
int  r_get_text_width(const char *, int);
int  r_get_text_height(void);
