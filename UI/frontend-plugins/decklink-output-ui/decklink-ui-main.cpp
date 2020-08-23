#include <obs-module.h>
#include <obs-frontend-api.h>
#include <QMainWindow>
#include <QAction>
#include <util/util.hpp>
#include <util/platform.h>
#include <media-io/video-io.h>
#include <media-io/video-frame.h>
#include "DecklinkOutputUI.h"
#include "../../../plugins/decklink/const.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("decklink-output-ui", "en-US")


bool main_output_running = false;
bool preview_output_running = false;

obs_output_t *output;

struct preview_output {
	bool enabled;
	obs_source_t *current_source;
	obs_output_t *output;

	video_t *video_queue;
	gs_texrender_t *texrender;
	gs_stagesurf_t *stagesurface;
	uint8_t *video_data;
	uint32_t video_linesize;

	obs_video_info ovi;
};

static struct preview_output context = {0};

OBSData load_settings()
{
	return nullptr;
}

void output_stop()
{
}

void output_start()
{
}

void output_toggle()
{
}

OBSData load_preview_settings()
{
	return nullptr;
}

void on_preview_scene_changed(enum obs_frontend_event event, void *param);
void render_preview_source(void *param, uint32_t cx, uint32_t cy);

void preview_output_stop()
{
}

void preview_output_start()
{
}

void preview_output_toggle()
{
}

void on_preview_scene_changed(enum obs_frontend_event event, void *param)
{
}

void render_preview_source(void *param, uint32_t cx, uint32_t cy)
{
}

void addOutputUI(void)
{

}

static void OBSEvent(enum obs_frontend_event event, void *)
{
}

bool obs_module_load(void)
{
	return true;
}
