#include <QtWidgets/QApplication>
#include "player/ascii_player_thread.h"
#include <QVideoWidget>
#include <iostream>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QMediaDevices>
#include <QAudioDevice>

int main(int argc, char *argv[])
{
	// QApplication instance
	QApplication a(argc, argv);
	// input hint
	std::cout << "Input an video file path:" << std::endl;
	// user input
	std::string file_path;
	std::cin >> file_path;
	// QVideoWidget instance(window)
	QVideoWidget video_widget;
	// show window
	video_widget.show();
	// AsciiPlayerThread instance
	AsciiPlayerThread ascii_player_thread(file_path);
	// QMediaPlayer instance
	QMediaPlayer player;
	// QAudioO
	QAudioOutput audio_output;
	// set audio_output's output device as default audio output device
	audio_output.setDevice(QMediaDevices::defaultAudioOutput());
	// set file played by QMediaPlayer 
	player.setSource(QUrl::fromLocalFile(file_path.c_str()));
	// set video output to window
	player.setVideoOutput(&video_widget);
	// set audio output to default output device
	player.setAudioOutput(&audio_output);
	// start playing ascii animation
	ascii_player_thread.start();
	// connect QMediaPlayer's position signal to AsciiPlayerThread's slot
	QObject::connect(&player, &QMediaPlayer::positionChanged, &ascii_player_thread, &AsciiPlayerThread::setPosition);
	// start playing video file
	player.play();
	return a.exec();
}
