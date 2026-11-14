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

#ifndef UPDATE_CHECKER_H
#define UPDATE_CHECKER_H

#include <QObject>
#include <QString>

class QNetworkAccessManager;
class QNetworkReply;
class QTemporaryDir;
class QTimer;
class QWidget;

/* Checks the KholaBangla Keyboard GitHub releases for a newer version and
 * installs it with the project's own installer. */
class UpdateChecker : public QObject {
  Q_OBJECT

public:
  explicit UpdateChecker(QWidget *window, QObject *parent = nullptr);
  ~UpdateChecker() override;

  /* Check now. When `interactive` is true the result is always shown,
   * otherwise only a newer, not skipped, version is shown. */
  void check(bool interactive);

  bool autoCheckEnabled() const;
  void setAutoCheckEnabled(bool on);

  /* <0 if a is older than b, 0 if equal, >0 if newer. */
  static int compareVersions(const QString &a, const QString &b);

private:
  void autoCheck();
  void handleReply(QNetworkReply *reply, bool interactive);
  void offerUpdate(const QString &version, bool interactive);
  void startUpdate(const QString &version);
  void runInstaller(const QString &version, const QString &script);

  QWidget *m_window;
  QNetworkAccessManager *m_net;
  QTimer *m_timer;
  QTemporaryDir *m_tempDir = nullptr;
  bool m_busy = false;
};

#endif // UPDATE_CHECKER_H
