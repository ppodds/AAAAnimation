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
	QApplication a(argc, argv);
	std::cout << "Enter an video file path:" << std::endl;
	std::string file_path;
	std::cin >> file_path;
	QVideoWidget video_widget;
	video_widget.show();
	AsciiPlayerThread ascii_player_thread(file_path);
	QMediaPlayer player;
	QAudioOutput audio_output;
	audio_output.setDevice(QMediaDevices::defaultAudioOutput());
	player.setSource(QUrl::fromLocalFile(file_path.c_str()));
	player.setVideoOutput(&video_widget);
	player.setAudioOutput(&audio_output);
	ascii_player_thread.start();
	QObject::connect(&player, &QMediaPlayer::positionChanged, &ascii_player_thread, &AsciiPlayerThread::setPosition);
	player.play();
	return a.exec();
}
