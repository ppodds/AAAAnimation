#include "aaaanimation.h"
#include <QtWidgets/QApplication>
#include <iostream>
#include <string>
#include <cwchar>
#include "ffmpeg/video_decoder.h"
#include <thread>
#include <iostream>
#include "main.h"
#include "console/console_controller.h"

extern "C" void transform(unsigned char*, unsigned char*, unsigned int, unsigned int, int);

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AAAAnimation w;
	w.show();
	char buf[1024 * 256];
	setbuf(stdout, buf);
	std::cout << "Enter an video file path:" << std::endl;
	std::string file_path;
	std::cin >> file_path;
	VideoDecoder video_decoder = VideoDecoder(file_path);
	ConsoleController console_controller;
	console_controller.set_console_font();
	console_controller.set_console_screen_buffer(video_decoder.get_video_width(),video_decoder.get_video_height());
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
			std::this_thread::sleep_for(std::chrono::seconds(1 / 30));
			console_controller.top();
		}
		frame = video_decoder.next_frame();
	}
	delete[] arr;
	return a.exec();
}
