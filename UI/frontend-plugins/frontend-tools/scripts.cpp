#include "obs-module.h"
#include "scripts.hpp"
#include "frontend-tools-config.h"
#include "../../properties-view.hpp"
#include "../../qt-wrappers.hpp"

#include <QFileDialog>
#include <QPlainTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QPushButton>
#include <QFontDatabase>
#include <QFont>
#include <QDialogButtonBox>
#include <QResizeEvent>
#include <QAction>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>

#include <obs.hpp>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-scripting.h>

#include <util/config-file.h>
#include <util/platform.h>
#include <util/util.hpp>

#include <string>

#include "ui_scripts.h"

#if COMPILE_PYTHON && (defined(_WIN32) || defined(__APPLE__))
#define PYTHON_UI 1
#else
#define PYTHON_UI 0
#endif

#if ARCH_BITS == 64
#define ARCH_NAME "64bit"
#else
#define ARCH_NAME "32bit"
#endif

#define PYTHONPATH_LABEL_TEXT "PythonSettings.PythonInstallPath" ARCH_NAME

/* ----------------------------------------------------------------- */

using OBSScript = OBSObj<obs_script_t *, obs_script_destroy>;

struct ScriptData {
	std::vector<OBSScript> scripts;

	inline obs_script_t *FindScript(const char *path)
	{
		for (OBSScript &script : scripts) {
			const char *script_path = obs_script_get_path(script);
			if (strcmp(script_path, path) == 0) {
				return script;
			}
		}

		return nullptr;
	}

	bool ScriptOpened(const char *path)
	{
		return false;
	}
};

static ScriptData *scriptData = nullptr;
static ScriptsTool *scriptsWindow = nullptr;
static ScriptLogWindow *scriptLogWindow = nullptr;
static QPlainTextEdit *scriptLogWidget = nullptr;

/* ----------------------------------------------------------------- */

ScriptLogWindow::ScriptLogWindow() : QWidget(nullptr)
{
}

ScriptLogWindow::~ScriptLogWindow()
{
}

void ScriptLogWindow::ScrollChanged(int val)
{
}

void ScriptLogWindow::resizeEvent(QResizeEvent *event)
{
}

void ScriptLogWindow::AddLogMsg(int log_level, QString msg)
{
}

void ScriptLogWindow::ClearWindow()
{
}

void ScriptLogWindow::Clear()
{
}

/* ----------------------------------------------------------------- */

ScriptsTool::ScriptsTool() : QWidget(nullptr), ui(new Ui_ScriptsTool)
{
}

ScriptsTool::~ScriptsTool()
{
}

void ScriptsTool::RemoveScript(const char *path)
{
}

void ScriptsTool::ReloadScript(const char *path)
{
}

void ScriptsTool::RefreshLists()
{
}

void ScriptsTool::SetScriptDefaults(const char *path)
{
}

void ScriptsTool::on_close_clicked()
{
}

void ScriptsTool::on_addScripts_clicked()
{
}

void ScriptsTool::on_removeScripts_clicked()
{
}

void ScriptsTool::on_reloadScripts_clicked()
{
}

void ScriptsTool::on_scriptLog_clicked()
{
}

void ScriptsTool::on_pythonPathBrowse_clicked()
{
}

void ScriptsTool::on_scripts_currentRowChanged(int row)
{
}

void ScriptsTool::on_defaults_clicked()
{
}

void ScriptsTool::on_description_linkActivated(const QString &link)
{
}

/* ----------------------------------------------------------------- */

extern "C" void FreeScripts()
{
}

static void obs_event(enum obs_frontend_event event, void *)
{
}

static void load_script_data(obs_data_t *load_data, bool, void *)
{
}

static void save_script_data(obs_data_t *save_data, bool saving, void *)
{
}

static void script_log(void *, obs_script_t *script, int log_level,
		       const char *message)
{
}

extern "C" void InitScripts()
{
}
