#include <assert.h>
#include "microui.h"
#include "renderer.h"
#include "atlas.inl"
#include "gl.h"
void
r_init(renderer *r)
{
	memset(r, 0, sizeof(*r));
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	GLuint t;
	glGenTextures(1, &t);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, ATLAS_WIDTH, ATLAS_HEIGHT, 0,
	    GL_RED, GL_UNSIGNED_BYTE, atlas_texture);

	GLint		    st;
	const GLchar *const vss =
	    "#version 100\n"
	    "precision mediump float;\n"
	    "uniform mat4 trans;\n"
	    "uniform vec2 sca;\n"
	    "attribute vec2 axy;\n"
	    "attribute vec2 auv;\n"
	    "attribute vec4 argba;\n"
	    "varying vec2 vuv;\n"
	    "varying vec4 vrgba;\n"
	    "void main()\n"
	    "{\n"
	    "    gl_Position = trans * vec4(axy.x, axy.y, 0.0, 1.0);\n"
	    "    vuv = auv*sca;\n"
	    "    vrgba = argba;\n"
	    "}\n";
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vss, 0);
	glCompileShader(vs);
	glGetShaderiv(vs, GL_COMPILE_STATUS, &st);
	if (!st) {
		char err[1024];
		glGetShaderInfoLog(vs, sizeof(err), 0, err);
		printf("verr %s\n", err);
	}
	const GLchar *const fss =
	    "#version 100\n"
	    "precision mediump float;\n"
	    "uniform sampler2D stex;\n"
	    "varying vec2 vuv;\n"
	    "varying vec4 vrgba;\n"
	    "void main()\n"
	    "{\n"
	    "    gl_FragColor = vrgba * texture2D(stex,vuv).r;\n"
	    "}\n";
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fss, 0);
	glCompileShader(fs);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &st);
	if (!st) {
		char err[1024];
		glGetShaderInfoLog(fs, sizeof(err), 0, err);
		printf("ferr %s\n", err);
	}
	GLuint sh = glCreateProgram();
	glAttachShader(sh, vs);
	glAttachShader(sh, fs);
	glLinkProgram(sh);
	glGetProgramiv(sh, GL_LINK_STATUS, &st);
	if (!st) {
		char err[1024];
		glGetProgramInfoLog(sh, sizeof(err), 0, err);
		printf("perr %s\n", err);
	}
	glUseProgram(sh);
	GLuint stex = glGetUniformLocation(sh, "stex");
	glUniform1i(stex, 0);
	r->sca = glGetUniformLocation(sh, "sca");
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	GLint xy = glGetAttribLocation(sh, "axy");
	assert(xy >= 0);
	GLint uv = glGetAttribLocation(sh, "auv");
	assert(uv >= 0);
	GLint rgba = glGetAttribLocation(sh, "argba");
	assert(rgba >= 0);
	glGenBuffers(1, &r->vertbo);
	glBindBuffer(GL_ARRAY_BUFFER, r->vertbo);
	glVertexAttribPointer(xy, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(xy);
	glGenBuffers(1, &r->texbo);
	glBindBuffer(GL_ARRAY_BUFFER, r->texbo);
	glVertexAttribPointer(uv, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(uv);
	glGenBuffers(1, &r->colbo);
	glBindBuffer(GL_ARRAY_BUFFER, r->colbo);
	glVertexAttribPointer(rgba, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, 0);
	glEnableVertexAttribArray(rgba);
	glGenBuffers(1, &r->indbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->indbo);
	r->trans = glGetUniformLocation(sh, "trans");
	assert(r->trans >= 0);
	glUniform2f(r->sca, 1.f / ATLAS_WIDTH, 1.f / ATLAS_HEIGHT);
	/* XXX Workaround, the previous call sets a bad value for the second */
	/* component */
	float sca[] = { 1.f / ATLAS_WIDTH, 1.f / ATLAS_HEIGHT };
	glUniform2fv(r->sca, 1, sca);
	assert(glGetError() == 0);
}

static void
flush(renderer *r, storage *s)
{
	if (s->bi == 0) {
		return;
	}

	// clang-format off
	GLfloat t[] = {
	  2. / s->w, 0, 0, 0,
	  0, -2. / s->h, 0, 0,
	  0, 0, -1, 0,
	  -1, 1, 1, 1,
	};
	// clang-format on

	unsigned bi = s->bi;
	s->bi = 0;
	glUniformMatrix4fv(r->trans, 1, GL_FALSE, t);
	glBindBuffer(GL_ARRAY_BUFFER, r->vertbo);
	glBufferData(
	    GL_ARRAY_BUFFER, bi * 8 * sizeof(s->xy[0]), s->xy, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, r->texbo);
	glBufferData(
	    GL_ARRAY_BUFFER, bi * 8 * sizeof(s->uv[0]), s->uv, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, r->colbo);
	glBufferData(GL_ARRAY_BUFFER, bi * 16 * sizeof(s->rgba[0]), s->rgba,
	    GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, r->indbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bi * 6 * sizeof(s->ind[0]),
	    s->ind, GL_DYNAMIC_DRAW);
	glDrawElements(GL_TRIANGLES, bi * 6, GL_UNSIGNED_INT, 0);
	//	assert(glGetError() == 0);
}

static void
push_quad(renderer *r, storage *s, mu_Rect dst, mu_Rect src, mu_Color color)
{
	if (s->bi == BUFFER_SIZE) {
		flush(r, s);
	}

	float sx = src.x;
	float sy = src.y;
	float sw = src.w;
	float sh = src.h;
	float dx = dst.x;
	float dy = dst.y;
	float dw = dst.w;
	float dh = dst.h;

	unsigned bi = s->bi++;
	unsigned vi = bi * 8;
	unsigned ci = bi * 16;
	unsigned ei = bi * 4;
	unsigned ii = bi * 6;
	s->ind[ii + 0] = ei + 0;
	s->ind[ii + 1] = ei + 1;
	s->ind[ii + 2] = ei + 2;
	s->ind[ii + 3] = ei + 2;
	s->ind[ii + 4] = ei + 3;
	s->ind[ii + 5] = ei + 1;
	s->uv[vi + 0] = sx;
	s->uv[vi + 1] = sy;
	s->uv[vi + 2] = sx + sw;
	s->uv[vi + 3] = sy;
	s->uv[vi + 4] = sx;
	s->uv[vi + 5] = sy + sh;
	s->uv[vi + 6] = sx + sw;
	s->uv[vi + 7] = sy + sh;
	s->xy[vi + 0] = dx;
	s->xy[vi + 1] = dy;
	s->xy[vi + 2] = dx + dw;
	s->xy[vi + 3] = dy;
	s->xy[vi + 4] = dx;
	s->xy[vi + 5] = dy + dh;
	s->xy[vi + 6] = dx + dw;
	s->xy[vi + 7] = dy + dh;
	for (unsigned i = 0; i < 4; i++) {
		s->rgba[ci + 4 * i + 0] = color.r;
		s->rgba[ci + 4 * i + 1] = color.g;
		s->rgba[ci + 4 * i + 2] = color.b;
		s->rgba[ci + 4 * i + 3] = color.a;
	}
}

void
r_draw_rect(renderer *r, storage *s, mu_Rect rect, mu_Color color)
{
	push_quad(r, s, rect, atlas[ATLAS_WHITE], color);
}

void
r_draw_text(
    renderer *r, storage *s, const char *text, mu_Vec2 pos, mu_Color color)
{
	mu_Rect dst = { pos.x, pos.y, 0, 0 };
	for (const char *p = text; *p; p++) {
		if ((*p & 0xc0) == 0x80) {
			continue;
		}
		int	chr = mu_min((unsigned char)*p, 127);
		mu_Rect src = atlas[ATLAS_FONT + chr];
		dst.w = src.w;
		dst.h = src.h;
		push_quad(r, s, dst, src, color);
		dst.x += dst.w;
	}
}

void
r_draw_icon(renderer *r, storage *s, int id, mu_Rect rect, mu_Color color)
{
	mu_Rect src = atlas[id];
	int	x = rect.x + (rect.w - src.w) / 2;
	int	y = rect.y + (rect.h - src.h) / 2;
	push_quad(r, s, mu_rect(x, y, src.w, src.h), src, color);
}

int
r_get_text_width(const char *text, int len)
{
	int res = 0;
	if (len == -1) {
		len = strlen(text);
	}
	for (const char *p = text; *p && len--; p++) {
		if ((*p & 0xc0) == 0x80) {
			continue;
		}
		int chr = mu_min((unsigned char)*p, 127);
		res += atlas[ATLAS_FONT + chr].w;
	}
	return res;
}

int
r_get_text_height(void)
{
	return 18;
}

void
r_set_clip_rect(renderer *r, storage *s, mu_Rect rect)
{
	flush(r, s);
	glScissor(rect.x, s->h - (rect.y + rect.h), rect.w, rect.h);
}

void
r_clear(renderer *r, storage *s, mu_Color clr)
{
	flush(r, s);
	glClearColor(clr.r / 255., clr.g / 255., clr.b / 255., clr.a / 255.);
	glClear(GL_COLOR_BUFFER_BIT);
}

void
r_present(renderer *r, storage *s)
{
	flush(r, s);
}

void
r_begin(renderer *r, storage *s, unsigned w, unsigned h)
{
	s->bi = 0;
	s->w = w;
	s->h = h;
	glViewport(0, 0, w, h);
	glScissor(0, 0, w, h);
}
