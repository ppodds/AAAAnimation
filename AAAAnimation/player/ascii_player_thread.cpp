#include "ascii_player_thread.h"
#include <iostream>
#include "../ffmpeg/video_decoder.h"
#include "../console/console_controller.h"
#include "../transform.h"

AsciiPlayerThread::AsciiPlayerThread()
{
}

AsciiPlayerThread::AsciiPlayerThread(std::string file_path)
{
	this->file_path = file_path;
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
	while (frame != nullptr) {
		if (frame->pict_type != AV_PICTURE_TYPE_NONE)
		{
			int height = frame->height;
			int width = frame->width;
			if (arr == nullptr)
				arr = new unsigned char[(long long)height * (width + 1)]();
			transform(frame->data[0], arr, width, height, frame->linesize[0]);
			std::cout << arr;
			QThread::currentThread()->msleep(1 / 30000);
			console_controller.top();
		}

		frame = video_decoder.next_frame();
	}
	delete[] arr;
	delete[] buf;
}
