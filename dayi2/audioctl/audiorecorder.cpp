/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QAudioProbe>
#include <QAudioRecorder>
#include <QDir>
#include <QFileDialog>
#include <QMediaRecorder>
#include <QtCore>
#include <QTime>
#include "basehelper.h"
#include "audiorecorder.h"
#include "qaudiolevel.h"
#include "../aliyun/osschannel.h"
static qreal getPeakValue(const QAudioFormat &format);
static QVector<qreal> getBufferLevels(const QAudioBuffer &buffer);

template <class T>
static QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels);

AudioRecorder::AudioRecorder()
{
    outputLocationSet =false;
    audioRecorder = new QAudioRecorder(this);
#if 0
    probe = new QAudioProbe;
    connect(probe, SIGNAL(audioBufferProbed(QAudioBuffer)),
            this, SLOT(processBuffer(QAudioBuffer)));
    probe->setSource(audioRecorder);
    connect(audioRecorder, SIGNAL(durationChanged(qint64)), this,
            SLOT(updateProgress(qint64)));
    connect(audioRecorder, SIGNAL(statusChanged(QMediaRecorder::Status)), this,
            SLOT(updateStatus(QMediaRecorder::Status)));
 //   connect(audioRecorder, SIGNAL(stateChanged(QMediaRecorder::State)),
 //           this, SLOT(onStateChanged(QMediaRecorder::State)));
 //   connect(audioRecorder, SIGNAL(error(QMediaRecorder::Error)), this,
//            SLOT(displayErrorMessage()));
#endif
}

AudioRecorder::~AudioRecorder()
{
    delete audioRecorder;
  //  delete probe;
}

void AudioRecorder::updateProgress(qint64 duration)
{
    if (audioRecorder->error() != QMediaRecorder::NoError || duration < 2000)
        return;
    qDebug()<< tr("Recorded %1 sec").arg(duration / 1000);
}

int AudioRecorder::recvAudioInfo(const QByteArray &messagee)
{
    WebHeadInfo info;
    int ret = BaseHelper::getWebInfo(messagee,&info);
    if(ret < 0 ){
        return -1;
    }
    // 开始录音
    if(1 == info.command_child)
    {
       startRecorder(messagee);
    }else if(2 == info.command_child)
    {
        stopRecorder(messagee);
    }


}


void AudioRecorder::updateStatus(QMediaRecorder::Status status)
{
   // QString statusMessage;

    switch (status) {
    case QMediaRecorder::RecordingStatus:
        // 文件保存位置
        qDebug()<< tr("文件保存为： %1").arg(audioRecorder->actualLocation().toString());
        break;
    case QMediaRecorder::PausedStatus:
      //  clearAudioLevels();
        qDebug()<< tr("暂停");
        break;
    case QMediaRecorder::UnloadedStatus:
    case QMediaRecorder::LoadedStatus:
   //     clearAudioLevels();
        qDebug()<< tr("停止");
    default:
        break;
    }

  //  if (audioRecorder->error() == QMediaRecorder::NoError)
        // qDebug()<<
        //ui->statusbar->showMessage(statusMessage);
}

int AudioRecorder::stopRecorder(const QByteArray &message)
{
    // 上传阿里云
    QString file =  QString::fromLocal8Bit("E:\dayi\build-DaYi-Desktop_Qt_5_9_1_MSVC2015_32bit-Debug\debug");
    OssChannel::getInstance().PushFile(file);
  //  audioRecorder->pause();
    return 0;

}
int AudioRecorder::startRecorder(const QByteArray &message)
{
    QString timeString = QString::number(BaseHelper::getTimeStamp(), 10);//nowTime.toString();
    WebHeadInfo headInfo ;
    BaseHelper::getWebInfo(message,&headInfo);
    QString Name = timeString + headInfo.userName + ".wav";
    setOutputLocation(Name);
    // 设置录音名字
    toggleRecord();
    return 0;
}




// 切换开始录音函数
void AudioRecorder::toggleRecord()
{
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/amr");
    audioSettings.setQuality(QMultimedia::HighQuality);
    audioRecorder->setEncodingSettings(audioSettings);
    audioRecorder->record();
}

// 停止录音
void AudioRecorder::togglePause()
{
    return ;
}

