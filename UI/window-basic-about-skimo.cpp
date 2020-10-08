#include "window-basic-about-skimo.hpp"
#include "window-basic-main.hpp"
#include "qt-wrappers.hpp"
#include "remote-text.hpp"
#include <util/util.hpp>
#include <util/platform.h>
#include <platform.hpp>
#include <json11.hpp>

using namespace json11;

SkimoAbout::SkimoAbout(QWidget *parent)
	: QDialog(parent), ui(new Ui::SkimoAbout)
{
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

	ui->setupUi(this);

	QString bitness;
	QString ver;

	if (sizeof(void *) == 4)
		bitness = " (32 bit)";
	else if (sizeof(void *) == 8)
		bitness = " (64 bit)";

#ifdef HAVE_OBSCONFIG_H
	ver += OBS_VERSION;
#else
	ver += LIBOBS_API_MAJOR_VER + "." + LIBOBS_API_MINOR_VER + "." +
	       LIBOBS_API_PATCH_VER;
#endif

	ui->version->setText(ver + bitness);

	ui->contribute->setText(QTStr("About.Contribute"));
	ui->donate->setText(
		"&nbsp;&nbsp;<a href='https://github.com/skimotv/SkimoMeetingRecorder'>" +
		QTStr("About.Donate") + "</a>");
	ui->donate->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui->donate->setOpenExternalLinks(true);

	ui->getInvolved->setText(
		"&nbsp;&nbsp;<a href='https://github.com/skimotv/SkimoMeetingRecorder'>" +
		QTStr("About.GetInvolved") + "</a>");
	ui->getInvolved->setTextInteractionFlags(Qt::TextBrowserInteraction);
	ui->getInvolved->setOpenExternalLinks(true);

	ui->about->setText("<a href='#'>" + QTStr("About") + "</a>");
	ui->authors->setText("<a href='#'>" + QTStr("About.Authors") + "</a>");
	ui->license->setText("<a href='#'>" + QTStr("About.License") + "</a>");

	ui->name->setProperty("themeID", "aboutName");
	ui->version->setProperty("themeID", "aboutVersion");
	ui->about->setProperty("themeID", "aboutHLayout");
	ui->authors->setProperty("themeID", "aboutHLayout");
	ui->license->setProperty("themeID", "aboutHLayout");
	ui->info->setProperty("themeID", "aboutInfo");

	connect(ui->about, SIGNAL(clicked()), this, SLOT(ShowAbout()));
	connect(ui->authors, SIGNAL(clicked()), this, SLOT(ShowAuthors()));
	connect(ui->license, SIGNAL(clicked()), this, SLOT(ShowLicense()));

	QPointer<SkimoAbout> about(this);

	OBSBasic *main = OBSBasic::Get();
	if (main->patronJson.empty() && !main->patronJsonThread) {
		RemoteTextThread *thread = new RemoteTextThread(
			"https://obsproject.com/patreon/about-box.json",
			"application/json");
		QObject::connect(thread, &RemoteTextThread::Result, main,
				 &OBSBasic::UpdatePatronJson);
		QObject::connect(
			thread,
			SIGNAL(Result(const QString &, const QString &)), this,
			SLOT(ShowAbout()));
		main->patronJsonThread.reset(thread);
		thread->start();
	} else {
		ShowAbout();
	}
}

void SkimoAbout::on_aboutOBS_clicked()
{
	if (about)
		about->close();

	about = new OBSAbout(this);
	about->show();

	about->setAttribute(Qt::WA_DeleteOnClose, true);
}

void SkimoAbout::ShowAbout()
{
	OBSBasic *main = OBSBasic::Get();

	if (main->patronJson.empty())
		return;

	std::string error;
	Json json = Json::parse(main->patronJson, error);
	QString text;

	//The following text is taken from skimo.tv
	text += "<h1>Skimo Smart Meeting Recorder:</h1>";
	text += "<p style=\"font-size:16px;\">";


	text += "Skimo Smart Meeting Recorder is an open source screen recording software which is installable in Mac, Windows and Linux and is forked from OBS Studio.<br>";
	text += "It enables users to record any meeting regardless of provider, bookmark for remarkable events and annotate any part of the video while recording.<br>";
	text +=	"Skimo Recorder can be used along with Skimo Newton to watch the recordings, and be able to access your bookmarks and annotations in the recordings.";

	ui->textBrowser->setHtml(text);
}

void SkimoAbout::ShowAuthors()
{
	std::string path;
	QString error = "Error! File could not be read.\n\n \
		Go to: https://github.com/obsproject/obs-studio/blob/master/AUTHORS";

	if (!GetDataFilePath("authors/AUTHORS", path)) {
		ui->textBrowser->setPlainText(error);
		return;
	}

	ui->textBrowser->setPlainText(QString::fromStdString(path));

	BPtr<char> text = os_quick_read_utf8_file(path.c_str());

	if (!text || !*text) {
		ui->textBrowser->setPlainText(error);
		return;
	}

	ui->textBrowser->setPlainText(QT_UTF8(text));
}

void SkimoAbout::ShowLicense()
{
	std::string path;
	QString error = "Error! File could not be read.\n\n \
		Go to: https://github.com/obsproject/obs-studio/blob/master/COPYING";

	if (!GetDataFilePath("license/gplv2.txt", path)) {
		ui->textBrowser->setPlainText(error);
		return;
	}

	BPtr<char> text = os_quick_read_utf8_file(path.c_str());

	if (!text || !*text) {
		ui->textBrowser->setPlainText(error);
		return;
	}

	ui->textBrowser->setPlainText(QT_UTF8(text));
}
