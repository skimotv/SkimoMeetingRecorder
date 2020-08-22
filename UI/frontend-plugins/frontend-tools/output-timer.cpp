#include <obs-frontend-api.h>
#include <obs-module.h>
#include <obs.hpp>
#include <util/util.hpp>
#include <QAction>
#include <QMainWindow>
#include <QTimer>
#include <QObject>
#include "output-timer.hpp"

using namespace std;

OutputTimer *ot;

OutputTimer::OutputTimer(QWidget *parent)
	: QDialog(parent), ui(new Ui_OutputTimer)
{
}

void OutputTimer::closeEvent(QCloseEvent *)
{
}

void OutputTimer::StreamingTimerButton()
{
}

void OutputTimer::RecordingTimerButton()
{
}

void OutputTimer::StreamTimerStart()
{
}

void OutputTimer::RecordTimerStart()
{
}

void OutputTimer::StreamTimerStop()
{
}

void OutputTimer::RecordTimerStop()
{
}

void OutputTimer::UpdateStreamTimerDisplay()
{
}

void OutputTimer::UpdateRecordTimerDisplay()
{
}

void OutputTimer::PauseRecordingTimer()
{
}

void OutputTimer::UnpauseRecordingTimer()
{
}

void OutputTimer::ShowHideDialog()
{
}

void OutputTimer::EventStopStreaming()
{
}

void OutputTimer::EventStopRecording()
{
}

static void SaveOutputTimer(obs_data_t *save_data, bool saving, void *)
{
}

extern "C" void FreeOutputTimer() {}

static void OBSEvent(enum obs_frontend_event event, void *)
{
}

extern "C" void InitOutputTimer()
{
}
