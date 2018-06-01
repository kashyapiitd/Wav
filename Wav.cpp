#include "Wav.h"

Wav::Wav(){};
Wav::~Wav(){};

status Wav::read_wave_file(string filename)
{
    /* Open the Wavfile in read mode*/
    fstream wavfile;
    wavfile.open(filename, ios::in | ios::binary);
    if (wavfile.is_open())
    {
        wavfile.read(wav_header.chunk_id, 4);
	wav_header.chunk_id[4] = 0;
	if (strcmp(wav_header.chunk_id, "RIFF") != 0)
	{
	    return status::INCORRECT_CHUNK_ID;
	}
	wavfile.read(reinterpret_cast<char *>(&wav_header.chunk_size), 4);
        wavfile.read(wav_header.format, 4);
	wav_header.format[4] = 0;
        if (strcmp(wav_header.format, "WAVE") != 0)
        {
           return status::INCORRECT_FORMAT;
 	}
	wavfile.read(wav_header.sub_chunk1_id, 3);
	wav_header.sub_chunk1_id[3] = 0;
        if (strcmp(wav_header.sub_chunk1_id, "fmt") != 0)
        {
           return status::INCORRECT_SUB_CHUNK1_ID;
 	}
	wavfile.seekg(1, ios_base::cur);
	wavfile.read(reinterpret_cast<char*> (&wav_header.sub_chunk1_size), 4);
	if (wav_header.sub_chunk1_size != 16)
	{
	    return status::INCORRECT_SUB_CHUNK1_SIZE;
	}
	wavfile.read(reinterpret_cast<char *> (&wav_header.audio_format), 2);
	if (wav_header.audio_format != 1)
	{
	    return status::INCORRECT_AUDIO_FORMAT;
	}
	wavfile.read(reinterpret_cast<char *> (&wav_header.number_channels), 2);
	if (wav_header.number_channels != 1)
	{
	    return status::INCORRECT_NUM_CHANNELS;
	}
	wavfile.read(reinterpret_cast<char *>(&wav_header.sampling_rate), 4);
        wavfile.read(reinterpret_cast<char *>(&wav_header.byte_rate), 4);
	wavfile.read(reinterpret_cast<char *>(&wav_header.block_align), 2);
	wavfile.read(reinterpret_cast<char *>(&wav_header.bits_per_sample), 2);
	bytes_per_sample = wav_header.bits_per_sample >> 3;
	if (wav_header.byte_rate != (wav_header.sampling_rate * bytes_per_sample * wav_header.number_channels))
	{
	    return status::INCORRECT_BYTE_RATE;
	} 	
	if (wav_header.block_align != (bytes_per_sample * wav_header.number_channels) )
	{
	    return status::INCORRECT_BLOCK_ALIGN;
	}
	wavfile.read(wav_header.sub_chunk2_id, 4);
	wav_header.sub_chunk2_id[4] = 0;
	if (strcmp(wav_header.sub_chunk2_id, "data") != 0)
	{
	    return status::INCORRECT_SUB_CHUNK2_ID;
	}
	wavfile.read(reinterpret_cast<char*> (&wav_header.sub_chunk2_size), 4);
	number_samples = wav_header.sub_chunk2_size / bytes_per_sample;
	if (bytes_per_sample == 2)
	{
	    data = new short[number_samples];
	}
	else if (bytes_per_sample == 4)
	{
	    data = new int[number_samples];
	}
	cout << number_samples <<" "<< wav_header.sub_chunk2_size<<" " << bytes_per_sample << endl;
	wavfile.read(reinterpret_cast<char*> (data), wav_header.sub_chunk2_size);
        return status::SUCESS;
	
    }
    else
    {
        return status::FILE_NOT_OPENED;
    }
}

