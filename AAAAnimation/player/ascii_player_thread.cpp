#include "ascii_player_thread.h"
#include <iostream>
#include "../ffmpeg/video_decoder.h"
#include "../console/console_controller.h"
#include "../transform.h"
#include "../utils.h"
#include <QThread>

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
	// stdout buffer
	char* buf = new char[1024 * 256];
	// set stdout buffer, I guess it would speed up program output
	setbuf(stdout, buf);
	// VideoDecoder instance
	VideoDecoder video_decoder = VideoDecoder(file_path);
	// ConsoleController instance
	ConsoleController console_controller;
	// set console mode to enable virtual terminal processing
	console_controller.set_console_mode();
	// set console font size, family... etc.
	console_controller.set_console_font();
	// set console screen buffer size and window size
	console_controller.set_console_screen_buffer(video_decoder.get_video_width(), video_decoder.get_video_height());
	// the latest frame which decoded by decoder
	AVFrame* frame = video_decoder.next_frame();
	// ascii frame which should be output
	unsigned char* arr = nullptr;
	// video timebase represent as a rational
	AVRational timebase_rational = video_decoder.get_video_timebase();
	// timebase in second
	float timebase = (float)timebase_rational.num / (float)timebase_rational.den;
	while (frame != nullptr) {
		// the time which frame should be played in ms 
		float play_time = frame->pts * timebase * 1000;
		// only calculate when this frame is a video frame and this frame is not too late to play
		if (frame->pict_type != AV_PICTURE_TYPE_NONE && position <= play_time) 
		{
			// video height
			int height = frame->height;
			// video width
			int width = frame->width;
			// initialize ascii frame buffer
			if (arr == nullptr)
				arr = new unsigned char[(long long)height * (width + 1)]();
			// calculate ascii frame from video's luminance
			transform(frame->data[0], arr, width, height, frame->linesize[0]);
			// check time again
			// wait until the proper time and play this frame
			wait_until_smaller(play_time - 150, &position); // 150ms offset to avoid drop too many frames
			// output ascii frame
			std::cout << arr;
			// set cursur position to left top
			console_controller.top();
		}
		// get next frame from decoder
		frame = video_decoder.next_frame();
	}
	// release memory
	delete[] arr;
	delete[] buf;
}

void AsciiPlayerThread::setPosition(qint64 position)
{
	this->position = position;
}