/*
 *  KholaBangla Keyboard
 *  Copyright (C) 2026 tasin-py
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QClipboard>
#include <QDateTime>
#include <QDesktopServices>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFile>
#include <QKeyEvent>
#include <QLabel>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPlainTextEdit>
#include <QProcess>
#include <QPushButton>
#include <QRegularExpression>
#include <QSettings>
#include <QStandardPaths>
#include <QTemporaryDir>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include "UpdateChecker.h"

static const char *REPO_URL = "https://github.com/tasin-py/KholaBangla-Keyboard";
static const char *RAW_URL = "https://raw.githubusercontent.com/tasin-py/KholaBangla-Keyboard";
static const char *TITLE = "KholaBangla Keyboard";

static const int CHECK_INTERVAL_HOURS = 24;

/* Keeps the progress window open while the installer is still running. */
class CloseGuard : public QObject {
public:
  CloseGuard(const bool *busy, QObject *parent) : QObject(parent), m_busy(busy) {}
protected:
  bool eventFilter(QObject *obj, QEvent *ev) override {
    if (*m_busy && (ev->type() == QEvent::Close ||
        (ev->type() == QEvent::KeyPress && static_cast<QKeyEvent *>(ev)->key() == Qt::Key_Escape))) {
      ev->ignore();
      return true;
    }
    return QObject::eventFilter(obj, ev);
  }
private:
  const bool *m_busy;
};

static QSettings &store() {
  static QSettings s("KholaBangla", "Keyboard");
  return s;
}

static QNetworkRequest makeRequest(const QUrl &url) {
  QNetworkRequest req(url);
  req.setRawHeader("User-Agent", QByteArray("KholaBangla-Keyboard/") + PROJECT_VERSION);
  req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, false);
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
  req.setTransferTimeout(20000);
#endif
  return req;
}

/* Accepts "1.2.3" or "v1.2.3"; returns an empty string otherwise. */
static QString cleanVersion(QString v) {
  v = v.trimmed();
  if (v.startsWith('v') || v.startsWith('V')) v.remove(0, 1);
  static const QRegularExpression re("^\\d+(\\.\\d+){0,3}$");
  return re.match(v).hasMatch() ? v : QString();
}

UpdateChecker::UpdateChecker(QWidget *window, QObject *parent)
  : QObject(parent), m_window(window), m_net(new QNetworkAccessManager(this)), m_timer(new QTimer(this)) {
  // First check shortly after start, then look again every few hours whether a day has passed.
  QTimer::singleShot(30 * 1000, this, &UpdateChecker::autoCheck);
  m_timer->setInterval(3 * 60 * 60 * 1000);
  connect(m_timer, &QTimer::timeout, this, &UpdateChecker::autoCheck);
  m_timer->start();
}

UpdateChecker::~UpdateChecker() {
  delete m_tempDir;
}

bool UpdateChecker::autoCheckEnabled() const {
  return store().value("update/AutoCheck", true).toBool();
}

void UpdateChecker::setAutoCheckEnabled(bool on) {
  store().setValue("update/AutoCheck", on);
}

int UpdateChecker::compareVersions(const QString &a, const QString &b) {
  const QStringList pa = cleanVersion(a).split('.'), pb = cleanVersion(b).split('.');
  for (int i = 0; i < qMax(pa.size(), pb.size()); ++i) {
    const int x = i < pa.size() ? pa[i].toInt() : 0;
    const int y = i < pb.size() ? pb[i].toInt() : 0;
    if (x != y) return x < y ? -1 : 1;
  }
  return 0;
}

void UpdateChecker::autoCheck() {
  if (!autoCheckEnabled() || m_busy) return;
  const QDateTime last = store().value("update/LastCheck").toDateTime();
  if (last.isValid() && last.secsTo(QDateTime::currentDateTimeUtc()) < CHECK_INTERVAL_HOURS * 3600) return;
  check(false);
}

void UpdateChecker::check(bool interactive) {
  if (m_busy) {
    if (interactive)
      QMessageBox::information(m_window, TITLE, "An update check or update is already running.");
    return;
  }
  m_busy = true;
  // GitHub answers this address with a redirect to the newest release's tag page.
  QNetworkReply *reply = m_net->get(makeRequest(QUrl(QString(REPO_URL) + "/releases/latest")));
  connect(reply, &QNetworkReply::finished, this, [=]() { handleReply(reply, interactive); });
}

void UpdateChecker::handleReply(QNetworkReply *reply, bool interactive) {
  reply->deleteLater();
  m_busy = false;

  const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
  const QString location = QString::fromUtf8(reply->rawHeader("Location"));
  const int tagPos = location.lastIndexOf("/tag/");
  const QString latest = tagPos >= 0 ? cleanVersion(QUrl::fromPercentEncoding(location.mid(tagPos + 5).toUtf8())) : QString();

  if (status < 300 || status >= 400 || latest.isEmpty()) {
    if (interactive)
      QMessageBox::warning(m_window, TITLE,
                           "Couldn't check for updates.\nPlease check your internet connection and try again.");
    return;
  }

  store().setValue("update/LastCheck", QDateTime::currentDateTimeUtc());

  if (compareVersions(latest, PROJECT_VERSION) <= 0) {
    if (interactive)
      QMessageBox::information(m_window, TITLE,
                               QString("You have the latest version (%1).").arg(PROJECT_VERSION));
    return;
  }

  if (!interactive && store().value("update/SkipVersion").toString() == latest) return;
  offerUpdate(latest, interactive);
}