//创建文件输出位置
void AudioRecorder::setOutputLocation(QString Name)
{
    QString filepath = QCoreApplication::applicationDirPath();
     qDebug() << "file path:" << filepath;
    QString fileName =filepath +"/"+ Name;
    qDebug() << "fileName:" << fileName;
    audioRecorder->setOutputLocation(QUrl::fromLocalFile(fileName));
    outputLocationSet = true;
}

void AudioRecorder::clearAudioLevels()
{
    for (int i = 0; i < audioLevels.size(); ++i)
        audioLevels.at(i)->setLevel(0);
}

// This function returns the maximum possible sample value for a given audio format
qreal getPeakValue(const QAudioFormat& format)
{
    // Note: Only the most common sample formats are supported
    if (!format.isValid())
        return qreal(0);

    if (format.codec() != "audio/pcm")
        return qreal(0);

    switch (format.sampleType()) {
    case QAudioFormat::Unknown:
        break;
    case QAudioFormat::Float:
        if (format.sampleSize() != 32) // other sample formats are not supported
            return qreal(0);
        return qreal(1.00003);
    case QAudioFormat::SignedInt:
        if (format.sampleSize() == 32)
            return qreal(INT_MAX);
        if (format.sampleSize() == 16)
            return qreal(SHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(CHAR_MAX);
        break;
    case QAudioFormat::UnSignedInt:
        if (format.sampleSize() == 32)
            return qreal(UINT_MAX);
        if (format.sampleSize() == 16)
            return qreal(USHRT_MAX);
        if (format.sampleSize() == 8)
            return qreal(UCHAR_MAX);
        break;
    }

    return qreal(0);
}

// returns the audio level for each channel
QVector<qreal> getBufferLevels(const QAudioBuffer& buffer)
{
    QVector<qreal> values;

    if (!buffer.format().isValid() || buffer.format().byteOrder() != QAudioFormat::LittleEndian)
        return values;

    if (buffer.format().codec() != "audio/pcm")
        return values;

    int channelCount = buffer.format().channelCount();
    values.fill(0, channelCount);
    qreal peak_value = getPeakValue(buffer.format());
    if (qFuzzyCompare(peak_value, qreal(0)))
        return values;

    switch (buffer.format().sampleType()) {
    case QAudioFormat::Unknown:
    case QAudioFormat::UnSignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<quint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<quint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<quint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] = qAbs(values.at(i) - peak_value / 2) / (peak_value / 2);
        break;
    case QAudioFormat::Float:
        if (buffer.format().sampleSize() == 32) {
            values = getBufferLevels(buffer.constData<float>(), buffer.frameCount(), channelCount);
            for (int i = 0; i < values.size(); ++i)
                values[i] /= peak_value;
        }
        break;
    case QAudioFormat::SignedInt:
        if (buffer.format().sampleSize() == 32)
            values = getBufferLevels(buffer.constData<qint32>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 16)
            values = getBufferLevels(buffer.constData<qint16>(), buffer.frameCount(), channelCount);
        if (buffer.format().sampleSize() == 8)
            values = getBufferLevels(buffer.constData<qint8>(), buffer.frameCount(), channelCount);
        for (int i = 0; i < values.size(); ++i)
            values[i] /= peak_value;
        break;
    }

    return values;
}

template <class T>
QVector<qreal> getBufferLevels(const T *buffer, int frames, int channels)
{
    QVector<qreal> max_values;
    max_values.fill(0, channels);

    for (int i = 0; i < frames; ++i) {
        for (int j = 0; j < channels; ++j) {
            qreal value = qAbs(qreal(buffer[i * channels + j]));
            if (value > max_values.at(j))
                max_values.replace(j, value);
        }
    }

    return max_values;
}

void AudioRecorder::processBuffer(const QAudioBuffer& buffer)
{
    #if 0
    if (audioLevels.count() != buffer.format().channelCount()) {
        qDeleteAll(audioLevels);
        audioLevels.clear();
        for (int i = 0; i < buffer.format().channelCount(); ++i) {
            QAudioLevel *level = new QAudioLevel(ui->centralwidget);
            audioLevels.append(level);
            ui->levelsLayout->addWidget(level);
        }
    }
#endif
    QVector<qreal> levels = getBufferLevels(buffer);
    for (int i = 0; i < levels.count(); ++i)
        audioLevels.at(i)->setLevel(levels.at(i));
}
