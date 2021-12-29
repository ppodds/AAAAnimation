#include "video_decoder.h"
#include "stream_wrapper.h"
#include <exception>
#include <stdio.h>

VideoDecoder::VideoDecoder(std::string video_path) {
	format_context = avformat_alloc_context();
	if (avformat_open_input(&format_context, video_path.c_str(), nullptr, nullptr) != 0)
		throw std::exception("Encounter error while opening video file!");
	for (size_t i = 0; i < format_context->nb_streams; i++) {
		AVStream* in_stream = format_context->streams[i];
		AVCodecParameters* code_par = in_stream->codecpar;
		if (code_par->codec_type == AVMEDIA_TYPE_VIDEO)
			video = StreamWrapper(in_stream, code_par);
		else if (code_par->codec_type == AVMEDIA_TYPE_AUDIO)
			audio = StreamWrapper(in_stream, code_par);
	}
	video.load_codec_context();
	audio.load_codec_context();
	temp_packet = nullptr;
	current_frame = nullptr;
}

VideoDecoder::~VideoDecoder()
{
	avformat_close_input(&format_context);
	av_packet_free(&temp_packet);
	av_frame_free(&current_frame);
}

AVFrame* VideoDecoder::next_frame() {
	if (temp_packet == nullptr)
	{
		temp_packet = av_packet_alloc();
		current_frame = av_frame_alloc();
	}
	else {
		av_packet_unref(temp_packet);
		av_frame_unref(current_frame);
	}
	while (av_read_frame(format_context, temp_packet) >= 0)
	{
		AVCodecContext* codec_context;
		if (temp_packet->stream_index == video.get_stream()->index)
			codec_context = video.get_codec_context();
		else if (temp_packet->stream_index == audio.get_stream()->index)
			codec_context = audio.get_codec_context();
		else
			continue;
		avcodec_send_packet(codec_context, temp_packet);
		avcodec_receive_frame(codec_context, current_frame);
		return current_frame;
	}
	current_frame = nullptr;
	return current_frame;
}

int VideoDecoder::get_video_width()
{
	return video.get_codec_context()->width;
}

int VideoDecoder::get_video_height()
{
	return video.get_codec_context()->height;
}

AVRational VideoDecoder::get_video_timebase()
{
	return video.get_stream()->time_base;
}