void UpdateChecker::offerUpdate(const QString &version, bool interactive) {
  for (;;) {
    QMessageBox box(QMessageBox::Information, TITLE,
                    QString("<b>KholaBangla Keyboard %1 is available.</b><br>You have version %2.")
                      .arg(version, PROJECT_VERSION),
                    QMessageBox::NoButton, m_window);
    box.setInformativeText("Update now? You will be asked for your password.");
    QPushButton *update = box.addButton("Update now", QMessageBox::AcceptRole);
    QPushButton *notes = box.addButton("What's new", QMessageBox::HelpRole);
    QPushButton *skip = interactive ? nullptr : box.addButton("Skip this version", QMessageBox::DestructiveRole);
    box.addButton("Later", QMessageBox::RejectRole);
    box.setDefaultButton(update);
    box.exec();

    if (box.clickedButton() == notes) {
      QDesktopServices::openUrl(QUrl(QString(REPO_URL) + "/releases/tag/" + version));
      continue; // show the question again
    }
    if (box.clickedButton() == update) startUpdate(version);
    else if (skip && box.clickedButton() == skip) store().setValue("update/SkipVersion", version);
    return;
  }
}

void UpdateChecker::startUpdate(const QString &version) {
  const QString manual = QString("bash -c \"$(curl -fsSL %1/main/tools/install.sh)\" -- --yes").arg(RAW_URL);

  if (QStandardPaths::findExecutable("pkexec").isEmpty()) {
    QApplication::clipboard()->setText(manual);
    QMessageBox::information(m_window, TITLE,
                             "One-click update needs pkexec (polkit), which isn't installed.\n\n"
                             "The update command has been copied. Paste it into a terminal and press Enter:\n\n" + manual);
    return;
  }

  // Use the installer from the release itself, so it matches that version.
  m_busy = true;
  QNetworkRequest req = makeRequest(QUrl(QString("%1/%2/tools/install.sh").arg(RAW_URL, version)));
  req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
  QNetworkReply *reply = m_net->get(req);
  connect(reply, &QNetworkReply::finished, this, [=]() {
    reply->deleteLater();
    m_busy = false;
    const QByteArray script = reply->readAll();
    if (reply->error() != QNetworkReply::NoError || !script.startsWith("#!")) {
      QMessageBox::warning(m_window, TITLE, "Couldn't download the update.\nPlease check your internet connection and try again.");
      return;
    }
    delete m_tempDir;
    m_tempDir = new QTemporaryDir();
    const QString path = m_tempDir->filePath("install.sh");
    QFile f(path);
    if (!m_tempDir->isValid() || !f.open(QIODevice::WriteOnly) || f.write(script) != script.size()) {
      QMessageBox::warning(m_window, TITLE, "Couldn't save the update installer.");
      return;
    }
    f.close();
    runInstaller(version, path);
  });
}

void UpdateChecker::runInstaller(const QString &version, const QString &script) {
  auto *dialog = new QDialog(m_window);
  dialog->setAttribute(Qt::WA_DeleteOnClose);
  dialog->setWindowTitle("Updating KholaBangla Keyboard");
  dialog->resize(620, 380);
  auto *label = new QLabel(QString("Installing KholaBangla Keyboard %1 ...").arg(version), dialog);
  auto *log = new QPlainTextEdit(dialog);
  log->setReadOnly(true);
  auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, dialog);
  buttons->setEnabled(false);
  connect(buttons, &QDialogButtonBox::rejected, dialog, &QDialog::close);
  auto *layout = new QVBoxLayout(dialog);
  layout->addWidget(label);
  layout->addWidget(log);
  layout->addWidget(buttons);

  dialog->installEventFilter(new CloseGuard(&m_busy, dialog));

  auto *proc = new QProcess(dialog);
  proc->setProcessChannelMode(QProcess::MergedChannels);
  connect(proc, &QProcess::readyRead, dialog, [=]() {
    static const QRegularExpression ansi("\\x1b\\[[0-9;]*[A-Za-z]");
    log->appendPlainText(QString::fromUtf8(proc->readAll()).remove(ansi).trimmed());
  });

  m_busy = true;
  connect(proc, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), dialog,
          [=](int code, QProcess::ExitStatus st) {
    m_busy = false;
    buttons->setEnabled(true);
    if (st == QProcess::NormalExit && code == 0) {
      label->setText(QString("<b>Updated to KholaBangla Keyboard %1.</b>").arg(version));
      QMessageBox ask(QMessageBox::Information, TITLE,
                      QString("KholaBangla Keyboard was updated to %1.").arg(version),
                      QMessageBox::NoButton, dialog);
      ask.setInformativeText("Restart KholaBangla Keyboard now? Typing uses the new version after you log out and back in.");
      QPushButton *restart = ask.addButton("Restart now", QMessageBox::AcceptRole);
      ask.addButton("Later", QMessageBox::RejectRole);
      ask.exec();
      if (ask.clickedButton() == restart) {
        QStringList args{"-c", "sleep 2; exec \"$0\" \"$@\"", QCoreApplication::applicationFilePath()};
        if (qApp->property("invokedAsTray").toBool()) args << "--tray";
        QProcess::startDetached("/bin/sh", args);
        qApp->quit();
      }
    } else if (code == 126 || code == 127) {
      // pkexec: the password window was closed, or permission was refused.
      label->setText("The update was cancelled.");
    } else {
      label->setText("<b>The update failed.</b> The details are below.");
    }
  });

  dialog->show();
  // pkexec clears the environment, so pass the version explicitly.
  proc->start("pkexec", {"env", "OB_VERSION=" + version, "/bin/bash", script, "--yes", "--no-setup"});
}
