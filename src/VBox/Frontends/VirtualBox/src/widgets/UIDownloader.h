/** @file
 *
 * VBox frontends: Qt GUI ("VirtualBox"):
 * UIDownloader class declaration
 */

/*
 * Copyright (C) 2006-2007 Sun Microsystems, Inc.
 *
 * This file is part of VirtualBox Open Source Edition (OSE), as
 * available from http://www.virtualbox.org. This file is free software;
 * you can redistribute it and/or modify it under the terms of the GNU
 * General Public License (GPL) as published by the Free Software
 * Foundation, in version 2 as it comes in the "COPYING" file of the
 * VirtualBox OSE distribution. VirtualBox OSE is distributed in the
 * hope that it will be useful, but WITHOUT ANY WARRANTY of any kind.
 *
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 USA or visit http://www.sun.com if you need
 * additional information or have any questions.
 */

#ifndef __UIDownloader_h__
#define __UIDownloader_h__

/* Global includes */
#include <QUrl>
#include <QWidget>

/* Local forward declarations */
class QIHttp;
class VBoxMiniCancelButton;

/* Global forward declarations */
class QHttpResponseHeader;
class QProgressBar;

class UIMiniProcessWidget : public QWidget
{
    Q_OBJECT;

public:

    UIMiniProcessWidget(QWidget *pParent = 0);

    void setCancelButtonText(const QString &strText);
    QString cancelButtonText() const;

    void setCancelButtonToolTip(const QString &strText);
    QString cancelButtonToolTip() const;

    void setProgressBarToolTip(const QString &strText);
    QString progressBarToolTip() const;

    void setSource(const QString &strSource);
    QString source() const;

signals:

    void sigCancel();

public slots:

    virtual void sltProcess(int cDone, int cTotal);

private:

    /* Private member vars */
    QProgressBar *m_pProgressBar;
    VBoxMiniCancelButton *m_pCancelButton;

    QString m_strSource;
};

/**
 * The UIDownloader class is QWidget class re-implementation which embeds
 * into the Dialog's status-bar and allows background http downloading.
 * This class is not supposed to be used itself and made for sub-classing only.
 *
 * This class has two parts:
 * 1. Acknowledging (getting information about target presence and size).
 * 2. Downloading (starting and handling file downloading process).
 * Every subclass can determine using or not those two parts and handling
 * the result of those parts itself.
 */
class UIDownloader : public QObject
{
    Q_OBJECT;

public:

    UIDownloader();

    void setSource(const QString &strSource);
    QString source() const;
    void setTarget(const QString &strTarget);
    QString target() const;

    virtual void startDownload() = 0;

signals:
    void sigDownloadProcess(int cDone, int cTotal);
    void sigFinished();

protected slots:

    /* Acknowledging part */
    virtual void acknowledgeStart();
    virtual void acknowledgeProcess(const QHttpResponseHeader &response);
    virtual void acknowledgeFinished(bool fError);

    /* Downloading part */
    virtual void downloadStart();
    virtual void downloadProcess(int cDone, int cTotal);
    virtual void downloadFinished(bool fError);

    /* Common slots */
    virtual void cancelDownloading();
    virtual void abortDownload(const QString &strError);
    virtual void suicide();

protected:

    /* In sub-class this function will show the user downloading object size
     * and ask him about downloading confirmation. Returns user response. */
    virtual bool confirmDownload() = 0;

    /* In sub-class this function will show the user which error happens
     * in context of downloading file and executing his request. */
    virtual void warnAboutError(const QString &strError) = 0;

    QUrl m_source;
    QString m_strTarget;
    QIHttp *m_pHttp;
};

#endif // __UIDownloader_h__

