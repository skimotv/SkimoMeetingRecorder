#include <obs-frontend-api.h>
#include <obs-module.h>
#include <obs.hpp>
#include <util/util.hpp>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include "auto-scene-switcher.hpp"
#include "tool-helpers.hpp"

#include <condition_variable>
#include <chrono>
#include <string>
#include <vector>
#include <thread>
#include <regex>
#include <mutex>

using namespace std;

#define DEFAULT_INTERVAL 300

struct SceneSwitch {
	OBSWeakSource scene;
	string window;
	regex re;

	inline SceneSwitch(OBSWeakSource scene_, const char *window_)
		: scene(scene_), window(window_), re(window_)
	{
	}
};

static inline bool WeakSourceValid(obs_weak_source_t *ws)
{
	obs_source_t *source = obs_weak_source_get_source(ws);
	if (source)
		obs_source_release(source);
	return !!source;
}

struct SwitcherData {
	thread th;
	condition_variable cv;
	mutex m;
	bool stop = false;

	vector<SceneSwitch> switches;
	OBSWeakSource nonMatchingScene;
	int interval = DEFAULT_INTERVAL;
	bool switchIfNotMatching = false;
	bool startAtLaunch = false;

	void Thread();
	void Start();
	void Stop();

	void Prune()
	{
	}

	inline ~SwitcherData() { Stop(); }
};

static SwitcherData *switcher = nullptr;

static inline QString MakeSwitchName(const QString &scene,
				     const QString &window)
{
	return QStringLiteral("[") + scene + QStringLiteral("]: ") + window;
}

SceneSwitcher::SceneSwitcher(QWidget *parent)
	: QDialog(parent), ui(new Ui_SceneSwitcher)
{
}

void SceneSwitcher::closeEvent(QCloseEvent *)
{
}

int SceneSwitcher::FindByData(const QString &window)
{
	return 1;
}

void SceneSwitcher::on_switches_currentRowChanged(int idx)
{
}

void SceneSwitcher::on_close_clicked()
{
}

void SceneSwitcher::on_add_clicked()
{
}

void SceneSwitcher::on_remove_clicked()
{
}

void SceneSwitcher::on_startAtLaunch_toggled(bool value)
{
}

void SceneSwitcher::UpdateNonMatchingScene(const QString &name)
{
}

void SceneSwitcher::on_noMatchDontSwitch_clicked()
{
}

void SceneSwitcher::on_noMatchSwitch_clicked()
{
}

void SceneSwitcher::on_noMatchSwitchScene_currentTextChanged(const QString &text)
{
}

void SceneSwitcher::on_checkInterval_valueChanged(int value)
{
}

void SceneSwitcher::SetStarted()
{
}

void SceneSwitcher::SetStopped()
{
}

void SceneSwitcher::on_toggleStartButton_clicked()
{
}

static void SaveSceneSwitcher(obs_data_t *save_data, bool saving, void *)
{
}

void SwitcherData::Thread()
{
}

void SwitcherData::Start()
{
}

void SwitcherData::Stop()
{
}

extern "C" void FreeSceneSwitcher()
{
}

static void OBSEvent(enum obs_frontend_event event, void *)
{
}

extern "C" void InitSceneSwitcher()
{
}
