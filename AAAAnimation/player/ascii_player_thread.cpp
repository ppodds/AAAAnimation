#include "ascii_player_thread.h"
#include <iostream>
#include "../ffmpeg/video_decoder.h"
#include "../console/console_controller.h"
#include "../transform.h"
#include <QThread>
#include<QDateTime>
#include <QString>
#include <QTime>
#include <QDebug>
#include <QDate>

AsciiPlayerThread::AsciiPlayerThread()
{
}

AsciiPlayerThread::AsciiPlayerThread(std::string file_path)
{
	this->file_path = file_path;
	this->position = 0;
}

void AsciiPlayerThread::run()
{
	char* buf = new char[1024 * 256];
	setbuf(stdout, buf);
	VideoDecoder video_decoder = VideoDecoder(file_path);
	ConsoleController console_controller;
	console_controller.set_console_font();
	console_controller.set_console_screen_buffer(video_decoder.get_video_width(), video_decoder.get_video_height());
	AVFrame* frame = video_decoder.next_frame();
	unsigned char* arr = nullptr;
	AVRational timebase_rational = video_decoder.get_video_timebase();
	// timebase in second
	float timebase = (float)timebase_rational.num / (float)timebase_rational.den;
	while (frame != nullptr) {
		// the time which frame should be played in ms 
		float play_time = frame->pts * timebase * 1000;
		if (frame->pict_type != AV_PICTURE_TYPE_NONE && position <= play_time) 
		{
			int height = frame->height;
			int width = frame->width;
			if (arr == nullptr)
				arr = new unsigned char[(long long)height * (width + 1)]();
			transform(frame->data[0], arr, width, height, frame->linesize[0]);
			// check time again
			// if this frame is too late, play it now
			if (position >= play_time)
				std::cout << arr;
			else {
				// wait until the proper time and play this frame
				QThread::currentThread()->wait(play_time - position);
				std::cout << arr;
			}
			console_controller.top();
		}
		frame = video_decoder.next_frame();
	}
	delete[] arr;
	delete[] buf;
}

void AsciiPlayerThread::setPosition(qint64 position)
{
	this->position = position;
}